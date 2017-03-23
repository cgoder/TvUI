#include "epg/ChannelHeadView.h"
#include "common/BaseTableViewCell.h"
using namespace cocos2d;
using namespace cocos2d::ui;
USING_NS_CC_EXT;

bool ChannelHeadView::init()
{
	m_focusIdx = -1;
	TableView* tableView = TableView::create(this, CCSizeMake(376, 500));
	m_tableView = tableView;
	bool isb = tableView->isClippingToBounds();
	tableView->setClippingToBounds(true);
	tableView->setDirection(extension::ScrollView::Direction::VERTICAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setAnchorPoint(Vec2(0, 0));
	tableView->setPosition(ccp(0, 76));
	tableView->setDelegate(this);
	tableView->setName("ID_TABLEVIEW_CHANHEAD");
	this->addChild(tableView);
	//tableView->reloadData();
	m_tableView = tableView;
	return true;
}
void ChannelHeadView::setEpgEvent(std::vector<std::string> channel)
{
	m_channelVec = channel;
	m_tableView->reloadData();
}
void ChannelHeadView::toExtensionsMainLayer(cocos2d::CCObject *sender)
{

}
ssize_t ChannelHeadView::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
	return 20;
}
cocos2d::Size ChannelHeadView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	return Size(376, 84);
}

void ChannelHeadView::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize ChannelHeadView::cellSizeForTable(TableView *table)
{
	return CCSizeMake(376, 84);
}

TableViewCell* ChannelHeadView::tableCellAtIndex(TableView *table, ssize_t idx)
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
	sprite->setPosition(Vec2(tableCellSizeForIndex(table, idx).width - 2, 0));
	cell->addChild(sprite);

	ImageView *sprite1 = ImageView::create("general/split_line_vec.png");
	sprite1->setScale9Enabled(true);
	sprite1->setContentSize(Size(tableCellSizeForIndex(table, idx).width, 2));
	sprite1->setAnchorPoint(Vec2(0, 0));
	sprite1->setPosition(Vec2(0, 0));
	cell->addChild(sprite1);

	ImageView *favsplit = ImageView::create("general/split_line_vec.png");
	favsplit->setScale9Enabled(true);
	favsplit->setContentSize(Size(2, tableCellSizeForIndex(table, idx).height));
	favsplit->setAnchorPoint(Vec2(0, 0));
	favsplit->setPosition(Vec2(296 - 2, 0));
	cell->addChild(favsplit);

	Button* fav = Button::create("general/general_favicon_normal.png", "general/general_favicon.png");
	//TODO set fav fav->sethilighted();
	fav->setAnchorPoint(Vec2(0,0.5));
	fav->setName("ID_BUT_FAV");
	fav->setPosition(Vec2(316,42));
	cell->addChild(fav);

	if (m_focusIdx == idx) {
		ImageView* focus = ImageView::create("general/general_button_focus.png");
		focus->setScale9Enabled(true);
		focus->setName("ID_PIC_FOCUS");
		int w = 80;
		int h = 84;
		focus->setContentSize(Size(w + 76, h + 80));
		focus->setPosition(Vec2(20, -10));
		focus->setZOrder(-1);
		fav->addChild(focus);
	}

	//TODO 添加epg view或者record状态
	std::string epgname = "null";
	if ((idx) < m_channelVec.size())
	{
		epgname = m_channelVec.at(idx);
	}

	auto label = Label::createWithTTF(epgname, "general/SourceHanSansTWHK-Light.ttf", 32);
	label->setColor(Color3B(91, 91, 91));
	label->setAnchorPoint(Vec2(0, 0.5));
	label->setPosition(Vec2(20, tableCellSizeForIndex(table, idx).height / 2));


	label->setName("ID_TEXT_TITLE");
	cell->addChild(label);
	return cell;
}
void ChannelHeadView::requestFocus(int focusIdx, int unFocusIdx)
{
	m_focusIdx = focusIdx;
	if (focusIdx != -1)
	{		
		TableViewCell *cell = m_tableView->cellAtIndex(focusIdx);
		if (cell) {
			Button* btn = (Button*)cell->getChildByName("ID_BUT_FAV");
			btn->removeChildByName("ID_PIC_FOCUS");
			ImageView* focus = ImageView::create("general/general_button_focus.png");
			focus->setScale9Enabled(true);
			focus->setName("ID_PIC_FOCUS");
			int w = 80;
			int h = 84;
			focus->setContentSize(Size(w + 76, h + 80));
			focus->setPosition(Vec2(20, -10));
			focus->setZOrder(-1);
			btn->addChild(focus);
		}
	}
	if (unFocusIdx != -1)
	{
		TableViewCell *cell = m_tableView->cellAtIndex(unFocusIdx);
		if (cell) {
			Button* btn = (Button*)cell->getChildByName("ID_BUT_FAV");
			btn->removeChildByName("ID_PIC_FOCUS");
		}
	}
}
void ChannelHeadView::onFavClick()
{
	if (m_focusIdx != -1)
	{
		TableViewCell *cell = m_tableView->cellAtIndex(m_focusIdx);
		if (cell)
		{
			Button* btn = (Button*)cell->getChildByName("ID_BUT_FAV"); 
			//TODO 根据选择设置喜爱状态
			if (btn->isHighlighted())
				btn->setHighlighted(false);
			else
				btn->setHighlighted(true);
		}
	}
}