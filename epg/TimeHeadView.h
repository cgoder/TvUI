#ifndef __EPG_TIMEHEAD_SOURCE_H__
#define __EPG_TIMEHEAD_SOURCE_H__

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
#include <set>
#include <vector>
class TimeHeadView : public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
	CREATE_FUNC(TimeHeadView);
	virtual bool init();

	void toExtensionsMainLayer(cocos2d::Object *sender);
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);//Cell大小
};


#endif  // __HELLOWORLD_SCENE_H__