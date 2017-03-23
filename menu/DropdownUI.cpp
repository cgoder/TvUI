#include "cocos2d.h"
#include "menu/DropdownUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "menu/MainResponse.h"
#include "tinyxml2/tinyxml2.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
DropdownUI::DropdownUI()
{
	m_btnFocused = nullptr;
	m_focusIdx = 0;
	m_focusCol = 0;
	m_focusRow = 0;
	m_gridView = nullptr;
	m_callFunc = nullptr;
	m_menuIdx = 0;
	m_response = nullptr;
	m_positionx = 0;
	m_positiony = 0;
}
DropdownUI::~DropdownUI()
{
}
void DropdownUI::addMenuStr(const char* str, std::vector<std::string> menuvec)
{
	m_menuNameVec = menuvec;
	int i = 0;
	for (auto menu : m_menuNameVec)
	{
		if (menu == str)
			m_menuIdx = i;
		i++;
	}
}
void DropdownUI::addMenuControl(std::vector<MenuControl*> menuVec, MenuControl* menu) {
	std::string itemstr;
	menu->getItemCur(itemstr);
	addMenuStr(itemstr.c_str(), menu->getItemVec());
	m_menuNameVec = menu->getItemVec();
	m_menuCtrlVec = menuVec;
	m_menu = menu;
};
Layer* DropdownUI::creatLayer(cocos2d::Node* node, cocos2d::Size cellSize, cocos2d::Size tableSize, cocos2d::Vec2 position, std::vector<MenuControl*> menuVec, MenuControl* menu, MenuResponse* response, Click_CallFun callFunc)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("DropdownUI");
		if (tuning) {
			return tuning;
		}
		else {
			DropdownUI* pRet = (DropdownUI*)DropdownUI::create();
			pRet->addCallBack(callFunc);
			pRet->addResponse(response);
			pRet->addMenuControl(menuVec, menu);
			pRet->initTableView(cellSize, tableSize, position);
			node->setZOrder(5);
			node->removeChildByName("ID_PIC_FOCUS");

			ImageView* unfocus = ImageView::create("general/general_button_normal.png");
			Size nodeSize = node->getContentSize();
			unfocus->setScale9Enabled(true);
			unfocus->setContentSize(Size(nodeSize.width + 20, nodeSize.height + 20));
			unfocus->setPosition(Vec2(nodeSize.width / 2, nodeSize.height / 2));
			unfocus->setName("ID_PIC_FOCUS");
			node->addChild(unfocus);
			node->addChild(pRet);
			return pRet;
		}
	}
	return nullptr;
}

void DropdownUI::initTableView(Size cellSize, Size tableSize, Vec2 position)
{
	m_cellWidth = cellSize.width;
	m_cellHeight = cellSize.height;
	float height = tableSize.height;
	m_colNums = 1;
	m_cellNums = m_rowNums = m_menuNameVec.size();
	if (height == 0)
	{
		height = m_cellHeight * m_rowNums;
	}
	this->setContentSize(Size(m_cellWidth, height + 60));
	this->setAnchorPoint(Vec2(0, 1));
	this->setPosition(Vec2(position.x - 200, position.y - height - 60));

	ImageView* shadow = ImageView::create("menu/pop_shadow.png");
	shadow->setScale9Enabled(true);
	shadow->setContentSize(Size(m_cellWidth + 67 * 2, height + 60 + 67 * 2));
	shadow->setPosition(Vec2(m_cellWidth / 2, (height + 60) / 2));
	this->addChild(shadow);

	ImageView* bg = ImageView::create("general/general_popup_bg.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setScaleX(m_cellWidth / bg->getContentSize().width);
	bg->setScaleY((height + 60.00) / bg->getContentSize().height);
	this->addChild(bg);

	ImageView* up = ImageView::create("menu/up.png");
	up->setPosition(Vec2(m_cellWidth / 2, 45 + height));
	this->addChild(up);

	ImageView* down = ImageView::create("menu/down.png");
	down->setPosition(Vec2(m_cellWidth / 2, 15));
	this->addChild(down);

	GridView* tableView = GridView::create(this, Size(m_cellWidth, height));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setAnchorPoint(Vec2(0, 0));
	tableView->setPosition(Vec2(-2, 30));
	//tableView->setPosition(Vec2(position));
	tableView->setColNum(m_colNums);
	tableView->setRowNum(m_rowNums);
	tableView->setDelegate(this);
	m_gridView = tableView;
	this->addChild(tableView);
	tableView->reloadData();
	this->addKeyListener(CC_CALLBACK_2(ListFocusLayer::onKeyPressed, this), this);
	//tableView->scrollStep(m_focusIdx, cocos2d::ui::Widget::FocusDirection::DOWN);
}
bool DropdownUI::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		bRet = true;
	} while (0);

	return bRet;
}
void DropdownUI::onKeyBack()
{
	Node* node = this->getParent();
	node->removeChildByName("ID_PIC_FOCUS");
	Size nodeSize = node->getContentSize();
	ImageView* focus = ImageView::create("general/general_button_focus.png");
	focus->setScale9Enabled(true);
	focus->setName("ID_PIC_FOCUS");
	focus->setContentSize(Size(nodeSize.width + 76, nodeSize.height + 80));
	focus->setPosition(Vec2(nodeSize.width / 2, nodeSize.height / 2 - 27));
	focus->setZOrder(-1);
	node->addChild(focus);
	node->setZOrder(0);

}
void DropdownUI::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
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
		onKeyBack();
		if (m_callFunc)
		{
			(this->getParent()->*m_callFunc)(this);
		}
		this->getParent()->removeChild(this);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
		onKeyLeft();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
		onKeyRight();
		break;
	default:
		ListFocusLayer::onKeyPressed(keyCode, unused_event);
		break;
	}
}
void DropdownUI::onKeyLeft()
{
}
void DropdownUI::onKeyRight()
{
}
bool DropdownUI::onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll)
{
	ListFocusLayer::onFocusChanged(next, direction, true);
	/*if (direction == cocos2d::ui::Widget::FocusDirection::UP)
	m_gridView->scrollStep(1, cocos2d::ui::Widget::FocusDirection::UP);
	if (direction == cocos2d::ui::Widget::FocusDirection::DOWN)
	m_gridView->scrollStep(1, cocos2d::ui::Widget::FocusDirection::DOWN);*/
	return false;
}
void DropdownUI::addTitle(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 60);
	text->setAnchorPoint(Vec2(0, 0));
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(87, 947));
	this->addChild(text);
}
void DropdownUI::addNote(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 32);
	text->setColor(Color3B(153, 153, 153));
	text->setAnchorPoint(Vec2(0, 0));
	text->setPosition(Vec2(387, 964));
	this->addChild(text);
}
void DropdownUI::toExtensionsMainLayer(cocos2d::Ref *sender)
{
}

void DropdownUI::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}

Size DropdownUI::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(m_cellWidth, m_cellHeight);
}

TableViewCell* DropdownUI::tableCellAtIndex(TableView *table, ssize_t idx)
{
	log("tableCellAtIndex,idx:%d,m_focusIdx:%d", idx, m_focusIdx);
	TableViewCell *cell = table->dequeueCell();
	//if (idx < m_menuIdx)
	{
		if (!cell) {
			cell = new BaseTableViewCell();
			((BaseTableViewCell*)cell)->addBtnlClick((Click_CallFun)&DropdownUI::onCellClick, this);
			cell->autorelease();
		}
		cell->removeAllChildrenWithCleanup(true);
		if (m_gridView) {
			Label* text = Label::createWithTTF(m_menuNameVec.at(idx), "general/SourceHanSansTWHK-Light.ttf", 32);
			text->setColor(Color3B(91, 91, 91));
			text->setPosition(Vec2(m_cellWidth / 2, m_cellHeight / 2));
			text->setName("ID_TEXT_VALUE");
			cell->addChild(text);
			if (idx == m_menuIdx)
			{
				ImageView* img = ImageView::create("menu/select.png");
				Size textSize = text->getContentSize();
				img->setName("ID_PIC_SELECT");
				img->setPosition(Vec2(-22, textSize.height / 2));
				text->addChild(img);
			}
			if (idx == m_focusIdx)
			{
				ImageView* focus = ImageView::create("general/general_button_focus.png");
				focus->setScale9Enabled(true);
				focus->setName("ID_PIC_FOCUS");
				focus->setContentSize(Size(m_cellWidth + 76, m_cellHeight + 80));
				focus->setPosition(Vec2(m_cellWidth / 2, m_cellHeight / 2 - 27));
				focus->setZOrder(-1);
				cell->addChild(focus);
			}
		}
	}
	return cell;
}

ssize_t DropdownUI::numberOfCellsInTableView(TableView *table)
{
	return m_cellNums;
}

void DropdownUI::onCellClick(cocos2d::Node* node)
{
	BaseTableViewCell* cell = dynamic_cast<BaseTableViewCell*> (m_gridView->cellAtIndex(m_menuIdx));
	if (cell)
		cell->getChildByName("ID_TEXT_VALUE")->removeChildByName("ID_PIC_SELECT");
	m_menuIdx = m_focusIdx;

	Node* text = node->getChildByName("ID_TEXT_VALUE");
	ImageView* img = ImageView::create("menu/select.png");
	Size textSize = text->getContentSize();
	img->setName("ID_PIC_SELECT");
	img->setPosition(Vec2(-22, textSize.height / 2));
	text->addChild(img);

	m_menu->setItemCur(m_menuNameVec.at(m_focusIdx));
	if (m_response) {
		Menu_CallFun func = m_response->getDropDownFunc();
		if (func)
		{
			(m_response->*func)(m_menuCtrlVec, m_menu, m_focusIdx, this, node);
		}
	}
}