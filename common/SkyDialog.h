#ifndef  _SKYDIALOG_H_
#define  _SKYDIALOG_H_
#include "cocos2d.h"
#include "common/common.h"
#include "common/BtnFocusLayer.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
class SkyDialog :
	public BtnFocusLayer //SkyLayer
{
public:
	SkyDialog();
	~SkyDialog();
	virtual bool init();
	static SkyDialog* create(cocos2d::Node* root, const std::string& filename, Click_CallFun callfuncl = nullptr, Click_CallFun callfuncr = nullptr,cocos2d::Ref* listener = nullptr);
	static SkyDialog* create(cocos2d::Node* root,cocos2d::Node* node, Click_CallFun callfuncl = nullptr, Click_CallFun callfuncr = nullptr, cocos2d::Ref* listener = nullptr);
	void addBtnlClick(Click_CallFun callfunc) { m_callFuncl = callfunc; };
	void addBtnrClick(Click_CallFun callfunc) { m_callFuncr = callfunc; };
	void setCallListener(cocos2d::Ref* listener) { m_callListener = listener;  	};
	void initDia();
	void onBtnYes(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnNo(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void setRootNode(cocos2d::Node* node) { m_rootNode = node; };
	void setTextTitle(const char* nodeName,const char* textTitle);
	void setBtnTitle(const char* nodeName, const char* textTitle);
	cocos2d::ui::Button* getFocused() { return m_btnFocused; };
protected:
	Click_CallFun m_callFuncl;
	Click_CallFun m_callFuncr;
	cocos2d::Node* m_rootNode;
	cocos2d::Ref* m_callListener;
};
#endif

