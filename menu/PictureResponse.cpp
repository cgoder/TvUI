#include "cocos2d.h"
#include "menu/PictureResponse.h"
#include "menu/MenuBaseUI.h"


USING_NS_CC;
using namespace cocos2d::ui;
PictureResponse::PictureResponse()
{
	m_pictureMenuExecutor = new PictureMenuExecutor;

}
PictureResponse::~PictureResponse()
{
	if (m_pictureMenuExecutor != NULL){
		delete m_pictureMenuExecutor;
		m_pictureMenuExecutor = NULL;
	}
}
void PictureResponse::initData(std::vector<MenuControl*> menuvec)
{
	m_pictureMenuExecutor->PictureModeRefresh();
	m_pictureMenuExecutor->PictureOptionRefresh();

	for (auto menu : menuvec)
	{
		std::string name = menu->getName();

		auto itor = m_pictureMenuExecutor->m_picture_mode_refresh.find(name);
		if(itor != m_pictureMenuExecutor->m_picture_mode_refresh.end())
		{
			menu->setItemCur(itor->second);
			continue;
		}

		auto itor1 = m_pictureMenuExecutor->m_ms_ui_picture.find(name);
		if(itor1 != m_pictureMenuExecutor->m_ms_ui_picture.end())
			menu->setCurValue(itor1->second);
	}
	
}
void PictureResponse::addMenuFuncByName(const std::string &funcname)
{
	if (funcname == "ID_SET_PIC_MODE")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicModeSet);
	else if (funcname == "ID_SET_BACKLIGHT")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicBacklightSet );
	else if (funcname == "ID_SET_CONTRAST")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicContrastSet);
	else if (funcname == "ID_SET_BRIGHTNESS")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicBrightnessSet);
	else if (funcname == "ID_SET_COLOR")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicColorSet);
	else if (funcname == "ID_SET_SHARPNESS")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicSharpnessSet);
	else if (funcname == "ID_SET_ASPECT")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicAspectSet);

	else if (funcname == "ID_SET_COLOR_TEMP")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicColorTempSet);
	else if (funcname == "ID_SET_DYNAMIC_NOISE")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicDynmicNoiseSet);
	else if (funcname == "ID_SET_MPEG_NOISE")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicMpegNoiseSet);
	else if (funcname == "ID_SET_DYNAMIC_CONTRAST")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicDynmicContrastSet);
	else if (funcname == "ID_SET_LIGHT_SENSOR")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicLightSensorSet);
	else if (funcname == "ID_SET_PICTURE_SENSOR")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPictureSensorSet);
	else if (funcname == "ID_SET_FILM_MODE")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPicFilmModeSet);
	else if (funcname == "ID_SET_PICTURE_RESET")
		addMenuFunc((Menu_CallFun)&PictureResponse::onPictureReset);



}
void PictureResponse::onPicModeSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{	
	std::string selectedItemMenuName, optionName;

	selectedItemMenuName = menu->getName();
	menu->getItemCur(optionName);
	m_pictureMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
	m_pictureMenuExecutor->PictureModeRefresh();
	m_pictureMenuExecutor->PictureOptionRefresh();

	for (auto menu : menuvec)
	{
		std::string name = menu->getName();

		auto itor = m_pictureMenuExecutor->m_picture_mode_refresh.find(name);
		if(itor != m_pictureMenuExecutor->m_picture_mode_refresh.end())
		{
			menu->setItemCur(itor->second);
			continue;
		}

		auto itor1 = m_pictureMenuExecutor->m_ms_ui_picture.find(name);
		if(itor1 != m_pictureMenuExecutor->m_ms_ui_picture.end())
			menu->setCurValue(itor1->second);
	}
}
void PictureResponse::onPicBacklightSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	std::string selectedItemMenuName, optionName;
	int curValue;

	selectedItemMenuName = menu->getName();
	curValue = menu->getCurValue();
	optionName = to_string(curValue);
	m_pictureMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
}
void PictureResponse::onPicContrastSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	std::string selectedItemMenuName, optionName;
	int curValue;

	selectedItemMenuName = menu->getName();
	curValue = menu->getCurValue();
	optionName = to_string(curValue);
	m_pictureMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
}
void PictureResponse::onPicBrightnessSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	std::string selectedItemMenuName, optionName;
	int curValue;

	selectedItemMenuName = menu->getName();
	curValue = menu->getCurValue();
	optionName = to_string(curValue);
	m_pictureMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
}
void PictureResponse::onPicColorSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	std::string selectedItemMenuName, optionName;
	int curValue;

	selectedItemMenuName = menu->getName();
	curValue = menu->getCurValue();
	optionName = to_string(curValue);
	m_pictureMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
}

void PictureResponse::onPicSharpnessSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	std::string selectedItemMenuName, optionName;
	int curValue;

	selectedItemMenuName = menu->getName();
	curValue = menu->getCurValue();
	optionName = to_string(curValue);
	m_pictureMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
}
void PictureResponse::onPicAspectSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	std::string selectedItemMenuName, optionName;

	selectedItemMenuName = menu->getName();
	menu->getItemCur(optionName);
	m_pictureMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
}
void PictureResponse::onPicColorTempSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onPictureCommonSet(menu);
}
void PictureResponse::onPicDynmicNoiseSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onPictureCommonSet(menu);
}

void PictureResponse::onPicMpegNoiseSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onPictureCommonSet(menu);
}

void PictureResponse::onPicDynmicContrastSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onPictureCommonSet(menu);
}

void PictureResponse::onPicLightSensorSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	//1 TODO: not implement yet.
}

void PictureResponse::onPictureSensorSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	//1 TODO: not implement yet.
}
void PictureResponse::onPicFilmModeSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onPictureCommonSet(menu);
}
void PictureResponse::onPictureReset(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	//1 TODO: not implement yet.
}

void PictureResponse::onPictureCommonSet(MenuControl* menu)
{
	std::string selectedItemMenuName, optionName;

	selectedItemMenuName = menu->getName();
	menu->getItemCur(optionName);
	m_pictureMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
}


