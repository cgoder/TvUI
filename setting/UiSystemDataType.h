/****************************************************************************
 * Notice:      Copyright (c) Skyworth.
 *              All rights reserved.
 * Owner:      miaolibin@skyworth.com
 ****************************************************************************/
#ifndef __UISYSTEMDATATYPE_H__
#define __UISYSTEMDATATYPE_H__

/** picture mode setting */
typedef enum
{
    /// picture mode min
    PICTURE_MIN,
    /// picture mode dynamic
    PICTURE_DYNAMIC = PICTURE_MIN,
    /// picture mode normal
    PICTURE_NORMAL,
    /// picture mode mild
    PICTURE_MOVIE,
    /// picture mode user
    PICTURE_USER,
    /// picture mode game
    PICTURE_GAME,
    /// picture mode auto, auto select PC mode or Normal mode for HDMI and VGA
    PICTURE_AUTO,
    /// picture mode pc
    PICTURE_PC,
    /// picture mode number
    PICTURE_NUMS
} EN_UI_PICTURE_MODE;

///color temperature
typedef enum
{
    ///color temperature min
    COLOR_TEMP_MIN = 0,
    ///color temperature cool
    COLOR_TEMP_COOL = COLOR_TEMP_MIN,
    ///color temperature medium
    COLOR_TEMP_NATURE,
    ///color temperature warm
    COLOR_TEMP_WARM,
    ///color temperature user
    COLOR_TEMP_USER,
#if (MSTAR_TVOS == 1)
    ///color temperature user
    COLOR_TEMP_USER2,
    //MS_COLOR_TEMP_NATURE,
    COLOR_TEMP_MAX = COLOR_TEMP_USER2,
#else
    //MS_COLOR_TEMP_NATURE,
    COLOR_TEMP_MAX = COLOR_TEMP_USER,
#endif
    COLOR_TEMP_NUM,
} EN_UI_COLOR_TEMP;

///noise reduction
typedef enum
{
    ///noise reduction min
    PIC_NR_MIN = 0,
    // ------------------------------------
    ///noise reduction off
    PIC_NR_OFF = PIC_NR_MIN,
    ///noise reduction low
    PIC_NR_LOW,
    ///noise reduction middle
    PIC_NR_MIDDLE,
    ///noise reduction high
    PIC_NR_HIGH,
    ///noise reduction auto
    PIC_NR_AUTO,
    //MS_NR_DEFAULT,
    // ------------------------------------
    ///noise reduction number
    PIC_NR_NUM,
} EN_UI_PIC_NR;

/// define MPEG noise reduction
typedef enum
{
    /// MPEG noise reduction min
    PIC_MPEG_NR_MIN,
    /// MPEG noise reduction off
    PIC_MPEG_NR_OFF = PIC_MPEG_NR_MIN,
    /// MPEG noise reduction low
    PIC_MPEG_NR_LOW,
    /// MPEG noise reduction middle
    PIC_MPEG_NR_MIDDLE,
    /// MPEG noise reduction high
    PIC_MPEG_NR_HIGH,
    /// total mpeg noise reduction type number
    PIC_MPEG_NR_NUM,
 } EN_UI_PIC_MPEG_NR;

typedef enum
{
    PIC_ASPECT_RATIO_AUTO = 0,
    PIC_ASPECT_RATIO_4_3,
    PIC_ASPECT_RATIO_16_9,
    PIC_ASPECT_RATIO_ZOOM1,
    PIC_ASPECT_RATIO_ZOOM2,
    PIC_ASPECT_RATIO_JUST_SCAN,
    PIC_ASPECT_RATIO_PANORAMA,
    PIC_ASPECT_RATIO_POINT_TO_POINT,
    PIC_ASPECT_RATIO_COUNT
}EN_UI_PIC_ASPECT_RATIO;

typedef enum
{
    UI_SETTING_OFF, //0
    UI_SETTING_ON,  ///1
} EN_UI_SETTING_ON_OFF;

typedef enum
{
    /// NONE
    E_ANTENNA_TYPE_NONE,
    /// Air
    E_ANTENNA_TYPE_AIR,
    /// Cable
    E_ANTENNA_TYPE_CABLE,
} EN_UI_ANTENNA_TYPE;

typedef enum
{
    SOUND_MODE_MIN,
    /// sound mode is standard
    SOUND_MODE_STANDARD = SOUND_MODE_MIN,
    /// sound mode is music
    SOUND_MODE_MUSIC,
    /// sound mode is movie
    SOUND_MODE_MOVIE,
    /// sound mode is sport
    SOUND_MODE_SPORTS,
    /// sound mode is user
    SOUND_MODE_USER,
    /// sound mode is on-site1
    SOUND_MODE_ONSITE1,
    /// sound mode is on-site2
    SOUND_MODE_ONSITE2,
    SOUND_MODE_NUM
} EN_UI_SOUND_MODE;

/// Define Surround mode type
typedef enum
{
    ///Surround mode type is OFF
    E_SURROUND_MODE_OFF,
    ///Surround mode type is ON
    E_SURROUND_MODE_ON,
    ///Surround mode type is SRS TSXT
    E_SURROUND_MODE_SRS_TSXT,
#if (AU_SUPPORT_DBX == 1)
    ///Surround mode type is DBX
    E_SURROUND_MODE_DBX,
#endif
} EN_UI_SURROUND_MODE;

/** define sound ad output */
typedef enum
{
    /// sound ad output is speaker
    AD_SPEAKER,
    /// sound ad output is headphone
    AD_HEADPHONE,
    /// sound ad output is both
    AD_BOTH,
} EN_UI_SOUND_AD_OUTPUT;

#if 0
//Digital Audio Output
typedef enum
{
    UI_SPDIF_PCM = 0,
    UI_SPDIF_AUTO,
    UI_SPDIF_COUNT
}EN_UI_SPDIF_MODE;
#endif

/// HDMI_TYPE_
typedef enum
{
    MSAPI_HDMI_MODE_PCM,    //Analog
    MSAPI_HDMI_MODE_RAW,    //Digital
    MSAPI_HDMI_MODE_UNKNOWN,    //Auto
} HDMI_TYPE_;

/** define Picture MS_UI_PICTURE */
typedef struct
{
    int backlight;
    int brightness;
    long int colorTemp;
    int contrast;
    int dynamicBacklight;
    int dynamicContrast;
    int hue;
    int perfectClear;
    int saturation;
    int sharpness;
    int vibrantColour;
    int eActiveBackLight;
    int eAutoBrightnessSensor;
} MS_UI_PICTURE;

#endif  //__UISYSTEMDATATYPE_H__
