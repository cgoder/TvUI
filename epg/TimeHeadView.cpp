#include "epg/TimeHeadView.h"
#include "common/BaseTableViewCell.h"
using namespace cocos2d;
using namespace cocos2d::ui;
USING_NS_CC_EXT;

bool TimeHeadView::init()
{
	TableView* tableViewtime = TableView::create(this, CCSizeMake(1544, 70));
	tableViewtime->setDirection(extension::ScrollView::Direction::HORIZONTAL);
	tableViewtime->setAnchorPoint(Vec2(0, 0));
	tableViewtime->setPosition(ccp(376, 576));
	tableViewtime->setDelegate(this);
	tableViewtime->setName("ID_TABLEVIEW_TIMEHEAD");
	this->addChild(tableViewtime);
	tableViewtime->reloadData();

	return true;
}

void TimeHeadView::toExtensionsMainLayer(cocos2d::CCObject *sender)
{

}
ssize_t TimeHeadView::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
	return 20;
}
cocos2d::Size TimeHeadView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	return Size(386, 70);
}

void TimeHeadView::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize TimeHeadView::cellSizeForTable(TableView *table)
{
	return CCSizeMake(60, 60);
}

TableViewCell* TimeHeadView::tableCellAtIndex(TableView *table, ssize_t idx)
{
	auto string = String::createWithFormat("%ld", idx);
	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new BaseTableViewCell();
		cell->autorelease();
	}
	cell->removeAllChildrenWithCleanup(true);

	ImageView *sprite = ImageView::create("general/split_line_vec.png");
	sprite->setScale9Enabled(true);
	sprite->setContentSize(Size(2, tableCellSizeForIndex(table, idx).height));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(tableCellSizeForIndex(table, idx).width -2, 0));
	cell->addChild(sprite);

	ImageView *sprite1 = ImageView::create("general/split_line_vec.png");
	sprite1->setScale9Enabled(true);
	sprite1->setContentSize(Size(tableCellSizeForIndex(table, idx).width, 2));
	sprite1->setAnchorPoint(Vec2(0, 0));
	sprite1->setPosition(Vec2(0, 0));
	cell->addChild(sprite1);

	auto label = Label::createWithTTF(string->getCString(), "general/SourceHanSansTWHK-Light.ttf", 32);
	label->setColor(Color3B(91, 91, 91));
	label->setAnchorPoint(Vec2(0.5, 0.5));
	label->setPosition(Vec2(tableCellSizeForIndex(table, idx).width / 2, tableCellSizeForIndex(table, idx).height / 2));
	label->setTag(123);
	cell->addChild(label);
	return cell;
}