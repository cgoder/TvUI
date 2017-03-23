#ifndef  _CHANNELMENU_H_
#define  _CHANNELMENU_H_
#include "cocos2d.h"
#include "common/common.h"
#include "common/SkyLayer.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
#include "epg/GridView/GridView.h"
#include "common/ListFocusLayer.h"
#include "menu/MenuLayer.h"
typedef void (cocos2d::Ref::*Click_CallFun)(cocos2d::Node* node);
class channelMenu :
	public MenuLayer
{
public:
	channelMenu();
	~channelMenu();
	virtual bool init();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node,int cols,int rows,int cells, Click_CallFun callFunc = nullptr);
	CREATE_FUNC(channelMenu);
	void addCallBack(Click_CallFun callFunc) { m_callFunc = callFunc; };
	//void addChooseStr(std::string str) { m_chooseStr.pushBack(str); };
	virtual void onCellClick(cocos2d::Node* node);
};
#endif

