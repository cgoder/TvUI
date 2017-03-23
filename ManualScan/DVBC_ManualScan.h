#ifndef __DVBCMANUALSCAN_SCENE_H__
#define __DVBCMANUALSCAN_SCENE_H__

#include "cocos2d.h"
#include "ui/UIImageView.h"
#include "ui/UIListView.h"
#include "common/common.h"
#include "common/BtnFocusLayer.h"
#include "skyscanapi/skyScanUiApi.h"
#include "skyscanapi/skyScanType.h"
#include "ManualScan/ManualScan.h"
#include "ManualScan/ManualScan_Type.h"
#include "string"
USING_NS_CC;
using namespace ui;

#define MAXITEM_C 4
#define DEFAULT_FREQ 250
class DVBC_Manual_Scan : public BtnFocusLayer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	DVBC_Manual_Scan();
	~DVBC_Manual_Scan();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual bool skyShow(cocos2d::Node* node);
	virtual void skyHide(cocos2d::Node* node);
	virtual void skyRefresh();
	// implement the "static create()" method manually
	CREATE_FUNC(DVBC_Manual_Scan);
	void SetOptionData(int medulation, int symbol, int scope, int freq);
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, Event *event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, Event *event);
	void drawCurrent(REMOTE_TYPE type, int list_focus, int item_focus);  //获取焦点index
	int KeyCode2int(cocos2d::EventKeyboard::KeyCode keyCode);
	void ChangeOptionData(REMOTE_TYPE type, int currentListFocus); //改变option数据
	void onBtnScan_C(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnCancel_C(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void updataScanStatus(float dt);
	void completeCountDown(float dt);
	void updataDataCounts(const char* nodeName, int counts);
	void onTuningComplete();
	static void dvbc_getdata(skyScanCallbackData data,void *ptr);

public:
	cocos2d::Node* rootNode;
	ListView *label_list;
	//std::vector<std::string> array_label;
	ListView *arrow_list_l;
	ListView *arrow_list_r;
	ListView *option_list;
	Text* medual_text;
	Text* symbol_text;
	Text* scope_text;
	ImageView * focus_image;
	ImageView * button_save;
	ImageView * button_cancle;
	ImageView * button_bg_save;
	ImageView * button_bg_cancle;
	Layout * inputlayer;
	TextField* inputtext;
	Text * freqtext;
	int list_focus;   //ui 上半部分 焦点位置
	int item_focus; //ui 下半部分 焦点位置
	//int input_focus; //
	cocos2d::Node* m_rootNode;
	std::string fre_result;
	std::string symbol_result;
	
	int m_countDown;
	bool m_switch;
	static skyScanCallbackData *tvdata;
	skyScanUi*pInstance;

	string medulation[6];
	string symbol[2];
	string  scanscope[3];
	int medulation_index;
	int symbol_index ;
	int scope_index;
};

#endif // __HELLOWORLD_SCENE_H__
