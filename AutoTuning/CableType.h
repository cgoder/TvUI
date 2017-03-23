#ifndef  _AUTO_TUNING_CABLE_TYPE_H_
#define  _AUTO_TUNING_CABLE_TYPE_H_
#include "cocos2d.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h" 
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
#include "common/common.h"
#include "common/SkyLayer.h"

#include "common/BtnFocusLayer.h"
#include "skyscanapi/skyScanUiApi.h"
class CableType :
	public BtnFocusLayer
{
public:
	CableType();
	~CableType();
	virtual bool init();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node,std::string &select, skyScanParam* params = nullptr, Click_CallFun callFunc = nullptr,int type = 1);

	// implement the "static create()" method manually
	CREATE_FUNC(CableType);
	
protected:
	void initCableType();
	
	void onBtnFull(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnOK(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnNet(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnFre(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnNetId(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnSym(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void setBtnEnable(cocos2d::Node* rootNode, const char* nodeName,bool enable);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);
	
	cocos2d::ui::Button* m_btnFocusedStore;
	cocos2d::Node* m_rootNode;
	void setSignalType(int type) { m_signalType = type; };
	void setParams(std::string &select, skyScanParam* params,Click_CallFun callFunc = nullptr, int type = 0);
protected:
	skyScanParam* m_scanParam;
	int m_signalType;
	skyScanUi* m_scanApi;
	std::vector<std::string> m_vecScope;
	button_user_data *m_btnData[3];
	Click_CallFun m_callFunc;
	cocos2d::EventKeyboard::KeyCode m_keyCode;
	cocos2d::Node* m_selectNode;
};
#endif

