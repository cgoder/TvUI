#ifndef __CHANNELLIST_PAGE_RECORDED_H__
#define __CHANNELLIST_PAGE_RECORDED_H__


#include "ChannelListPage.h"
#include "tvplayer/CCPvrManager.h"


#include "rec/PVRRecordDB.h"



class ChannelListPageRecorded : public ChannelListPageView
{
public:
	virtual bool init(ElementDisplayListSystem *edls,ssize_t index,bool is_channellist);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table)override;

private:
	
	PVRRecordDB* recordDB;
	std::vector<PVRRecordInfo> pvrlist;

};

#endif // __CHANNELLIST_PAGE_RECORDED_H__

