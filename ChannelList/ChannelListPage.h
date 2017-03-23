#ifndef __CHANNELLISTPAGE_H__
#define __CHANNELLISTPAGE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "extensions/ExtensionExport.h"
#include "ChannelListTableView.h"
#include "ChannelEdit/ElementDisplayList.h"

USING_NS_CC;

enum
{	
	CHLIST_CHLIST_TAG= 0x400,
	CHLIST_TAB_TAG= 0x800,
	CHLIST_LINE_TAG= 0x1200
};

class ChannelListPageView :  public cocos2d::Scene, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    //CREATE_FUNC(ChannelListPageView);
//M by frank.
    //virtual bool init() override;  
    ssize_t cellcurrentPlayedChannelIndex;
    ////TableViewCell* cellcurrentPlayedChannel;
	virtual bool init(ElementDisplayListSystem *edls,ssize_t index,bool is_channellist);

    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view)override {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)override {};
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)override;
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table)override;
	virtual void tableCellHighlight(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual void tableCellUnhighlight(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual void tableCellWillRecycle(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
		
	ssize_t numberofchannels;
	bool* favorite;
	bool* locked;
	bool is_focus_triggered;
	int x_position;
	int y_position;	
    ssize_t cur_idx;
    bool is_channellist;
    ElementDisplayListSystem *edls;
    bool play_or_del;
};

#endif // __CHANNELLISTPAGE_H__

