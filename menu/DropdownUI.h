#ifndef  _DropdownUI_H_
#define  _DropdownUI_H_
#include "cocos2d.h"
#include "common/common.h"
#include "common/SkyLayer.h"
#include "common/ListFocusLayer.h"
#include "extensions/cocos-ext.h"
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
#include "menu/MenuControl.h"
#include "menu/MenuResponse.h"
#include "tinyxml2/tinyxml2.h"
class DropdownUI :
	public ListFocusLayer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
	DropdownUI();
	~DropdownUI();
	virtual bool init();
	void addResponse(MenuResponse* response) { m_response = response; };
	void addMenuControl(std::vector<MenuControl*> menuVec, MenuControl* menu);
	void initTableView(cocos2d::Size cellSize, cocos2d::Size tableSize, cocos2d::Vec2 position);
	static cocos2d::Layer* creatLayer(cocos2d::Node* node, cocos2d::Size cellSize, cocos2d::Size tableSize, cocos2d::Vec2 position, std::vector<MenuControl*> menuVec, MenuControl* menu, MenuResponse* response = nullptr, Click_CallFun callFunc = nullptr);
	virtual bool onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll = true);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);
	void onKeyLeft();
	void onKeyRight();
	void addTitle(const char* str);
	void addNote(const char* str);
	CREATE_FUNC(DropdownUI);
	void addCallBack(Click_CallFun callFunc) { m_callFunc = callFunc; };
	void addMenuStr(const char* str, std::vector<std::string> menuvec);
	void toExtensionsMainLayer(cocos2d::Ref *sender);
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
	virtual void onCellClick(cocos2d::Node* node);

protected:
	void onKeyBack();
	std::vector<std::string> m_menuNameVec;
	int m_menuIdx;
	MenuResponse* m_response;
	std::vector<MenuControl*> m_menuCtrlVec;
	MenuControl* m_menu;
	float m_cellWidth;
	float m_cellHeight;
	float m_positionx;
	float m_positiony;
};
#endif

