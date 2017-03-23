
#ifndef  __PICTUREMENUITEMINFO_H__
#define  __PICTUREMENUITEMINFO_H__

#include "../../setting/UiSystemDataType.h"

class PictureMenuItemInfo
{
public:
	struct ms_ui_picture
	{
		int backlight;
		int brightness;
		int contrast;
		int sharpness;
	} m_ms_ui_picture;
	
	typedef struct picture_mode_map
	{
		EN_UI_PICTURE_MODE ui_picture_mode;
		std::string selectMode;
	}picture_mode_map;
	
	static const picture_mode_map m_picture_mode_map[];
	
	typedef struct colortemp_mode_map
	{
		EN_UI_COLOR_TEMP ui_colortemp_mode;
		std::string selectMode;
	}colortemp_mode_map;
	
	static const picture_mode_map m_colortemp_mode_map[];
	
	typedef struct enpicnr_mode_map
	{
		EN_UI_PIC_NR ui_enpicnr_mode;
		std::string selectMode;
	}enpicnr_mode_map;
	
	static const enpicnr_mode_map m_enpicnr_mode_map[];

	typedef struct enpicmpegnr_mode_map
	{
		EN_UI_PIC_MPEG_NR ui_enpicmpegnr_mode;
		std::string selectMode;
	}enpicmpegnr_mode_map;
	
	static const enpicmpegnr_mode_map m_enpicmpegnr_mode_map[];

	typedef struct aspect_ratio_map
	{
		EN_UI_PIC_ASPECT_RATIO ui_aspect_ratio_mode;
		std::string selectMode;
	}aspect_ratio_map;
	
	static const aspect_ratio_map m_aspect_ratio_map[];


};


static const PictureMenuItemInfo::picture_mode_map m_picture_mode_map[] =
{
	{ PICTURE_NORMAL, "Standard" },
	{ PICTURE_MOVIE, "Movie" },
	{ PICTURE_DYNAMIC, "Sport" },
	{ PICTURE_USER, "User" }
};

static const PictureMenuItemInfo::colortemp_mode_map m_colortemp_mode_map[] =
{
	{ COLOR_TEMP_NATURE, "Natural" },
	{ COLOR_TEMP_WARM, "Warm" },
	{ COLOR_TEMP_COOL, "Cool" }
};
 
static const PictureMenuItemInfo::enpicnr_mode_map m_enpicnr_mode_map[] =
{
	{ PIC_NR_OFF, "Off" },
	{ PIC_NR_LOW, "Low" },
	{ PIC_NR_MIDDLE, "Middle" },
	{ PIC_NR_HIGH, "High" }
};
 
static const PictureMenuItemInfo::enpicmpegnr_mode_map m_enpicmpegnr_mode_map[] =
{
	{ PIC_MPEG_NR_OFF, "Off" },
	{ PIC_MPEG_NR_LOW, "Low" },
	{ PIC_MPEG_NR_MIDDLE, "Middle" },
	{ PIC_MPEG_NR_HIGH, "High" }
};

static const PictureMenuItemInfo::aspect_ratio_map m_aspect_ratio_map[] =
{
	{ PIC_ASPECT_RATIO_16_9, "16:9" },
	{ PIC_ASPECT_RATIO_4_3, "4:3" },
	{ PIC_ASPECT_RATIO_ZOOM1, "Movie" },  //todo,not confirmed.
	{ PIC_ASPECT_RATIO_ZOOM2, "Native" },  //todo,not confirmed.
	{ PIC_ASPECT_RATIO_PANORAMA, "Panoramic" }
};

template<class T, size_t N>
unsigned int LengthofArray(const T(&array)[N]){
	return (sizeof(array) / sizeof(T));
};

#endif //__PICTUREMENUITEMINFO_H__
