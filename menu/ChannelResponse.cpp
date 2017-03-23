#include "cocos2d.h"
#include "menu/ChannelResponse.h"
#include "menu/MenuBaseUI.h"
#include "menu/PictureResponse.h"
#include "AutoTuning/AutoTuning.h"
#include "ChannelEdit/ChannelEdit.h"
#include "ManualScan/ManualScan.h"
#include "tvScene.h"
USING_NS_CC;
using namespace cocos2d::ui;
ChannelResponse::ChannelResponse()
{
}
ChannelResponse::~ChannelResponse()
{

}
void ChannelResponse::initData(std::vector<MenuControl*> menuvec)
{

}
void ChannelResponse::addMenuFuncByName(const std::string &funcname)
{
	if (funcname == "ID_SET_DVBT_AUTO_SCAN")
		addMenuFunc((Menu_CallFun)&ChannelResponse::onAutoScan);
	else if (funcname == "ID_SET_DVBT_MANUAL_SCAN")
		addMenuFunc((Menu_CallFun)&ChannelResponse::onManualScan );
	else if (funcname == "ID_SET_CHANNEL_EDIT")
		addMenuFunc((Menu_CallFun)&ChannelResponse::onChannelEdit);
	else if (funcname == "ID_SET_ANTENNA_POWER")
		addMenuFunc((Menu_CallFun)&ChannelResponse::onAntennaPowerSet );
	else if (funcname == "ID_SET_CI_INFO")
		addMenuFunc((Menu_CallFun)&ChannelResponse::onCiInfo);
	else if (funcname == "ID_SET_SIGNAL_INFO")
		addMenuFunc((Menu_CallFun)&ChannelResponse::onSignalInfo);
	else
		addMenuFunc((Menu_CallFun)&ChannelResponse::onTest);
}
void ChannelResponse::onAutoScan(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	cocos2d::Node* curNode = tvScene::getRootLayer();
	log("#############curNode:%p##############\n", curNode);
	AutoTuning::creatLayer(curNode);
}
void ChannelResponse::onManualScan(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	cocos2d::Node* curNode = tvScene::getRootLayer();
	log("#############curNode:%p##############\n", curNode);
	Manual_Scan::creatLayer(curNode);
}
void ChannelResponse::onChannelEdit(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	cocos2d::Node* curNode = tvScene::getRootLayer();
	log("#############curNode:%p##############\n", curNode);
	ChannelEdit::creatLayer(curNode);
}
void ChannelResponse::onAntennaPowerSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
}
void ChannelResponse::onCiInfo(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void ChannelResponse::onSignalInfo(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void ChannelResponse::onTest(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}