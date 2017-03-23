#ifndef __CHANNELLISTABLEVIEW_H__
#define __CHANNELLISTABLEVIEW_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "extensions/ExtensionExport.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ChannelListTableView : public TableView
{
public:
	static ChannelListTableView* create(TableViewDataSource* dataSource, Size size);
	void scrollToIndex(int index);
};

#endif // __CHANNELLISTABLEVIEW_H__

