
#ifndef  __SOUNDMENUITEMINFO_H__
#define  __SOUNDMENUITEMINFO_H__

#include "mapi_types.h"
#include "../../setting/UiSystemDataType.h"
#include "../../setting/AudioSetting.h"

class SoundMenuItemInfo
{
public:
	typedef struct Sound_ad_outputmode_map
	{
		EN_UI_SOUND_AD_OUTPUT ui_Sound_ad_outputmode;
		std::string selectMode;
	}Sound_ad_outputmode_map;
	static const Sound_ad_outputmode_map m_Sound_ad_outputmode_map[];

	typedef struct Sound_digitaloutput_map
	{
		EN_UI_SPDIF_MODE ui_Sound_digitaloutput;
		std::string selectMode;
	}Sound_digitaloutput_map;
	static const Sound_digitaloutput_map m_Sound_digitaloutput_map[];

	typedef struct Sound_HDMI_map
	{
		HDMI_TYPE_ ui_Sound_hdmi;
		std::string selectMode;
	}Sound_HDMI_map;
	static const SoundMenuItemInfo::Sound_HDMI_map m_Sound_HDMI_map[];

	typedef struct Sound_mode_map
	{
		EN_UI_SOUND_MODE ui_soundMode;
		std::string selectMode;
	}Sound_mode_map;
	static const SoundMenuItemInfo::Sound_mode_map m_Sound_mode_map[];

	
};

static const SoundMenuItemInfo::Sound_ad_outputmode_map m_Sound_ad_outputmode_map[] =
{
	{ AD_SPEAKER, "Lineout" },
	{ AD_HEADPHONE, "Headphone" }
#if 0
	{ Sound_NORMAL, "Standard" },
	{ Sound_MOVIE, "Music" },
	{ Sound_DYNAMIC, "Movie" },
	{ Sound_USER, "User" }
	
#endif
};
static const SoundMenuItemInfo::Sound_digitaloutput_map m_Sound_digitaloutput_map[] =
{
	{ UI_SPDIF_AUTO, "Auto" },
	{ UI_SPDIF_PCM, "PCM" }
};

static const SoundMenuItemInfo::Sound_HDMI_map m_Sound_HDMI_map[] =
{
	{ MSAPI_HDMI_MODE_PCM, "Analog" },	//Analog
	{ MSAPI_HDMI_MODE_RAW, "Digital" },	//Digital
	{ MSAPI_HDMI_MODE_UNKNOWN, "Auto" }	//Auto
};



static const SoundMenuItemInfo::Sound_mode_map m_Sound_mode_map[] =
{
	{ SOUND_MODE_STANDARD, "Standard" },
	{ SOUND_MODE_MUSIC, "Music" },
	{ SOUND_MODE_MOVIE, "Movie" },
	{ SOUND_MODE_USER, "User" }
};


//1 TODO:
#if 0
static const SoundMenuItemInfo::aspect_ratio_map m_aspect_ratio_map[] =
{
	{ Sound_NORMAL, "16:9" },
	{ Sound_MOVIE, "4:3" },
	{ Sound_DYNAMIC, "Panoramic" },
	{ Sound_USER, "Movie" },
	{ Sound_USER, "Native" }
};
#endif

template<class T, size_t N>
unsigned int LengthofArray(const T(&array)[N]){
	return (sizeof(array) / sizeof(T));
};


#endif //__SOUNDMENUITEMINFO_H__
