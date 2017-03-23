#include "cocos2d.h"
#include "menu/MainResponse.h"
#include "menu/MenuBaseUI.h"
#include "menu/PictureResponse.h"
#include "menu/ChannelResponse.h"
#include "menu/SoundResponse.h"
#include "menu/TimeResponse.h"
#include "menu/AdvanceResponse.h"
#include "menu/SetupResponse.h"
USING_NS_CC;
using namespace cocos2d::ui;
MainResponse::MainResponse()
{
}
MainResponse::~MainResponse()
{

}
void MainResponse::initData(std::vector<MenuControl*> menuvec)
{

}
void MainResponse::addMenuFuncByName(const std::string &funcname)
{
	if (funcname == "ID_TITLE_SET_SOUND")
		addMenuFunc((Menu_CallFun)&MainResponse::onSoundMenu);
	else if (funcname == "ID_TITLE_SET_PIC")
		addMenuFunc((Menu_CallFun)&MainResponse::onPictureMenu );
	else if (funcname == "ID_TITLE_SET_CHANNEL")
		addMenuFunc((Menu_CallFun)&MainResponse::onChannelMenu);
	else if (funcname == "ID_TITLE_SET_ADVANCE")
		addMenuFunc((Menu_CallFun)&MainResponse::onAdvanceMenu );
	else if (funcname == "ID_TITLE_SET_INSTALL")
		addMenuFunc((Menu_CallFun)&MainResponse::onInstallMenu);
	else if (funcname == "ID_TITLE_SET_TIME")
		addMenuFunc((Menu_CallFun)&MainResponse::onTimeMenu);
	else if (funcname == "ID_TITLE_SET_SETUP")
		addMenuFunc((Menu_CallFun)&MainResponse::onSetupMenu);
	else if (funcname == "ID_TITLE_SET_NETWORK")
		addMenuFunc((Menu_CallFun)&MainResponse::onNetworkMenu);
	else
		addMenuFunc((Menu_CallFun)&MainResponse::onTest);
}
void MainResponse::onChannelMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/channel.xml", new ChannelResponse());
}
void MainResponse::onPictureMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/picture.xml", new PictureResponse());
}
void MainResponse::onSoundMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/sound.xml", new SoundResponse());
}
void MainResponse::onInstallMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void MainResponse::onTimeMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/time.xml", new TimeResponse());
}

void MainResponse::onNetworkMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}

void MainResponse::onAdvanceMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/advance.xml", new AdvanceResponse());
}
void MainResponse::onSetupMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/setup.xml", new SetupResponse());
}
void MainResponse::onTest(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}