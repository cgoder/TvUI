#ifndef __ATV_MANUAL_SCAN_H__
#define __ATV_MANUAL_SCAN_H__

#include "cocos2d.h"
#include "ui/UIImageView.h"
#include "ui/UIListView.h"
#include "common/common.h"
#include "common/BtnFocusLayer.h"
#include "skyscanapi/skyScanUiApi.h"
#define SCANTV
USING_NS_CC;
using namespace ui;
typedef enum
{
	STATUS_SEARCH_IDLE,
	STATUS_SEARCH_LEFT,
	STATUS_SEARCH_RIGHT,
}ManualScanStatus;
class ATV_Manual_Scan : public BtnFocusLayer
{
public:
	ATV_Manual_Scan();
	~ATV_Manual_Scan();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	static void tuningBack(skyScanCallbackData data, void* ptr);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	/*
	void onBtnScan(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnCancel(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	*/
	void onBtnChan(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnSound(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnColor(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnSearch(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnTune(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);

/*
	void updataScanStatus(float dt);
	void completeCountDown(float dt);
	void updataDataCounts(const char* nodeName, int counts);
	void onTuningComplete();
*/
/*
	void setScanFreParams();
	void setScanBand();
	void setScanScope();
*/
	void initScanData();
	void setScanColor();
	void setScanSound();
	
	void updateSignalQuality();

	void setSearchStatus(ManualScanStatus status) { m_searchStatus = status; };
	// implement the "static create()" method manually
	CREATE_FUNC(ATV_Manual_Scan);

protected:
	cocos2d::EventKeyboard::KeyCode m_keyCode;
	std::vector<skyFreqData> vec_Freq;
#ifdef SCANTV
	skyScanUi* m_scanApi;
#endif
	std::vector<std::string> m_vecAudio;
	std::vector<std::string> m_vecColor;
	button_user_data *m_btnData[5];
	cocos2d::Node* m_rootNode;
	int m_countDown;
	skyScanCallbackData m_scanData;
	ManualScanStatus m_searchStatus;
	int m_channelNums;
	skyScanParam* m_scanParam;
};

#endif // __HELLOWORLD_SCENE_H__
