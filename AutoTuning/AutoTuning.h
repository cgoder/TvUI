#ifndef  _AUTO_TUNING_H_
#define  _AUTO_TUNING_H_
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
#define SCANTV
class AutoTuning :
	public BtnFocusLayer
{
public:
	AutoTuning();
	~AutoTuning();	
	static cocos2d::Layer* creatLayer(cocos2d::Node* node, int type = 0);
protected:
	void initTuning();
	void onBtnStop_Tuning(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	
	void StopTuning();
	void onBtnStop_Tuning_Confirm(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnStop_Tuning_Cancel(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);


	void initTuning_Stoped();
	void onBtnTuning_Again(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnTuning_Close(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	
	void initTuning_Completed();
	void onBtnTuning_Completed(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void updataScanStatus(float dt);
	void completeCountDown(float dt);
	void updataDataCounts(const char* nodeName, int counts);
	
	cocos2d::ui::Button* m_btnFocusedStore;
	cocos2d::Node* m_rootNode;
	static void tuningBack(skyScanCallbackData data,void* ptr);
	void setSignalType(int type) { m_signalType = type; };
protected:
#ifdef SCANTV
	skyScanUi* m_scanApi;
#endif
	int m_countDown;
	int m_signalType;
	skyScanCallbackData m_scanData;
	skyScanParam* m_scanParam;
};
#endif

