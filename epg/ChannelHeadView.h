#ifndef __EPG_CHANNELHEAD_SOURCE_H__
#define __EPG_CHANNELHEAD_SOURCE_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "extensions/GUI/CCScrollView/CCTableView.h"
#include "extensions/GUI/CCScrollView/CCTableViewCell.h"
#include "extensions/ExtensionExport.h"
#include "cocos2d.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h" 
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
#include "tvplayer/CEpgEvent.h"
#include <set>
#include <vector>
class ChannelHeadView : public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
	CREATE_FUNC(ChannelHeadView);
	virtual bool init();
	void toExtensionsMainLayer(cocos2d::Object *sender);
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);//Cell大小
	void requestFocus(int focusIdx, int unFocusIdx);

	void setEpgEvent(std::vector<std::string> channel);
	cocos2d::extension::TableView* m_tableView;
	void onFavClick();
protected:
	int m_focusIdx;
	std::vector<std::string> m_channelVec;
};

#endif  // __HELLOWORLD_SCENE_H__