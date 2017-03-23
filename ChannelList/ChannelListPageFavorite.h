#ifndef __CHANNELLISTPAGEFAVORITE_H__
#define __CHANNELLISTPAGEFAVORITE_H__


#include "ChannelListPage.h"


class ChannelListPageViewFavorite : public ChannelListPageView
{
public:
	virtual bool init(ElementDisplayListSystem *edls,ssize_t index,bool is_channellist);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table)override;

private:
		std::vector<CChannel*> favCh;
};

#endif // __CHANNELLISTPAGEFAVORITE_H__

