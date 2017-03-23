
#include "ChannelListTableView.h"

USING_NS_CC;
USING_NS_CC_EXT;

void ChannelListTableView::scrollToIndex(int index) {  
	Vec2 offset = Vec2(0.0, 0.0) - _offsetFromIndex(index);//ccpSub(/*CCPointZero*/ Vec2(0.0, 0.0), _offsetFromIndex(index));
    float newX, newY;  
	Vec2 maxInset, minInset;
      
    maxInset = this->maxContainerOffset();  
    minInset = this->minContainerOffset();  
      
    //check to see if offset lies within the inset bounds  
    newX     = MIN(offset.x, maxInset.x);  
    newX     = MAX(newX, minInset.x);  
    newY     = MIN(offset.y, maxInset.y);  
    newY     = MAX(newY, minInset.y);  
      
	setContentOffset(Vec2(newX, newY), false);
}  


ChannelListTableView* ChannelListTableView::create(TableViewDataSource* dataSource, Size size)
{
	TableView* tableView = TableView::create(dataSource, size);
	return (ChannelListTableView*)tableView;
}

