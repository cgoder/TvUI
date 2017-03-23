

#include "PictureMenuExecutor.h"

#include "PictureMenuItemInfo.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "../../setting/UiSystemDataType.h"
#include "../../setting/PictureSetting.h"

USING_NS_CC;

//PictureSetting pictureSetting;
EN_UI_PICTURE_MODE pPicMode;
MS_UI_PICTURE pstUiPicture;


void PictureMenuExecutor::PictureModeRefresh(void)
{	
	PictureSetting::getInstance()->PictureGetPicMode(&pPicMode, &pstUiPicture);
	unsigned int picture_mode_total = LengthofArray(m_picture_mode_map);
	for (unsigned int i = 0; i < picture_mode_total; i++)
	{
		if (m_picture_mode_map[i].ui_picture_mode == pPicMode)
			m_picture_mode_refresh["ID_SET_PIC_MODE"] = m_picture_mode_map[i].selectMode;
	};

	EN_UI_COLOR_TEMP penColorTempMode;
	PictureSetting::getInstance()->PictureGetColorTempMode(&penColorTempMode);
	unsigned int colortemp_mode_total = LengthofArray(m_colortemp_mode_map);
	for (unsigned int i = 0; i < colortemp_mode_total; i++)
	{
		if (m_colortemp_mode_map[i].ui_colortemp_mode == penColorTempMode)
			m_picture_mode_refresh["ID_SET_COLOR_TEMP"] = m_colortemp_mode_map[i].selectMode;
	};
	
	//EN_UI_PIC_ASPECT_RATIO picAspectRatio;
	signed int picAspectRatio;
	PictureSetting::getInstance()->PictureGetAspectRatio(&picAspectRatio);
	unsigned int picaspectratio_mode_total = LengthofArray(m_aspect_ratio_map);
	for (unsigned int i = 0; i < picaspectratio_mode_total; i++)
	{
		if (m_aspect_ratio_map[i].ui_aspect_ratio_mode == picAspectRatio)
			m_picture_mode_refresh["ID_SET_ASPECT"] = m_aspect_ratio_map[i].selectMode;
	};

	EN_UI_PIC_NR penPicNr;
	PictureSetting::getInstance()->PictureGetDynamicNoiseReduction(&penPicNr);
	unsigned int enpicnr_mode_total = LengthofArray(m_enpicnr_mode_map);
	for (unsigned int i = 0; i < enpicnr_mode_total; i++)
	{
		if (m_enpicnr_mode_map[i].ui_enpicnr_mode == penPicNr)
			m_picture_mode_refresh["ID_SET_DYNAMIC_NOISE"] = m_enpicnr_mode_map[i].selectMode;
	};

	EN_UI_PIC_MPEG_NR enMpegPicNr;
	PictureSetting::getInstance()->PictureGetMpegNoiseReduction(&enMpegPicNr);
	unsigned int enpicmpegnr_mode_total = LengthofArray(m_enpicmpegnr_mode_map);
	for (unsigned int i = 0; i < enpicmpegnr_mode_total; i++)
	{
		if (m_enpicmpegnr_mode_map[i].ui_enpicmpegnr_mode == enMpegPicNr)
			m_picture_mode_refresh["ID_SET_MPEG_NOISE"] = m_enpicmpegnr_mode_map[i].selectMode;
	};
	
	EN_UI_SETTING_ON_OFF bDynamicContrast;
	PictureSetting::getInstance()->PictureGetDynamicContrast(&bDynamicContrast);
	if(bDynamicContrast == UI_SETTING_ON)
		m_picture_mode_refresh["ID_SET_DYNAMIC_CONTRAST"] = "On";
	else
		m_picture_mode_refresh["ID_SET_DYNAMIC_CONTRAST"] = "Off";
	
	EN_UI_SETTING_ON_OFF bFilmMode;
	PictureSetting::getInstance()->PictureGeFilmMode(&bFilmMode);
	if(bFilmMode == UI_SETTING_ON)
		m_picture_mode_refresh["ID_SET_FILM_MODE"] = "On";
	else
		m_picture_mode_refresh["ID_SET_FILM_MODE"] = "Off";
	
}

void PictureMenuExecutor::PictureOptionRefresh(void)
{	
#if 1
	PictureSetting::getInstance()->PictureGetPicMode(&pPicMode, &pstUiPicture);
	m_ms_ui_picture["ID_SET_BACKLIGHT"] = pstUiPicture.backlight;
	m_ms_ui_picture["ID_SET_CONTRAST"] = pstUiPicture.contrast;
	m_ms_ui_picture["ID_SET_BRIGHTNESS"] = pstUiPicture.brightness;
	m_ms_ui_picture["ID_SET_COLOR"] = pstUiPicture.saturation;
	m_ms_ui_picture["ID_SET_SHARPNESS"] = pstUiPicture.sharpness;

#else
	PictureSetting pictureSetting;
	int16_t backlight, brightness, contrast, color, sharpness;

	pictureSetting.PictureGetBrightness(&backlight);
	if(backlight < 0 || backlight > 100) backlight = 50;
	m_ms_ui_picture["ID_SET_BACKLIGHT"] = backlight;
	pictureSetting.PictureGetContrast(&contrast);
	if(contrast < 0 || contrast > 100) contrast = 50;
	m_ms_ui_picture["ID_SET_CONTRAST"] = contrast;
	pictureSetting.PictureGetBrightness(&brightness);
	if(brightness < 0 || brightness > 100) brightness = 50;
	m_ms_ui_picture["ID_SET_BRIGHTNESS"] = brightness;
	pictureSetting.PictureGetColor(&color);
	if(color < 0 || color > 100) color = 50;
	m_ms_ui_picture["ID_SET_COLOR"] = color;
	pictureSetting.PictureGetSharpness(&sharpness);
	if(sharpness < 0 || sharpness > 100) sharpness = 50;
	m_ms_ui_picture["ID_SET_SHARPNESS"] = sharpness;
#endif	
}

class PictureMenuExecutor::PriveteImpl
{
public:
	//typedef void (cocos2d::Ref::*Click_CallFun)(cocos2d::Node* node);
	typedef int(PriveteImpl::*MenuItem_Function)(std::string& option);
	typedef std::map<std::string, MenuItem_Function> MenuItem_FunctionMap;
	typedef std::map<std::string, MenuItem_Function>::const_iterator MenuItem_FunctionMapIter;

	MenuItem_FunctionMap m_MenuItem_FunctionMap;

	PriveteImpl()
	{
		m_MenuItem_FunctionMap["ID_SET_PIC_MODE"] = &PriveteImpl::Picture_Mode; //"Picture Mode"
		m_MenuItem_FunctionMap["ID_SET_BACKLIGHT"] = &PriveteImpl::Backlight; //"Backlight"
		m_MenuItem_FunctionMap["ID_SET_CONTRAST"] = &PriveteImpl::Contrast; //"Contrast"
		m_MenuItem_FunctionMap["ID_SET_BRIGHTNESS"] = &PriveteImpl::Brightness; //"Brightness"
		m_MenuItem_FunctionMap["ID_SET_COLOR"] = &PriveteImpl::Color; //"Color"
		m_MenuItem_FunctionMap["ID_SET_SHARPNESS"] = &PriveteImpl::Sharpness; //"Sharpness"

		m_MenuItem_FunctionMap["ID_SET_COLOR_TEMP"] = &PriveteImpl::Color_Temperature; //"Color Temperature"
		m_MenuItem_FunctionMap["ID_SET_DYNAMIC_NOISE"] = &PriveteImpl::Dynamic_Noise_Reduction; //"Dynamic Noise Reduction"
		m_MenuItem_FunctionMap["ID_SET_MPEG_NOISE"] = &PriveteImpl::MPEG_Noise_Reduction; //"MPEG Noise Reduction"
		
			
		m_MenuItem_FunctionMap["ID_SET_ASPECT"] = &PriveteImpl::Aspect_Ratio; //"Aspect Ratio"
		m_MenuItem_FunctionMap["ID_SET_DYNAMIC_CONTRAST"] = &PriveteImpl::Dynamic; //"Dynamic"
		m_MenuItem_FunctionMap["ID_SET_LIGHT_SENSOR"] = NULL; //"Light Sensor"
		m_MenuItem_FunctionMap["ID_SET_PICTURE_SENSOR"] = NULL; //"icture Sensor"
		m_MenuItem_FunctionMap["ID_SET_FILM_MODE"] = &PriveteImpl::Film_Mode; //"Film Mode"
		m_MenuItem_FunctionMap["ID_SET_PICTURE_RESET"] = &PriveteImpl::Picture_Reset; //"Picture Reset"

	}

	~PriveteImpl()
	{
		PictureSetting::destroyInstance();
	}

public:

	int Execute(string& menuname, string& option)
	{
		MenuItem_FunctionMapIter itor = m_MenuItem_FunctionMap.find(menuname);
		if (itor != m_MenuItem_FunctionMap.end() && itor->second != NULL)
			return (this->*(itor->second))(option);
		return 0;
	}

	
	int Picture_Mode(std::string& option)
	{
		EN_UI_PICTURE_MODE enPicMode;

		unsigned int picture_mode_total = LengthofArray(m_picture_mode_map);
		
		for (unsigned int i = 0; i < picture_mode_total; i++)
		{
			if (m_picture_mode_map[i].selectMode == option)
			{
				enPicMode = m_picture_mode_map[i].ui_picture_mode;
				break;
			}
		};
		
		PictureSetting::getInstance()->PictureSetPicMode(enPicMode);
		return 0;
	}
	
	int Backlight(std::string& option)
	{
		PictureSetting::getInstance()->PictureSetBacklight(stoi(option));
		return 0;
	}
	
	int Contrast(std::string& option)
	{
		PictureSetting::getInstance()->PictureSetContrast(stoi(option));
		return 0;
	}
	
	int Brightness(std::string& option)
	{

		//PictureSetting pictureSetting;
		//pictureSetting.PictureSetBrightness(atoi(option));
		PictureSetting::getInstance()->PictureSetBrightness(stoi(option));
		return 0;
	}

	int Color(std::string& option)
	{
		PictureSetting::getInstance()->PictureSetColor(stoi(option));
		return 0;
	}
	
	int Sharpness(std::string& option)
	{
		PictureSetting::getInstance()->PictureSetSharpness(stoi(option));
		return 0;
	}
	
	int Color_Temperature(std::string& option)
	{
		EN_UI_COLOR_TEMP enColorTempMode;

		unsigned int colortemp_mode_total = LengthofArray(m_colortemp_mode_map);
		
		for (unsigned int i = 0; i < colortemp_mode_total; i++)
		{
			if (m_colortemp_mode_map[i].selectMode == option)
			{
				enColorTempMode = m_colortemp_mode_map[i].ui_colortemp_mode;
				break;
			}
		}
		
		PictureSetting::getInstance()->PictureSetColorTempMode(enColorTempMode);
		return 0;
	}
	
	int Dynamic_Noise_Reduction(std::string& option)
	{
		EN_UI_PIC_NR enPicNr;
		
		unsigned int enpicnr_mode_total = LengthofArray(m_enpicnr_mode_map);
		
		for (unsigned int i = 0; i < enpicnr_mode_total; i++)
		{
			if (m_enpicnr_mode_map[i].selectMode == option)
			{
				enPicNr = m_enpicnr_mode_map[i].ui_enpicnr_mode;
				break;
			}
		}
		PictureSetting::getInstance()->PictureSetDynamicNoiseReduction(enPicNr);
		return 0;
	}
	
	int MPEG_Noise_Reduction(std::string& option)
	{
		EN_UI_PIC_MPEG_NR enMpegPicNr;
		
		unsigned int enpicmpegnr_mode_total = LengthofArray(m_enpicmpegnr_mode_map);
		
		for (unsigned int i = 0; i < enpicmpegnr_mode_total; i++)
		{
			if (m_enpicmpegnr_mode_map[i].selectMode == option)
			{
				enMpegPicNr = m_enpicmpegnr_mode_map[i].ui_enpicmpegnr_mode;
				break;
			}
		}
		PictureSetting::getInstance()->PictureSetMpegNoiseReduction(enMpegPicNr);
		return 0;
	}
	
	int Aspect_Ratio(std::string& option)
	{
		EN_UI_PIC_ASPECT_RATIO picAspectRatio;
		
		unsigned int aspect_ratio_total = LengthofArray(m_aspect_ratio_map);
		
		for (unsigned int i = 0; i < aspect_ratio_total; i++)
		{
			if (m_aspect_ratio_map[i].selectMode == option)
			{
				picAspectRatio = m_aspect_ratio_map[i].ui_aspect_ratio_mode;
				break;
			}
		}
		PictureSetting::getInstance()->PictureSetAspectRatio(picAspectRatio);
		return 0;
	}
	
	int Dynamic(std::string& option)
	{
		EN_UI_SETTING_ON_OFF bDynamicContrast;
		if(option == "On")
			bDynamicContrast = UI_SETTING_ON; 
		else
			bDynamicContrast = UI_SETTING_OFF;
		PictureSetting::getInstance()->PictureSetDynamicContrast(bDynamicContrast);
		return 0;
	}
	
	int Film_Mode(std::string& option)
	{
		EN_UI_SETTING_ON_OFF bFilmMode;
		if(option == "On")
			bFilmMode = UI_SETTING_ON; 
		else
			bFilmMode = UI_SETTING_OFF;
		PictureSetting::getInstance()->PictureSetFilmMode(bFilmMode);
		return 0;
	}
	

	//1 TODO:
	int Picture_Reset(std::string& option)
	{
		return 0;
	}	
	
};


PictureMenuExecutor::PictureMenuExecutor()
	:m_pImpl(new PriveteImpl)
{
	//PictureOptionRefresh();
	
}

PictureMenuExecutor::~PictureMenuExecutor()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = NULL;
	}
	//m_ms_ui_picture.~map();
}


void PictureMenuExecutor::menuRelativeOptionCallbackFun(string& selectedItemMenuName, string& optionName)
{
	if (selectedItemMenuName.empty() || optionName.empty())
		return;
	else{
		m_pImpl->Execute(selectedItemMenuName, optionName);
	}

}


