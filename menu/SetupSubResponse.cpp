#include "cocos2d.h"
#include "menu/SetupSubResponse.h"
#include "menu/MenuBaseUI.h"
#include "menu/DropdownUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
SetupSubResponse::SetupSubResponse()
{

}
SetupSubResponse::~SetupSubResponse()
{

}
void SetupSubResponse::initData(std::vector<MenuControl*> menuvec)
{
	
}
void SetupSubResponse::addMenuFuncByName(const std::string &funcname)
{
	if (funcname == "ID_SET_AUDLANG_PRIMARY")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onAudLangPrimaryMenu);
	else if (funcname == "ID_SET_AUDLANG_SECOND")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onAudLangSecondMenu);
	else if (funcname == "ID_SET_SUBLANG_PRIMARY")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onSubLangPrimaryMenu);
	else if (funcname == "ID_SET_SUBLANG_SECOND")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onSubLangSecondMenu);


	else if (funcname == "ID_SET_PVR_DISK")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onPVRDiskSet);
	else if (funcname == "ID_SET_PVR_TIME_SHIFT")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onPVRTimeShiftSet);
	else if (funcname == "ID_SET_PVR_FORMAT")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onPVRFormatSet);
	else if (funcname == "ID_SET_PVR_SPEED")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onPVRSpeedSet);

	else if (funcname == "ID_SET_SETUP_HDMI_CEC")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onHDMICECSet);
	else if (funcname == "ID_SET_SETUP_DEVICE_LIST")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onHDMIDeviceSet);
	else if (funcname == "ID_SET_SETUP_STANDBY")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onHDMIStanbySet);
	else if (funcname == "ID_SET_SETUP_POWERON")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onHDMIPowerOnSet);

	else if (funcname == "ID_SET_PRES_STICKER")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onPresStickerSet);
	else if (funcname == "ID_SET_PRES_USB")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onPresUSBSet);

	else if (funcname == "ID_SET_SETUP_FAST_BOOT")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onAdvFastBootReset);
	else if (funcname == "ID_SET_SETUP_NETWAKE")
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onAdvNetWakeReset);
	else
		addMenuFunc((Menu_CallFun)&SetupSubResponse::onAdvNetWakeReset);

}
void SetupSubResponse::onAudLangPrimaryMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	this->addDropDownFunc((Menu_CallFun)&SetupSubResponse::onAudLangPrimarySet);
	Size cellSize(menu->getItemWidth(), menu->getItemHeight());
	Size tableSize(menu->getItemWidth(), menu->getTableHeight());
	Vec2 position(menu->getCellWidth(), 0);
	auto layer = DropdownUI::creatLayer(node, cellSize, tableSize, position, menuvec, menu, this);
}
void SetupSubResponse::onAudLangSecondMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	this->addDropDownFunc((Menu_CallFun)&SetupSubResponse::onAudLangSecondSet);
	Size cellSize(menu->getItemWidth(), menu->getItemHeight());
	Size tableSize(menu->getItemWidth(), menu->getTableHeight());
	Vec2 position(menu->getCellWidth(), 0);
	auto layer = DropdownUI::creatLayer(node, cellSize, tableSize, position, menuvec, menu, this);
}
void SetupSubResponse::onSubLangPrimaryMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	this->addDropDownFunc((Menu_CallFun)&SetupSubResponse::onSubLangPrimarySet);
	Size cellSize(menu->getItemWidth(), menu->getItemHeight());
	Size tableSize(menu->getItemWidth(), menu->getTableHeight());
	Vec2 position(menu->getCellWidth(), 0);
	auto layer = DropdownUI::creatLayer(node, cellSize, tableSize, position, menuvec, menu, this);
}
void SetupSubResponse::onSubLangSecondMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	this->addDropDownFunc((Menu_CallFun)&SetupSubResponse::onSubLangSecondSet);
	Size cellSize(menu->getItemWidth(), menu->getItemHeight());
	Size tableSize(menu->getItemWidth(), menu->getTableHeight());
	Vec2 position(menu->getCellWidth(), 0);
	auto layer = DropdownUI::creatLayer(node, cellSize, tableSize, position, menuvec, menu, this);
}
void SetupSubResponse::onAudLangPrimarySet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{	
	
}
void SetupSubResponse::onAudLangSecondSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	
}
void SetupSubResponse::onSubLangPrimarySet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	
}
void SetupSubResponse::onSubLangSecondSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	
}
void SetupSubResponse::onPVRDiskSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	
}

void SetupSubResponse::onPVRTimeShiftSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	
}
void SetupSubResponse::onPVRFormatSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupSubResponse::onPVRSpeedSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupSubResponse::onHDMICECSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupSubResponse::onHDMIDeviceSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupSubResponse::onHDMIStanbySet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupSubResponse::onHDMIPowerOnSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupSubResponse::onPresStickerSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupSubResponse::onPresUSBSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupSubResponse::onAdvFastBootReset(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SetupSubResponse::onAdvNetWakeReset(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
