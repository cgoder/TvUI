#ifndef __CHANNELLIST_PAGE_SCH_VIEWING_H__
#define __CHANNELLIST_PAGE_SCH_VIEWING_H__


#include "ChannelListPage.h"
#include "tvplayer/CScheduleManager.h"

class ChannelListPageSchViewing : public ChannelListPageView
{
public:
	virtual bool init(ElementDisplayListSystem *edls,ssize_t index,bool is_channellist);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table)override;

private:
		
		std::vector<EpgSchedule> schedules;		
};

#endif // __CHANNELLIST_PAGE_SCH_VIEWING_H__

