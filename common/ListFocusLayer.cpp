#include "cocos2d.h"
#include "common/ListFocusLayer.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
ListFocusLayer::ListFocusLayer()
{
	m_btnFocused = nullptr;
	m_focusIdx = 0;
	m_focusCol = 0;
	m_focusRow = 0;
	m_gridView = nullptr;
	m_focusCell = nullptr;
	m_bFocus = true;
}
ListFocusLayer::~ListFocusLayer()
{

}
bool ListFocusLayer::findHorNextFocus(int &next, cocos2d::ui::Widget::FocusDirection direction)
{
	bool ret = false;
	int offset_hor, offset_ver;
	offset_hor = m_rowNums;
	offset_ver = 1;
	switch (direction)
	{
	case cocos2d::ui::Widget::FocusDirection::LEFT:
		if (m_focusIdx / m_rowNums > 0)
			next = m_focusIdx - offset_hor;
		else
			next = -1;
		break;
	case cocos2d::ui::Widget::FocusDirection::RIGHT:
		if (m_focusIdx / m_rowNums < m_colNums - 1)
			next = m_focusIdx + offset_hor;
		else
			next = -1;
		break;
	case cocos2d::ui::Widget::FocusDirection::UP:
		next = m_focusIdx - offset_ver;
		
		break;
	case cocos2d::ui::Widget::FocusDirection::DOWN:
		next = m_focusIdx + offset_ver;
		
		break;
	}
	if (next < 0 || next >= m_cellNums)
		return ret;
	Size cellsize = m_gridView->getDataSource()->tableCellSizeForIndex(m_gridView, next);
	if (cellsize.width > 0 && cellsize.height > 0)
		ret = true;
	return ret;

}
bool ListFocusLayer::findNextFocus(int &next,cocos2d::ui::Widget::FocusDirection direction)
{
	bool ret = false;
	if (!m_gridView)
		return ret;
	int offset_hor, offset_ver;
	if (m_gridView->getDirection() == cocos2d::extension::ScrollView::Direction::HORIZONTAL)
	{
		return findHorNextFocus(next,direction);
	}
	else
	{
		offset_hor = 1;
		offset_ver = m_colNums;		
	}
	switch (direction)
	{
		case cocos2d::ui::Widget::FocusDirection::LEFT:
			if (m_focusIdx % m_colNums > 0)
				next = m_focusIdx - offset_hor;
			else
				next = -1;
		    break;
		case cocos2d::ui::Widget::FocusDirection::RIGHT:
			if (m_focusIdx % m_colNums < m_colNums - 1)
				next = m_focusIdx + offset_hor;
			else
				next = -1;
		    break;
		case cocos2d::ui::Widget::FocusDirection::UP:
			next = m_focusIdx - offset_ver;
			if (next < 0)
			{
				next = (m_rowNums - 1) * m_colNums + m_focusIdx;
			}
			break;
		case cocos2d::ui::Widget::FocusDirection::DOWN:
		    next = m_focusIdx + offset_ver;
			if (next >= m_cellNums)
			{
				next = next - (m_rowNums * m_colNums);
			}
			break;
	}
	if (next < 0 || next >= m_cellNums)
		return ret;
	Size cellsize = m_gridView->getDataSource()->tableCellSizeForIndex(m_gridView, next);
	if (cellsize.width > 0 && cellsize.height > 0)
		ret = true;
	return ret;
}

void ListFocusLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	this->stopPropagation(keyCode, unused_event);
	int next = 1;
	BaseTableViewCell* cell = nullptr;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
		if (findNextFocus(next, cocos2d::ui::Widget::FocusDirection::LEFT))
		    onFocusChanged(next, cocos2d::ui::Widget::FocusDirection::LEFT);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
		if (findNextFocus(next, cocos2d::ui::Widget::FocusDirection::RIGHT))
		    onFocusChanged(next, cocos2d::ui::Widget::FocusDirection::RIGHT);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_UP:
		if (findNextFocus(next, cocos2d::ui::Widget::FocusDirection::UP))
		    onFocusChanged(next, cocos2d::ui::Widget::FocusDirection::UP);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_DOWN:
		if (findNextFocus(next, cocos2d::ui::Widget::FocusDirection::DOWN))
		    onFocusChanged(next, cocos2d::ui::Widget::FocusDirection::DOWN);
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
	case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
		//onSimuCellClick();
		if (m_gridView)
		{
			cell = dynamic_cast<BaseTableViewCell*> (m_gridView->cellAtIndex(m_focusIdx));
			if (m_callFunc)
			{
				(this->getParent()->*m_callFunc)(this);
				this->getParent()->removeChild(this);
			}
			else
			{
				if (cell)
					cell->onCellClick();
			}
		}
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
bool ListFocusLayer::onFocusChanged( int next,cocos2d::ui::Widget::FocusDirection direction,bool isscroll)
{
	/*bool find = findNextFocus(next,direction);
	if (!find)
		return true;*/
	GridView* table = m_gridView;
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
			Size size = table->getDataSource()->tableCellSizeForIndex(table, next);
			focus->setName("ID_PIC_FOCUS");
			int w = size.width;
			int h = size.height;
			focus->setContentSize(Size(w + 76, h + 80));
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
bool ListFocusLayer::parseUserData(char *in, char * matching, char* out) {
	if (!in)
		return false;
	char *find = NULL;
	if (NULL != (find = strstr(in, matching))) {
		find += strlen(matching);//strlen("key=")
		sscanf(find, "%[^&]", out);
		return true;
	}
	return false;
}
