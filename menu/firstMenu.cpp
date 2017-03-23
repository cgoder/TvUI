#include "cocos2d.h"
#include "menu/firstMenu.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
#include "menu/channelMenu.h"
#include "menu/MenuBaseUI.h"
#include "menu/MainResponse.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
firstMenu::firstMenu()
{
	this->setName("firstMenu");
	m_btnFocused = nullptr;
	m_focusIdx = 0;
	m_focusCol = 0;
	m_focusRow = 0;
	m_gridView = nullptr;
	m_callFunc = nullptr;
	m_menuIdx = 0;	
}
firstMenu::~firstMenu()
{	
}

Layer* firstMenu::creatLayer(cocos2d::Node* node, int cols,int rows,int cells,Click_CallFun callFunc)
{
	return MenuBaseUI::creatLayer(node, "xml/menu.xml", new MainResponse());
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("firstMenu");
		if (tuning) {
			return tuning;
		}
		else 
		{
			firstMenu* pRet =(firstMenu*) firstMenu::create();
			pRet->addCallBack(callFunc);
			pRet->setColNum(cols);
			pRet->setRowNum(rows);
			pRet->setCellNum(cells);
			
			pRet->initTableView();
			node->addChild(pRet);
			return pRet;
		}
	}
	return nullptr;
}
void firstMenu::initTableView()
{	
	m_menuName.push_back("Channels");
	m_menuName.push_back("Picture");
	m_menuName.push_back("Audio");
	m_menuName.push_back("Options");
	m_menuName.push_back("Network");
	m_focusIdx = m_rowNums / 2;// (m_rowNums > 2) ? m_rowNums - 2 : m_rowNums;
	int height = 100 * m_rowNums;
	ImageView* bg = ImageView::create("general/general_popup_bg.png");
	bg->setName("ID_PIC_BG");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setOpacity(255);
	//bg->setScaleY(((float)(height + 400))/1080.00);
	bg->setScaleX(((float)376) / 1920.00);
	this->addChild(bg);
	this->setContentSize(Size(376, height));

	GridView* tableView = GridView::create(this, Size(350, height));
	tableView->setClippingToBounds(false);
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
	tableView->setClippingToBounds(false);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setPosition(Vec2(20,0));
	tableView->setColNum(m_colNums);
	tableView->setRowNum(m_rowNums);
	tableView->setDelegate(this);
	m_gridView = tableView;
	this->addChild(tableView);
	tableView->reloadData();

	tableView->scrollStep(m_focusIdx, cocos2d::ui::Widget::FocusDirection::DOWN);
}
bool firstMenu::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		bRet = true;
	} while (0);
	
	this->addKeyListener(CC_CALLBACK_2(ListFocusLayer::onKeyPressed, this), this);
	return bRet;
}
void firstMenu::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	BaseTableViewCell* cell = nullptr;
	this->stopPropagation(keyCode, unused_event);
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ENTER:
	case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
		cell = dynamic_cast<BaseTableViewCell*> (m_gridView->cellAtIndex(m_focusIdx));
		if (m_callFunc)
		{
			(this->getParent()->*m_callFunc)(this);
		}
		else
		{
			if (cell)
				cell->onCellClick();
		}
		break;
	default:
		ListFocusLayer::onKeyPressed(keyCode, unused_event);
		break;
	}
}
bool firstMenu::onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll )
{
	ListFocusLayer::onFocusChanged(next, direction, false);
	if (isscroll)
	{
		if (direction == cocos2d::ui::Widget::FocusDirection::UP)
			m_gridView->scrollStep(1, cocos2d::ui::Widget::FocusDirection::UP);
		if (direction == cocos2d::ui::Widget::FocusDirection::DOWN)
			m_gridView->scrollStep(1, cocos2d::ui::Widget::FocusDirection::DOWN);
	}
	return false;
}
void firstMenu::addTitle(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 60);
	text->setAnchorPoint(Vec2(0, 0));
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(87,947));
	this->addChild(text);
}
void firstMenu::addNote(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 32);
	text->setColor(Color3B(153, 153, 153));
	text->setAnchorPoint(Vec2(0, 0));
	text->setPosition(Vec2(387,964));
	this->addChild(text);
}
void firstMenu::toExtensionsMainLayer(cocos2d::Ref *sender)
{
}

void firstMenu::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}

Size firstMenu::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(320, 100);
}

TableViewCell* firstMenu::tableCellAtIndex(TableView *table, ssize_t idx)
{
	log("tableCellAtIndex,idx:%d,m_focusIdx:%d", idx, m_focusIdx);
	TableViewCell *cell = table->dequeueCell();
	//if (idx < m_menuIdx)
	{	
		if (!cell) {
			cell = new BaseTableViewCell();
			((BaseTableViewCell*)cell)->addBtnlClick((Click_CallFun)&firstMenu::onCellClick, this);
			cell->autorelease();
		}
		cell->removeAllChildrenWithCleanup(true);
		char normalname[64];
		int sourceidx = idx + 1;
		if (idx > 8)
			sourceidx = 1;
		sprintf(normalname, "menu/first_normal_%d.png", sourceidx);
		char focusname[64];
		sprintf(focusname, "menu/first_focus_%d.png", sourceidx);
		Button* btn = Button::create(normalname, focusname);
		Size size = tableCellSizeForIndex(table, idx);
		int w = size.width;
		int h = size.height;
		btn->setTitleText("");
		btn->setName("ID_BUT_ICON");
		btn->setAnchorPoint(Vec2(0.5, 0.5));
		btn->setPosition(Vec2(w / 2 - 50, h / 2));
		btn->setZOrder(2);
		cell->addChild(btn);		
		if (idx == m_focusIdx)
		{
			m_focusCell = cell;
			ImageView* focus = ImageView::create("general/general_button_focus.png");
			focus->setScale9Enabled(true);		
			focus->setContentSize(Size(w + 76, h + 80));
			focus->setPosition(Vec2(w / 2, h / 2 - 27));
			focus->setName("ID_PIC_FOCUS");
			cell->addChild(focus);
			btn->setHighlighted(true);
		}
		auto text = Text::create(m_menuName.at(idx), "general/SourceHanSansTWHK-Light.ttf", 32);
		//Lable::createWithTTF(m_menuStr[idx], "general/SourceHanSansTWHK-Light.ttf", 32);
		//text->setAnchorPoint(Vec2(0, 0));
		text->setColor(Color3B(91, 91, 91));
		text->setAnchorPoint(Vec2(0,0.5));
		text->setPosition(Vec2(150, h/2));
		text->setName("ID_TEXT_NAME");
		text->setZOrder(2);
		cell->addChild(text);
	}
	return cell;
}

ssize_t firstMenu::numberOfCellsInTableView(TableView *table)
{
	return m_cellNums;
}
void firstMenu::onCellClick(cocos2d::Node* node)
{
	BaseTableViewCell* cell = dynamic_cast<BaseTableViewCell*> (m_gridView->cellAtIndex(m_focusIdx));
	
	Layer* layer = nullptr;
	switch (m_focusIdx)
	{
	case 0:
		((Button*)cell->getChildByName("ID_BUT_ICON"))->setHighlighted(false);
		cell->removeChildByName("ID_PIC_FOCUS");
		this->getChildByName("ID_PIC_BG")->setScaleX(750.00 / 1920.00);
		layer = channelMenu::creatLayer(this, 1, 5, 5, (Click_CallFun)&firstMenu::onChildMenuBack);
		layer->setAnchorPoint(Vec2(0, 0.5));
		layer->setPosition(350, 70);
		break;
	case 1:
		break;
	}	
}
void firstMenu::onChildMenuBack(cocos2d::Node* node)
{
	this->getChildByName("ID_PIC_BG")->setScaleX(376.00 / 1920.00);
	onFocusChanged(m_focusIdx, cocos2d::ui::Widget::FocusDirection::DOWN, false);
}