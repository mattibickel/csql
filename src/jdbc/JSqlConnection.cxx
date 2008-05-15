#include<AbsSqlStatement.h>
#include<SqlFactory.h>
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class JSqlConnection */

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     JSqlConnection
 * Method:    alloc
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlConnection_alloc
  (JNIEnv *env, jobject obj, jint mode)
{
    jclass cls;
    jfieldID fid;

    // Create new SqlConnection
    AbsSqlConnection *con;
    if (mode ==1 )
        con = SqlFactory::createConnection(CSql);
    else
        con = SqlFactory::createConnection(CSqlGateway);

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlConPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    env->SetLongField( obj, fid, (jlong) con );
    return;
}

/*
 * Class:     JSqlConnection
 * Method:    free
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_csql_jdbc_JSqlConnection_free
  (JNIEnv *env, jobject obj)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlConPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return;
    }
    AbsSqlConnection *con = (AbsSqlConnection*) env->GetLongField( obj, fid );
    delete con;
    return;
}

/*
 * Class:     JSqlConnection
 * Method:    connect
 * Signature: (Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlConnection_connect
  (JNIEnv *env, jobject obj, jstring user, jstring pass)
{
    jclass cls;
    jfieldID fid;
    char *username=0, *password=0;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlConPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return( -1 );
    }
    AbsSqlConnection *con = (AbsSqlConnection*) env->GetLongField( obj, fid );
    jboolean isCopy = JNI_TRUE;
    username = (char*) env->GetStringUTFChars( user, &isCopy );
    password = (char*) env->GetStringUTFChars( pass, &isCopy );
    jint rv = (jint) con->connect(username, password);
    return rv;
}

/*
 * Class:     JSqlConnection
 * Method:    disconnect
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlConnection_disconnect
  (JNIEnv *env, jobject obj)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlConPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return( -1 );
    }
    AbsSqlConnection *con = (AbsSqlConnection*) env->GetLongField( obj, fid );
    jint rv = (jint) con->disconnect();
    return rv;

}

/*
 * Class:     JSqlConnection
 * Method:    isOpen
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_csql_jdbc_JSqlConnection_isOpen
  (JNIEnv *env, jobject obj)
{
    //TODO
    return false;
}

/*
 * Class:     JSqlConnection
 * Method:    beginTrans
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlConnection_beginTrans
  (JNIEnv *env, jobject obj, jint type)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlConPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return( -1 );
    }
    AbsSqlConnection *con = (AbsSqlConnection*) env->GetLongField( obj, fid );
    jint rv = (jint) con->beginTrans((IsolationLevel) type );
    return rv;
}

/*
 * Class:     JSqlConnection
 * Method:    commit
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlConnection_commit
  (JNIEnv *env, jobject obj)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlConPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return( -1 );
    }
    AbsSqlConnection *con = (AbsSqlConnection*) env->GetLongField( obj, fid );
    jint rv = (jint) con->commit();
    return rv;

}

/*
 * Class:     JSqlConnection
 * Method:    rollback
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_csql_jdbc_JSqlConnection_rollback
  (JNIEnv *env, jobject obj)
{
    jclass cls;
    jfieldID fid;

    cls = env->GetObjectClass( obj );
    fid = env->GetFieldID( cls, "sqlConPtr", "J");
    if (fid == 0)
    {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,"JNI: GetFieldID failed.\n");
        return( -1 );
    }
    AbsSqlConnection *con = (AbsSqlConnection*) env->GetLongField( obj, fid );
    jint rv = (jint) con->rollback();
    return rv;

}

#ifdef __cplusplus
}
#endif
