/****************************************************************************
 * Notice:      Copyright (c) Skyworth.
 *              All rights reserved.
 * Owner:      miaolibin@skyworth.com
 ****************************************************************************/

#ifndef __CPICTURESERVICE_H__
#define __CPICTURESERVICE_H__
#include "PictureManagerTypeDefine.h"


class CPictureService
{
public:
	CPictureService();
	~CPictureService();

        void PictureServiceSetBrightness(int16_t value);
        bool PictureServiceGetBrightness(int16_t * const pvalue);
        void PictureServiceSetColor(int16_t value);
        void PictureServiceSetContrast(int16_t value);
        bool PictureServiceGetContrast(int16_t * const pvalue);
        void PictureServiceSetSharpness(int16_t value);
        bool PictureServiceGetSharpness(int16_t * const pvalue);
        void PictureServiceSetTint(int16_t value);
        bool PictureServiceGetBacklight(int32_t * const pvalue);
        void PictureServiceSetBacklight(int32_t value);
        void PictureServiceSetAspectRatio(int32_t value);
        void PictureServiceSetColorTemp(PQL_COLOR_TEMP_DATA &pstColorTemp);
        void PictureServiceSetColorTempEX(PQL_COLOR_TEMPEX_DATA &pstColorTemp);
        bool PictureServiceSetNoiseReduction(int32_t nr);
        bool PictureServiceSetMpegNoiseReduction(int32_t enMNRMode);
        void PictureServiceSetDynamicContrast(bool bDynamicContrast);
        void PictureServiceSetFilm(int32_t enFilm);

};


#endif // __CPICTURESERVICE_H__

