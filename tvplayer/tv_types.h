#ifndef __SKYTV_TYPES_H__
#define __SKYTV_TYPES_H__

#ifdef _WIN32
#define FUNC_ENTRY() {}//printf("\n######## [%s]%d enter! #######\n", __FUNCTION__,__LINE__)
#define FUNC_EXIT() {}//printf("\n######## [%s]%d exit! #######\n", __FUNCTION__,__LINE__)
#else
#define FUNC_ENTRY() printf("\n######## [%s]%d enter! #######\n", __PRETTY_FUNCTION__,__LINE__)
#define FUNC_EXIT() printf("\n######## [%s]%d exit! #######\n", __PRETTY_FUNCTION__,__LINE__)
#endif

typedef enum
{
    SKYTV_INPUT_SOURCE_UNKNOWN = 0, //0

    SKYTV_INPUT_SOURCE_ATV, //1

    SKYTV_INPUT_SOURCE_DTV, //DTV 2
    SKYTV_INPUT_SOURCE_DVBC,    //DVBC  3
    SKYTV_INPUT_SOURCE_DVBC2,   //DVBC2 4
    SKYTV_INPUT_SOURCE_DVBS,    //DVBS  5
    SKYTV_INPUT_SOURCE_DVBS2,   //DVBS2 6
    SKYTV_INPUT_SOURCE_DVBT,    //DVBT  7
    SKYTV_INPUT_SOURCE_DVBT2,         //DVBT2          8
    SKYTV_INPUT_SOURCE_DTMB,        //DTMB          9
    SKYTV_INPUT_SOURCE_ATSC,        //ATSC         10
    SKYTV_INPUT_SOURCE_ISDB,        //ISDB         11
    SKYTV_INPUT_SOURCE_DTV_MAX,     ///<HDMI max         12

    SKYTV_INPUT_SOURCE_HDMI1,       ///<HDMI 1      13
    SKYTV_INPUT_SOURCE_HDMI2,      ///<HDMI 2      14
    SKYTV_INPUT_SOURCE_HDMI3,      ///<HDMI 3      15
    SKYTV_INPUT_SOURCE_HDMI4,      ///<HDMI 4      16
    SKYTV_INPUT_SOURCE_HDMI_MAX,   ///<HDMI max    17

    SKYTV_INPUT_SOURCE_YPBPR,        ///<Component 1    18
    SKYTV_INPUT_SOURCE_YPBPR2,       ///<Component 2    19
    SKYTV_INPUT_SOURCE_YPBPR3,       ///<Component 3    20
    SKYTV_INPUT_SOURCE_YPBPR4,       ///<Component 3    21
    SKYTV_INPUT_SOURCE_YPBPR_MAX,    ///<Component max   22

    SKYTV_INPUT_SOURCE_DVI,          ///<DVI 1            23
    SKYTV_INPUT_SOURCE_DVI2,         ///<DVI 2            24
    SKYTV_INPUT_SOURCE_DVI3,         ///<DVI 2            25
    SKYTV_INPUT_SOURCE_DVI4,         ///<DVI 4            26
    SKYTV_INPUT_SOURCE_DVI_MAX,      ///<DVI max          27

    SKYTV_INPUT_SOURCE_CVBS,         ///<AV 1           29
    SKYTV_INPUT_SOURCE_CVBS2,        ///<AV 2           30
    SKYTV_INPUT_SOURCE_CVBS3,        ///<AV 3           31
    SKYTV_INPUT_SOURCE_CVBS4,        ///<AV 4           32
    SKYTV_INPUT_SOURCE_CVBS_MAX,        ///<AV max           33

    SKYTV_INPUT_SOURCE_SVIDEO,       ///<S-video 1      34
    SKYTV_INPUT_SOURCE_SVIDEO2,      ///<S-video 2      35
    SKYTV_INPUT_SOURCE_SVIDEO3,      ///<S-video 3      36
    SKYTV_INPUT_SOURCE_SVIDEO4,      ///<S-video 4      37
    SKYTV_INPUT_SOURCE_SVIDEO_MAX,   ///<S-video max    38

    SKYTV_INPUT_SOURCE_STORAGE,  ///<Storage1            39
    SKYTV_INPUT_SOURCE_STORAGE2,  ///<Storage2            40
    SKYTV_INPUT_SOURCE_STORAGE3,  ///<Storage3            41
    SKYTV_INPUT_SOURCE_STORAGE4,  ///<Storage4            42
    SKYTV_INPUT_SOURCE_STORAGE_MAX,  ///<Storage max            43

    SKYTV_INPUT_SOURCE_VGA,  ///<VGA      44

    SKYTV_INPUT_SOURCE_GOOGLE_CAST,  ///<Google Cast      45

} SKYTV_INPUT_SOURCE_TYPE;

typedef enum
{
    SKYTV_CHANNEL_OPT_FAV = 0,
    SKYTV_CHANNEL_OPT_LOCK,
    SKYTV_CHANNEL_OPT_HIDE,
    SKYTV_CHANNEL_OPT_DEL
} SKYTV_CHANNEL_OPT_TYPE;

typedef enum {
    SKYTV_TIMEZONE_UTC = 0,
    SKYTV_TIMEZONE_UTC_P1,
    SKYTV_TIMEZONE_UTC_P2,
    SKYTV_TIMEZONE_UTC_P3,
    SKYTV_TIMEZONE_UTC_P4,
    SKYTV_TIMEZONE_UTC_P5,
    SKYTV_TIMEZONE_UTC_P6,
    SKYTV_TIMEZONE_UTC_P7,
    SKYTV_TIMEZONE_UTC_P8,
    SKYTV_TIMEZONE_UTC_P9,
    SKYTV_TIMEZONE_UTC_P10,
    SKYTV_TIMEZONE_UTC_P11,
    SKYTV_TIMEZONE_UTC_P12,
    SKYTV_TIMEZONE_UTC_N11,
    SKYTV_TIMEZONE_UTC_N10,
    SKYTV_TIMEZONE_UTC_N9,
    SKYTV_TIMEZONE_UTC_N8,
    SKYTV_TIMEZONE_UTC_N7,
    SKYTV_TIMEZONE_UTC_N6,
    SKYTV_TIMEZONE_UTC_N5,
    SKYTV_TIMEZONE_UTC_N4,
    SKYTV_TIMEZONE_UTC_N3,
    SKYTV_TIMEZONE_UTC_N2,
    SKYTV_TIMEZONE_UTC_N1
} SKYTV_TIMEZONE_E;

typedef enum {
    SKYTV_COUNTRY_UNKNOWN = 0,
    SKYTV_COUNTRY_CHINA,
    SKYTV_COUNTRY_UK
} SKYTV_COUNTRY_E;

typedef enum {
    SKYTV_LANGUAGE_UNKNOWN = 0,
    SKYTV_LANGUAGE_ENGLISH,
    SKYTV_LANGUAGE_CHINESE_S,
    SKYTV_LANGUAGE_CHINESE_T,
    SKYTV_LANGUAGE_JAPANESE

} SKYTV_LANGUAGE_E;

#endif //__SKYTV_TYPES_H__
