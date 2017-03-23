

#include "SoundMenuExecutor.h"

#include "SoundMenuItemInfo.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "../../setting/UiSystemDataType.h"
#include "../../setting/AudioSetting.h"

USING_NS_CC;

EN_UI_SOUND_MODE enSoundMode;
SoundModeSetting stSoundModeSetting;

void SoundMenuExecutor::SoundSettingRefresh(void)
{	
	char value;
	AudioSetting::getInstance()->AudioGetBalance(&value);

	m_ms_ui_Sound["ID_SET_SOUND_BALANCE"] = value;

	EN_UI_SETTING_ON_OFF bValue;
	AudioSetting::getInstance()->AudioGetAutoVolume(&bValue);
	if(bValue == UI_SETTING_ON)
		m_sound_setting["ID_SET_SOUND_AUTO_VULUME"] = "On";
	else
		m_sound_setting["ID_SET_SOUND_AUTO_VULUME"] = "Off";

	EN_UI_SURROUND_MODE surroundmodeValue;
	AudioSetting::getInstance()->AudioGetSurroundSound(&surroundmodeValue);
	if(bValue == E_SURROUND_MODE_ON)
		m_sound_setting["ID_SET_SOUND_SURROUND"] = "On";
	else
		m_sound_setting["ID_SET_SOUND_SURROUND"] = "Off";

	EN_UI_SOUND_AD_OUTPUT enValue;
	AudioSetting::getInstance()->AudioGetAnalogOutput(&enValue);
	unsigned int sound_ad_outputmode_total = LengthofArray(m_Sound_ad_outputmode_map);
	for (unsigned int i = 0; i < sound_ad_outputmode_total; i++)
	{
		if (m_Sound_ad_outputmode_map[i].ui_Sound_ad_outputmode == enValue)
			m_sound_setting["ID_SET_SOUND_AAOUTPUT"] = m_Sound_ad_outputmode_map[i].selectMode;
	};

	EN_UI_SPDIF_MODE spdif_mode_value;
	AudioSetting::getInstance()->AudioGetDigitalOutput(&spdif_mode_value);
	unsigned int sound_digitaloutputmode_total = LengthofArray(m_Sound_digitaloutput_map);
	for (unsigned int i = 0; i < sound_digitaloutputmode_total; i++)
	{
		if (m_Sound_digitaloutput_map[i].ui_Sound_digitaloutput == spdif_mode_value)
			m_sound_setting["ID_SET_SOUND_DAOUTPUT"] = m_Sound_digitaloutput_map[i].selectMode;
	};

	HDMI_TYPE_ hdmitype_value;
	AudioSetting::getInstance()->AudioGetAudioHdmiType(&hdmitype_value);
	unsigned int sound_hdmi_total = LengthofArray(m_Sound_HDMI_map);
	for (unsigned int i = 0; i < sound_hdmi_total; i++)
	{
		if (m_Sound_HDMI_map[i].ui_Sound_hdmi == hdmitype_value)
			m_sound_setting["ID_SET_SOUND_HDMI"] = m_Sound_HDMI_map[i].selectMode;
	};
	
}

void SoundMenuExecutor::SoundModeRefresh(void)
{
	std::string defaultSelectMode;
	AudioSetting::getInstance()->AudioGetSoundMode(&enSoundMode, &stSoundModeSetting);

	unsigned int Sound_mode_total = LengthofArray(m_Sound_mode_map);
	for (auto i = 0; i < Sound_mode_total; i++)
	{
		if (m_Sound_mode_map[i].ui_soundMode == enSoundMode)
			defaultSelectMode = m_Sound_mode_map[i].selectMode;
	}
	m_sound_setting["ID_SET_SOUND_MODE1"] = defaultSelectMode;
	
	m_ms_ui_Sound["ID_SET_SOUND_TREBLE"] = stSoundModeSetting.treble;
	m_ms_ui_Sound["ID_SET_SOUND_BASS"] = stSoundModeSetting.bass;
	m_ms_ui_Sound["ID_SET_SOUND_TREBLE"] = stSoundModeSetting.treble;
	m_ms_ui_Sound["ID_SET_SOUND_120HZ"] = stSoundModeSetting.eqBand1; //AudioGetEqBand1
	m_ms_ui_Sound["ID_SET_SOUND_500HZ"] = stSoundModeSetting.eqBand2;
	m_ms_ui_Sound["ID_SET_SOUND_1.5KHZ"] = stSoundModeSetting.eqBand3;
	m_ms_ui_Sound["ID_SET_SOUND_5KHZ"] = stSoundModeSetting.eqBand4;
	m_ms_ui_Sound["ID_SET_SOUND_10KHZ"] = stSoundModeSetting.eqBand5;		

	EN_UI_SETTING_ON_OFF bValue;
	AudioSetting::getInstance()->AudioGetEqualizerMode(&bValue);
	if(bValue == UI_SETTING_ON)
		m_sound_setting["ID_SET_SOUND_EQU"] = "On";
	else
		m_sound_setting["ID_SET_SOUND_EQU"] = "Off";
	
}

class SoundMenuExecutor::PriveteImpl
{
public:
	//typedef void (cocos2d::Ref::*Click_CallFun)(cocos2d::Node* node);
	typedef int(PriveteImpl::*MenuItem_Function)(std::string& option);
	typedef std::map<std::string, MenuItem_Function> MenuItem_FunctionMap;
	typedef std::map<std::string, MenuItem_Function>::const_iterator MenuItem_FunctionMapIter;

	MenuItem_FunctionMap m_MenuItem_FunctionMap;

	PriveteImpl()
	{
		//m_MenuItem_FunctionMap["ID_SET_SOUND_MODE"] = &PriveteImpl::Sound_Mode; //"Sound Mode"
		m_MenuItem_FunctionMap["ID_SET_SOUND_BALANCE"] = &PriveteImpl::Balance; //"Balance"
		m_MenuItem_FunctionMap["ID_SET_SOUND_AUTO_VULUME"] = &PriveteImpl::Auto_Volume; //"Auto Volume"
		m_MenuItem_FunctionMap["ID_SET_SOUND_SURROUND"] = &PriveteImpl::Surround_Sound; //"Surround Sound"
		m_MenuItem_FunctionMap["ID_SET_SOUND_AAOUTPUT"] = &PriveteImpl::Analog_Audio_Output; //"Analog Audio Output"
		m_MenuItem_FunctionMap["ID_SET_SOUND_DAOUTPUT"] = &PriveteImpl::Digital_Audio_Output; //"Digital Audio Output"
		m_MenuItem_FunctionMap["ID_SET_SOUND_HDMI"] = &PriveteImpl::Audio_HDMI; //"Audio HDMI"
		m_MenuItem_FunctionMap["ID_SET_SOUND_DES"] = &PriveteImpl::Audio_Description; //"Audio Description"
		m_MenuItem_FunctionMap["ID_SET_SOUND_RESET"] = &PriveteImpl::Sound_Reset; //"Sound Reset"

		m_MenuItem_FunctionMap["ID_SET_SOUND_MODE1"] = &PriveteImpl::Sound_Mode; //"Sound Mode"
		m_MenuItem_FunctionMap["ID_SET_SOUND_EQU"] = &PriveteImpl::Equalizer_Mode; //"Equalizer Mode"
		m_MenuItem_FunctionMap["ID_SET_SOUND_BASS"] = &PriveteImpl::Bass; //"Bass"
		m_MenuItem_FunctionMap["ID_SET_SOUND_TREBLE"] = &PriveteImpl::Treble; //"Treble"
		m_MenuItem_FunctionMap["ID_SET_SOUND_120HZ"] = &PriveteImpl::Sound_120Hz; //"120Hz"
		m_MenuItem_FunctionMap["ID_SET_SOUND_500HZ"] = &PriveteImpl::Sound_500Hz; //"500Hz"
		m_MenuItem_FunctionMap["ID_SET_SOUND_1.5KHZ"] = &PriveteImpl::Sound_1_5KHz; //"1.5KHz"
		m_MenuItem_FunctionMap["ID_SET_SOUND_5KHZ"] = &PriveteImpl::Sound_5KHz; //"5KHZ"
		m_MenuItem_FunctionMap["ID_SET_SOUND_10KHZ"] = &PriveteImpl::Sound_10KHz; //"10KHz"

	}

	~PriveteImpl()
	{
		AudioSetting::destroyInstance();;
	}

public:

	int Execute(string& menuname, string& option)
	{
		
		MenuItem_FunctionMapIter itor = m_MenuItem_FunctionMap.find(menuname);
		if(itor == m_MenuItem_FunctionMap.end())
			return 0;
		return (this->*(itor->second))(option);
	}
	
	//int Sound_Mode(std::string& option)
	//{
	//
	//	return 0;
	//}

	int Balance(std::string& option)
	{
		AudioSetting::getInstance()->AudioSetBalance(stoi(option));
		return 0;
	}
	
	int Auto_Volume(std::string& option)
	{
		EN_UI_SETTING_ON_OFF bAutovolume;
		if(option == "On")
			bAutovolume = UI_SETTING_ON; 
		else
			bAutovolume = UI_SETTING_OFF;
		AudioSetting::getInstance()->AudioSetAutoVolume(bAutovolume);
		return 0;
	}
	
	int Surround_Sound(std::string& option)
	{
		EN_UI_SURROUND_MODE bSurroundsound;
		if(option == "On")
			bSurroundsound = E_SURROUND_MODE_ON; 
		else
			bSurroundsound = E_SURROUND_MODE_OFF;
		AudioSetting::getInstance()->AudioSetSurroundSound(bSurroundsound);
		return 0;
	}

	int Analog_Audio_Output(std::string& option)
	{
		EN_UI_SOUND_AD_OUTPUT sound_ad_outputmode;
		
		unsigned int sound_ad_outputmode_total = LengthofArray(m_Sound_ad_outputmode_map);
		
		for (unsigned int i = 0; i < sound_ad_outputmode_total; i++)
		{
			if (m_Sound_ad_outputmode_map[i].selectMode == option)
			{
				sound_ad_outputmode = m_Sound_ad_outputmode_map[i].ui_Sound_ad_outputmode;
				break;
			}
		}
		AudioSetting::getInstance()->AudioSetAnalogOutput(sound_ad_outputmode);
		return 0;
	}
		
	
	int Digital_Audio_Output(std::string& option)
	{
		EN_UI_SPDIF_MODE enValue;
		
		unsigned int sound_digitaloutput_total = LengthofArray(m_Sound_digitaloutput_map);
		
		for (unsigned int i = 0; i < sound_digitaloutput_total; i++)
		{
			if (m_Sound_digitaloutput_map[i].selectMode == option)
			{
				enValue = m_Sound_digitaloutput_map[i].ui_Sound_digitaloutput;
				break;
			}
		}
		AudioSetting::getInstance()->AudioSetDigitalOutput(enValue);
		return 0;
	}
		
	int Audio_HDMI(std::string& option)
	{
		HDMI_TYPE_ enValue;
		unsigned int sound_digitaloutput_total = LengthofArray(m_Sound_HDMI_map);
		
		for (unsigned int i = 0; i < sound_digitaloutput_total; i++)
		{
			if (m_Sound_HDMI_map[i].selectMode == option)
			{
				enValue = m_Sound_HDMI_map[i].ui_Sound_hdmi;
				break;
			}
		}
			
		AudioSetting::getInstance()->AudioSetAudioHdmiType(enValue);
		return 0;
	}

//1 TODO:

	int Audio_Description(std::string& option)
	{
		return 0;
	}
	
	int Sound_Reset(std::string& option)
	{
		return 0;
	}

	
	int Sound_Mode(std::string& option)
	{
		EN_UI_SOUND_MODE sound_mode;
		
		unsigned int sound_mode_total = LengthofArray(m_Sound_mode_map);
		
		for (unsigned int i = 0; i < sound_mode_total; i++)
		{
			if (m_Sound_mode_map[i].selectMode == option)
			{
				sound_mode = m_Sound_mode_map[i].ui_soundMode;
				break;
			}
		}
		AudioSetting::getInstance()->AudioSetSoundMode(sound_mode);
		return 0;
	}
	
	int Equalizer_Mode(std::string& option)
	{
		EN_UI_SETTING_ON_OFF bValue;
		if(option == "On")
			bValue = UI_SETTING_ON; 
		else
			bValue = UI_SETTING_OFF;
		AudioSetting::getInstance()->AudioSetEqualizerMode(bValue);
		return 0;
	}
	
	int Bass(std::string& option)
	{
		AudioSetting::getInstance()->AudioSetBass(stoi(option));
		return 0;
	}
	int Treble(std::string& option)
	{
		AudioSetting::getInstance()->AudioSetTreble(stoi(option));
		return 0;
	}
	int Sound_120Hz(std::string& option)
	{
		AudioSetting::getInstance()->AudioSetEqBand1(stoi(option));
		return 0;
	}
	int Sound_500Hz(std::string& option)
	{
		AudioSetting::getInstance()->AudioSetEqBand2(stoi(option));
		return 0;
	}
	int Sound_1_5KHz(std::string& option)
	{
		AudioSetting::getInstance()->AudioSetEqBand3(stoi(option));
		return 0;
	}
	int Sound_5KHz(std::string& option)
	{
		AudioSetting::getInstance()->AudioSetEqBand4(stoi(option));
		return 0;
	}
	int Sound_10KHz(std::string& option)
	{
		AudioSetting::getInstance()->AudioSetEqBand5(stoi(option));
		return 0;
	}
};


SoundMenuExecutor::SoundMenuExecutor()
	:m_pImpl(new PriveteImpl)
{

}

SoundMenuExecutor::~SoundMenuExecutor()
{
	if (m_pImpl)
	{
		delete m_pImpl;
		m_pImpl = NULL;
	}
	//m_ms_ui_Sound.~map();
}


void SoundMenuExecutor::menuRelativeOptionCallbackFun(string& selectedItemMenuName, string& optionName)
{
	if (selectedItemMenuName.empty() || optionName.empty())
		return;
	else{
		m_pImpl->Execute(selectedItemMenuName, optionName);
	}

}


