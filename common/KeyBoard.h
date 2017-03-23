#ifndef  _KeyBoard_H_
#define  _KeyBoard_H_
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
class KeyBoard :
	public ListFocusLayer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
	KeyBoard();
	~KeyBoard();
	virtual bool init();
	void initTableView();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node,cocos2d::Node* text = nullptr, Click_CallFun callFunc = nullptr);
	void addTitle(const char* str);
	void addNote(const char* str);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);
	CREATE_FUNC(KeyBoard);
	void addCallBack(Click_CallFun callFunc) { m_callFunc = callFunc; };
	void toExtensionsMainLayer(cocos2d::Ref *sender);
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
	void onCellClick(cocos2d::Node* node);
	void setTextNode(cocos2d::Node* node) { m_rootText = node; };	
protected:
	void setTextString();
	char m_keyBoard[60];
	char m_KeyBoardUP[60];
	char m_KeyBoardSign[60];
	char m_keyBoardPress[70];
	cocos2d::ui::Text* m_textInput;
	cocos2d::Node* m_rootText;
	std::string m_inputStr;
	bool m_bSign;
	bool m_bUp;
};
#endif

