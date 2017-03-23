/****************************************************************************
 * Notice:      Copyright (c) Skyworth.
 *              All rights reserved.
 * Owner:      miaolibin@skyworth.com
 ****************************************************************************/

#include <string>
#ifdef WIN32
#include "../tvplayer/tv_common.h"
#else
#include "tv_common.h"
#endif
#include "DatabaseManagerType.h"
#include "mapi_types.h"
#include "UiSystemDataBase.h"
#include "PictureSetting.h"
#include "mapi_video_datatype.h"

extern bool input2source(unsigned int input, unsigned int& source, unsigned int& dtvRoute);

#define UI_PICTURE_DBG     printf

PictureSetting *PictureSetting::m_pInstance = NULL;

static MAPI_INPUT_SOURCE_TYPE GetMapiSourceType(void) 
{
    bool ret = false;
    uint32_t MapiSrcType = MAPI_INPUT_SOURCE_DTV;
    uint32_t temp = 0;
    SKYTV_INPUT_SOURCE_TYPE enUiSrcType = skyTvMw::getInstance()->getInputSource();

    ret = input2source(enUiSrcType, MapiSrcType, temp);
    if(ret == false)
    {
        printf("error!!![FUNC:%s]\r\n", __FUNCTION__);
        MapiSrcType = MAPI_INPUT_SOURCE_DTV;
    }
    UI_PICTURE_DBG("[FUNC:%s] enUiSrcType=%d, MapiSrcType=%d\r\n", __FUNCTION__, enUiSrcType, MapiSrcType);

    return (MAPI_INPUT_SOURCE_TYPE)MapiSrcType;
}

PictureSetting::PictureSetting()
{
    m_pstUiVideoData = NULL;
    bool ret = PictureSetting::PsSettingDataInit(EN_PS_DT_VIDEO, NULL);
    if(ret == false)
    {
        printf("error!!![FUNC:%s]\r\n", __FUNCTION__);
    }
}

PictureSetting::~PictureSetting()
{

}

PictureSetting* PictureSetting::getInstance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new PictureSetting();
    }
    return m_pInstance;
}

void PictureSetting::destroyInstance(void)
{
    if(m_pInstance != NULL)
    {
        m_pInstance->PsSaveSettingDataAll();
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

void PictureSetting::PictureSetPicMode(EN_UI_PICTURE_MODE enPicMode)
{    

    m_pstUiVideoData->picture = enPicMode;

    PictureSetContrast(m_pstUiVideoData->astPicture[enPicMode].contrast);
    PictureSetBrightness(m_pstUiVideoData->astPicture[enPicMode].brightness);
    PictureSetColor(m_pstUiVideoData->astPicture[enPicMode].saturation);//color
    PictureSetTint(m_pstUiVideoData->astPicture[enPicMode].hue);//tint
    PictureSetSharpness(m_pstUiVideoData->astPicture[enPicMode].sharpness);
    PictureSetBacklight(m_pstUiVideoData->astPicture[enPicMode].backlight);
}

bool PictureSetting::PictureGetPicMode(EN_UI_PICTURE_MODE *pPicMode, MS_UI_PICTURE *pstUiPicture)
{
    
    if(pPicMode != NULL)
    {
        *pPicMode = (EN_UI_PICTURE_MODE) m_pstUiVideoData->picture;
    }
    if(pstUiPicture != NULL)
    {
        memcpy(pstUiPicture, &(m_pstUiVideoData->astPicture[m_pstUiVideoData->picture]), sizeof(MS_UI_PICTURE));
    }
    return true;
}
void PictureSetting::PictureSetBrightness(int16_t value)
{
    PictureSetting::PsSetPictureItem(value, EN_PS_BRIGHTNESS);
}

bool PictureSetting::PictureGetBrightness(int16_t * const pvalue)
{
    *pvalue = m_pstUiVideoData->astPicture[m_pstUiVideoData->picture].brightness;
    return true;
}

void PictureSetting::PictureSetColor(int16_t value)//saturation
{
    PictureSetting::PsSetPictureItem(value, EN_PS_SATURATION);
}  

bool PictureSetting::PictureGetColor(int16_t * const pvalue)    //saturation
{
    *pvalue = m_pstUiVideoData->astPicture[m_pstUiVideoData->picture].saturation;
    return true;
}

void PictureSetting::PictureSetContrast(int16_t value)
{
    PictureSetting::PsSetPictureItem(value, EN_PS_CONTRAST);
}

bool PictureSetting::PictureGetContrast(int16_t * const pvalue)
{
    *pvalue = m_pstUiVideoData->astPicture[m_pstUiVideoData->picture].contrast;
    return true;
}
void PictureSetting::PictureSetSharpness(int16_t value)
{
    PictureSetting::PsSetPictureItem(value, EN_PS_SHARPNESS);
}

bool PictureSetting::PictureGetSharpness(int16_t * const pvalue)
{
    *pvalue = m_pstUiVideoData->astPicture[m_pstUiVideoData->picture].sharpness;
    return true;    
}

void PictureSetting::PictureSetTint(int16_t value)  //hue
{
    PictureSetting::PsSetPictureItem(value, EN_PS_HUE);
}

bool PictureSetting::PictureGetTint(int16_t * const pvalue)//hue
{
    *pvalue = m_pstUiVideoData->astPicture[m_pstUiVideoData->picture].hue;
    return true;
}

bool PictureSetting::PictureGetBacklight(int16_t * const pvalue)
{
    *pvalue = m_pstUiVideoData->astPicture[m_pstUiVideoData->picture].backlight;
    return true;
}

void PictureSetting::PictureSetBacklight(int16_t value)
{
    PictureSetting::PsSetPictureItem(value, EN_PS_BACKLIGHT);
}

void PictureSetting::PictureSetAspectRatio(int32_t value)
{
    mapi_video_datatype::MAPI_VIDEO_ARC_Type MapiVideoArcType = mapi_video_datatype::E_AR_AUTO;
    
    //convert ui arc type to mapi arc type 
    switch(value)
    {
        case PIC_ASPECT_RATIO_AUTO:
            MapiVideoArcType = mapi_video_datatype::E_AR_AUTO;
            break;
        case PIC_ASPECT_RATIO_4_3:
            MapiVideoArcType = mapi_video_datatype::E_AR_4x3;
            break;
        case PIC_ASPECT_RATIO_16_9:
            MapiVideoArcType = mapi_video_datatype::E_AR_16x9;
            break;
        case PIC_ASPECT_RATIO_ZOOM1:
            MapiVideoArcType = mapi_video_datatype::E_AR_Zoom1;
            break;
        case PIC_ASPECT_RATIO_ZOOM2:
            MapiVideoArcType = mapi_video_datatype::E_AR_Zoom2;
            break;
        case PIC_ASPECT_RATIO_JUST_SCAN:
            MapiVideoArcType = mapi_video_datatype::E_AR_JustScan;
            break;
        case PIC_ASPECT_RATIO_PANORAMA:
            MapiVideoArcType = mapi_video_datatype::E_AR_Panorama;
            break;
        case PIC_ASPECT_RATIO_POINT_TO_POINT:
            MapiVideoArcType = mapi_video_datatype::E_AR_DotByDot;
            break;
        default:
            printf("error!!![FUNC:%s]\r\n", __FUNCTION__);
            return;
    }
    
    switch(m_pstUiVideoData->picture)
    {
        case PICTURE_GAME:
            m_pstUiVideoData->enGameModeARCType = MapiVideoArcType;
            break;
        case PICTURE_AUTO:
            m_pstUiVideoData->enAutoModeARCType = MapiVideoArcType;
            break;
        case PICTURE_PC:
            m_pstUiVideoData->enPcModeARCType = MapiVideoArcType;
            break;
        default:
            m_pstUiVideoData->arcType = MapiVideoArcType;
            break;
    }
    PictureSetting::PictureServiceSetAspectRatio(MapiVideoArcType);
}

bool PictureSetting::PictureGetAspectRatio(int32_t * const pvalue)
{
    mapi_video_datatype::MAPI_VIDEO_ARC_Type MapiVideoArcType = mapi_video_datatype::E_AR_AUTO;

    switch(m_pstUiVideoData->picture)
    {
        case PICTURE_GAME:
            MapiVideoArcType = (mapi_video_datatype::MAPI_VIDEO_ARC_Type)m_pstUiVideoData->enGameModeARCType;
            break;
        case PICTURE_AUTO:
            MapiVideoArcType= (mapi_video_datatype::MAPI_VIDEO_ARC_Type)m_pstUiVideoData->enAutoModeARCType;
            break;
        case PICTURE_PC:
            MapiVideoArcType = (mapi_video_datatype::MAPI_VIDEO_ARC_Type)m_pstUiVideoData->enPcModeARCType;
            break;
        default:
            MapiVideoArcType = (mapi_video_datatype::MAPI_VIDEO_ARC_Type)m_pstUiVideoData->arcType;
            break;
    }
    
    //convert mapi arc type to ui arc type
    switch(MapiVideoArcType)
    {
        case mapi_video_datatype::E_AR_DEFAULT:
            /* fall through */
        case mapi_video_datatype::E_AR_AUTO:
            *pvalue = PIC_ASPECT_RATIO_AUTO;
            break;
        case mapi_video_datatype::E_AR_4x3:
            *pvalue = PIC_ASPECT_RATIO_4_3;
            break;
        case mapi_video_datatype::E_AR_16x9:
            *pvalue = PIC_ASPECT_RATIO_16_9;
            break;
        case mapi_video_datatype::E_AR_Zoom1:
            *pvalue = PIC_ASPECT_RATIO_ZOOM1;
            break;
        case mapi_video_datatype::E_AR_Zoom2:
            *pvalue = PIC_ASPECT_RATIO_ZOOM2;
            break;
        case mapi_video_datatype::E_AR_JustScan:
            *pvalue = PIC_ASPECT_RATIO_JUST_SCAN;
            break;
        case mapi_video_datatype::E_AR_Panorama:
            *pvalue = PIC_ASPECT_RATIO_PANORAMA;
            break;
        case mapi_video_datatype::E_AR_DotByDot:
            *pvalue = PIC_ASPECT_RATIO_POINT_TO_POINT;
            break;
        default:
            printf("error!!![FUNC:%s]\r\n", __FUNCTION__);
            return false;
    }

    return true;
}

/***************
FUNCTION NAME:PictureSetColorTempMode
***************/
void PictureSetting::PictureSetColorTempMode(EN_UI_COLOR_TEMP enColorTempMode)
{
    PQL_COLOR_TEMPEX_DATA  stColorTempExUser_tmp = {0};
    MAPI_INPUT_SOURCE_TYPE enMapiSrcType = MAPI_INPUT_SOURCE_DTV;

    enMapiSrcType = GetMapiSourceType();
       
    m_pstUiVideoData->astPicture[m_pstUiVideoData->picture].colorTemp = enColorTempMode;
    /*get ColorTemp mode param*/
    UI_System_Database::GetUiSystemDbInstance()->GetColorTempEx(&stColorTempExUser_tmp, &enColorTempMode, enMapiSrcType);

    PictureSetting::PictureServiceSetColorTempEX(stColorTempExUser_tmp);
}

bool PictureSetting::PictureGetColorTempMode(EN_UI_COLOR_TEMP *penColorTempMode)
{

    if(penColorTempMode == NULL)
        return false;
    
    *penColorTempMode = (EN_UI_COLOR_TEMP)m_pstUiVideoData->astPicture[m_pstUiVideoData->picture].colorTemp;

    /*if(pstUiColorTempData != NULL)
    {
        MAPI_INPUT_SOURCE_TYPE enMapiSrcType = MAPI_INPUT_SOURCE_DTV;
        PQL_COLOR_TEMPEX_DATA  stColorTempExUser_tmp;
        uint32_t CurrentMode = COLOR_TEMP_NATURE;

        enMapiSrcType = GetMapiSourceType();
        CurrentMode = *penColorTempMode;
        UI_System_Database::GetUiSystemDbInstance()->GetColorTempEx(&stColorTempExUser_tmp, &CurrentMode, enMapiSrcType);
        memcpy(pstUiColorTempData, &stColorTempExUser_tmp, sizeof(PQL_COLOR_TEMPEX_DATA));
    }*/
    return true;
}

bool PictureSetting::PictureSetDynamicNoiseReduction(EN_UI_PIC_NR enPicNr)
{
    bool ret = false;
    EN_UI_COLOR_TEMP enColorTemp = COLOR_TEMP_COOL;

    enColorTemp = (EN_UI_COLOR_TEMP)m_pstUiVideoData->astPicture[m_pstUiVideoData->picture].colorTemp;
    m_pstUiVideoData->noiseReductionMode[enColorTemp].eNR = enPicNr;

    ret = PictureSetting::PictureServiceSetNoiseReduction(enPicNr);
    return ret;
}
bool PictureSetting::PictureGetDynamicNoiseReduction(EN_UI_PIC_NR *penPicNr)
{
    EN_UI_COLOR_TEMP enColorTemp = COLOR_TEMP_COOL;
    
    if(penPicNr == NULL)
        return false;
    
    enColorTemp = (EN_UI_COLOR_TEMP)m_pstUiVideoData->astPicture[m_pstUiVideoData->picture].colorTemp;

    *penPicNr = (EN_UI_PIC_NR)m_pstUiVideoData->noiseReductionMode[enColorTemp].eNR;// = enPicNr;
    return true;
}

bool PictureSetting::PictureSetMpegNoiseReduction(EN_UI_PIC_MPEG_NR enMpegPicNr)
{
    bool ret = false;
    EN_UI_COLOR_TEMP enColorTemp = COLOR_TEMP_COOL;

    enColorTemp = (EN_UI_COLOR_TEMP)m_pstUiVideoData->astPicture[m_pstUiVideoData->picture].colorTemp;
    m_pstUiVideoData->noiseReductionMode[enColorTemp].eMPEG_NR= enMpegPicNr;

    ret = PictureSetting::PictureServiceSetMpegNoiseReduction(enMpegPicNr);
    return ret;
}

bool PictureSetting::PictureGetMpegNoiseReduction(EN_UI_PIC_MPEG_NR *penMpegPicNr)
{
    EN_UI_COLOR_TEMP enColorTemp = COLOR_TEMP_COOL;
    
    if(penMpegPicNr == NULL)
        return false;
    
    enColorTemp = (EN_UI_COLOR_TEMP)m_pstUiVideoData->astPicture[m_pstUiVideoData->picture].colorTemp;

    *penMpegPicNr = (EN_UI_PIC_MPEG_NR)m_pstUiVideoData->noiseReductionMode[enColorTemp].eMPEG_NR;
    return true;
}

void PictureSetting::PictureSetDynamicContrast(EN_UI_SETTING_ON_OFF bDynamicContrast)
{
    bool ret = PictureSetting::PsSettingDataInit(EN_PS_DT_VIDEO, NULL);

    PictureSetting::PictureServiceSetDynamicContrast(bDynamicContrast);
    if(ret == false)
        return;
    m_pstUiVideoData->dynamicContrast = bDynamicContrast;
}

bool PictureSetting::PictureGetDynamicContrast(EN_UI_SETTING_ON_OFF *pbDynamicContrast)
{

    *pbDynamicContrast = (EN_UI_SETTING_ON_OFF)m_pstUiVideoData->dynamicContrast;
    
    return true;        
}
void PictureSetting::PictureSetFilmMode(EN_UI_SETTING_ON_OFF bFilmMode)
{
    PictureSetting::PictureServiceSetFilm(bFilmMode);
    m_pstUiVideoData->filmMode = bFilmMode;
}

bool PictureSetting::PictureGeFilmMode(EN_UI_SETTING_ON_OFF *pbFilmMode)
{
    *pbFilmMode = (EN_UI_SETTING_ON_OFF)m_pstUiVideoData->filmMode;
    return true;
}

void PictureSetting::PictureSettingReset(void)
{
    uint8_t i =0;
    MS_UI_VIDEO stUiVideoData = {0};
    MAPI_INPUT_SOURCE_TYPE enMapiSrcType = MAPI_INPUT_SOURCE_DTV;

    enMapiSrcType = GetMapiSourceType();
    UI_System_Database::GetUiSystemDbInstance()->GetFactoryVideoSetting(&stUiVideoData, &enMapiSrcType);

    /*picture mode and color Temp. data*/
    m_pstUiVideoData->picture = stUiVideoData.picture;
    for(i=PICTURE_MIN; i<PICTURE_NUMS; i++)
    {
        memcpy(&(m_pstUiVideoData->astPicture[i]), 
                        &(stUiVideoData.astPicture[i]), 
                        sizeof(MS_UI_PICTURE));
    }
    
    /*Aspect Ratio*/
    m_pstUiVideoData->enGameModeARCType = stUiVideoData.enGameModeARCType;
    m_pstUiVideoData->enAutoModeARCType = stUiVideoData.enAutoModeARCType;
    m_pstUiVideoData->enPcModeARCType = stUiVideoData.enPcModeARCType;
    m_pstUiVideoData->arcType = stUiVideoData.arcType;

    /*Noise Reduction data*/
    for(i=E_COLOR_TEMP_MIN; i<E_COLOR_TEMP_NUM; i++)
    {
            m_pstUiVideoData->noiseReductionMode[i].eNR = stUiVideoData.noiseReductionMode[i].eNR;
            m_pstUiVideoData->noiseReductionMode[i].eMPEG_NR = stUiVideoData.noiseReductionMode[i].eMPEG_NR;
    }
    
    /*Dynamic Contrast data*/
    m_pstUiVideoData->dynamicContrast = stUiVideoData.dynamicContrast;

    /*filmMode data*/
    m_pstUiVideoData->filmMode = stUiVideoData.filmMode;

    //PsSaveSettingDataAll();
}

/**** private functions*****/
void PictureSetting::PsSetPictureItem(int16_t value, EN_UI_PS_ITEM enItem)
{
    EN_UI_PICTURE_MODE PictureMode = PICTURE_USER;
    
    PictureMode = (EN_UI_PICTURE_MODE) m_pstUiVideoData->picture;

    switch(enItem)
    {
        case EN_PS_BRIGHTNESS:
            m_pstUiVideoData->astPicture[PictureMode].brightness = (int)value;
            PictureSetting::PictureServiceSetBrightness(value);            
            break;
        case EN_PS_CONTRAST:
            m_pstUiVideoData->astPicture[PictureMode].contrast = (int)value;
            PictureSetting::PictureServiceSetContrast(value);            
            break;
        case EN_PS_SATURATION: //color
            m_pstUiVideoData->astPicture[PictureMode].saturation = (int)value;
            PictureSetting::PictureServiceSetColor(value);        
            break;
        case EN_PS_SHARPNESS:
            m_pstUiVideoData->astPicture[PictureMode].sharpness = (int)value;
            PictureSetting::PictureServiceSetSharpness(value);
            break;
        case EN_PS_HUE: //tint
            m_pstUiVideoData->astPicture[PictureMode].hue = (int)value;
            PictureSetting::PictureServiceSetTint(value);
            break;
        case EN_PS_BACKLIGHT:
            m_pstUiVideoData->astPicture[PictureMode].backlight = (int)value;
            PictureSetting::PictureServiceSetBacklight(value);
            break;
        default:
            return;
    }

}

bool PictureSetting::PsSettingDataInit(EN_UI_DATA_TYPES DataType, void *pstSettingData)
{
    MAPI_INPUT_SOURCE_TYPE enMapiSrcType = MAPI_INPUT_SOURCE_DTV;

    switch(DataType)
    {
        case EN_PS_DT_VIDEO:
            if(m_pstUiVideoData == NULL)
            {
                enMapiSrcType = GetMapiSourceType();
                m_pstUiVideoData = new MS_UI_VIDEO;
                if(m_pstUiVideoData == NULL)
                    return false;
                UI_System_Database::GetUiSystemDbInstance()->GetVideoSetting(m_pstUiVideoData, (MAPI_INPUT_SOURCE_TYPE*)&enMapiSrcType);
            }
            if(pstSettingData != NULL)
            {
                memcpy(pstSettingData, m_pstUiVideoData, sizeof(MS_UI_VIDEO));
            }
            break;
        default:
            break;
    }
    return true;
}

void PictureSetting::PsSaveSettingDataAll(void)
{
    MAPI_INPUT_SOURCE_TYPE enMapiSrcType = MAPI_INPUT_SOURCE_DTV;
    enMapiSrcType = GetMapiSourceType();
    if(m_pstUiVideoData != NULL)
    {
        UI_System_Database::GetUiSystemDbInstance()->SetVideoSetting(m_pstUiVideoData, (MAPI_INPUT_SOURCE_TYPE*)&enMapiSrcType);
        delete m_pstUiVideoData;
        m_pstUiVideoData = NULL;
    }
}

