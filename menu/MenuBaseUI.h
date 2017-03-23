#ifndef  _MenuBaseUI_H_
#define  _MenuBaseUI_H_
#include "cocos2d.h"
#include "common/common.h"
#include "common/SkyLayer.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
#include "epg/GridView/GridView.h"
#include "common/ListFocusLayer.h"
#include "menu/MenuControl.h"
#include "menu/MenuResponse.h"
#include "tinyxml2/tinyxml2.h"
class MenuBaseUI :
	public ListFocusLayer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
	MenuBaseUI();
	~MenuBaseUI();
	virtual bool init();
	void addResponse(MenuResponse* response) { m_response = response; };
	void initTableView(const std::string &xml);
	static cocos2d::Layer* creatLayer(cocos2d::Node* node,const std::string &xml, MenuResponse* response = nullptr, Click_CallFun callFunc = nullptr);
	virtual bool onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll = true);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);
	void onKeyLeft();
	void onKeyRight();
	void addTitle(const char* str);
	void addNote(const char* str);
	CREATE_FUNC(MenuBaseUI);
	void addCallBack(Click_CallFun callFunc) { m_callFunc = callFunc; };
	//void addChooseStr(std::string str) { m_chooseStr.pushBack(str); };
	void addMenuStr(char* str);
	void toExtensionsMainLayer(cocos2d::Ref *sender);
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
	virtual void onCellClick(cocos2d::Node* node);
	int64_t time_ms(const std::string func,int line);
	void initData(const std::string& filename);
	void parseBg(tinyxml2::XMLElement* ele);
	cocos2d::Node* parseImage(tinyxml2::XMLElement* ele,cocos2d::Node* rootNode = nullptr);
	cocos2d::Node* parseText(tinyxml2::XMLElement* ele, cocos2d::Node* rootNode = nullptr);
	cocos2d::Node* parseButton(tinyxml2::XMLElement* ele, cocos2d::Node* rootNode = nullptr);
	void parseTable(tinyxml2::XMLElement* ele);
	void parseMenu(tinyxml2::XMLElement* ele);
protected:
	bool checkSignal(const std::string signal);
	std::vector<std::string> m_menuNameVec;
	int m_menuIdx;
	MenuResponse* m_response;
	std::vector<MenuControl*> m_menuCtrlVec;
	int m_tempFocusIndex;
	float m_cellWidth;
	float m_cellHeight;
	float m_positionx;
	float m_positiony;
};
#endif

