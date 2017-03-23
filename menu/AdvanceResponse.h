#ifndef  _AdvanceResponse_H_
#define  _AdvanceResponse_H_
#include "cocos2d.h"
#include "menu/MenuResponse.h"
class AdvanceResponse:
	public MenuResponse
{
public:
	AdvanceResponse();
	~AdvanceResponse();
	virtual void initData(std::vector<MenuControl*> menuvec);
	virtual void addMenuFuncByName(const std::string &funcname );
	void onAdvanceLockSystem(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onAdvanceSetPwd(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onAdvanceBlockChannel(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onAdvanceParentControl(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onAdvancePannelLock(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
};
#endif

