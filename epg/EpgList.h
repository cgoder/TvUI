#ifndef  _EPG_LIST_H_
#define  _EPG_LIST_H_
#include "cocos2d.h"
#include "common/common.h"
#include "common/SkyLayer.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
#include "epg/GridView/GridView.h"
#include "common/ListFocusLayer.h"
#include "epg/ChannelHeadView.h"
#include "tvplayer/CEpgEvent.h"
typedef void (cocos2d::Ref::*Click_CallFun)(cocos2d::Node* node);
class EpgList :
	public ListFocusLayer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
	EpgList();
	~EpgList();
	virtual bool init();
	void initTableView();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node, Click_CallFun callFunc = nullptr);
	CREATE_FUNC(EpgList);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);
	virtual bool onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll = true);
	void addCallBack(Click_CallFun callFunc) { m_callFunc = callFunc; };
	void toExtensionsMainLayer(cocos2d::Ref *sender);
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
	void onEpgCellClick(cocos2d::Node* node);
	void onViewClick(cocos2d::Node* node);
	void onRecordClick(cocos2d::Node* node);
	void onViewCancel(cocos2d::Node* node);
	void onRecordCancel(cocos2d::Node* node);
	int convertToVisbleRow(int row, cocos2d::extension::TableView *table);
protected:
	ChannelHeadView* m_chanHeader;
	int m_bgFocusIdx;

	std::vector<EpgEvent> m_epgEvents[8];
	std::vector<int> m_epgChNo;
	std::vector<std::string> m_channelVec;
};
#endif

