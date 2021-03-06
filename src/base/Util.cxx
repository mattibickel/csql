#include<Util.h>
#include<Config.h>

unsigned int Util::hashBinary(char *strVal, int length)
{
    unsigned int hval, g;
    hval = 0;
    char *str =strVal;
    int iter = 0;
    while (iter != length)
    {
        hval <<= 4;
        hval += (unsigned int) *str++;
        g = hval & ((unsigned int) 0xf << (32 - 4));
        if (g != 0)
            {
                hval ^= g >> (32 - 8);
                hval ^= g;
            }
        iter++;
    }
    return hval;
}

unsigned int Util::hashString(char *strVal)
{
    unsigned int hval, g;
    hval = 0;
    char *str =strVal;
    while (*str != '\0')
    {
        hval <<= 4;
        hval += (unsigned int) *str++;
        g = hval & ((unsigned int) 0xf << (32 - 4));
        if (g != 0)
        {
            hval ^= g >> (32 - 8);
            hval ^= g;
        }
    }
    return hval;
}

DbRetVal GlobalUniqueID::create()
{
    int key = Conf::config.getShmIDKey();
    int id = os::shm_create(key, MAX_UNIQUE_ID *sizeof(int), 0666);
    if (-1 == id) {
        if (errno != EEXIST)
            printError(ErrOS, "Unable to create shared memory");
        return ErrOS;
    }
    ptr = os::shm_attach(id, NULL, 0);
    if ((void*)-1 == ptr) {
        printError(ErrOS, "Unable to attach shared memory");
        return ErrOS;
    }
    memset(ptr, 0, MAX_UNIQUE_ID *sizeof(int));
    return OK;
}
   
DbRetVal GlobalUniqueID::open() 
{
    if (ptr != NULL) return OK;
    int key = Conf::config.getShmIDKey();
    int id = os::shm_open(key, MAX_UNIQUE_ID *sizeof(int), 0666);
    if (-1 == id) {
        printError(ErrOS, "Unable to create shared memory");
    }
    ptr = os::shm_attach(id, NULL, 0);
    if ((void*)-1 == ptr) {
        printError(ErrOS, "Unable to create shared memory");
    }
    return OK;
}

DbRetVal GlobalUniqueID::destroy()
{
    int key = Conf::config.getShmIDKey();
    int id = os::shm_open(key, MAX_UNIQUE_ID *sizeof(int), 0666);
    if (-1 == id) {
//        printError(ErrOS, "Unable to open shared memory");
        return ErrOS;
    }
    os::shm_remove(id);
    return OK;
}

int GlobalUniqueID::getID(UniqueIDType type)
{
    InUse *id = (int*)(((char*)ptr) + sizeof(int) * type);
    InUse oldVal = *id;
    InUse newVal = oldVal + 1;
    int ret = Mutex::CASGen(id, oldVal, newVal);
    if (ret) return -1;
    return *id;
}

