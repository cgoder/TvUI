/****************************************************************************
 * Notice:      Copyright (c) Skyworth.
 *              All rights reserved.
 * Owner:      miaolibin@skyworth.com
 ****************************************************************************/
#include "../tvplayer/tv_common.h"
#include "mapi_types.h"

#include "CPictureService.h" //skytvmw UAPI

CPictureService::CPictureService() {

}

CPictureService::~CPictureService() {

}

void CPictureService::PictureServiceSetBrightness(int16_t value)
{

}

bool CPictureService::PictureServiceGetBrightness(int16_t * const pvalue)
{
    *pvalue = 50;
    return true;
}

void CPictureService::PictureServiceSetColor(int16_t value)
{

}  

void CPictureService::PictureServiceSetContrast(int16_t value)
{

}

bool CPictureService::PictureServiceGetContrast(int16_t * const pvalue)
{
    *pvalue = 50;
    return true;
}
void CPictureService::PictureServiceSetSharpness(int16_t value)
{

}

bool CPictureService::PictureServiceGetSharpness(int16_t * const pvalue)
{
    *pvalue = 50;
    return true;
}

void CPictureService::PictureServiceSetTint(int16_t value)
{

}

bool CPictureService::PictureServiceGetBacklight(int32_t * const pvalue)
{
    *pvalue = 50;
    return true;
}

void CPictureService::PictureServiceSetBacklight(int32_t value)
{
}

void CPictureService::PictureServiceSetAspectRatio(int32_t value)
{

}

void CPictureService::PictureServiceSetColorTemp(PQL_COLOR_TEMP_DATA &pstColorTemp)
{
    
}

void CPictureService::PictureServiceSetColorTempEX(PQL_COLOR_TEMPEX_DATA &pstColorTemp)
{
  
}

bool CPictureService::PictureServiceSetNoiseReduction(int32_t nr)
{
    return true;
}

bool CPictureService::PictureServiceSetMpegNoiseReduction(int32_t enMNRMode)
{
    return true;
}

void CPictureService::PictureServiceSetDynamicContrast(bool bDynamicContrast)
{

}
void CPictureService::PictureServiceSetFilm(int32_t enFilm)
{

}

bool input2source(unsigned int input, unsigned int& source, unsigned int& dtvRoute) {
	// source = MAPI_INPUT_SOURCE_DTV;
	// dtvRoute = E_ROUTE_NONE;

	switch (input) {
	case SKYTV_INPUT_SOURCE_ATV:
		source = MAPI_INPUT_SOURCE_ATV;
		break;
	case SKYTV_INPUT_SOURCE_DVBS:
		source = MAPI_INPUT_SOURCE_DTV;
		break;
	case SKYTV_INPUT_SOURCE_DVBS2:
		source = MAPI_INPUT_SOURCE_DTV;
		break;
	case SKYTV_INPUT_SOURCE_DVBT:
		source = MAPI_INPUT_SOURCE_DTV;
		break;
	case SKYTV_INPUT_SOURCE_DVBT2:
		source = MAPI_INPUT_SOURCE_DTV;
		break;
	case SKYTV_INPUT_SOURCE_DTMB:
		source = MAPI_INPUT_SOURCE_DTV;
		break;
	case SKYTV_INPUT_SOURCE_ATSC:
		source = MAPI_INPUT_SOURCE_DTV;
		break;
	case SKYTV_INPUT_SOURCE_ISDB:
		source = MAPI_INPUT_SOURCE_DTV;
		break;
	case SKYTV_INPUT_SOURCE_CVBS:
	case SKYTV_INPUT_SOURCE_CVBS2:
	case SKYTV_INPUT_SOURCE_CVBS3:
	case SKYTV_INPUT_SOURCE_CVBS4:
		source = MAPI_INPUT_SOURCE_CVBS + (input - SKYTV_INPUT_SOURCE_CVBS);
		break;
	case SKYTV_INPUT_SOURCE_YPBPR:
	case SKYTV_INPUT_SOURCE_YPBPR2:
	case SKYTV_INPUT_SOURCE_YPBPR3:
	case SKYTV_INPUT_SOURCE_YPBPR4:
		source = MAPI_INPUT_SOURCE_YPBPR + (input - SKYTV_INPUT_SOURCE_YPBPR);
		break;
	case SKYTV_INPUT_SOURCE_SVIDEO:
	case SKYTV_INPUT_SOURCE_SVIDEO2:
	case SKYTV_INPUT_SOURCE_SVIDEO3:
	case SKYTV_INPUT_SOURCE_SVIDEO4:
		source = MAPI_INPUT_SOURCE_SVIDEO + (input - SKYTV_INPUT_SOURCE_SVIDEO);
		break;
	case SKYTV_INPUT_SOURCE_DVI:
	case SKYTV_INPUT_SOURCE_DVI2:
	case SKYTV_INPUT_SOURCE_DVI3:
	case SKYTV_INPUT_SOURCE_DVI4:
		source =  MAPI_INPUT_SOURCE_DVI + (input - SKYTV_INPUT_SOURCE_DVI);
		break;
	case SKYTV_INPUT_SOURCE_VGA:
		source = MAPI_INPUT_SOURCE_VGA;
		break;
	case SKYTV_INPUT_SOURCE_HDMI1:
	case SKYTV_INPUT_SOURCE_HDMI2:
	case SKYTV_INPUT_SOURCE_HDMI3:
	case SKYTV_INPUT_SOURCE_HDMI4:
		source = MAPI_INPUT_SOURCE_HDMI + (input - SKYTV_INPUT_SOURCE_HDMI1);
		break;
	case SKYTV_INPUT_SOURCE_STORAGE:
	case SKYTV_INPUT_SOURCE_STORAGE2:
	case SKYTV_INPUT_SOURCE_STORAGE3:
	case SKYTV_INPUT_SOURCE_STORAGE4:
		source = MAPI_INPUT_SOURCE_STORAGE;
		break;
	case SKYTV_INPUT_SOURCE_DVBC:
	case SKYTV_INPUT_SOURCE_DVBC2:
		source = MAPI_INPUT_SOURCE_DTV;
		break;
	default:
		return false;
	}
	return true;
}


