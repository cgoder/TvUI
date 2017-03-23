#ifndef __CTIME_H__
#define __CTIME_H__

#include <string>

typedef struct SkyTvTime
{
    unsigned short u16Year;// year
    unsigned char  u8Month;// month
    unsigned char  u8Day;// day
    unsigned char  u8Hour;// hour
    unsigned char  u8Minute;// minute
    unsigned char  u8Second;// second
    unsigned char  u8Week;//week
} SkyTvTimeStruct;

typedef struct SkyTvTimeString
{
    std::string strYear;// year
    std::string  strMonth;// month
    std::string  strDay;// day
    std::string  strHour;// hour
    std::string  strMinute;// minute
    std::string  strSecond;// second
    std::string  strWeek;// week
} SkyTvTimeStringStruct;

class CTime
{
public:
    static unsigned char getLeap(unsigned short u16year);
    static unsigned short getDaysOfYear(unsigned short u16year);
    static unsigned char getDaysOfMonth(unsigned short u16Year, unsigned char u8Month);
    static unsigned char getDayOfWeek(unsigned short u16Year, unsigned char u8Month, unsigned char u8Day);
    static bool seconds2Time(unsigned int u32Seconds, SkyTvTime& time);
    static bool seconds2TimeString(unsigned int u32Seconds, SkyTvTimeString& timeString);
    static bool seconds2TimeString(unsigned int u32Seconds, std::string& timeString);
    static bool getLocalTime(SkyTvTime& time);
    static bool getLocalTime(SkyTvTimeString& timeString);
    static unsigned long getClock(void);
};

#endif //__CTIME_H__
