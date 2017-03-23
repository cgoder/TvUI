#ifndef  _AUTO_TUNING_CABLE_H_
#define  _AUTO_TUNING_CABLE_H_
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
#include "AutoTuning/AutoTuning.h"
class CableAutoTuning :
	public AutoTuning
{
public:
	CableAutoTuning();
	~CableAutoTuning();
	virtual bool init();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node,int type = 0);

	// implement the "static create()" method manually
	CREATE_FUNC(CableAutoTuning);
	
protected:
	void initCableAutoTuning();
	void onBtnScan(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnCountry(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnType(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnScope(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onCountryChoose(cocos2d::Node* node);
	void onTypeChoose(cocos2d::Node* node);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);

protected:
	cocos2d::EventKeyboard::KeyCode m_keyCode;
	std::vector<std::string> m_vecScope;
	button_user_data* m_btnData;
};
#endif

