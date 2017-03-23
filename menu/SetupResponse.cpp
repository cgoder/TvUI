#include "cocos2d.h"
#include "menu/SetupResponse.h"
#include "menu/SetupSubResponse.h"
#include "menu/MenuBaseUI.h"
#include "menu/DropdownUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
SetupResponse::SetupResponse()
{

}
SetupResponse::~SetupResponse()
{
	
}
void SetupResponse::initData(std::vector<MenuControl*> menuvec)
{	
	
}
void SetupResponse::addMenuFuncByName(const std::string &funcname)
{
	if (funcname == "ID_SET_OSD_LANGUAHE")
		addMenuFunc((Menu_CallFun)&SetupResponse::onOsdLanguageMenu);
	else if (funcname == "ID_SET_AUDIO_LANGUAGE")
		addMenuFunc((Menu_CallFun)&SetupResponse::onAudioLanguageMenu);
	else if (funcname == "ID_SET_SUBTITLE_LANGUAGE")
		addMenuFunc((Menu_CallFun)&SetupResponse::onSubLanguageMenu);
	else if (funcname == "ID_SET_HEAR_IMPAIRED")
		addMenuFunc((Menu_CallFun)&SetupResponse::onHearImpairedSet);
	else if (funcname == "ID_SET_TELETEXT_LANGUAGE")
		addMenuFunc((Menu_CallFun)&SetupResponse::onTeletextLanguageMenu);
	else if (funcname == "ID_SET_PVR")
		addMenuFunc((Menu_CallFun)&SetupResponse::onPVRSystemMenu);
	else if (funcname == "ID_SET_HDMI_CEC")
		addMenuFunc((Menu_CallFun)&SetupResponse::onHDMICESMenu);

	else if (funcname == "ID_SET_LOCATION")
		addMenuFunc((Menu_CallFun)&SetupResponse::onLocationSet);
	else if (funcname == "ID_SET_PRESENTATION")
		addMenuFunc((Menu_CallFun)&SetupResponse::onPresentationMenu);
	else if (funcname == "ID_SET_UPDATE")
		addMenuFunc((Menu_CallFun)&SetupResponse::onUpdateMenu);
	else if (funcname == "ID_SET_ADVANCE_OPTION")
		addMenuFunc((Menu_CallFun)&SetupResponse::onAdvanceOptionMenu);
	else if (funcname == "ID_SET_BLUE_SCREEN")
		addMenuFunc((Menu_CallFun)&SetupResponse::onBlueScreenSet);
	else if (funcname == "ID_SET_SETUP_RESET")
		addMenuFunc((Menu_CallFun)&SetupResponse::onSetupResetMenu);
	else 
		addMenuFunc((Menu_CallFun)&SetupResponse::onSetupResetMenu);
}
void SetupResponse::onOsdLanguageMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{	
	this->addDropDownFunc((Menu_CallFun)&SetupResponse::onOsdLanguageSet);
	Size cellSize(menu->getItemWidth(), menu->getItemHeight());
	Size tableSize(menu->getItemWidth(), menu->getTableHeight());
	Vec2 position(menu->getCellWidth(), 0);
	auto layer = DropdownUI::creatLayer(node, cellSize, tableSize, position, menuvec, menu, this);
}
void SetupResponse::onTeletextLanguageMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	this->addDropDownFunc((Menu_CallFun)&SetupResponse::onTeletextLanguageSet);
	Size cellSize(menu->getItemWidth(), menu->getItemHeight());
	Size tableSize(menu->getItemWidth(), menu->getTableHeight());
	Vec2 position(menu->getCellWidth(), 0);
	auto layer = DropdownUI::creatLayer(node, cellSize, tableSize, position, menuvec, menu, this);
}
void SetupResponse::onAudioLanguageMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/setup_aud_lang.xml", new SetupSubResponse());
}
void SetupResponse::onSubLanguageMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/setup_sub_lang.xml", new SetupSubResponse());
}

void SetupResponse::onPVRSystemMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/setup_pvr.xml", new SetupSubResponse());
}
void SetupResponse::onHDMICESMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/setup_hdmi.xml", new SetupSubResponse());
}

void SetupResponse::onPresentationMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/setup_present.xml", new SetupSubResponse());
}

void SetupResponse::onAdvanceOptionMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/setup_advance.xml", new SetupSubResponse());
}
void SetupResponse::onUpdateMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupResponse::onSetupResetMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupResponse::onHearImpairedSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupResponse::onBlueScreenSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupResponse::onLocationSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}

void SetupResponse::onOsdLanguageSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupResponse::onTeletextLanguageSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}

