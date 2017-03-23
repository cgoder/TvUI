//<MStar Software>
//******************************************************************************
//
//******************************************************************************
//<MStar Software>
#ifndef __DATABASEMANAGER_TYPEDEFINE_H__
#define __DATABASEMANAGER_TYPEDEFINE_H__
#include "mapi_types.h"
#define MAX_FAVLIST_NUM 8
typedef enum
{
    E_INPUT_SOURCE_TYPE_VGA,          ///<VGA input
    E_INPUT_SOURCE_TYPE_ATV,          ///<ATV input
    E_INPUT_SOURCE_TYPE_CVBS,         ///<AV
    E_INPUT_SOURCE_TYPE_SVIDEO,       ///<S-video
    E_INPUT_SOURCE_TYPE_YPBPR,        ///<Component 1
    E_INPUT_SOURCE_TYPE_SCART,        ///<Scart
    E_INPUT_SOURCE_TYPE_HDMI,         ///<HDMI
    E_INPUT_SOURCE_TYPE_DTV,          ///<DTV  <DTV2
    E_INPUT_SOURCE_TYPE_OTHERS,		  ///<DVI    <Storage    <KTV     <Storage2
    E_INPUT_SOURCE_TYPE_NUM,      	///<number of the source
    //E_INPUT_SOURCE_TYPE_NONE = MS_INPUT_SOURCE_TYPE_NUM,    ///<NULL input
} EN_INPUT_SOURCE_TYPE;

typedef enum
{
    /// picture mode min
    E_PICTURE_MIN,
    /// picture mode dynamic
    E_PICTURE_DYNAMIC = E_PICTURE_MIN,
    /// picture mode normal
    E_PICTURE_NORMAL,
    /// picture mode mild
    E_PICTURE_MOVIE,
    /// picture mode user
    E_PICTURE_USER,

#if 0   //consistent to PICTURE_MODE_COUNT in MainMenuFrame
    E_PICTURE_VIVID,
    E_PICTURE_NATURAL,
    E_PICTURE_SPORTS,
#endif
    /// picture mode number
    E_PICTURE_NUMS,
} EN_PICTURE;

typedef enum
{
    ///color temperature min
    E_COLOR_TEMP_MIN = 0,
    ///color temperature cool
    E_COLOR_TEMP_COOL = E_COLOR_TEMP_MIN,
    ///color temperature medium
    E_COLOR_TEMP_NATURE,
    ///color temperature warm
    E_COLOR_TEMP_WARM,
    ///color temperature user
    E_COLOR_TEMP_USER,
#if (MSTAR_TVOS == 1)
    ///color temperature user
    E_COLOR_TEMP_USER2,
    //MS_COLOR_TEMP_NATURE,
    E_COLOR_TEMP_MAX = E_COLOR_TEMP_USER2,
#else
    //MS_COLOR_TEMP_NATURE,
    E_COLOR_TEMP_MAX = E_COLOR_TEMP_USER,
#endif
    E_COLOR_TEMP_NUM,
} EN_COLOR_TEMP;

typedef enum
{
    /// sound mode is standard
    E_TVOS_SOUND_MODE_STANDARD,
    /// sound mode is music
    E_TVOS_SOUND_MODE_MUSIC,
    /// sound mode is movie
    E_TVOS_SOUND_MODE_MOVIE,
    /// sound mode is sport
    E_TVOS_SOUND_MODE_SPORTS,
    /// sound mode is user
    E_TVOS_SOUND_MODE_USER,
    E_TVOS_SOUND_MODE_NUM
} EN_TVOS_SOUND_MODE;

//typedef struct
//{
//
//} ST_USER_SOUND_SETTING;

typedef struct
{
    int16_t n16BlueGain;
    int16_t n16BlueOffset;
    int16_t n16GreenGain;
    int16_t n16GreenOffset;
    int16_t n16RedGain;
    int16_t n16RedOffset;
} ST_COLOR_TEMPERATURE_DATA;

typedef struct
{
    int32_t n32BlueGain;
    int32_t n32BlueOffset;
    int32_t n32GreenGain;
    int32_t n32GreenOffset;
    int32_t n32RedGain;
    int32_t n32RedOffset;
} ST_COLOR_TEMPERATURE_EX_DATA;

typedef struct
{
    int32_t n32LocationNo;
    int16_t n16ManualLatitude;
    int16_t n16ManualLongitude;
} ST_USER_LOCATION_SETTING;

typedef struct
{
    uint16_t u16HwModel;
    uint16_t u16HwVersion;
    uint16_t u16SwapModel;
    uint16_t u16SwapVersion;
    uint32_t u32Oui;
} ST_USER_CUSTOMER_OAD_INFO;

typedef struct
{
    uint16_t u16CheckSum;
    uint32_t u32WakeUpTime;
    uint8_t u8ScheduleOn;
} ST_OAD_WAKEUP_INFO;

typedef struct
{
    int32_t n32HCapStart;
    int32_t n32HCropLeft;
    int32_t n32HCropRight;
    int32_t n32VCapStart;
    int32_t n32VCropDown;
    int32_t n32VCropUp;
} ST_VIDEO_WINDOW_INFO;

typedef struct
{
    int16_t n16Band;
    int16_t n16Foh;
    int16_t n16Fol;
    int16_t n16Gain;
    int16_t n16QValue;
} ST_AUDIO_PEQ_PARAM;

typedef struct
{
    int16_t n16OverScanHPos;
    int16_t n16OverScanHRatio;
    int16_t n16OverScanVPos;
    int16_t n16OverScanVRatio;
} ST_OVER_SCAN_SETTING_USER;

typedef struct
{
    int32_t n32AntennaType;
    int32_t n32CableSystem;
    int32_t n32CheckSum;
    char cAntennaPower;
} ST_TV_MEDIUM_SETTING;

typedef struct
{
    uint8_t u8Osd_V0;
    uint8_t u8Osd_V100;
    uint8_t u8Osd_V25;
    uint8_t u8Osd_V50;
    uint8_t u8Osd_V75;
} ST_NLA_POINT;

typedef struct
{
    bool bAutoSleepFlag;
    bool bClockMode;
    int16_t enOffTimeState;
    int16_t enOnTimeState;
    int16_t eTimeZoneInfo;
    bool bIs12Hour;
    bool bIsAutoSync;
    bool bIsDaylightSaving;
    int32_t n32offsetTime;
    int32_t n32OffTimeFlag;
    int16_t n16OffTimerInfoHour;
    int16_t n16OffTimerInfoMin;
    int16_t n16OnTimeFlag;
    int16_t n16OnTimerInfoHour;
    int16_t n16OnTimerInfoMin;
    int32_t n32OnTimerChannel;
    int16_t n16OnTimerVolume;
    int16_t n16OnTimeTvSrc;
    int32_t n32TimeDataCs;
    int32_t n32TimerBootMode;
} ST_COMMON_VO_TIME;

typedef struct
{
    int16_t balance;
    int16_t bass;
    int32_t enSoundAudioChannel;
    int16_t eqBand1;
    int16_t eqBand2;
    int16_t eqBand3;
    int16_t eqBand4;
    int16_t eqBand5;
    int16_t eqBand6;    //unused
    int16_t eqBand7;    //unused
    int16_t treble;
    bool userMode; //Equalizer Mode
} SoundModeSetting;

typedef struct
{
    int32_t adOutput;
    int16_t adVolume;
    SoundModeSetting astSoundModeSetting[E_TVOS_SOUND_MODE_NUM];
    int32_t audysseyDynamicVolume;
    int32_t audysseyEq;
    int16_t balance;
    int32_t checkSum;
    bool enableAd;
    bool enableAVC;
    int16_t headPhonePreScale;
    int16_t headphoneVolume;
    int16_t lineOutPreScale;
    int16_t muteFlag;
    int16_t primaryFlag;
    int16_t scart1PreScale;
    int16_t scart2PreScale;
    int32_t soundAudioChannel;
    int32_t soundAudioLanguage1;
    int32_t soundAudioLanguage2;
    int32_t soundMode;
    int16_t spdifDelay;
    int16_t speakerdelay;
    int16_t speakerPreScale;
    int32_t surround;
    int32_t surroundSoundMode;
    int16_t volume;
} UserSoundSetting;

typedef struct
{
    /// user subtitle language 1
    uint32_t  SubtitleDefaultLanguage;
    /// user subtitle language 2
    uint32_t  SubtitleDefaultLanguage_2;
    /// HardOfHearing setting, 0=Off, 1= On
    uint8_t fHardOfHearing; //: 1;
    /// subtitle enable or not, 0=Off, 1= On
    uint8_t fEnableSubTitle; //: 1;
    /// reserve for future use
    uint8_t Reserved; // : 6;
} UserSubtitleSetting;

typedef struct
{
    uint8_t u8RedGain;
    uint8_t u8GreenGain;
    uint8_t u8BlueGain;
    uint8_t u8RedOffset;
    uint8_t u8GreenOffset;
    uint8_t u8BlueOffset;
} PqlColorTempData;

typedef struct
{
    uint16_t u16RedGain;
    uint16_t u16GreenGain;
    uint16_t u16BlueGain;
    uint16_t u16RedOffset;
    uint16_t u16GreenOffset;
    uint16_t u16BlueOffset;
} PqlColorTempexData;

typedef struct
{
    /// Enable / Disable 3D feature
    bool         bEnable3D;
    /// 3D input type
    uint32_t    enInput3DMode;
    /// 3D output type
    uint32_t   enOutput3DMode;
} st3dInfo;

typedef struct
{
    /// MM text subtitle font size
    uint8_t u8SubtitleSpecific;
    /// Text subtitle background color
    uint8_t u8SubtitleBGColor;
    /// Text subtitle font color
    uint8_t u8SubtitleFontColor;
    /// Photo slide show time
    uint8_t u8SlideShowTime;
    /// Photo slide show mode
    uint8_t u8SlideShowMode;
    /// Movie/Photo Preview On or off
    uint8_t fPreviewOn; //      : 1;
    /// Movie Resume on or off
    uint8_t fResumePlay; //      : 1;
    /// Reserved
    uint8_t Reserved; //         : 6;
} UserMmSetting;
typedef struct
{
    /// the ID of Location.
    uint16_t u16LocationNo;
    /// the Longitude value
    int16_t s16ManualLongitude;
    /// the Latitude value
    int16_t s16ManualLatitude;
} UserLocationSetting;
typedef struct
{
    /// display mode
    uint32_t enDisplayMode;
    /// 3d format
    uint32_t en3DFormat;
    /// 2d format
    uint32_t en2DFormat;
    /// auto start setting
    uint32_t enAutoStart;
    /// the period of watching 3D, time's unit is ms
    uint32_t en3DTimerPeriod;
} st3dSetting;
typedef struct
{
    int16_t backlight;
    int16_t brightness;
    int32_t colorTemp;
    int16_t contrast;
    int32_t dynamicBacklight;
    int32_t dynamicContrast;
    int16_t hue;
    int32_t perfectClear;
    int16_t saturation;
    int16_t sharpness;
    int32_t vibrantColour;
} ST_PICTURE;

typedef struct
{
    /// noise reduction setting
    uint32_t eNR;
    /// MPEG noise reduction setting
    uint32_t eMPEG_NR;
} ST_NOISE_REDUCE_MODE;

typedef struct
{
    /// check sum <<checksum should be put at top of the struct, do not move it to other place>>
    uint16_t u16CheckSum;
    /// brightness
    uint8_t u8SubBrightness;
    /// contrast
    uint8_t u8SubContrast;
} ST_SUB_COLOR;

typedef struct
{
    /// 3D Video Setting
    uint32_t eThreeDVideo;
    /// 3D Video Display Mode
    uint32_t eThreeDVideoDisplayMode;
    /// 3D Video Display Formmat
    uint32_t eThreeDVideoDisplayFormat;
    /// 3D Video 3D Depth
    uint32_t eThreeDVideo3DDepth;
    /// 3D Video Auto Start
    uint32_t eThreeDVideoAutoStart;
    /// 3D Video 3D Output Aspect
    uint32_t eThreeDVideo3DOutputAspect;
    /// 3D Video 3D Left Rigth View Switch
    uint32_t eThreeDVideoLRViewSwitch;
} ST_3D_VIDEO_MODE;

typedef struct
{
   ///overscanHposition
    uint8_t   OverScanHposition;
   ///overscanVposition
    uint8_t   OverScanVposition;
   ///OverScanHRatio
    uint8_t   OverScanHRatio;
   ///OverScanVRatio
    uint8_t   OverScanVRatio;
} ST_OVERSCAN_SETTING_USER;
#endif //__DATABASEMANAGER_TYPEDEFINE_H__
