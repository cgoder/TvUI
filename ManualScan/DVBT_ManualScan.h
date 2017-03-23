#ifndef __DVBT_MANUALSCAN_H__
#define __DVBT_MANUALSCAN_H__

#include "cocos2d.h"
#include "ui/UIImageView.h"
#include "ui/UIListView.h"
#include "common/common.h"
#include "common/BtnFocusLayer.h"
#include "skyscanapi/skyScanUiApi.h"
USING_NS_CC;
using namespace ui;

class DVBT_Manual_Scan : public BtnFocusLayer
{
public:
	DVBT_Manual_Scan();
	~DVBT_Manual_Scan();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	static void tuningBack(skyScanCallbackData data, void* ptr);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void onBtnScan(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnCancel(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnScope(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnFreid(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnBand(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);
	void updataScanStatus(float dt);
	void completeCountDown(float dt);
	void updataDataCounts(const char* nodeName, int counts);
	void onTuningComplete();


	void setScanFreParams();
	void setScanBand();
	void setScanScope();

	void updateSignalQuality();
    // implement the "static create()" method manually
	CREATE_FUNC(DVBT_Manual_Scan);
	
protected:
	cocos2d::EventKeyboard::KeyCode m_keyCode;
	std::vector<skyFreqData> vec_Freq;
	skyScanUi* m_scanApi;
	std::vector<std::string> m_vecScope;
	std::vector<std::string> m_vecBand;
	button_user_data *m_btnData[3];
	cocos2d::Node* m_rootNode;
	int m_countDown;
	skyScanCallbackData m_scanData;
	skyScanParam m_scanParam;
};

#endif // __HELLOWORLD_SCENE_H__
