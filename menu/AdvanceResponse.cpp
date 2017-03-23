#include "cocos2d.h"
#include "menu/AdvanceResponse.h"
#include "menu/SoundModeResponse.h"
#include "menu/MenuBaseUI.h"
#include "common/SetPassword.h"
USING_NS_CC;
using namespace cocos2d::ui;
AdvanceResponse::AdvanceResponse()
{
}
AdvanceResponse::~AdvanceResponse()
{

}
void AdvanceResponse::initData(std::vector<MenuControl*> menuvec)
{

}
void AdvanceResponse::addMenuFuncByName(const std::string &funcname)
{
	if (funcname == "ID_ADVANCE_LOCK_SYSTEM")
		addMenuFunc((Menu_CallFun)&AdvanceResponse::onAdvanceLockSystem);
	else if (funcname == "ID_ADVANCE_SET_PWD")
		addMenuFunc((Menu_CallFun)&AdvanceResponse::onAdvanceSetPwd );
	else if (funcname == "ID_ADVANCE_BLOCK_CHANNEL")
		addMenuFunc((Menu_CallFun)&AdvanceResponse::onAdvanceBlockChannel);
	else if (funcname == "ID_ADVANCE_PARENTAL")
		addMenuFunc((Menu_CallFun)&AdvanceResponse::onAdvanceParentControl);
	else if (funcname == "ID_ADVANCE_PANEL_LOCK")
		addMenuFunc((Menu_CallFun)&AdvanceResponse::onAdvancePannelLock);

}
void AdvanceResponse::onAdvanceLockSystem(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void AdvanceResponse::onAdvanceSetPwd(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	SetPassword::creatLayer(rootNode);
}
void AdvanceResponse::onAdvanceBlockChannel(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void AdvanceResponse::onAdvanceParentControl(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void AdvanceResponse::onAdvancePannelLock(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}


