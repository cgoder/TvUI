#include "cocos2d.h"
#include "menu/MenuLayer.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
MenuLayer::MenuLayer()
{
	m_btnFocused = nullptr;
	m_focusIdx = 0;
	m_focusCol = 0;
	m_focusRow = 0;
	m_gridView = nullptr;
	m_callFunc = nullptr;
	m_menuIdx = 0;
}
MenuLayer::~MenuLayer()
{
	
}
void MenuLayer::addMenuStr(char* str)
{
	m_menuNameVec.push_back(str);
	m_menuIdx++;
}

Layer* MenuLayer::creatLayer(cocos2d::Node* node, int cols,int rows,int cells,Click_CallFun callFunc)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("MenuLayer");
		if (tuning) {
			return tuning;
		}
		else {
			MenuLayer* pRet =(MenuLayer*) MenuLayer::create();
			pRet->addCallBack(callFunc);
			pRet->setColNum(cols);
			pRet->setRowNum(rows);
			pRet->setCellNum(cells);
			node->addChild(pRet);
			return pRet;
		}
	}
	return nullptr;
}
void MenuLayer::initTableView()
{	
	m_focusIdx = m_rowNums / 2;// (m_rowNums > 2) ? m_rowNums - 2 : m_rowNums;
	int height = 84 * m_rowNums;

	this->setContentSize(Size(376, height));
	ImageView* arrow = ImageView::create("channellist/channellist_turnleft.png");
	arrow->setPosition(Vec2(0, height - 42));
	this->addChild(arrow);

	GridView* tableView = GridView::create(this, Size(376, height));
	tableView->setClippingToBounds(false);
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
	tableView->setClippingToBounds(false);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setPosition(Vec2(50, 0));
	tableView->setColNum(m_colNums);
	tableView->setRowNum(m_rowNums);
	tableView->setDelegate(this);
	m_gridView = tableView;
	this->addChild(tableView);
	tableView->reloadData();

	tableView->scrollStep(m_focusIdx, cocos2d::ui::Widget::FocusDirection::DOWN);
}
bool MenuLayer::init()
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
void MenuLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	BaseTableViewCell* cell = nullptr;
	this->stopPropagation(keyCode, unused_event);
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ENTER:
	case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
		cell = dynamic_cast<BaseTableViewCell*> (m_gridView->cellAtIndex(m_focusIdx));
		if (cell)
			cell->onCellClick();
		break;
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
	case EventKeyboard::KeyCode::KEY_BACK:
	case EventKeyboard::KeyCode::KEY_TV_BACK:
	case EventKeyboard::KeyCode::KEY_TV_EXIT:
		//TODO for back
		if (m_callFunc)
		{
			(this->getParent()->*m_callFunc)(this);
		}
		this->getParent()->removeChild(this);
		break;
	default:
		ListFocusLayer::onKeyPressed(keyCode, unused_event);
		break;
	}
}
bool MenuLayer::onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll )
{
	ListFocusLayer::onFocusChanged(next, direction, false);
	if (direction == cocos2d::ui::Widget::FocusDirection::UP)
	    m_gridView->scrollStep(1, cocos2d::ui::Widget::FocusDirection::UP);
	if (direction == cocos2d::ui::Widget::FocusDirection::DOWN)
		m_gridView->scrollStep(1, cocos2d::ui::Widget::FocusDirection::DOWN);
	return false;
}
void MenuLayer::addTitle(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 60);
	text->setAnchorPoint(Vec2(0, 0));
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(87,947));
	this->addChild(text);
}
void MenuLayer::addNote(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 32);
	text->setColor(Color3B(153, 153, 153));
	text->setAnchorPoint(Vec2(0, 0));
	text->setPosition(Vec2(387,964));
	this->addChild(text);
}
void MenuLayer::toExtensionsMainLayer(cocos2d::Ref *sender)
{
}

void MenuLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}

Size MenuLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(310, 84);
}

TableViewCell* MenuLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
	log("tableCellAtIndex,idx:%d,m_focusIdx:%d", idx, m_focusIdx);
	TableViewCell *cell = table->dequeueCell();
	//if (idx < m_menuIdx)
	{	
		if (!cell) {
			cell = new BaseTableViewCell();
			((BaseTableViewCell*)cell)->addBtnlClick((Click_CallFun)&MenuLayer::onCellClick, this);
			cell->autorelease();
		}
		cell->removeAllChildrenWithCleanup(true);
		Size size = tableCellSizeForIndex(table, idx);
		int w = size.width;
		int h = size.height;
		Button* btn = Button::create("broadcast/broadcast_listbutton_normal.png", "broadcast/broadcast_listbutton_bg.png", "broadcast/broadcast_listbutton_focus.png");
		btn->setTitleText("");
		btn->setPosition(Vec2(50, h/2));
		btn->setZOrder(2);
		cell->addChild(btn);		
		if (idx == 0)
			btn->setEnabled(false);
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
		auto text = Text::create(m_menuNameVec.at(idx), "general/SourceHanSansTWHK-Light.ttf", 32);
		text->setColor(Color3B(91, 91, 91));
		text->setAnchorPoint(Vec2(0,0.5));
		text->setPosition(Vec2(90, h/2));
		text->setName("ID_TEXT_NAME");
		text->setZOrder(2);
		cell->addChild(text);
	}
	return cell;
}

ssize_t MenuLayer::numberOfCellsInTableView(TableView *table)
{
	return m_cellNums;
}

void MenuLayer::onCellClick(cocos2d::Node* node)
{

}