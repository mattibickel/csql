/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef DATATYPE_H
#define DATATYPE_H

#ifndef WINNT
//#include<sqlext.h>
//#include<sqltypes.h>
#endif

#include<ErrorType.h>
#include<Config.h>
#include<Function.h>
typedef int JulianRep;


/**
* @class DataType
* Data Types supported by the database system.
* <br/>
* 
*/
enum DataType {
   typeInt         =  0, /**<integer type*/
   typeLong        =  1,
   typeLongLong    =  2,
   typeShort       =  3,
   typeByteInt     =  4,

   typeDouble      =  10,
   typeFloat       =  11,
   typeDecimal     =  12,

   typeDate        =  20,
   typeTime        =  21,
   typeTimeStamp   =  22,

   typeString      =  30,
   typeBinary      =  31,
   typeVarchar     =  32,

   typeComposite   =  98,
   typeULong       =  99,
   typeUnknown     =  100
};

/**
* @class ComparisionOp
* Comparision operators supported by the database system.
* <br/>
* 
*/
enum ComparisionOp {
    OpEquals = 0,
    OpNotEquals,
    OpLessThan,
    OpLessThanEquals,
    OpGreaterThan,
    OpGreaterThanEquals,
    OpLike, // for Like operator
    OpIsNull,
    OpInvalidComparisionOp
};
static char CompOpNames[][20] =
{
    "Equals", "NotEquals", "LessThan", "LessThanEquals", "GreaterThan", 
    "GreaterThanEquals", "Like", "isNULL", "Invalid"
};


/**
* @class LogicalOp
* Logical operators supported by the database system.
* <br/>
* 
*/
enum LogicalOp {
    OpAnd = 0,
    OpOr,
    OpNot,
    OpInvalidLogicalOp
};

static char LogOpNames[][10] =
{
    "AND", "OR", "NOT", "Invalid"
};

class DllExport AllDataType
{
    public:
    inline static long size(DataType type, int length =0);
    static char* getSQLString(DataType type);
    static short convertToSQLType(DataType type);
    static short convertToCSQLSQLType(DataType type);
    static short convertToSQL_C_Type(DataType type,TDBInfo tdbname=mysql);
    static DataType convertFromSQLType(short type,int length=0, int scale=0, TDBInfo tdbname=mysql);

    inline static void copyVal(void* dest, void *src, DataType type, int length = 0,int dbFlag=0);
    inline static void copyZeroVal(void* dest, DataType type, int length = 0);
    inline static void cachecopyVal(void* dest, void *src, DataType type, int length = 0,int dbFlag=0);
    inline static void addVal(void* dest, void *src, DataType type);
    static void divVal(double* dest, int src, DataType type);
    static void subVal(void* dest, void *src, DataType type);
    static void mulVal(void* dest, void *src, DataType type);
    static void mudVal(void* dest, void *src, DataType type);
    static void divVal(void* dest, void *src, DataType type);
    static void increment(void* dest, void *src, DataType type);
    static bool isValueZero(void* dest, DataType type);

    inline static bool compareVal(void *src1, void *src2, ComparisionOp op,
                           DataType type, long length = 0);
    static bool compareIntVal(void* src1, void* src2, ComparisionOp op);
    static bool compareLongVal(void* src1, void* src2, ComparisionOp op);
    static bool compareLongLongVal(void* src1, void* src2, ComparisionOp op);
    static bool compareShortVal(void* src1, void* src2, ComparisionOp op);
    static bool compareByteIntVal(void* src1, void* src2, ComparisionOp op);
    static bool compareDoubleVal(void* src1, void* src2, ComparisionOp op);
    static bool compareFloatVal(void* src1, void* src2, ComparisionOp op);
    static bool compareDateVal(void* src1, void* src2, ComparisionOp op);
    static bool compareTimeVal(void* src1, void* src2, ComparisionOp op);
    static bool compareTimeStampVal(void* src1, void* src2, ComparisionOp op);
    static bool compareStringVal(void* src1, void* src2, ComparisionOp op);
    static bool compareBinaryVal(void* src1, void* src2,
                                 ComparisionOp op, int length);


    static void convert(DataType srcType, void *src, DataType destType, void *dest, int length=0);
    static void convertToInt(void* dest, void* src, DataType srcType);
    static void convertToLong(void* dest, void* src, DataType srcType);
    static void convertToLongLong(void* dest, void* src, DataType srcType);
    static void convertToShort(void* dest, void* src, DataType srcType);
    static void convertToByteInt(void* dest, void* src, DataType srcType);
    static void convertToFloat(void* dest, void* src, DataType srcType);
    static void convertToDouble(void* dest, void* src, DataType srcType);
    static void convertToString(void* dest, void* src, DataType srcType, int length=0,TDBInfo tdbname=mysql);
    static void convertToDate(void* dest, void* src, DataType srcType);
    static void convertToTime(void* dest, void* src, DataType srcType);
    static void convertToTimeStamp(void* dest, void* src, DataType srcType);
    static void convertToBinary(void* dest, void* src, DataType srcType, int length);
    static DataType getCsqlTypeFromFunctionType(FunctionType type);
    static  DataType getCsqlTypeFromFunctionTypeForComparision(FunctionType type);
    static void memoryset(void *value,DataType type);
    inline static ComparisionOp getComparisionOperator(char *str);

    static void* alloc(DataType type, int length =0);
    static DbRetVal strToValue(void *dest, char *src, DataType type, int length=0);
    static int printVal(void *src, DataType type, int length,int dbFlag=0);
    inline static bool isValidFieldForAvg(DataType type);
};


/**
* @class ByteInt
* Represents 8 bit integer.
* <br/>
* 
*/
class DllExport ByteInt {

    public:
    ByteInt() { }

    /** copy constructor
    */ 
    ByteInt(const ByteInt &v) { val = v.val; }
    /** constructor with char
    *   @param v char value
    */  
    ByteInt(char v) { val = v; }
    operator int() const { return (int) val; }
    char operator=(ByteInt v)   { return val = v.val; }
    char operator=(char v)          { return val = v; }
    char operator+=(ByteInt v)  { return val += v.val; }
    char operator+=(char v)         { return val += v; }
    char operator-=(ByteInt v)  { return val -= v.val; }
    char operator-=(char v)         { return val -= v; }
    char operator*=(ByteInt v)  { return val *= v.val; }
    char operator*=(char v)         { return val *= v; }
    char operator/=(ByteInt v)  { return val /= v.val; }
    char operator/=(char v)         { return val /= v; }
    char operator%=(ByteInt v)  { return val %= v.val; }
    char operator%=(char v)         { return val %= v; }
    char operator<<=(ByteInt v) { return val <<= v.val; }
    char operator<<=(char v)        { return val <<= v; }
    char operator>>=(ByteInt v) { return val >>= v.val; }
    char operator>>=(char v)        { return val >>= v; }
    char operator&=(ByteInt v)  { return val &= v.val; }
    char operator&=(char v)         { return val &= v; }
    char operator|=(ByteInt v)  { return val |= v.val; }
    char operator|=(char v)         { return val |= v; }
    char operator^=(ByteInt v)  { return val ^= v.val; }
    char operator^=(char v)         { return val ^= v; }
    char operator++()               { return val++; }
    char operator++(int)               { char tmp = val; val++; return val; }
    char operator--()               { return val--; }
    char operator--(int)               { char tmp = val; val--; return val; }

    private:
    signed char val;
};


/**
* @class Date
* Represents Date Data type.
* <br/>
* 
*/
class DllExport Date {  // The class a user would declare to hold date

    public:
    Date() {julianDate = 0;}
    Date(JulianRep julian) : julianDate(julian) {}

    /** constructor with year, month, day
    *   @param year year
    *   @param month month
    *   @param day day
    */  
    Date(int year, int month, int day);

    Date(const Date &d2) { julianDate = d2.julianDate; }
    Date& operator=(const Date& d2)
        { julianDate=d2.julianDate; return *this; }

    /** sets the date with specified year, month, day
    *   @param year year
    *   @param month month
    *   @param day day
    */  
    int set(int year, int month, int day);
    int set(const struct tm *tmptr);

    /** get year, month, day of the date
    *   @param year year IN
    *   @param month month IN
    *   @param day day IN
    */  
    int get(int &year, int &month, int &day) const;

    /** checks for the validity of the date
    */  
    bool isValid() const;

    /** resets the date to zero
    */  
    void setNull() { julianDate = 0;}

    /** returns day of the week
    */  
    int dayOfWeek() const;

    /** returns day of the week.
    * values are "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday".
    */  
    const char *dayOfWeekName() const;

    /** returns day of the week abbreviation
    * values are "Sun",    "Mon",    "Tue",     "Wed",       "Thu",      "Fri",    "Sat"
    */
    const char *dayOfWeekAbbr() const;

    /** returns day of the week.
    * values are "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday".
    */  
    static const char *dayOfWeekName(int day); // 0--> Sunday

    /** returns day of the week abbreviation
    * values are "Sun",    "Mon",    "Tue",     "Wed",       "Thu",      "Fri",    "Sat"
    */
    static const char *dayOfWeekAbbr(int day);

    static int dayOfWeek(JulianRep juldate);


    void addDay(int noOfDays);
    void subDay(int noOfDays);
    void addMonth(int noOfMons);
    void subMonth(int noOfMons);
    void addYear(int noOfYrs);
    void subYear(int noOfYrs);
    
    /** returns the day of the month. Values are 1 to 31
    */  
    int dayOfMonth() const;

    int dayOfYear() const;

    /** returns the month Values are 1 to 12.
    */
    int month() const;

    /** returns the month name
    *   values are "January", "February", "March",     "April",   "May",      "June",
    *   "July",    "August",   "September", "October", "November", "December"
    */
    const char *monthName() const;

    /** returns the month name abbreviation
    * values are "Jan",     "Feb",      "Mar",      "Apr",     "May",      "Jun",
    * "Jul",     "Aug",      "Sep",      "Oct",     "Nov",      "Dec"
    */
    const char *monthAbbr() const;

    /** returns the month name
    *   values are "January", "February", "March",     "April",   "May",      "June",
    *   "July",    "August",   "September", "October", "November", "December"
    */
    static const char *monthName(int month);


    /** returns the month name abbreviation
    * values are "Jan",     "Feb",      "Mar",      "Apr",     "May",      "Jun",
    * "Jul",     "Aug",      "Sep",      "Oct",     "Nov",      "Dec"
    */
    static const char *monthAbbr(int month);

    /** parses the date string passed and stores it
    *It should of the format "mm/dd/yyyy"
    */
    int parseFrom(const char *s);
    
    int getCalDay() { return julianDate;}
    static void changeToCsqlFormat(char *src);


    Date &operator++() { julianDate++; return *this; }
    Date &operator--() { julianDate--; return *this; }

    Date &operator+=(int days) { julianDate += days; return *this;}
    Date &operator-=(int days) { julianDate -= days; return *this;}

    /** returns the year
    */  
    int year() const;

    /** checks for the validity of the date
    */  
    static bool isValidDate(int year, int month, int day);

    friend Date  operator+(const Date &d1, int days);
    friend Date  operator+(int days, const Date &d1);
    friend Date  operator-(const Date &d1, int days);
    friend int  operator-(const Date &d1, const Date & d2);
    friend int  operator<(const Date &d1 ,const Date &d2);
    friend int  operator>(const Date &d1 ,const Date &d2);
    friend int  operator<=(const Date &d1 ,const Date &d2);
    friend int  operator>=(const Date &d1 ,const Date &d2);
    friend int  operator==(const Date &d1 ,const Date &d2);
    friend int  operator!=(const Date &d1 ,const Date &d2);

    /** checks for leap year
    */  
    static bool isLeapYear(int year);

    /** returns the number of days in the specified month of the year.
    */  
    static int daysInMonth(int month, int year);

    static int YMDToJulian(int year,int mon,int day, JulianRep &julian);
    static int julianToYMD(JulianRep julian,int &year,int &month,int &day);

    private:
    JulianRep julianDate;



};

/**
* @class Time
* Represents Time Data type.
* <br/>
* 
*/
class DllExport Time {  // The class a user would declare to hold time
    public:
    Time() {timeVal = 0;}

    /** Overloaded constructor
    *   @param hours hours
    *   @param mins mins
    *   @param secs secs
    *   @param usec usec
    */  
    Time(int hours, int mins, int secs, int usec = 0);
    Time(int totalSecs) : timeVal(totalSecs) {;}
    Time(const Time &d2) { timeVal = d2.timeVal; }
    Time& operator=(const Time& d2) { timeVal=d2.timeVal; return *this; }

    /** sets the time with specified hours, mins, secs
    *   @param hours hours
    *   @param mins mins
    *   @param secs secs
    *   @param usec usec
    */  
    int set(int hours, int mins, int secs, int usec = 0);

    /** retrieves the time using IN parameters
    *   @param hours hours
    *   @param mins mins
    *   @param secs secs
    */  
    int get(int &hours, int &mins, int &secs) const;




    int getCalSec(){ return timeVal/10000; }
    /** checks for the validity of the time
    */  
    bool isValid() const;

    /** resets the time
    */  
    void setNull() { timeVal = -1;}

    int secondsSinceMidnight() const { return timeVal/10000;}

    /** returns the microsecs
    */ 
    int usec() const; // to nearest 100 of usec.

    /** returns the millisecs
    */  
    int msec() const;

    /** returns the secs
    */ 
    int seconds() const;

    /** returns the minutes
    */ 
    int minutes() const;

    /** returns the hours
    */ 
    int hours() const;

    //
    int addSec(int secs);
    int subSec(int secs);
    int addMin(int mins);
    int subMin(int mins);
    int addHour(int hours);
    int subHour(int hours);

    /** sets the millisecs
    */ 
    int setMsec(int ms);

    /** sets the microsecs
    */ 
    int setUsec(int us);

    /** parses the time string passed and stores it
    *It should of the format "hh:mm::ss"
    */
    int parseFrom(const char *s);

    Time &operator++() { timeVal += 10000; return *this; }
    Time &operator--() { timeVal -= 10000; return *this; }

    Time &operator+=(int seconds) { timeVal += seconds*10000; return *this; }
    Time &operator-=(int seconds) { timeVal -= seconds*10000; return *this; }


    /** checks for the validity of the time specified
    */  
    static bool isValidTime(int hours, int mins, int secs);

    friend Time operator+(const Time &t1, int seconds);
    friend Time operator+(int seconds, const Time &t1);
    friend Time operator-(const Time &t1, int seconds);
    friend int  operator-(const Time &t1, const Time& t2);
    friend int  operator<(const Time &t1 ,const Time &t2 );
    friend int  operator>(const Time &t1 ,const Time &t2 );
    friend int  operator<=(const Time &t1 ,const Time &t2 );
    friend int  operator>=(const Time &t1 ,const Time &t2 );
    friend int  operator==(const Time &t1 ,const Time &t2 );
    friend int  operator!=(const Time &t1 ,const Time &t2 );


    private:
    int timeVal;
};

/**
* @class TimeStamp
* Represents TimeStamp Data type.
* <br/>
* 
*/
class DllExport TimeStamp {

    public:
    TimeStamp() {}

    /** Overloaded constructor
    *   @param year year
    *   @param month month
    *   @param day day
    *   @param hours hours
    *   @param mins mins
    *   @param secs secs
    *   @param usec usec
    */  
    TimeStamp(int year, int month, int day, int hour, int minute, int sec, int usec = 0) :
        date(year, month, day), time(hour, minute, sec, usec) { }

    TimeStamp(const TimeStamp &ts)
    { date = ts.date; time = ts.time; }
    TimeStamp(const Date &d, Time &t) : date(d), time(t) {}


    TimeStamp& operator=(const TimeStamp& d2)
        { date=d2.date; time = d2.time; return *this; }

    /** get year, month, day from the date part of the timestamp
    *   @param year year IN
    *   @param month month IN
    *   @param day day IN
    */
    int getDate(int &year, int &month, int &day)
         { return date.get(year, month, day); }

    /** get the date part of the timestamp 
    *   @param Date date
    */ 
   void getDate(Date &newDate) const
         { newDate = date; }

    /** sets the date with specified year, month, day
    *   @param year year
    *   @param month month
    *   @param day day
    */
    int setDate(int year, int month, int day)
         { return date.set(year, month, day); }

    /** set the date part of the timestamp 
    *   @param Date date
    */
    void setDate(const Date &newDate)
         { date = newDate; }


    operator Date() { return date; }
    operator Time() { return time; }



    /** retrieves the time using IN parameters
    *   @param hours hours
    *   @param mins mins
    *   @param secs secs
    */
    int getTime(int &hours, int &mins, int &secs) const
         { return time.get(hours, mins, secs); }
    /** retrieves the time part of the timestamp 
    *   @param newTime Time
    */
    void getTime(Time &newTime) const
         { newTime = time; }

    /** sets the time with specified hours, mins, secs
    *   @param hours hours
    *   @param mins mins
    *   @param secs secs
    *   @param usec usec
    */
    int setTime(int hours, int mins, int secs, int usec = 0)
         { return time.set(hours, mins, secs, usec); }

    /** set the time part of the timestamp 
    *   @param newTime Time
    */
    void setTime(const Time &newTime)
         { time = newTime; }

    /** checks for the validity of the timestamp
    */  
    bool isValid() const { return date.isValid() && time.isValid(); }

    /** resets the date and time */
    void setNull() { date.setNull(); time.setNull(); }

    /** returns day of the week. Values are 1-7
    */  
    int dayOfWeek() const { return date.dayOfWeek(); }

   /** returns day of the week.
    * values are "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Satur
day".
    */
    const char *dayOfWeekName() const { return date.dayOfWeekName(); }

    /** returns day of the week abbreviation
    * values are "Sun",    "Mon",    "Tue",     "Wed",       "Thu",      "Fri",    "Sat"
    */
    const char *dayOfWeekAbbr() const { return date.dayOfWeekAbbr(); }

    /** returns the day of the month. Values are 1 to 31
    */
    int dayOfMonth() const { return date.dayOfMonth(); }
    int dayOfYear() const { return date.dayOfYear(); }

    /** returns the month. Values are 1 to 12.
    */

    int month() const { return date.month(); }

    /** returns the month name
    *   values are "January", "February", "March",     "April",   "May",      "June",
    *   "July",    "August",   "September", "October", "November", "December"
    */
    const char *monthName() const { return date.monthName(); }

    /** returns the month name abbreviation
    * Values are "Jan",     "Feb",      "Mar",      "Apr",     "May",      "Jun",
    * "Jul",     "Aug",      "Sep",      "Oct",     "Nov",      "Dec"
    */
    const char *monthAbbr() const { return date.monthAbbr(); }

    /** returns the year
    */
    int year() const { return date.year(); }

    int secondsSinceMidnight() const { return time.secondsSinceMidnight(); }
    /** returns the seconds */
    int seconds() const { return time.seconds(); }
    /** returns the minutes */
    int minutes() const { return time.minutes(); }
    /** returns the hours */
    int hours() const { return time.hours(); }
    /** returns the millisecs */
    int msec() const { return time.msec(); }
    /** returns the microsecs */
    int usec() const { return time.usec(); }

    /** sets the millisecs */
    int setMsec(int ms) { return time.setMsec(ms) ; }
    /** sets the microsecs */
    int setUsec(int us) { return time.setUsec(us) ; }

    /** parses the date string passed and stores it
    *It should of the format "mm/dd/yyyy"
    */
    int parseDateFrom(const char *s) { return date.parseFrom(s); }

    /** parses the time string passed and stores it
    *It should of the format "hh:mm::ss"
    */

    int parseTimeFrom(const char *s) { return time.parseFrom(s); }
    
    static void changeToCsqlFormat(char *src);

    int parseFrom(const char *s);
    friend int  operator<(const TimeStamp &d1, const TimeStamp &d2);
    friend int  operator>(const TimeStamp &d1, const TimeStamp &d2);
    friend int  operator<=(const TimeStamp &d1, const TimeStamp &d2);
    friend int  operator>=(const TimeStamp &d1, const TimeStamp &d2);
    friend int  operator==(const TimeStamp &d1, const TimeStamp &d2);
    friend int  operator!=(const TimeStamp &d1, const TimeStamp &d2);
    void addYear(int noOfYrs ){ date.addYear(noOfYrs);}

    void subYear(int noOfYrs ) {   date.subYear(noOfYrs); }

    void addMonth(int noOfMons ) { date.addMonth(noOfMons);}   

    void subMonth(int noOfMons) { date.subMonth(noOfMons);}

    void addDay(int noOfDays) { date.addDay(noOfDays);}

    void subDay(int noOfDays) { date.subDay(noOfDays); }

    void addHour(int hours);

    void subHour(int hours);

    void addMin(int noOfMins);

    void subMin(int noOfMins);

    void addSec(int noOfSecs);

    void subSec(int noOfSecs);
    
    int secDiff(TimeStamp &ts);
    int minDiff(TimeStamp &ts);
    int hourDiff(TimeStamp &ts);
    int dayDiff(TimeStamp &ts);
    int monthDiff(TimeStamp &ts);
    int yearDiff(TimeStamp &ts); 

    private:
    Date date;
    Time time;
};

#include<DataTypeInline.h>
#endif


