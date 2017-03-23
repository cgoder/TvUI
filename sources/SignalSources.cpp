#include "cocos2d.h"
#include "sources/SignalSources.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
//#include "sources/noSignal.h"
#include "tvplayer/tv_common.h"
#include "localMedia/localMedia.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
SignalSources::SignalSources()
{	
	this->setName("SignalSources");
	m_btnFocused = nullptr;
	m_focusIdx = 0;
	m_focusCol = 0;
	m_focusRow = 0;
	m_gridView = nullptr;
	m_callFunc = nullptr;
}
SignalSources::~SignalSources()
{

}

Layer* SignalSources::creatLayer(cocos2d::Node* node,Click_CallFun callFunc)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("SignalSources");
		if (tuning) {
			return tuning;
		}
		else {
			log("AutoTuning:ceart");
			SignalSources* pRet =(SignalSources*) SignalSources::create();
			pRet->setAnchorPoint(Vec2(0, 0));
			pRet->setPosition(Vec2(0,0));
			pRet->addCallBack(callFunc);
			pRet->setColNum(11);
			pRet->setRowNum(1);
			pRet->setCellNum(11);
			pRet->initTableView();
			node->addChild(pRet);
			return pRet;
		}
	}
	return nullptr;
}
void SignalSources::initTableView()
{
#ifndef WIN32
	SKYTV_INPUT_SOURCE_TYPE type = skyTvMw::getInstance()->getInputSource();
	switch (type)
	{
	case SKYTV_INPUT_SOURCE_HDMI1:
		m_focusIdx = 0;
		break;
	case SKYTV_INPUT_SOURCE_STORAGE:
		m_focusIdx = 1;
		break;
	case SKYTV_INPUT_SOURCE_DVBT:
		m_focusIdx = 2;
		break;
	case SKYTV_INPUT_SOURCE_ATV:
		m_focusIdx = 3;
		break;
	case SKYTV_INPUT_SOURCE_DVBC:
		m_focusIdx = 4;
		break;
	case SKYTV_INPUT_SOURCE_YPBPR:
		m_focusIdx = 5;
		break;
	case SKYTV_INPUT_SOURCE_CVBS:
		m_focusIdx = 6;
		break;
	case SKYTV_INPUT_SOURCE_VGA:
		m_focusIdx = 7;
		break;
	case SKYTV_INPUT_SOURCE_DVBS:
		m_focusIdx = 8;
		break;
	case SKYTV_INPUT_SOURCE_HDMI2:
		m_focusIdx = 9;
		break;
	case SKYTV_INPUT_SOURCE_HDMI3:
		m_focusIdx = 10;
		break;
	}
#endif
	int height = 84 * m_rowNums;
	GridView* tableView = GridView::create(this, Size(1870, 320));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
	tableView->setClippingToBounds(false);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setAnchorPoint(Vec2(0, 0));
	tableView->setPosition(Vec2(50, 50));
	tableView->setColNum(m_colNums);
	tableView->setRowNum(m_rowNums);
	tableView->setDelegate(this);
	tableView->setName("ID_TABLEVIEW_CHOOSE");
	m_gridView = tableView;
	this->addChild(tableView);
	tableView->reloadData();
	if (m_focusIdx > 5)
	    tableView->scrollStep(m_focusIdx - 4 , cocos2d::ui::Widget::FocusDirection::RIGHT);
}
bool SignalSources::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		bRet = true;
	} while (0);
	m_sourceName.push_back("HDMI 1");
	m_sourceName.push_back("USB");
	m_sourceName.push_back("DVB_T");
	m_sourceName.push_back("ATV");
	m_sourceName.push_back("CABLE");
	m_sourceName.push_back("分量");
	m_sourceName.push_back("AV");
	m_sourceName.push_back("VGA");
	m_sourceName.push_back("DVB_S");
	m_sourceName.push_back("HDMI 2");
	m_sourceName.push_back("HDMI 3");
	this->setContentSize(Size(1920,370));
	ImageView* bg = ImageView::create("general/general_popup_bg.png");
	//bg->setFlippedY(true);
	bg->setScaleY(0.342);
	bg->setAnchorPoint(Vec2(0,0));
	bg->setPosition(Vec2(0,0));
	this->addChild(bg);
		
	this->addKeyListener(CC_CALLBACK_2(SignalSources::onKeyPressed, this), this);
	
	return bRet;
}
void SignalSources::addTitle(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 60);
	text->setAnchorPoint(Vec2(0, 0));
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(87,947));
	this->addChild(text);
}
void SignalSources::addNote(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 32);
	text->setColor(Color3B(153, 153, 153));
	text->setAnchorPoint(Vec2(0, 0));
	text->setPosition(Vec2(387,964));
	this->addChild(text);
}
void SignalSources::toExtensionsMainLayer(cocos2d::Ref *sender)
{
}

void SignalSources::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}

Size SignalSources::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(280, 310);
}

TableViewCell* SignalSources::tableCellAtIndex(TableView *table, ssize_t idx)
{
	log("tableCellAtIndex,idx:%d,m_focusIdx:%d", idx, m_focusIdx);
	TableViewCell *cell = table->dequeueCell();
	{	
		if (!cell) {
			cell = new BaseTableViewCell();
			((BaseTableViewCell*)cell)->addBtnlClick((Click_CallFun)&SignalSources::onCellClick, this);
			cell->autorelease();
		}
		cell->removeAllChildrenWithCleanup(true);
		Size size = tableCellSizeForIndex(table, idx);
		int w = size.width;
		int h = size.height;
		char normalname[64];
		int sourceidx = idx + 1;
		if (idx > 8)
			sourceidx = 1; 
		sprintf(normalname,"sources/source_normal_%d.png", sourceidx);
		char focusname[64];
		sprintf(focusname, "sources/source_focus_%d.png", sourceidx);
		Button* btn = Button::create(normalname, focusname);
		btn->setPosition(Vec2(140,167));
		cell->addChild(btn);
		auto text = Text::create(m_sourceName.at(idx), "general/SourceHanSansTWHK-Light.ttf", 40);
		text->setAnchorPoint(Vec2(0.5, 0.5));
		text->setColor(Color3B(153, 153, 153));
		text->setPosition(Vec2(w/2, 40));
		text->setName("ID_TEXT_TITLE");
		text->setZOrder(2);
		cell->addChild(text);
		if (m_focusIdx == idx)
		{
			btn->setHighlighted(true);
			text->setColor(Color3B(0, 0, 0));
			ImageView* focus = ImageView::create("sources/shadow.png");
			focus->setName("ID_PIC_FOCUS");
			focus->setPosition(Vec2(140, 167));
			focus->setZOrder(-1);
			cell->addChild(focus);	

			ImageView* select = ImageView::create("sources/green_selected.png");
			Size size = text->getContentSize();
			select->setPosition(Vec2(-12, size.height/2));
			select->setName("ID_PIC_SELECT");
			text->addChild(select);
		}
	}
	return cell;
}

ssize_t SignalSources::numberOfCellsInTableView(TableView *table)
{
	return m_cellNums;
}
void SignalSources::onCellClick(cocos2d::Node* node)
{
	auto scene = Director::getInstance()->getRunningScene();
	switch (m_focusIdx)
	{
	case 0:
		skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_HDMI1);
		break;
	case 1:
		skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_STORAGE);
		localMedia::creatLayer(scene);
		break;
	case 2:
		skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_DVBT);
		break;
	case 3:
		skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_ATV);
		break;
	case 4:
		skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_DVBC);
		break;
	case 5:
		skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_YPBPR);
		break;
	case 6:
		skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_CVBS);
		break;
	case 7:
		skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_VGA);
		break;
	case 8:
		skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_DVBS);
		break;
	case 9:
		skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_HDMI2);
		break;
	case 10:
		skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_HDMI3);
		break;
	}
//	noSignal::creatLayer(this->getParent());
	this->getParent()->removeChild(this);
}

void SignalSources::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	 ListFocusLayer::onKeyPressed(keyCode, unused_event);
}
bool SignalSources::onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll)
{
	GridView* table = m_gridView;
	TableViewCell* cell = table->cellAtIndex(next);
	TableViewCell* prev = table->cellAtIndex(m_focusIdx);
	if (prev) {
		prev->removeChildByName("ID_PIC_FOCUS");
		Node *text = prev->getChildByName("ID_TEXT_TITLE");
		text->removeChildByName("ID_PIC_SELECT");

		Vector<cocos2d::Node*> pChildren = prev->getChildren();
		for (Node *node : pChildren)
		{
			if (dynamic_cast<Button*>(node))
			{
				((Button*)node)->setHighlighted(false);
			}
			else if (dynamic_cast<Text*>(node))
			{
				((Text*)node)->setColor(Color3B(153, 153, 153));
			}
		}
	}
	if (cell)
	{
		m_focusCell = cell;
		if (m_bFocus) {
			Vector<cocos2d::Node*> pChildren = cell->getChildren();
			for (Node *node : pChildren)
			{
				if (dynamic_cast<Button*>(node))
				{
					((Button*)node)->setHighlighted(true);
				}
				else if (dynamic_cast<Text*>(node))
				{
					((Text*)node)->setColor(Color3B(0,0,0));
				}
			}
			ImageView* focus = ImageView::create("sources/shadow.png");
			focus->setName("ID_PIC_FOCUS");
			focus->setPosition(Vec2(140, 167));
			focus->setZOrder(-1);
			cell->addChild(focus);
			ImageView* select = ImageView::create("sources/green_selected.png");
			Node *text = cell->getChildByName("ID_TEXT_TITLE");
			Size size = text->getContentSize();
			select->setName("ID_PIC_SELECT");
			select->setPosition(Vec2(-12, size.height / 2));
			text->addChild(select);
		}
		log("next:%d,focusidx:%d", next, m_focusIdx);
		m_focusIdx = next;
	}
	if (!(cell && table->isIdxVisible(cell, next)))
	{
		m_focusIdx = next;
		if (isscroll)
			table->scrollToIndex(m_focusIdx);
		return true;
	}
	return false;
}