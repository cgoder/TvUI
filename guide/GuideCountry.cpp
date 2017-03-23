#include "cocos2d.h"
#include "guide/GuideCountry.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
#include "tvScene.h"
#include "guide/GuideSource.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
#define CELL_FOCUS_WIDTH 270.00
#define CELL_FOCUS_HEIGHT 70.00
#define CELL_WIDTH 270
#define CELL_HEIGHT 70


GuideCountry::GuideCountry()
{
	m_btnFocused = nullptr;
	m_focusIdx = 0;
	m_focusCol = 0;
	m_focusRow = 0;
	m_gridView = nullptr;
	m_callFunc = nullptr;
	m_menuIdx = 0;
}
GuideCountry::~GuideCountry()
{
	
}
void GuideCountry::addMenuStr(char* str)
{
	m_menuNameVec.push_back(str);
	m_menuIdx++;
}

Layer* GuideCountry::creatLayer(cocos2d::Node* node, int cols,int rows,int cells,Click_CallFun callFunc)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("GuideCountry");
		if (tuning) {
			return tuning;
		}
		else {
			GuideCountry* pRet =(GuideCountry*) GuideCountry::create();
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
void GuideCountry::initTableView()
{	
	//addNumsText(m_countryVec.size());
	if (m_cellNums == 0)
	{
		ImageView* sorry = ImageView::create("localMedia/sorry.png");
		sorry->setName("ID_PIC_SORRY");
		sorry->setPosition(Vec2(1920 / 2, 1080 / 2));
		this->addChild(sorry);
		Text* sorry_t = Text::create("no country", "general/SourceHanSansTWHK-Light.ttf", 32);
		sorry_t->setPosition(Vec2(1920 / 2, 1080 / 2 - 100));
		sorry_t->setColor(Color3B(153, 153, 153));
		sorry_t->setName("ID_TEXT_SORRY");
		this->addChild(sorry_t);
		this->addKeyListener(CC_CALLBACK_2(ListFocusLayer::onKeyPressed, this), this);
		return;
	}
	//m_focusIdx = m_rowNums / 2;// (m_rowNums > 2) ? m_rowNums - 2 : m_rowNums;
	int height = CELL_HEIGHT * m_rowNums;
	GridView* tableView = GridView::create(this, Size(1000, 400));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setAnchorPoint(Vec2(0,0));
	tableView->setPosition(Vec2(410, 300));
	tableView->setColNum(m_colNums);
	tableView->setRowNum(m_rowNums);
	tableView->setDelegate(this);
	m_gridView = tableView;
	this->addChild(tableView);
	tableView->reloadData();
	//addNote(m_countryVec.at(m_focusIdx).c_str());
	this->addKeyListener(CC_CALLBACK_2(ListFocusLayer::onKeyPressed, this), this);
//	tableView->scrollStep(m_focusIdx, cocos2d::ui::Widget::FocusDirection::DOWN);
}
bool GuideCountry::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		bRet = true;
	} while (0);
	
	ImageView* bg = ImageView::create("general/general_bg.png");
	bg->setName("ID_PIC_BG");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0,0));
	this->addChild(bg);

	Text* text = Text::create("You can use TV based on the selected countries time zone.", "general/SourceHanSansTWHK-Light.ttf", 28);
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(990, 995));
	this->addChild(text);

	addTitle("Country Selection");
	ImageView* split = ImageView::create("general/general_listline.png");
	split->setAnchorPoint(Vec2(0,0));
	split->setPosition(Vec2(0,958.15));
	split->setScaleY(2);
	this->addChild(split);
	
	Sprite* sprite = Sprite::create("general/general_popup_bg.png", Rect(185, 192, 1550, 704));
	sprite->setPosition(Vec2(960, 543));
	this->addChild(sprite);

	text = Text::create("Select your country", "general/SourceHanSansTWHK-Light.ttf", 36);
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(950, 775));
	this->addChild(text);
	
	ImageView* btn = ImageView::create("general/general_button_normal.png");
	btn->setName("ID_PIC_BTN");	
	btn->setScale9Enabled(true);	
	btn->setContentSize(Size(150,70));
	btn->setPosition(Vec2(955,88));
	
	text = Text::create("Start", "general/SourceHanSansTWHK-Light.ttf", 28);
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(150/2, 70/2));
	btn->addChild(text);	
	
	this->addChild(btn);
	
	
	ImageView* arrow = ImageView::create("epgturning/epg_arrow_turnleft_normal.png");
	arrow->setName("arrow_turnleft");	
	arrow->setPosition(Vec2(272,472));
	arrow->setVisible(true);	
	this->addChild(arrow);
	arrow = ImageView::create("epgturning/epg_arrow_turnright_normal.png");
	arrow->setName("arrow_turnright");	
	arrow->setPosition(Vec2(1648,472));
	arrow->setVisible(true);	
	this->addChild(arrow);
	
	return bRet;
}
void GuideCountry::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	BaseTableViewCell* cell = nullptr;
	this->stopPropagation(keyCode, unused_event);
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ENTER:
	case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
		if (m_gridView) {
			cell = dynamic_cast<BaseTableViewCell*> (m_gridView->cellAtIndex(m_focusIdx));
			if (cell)
				cell->onCellClick();
		}
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
bool GuideCountry::onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll )
{
	GridView* table = m_gridView;
	//addNote(m_countryVec.at(next).c_str());
	TableViewCell* cell = table->cellAtIndex(next);
	TableViewCell* prev = table->cellAtIndex(m_focusIdx);
	//TODO判断next 是否为有效节点
	if (prev) {
		prev->removeChildByName("ID_PIC_FOCUS");
		Vector<cocos2d::Node*> pChildren = prev->getChildren();
		for (Node *node : pChildren)
		{
			if (dynamic_cast<Button*>(node))
			{
				((Button*)node)->setHighlighted(false);
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
			}
			ImageView* focus = ImageView::create("general/general_button_focus.png");
			focus->setScale9Enabled(true);
			focus->setCapInsets(Rect(40, 16, 135, 73));
			Size size = table->getDataSource()->tableCellSizeForIndex(table, next);
			focus->setName("ID_PIC_FOCUS");
			int w = size.width;
			int h = size.height;
			focus->setContentSize(Size(CELL_FOCUS_WIDTH + 76, CELL_FOCUS_HEIGHT + 80));
			focus->setPosition(Vec2(w / 2, h / 2 - 27));
			focus->setZOrder(-1);
			cell->addChild(focus);
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
void GuideCountry::addTitle(const char* str)
{
	Text* text =(Text*) this->getChildByName("ID_TEXT_TITLE");
	if (text) {
		text->setString(str);
	}
	else {
		text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 60);
		text->setAnchorPoint(Vec2(0, 0.5));
		text->setColor(Color3B(153, 153, 153));
		text->setPosition(Vec2(87, 992));
		text->setName("ID_TEXT_TITLE");
		this->addChild(text);
	}
}
void GuideCountry::addNote(const char* str)
{
	Text* text = (Text*) this->getChildByName("ID_TEXT_NODE");
	if (text) {
		text->setString(str);
	}
	else {
		text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 32);
		text->setColor(Color3B(153, 153, 153));
		text->setAnchorPoint(Vec2(0, 0.5));
		text->setPosition(Vec2(287, 988));
		text->setName("ID_TEXT_NODE");
		this->addChild(text);
	}
}
void GuideCountry::addNumsText(int nums)
{
	char str[64] = { 0 };
	sprintf(str, "%d videos", nums);
	Text* text = (Text*) this->getChildByName("ID_TEXT_NUMS");
	if (text) {
		text->setString(str);
	}
	else {
		text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 32);
		text->setColor(Color3B(153, 153, 153));
		text->setAnchorPoint(Vec2(1, 0.5));
		text->setPosition(Vec2(1800, 988));
		text->setName("ID_TEXT_NUMS");
		this->addChild(text);
	}
}
void GuideCountry::toExtensionsMainLayer(cocos2d::Ref *sender)
{
}

void GuideCountry::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}

Size GuideCountry::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(CELL_WIDTH, CELL_HEIGHT);
}

TableViewCell* GuideCountry::tableCellAtIndex(TableView *table, ssize_t idx)
{
	log("tableCellAtIndex,idx:%d,m_focusIdx:%d", idx, m_focusIdx);
	TableViewCell *cell = table->dequeueCell();
	//if (idx < m_menuIdx)
	{	
		if (!cell) {
			cell = new BaseTableViewCell();
			((BaseTableViewCell*)cell)->addBtnlClick((Click_CallFun)&GuideCountry::onCellClick, this);
			cell->autorelease();
		}
		cell->removeAllChildrenWithCleanup(true);
		Size size = tableCellSizeForIndex(table, idx);
		int w = size.width;
		int h = size.height;	

		Label* text = Label::createWithTTF(m_countryVec.at(idx), "general/SourceHanSansTWHK-Light.ttf", 32);
		text->setColor(Color3B(153, 153, 153));
		text->setAnchorPoint(Vec2(0.5, 0.5));
		text->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
		text->setPosition(Vec2(CELL_WIDTH/2, CELL_HEIGHT / 2 - 10));
		cell->addChild(text);

		if (idx == m_focusIdx)
		{
			m_focusCell = cell;
			ImageView* focus = ImageView::create("general/general_button_focus.png");
			focus->setScale9Enabled(true);	
			focus->setCapInsets(Rect(40, 16, 135, 73));
			focus->setContentSize(Size(CELL_FOCUS_WIDTH + 76, CELL_FOCUS_HEIGHT + 80));
			focus->setPosition(Vec2(w / 2, h / 2 - 27));
			focus->setName("ID_PIC_FOCUS");
			focus->setZOrder(-1);
			cell->addChild(focus);			
		}	
	}
	return cell;
}

ssize_t GuideCountry::numberOfCellsInTableView(TableView *table)
{
	return m_cellNums;
}

void GuideCountry::onCellClick(cocos2d::Node* node)
{
	//TODO
	
	cocos2d::Node* curNode = tvScene::getTvLayer();				
	GuideSource::creatLayer(curNode);	
	
}