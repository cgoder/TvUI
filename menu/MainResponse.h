#ifndef  _MainResponse_H_
#define  _MainResponse_H_
#include "cocos2d.h"
#include "menu/MenuResponse.h"
class MainResponse:
	public MenuResponse
{
public:
	MainResponse();
	~MainResponse();
	virtual void initData(std::vector<MenuControl*> menuvec);
	virtual void addMenuFuncByName(const std::string &funcname );
	void onChannelMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPictureMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onSoundMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onSetupMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onAdvanceMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onTimeMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onNetworkMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onInstallMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);

	void onTest( std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
};
#endif

