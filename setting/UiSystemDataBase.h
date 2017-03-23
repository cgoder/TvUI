/****************************************************************************
 * Notice:      Copyright (c) Skyworth.
 *              All rights reserved.
 * Owner:      miaolibin@skyworth.com
 ****************************************************************************/
#ifndef __UISYSTEMDATABASE_H__
#define __UISYSTEMDATABASE_H__
#include "UiSystemDataType.h"
#include "CDatabaseService.h"
#include "PictureManagerTypeDefine.h"
#include "DatabaseManagerType.h"
#include "mapi_audio_datatype.h"
#ifdef WIN32
#include "../sqlite3/sqlite3.h"
#else
#include "sqlite3.h"
#endif

/** 3D Video display mode */
typedef enum
{
    /// 2D mode
    DB_ThreeD_Video_DISPLAYMODE_2D = 0,
    /// 3D mode
    DB_ThreeD_Video_DISPLAYMODE_3D,
    /// 2D to 3D mode
    DB_ThreeD_Video_DISPLAYMODE_2D_TO_3D,
    /// 3D to 2D mode
    DB_ThreeD_Video_DISPLAYMODE_3D_TO_2D,
    /// total mode number
    DB_ThreeD_Video_DISPLAYMODE_COUNT
}EN_ThreeD_Video_DISPLAYMODE;
/** 3D Video LR View Switch */
typedef enum
{
    /// 3D Left Right exchanging/HotkeyControlFrame.cpp
    DB_ThreeD_Video_LRVIEWSWITCH_EXCHANGE = 0,
    /// 3D Left Right not exchanging
    DB_ThreeD_Video_LRVIEWSWITCH_NOTEXCHANGE,
    /// 3D Left Right exchanging total number
    DB_ThreeD_Video_LRVIEWSWITCH_COUNT
}EN_ThreeD_Video_LRVIEWSWITCH;

/** Audio type */
typedef enum
{
    /// Audio Type: normal
    E_AUDIO_NORMAL_MODE,
    /// Audio Type: hearing impaired
    E_AUDIO_HEARING_IMPAIRED,
    /// Audio Type: visual impaired
    E_AUDIO_VISUAL_IMPAIRED,
}EN_AUDIO_TRACK_TYPE;
/// the boot up type
typedef enum
{
    /// on timer boot up
    EN_TIMER_BOOT_ON_TIMER,
    /// boot up because of reminder
    EN_TIMER_BOOT_REMINDER,
    /// boot up because of recorder
    EN_TIMER_BOOT_RECORDER,
    /// boot up because of ci op refresh
    EN_TIMER_BOOT_CI_OP_REFRESH,
    /// normal boot up
    EN_TIMER_BOOT_NONE,
} EN_TIMER_BOOT_TYPE;


/** 3D Video display format */
typedef enum
{
    /// 3D Side by side mode
    DB_ThreeD_Video_DISPLAYFORMAT_SIDE_BY_SIDE = 0,
    /// 3D Top Bottom mode
    DB_ThreeD_Video_DISPLAYFORMAT_TOP_BOTTOM,
    /// 3D Frame Packing mode
    DB_ThreeD_Video_DISPLAYFORMAT_FRAME_PACKING,
    /// 3D Line alternative mode
    DB_ThreeD_Video_DISPLAYFORMAT_LINE_ALTERNATIVE,
    /// 3D Frame alternative mode
    DB_ThreeD_Video_DISPLAYFORMAT_FRAME_ALTERNATIVE,
    /// 3D off mode
    DB_ThreeD_Video_DISPLAYFORMAT_NATIVE,
    /// total format number
    DB_ThreeD_Video_DISPLAYFORMAT_COUNT
}EN_ThreeD_Video_DISPLAYFORMAT;
/** 3D Video 3D Depth */
typedef enum
{
    /// 3D Depth weak
    DB_ThreeD_Video_3DDEPTH_WEAK = 0,
    /// 3D Depth middle
    DB_ThreeD_Video_3DDEPTH_MIDDLE,
    /// 3D Depth strong
    DB_ThreeD_Video_3DDEPTH_STRONG,
    /// 3D Depth total number
    DB_ThreeD_Video_3DDEPTH_COUNT
}EN_ThreeD_Video_3DDEPTH;
/** 3D Video 3D Output Aspect */
typedef enum
{
    /// 3D output aspect in fullscreen
    DB_ThreeD_Video_3DOUTPUTASPECT_FULLSCREEN = 0,
    /// 3D output aspect in center
    DB_ThreeD_Video_3DOUTPUTASPECT_CENTER,
    /// 3D output aspect in auto adapted
    DB_ThreeD_Video_3DOUTPUTASPECT_AUTOADAPTED,
    /// 3D output aspect total number
    DB_ThreeD_Video_3DOUTPUTASPECT_COUNT
}EN_ThreeD_Video_3DOUTPUTASPECT;

/** ISDB Air channel type (DTV or ATV) */
typedef enum
{
    /// DTV
    MS_ISDB_AIR_CHANNEL_DTV = 0,
    /// ATV
    MS_ISDB_AIR_CHANNEL_ATV,
}MS_ISDB_AIR_CHANNEL;
/** PIP mode setting */
typedef enum
{
    /// pip mode on
    EN_PIP_MODE_PIP,
    /// pip mode pop and full
    EN_PIP_MODE_POP_FULL,
    /// pip mode pop
    EN_PIP_MODE_POP,
    /// PIP mode off
    EN_PIP_MODE_OFF,
    /// PIP mode invalid
    EN_PIP_MODE_INVALID,
} EN_PIP_MODE;

/** PIP size setting */
typedef enum
{
    /// PIP size small
    EN_PIP_SIZE_SMALL,
    /// PIP size small
    EN_PIP_SIZE_MEDIUM,
    /// PIP size large
    EN_PIP_SIZE_LARGE,
    /// PIP size invalid
    EN_PIP_SIZE_INVALID,
} EN_PIP_SIZE;

/** PIP position setting */
typedef enum
{
    /// PIP position is letf and top
    EN_PIP_POSITION_LEFT_TOP,
    /// PIP position is right and top
    EN_PIP_POSITION_RIGHT_TOP,
    /// PIP position is letf and buttom
    EN_PIP_POSITION_LEFT_BOTTOM,
    /// PIP position is right and buttom
    EN_PIP_POSITION_RIGHT_BOTTOM,
    //EN_PIP_POSITION_USER,             /* We do not support user-defined position */
    /// PIP position invalid
    EN_PIP_POSITION_INVALID,
} EN_PIP_POSITION;

/** PIP sound SRC setting */
typedef enum
{
    /// PIP sound SRC main
    EN_PIP_SOUND_SRC_MAIN,
    /// PIP sound SRC sub
    EN_PIP_SOUND_SRC_SUB,
    /// PIP sound SRC invalid
    EN_PIP_SOUND_SRC_INVALID,
} EN_PIP_SOUND_SRC;
/** Factory Power-On Mode */
typedef enum
{
    EN_POWER_MODE_SECONDARY,
    EN_POWER_MODE_MEMORY,
    EN_POWER_MODE_DIRECT,
    EN_POWER_MODE_MAX
}MS_UI_FACTORY_POWER_MODE;

/// AVD PLL TRACK SPEED type
typedef enum
{
    /// OFF, K1=0x10 K2=0x20
    AVD_PLL_TRACK_OFF = 0,
    /// SPECIAL FORCE, K1=0x2E K2=0x6A
    AVD_PLL_TRACK_SPECIAL,
    /// FORCE LOW, K1=0x82 K2=0x4
    AVD_PLL_TRACK_LO,
    /// FORCE MIDDLE LOW, K1=0x90 K2=0x20
    AVD_PLL_TRACK_MID_LO,
    /// FORCE MIDDLE HIGH, K1=0x9A K2=0x35
    AVD_PLL_TRACK_MID_HI,
    /// FORCE HI, K1=0xBC K2=0x6A
    AVD_PLL_TRACK_HI,
    /// UNDEFINE
    AVD_PLL_TRACK_UNDEFINE,
} EN_AVD_PLL_TRACK_TYPE;
/// AVD FORCE SLICE type
typedef enum
{
    /// OFF
    AVD_FORCE_SLICE_OFF = 0,
    /// FORCE SLICE H
    AVD_FORCE_SLICE_H,
    /// FORCE SLICE V
    AVD_FORCE_SLICE_V,
    /// FORCE SLICE H+V
    AVD_FORCE_SLICE_HV,
    /// UNDEFINE
    AVD_FORCE_SLICE_UNDEFINE,
} EN_AVD_FORCE_SLICE_TYPE;
/** define items which use no-linear adjust */
typedef enum
{
    /// volume
    EN_NLA_VOLUME,
    /// picture brightness
    EN_NLA_BRIGHTNESS,
    /// picture contrast
    EN_NLA_CONTRAST,
    /// picture saturation
    EN_NLA_SATURATION,
    /// picture sharpness
    EN_NLA_SHARPNESS,
    /// picture hue
    EN_NLA_HUE,
    /// picture back light
    EN_NLA_BACKLIGHT,
    /// the number of the index
    EN_NLA_NUMS
}MS_NLA_SET_INDEX;

/** VD setting */
typedef struct
{
    /// AFEC D4
    unsigned char u8AFEC_D4;
    /// AFEC D8 bit 0~3
    unsigned char u8AFEC_D8_Bit3210;
    /// AFEC D5 bit2
    unsigned char u8AFEC_D5_Bit2;//[2]When CF[2]=1, K1/K2 Default Value, K1=2E,K2=6A
    /// AFEC D7 lower bound
    unsigned char u8AFEC_D7_LOW_BOUND;//Color kill
    /// AFEC D7 higher bound
    unsigned char u8AFEC_D7_HIGH_BOUND;//Color kill
    /// AFEC D9 bit 0
    unsigned char u8AFEC_D9_Bit0;
    /// AFEC A0
    unsigned char u8AFEC_A0; //only debug
    /// AFEC  A1
    unsigned char u8AFEC_A1; //only debug
    /// AFEC 66 bit 6~7
    unsigned char u8AFEC_66_Bit76;//only debug
    /// AFEC 6E bit 4~7
    unsigned char u8AFEC_6E_Bit7654;//only debug
    /// AFEC 6E bit 0~3
     unsigned char u8AFEC_6E_Bit3210;//only debug
    /// AFEC 43
    unsigned char u8AFEC_43;//auto or Fixed AGC
    /// AFEC 44
    unsigned char u8AFEC_44;//AGC gain
    /// AFEC CB
    unsigned char u8AFEC_CB;
    /// AFEC CF bit2 ATV
    unsigned char u8AFEC_CF_Bit2_ATV;
    /// AFEC CF bit2 AV
    unsigned char u8AFEC_CF_Bit2_AV;
    /// AFEC PLL Track Type
    EN_AVD_PLL_TRACK_TYPE enPllTrackType;
    /// AFEC Force Slice Type
    EN_AVD_FORCE_SLICE_TYPE enForceSliceType;
    /// AFEC_Gain_AutoTune_OPTION
    bool bEnableAutoTune;
}MS_UI_Factory_NS_VD_SET;

/** Usr-NLA setting */
typedef struct
{
    /// check sum <<checksum should be put at top of the struct, do not move it to other place>>
    unsigned char u16CheckSum;
    /// Point 0,25,50,75,100
    ST_NLA_POINT stNLASetting[EN_NLA_NUMS];
} MS_UI_NLA_SETTING;


#if(ISDB_SYSTEM_ENABLE == 1)
/** ISDB SCAN OPTION  Mode (Primary or All) */
typedef enum
{
    /// Primary
    ISDB_SCAN_OPT_PRIMARY = 0,
    /// All
    ISDB_SCAN_OPT_ALL,
}EN_UI_ISDB_SCAN_OPT;

/** ISDB user settings */
typedef struct
{
    /// checksum
    unsigned int u16CheckSum;
    /// ginge mode
    bool bGingaMode;
    /// ATV CC mode
    unsigned char u8ATVCCMode;
    /// DTV CC mode
    unsigned char u8DTVCCMode;
    /// SCAN OPTION mode
    EN_UI_ISDB_SCAN_OPT enScanOpt;
} MS_UI_USER_ISDB_SETTING;

#endif
#define SQL_UI_AFRESHCNT   30 //prepare database more times while databse is locked
#define SQL_UI_AFRESHSLP   10 //retry sleep ms
#define QUERY_UI_STRING_LENGTH   128
#define MAX_FAVTYPE_NAME_SIZE   32
#define INPUTSOURCE_NAME_MAX_SIZE 256
#define USB_SERIAL_NUMBER_LENGTH            32
#define MAX_SMB_BUF_LEN 128

#if (CA_ENABLE == 1)
#define CA_ZONE_ID_LEN                      (6)    /// CA zone ID length
#endif

#define STR(tbl)    #tbl
#define T_SystemSetting   STR(tbl_SystemSetting)
#define T_SoundSetting    STR(tbl_SoundSetting)
#define T_SoundSetting_IDX 0x17
#define T_FactoryExtern    STR(tbl_FactoryExtern)
#define T_VideoSetting   STR(tbl_VideoSetting)
#define T_PicMode_Setting   STR(tbl_PicMode_Setting)
#define T_UserOverScanMode   STR(tbl_UserOverScanMode)
#define T_NRMode   STR(tbl_NRMode)
#define T_SoundMode_Setting   STR(tbl_SoundModeSetting)
#define T_SubtitleSetting   STR(tbl_SubtitleSetting)
#define T_SubtitleSetting_IDX 0x18
#define T_USER_COLORTEMP   STR(tbl_UserColorTemp)
#define T_USER_COLORTEMP_EX   STR(tbl_UserColorTempEx)
#define T_3DInfo  STR(tbl_3DInfo)
#define T_UserMMSetting   STR(tbl_UserMMSetting)
#define T_UserLocationSetting   STR(tbl_UserLocationSetting)
#define T_MfcMode   STR(tbl_MfcMode)
#define T_FavTypeName   STR(tbl_FavTypeName)
#define T_3DSetting  STR(tbl_3DSetting)
#define T_InputSource_Type   STR(tbl_InputSource_Type)
#define T_MediumSetting   STR(tbl_MediumSetting)
#define T_CIAdjust  STR(tbl_CIAdjust)
#define T_PEQAdjust  STR(tbl_PEQAdjust)
#define T_NonStarndardAdjust  STR(tbl_NonStandardAdjust)
#define T_SSCAdjust  STR(tbl_SSCAdjust)
#define T_NonLinearAdjust  STR(tbl_NonLinearAdjust)
#if (ISDB_SYSTEM_ENABLE == 1)
#define T_IsdbUserSetting   STR(tbl_IsdbUserSetting)
#endif
#ifdef WIN32
#define SQL_UI_DB_PATH  "../sqlite3/user_setting.db"
#define SQL_UI_DB_FACTORY_PATH  "../sqlite3/factory.db"
#define SQL_UI_DB_BACKUP_PATH  "../sqlite3/user_setting.db"
#define SQL_UI_DB_FACTORY_BACKUP_PATH  "../sqlite3/factory.db"
#else
#define SQL_UI_DB_PATH  "/Customer/user_setting.db"
#define SQL_UI_DB_FACTORY_PATH  "/Customer/factory.db"
#define SQL_UI_DB_BACKUP_PATH  "/Customer/user_setting.db"
#define SQL_UI_DB_FACTORY_BACKUP_PATH  "/Customer/factory.db"
#endif
//------------------factory.db-----------------------------
#define T_FacrotyColorTempEx  STR(tbl_FactoryColorTempEx)

#define MSG_SQL_UI_DBG(x)     //x
#define MSG_SQL_UI_ERROR(x)     x

/// define for MIU maximum numbers
#define MIU_COUNTS_MAXIMUM 8
#define U8_UI_ARRAY_TYPE   0x01
#define U16_UI_ARRAY_TYPE   0x02
#define U32_UI_ARRAY_TYPE   0x04

/*********************Start enum***************************/
/// 3D aspect ratio type
typedef enum
{
    E_3D_AR_FULL = 0,   // full screen
    E_3D_AR_AUTO,       // auto adapt
    E_3D_AR_CENTER,     // centering
}EN_UI_VIDEO_3D_ARC_Type;

/** input source type for color temp */
typedef enum
{
    MS_INPUT_SOURCE_TYPE_VGA,          ///<VGA input
    MS_INPUT_SOURCE_TYPE_ATV,          ///<ATV input
    MS_INPUT_SOURCE_TYPE_CVBS,         ///<AV
    MS_INPUT_SOURCE_TYPE_SVIDEO,       ///<S-video
    MS_INPUT_SOURCE_TYPE_YPBPR,        ///<Component 1
    MS_INPUT_SOURCE_TYPE_SCART,        ///<Scart
    MS_INPUT_SOURCE_TYPE_HDMI,         ///<HDMI
    MS_INPUT_SOURCE_TYPE_DTV,          ///<DTV  <DTV2
    MS_INPUT_SOURCE_TYPE_OTHERS,       ///<DVI    <Storage    <KTV     <Storage2
    MS_INPUT_SOURCE_TYPE_RVU,          ///<RVU
    MS_INPUT_SOURCE_TYPE_MAX = MS_INPUT_SOURCE_TYPE_RVU,
    MS_INPUT_SOURCE_TYPE_NUM,       ///<number of the source
    MS_INPUT_SOURCE_TYPE_NONE = MS_INPUT_SOURCE_TYPE_NUM,    ///<NULL input
} EN_UI_MS_INPUT_SOURCE_TYPE;

typedef enum
{
    E_RECORD_BACKGROUND,
    E_RECORD_SUB,
    E_RECORD_SUB_BACKGROUND,
    E_RECORD_NONE,
    E_RECORD_SOURCE_MAX
}EN_PVR_RECORD_STATUS;

/** Cable system */
typedef enum
{
    /// NONE
    E_CABLE_SYSTEM_NONE,
    /// STD
    E_CABLE_SYSTEM_STD,
    /// IRC
    E_CABLE_SYSTEM_IRC,
    /// HRC
    E_CABLE_SYSTEM_HRC,
    /// AUTO
    E_CABLE_SYSTEM_AUTO,
} EN_UI_CABLE_SYSTEM;

/// the display mode
typedef enum
{
    /// 2D mode
    EN_DISP_MODE_2D,
    /// 3D mode
    EN_DISP_MODE_3D,
    /// 2D to 3D mode
    EN_DISP_MODE_2DTO3D,
    /// 3D to 2D mode
    EN_DISP_MODE_3DTO2D,
    /// total mode number
    EN_DISP_MODE_NUM
}EN_UI_DISPLAY_MODE;

/// the 3D display format
typedef enum
{
    /// side by side
    EN_3D_DISP_FORMAT_SBS,
    /// top and bottom
    EN_3D_DISP_FORMAT_TAB,
    /// frame packing
    EN_3D_DISP_FORMAT_FP,
    /// frame alternative
    EN_3D_DISP_FORMAT_FRMA,
    /// Line alernative
    EN_3D_DISP_FORMAT_LAP,
    /// Field alernative
    EN_3D_DISP_FORMAT_FIDA,
    /// Check Board
    EN_3D_DISP_FORMAT_CKB,

    /// format number
    EN_3D_DISP_FORMAT_NUM
}EN_UI_3D_DISPLAY_FORMAT;

/// the 2D display format
typedef enum
{
    /// side by side
    EN_2D_DISP_FORMAT_SBS,
    /// top and bottom
    EN_2D_DISP_FORMAT_TAB,
    /// frame packing
    EN_2D_DISP_FORMAT_FP,
    /// native
    EN_2D_DISP_FORMAT_NATIVE,
    /// frame alternative
    EN_2D_DISP_FORMAT_FRMA,
    /// Line alernative
    EN_2D_DISP_FORMAT_LAP,
    /// format number
    EN_2D_DISP_FORMAT_NUM
}EN_UI_2D_DISPLAY_FORMAT;

/// auto start setting type
typedef enum
{
    /// off
    EN_AUTO_START_OFF,
    /// auto start using 2D mode
    EN_AUTO_START_2D,
    /// auto start using 3D mode
    EN_AUTO_START_3D,
    /// type number
    EN_AUTO_START_NUM,
}EN_UI_AUTO_START;

/// the 3D timer period
typedef enum
{
    /// off
    TIMER_PERIOD_OFF = 0,
    /// 30 min
    TIMER_PERIOD_30 = 30*60000,
    /// 60 min
    TIMER_PERIOD_60 = 60*60000,
    /// 90 min
    TIMER_PERIOD_90 = 90*60000,
    /// 120 min
    TIMER_PERIOD_120 = 120*60000,
    /// timer period number
    TIMER_PERIOD_NUM
}EN_UI_3D_TIMER_PERIOD;


typedef enum
{
  ///min
  MS_MIN = 0,
  // ------------------------------------
  ///off
  MS_OFF = MS_MIN,
  ///low
  MS_LOW,
  ///middle
  MS_MIDDLE,
  ///high
  MS_HIGH,
  ///auto
  MS_AUTO,
  // ------------------------------------
  ///number
  MS_NUM = MS_AUTO,
} EN_UI_MS_PIC_ADV;

/** define noise reduction setting */
typedef enum
{
    /// noise reduction min
    MS_NR_MIN,
    /// noise reduction off
    MS_NR_OFF = MS_NR_MIN,
    /// noise reduction low
    MS_NR_LOW,
    /// noise reduction middle
    MS_NR_MIDDLE,
    /// noise reduction high
    MS_NR_HIGH,
    /// noise reduction auto
    MS_NR_AUTO,
    /// total noise reduction type number
    MS_NR_NUM,
} EN_UI_MS_NR;

/** MPEG noise reduction setting */
typedef enum
{
    /// MPEG noise reduction min
    MS_MPEG_NR_MIN,
    /// MPEG noise reduction off
    MS_MPEG_NR_OFF = MS_MPEG_NR_MIN,
    /// MPEG noise reduction low
    MS_MPEG_NR_LOW,
    /// MPEG noise reduction middle
    MS_MPEG_NR_MIDDLE,
    /// MPEG noise reduction high
    MS_MPEG_NR_HIGH,
    /// total mpeg noise reduction type number
    MS_MPEG_NR_NUM,
} EN_UI_MS_MPEG_NR;

/// Define aspect ratio type
typedef enum
{
  /// Default
  UI_AR_DEFAULT = 0,
  /// 16x9
  UI_AR_16x9,
  /// 4x3
  UI_AR_4x3,
  /// Auto
  UI_AR_AUTO,
  /// Panorama
  UI_AR_Panorama,
  /// Just Scan
  UI_AR_JustScan,
  /// Zoom 1
  UI_AR_Zoom1,
  /// Zoom 2
  UI_AR_Zoom2,
  UI_AR_14x9,
  /// point to point
  UI_AR_DotByDot,
   /// Subtitle
  UI_AR_Subtitle,
  /// movie
  UI_AR_Movie,
  /// Personal
  UI_AR_Personal,
  /// 4x3 Panorama
  UI_AR_4x3_PanScan,
  /// 4x3 Letter Box
  UI_AR_4x3_LetterBox,
  /// 16x9 PillarBox
  UI_AR_16x9_PillarBox,
  /// 16x9 PanScan
  UI_AR_16x9_PanScan,
  /// 4x3 Combind
  UI_AR_4x3_Combind,
  /// 16x9  Combind
  UI_AR_16x9_Combind,
  /// Zoom 2X
  UI_AR_Zoom_2x,
  /// Zoom 3X
  UI_AR_Zoom_3x,
  /// Zoom 4X
  UI_AR_Zoom_4x,
  /// In front of E_AR_CUS is Supernova area and the customization area at the back of E_AR_CUS.
  UI_AR_CUS =0x20,
  /// Maximum value of this enum
  UI_AR_MAX=0x40,
} EN_UI_VIDEO_AR_Type;

/// the display resolution type
typedef enum
{
   DISPLAY_RES_MIN = 0,

   DISPLAY_SEC32_LE32A_FULLHD = DISPLAY_RES_MIN,
   // For Normal LVDS panel
   DISPLAY_RES_SXGA = 1,                     ///< 1280x1024, Pnl_AU17_EN05_SXGA
   DISPLAY_RES_WXGA = 2,                     ///< 1366x768, Pnl_AU20_T200XW02_WXGA,
   DISPLAY_RES_WXGA_PLUS = 3,                ///< 1440x900, Pnl_CMO19_M190A1_WXGA, Pnl_AU19PW01_WXGA
   DISPLAY_RES_WSXGA = 4,                    ///< 1680x1050, Pnl_AU20_M201EW01_WSXGA,
   DISPLAY_RES_FULL_HD = 5,                  ///< 1920x1080, Pnl_AU37_T370HW01_HD, Pnl_CMO216H1_L01_HD.h

   DISPLAY_DACOUT_PAL_MIN = 6,
   DISPLAY_DACOUT_576I = DISPLAY_DACOUT_PAL_MIN,  //pal
   DISPLAY_DACOUT_576P,
   DISPLAY_DACOUT_720P_50,
   DISPLAY_DACOUT_1080P_24,
   DISPLAY_DACOUT_1080P_25,
   DISPLAY_DACOUT_1080I_50,
   DISPLAY_DACOUT_1080P_50,
   DISPLAY_DACOUT_PAL_MAX = DISPLAY_DACOUT_1080P_50,

   DISPLAY_DACOUT_NTSC_MIN = 13,
   DISPLAY_DACOUT_480I = DISPLAY_DACOUT_NTSC_MIN, //ntsc
   DISPLAY_DACOUT_480P,
   DISPLAY_DACOUT_720P_60,
   DISPLAY_DACOUT_1080P_30,
   DISPLAY_DACOUT_1080I_60,
   DISPLAY_DACOUT_1080P_60,
   DISPLAY_DACOUT_NTSC_MAX = DISPLAY_DACOUT_1080P_60,
   DISPLAY_DACOUT_AUTO,

   DISPLAY_CMO_CMO260J2_WUXGA,           // 1920*1200
   //For 4k2k
   DISPLAY_4K2K_30P = 0x30,
   DISPLAY_3840P_30 = DISPLAY_4K2K_30P,
   DISPLAY_4K2K_25P = 0x31,
   DISPLAY_3840P_25 = DISPLAY_4K2K_25P,
   DISPLAY_4K2K_24P = 0x32,
   DISPLAY_3840P_24 = DISPLAY_4K2K_24P,
   DISPLAY_4K2K_60P = 0x33,
   DISPLAY_3840P_60 = DISPLAY_4K2K_60P,
   DISPLAY_4K2K_50P = 0x34,
   DISPLAY_3840P_50 = DISPLAY_4K2K_50P,
   DISPLAY_4096P_24 = 0x35,
   DISPLAY_4096P_25 = 0x36,
   DISPLAY_4096P_30 = 0x37,
   DISPLAY_4096P_50 = 0x38,
   DISPLAY_4096P_60 = 0x39,
   DISPLAY_4K1K_120P = 0x3A,
   DISPLAY_4K1K_60P = 0x3B,
   DISPLAY_4K1K_30P = 0x3C,
   //For VGA OUTPUT 60HZ
   DISPLAY_VGAOUT_60_MIN = 0x40,
   DISPLAY_VGAOUT_640x480P_60 = DISPLAY_VGAOUT_60_MIN,
   DISPLAY_VGAOUT_1280x720P_60,
   DISPLAY_VGAOUT_1920x1080P_60,
   DISPLAY_VGAOUT_60_MAX = DISPLAY_VGAOUT_1920x1080P_60,
   //For VGA OUTPUT 50HZ
   //For TTL output
   DISPLAY_TTLOUT_60_MIN = 0xC0,
   DISPLAY_TTLOUT_480X272_60 = DISPLAY_TTLOUT_60_MIN,
   DISPLAY_TTLOUT_60_MAX = DISPLAY_TTLOUT_480X272_60,

   // For 3D format output
   DISPLAY_FRAMEPACKING_24P = 0xD0,
   DISPLAY_DACOUT_2205P_24 = DISPLAY_FRAMEPACKING_24P,
   DISPLAY_DACOUT_1470P_60,
   DISPLAY_RES_MAX_NUM,
} EN_UI_DISPLAY_RES_TYPE;

/// Video out VE type
typedef enum
{
    E_VIDEO_OUT_VE_NTSC,    ///< NTSC
    E_VIDEO_OUT_VE_PAL,     ///< PAL_B
    E_VIDEO_OUT_VE_PAL_N,   ///< PAL_N
    E_VIDEO_OUT_VE_PAL_M,   ///< PAL_M
    E_VIDEO_OUT_VE_PAL_NC,  ///< PAL_NC
    E_VIDEO_OUT_VE_AUTO,    ///< Auto
} EN_UI_VIDEO_OUT_VE_SYS;

/// Video standard
typedef enum
{
    /// Video standard PAL BGHI
    E_VIDEOSTANDARD_PAL_BGHI        = 0x00,
    /// Video standard NTSC M
    E_VIDEOSTANDARD_NTSC_M          = 0x01,
    /// Video standard SECAM
    E_VIDEOSTANDARD_SECAM           = 0x02,
    /// Video standard  NTSC 44
    E_VIDEOSTANDARD_NTSC_44         = 0x03,
    /// Video standard  PAL M
    E_VIDEOSTANDARD_PAL_M           = 0x04,
    /// Video standard  PAL N
    E_VIDEOSTANDARD_PAL_N           = 0x05,
    /// Video standard PAL 60
    E_VIDEOSTANDARD_PAL_60          = 0x06,
    /// NOT Video standard
    E_VIDEOSTANDARD_NOTSTANDARD     = 0x07,
    /// Video standard AUTO
    E_VIDEOSTANDARD_AUTO            = 0x08,
    /// Max Number
    E_VIDEOSTANDARD_MAX
} EN_UI_AVD_VideoStandardType;

/// Audio SIF MTS Mode Type
typedef enum
{   ///< Audio Mode Invalid
     E_UI_AUDIOMODE_INVALID_                    = 0x00,
    ///< Audio Mode MONO
     E_UI_AUDIOMODE_MONO_                       = 0x01,
    ///< Audio Mode Forced MONO
     E_UI_AUDIOMODE_FORCED_MONO_                = 0x02,
    ///< Audio Mode G Stereo
     E_UI_AUDIOMODE_G_STEREO_                   = 0x03,
    ///< Audio Mode  K Stereo
     E_UI_AUDIOMODE_K_STEREO_                   = 0x04,
    ///< Audio Mode MONO SAP
      E_UI_AUDIOMODE_MONO_SAP_                   = 0x05,
    ///< Audio Mode Stereo SAP
      E_UI_AUDIOMODE_STEREO_SAP_                 = 0x06,
    ///< Audio Mode Dual A
      E_UI_AUDIOMODE_DUAL_A_                     = 0x07,
    ///< Audio Mode Dual B
      E_UI_AUDIOMODE_DUAL_B_                     = 0x08,
    ///< Audio Mode Dual AB
      E_UI_AUDIOMODE_DUAL_AB_                    = 0x09,
    ///< Audio Mode NICAM MONO
      E_UI_AUDIOMODE_NICAM_MONO_                 = 0x0A,
    ///< Audio Mode NICAM Stereo
      E_UI_AUDIOMODE_NICAM_STEREO_               = 0x0B,
    ///< Audio Mode NICAM DUAL A
      E_UI_AUDIOMODE_NICAM_DUAL_A_               = 0x0C,
    ///< Audio Mode NICAM DUAL B
      E_UI_AUDIOMODE_NICAM_DUAL_B_               = 0x0D,
    ///< Audio Mode NICAM DUAL AB
      E_UI_AUDIOMODE_NICAM_DUAL_AB_              = 0x0E,
    ///< Audio Mode HIDEV MONO
      E_UI_AUDIOMODE_HIDEV_MONO_                 = 0x0F,
    ///< Audio Mode Left left
      E_UI_AUDIOMODE_LEFT_LEFT_                  = 0x10,
    ///< Audio Mode right right
      E_UI_AUDIOMODE_RIGHT_RIGHT_                = 0x11,
    ///< Audio Mode left right
      E_UI_AUDIOMODE_LEFT_RIGHT_                 = 0x12
} EN_UI_AUDIOMODE_TYPE_;

/** dynamic contrast settings */
typedef enum
{
    /// Dynamic Contrast min
    MS_Dynamic_Contrast_MIN,
    /// Dynamic Contrast off
    MS_Dynamic_Contrast_OFF = MS_Dynamic_Contrast_MIN,
    /// Dynamic Contrast on
    MS_Dynamic_Contrast_ON,
    /// Dynamic Contrast type number
    MS_Dynamic_Contrast_NUM,
} EN_UI_MS_Dynamic_Contrast;

/** Super mode settings */
typedef enum
{
    /// SUPER min
    MS_SUPER_MIN,
    /// SUPER off
    MS_SUPER_OFF = MS_SUPER_MIN,
    /// SUPER on
    MS_SUPER_ON,
    /// SUPER number
    MS_SUPER_NUM,
}EN_UI_MS_SUPER;

/** MFC mode */
typedef enum
{
    MS_MFC_OFF = 0,
    MS_MFC_LOW,
    MS_MFC_MIDDLE,
    MS_MFC_HIGH,
    MS_MFC_BYPASS,
    MS_MFC_COUNT
} EN_UI_MFC;

/// Receiver TV format
typedef enum
{
    E_DISPLAY_TVFORMAT_4TO3,
    E_DISPLAY_TVFORMAT_16TO9SD,
    E_DISPLAY_TVFORMAT_16TO9HD,
    E_DISPLAY_TVFORMAT_COUNT,
} EN_UI_DISPLAY_TVFORMAT;

/** film mode settings */
typedef enum
{
    /// FILM min
    MS_FILM_MIN,
    /// FILM off
    MS_FILM_OFF = MS_FILM_MIN,
    /// FILM on
    MS_FILM_ON,
    /// FILM number
    MS_FILM_NUM,
}EN_UI_MS_FILM;

/** 3D Video Auto Start */
typedef enum
{
    ///auto start off
    DB_ThreeD_Video_AUTOSTART_OFF = 0,
    ///auto start 2D
    DB_ThreeD_Video_AUTOSTART_2D,
    ///auto start 3D
    DB_ThreeD_Video_AUTOSTART_3D,
    ///auto start total number
    DB_ThreeD_Video_AUTOSTART_COUNT
}EN_ThreeD_Video_AUTOSTART;

/** 3D Video mode */
typedef enum
{
    DB_ThreeD_Video_OFF = 0,
    DB_ThreeD_Video_2D_TO_3D,
    DB_ThreeD_Video_SIDE_BY_SIDE,
    DB_ThreeD_Video_TOP_BOTTOM,
    DB_ThreeD_Video_FRAME_INTERLEAVING,
    DB_ThreeD_Video_PACKING_1080at24p,
    DB_ThreeD_Video_PACKING_720at60p,
    DB_ThreeD_Video_PACKING_720at50p,
    DB_ThreeD_Video_CHESS_BOARD,
    DB_ThreeD_Video_COUNT
} EN_UI_ThreeD_Video;

/** Audyssey dynamic volume setting */
typedef enum
{
    /// OFF
    AUDYSSEY_DYNAMIC_VOLUME_OFF = 0,
    /// ON
    AUDYSSEY_DYNAMIC_VOLUME_ON,
    /// number of the setting
    AUDYSSEY_DYNAMIC_VOLUME_NUM
} EN_UI_AUDYSSEY_DYNAMIC_VOLUME_MODE;

/** Audyssey EQ setting */
typedef enum
{
    /// OFF
    AUDYSSEY_EQ_OFF = 0,
    /// ON
    AUDYSSEY_EQ_ON,
    /// number of the setting
    AUDYSSEY_EQ_NUM
} EN_UI_AUDYSSEY_EQ_MODE;

/** Define surround mode */
typedef enum
{
    /// surround mode is mountain
    SURROUND_MODE_MOUNTAIN,       //0
    /// surround mode is champaign
    SURROUND_MODE_CHAMPAIGN,      //1
    /// surround mode is city
    SURROUND_MODE_CITY,           //2
    /// surround mode is theater
    SURROUND_MODE_THEATER,        //3
    SURROUND_MODE_NUM
} EN_UI_SURROUND_TYPE;

/** Define audio mode setting */
typedef enum
{
    /// audio mode is LR
    AUD_MODE_LR,
    /// audio mode is LL
    AUD_MODE_LL,
    /// audio mode is RR
    AUD_MODE_RR,
    AUD_MODE_NUM
} EN_UI_AUD_MODE;

/** define of local dimm */
typedef enum
{
    /// local dimm min
    MS_LOCAL_DIMM_MIN,
    /// local dimm off
    MS_LOCAL_DIMM_OFF = MS_LOCAL_DIMM_MIN,
    /// local dimm low
    MS_LOCAL_DIMM_LOW,
    /// local dimm middle
    MS_LOCAL_DIMM_MIDDLE,
    /// local dimm high
    MS_LOCAL_DIMM_HIGH,
    /// total local dimm type number
    MS_LOCAL_DIMM_NUM,
} EN_UI_LOCAL_DIMM_MODE;

/// Active Backlight settings
typedef enum
{
    /// Active Backlight min
    MS_ACTIVE_BACKLIGHT_MIN,
    /// Active Backlight off
    MS_ACTIVE_BACKLIGHT_OFF = MS_ACTIVE_BACKLIGHT_MIN,
    /// Active Backlight on
    MS_ACTIVE_BACKLIGHT_ON,
    /// Active Backlight number
    MS_ACTIVE_BACKLIGHT_NUM,
} EN_UI_MS_ACTIVE_BACKLIGHT;

/// Auto Brightness settings
typedef enum
{
    /// Auto Brightness min
    MS_AUTO_BRIGHTNESS_MIN,
    /// Auto Brightness off
    MS_AUTO_BRIGHTNESS_OFF = MS_AUTO_BRIGHTNESS_MIN,
    /// Auto Brightness on
    MS_AUTO_BRIGHTNESS_ON,
    /// Auto Brightness number
    MS_AUTO_BRIGHTNESS_NUM,
} EN_UI_MS_AUTO_BRIGHTNESS;

/** define Customer DB Index */
typedef enum
{
    /// 3D Router Name
    EN_DB_3DVideoRouterIndex,
    /// 3D To 2D Router Name
    EN_DB_3DTo2DVideoRouterIndex,
    /// Display Mode Router Name
    EN_DB_DisplayModeRouterIndex,
    /// ADC Adjust Name
    EN_DB_FactoryADCAdjustIndex,
    /// Color Temp Name
    EN_DB_FactoryColorTempIndex,
    /// Color TempEx Name
    EN_DB_FactoryColorTempExIndex,
    /// NonLiner Name
    EN_DB_NonLinearAdjustIndex,
    /// NonLiner Name for 3D
    EN_DB_NonLinearAdjust3DIndex,
    /// Color TempEx Name for 3D
    EN_DB_FactoryColorTempEx3DIndex,
    /// 4K2K 3D Router Name
    EN_DB_4K2K3DVideoRouterIndex,
    /// 4K2K 60Hz 3D Router Name
    EN_DB_4K2K60Hz3DVideoRouterIndex,
    /// Path Max
    EN_DB_INDEX_MAX,
}EN_UI_DB_TYPE_INDEX;

typedef enum
{
    EN_UI_NO_MODULE     = 0x00,
    EN_UI_MODULE_INITIALIZING,
    EN_UI_MODULE_READY,
    EN_UI_MODULE_RESET,
} E_UI_CARD_STATE;

///CI+ Credential mode
typedef enum
{
    ///CI+ Credential mode : default
    EN_CREDENTIAL_DEFAULT = 0,
    ///CI+ Credential mode : test
    EN_CREDENTIAL_TEST,
    ///CI+ Credential mode : production
    EN_CREDENTIAL_PRODUCTION,
    ///CI+ Credential mode count
    EN_CREDENTIAL_COUNT
}EN_CREDENTIAL_MODE;

typedef enum
{
    EN_UI_CI_FUNCTION_RM                                   = 0x00,
    EN_UI_CI_FUNCTION_APPINFO,
    EN_UI_CI_FUNCTION_CAS,
    EN_UI_CI_FUNCTION_HC,
    EN_UI_CI_FUNCTION_DT,
    EN_UI_CI_FUNCTION_MMI,
    EN_UI_CI_FUNCTION_LSC,
    EN_UI_CI_FUNCTION_CC,
    EN_UI_CI_FUNCTION_HLC,
    EN_UI_CI_FUNCTION_CU,
    EN_UI_CI_FUNCTION_OP,
    EN_UI_CI_FUNCTION_SAS,
    EN_UI_CI_FUNCTION_APPMMI,
    EN_UI_CI_FUNCTION_PMT,
    EN_UI_CI_FUNCTION_HSS,
    EN_UI_CI_FUNCTION_AUTH,
    EN_UI_CI_FUNCTION_DEFAULT,
    EN_UI_CI_BY_PASS_MODE,
    EN_UI_CI_PERFORMANCE_MONITOR,
    EN_UI_CI_PLUS_CREDENTIAL_MODE,
    EN_UI_CI_PLUS_TEST_CREDENTIAL_PATH,
    EN_UI_CI_PLUS_PRODUCTION_CREDENTIAL_PATH,
//  please insert new enum before debug count
    EN_UI_CI_FUNCTION_DEBUG_COUNT
} EN_UI_CI_FUNCTION;

typedef enum
{
    EN_UI_MMI_TYPE_NONE  = 0x00,
    EN_UI_MMI_TYPE_MENU,
    EN_UI_MMI_TYPE_LIST,
    EN_UI_MMI_TYPE_ENQ,
    EN_UI_MMI_TYPE_TEXT
} EN_UI_MMI_TYPE;

/*********************end enum***************************/

/*******************************************************/
/** SSC settings */
typedef struct
{
    /// flag to indicate LVDS SSC enable
    bool Lvds_SscEnable;
    /// flag to indicate MIU SSC enable
    bool Miu_SscEnable;
    /// LVDS SSC span value
    unsigned int     Lvds_SscSpan;
    /// LVDS SSC step value
    unsigned int      Lvds_SscStep;
    /// MIU SSC span value
    unsigned int      Miu_SscSpan[MIU_COUNTS_MAXIMUM];
    /// LVDS SSC step value
    unsigned int      Miu_SscStep[MIU_COUNTS_MAXIMUM];
} MS_UI_FACTORY_SSC_SET;

/** SSC setting (2 miu settings) */
typedef struct
{
    /// LVDS SSC span value
    unsigned int      Lvds_SscSpan;
    /// LVDS SSC step value
    unsigned int      Lvds_SscStep;
    /// MIU0 SSC span value
    unsigned int      Miu0_SscSpan;
    /// MIU0 SSC step value
    unsigned int      Miu0_SscStep;
    /// MIU1 SSC span value
    unsigned int      Miu1_SscSpan;
    /// MIU1 SSC step value
    unsigned int      Miu1_SscStep;
    /// flag to indicate LVDS SSC enable
    bool Lvds_SscEnable;
    /// flag to indicate MIU SSC enable
    bool Miu_SscEnable;
} MS_UI_FACTORY_SSC2_SET;

/** 6M30 SSC setting  */
typedef struct
{
    /// LVDS 6M30SSC span value
    unsigned char Lvds_6M30SscSpan;
    /// LVDS 6M30SSC step value
    unsigned char Lvds_6M30SscStep;
    /// MIU 6M30SSC span value
    unsigned char Miu_6M30SscSpan;
    /// MIU 6M30SSC step value
    unsigned char Miu_6M30SscStep;
    /// flag to indicate LVDS 6M30SSC enable
    bool Lvds_6M30SscEnable;
    /// flag to indicate MIU 6M30SSC enable
    bool Miu_6M30SscEnable;
} MS_UI_FACTORY_6M30SSC_SET;

/** VIF setting */
typedef struct
{
    /// top
    unsigned char VifTop;
    /// VGA max
    unsigned int VifVgaMaximum;
    /// Gain distribution threshold
    unsigned int GainDistributionThr;
    /// VIF AGC VGA base
    unsigned char VifAgcVgaBase;
    /// china descrambler box mode: A1(0~5) J2(0~11) usefull
    unsigned char ChinaDescramblerBox;
    /// CRKP1
    unsigned char VifCrKp1;
    /// CRKI1
    unsigned char VifCrKi1;
    /// CRKP2
    unsigned char VifCrKp2;
    /// CRKI2
    unsigned char VifCrKi2;
    /// CRKP
    unsigned char VifCrKp;
    /// CRKI
    unsigned char VifCrKi;
    /// CR lock threshold
    unsigned int VifCrLockThr;
    /// CR threshold
    unsigned int VifCrThr;
    /// flag to indicate CR KPKI
    bool VifCrKpKiAdjust;
    /// delay reduce
    unsigned char VifDelayReduce;
    /// over modulation
    bool VifOverModulation;
    /// clamping values
    unsigned int VifClampgainClampOvNegative;
    /// clamping gain values
    unsigned int VifClampgainGainOvNegative;
    /// VIF AGC REF VALUE
    unsigned char VifACIAGCREF;
    ///VIF AGC
    unsigned char VifAgcRefNegative;
    ///VIF_ASIA_SIGNAL_OPTION
    bool VifAsiaSignalOption;
    /// china descrambler box deolay,:
    unsigned int ChinaDescramblerBoxDelay;
}MS_UI_Factory_NS_VIF_SET;


/** define factory CI setting */
typedef struct
{
    ///check sum
    unsigned int u16CheckSum;
#if (CI_PLUS_ENABLE == 1)
    /// CI credential mode
    unsigned char  enCredentialMode;
#endif
    ///CI PerformanceMonitor
    unsigned char bPerformanceMonitor;
    ///CI debug level 0~4
    unsigned char u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_DEBUG_COUNT];
}ST_UI_FACTORY_CI_SETTING;

typedef struct
{
    /// checksum
    unsigned int u16CheckSum;
    /// The start padding of scheduled recordings in minutes.
    /// This value should not be changed if there exists schedule recording.
    unsigned int u16ScheduledRecordStartPadding;
    /// The end padding of scheduled recordings in minutes.
    /// This value should not be changed if there exists schedule recording.
    unsigned int u16ScheduledRecordEndPadding;
} MS_UI_PVR_SETTING;

/** define of pip setting */
typedef struct
{
    /// check sum <<checksum should be put at top of the struct, do not move it to other place>>
    unsigned int  u16CheckSum;
    /// PIP mode setting
    unsigned int  enPipMode;
    /// subInputSource setting
    unsigned int  enSubInputSourceType;
    /// Pip size setting
    unsigned int  enPipSize;
    /// Pip position setting
    unsigned int  enPipPosition;
    /// pip bolderenable setting
    bool          bBolderEnable;
    /// pip sound src setting
    unsigned int  enPipSoundSrc;
    //==Used in Factory Menu=========================
    /// border width setting 1 ~ 10
    unsigned char u8BorderWidth;
    /// pip enable setting
    bool          bPipEnable;
    //===============================================
} PipUiSetting;

/** factory device setting */
typedef struct
{
    /// power mode setting
    MS_UI_FACTORY_POWER_MODE stPowerMode;
    /// VD setting
    MS_UI_Factory_NS_VD_SET stNSVDsetting;
        /// VIF setting
   MS_UI_Factory_NS_VIF_SET stNSVIFsetting;
    /// SSC setting
   MS_UI_FACTORY_SSC_SET stSSCsetting;
    /// SSC2 setting
   MS_UI_FACTORY_SSC2_SET stSSC2setting;
    /// 6M30SSC setting
   MS_UI_FACTORY_6M30SSC_SET st6M30SSCsetting;
}MS_FACTORY_UI_EXTERN_SETTING;

/** define user _SoundSettingType */
typedef struct _SoundSettingUiType
{
    /// check sum <<checksum should be put at top of the struct, do not move it to other place>>
    unsigned int    u16CheckSum;
    /// Sound Mode Enumeration
    EN_UI_SOUND_MODE     soundMode;
    /// The settings for each sound mode
    SoundModeSetting astSoundModeSetting[SOUND_MODE_NUM];
    /// Audyssey Dynamic Volume
    EN_UI_AUDYSSEY_DYNAMIC_VOLUME_MODE audysseyDynamicVolume;
    /// Audyssey EQ
    EN_UI_AUDYSSEY_EQ_MODE audysseyEq;
    /// Surround Sound Mode
    EN_UI_SURROUND_MODE surroundSoundMode;
    /// surround mode enum
    EN_UI_SURROUND_TYPE  surround;
    /// AVC enable
    bool           enableAVC;
    /// Volume
    unsigned char                volume;
    /// Headphone Volume
    unsigned char                 HPVolume;
    /// Balance
    unsigned char                 balance;
    /// Primary_Flag
    unsigned char                 primaryFlag;
    /// Audio language setting 1
    MEMBER_LANGUAGE   soundAudioLanguage1;  //EN_LANGUAGE
    /// Audio language setting 2
    MEMBER_LANGUAGE   soundAudioLanguage2;  //EN_LANGUAGE
    /// Audio mute
    unsigned char                 muteFlag;     // for ATSC_TRUNK
    /// audio mode setting
    EN_UI_AUD_MODE       soundAudioChannel;
    /// AD enable
    bool           enableAd;
    /// AD volume adjust
    unsigned char                 adVolume;
    /// sound ad output
    EN_UI_SOUND_AD_OUTPUT adOutput;
    /// SPDIF mode setting
    SPDIF_TYPE_ enSPDIFMODE;
    /// the delay of SPDIF
    unsigned char spdifDelay;
    /// the delay of speaker
    unsigned char  speakerdelay;
    //audo speaker prescale value
    unsigned char  SpeakerPreScale[MAPI_INPUT_SOURCE_NUM];;
    //audo headphone prescale value
    unsigned char  HeadPhonePreScale[MAPI_INPUT_SOURCE_NUM];;
    //audo line-out prescale value
    unsigned char  LineOutPreScale[MAPI_INPUT_SOURCE_NUM];;
    //audo scart1 prescale value
    unsigned char  SCART1PreScale[MAPI_INPUT_SOURCE_NUM];;
    //audo scart2 prescale value
    unsigned char  SCART2PreScale[MAPI_INPUT_SOURCE_NUM];;
    /// DTV Audio Type
    EN_AUDIO_TRACK_TYPE enAudioType;

    /// DRC enable
    bool           bEnableDRC;
    HDMI_TYPE_ AudioHdmiType;
} MS_UI_USER_SOUND_SETTING;

typedef struct
{
    unsigned int n16BlueGain;
    unsigned int n16BlueOffset;
    unsigned int n16GreenGain;
    unsigned int n16GreenOffset;
    unsigned int n16RedGain;
    unsigned int n16RedOffset;
} MS_UI_COLOR_TEMPERATURE_DATA;

/** define color temperatue mode setting in 16 bit */
typedef struct
{
    /// check sum <<checksum should be put at top of the struct, do not move it to other place>>
    unsigned int u16CheckSum;
    /// color temperature mode setting for dvbt
    PqlColorTempexData astColorTempEx[COLOR_TEMP_NUM][MS_INPUT_SOURCE_TYPE_NUM];    //24*8 Byte    //Dawn :color temp for each source

} T_MS_UI_COLOR_TEMPEX;

typedef struct
{
    /// noise reduction setting
    unsigned long int eNR;
    /// MPEG noise reduction setting
    unsigned long int eMPEG_NR;
} UI_NOISE_REDUCE_MODE;

typedef struct
{
    /// check sum <<checksum should be put at top of the struct, do not move it to other place>>
    unsigned int u16CheckSum;
    /// brightness
    unsigned char u8SubBrightness;
    /// contrast
    unsigned char u8SubContrast;
} MS_UI_SUB_COLOR;

typedef struct
{
    /// 3D Video Setting
    unsigned long int eThreeDVideo;
    /// 3D Video Display Mode
    unsigned long int  eThreeDVideoDisplayMode;
    /// 3D Video Display Formmat
    unsigned long int  eThreeDVideoDisplayFormat;
    /// 3D Video 3D Depth
    unsigned long int  eThreeDVideo3DDepth;
    /// 3D Video Auto Start
    unsigned long int  eThreeDVideoAutoStart;
    /// 3D Video 3D Output Aspect
    unsigned long int  eThreeDVideo3DOutputAspect;
    /// 3D Video 3D Left Rigth View Switch
    unsigned long int  eThreeDVideoLRViewSwitch;
} MS_UI_3D_VIDEO_MODE;

typedef struct
{
   ///overscanHposition
    unsigned char   OverScanHposition;
   ///overscanVposition
    unsigned char   OverScanVposition;
   ///OverScanHRatio
    unsigned char   OverScanHRatio;
   ///OverScanVRatio
    unsigned char   OverScanVRatio;
} MS_UI_OVERSCAN_SETTING_USER;

//ST_VIDEO
typedef struct
{
    long int arcType;
    MS_UI_PICTURE astPicture [PICTURE_NUMS];
    long int checkSum;
    long int dynamicContrast;
    long int filmMode;
    long int lastAudioStandardMode;
    long int lastVideoStandardMode;
    UI_NOISE_REDUCE_MODE noiseReductionMode[E_COLOR_TEMP_NUM];
    long int outputResolution;
    int picture;
    MS_UI_SUB_COLOR subColor;
    MS_UI_3D_VIDEO_MODE threeDimensionInforVideoMode;
    long int tvFormat;
    long int tvSystemSetting;
    MS_UI_OVERSCAN_SETTING_USER userOverScanMode;
     long int enAutoModeARCType;
    /// PC mdoe aspect ratio type
    long int enPcModeARCType;
    /// GAME mode aspect ratio type
    long int enGameModeARCType;
    /// Current pciture mode is 0:Normal mode or 1:PC mode , only for auto mode
    bool bIsPcMode;
} MS_UI_VIDEO;

typedef struct
{
    /// flags to indicate network enable
    bool bnetSelected;
    /// dynamic or static IP
    unsigned long int u8Netconfig;
    /// IP address byte 0
    unsigned char u8IPAddr0;
    /// IP address byte 1
    unsigned char u8IPAddr1;
    /// IP address byte 2
    unsigned char u8IPAddr2;
    /// IP address byte 3
    unsigned char u8IPAddr3;

    /// netmask byte 0
    unsigned char u8Netmask0;
    /// netmask byte 1
    unsigned char u8Netmask1;
    /// netmask byte 2
    unsigned char u8Netmask2;
    /// netmask byte 3
    unsigned char u8Netmask3;

    /// gateway byte 0
    unsigned char u8Gateway0;
    /// gateway byte 1
    unsigned char u8Gateway1;
    /// gateway byte 2
    unsigned char u8Gateway2;
    /// gateway byte 3
    unsigned char u8Gateway3;

    /// DNS byte 0
    unsigned char u8DNS0;
    /// DNS byte 1
    unsigned char u8DNS1;
    /// DNS byte 2
    unsigned char u8DNS2;
    /// DNS byte 3
    unsigned char u8DNS3;

    /// IP address of the remote device
    char Ip[MAX_SMB_BUF_LEN];
    /// net device name
    char Ip_name[MAX_SMB_BUF_LEN];
    /// user name
    char NET_User_name[MAX_SMB_BUF_LEN];
    /// password
    char NET_Password[MAX_SMB_BUF_LEN];
} MS_UI_NetworkSetting;

typedef struct
{
    /// MM text subtitle font size
    unsigned char u8SubtitleSpecific;
    /// Text subtitle background color
    unsigned char u8SubtitleBGColor;
    /// Text subtitle font color
    unsigned char u8SubtitleFontColor;
    /// Photo slide show time
    unsigned char u8SlideShowTime;
    /// Photo slide show mode
    unsigned char u8SlideShowMode;
    /// Movie/Photo Preview On or off
    unsigned char fPreviewOn; //      : 1;
    /// Movie Resume on or off
    unsigned char fResumePlay; //      : 1;
    /// Reserved
    unsigned char Reserved; //         : 6;
} MS_UI_UserMmSetting;

typedef struct
{
    /// the ID of Location.
    unsigned int u16LocationNo;
    /// the Longitude value
    int s16ManualLongitude;
    /// the Latitude value
    int s16ManualLatitude;
} MS_UI_UserLocationSetting;

typedef struct
{
    /// MFC setting
    unsigned long int eMFC;
} MS_UI_StMfcMode;

typedef struct
{
    /// display mode
    unsigned long int enDisplayMode;
    /// 3d format
    unsigned long int en3DFormat;
    /// 2d format
    unsigned long int en2DFormat;
    /// auto start setting
    unsigned long int enAutoStart;
    /// the period of watching 3D, time's unit is ms
    unsigned long int en3DTimerPeriod;
} MS_UI_St3DSetting;

/** define  UserUiSystemSetting */
typedef struct _UserUiSystemSetting
{
    /// check sum <<checksum should be put at top of the struct, do not move it to other place>>
    unsigned int u16CheckSum;
    /// check to run InstallationGuide or not
    bool fRunInstallationGuide;
    /// check if no channel to show banner
    bool fNoChannel;
    /// check SI auto update off or not,CableReady Manual scanning shall set SI updates to "OFF" on all physical channels.
    bool bDisableSiAutoUpdate;
    /// input source selection
    unsigned long int enInputSourceType;
    /// country setting
    unsigned long int  Country;
    /// Cable Operator setting
    unsigned long int  enCableOperators;
    /// Satellite platform setting
    unsigned long int  enSatellitePlatform;
    ///Network ID field
    unsigned int u16NetworkId;
    /// OSD language
    unsigned long int  Language;
    /// subtitle language setting
    UserSubtitleSetting stSubtitleSetting;
    /// color temperature setting
    PqlColorTempData stUserColorTemp;
    /// color temperature setting for dvbt
    PqlColorTempexData stUserColorTempEx[E_INPUT_SOURCE_TYPE_NUM];
    /// 3D settings
    st3dInfo st3DInfo;
#if (STEREO_3D_ENABLE == 1)
    /// 3D ARC
    unsigned long int  en3DARC;
#endif
    /// user's MM setting
    MS_UI_UserMmSetting stUserMMSetting;
    /// Network setting
    MS_UI_NetworkSetting stNetworkSetting;
    /// user location setting
    MS_UI_UserLocationSetting stUserLocationSetting;
    /// SoftwareUpdate 0=Off, 1= On
    unsigned char fSoftwareUpdate;
    /// OAD Upddate Time
    unsigned char U8OADTime;
    /// OAD Scan auto execution after system bootup 0=Off, 1=On
    unsigned char fOADScanAfterWakeup;
    /// autovolume 0=Off, 1= On
    unsigned char fAutoVolume;
    /// DcPowerOFFMode 0= Power Off, 1= DC Power Off
    unsigned char fDcPowerOFFMode;
    /// DTV Player Extend
    unsigned char DtvRoute;
    /// SCART output RGB
    unsigned char ScartOutRGB;
    /// OSD Transparency, 0=0%, 1=25%, 2=50%, 3=75%, 4=100%
    unsigned char U8Transparency;
    /// OSD timeout (seconds)
    unsigned long int u32MenuTimeOut;
    /// Audio Only
    unsigned char AudioOnly;
    /// watch dog
    unsigned char bEnableWDT;
    ///Favorite Network Region
    unsigned char u8FavoriteRegion;
    ///Bandwidth
    unsigned char u8Bandwidth;
    ///Time Shift Size Type
    unsigned char u8TimeShiftSizeType;
    ///Do OAD scan right now
    unsigned char fOadScan;
    ///PVR Record All Enable in factory menu
    unsigned char bEnablePVRRecordAll;
    ///Color range mode 0-255\16-235  for HDMI
    unsigned char u8ColorRangeMode;
    ///HDMI Audio Source  0: DVD 1: PC
    unsigned char u8HDMIAudioSource;
    /// PVR enable always timeshift (1 bit, union with bEnablePVRRecordAll if needed)
    unsigned char bEnableAlwaysTimeshift;
    /// MFC
    MS_UI_StMfcMode MfcMode;
    /// enum for SUPER
    unsigned long int eSUPER;
    ///Favorite type name,DVBS2 multi-favorite list
    char FavTypeName[MAX_FAVLIST_NUM][MAX_FAVTYPE_NAME_SIZE];
    /// DVBS ChannelList Program Sorting Type
    unsigned char u8ProgramSortingType;
    /// check to Uart Bus
    bool bUartBus;

    #if (AUTOZOOM_ENABLE == 1)
    ///For DTV AutoZoom
    unsigned char m_AutoZoom;
    #endif

    // OverScan on/off for all source
    #if (ENABLE_OVERSCAN_FOR_ALL_SOURCE == 1)
    bool bOverScan;
    #endif

    #if (STEREO_3D_ENABLE == 1)
    /// 3D settings
    MS_UI_St3DSetting st3DSetting;
    #endif
#if (ISDB_SYSTEM_ENABLE == 1)
    /// Brazil video system
    unsigned char  m_u8BrazilVideoStandardType;
#endif

    unsigned char m_u8SoftwareUpdateMode;

    ///For rename inputSource TV
    char InputSourceName_TV[INPUTSOURCE_NAME_MAX_SIZE];
    ///For rename inputSource Componant1
    char InputSourceName_Componant1[INPUTSOURCE_NAME_MAX_SIZE];
    ///For rename inputSource PC_RGB
    char InputSourceName_PC_RGB[INPUTSOURCE_NAME_MAX_SIZE];
    ///For rename inputSource PC_RGB2
    char InputSourceName_PC_RGB2[INPUTSOURCE_NAME_MAX_SIZE];
    ///For rename inputSource PC_RGB3
    char InputSourceName_PC_RGB3[INPUTSOURCE_NAME_MAX_SIZE];
    ///For rename inputSource HDMI1
    char InputSourceName_HDMI1[INPUTSOURCE_NAME_MAX_SIZE];
    ///For rename inputSource HDMI2
    char InputSourceName_HDMI2[INPUTSOURCE_NAME_MAX_SIZE];
    ///For rename inputSource HDMI3
    char InputSourceName_HDMI3[INPUTSOURCE_NAME_MAX_SIZE];
    ///For rename inputSource HDMI4
    char InputSourceName_HDMI4[INPUTSOURCE_NAME_MAX_SIZE];
    ///For rename inputSource AV1
    char InputSourceName_AV1[INPUTSOURCE_NAME_MAX_SIZE];
    ///For rename inputSource RVU
    char InputSourceName_RVU[INPUTSOURCE_NAME_MAX_SIZE];

    unsigned long int OSD_Active_Time;
    bool m_MessageBoxExist;//0 not exit 1 exit

#if (FREEVIEW_AU_ENABLE == 1)
    ///OAD SW VErsion
    unsigned int u16LastOADVersion;
#endif
    bool bEnableAutoChannelUpdate;//run standby scan and OAD check when enter standby mode
#if (PVR_ENABLE == 1)
    char u8PvrUsbDeviceSerialNumber[USB_SERIAL_NUMBER_LENGTH];
    unsigned char u8PvrSelectedPartition;
#endif
    unsigned long int u32MsrvTimerCounter;

    unsigned long int enLocalDimm;
    bool bATVChSwitchFreeze;//ATV channel switch mode:0->black screen,1->freeze

#if (ENABLE_NETREADY == 1)
    unsigned long int nsConfig;
#endif

#if (OFL_DET == 1)
    /// offline detect 0=Off, 1= On
    bool bSourceDetectEnable;
    /// Auto switch source if signal plug out/in, 0=Off, 1= On
    bool bAutoSourceSwitch;
#endif
    bool bDisableDynamicRescan;//disable dynamic rescan at least for country Germany/Austria/Switzerland.
    ///Last TV signal source in RF for Scart Out TV mode
    unsigned long int enLastTVInputSourceType;
    ///Auto switch MHL when plug out/in, 0 = Off, 1 = On
    bool bAutoMHLSwitch;
#if (FREEVIEW_AU_ENABLE == 1)
    /// Viewer prompt to update
    bool bViewerPrompt;
#endif
#if(CI_PLUS_ENABLE == 1)
    unsigned char u8OpMode;
    unsigned long int u32CicamIdentifier;
#endif

#if (CA_ENABLE == 1)
    unsigned long int u32FeatureConfigBitmap;
    unsigned long int u32FeatureConfigExtendBitmap;
    unsigned char u8DebitLimitThreshold;
    unsigned long int stIppvCallbackInfo;
    unsigned long int stDataMiningParam;
    unsigned long int stForceStatusReport;
    unsigned long int stDownloadType;
    unsigned long int u32IrdSequenceNum;
    unsigned long int u32CaPinCodeId;
    unsigned long int u16BouquetID;
    char u8ZoneID[CA_ZONE_ID_LEN];
    unsigned char u8CustomerServicePhoneNumber;
    unsigned char u8PPVOrderPhoneNumber;
    unsigned long int astTextMessage;
    unsigned long int stAttributeDisplay;
#endif

#if (HBBTV_ENABLE == 1)
    bool bEnableHbbtv;
    bool bEnableStoreCookies;
#endif
#if (WOL_ENABLE == 1)
    bool bWOLEnable;
#endif

#if (STR_ENABLE == 1)
    /// 0: always DC --- 1: always AC --- >1: how many times of DC before AC
    unsigned long int u32StrPowerMode;
#endif

#if (XVYCC_ENABLE == 1)
    bool bxvYCCOnOff;
#endif

#if (STB_ENABLE == 1)
    ///Deep color status, 0 = Off, 1 = On
    bool bDeepColor;
#endif

#if (PVR_ENABLE == 1)
  /// check if it was recording before poweroff
    bool bRecordStopByPoweroff;
#endif
    bool bEnableACR;

    /// Monitor HDMI ITC  0: Off  1: On
    bool bMonitorITC;
    /// For "KDG TD 0017 Digital TV Receiver Analysis", version 1.2.1, 5.3. Bouquet and Service Arrangement Update
    bool bServiceListNeedRearrange;
#if ((ISDB_SYSTEM_ENABLE == 1) || (ESASIA_NTSC_SYSTEM_ENABLE == 1))
    /// BIT1:SDT, BIT2:NIT, BIT3:PAT, BIT4:PMTa, BIT5:PMTo, BIT6:EIT, BIT_ALL: All. debug mode used to control SI Monitor ON/OFF
    unsigned char u8MonitorDebugMode;
#endif
#if (CI_PLUS_ENABLE == 1)
    /// Store if tuner occupited by CI for CU
    bool bCiOccupiedTuner;
    /// Store user's pin code setting
    unsigned long int u16CiPinCode;
#endif
   bool bEnableUHF7M;
} MS_UI_UserSystemSetting;


/**********************************************************/

class UI_System_Database
{
public:
     //-------------------------------------------------------------------------------------------------
    /// Class Constructor.
    //-------------------------------------------------------------------------------------------------
    UI_System_Database(void);

    //-------------------------------------------------------------------------------------------------
    /// Class Destructor.
    //-------------------------------------------------------------------------------------------------
    ~UI_System_Database(void);
    //-------------------------------------------------------------------------------------------------
    /// Get the instance of UI_System_Database
    /// @return UI_System_Database: the pointer to the instance
    //-------------------------------------------------------------------------------------------------
    static UI_System_Database* GetUiSystemDbInstance(void);
    //-------------------------------------------------------------------------------------------------
    /// Get Current OSD Language Setting
    /// @return MEMBER_LANGUAGE: OSD Language Setting
    //-------------------------------------------------------------------------------------------------
    virtual MEMBER_LANGUAGE GetOsdLanguage();

    //-------------------------------------------------------------------------------------------------
    /// Set OSD Language Setting
    /// @param pValue \b IN: the pointer to structure of MEMBER_LANGUAGE
    /// @return None
    //-------------------------------------------------------------------------------------------------
    virtual void SetOsdLanguage(MEMBER_LANGUAGE *pValue);

    //-------------------------------------------------------------------------------------------------
    /// Get Current System Country Setting
    /// @return MEMBER_COUNTRY: System Country Setting
    //-------------------------------------------------------------------------------------------------
    virtual MEMBER_COUNTRY GetSystemCountry(void);
#if (STEREO_3D_ENABLE == 1)
    virtual void SetV3DAspectRatio(const int u8Value);
#endif
    virtual void SetSoundMode(const int u8Value);
    //--------- Factory ----------
    virtual void GetFactoryExtSetting_Power_Mode(unsigned char* u8PowerMode);
    virtual void SetFactoryExtSetting_Power_Mode(unsigned char* u8PowerMode);
    virtual void GetVideoSetting(MS_UI_VIDEO *pValue, MAPI_INPUT_SOURCE_TYPE *pParam);
    virtual void SetVideoSetting(MS_UI_VIDEO *pValue, MAPI_INPUT_SOURCE_TYPE  *pParam);
    virtual void SaveUiVideoSetting(unsigned char u8Index);
    virtual void LoadUiVideoSetting(unsigned char u8Index);
    virtual void GetAudioSetting(MS_UI_USER_SOUND_SETTING *pstSoundSetting);
    virtual void SaveUiSoundSetting(MS_UI_USER_SOUND_SETTING *pstSoundSetting);
    virtual void LoadUiSoundSetting(void);
    virtual void SetAudioSetting(MS_UI_USER_SOUND_SETTING *pstSoundSetting);
    virtual void GetUserSystemSetting(MS_UI_UserSystemSetting *pstUserSystemSetting);
    virtual void LoadUiSysSetting(void);
    virtual void SetUserSystemSetting(MS_UI_UserSystemSetting *pstUserSystemSetting);
    virtual void SaveUiSysSetting(MS_UI_UserSystemSetting *pstUserSystemSetting);
    virtual void GetMediumSetting(ST_TV_MEDIUM_SETTING *pstMediumSetting);
    virtual void SetMediumSetting(ST_TV_MEDIUM_SETTING *pstMediumSetting);
    virtual unsigned int GetSystemNetworkId(void);
    virtual void SetSystemNetworkId(unsigned int u16NetworkIdValue);
    virtual bool IsInstallationGuideEnabled(void);
    virtual bool IsAutoChannelUpdateEnabled(void);
#if (CI_PLUS_ENABLE == 1)
    virtual unsigned char GetCredentialMode(void);
#endif
    virtual void SetInstallationguideEnabled(bool *pValue);
    virtual void SetColorTempEx(PQL_COLOR_TEMPEX_DATA *pOrgValue, void *pParam, MAPI_INPUT_SOURCE_TYPE  eCurrentInputType);
    virtual void GetColorTempEx(PQL_COLOR_TEMPEX_DATA *pValue, void *pParam, MAPI_INPUT_SOURCE_TYPE enSrcType);
    virtual void GetPEQSetting(void *pValue, unsigned char u8BandIndex);
    virtual void SetPEQSetting(void *pValue, unsigned char u8BandIndex);
    virtual void GetFactoryExtSetting_NSVD(MS_UI_Factory_NS_VD_SET *pValue);
    virtual void SetFactoryExtSetting_NSVD(MS_UI_Factory_NS_VD_SET *pValue);
    virtual void GetFactoryExtSetting_VIF(MS_UI_Factory_NS_VIF_SET *pValue);
    virtual void SetFactoryExtSetting_VIF(MS_UI_Factory_NS_VIF_SET *pValue);
    virtual void GetFactoryExtSetting_SSC(MS_UI_FACTORY_SSC_SET *pValue);
    virtual void SetFactoryExtSetting_SSC(MS_UI_FACTORY_SSC_SET *pValue);
    virtual void GetFactoryExtSetting_6M30SSC(MS_UI_FACTORY_6M30SSC_SET *pValue);
    virtual void SetFactoryExtSetting_6M30SSC(MS_UI_FACTORY_6M30SSC_SET *pValue);
    virtual void GetFactoryVideoSetting(MS_UI_VIDEO *pstUiVideo, MAPI_INPUT_SOURCE_TYPE *penSrcType);
    virtual void GetFactoryAudioSetting(MS_UI_USER_SOUND_SETTING *pstSoundSetting);
    virtual EN_UI_MS_INPUT_SOURCE_TYPE UITransMapiInputSourceToMsInputSoutrceType(MAPI_INPUT_SOURCE_TYPE enInputSrc);
    virtual unsigned char GetPerformanceMonitor(void);
    virtual void SetPerformanceMonitor(unsigned char pstPerformanceMonitor);
    virtual unsigned int UiCalCheckSum(unsigned char *pBuf, unsigned int u16BufLen);
    virtual void GetSubtitleSetting(UserSubtitleSetting* pUserSubtitleSetting);
    virtual void SetSubtitleSetting(UserSubtitleSetting* pUserSubtitleSetting);
    virtual void GetLocationSetting(MS_UI_UserLocationSetting *pValue);
    virtual void SetLocationSetting(MS_UI_UserLocationSetting *pValue);
    virtual void SetCIDebugLevel(EN_UI_CI_FUNCTION enDebugIndex, unsigned char u8DebugLevel);
    virtual unsigned char GetCIDebugLevel(EN_UI_CI_FUNCTION enDebugIndex);
    virtual void SaveUiCISet(void);

    class SQL_UI_Connect
    {
    public:
        //-------------------------------------------------------------------------------------------------
        /// Class Constructor.
        //-------------------------------------------------------------------------------------------------
        SQL_UI_Connect(void);
        SQL_UI_Connect(const char *dbpath, sqlite3 **ppdb);

        //-------------------------------------------------------------------------------------------------
        /// Class Destructor.
        //-------------------------------------------------------------------------------------------------
        ~SQL_UI_Connect(void);

        int SQL_UI_Open(const char *dbpath, struct sqlite3 **ppdb);
        int SQL_UI_Close(struct sqlite3 **ppdb);

    private:
        struct sqlite3 **m_ppdb;
    };

    class SQL_UI_Transaction
    {
    public:
        //-------------------------------------------------------------------------------------------------
        /// Class Constructor.
        //-------------------------------------------------------------------------------------------------
        SQL_UI_Transaction(struct sqlite3 *db);

        //-------------------------------------------------------------------------------------------------
        /// Class Destructor.
        //-------------------------------------------------------------------------------------------------
        ~SQL_UI_Transaction(void);

    private:
        struct sqlite3 *pdb;
        int rc;
        char *zErrMsg;
    };

    class SQL_UI_LookupPre
    {
    public:
        //-------------------------------------------------------------------------------------------------
        /// Class Constructor.
        //-------------------------------------------------------------------------------------------------
        SQL_UI_LookupPre(struct sqlite3 *db, const char *table, int &ColNum, char * Condition);

        //-------------------------------------------------------------------------------------------------
        /// Class Destructor.
        //-------------------------------------------------------------------------------------------------
        ~SQL_UI_LookupPre(void);

        struct sqlite3_stmt *pSqlstmt;
    };

    //-------------------------------------------------------------------------------------------------
    /// SQL command package
    //-------------------------------------------------------------------------------------------------
    virtual int SQL_UI_Step(struct sqlite3_stmt *pstmt);
    virtual int SQL_UI_GetColumnIndex(struct sqlite3_stmt *stmt,const char *ColName);
    virtual int SQL_UI_SetU32(struct sqlite3 *db, const char *Table, const char *Title, const char *Condition, unsigned int Value);
    virtual unsigned int SQL_UI_GetU32(struct sqlite3_stmt *stmt, const char *Title);
    const unsigned char * SQL_UI_GetText(struct sqlite3_stmt * stmt, const char * Title);
    virtual bool SQL_UI_SetText(struct sqlite3* db, const char *Table, const char * Title, const char * Condition, char * Text);
    virtual bool SQL_UI_GetArray(struct sqlite3_stmt * stmt, const char * Title, void * pArray, unsigned int u16Size, unsigned char ArrayType);
    virtual bool SQL_UI_SetArray(struct sqlite3* db, const char *Table, const char * Title, const char * Condition, void * pArray, unsigned int u16Size, unsigned char ArrayType);
    //-------------------------------------------------------------------------------------------------
    /// load the setting of color temperatue in 16 bit
    /// @return None
    //-------------------------------------------------------------------------------------------------
    virtual void LoadFactoryColorTempEx(void);
private:
    /// factory color temperature in 16 bit
    T_MS_UI_COLOR_TEMPEX m_stFactoryColorTempEx;
    /// the UI system setting
    MS_UI_UserSystemSetting m_stUiSysSetting;
    /// the Sound setting
    MS_UI_USER_SOUND_SETTING m_stUiSoundSetting;
    /// factory external setting
    MS_FACTORY_UI_EXTERN_SETTING m_stUiFactoryExt;
    /// last video setting
    MS_UI_VIDEO *m_pastUiVideo;
    /// the Medium setting
    ST_TV_MEDIUM_SETTING m_stUiMediumSetting;
    /// factory CI setting
    ST_UI_FACTORY_CI_SETTING m_stUiCISet;
    /// factory PEQ setting
    ST_AUDIO_PEQ_PARAM m_stUiPEQSet;
    /// factory NLA setting
    MS_UI_NLA_SETTING *m_pastUiNLASet;

    static UI_System_Database *m_UipInstance;

    struct sqlite3 *pUiSqldb;
    struct sqlite3 *pUiSqlfactorydb;
};

#endif  //__UISYSTEMDATABASE_H__

