/****************************************************************************
 * Notice:      Copyright (c) Skyworth.
 *              All rights reserved.
 * Owner:      miaolibin@skyworth.com
 ****************************************************************************/

#ifndef __PICTURE_SETTING_H__
#define __PICTURE_SETTING_H__
#include "CPictureService.h"
#include "UiSystemDataType.h"
#include "UiSystemDataBase.h"

typedef enum
{
    EN_PS_BRIGHTNESS,
    EN_PS_CONTRAST,
    EN_PS_SATURATION,
    EN_PS_SHARPNESS,
    EN_PS_HUE,
    EN_PS_BACKLIGHT,
}EN_UI_PS_ITEM;

typedef enum
{
    EN_PS_DT_VIDEO,
}EN_UI_DATA_TYPES;

class PictureSetting : public CPictureService
{
public:
        ~PictureSetting();
        static PictureSetting* getInstance(void);
        static void destroyInstance(void);        
        void PictureSetPicMode(EN_UI_PICTURE_MODE enPicMode);
        bool PictureGetPicMode(EN_UI_PICTURE_MODE *pPicMode, MS_UI_PICTURE *pstUiPicture);        
        void PictureSetBrightness(int16_t value);
        bool PictureGetBrightness(int16_t * const pvalue);
        void PictureSetColor(int16_t value);
        bool PictureGetColor(int16_t * const pvalue);
        void PictureSetContrast(int16_t value);
        bool PictureGetContrast(int16_t * const pvalue);
        void PictureSetSharpness(int16_t value);
        bool PictureGetSharpness(int16_t * const pvalue);
        void PictureSetTint(int16_t value);
        bool PictureGetTint(int16_t * const pvalue);
        void PictureSetBacklight(int16_t value);
        bool PictureGetBacklight(int16_t * const pvalue);
        void PictureSetAspectRatio(int32_t value);
        bool PictureGetAspectRatio(int32_t * const pvalue);
        void PictureSetColorTempMode(EN_UI_COLOR_TEMP enColorTempMode);
        bool PictureGetColorTempMode(EN_UI_COLOR_TEMP *penColorTempMode);
        bool PictureSetDynamicNoiseReduction(EN_UI_PIC_NR enPicNr);
        bool PictureGetDynamicNoiseReduction(EN_UI_PIC_NR *penPicNr);
        bool PictureSetMpegNoiseReduction(EN_UI_PIC_MPEG_NR enMpegPicNr);
        bool PictureGetMpegNoiseReduction(EN_UI_PIC_MPEG_NR *penMpegPicNr);
        void PictureSetDynamicContrast(EN_UI_SETTING_ON_OFF bDynamicContrast);
        bool PictureGetDynamicContrast(EN_UI_SETTING_ON_OFF *pbDynamicContrast);
        void PictureSetFilmMode(EN_UI_SETTING_ON_OFF bFilmMode);
        bool PictureGeFilmMode(EN_UI_SETTING_ON_OFF *pbFilmMode);
        void PictureSettingReset(void);        
private:
        PictureSetting();
        void PsSetPictureItem(int16_t value, EN_UI_PS_ITEM enItem);
        bool PsSettingDataInit(EN_UI_DATA_TYPES DataType, void *pstSettingData);
        void PsSaveSettingDataAll(void);
        MS_UI_VIDEO *m_pstUiVideoData;
        static PictureSetting *m_pInstance;

};

#endif // __PICTURE_SETTING_H__

