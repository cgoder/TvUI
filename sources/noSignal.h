#ifndef  _NO_SIGNAL_H_
#define  _NO_SIGNAL_H_
#include "cocos2d.h"
#include "common/common.h"
#include "common/SkyLayer.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
#include "epg/GridView/GridView.h"
#include "common/ListFocusLayer.h"
typedef void (cocos2d::Ref::*Click_CallFun)(cocos2d::Node* node);
class noSignal :
	public SkyLayer
{
public:
	noSignal();
	~noSignal();
	virtual bool init();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node,Click_CallFun callFunc = nullptr);
	/*virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);
	virtual bool onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll = true);*/

	void menuCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(noSignal);
	
protected:
	int m_sourceType;
};
#endif

