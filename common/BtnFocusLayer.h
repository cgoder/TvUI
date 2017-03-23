#ifndef  _BTNFOCUS_LAYER_H_
#define  _BTNFOCUS_LAYER_H_
#include "cocos2d.h"
#include "common/common.h"
#include "common/SkyLayer.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
typedef void (cocos2d::Ref::*Click_CallFun)(cocos2d::Node* node);
typedef struct button_user_data {
	int type;
	int index;
	void* data;
	std::string text;
}_BUTTON_USER_DATA;
enum BUTTON_TYPE {
	TYPE_CLICK,
    TYPE_NUMS,
    TYPE_TEXT,
	TYPE_TEXTNUMS,
};
class BtnFocusLayer :
	public SkyLayer
{
public:
	BtnFocusLayer();
	~BtnFocusLayer();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);
	virtual void onFocusChanged(cocos2d::Node *nodeLostFocus, cocos2d::Node *nodeGetFocus);
	void findNextFocus(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event,char* direction);
	bool parseUserData(char *in, char * matching, char* out);
	void checkBtnText(cocos2d::ui::Button* node,cocos2d::Touch touch);
	void setTextTitle(cocos2d::Node* rootNode,const char* nodeName, const char* textTitle);
	void setBtnTitle(cocos2d::Node* rootNode,const char* nodeName, const char* textTitle);
//	void setBtnFunc(cocos2d::Node* rootNode, const char* nodeName, std::function<void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType)> func, void* userdata);
	cocos2d::ui::Button* setBtnFunc(cocos2d::Node* rootNode, const char* nodeName, std::function<void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType)> func, void* userdata);
protected:
	cocos2d::ui::Button* m_btnFocused;
	cocos2d::ui::Button* m_btnTempFocused;
};
#endif

