#include "cocos2d.h"
#include "epg/EpgList.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
#include "epg/ChannelHeadView.h"
#include "epg/TimeHeadView.h"
#include "common/SkyDialog.h"
#include "tvplayer/CEpgManager.h"
#include "common/common.h"
#include "tvplayer/CChannel.h"
#include "tvplayer/TvPlayer.h"
#include "tvplayer/CEpgManager.h"
#include "tvplayer/CScheduleManager.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
#define CELL_GEIGHT 84
EpgList::EpgList()
{
	this->setName("EpgList");
	m_btnFocused = nullptr;
	m_focusIdx = 0;
	m_focusCol = 0;
	m_focusRow = 0;
	m_gridView = nullptr;
	m_callFunc = nullptr;
	m_bgFocusIdx = 1;
}
EpgList::~EpgList()
{

}
Layer* EpgList::creatLayer(cocos2d::Node* node, Click_CallFun callFunc)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("EpgList");
		if (tuning) {
			return tuning;
		}
		else {
			log("EpgList:create");
			auto ptuning = EpgList::create();
			ptuning->addCallBack(callFunc);
			ptuning->initTableView();
			node->addChild(ptuning);
			return ptuning;
		}
	}
	return nullptr;
}
void EpgList::initTableView()
{
	m_focusIdx = 0;
	int colNum = 20;
	this->setColNum(colNum);
	this->setRowNum(colNum);
	this->setCellNum(400);
	GridView* tableView = GridView::create(this, Size(1544, 500));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::BOTH);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setAnchorPoint(Vec2(0, 0));
	tableView->setPosition(Vec2(376, 76));
	tableView->setColNum(colNum);
	tableView->setRowNum(colNum);
	tableView->setDelegate(this);
	tableView->setName("ID_TABLEVIEW_EPG");
	m_gridView = tableView;	
	this->addChild(tableView);
	tableView->reloadData();
	this->addKeyListener(CC_CALLBACK_2(EpgList::onKeyPressed, this), this);
}
bool EpgList::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		bRet = true;
	} while (0);

	unsigned int channum = Get_TvPlayer()->getLastChannelIndex();
	for (int ii = 0; ii < 7; ii++) {
		CChannel* pcurchan = Get_TvPlayer()->getChannel(channum);
		if (pcurchan) {
			log("###############EpgList getepg:%d ###############",ii);
			m_channelVec.push_back(pcurchan->getName());
			Channel curchan = pcurchan->get();
			CEpgManager::getInstance()->start(curchan);
			m_epgChNo.push_back(channum);
			CEpgManager::getInstance()->getEventAll(curchan, m_epgEvents[ii]);
		}
		channum++;
	}

	auto rootNode = CSLoader::createNode("epg.csb");
	rootNode->setName("ID_LAYER_EPG_BG");
	this->addChild(rootNode);

	ChannelHeadView* chanhead = ChannelHeadView::create();
	chanhead->setName("ID_LAYER_CHANHEAD");
	this->addChild(chanhead);
	m_chanHeader = chanhead;
	chanhead->setEpgEvent(m_channelVec);

	TimeHeadView* timehead = TimeHeadView::create();
	timehead->setName("ID_LAYER_TIMEHEAD");
	this->addChild(timehead);

	return bRet;
}
bool EpgList::onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll)
{
	char list_name[64] = { 0 };
	int nextlist = 0;
	Layout* node = nullptr;
	bool bscroll =  ListFocusLayer::onFocusChanged(next, direction,false);
	switch (direction)
	{
	case cocos2d::ui::Widget::FocusDirection::DOWN:
	{
		nextlist = m_bgFocusIdx + 1;
		sprintf(list_name, "ID_LAY_BG_LIST_%d", nextlist);
		node = (Layout*)this->getChildByName("ID_LAYER_EPG_BG")->getChildByName("ID_LAY_BG")->getChildByName(list_name);
		if (node) {
			node->setBackGroundColorOpacity(124);

			sprintf(list_name, "ID_LAY_BG_LIST_%d", m_bgFocusIdx);
			node = (Layout*)this->getChildByName("ID_LAYER_EPG_BG")->getChildByName("ID_LAY_BG")->getChildByName(list_name);
			node->setBackGroundColorOpacity(0);
			m_bgFocusIdx = nextlist;
		}
	}
	break;
	case cocos2d::ui::Widget::FocusDirection::UP:
	{
		nextlist = m_bgFocusIdx - 1;
		sprintf(list_name, "ID_LAY_BG_LIST_%d", nextlist);
		node = (Layout*)this->getChildByName("ID_LAYER_EPG_BG")->getChildByName("ID_LAY_BG")->getChildByName(list_name);
		if (node) {
			node->setBackGroundColorOpacity(124);

			sprintf(list_name, "ID_LAY_BG_LIST_%d", m_bgFocusIdx);
			node = (Layout*)this->getChildByName("ID_LAYER_EPG_BG")->getChildByName("ID_LAY_BG")->getChildByName(list_name);
			node->setBackGroundColorOpacity(0);
			m_bgFocusIdx = nextlist;
		}
	}
		break;
	default:
		break;
	}
	if (bscroll)
	{
		Vec2 offset = m_gridView->scrollToIndex(m_focusIdx);
		TableView* timehead = (TableView*) this->getChildByName("ID_LAYER_TIMEHEAD")->getChildByName("ID_TABLEVIEW_TIMEHEAD");
		Vec2 timeoff = timehead->getContentOffset();
		timeoff.x = offset.x;
		timehead->setContentOffset(timeoff);

		TableView* chanhead = (TableView*) this->getChildByName("ID_LAYER_CHANHEAD")->getChildByName("ID_TABLEVIEW_CHANHEAD");
		Vec2 chanoff = chanhead->getContentOffset();
		chanoff.y = offset.y;
		chanhead->setContentOffset(chanoff);
	}
	return true;
}
void EpgList::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{	
	this->stopPropagation(keyCode, unused_event);
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
		if (m_focusIdx % m_colNums == 0) {
			m_bFocus = false;			
			onFocusChanged(m_focusIdx, cocos2d::ui::Widget::FocusDirection::LEFT);
			m_chanHeader->requestFocus(m_focusIdx / m_colNums, -1);
		}
		else
			ListFocusLayer::onKeyPressed(keyCode, unused_event);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
		if (!m_bFocus) {			
			m_bFocus = true;
			onFocusChanged(m_focusIdx, cocos2d::ui::Widget::FocusDirection::RIGHT);
			m_chanHeader->requestFocus(-1, m_focusIdx / m_colNums);
		}
		else
		    ListFocusLayer::onKeyPressed(keyCode, unused_event);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_UP:
		if (!m_bFocus) {
			if (m_focusIdx > (m_colNums - 1)) {					
				m_chanHeader->requestFocus((m_focusIdx - m_colNums) / m_colNums, m_focusIdx / m_colNums);
				m_focusIdx -= m_colNums;
				onFocusChanged(m_focusIdx, cocos2d::ui::Widget::FocusDirection::UP);
			}
		}
		else
			ListFocusLayer::onKeyPressed(keyCode, unused_event);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_DOWN:
		if (!m_bFocus) {
			if (m_focusIdx < (m_cellNums - m_colNums)) {					
				m_chanHeader->requestFocus((m_focusIdx + m_colNums) / m_colNums, m_focusIdx / m_colNums);
				m_focusIdx += m_colNums;
				onFocusChanged(m_focusIdx, cocos2d::ui::Widget::FocusDirection::DOWN);
			}
		}
		else
			ListFocusLayer::onKeyPressed(keyCode, unused_event);
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
	case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
		if (!m_bFocus) {
			m_chanHeader->onFavClick();
		}
		else
			ListFocusLayer::onKeyPressed(keyCode, unused_event);
		break;
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
	case EventKeyboard::KeyCode::KEY_BACK:
	case EventKeyboard::KeyCode::KEY_TV_BACK:
	case EventKeyboard::KeyCode::KEY_TV_EXIT:
		//TODO for back
		this->getParent()->removeChild(this);
		break;
	default:
		break;
	}
	
}
void EpgList::toExtensionsMainLayer(cocos2d::Ref *sender)
{
}

void EpgList::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}

Size EpgList::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(300 + (idx % 15) * 10, 84);
}
int EpgList::convertToVisbleRow(int row, cocos2d::extension::TableView *table)
{
	int visbleRow = row;
	const Vec2 offset = table->getContentOffset();
	Size viewsize = table->getViewSize();
	Size contentSize = table->getContentSize();
	int rollRow =(contentSize.height + offset.y - viewsize.height )/ CELL_GEIGHT;
	visbleRow -= rollRow;
	return visbleRow;
}

TableViewCell* EpgList::tableCellAtIndex(TableView *table, ssize_t idx)
{	
	int rows = idx / m_colNums;
	int visbleRow = convertToVisbleRow(rows,table);
	log("tableCellAtIndex,idx:%d,m_focusIdx:%d,rows:%d,visbleRow:%d", idx, m_focusIdx,rows, visbleRow);
	auto string = String::createWithFormat("%ld", idx);
	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new BaseTableViewCell();
		((BaseTableViewCell*)cell)->addBtnlClick((Click_CallFun)&EpgList::onEpgCellClick,this);
		cell->autorelease();
	}
	cell->removeAllChildrenWithCleanup(true);
	if (idx == m_focusIdx && m_bFocus)
	{
		m_focusCell = cell;
		ImageView* focus = ImageView::create("general/general_button_focus.png");
		focus->setScale9Enabled(true);
		Size size = tableCellSizeForIndex(table, idx);
		int w = size.width;
		int h = size.height;
		focus->setContentSize(Size(w + 76, h + 80));
		focus->setPosition(Vec2(w / 2, h / 2 - 27));
		focus->setName("ID_PIC_FOCUS");
		focus->setZOrder(-1);
		cell->addChild(focus);
	}
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
	
	//TODO Ìí¼Óepg view»òÕßrecord×´Ì¬
	bool bSchedule = false;
	bool bScheduleRec = false;
	std::string epgname = "null";
	if ((idx % m_colNums) < m_epgEvents[visbleRow].size())
	{
		if (visbleRow < 7) {
			EpgEvent epge = m_epgEvents[visbleRow].at(idx % m_colNums);
			epgname = epge.eventName;
			bSchedule = epge.bSchedule;
			bScheduleRec = epge.bScheduleRec;
		}
	}
	if (bSchedule)
	{
		Button* schedule = Button::create("epgturning/epg_view.png", "epgturning/epg_view.png", "epgturning/epg_rec.png");
		schedule->setName("ID_BUT_SCHEDULE");
		schedule->setAnchorPoint(Vec2(0, 0.5));
		schedule->setPosition(Vec2(20, 42));
		//TODO add view
		schedule->setEnabled(true);
		cell->addChild(schedule);
	}

	if (bScheduleRec)
	{
		Button* schedule = Button::create("epgturning/epg_view.png", "epgturning/epg_view.png", "epgturning/epg_rec.png");
		schedule->setName("ID_BUT_SCHEDULE");
		//TODO add record
		schedule->setEnabled(false);
		schedule->setAnchorPoint(Vec2(0, 0.5));
		schedule->setPosition(Vec2(20, 42));
		cell->addChild(schedule);
	}

	log("###############EpgList tableCellAtIndex:%d ###############", idx);
	auto label = Label::createWithTTF(epgname, "general/SourceHanSansTWHK-Light.ttf", 32);
	label->setAnchorPoint(Vec2(0.5, 0.5));
	label->setColor(Color3B(91, 91, 91));
	label->setPosition(Vec2(tableCellSizeForIndex(table, idx).width / 2, tableCellSizeForIndex(table, idx).height / 2));
	label->setTag(123);
	cell->addChild(label);
	return cell;
}

ssize_t EpgList::numberOfCellsInTableView(TableView *table)
{
	return 400;
}
void EpgList::onEpgCellClick(cocos2d::Node* node)
{
	Button* btn = (Button*)node->getChildByName("ID_BUT_SCHEDULE");
	if(btn != nullptr) {
		if (btn->isEnabled()) {
			SkyDialog* dia = SkyDialog::create(this, "Dia_Epg_0.csb", (Click_CallFun)(&EpgList::onViewCancel));
		}
		else {
			SkyDialog* dia = SkyDialog::create(this, "Dia_Epg_0.csb", (Click_CallFun)(&EpgList::onRecordCancel));
		}
	}
	else
	    SkyDialog* dia = SkyDialog::create(this, "Dia_Epg_0.csb", (Click_CallFun)(&EpgList::onViewClick), (SEL_CallFuncN)(&EpgList::onRecordClick));
}
void EpgList::onViewClick(cocos2d::Node* node)
{
	Node* cell = m_gridView->cellAtIndex(m_focusIdx);
	if (cell) {
		Button* schedule = Button::create("epgturning/epg_view.png","epgturning/epg_view.png", "epgturning/epg_rec.png");
		schedule->setName("ID_BUT_SCHEDULE");
		schedule->setAnchorPoint(Vec2(0,0.5));
		schedule->setPosition(Vec2(20,42));
		//TODO add view
		schedule->setEnabled(true);
		cell->addChild(schedule);

		int rows = m_focusIdx / m_colNums;
		int visbleRow = convertToVisbleRow(rows, m_gridView);
		if ((m_focusIdx % m_colNums) < m_epgEvents[visbleRow].size())
		{
			if (visbleRow < 7) {
				EpgEvent epge = m_epgEvents[visbleRow].at(m_focusIdx % m_colNums);
				epge.bSchedule = true;
				CChannel* pcurchan = Get_TvPlayer()->getChannel(m_epgChNo.at(visbleRow));
				if (pcurchan)
				{
					log("#################epglist viewadd :%s,name:%s", pcurchan->getNo().c_str(), pcurchan->getName().c_str());
					CScheduleManager::getInstance()->setScheduleView(pcurchan->get(), epge);
				}
			}
		}		
	}
}
void EpgList::onRecordClick(cocos2d::Node* node)
{
	Node* cell = m_gridView->cellAtIndex(m_focusIdx);
	if (cell) {
		Button* schedule = Button::create("epgturning/epg_view.png","epgturning/epg_view.png", "epgturning/epg_rec.png");
		schedule->setName("ID_BUT_SCHEDULE");
		//TODO add record
		schedule->setEnabled(false);
		schedule->setAnchorPoint(Vec2(0, 0.5));
		schedule->setPosition(Vec2(20, 42));
		cell->addChild(schedule);


		int rows = m_focusIdx / m_colNums;
		int visbleRow = convertToVisbleRow(rows, m_gridView);
		if ((m_focusIdx % m_colNums) < m_epgEvents[visbleRow].size())
		{
			if (visbleRow < 7) {
				EpgEvent epge = m_epgEvents[visbleRow].at(m_focusIdx % m_colNums);
				epge.bScheduleRec = true;
				CChannel* pcurchan = Get_TvPlayer()->getChannel(m_epgChNo.at(visbleRow));
				if (pcurchan)
				{
					log("#################epglist recadd :%s,name:%s", pcurchan->getNo().c_str(), pcurchan->getName().c_str());
					CScheduleManager::getInstance()->setScheduleRec(pcurchan->get(), epge);
				}
			}
		}

	}
}
void EpgList::onViewCancel(cocos2d::Node* node)
{
	Node* cell = m_gridView->cellAtIndex(m_focusIdx);
	if (cell) {
		cell->removeChildByName("ID_BUT_SCHEDULE");

		int rows = m_focusIdx / m_colNums;
		int visbleRow = convertToVisbleRow(rows, m_gridView);
		if ((m_focusIdx % m_colNums) < m_epgEvents[visbleRow].size())
		{
			if (visbleRow < 7) {
				EpgEvent epge = m_epgEvents[visbleRow].at(m_focusIdx % m_colNums);
				epge.bSchedule = false;
				CChannel* pcurchan = Get_TvPlayer()->getChannel(m_epgChNo.at(visbleRow));
				if (pcurchan)
				{
					log("#################epglist onViewCancel :%s,name:%s", pcurchan->getNo().c_str(), pcurchan->getName().c_str());
					CScheduleManager::getInstance()->cancelScheduleView(pcurchan->get(), epge);
				}
			}
		}

		//TODO cancel view
	}
}
void EpgList::onRecordCancel(cocos2d::Node* node)
{
	Node* cell = m_gridView->cellAtIndex(m_focusIdx);
	if (cell) {
		cell->removeChildByName("ID_BUT_SCHEDULE");
		//TODO cancel record
		int rows = m_focusIdx / m_colNums;
		int visbleRow = convertToVisbleRow(rows, m_gridView);
		if ((m_focusIdx % m_colNums) < m_epgEvents[visbleRow].size())
		{
			if (visbleRow < 7) {
				EpgEvent epge = m_epgEvents[visbleRow].at(m_focusIdx % m_colNums);
				epge.bScheduleRec = false;
				CChannel* pcurchan = Get_TvPlayer()->getChannel(m_epgChNo.at(visbleRow));
				if (pcurchan)
				{
					log("#################epglist onRecordCancel :%s,name:%s", pcurchan->getNo().c_str(), pcurchan->getName().c_str());
					CScheduleManager::getInstance()->cancelScheduleRec(pcurchan->get(), epge);
				}
			}
		}
	}
}