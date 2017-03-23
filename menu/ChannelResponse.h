#ifndef  _ChannelResponse_H_
#define  _ChannelResponse_H_
#include "cocos2d.h"
#include "menu/MenuResponse.h"
class ChannelResponse:
	public MenuResponse
{
public:
	ChannelResponse();
	~ChannelResponse();
	virtual void initData(std::vector<MenuControl*> menuvec);
	virtual void addMenuFuncByName(const std::string &funcname );
	void onAutoScan(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onManualScan(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onChannelEdit(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onAntennaPowerSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onCiInfo(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onSignalInfo(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	
	void onTest( std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
};
#endif

