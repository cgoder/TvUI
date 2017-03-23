#ifndef __CHANNELLIST_PAGE_SCH_RECORDING_H__
#define __CHANNELLIST_PAGE_SCH_RECORDING_H__


#include "ChannelListPage.h"
#include "tvplayer/CScheduleManager.h"

class ChannelListPageSchRecording : public ChannelListPageView
{
public:
	virtual bool init(ElementDisplayListSystem *edls,ssize_t index,bool is_channellist);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table)override;

private:
		std::vector<EpgSchedule> schedules;	
};

#endif // __CHANNELLIST_PAGE_SCH_RECORDING_H__

