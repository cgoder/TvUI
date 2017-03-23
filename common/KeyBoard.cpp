#include "cocos2d.h"
#include "common/KeyBoard.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
KeyBoard::KeyBoard()
{	
	this->setName("KeyBoard");
	m_btnFocused = nullptr;
	m_focusIdx = 0;
	m_focusCol = 0;
	m_focusRow = 0;
	m_gridView = nullptr;
	m_callFunc = nullptr;
	m_rootText = nullptr;
	m_bSign = false;
	m_bUp = false;
}
KeyBoard::~KeyBoard()
{

}

Layer* KeyBoard::creatLayer(cocos2d::Node* node, cocos2d::Node* text, Click_CallFun callFunc)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("KeyBoard");
		if (tuning) {
			return tuning;
		}
		else {
			log("AutoTuning:ceart");
			KeyBoard* pRet =(KeyBoard*) KeyBoard::create();
			Size size = node->getContentSize();
			pRet->setPosition(Vec2(size.width/2 - 550,0));
			pRet->addCallBack(callFunc);
			pRet->setTextNode(text);
			pRet->setColNum(11);
			pRet->setRowNum(4);
			pRet->setCellNum(44);
			pRet->initTableView();
			node->addChild(pRet);
			return pRet;
		}
	}
	return nullptr;
}
void KeyBoard::initTableView()
{

	int height = 84 * m_rowNums;
	GridView* tableView = GridView::create(this, Size(1100, 336));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::BOTH);
	tableView->setClippingToBounds(false);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setAnchorPoint(Vec2(0, 0));
	tableView->setPosition(Vec2(0, 0));
	tableView->setColNum(m_colNums);
	tableView->setRowNum(m_rowNums);
	tableView->setDelegate(this);
	tableView->setName("ID_TABLEVIEW_CHOOSE");
	m_gridView = tableView;
	this->addChild(tableView);
	tableView->reloadData();
//	tableView->scrollStep(m_chooseIdx / m_rowNums, cocos2d::ui::Widget::FocusDirection::RIGHT);
}
bool KeyBoard::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		bRet = true;
	} while (0);
	this->setContentSize(Size(1100,420));
	ImageView* bg = ImageView::create("general/general_bg.png");
	bg->setAnchorPoint(Vec2(0,0));
	bg->setPosition(Vec2(0,0));
	bg->setScale9Enabled(true);
	bg->setContentSize(Size(1100,420));
	this->addChild(bg);
	
	LayerColor* layco = LayerColor::create(Color4B(255,255,255,255), 1100,84);
	layco->setAnchorPoint(Vec2(0,0));
	layco->setPosition(Vec2(0, 336));
	this->addChild(layco);
	m_textInput = Text::create("", "general/SourceHanSansTWHK-Light.ttf", 32);
	m_textInput->setAnchorPoint(Vec2(0, 0));
	m_textInput->setTextColor(Color4B(0,0,0,255));
	m_textInput->setPosition(Vec2(0, 336));
	this->addChild(m_textInput);

	m_inputStr = "";
	
	this->addKeyListener(CC_CALLBACK_2(KeyBoard::onKeyPressed, this), this);

	char* temp = "123abcdefg 456hijklmn 789opqrstu @0.vwxyz  ";
	char* tempup = "123ABCDEFG 456HIJKLMN 789OPQRSTU @0.VWXYZ  ";
	char* tempsin = ".,?!/:&@|= *#$%\"\'\\^~` ;+()<>{}[] _-       ";
	for (int i = 0; i < strlen(temp); i++)
	{
		m_keyBoard[i] = temp[i];
	}
	for (int i = 0; i < strlen(tempup); i++)
	{
		m_KeyBoardUP[i] = tempup[i];
	}
	for (int i = 0; i < strlen(tempsin); i++)
	{
		m_KeyBoardSign[i] = tempsin[i];
	}
	m_keyBoard[strlen(temp)] = '\0';
	m_KeyBoardUP[strlen(tempup)] = '\0';
	m_KeyBoardSign[strlen(tempsin)] = '\0';

	char* temppress = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < strlen(temppress); i++)
	{
		m_keyBoardPress[i] = temppress[i];
	}
	m_keyBoardPress[strlen(temppress)] = '\0';
	return bRet;
}
void KeyBoard::addTitle(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 60);
	text->setAnchorPoint(Vec2(0, 0));
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(87,947));
	this->addChild(text);
}
void KeyBoard::addNote(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 32);
	text->setColor(Color3B(153, 153, 153));
	text->setAnchorPoint(Vec2(0, 0));
	text->setPosition(Vec2(387,964));
	this->addChild(text);
}
void KeyBoard::toExtensionsMainLayer(cocos2d::Ref *sender)
{
}

void KeyBoard::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}

Size KeyBoard::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(100, 84);
}

TableViewCell* KeyBoard::tableCellAtIndex(TableView *table, ssize_t idx)
{
	log("tableCellAtIndex,idx:%d,m_focusIdx:%d", idx, m_focusIdx);
	TableViewCell *cell = table->dequeueCell();
	{	
		if (!cell) {
			cell = new BaseTableViewCell();
			((BaseTableViewCell*)cell)->addBtnlClick((Click_CallFun)&KeyBoard::onCellClick, this);
			cell->autorelease();
		}
		cell->removeAllChildrenWithCleanup(true);
		Size size = tableCellSizeForIndex(table, idx);
		int w = size.width;
		int h = size.height;
		if (idx == m_focusIdx)
		{
			m_focusCell = cell;
			ImageView* focus = ImageView::create("general/general_button_focus.png");
			focus->setScale9Enabled(true);					
			focus->setContentSize(Size(w + 76, h + 80));
			focus->setPosition(Vec2(w / 2, h / 2 - 27));
			focus->setName("ID_PIC_FOCUS");
			cell->addChild(focus);
		}
		//m_chooseVec
		String* string = nullptr;
		switch (idx)
		{
		case 10:
			string = String::createWithFormat("%s", "del");
			break;
		case 21:
			if (m_bUp)
			    string = String::createWithFormat("%s", "A/123");
			else
				string = String::createWithFormat("%s", "a/123");
			break;
		case 32:
			string = String::createWithFormat("%s", "sign");
			break;
		case 43:
			string = String::createWithFormat("%s","ok");
			break;
		default:
			if (m_bSign)
				string = String::createWithFormat("%c", m_KeyBoardSign[idx]);
			else
			{
				if (m_bUp)
					string = String::createWithFormat("%c", m_KeyBoardUP[idx]);
				else
					string = String::createWithFormat("%c", m_keyBoard[idx]);
			}
			break;
		}
		
		auto text = Text::create(string->getCString(), "general/SourceHanSansTWHK-Light.ttf", 32);
		text->setAnchorPoint(Vec2(0.5, 0.5));
		text->setColor(Color3B(91, 91, 91));
		text->setPosition(Vec2(w/2, h/2));
		text->setName("ID_TEXT_NAME");
		text->setZOrder(2);
		cell->addChild(text);
	}
	return cell;
}

ssize_t KeyBoard::numberOfCellsInTableView(TableView *table)
{
	return m_cellNums;
}
void KeyBoard::onCellClick(cocos2d::Node* node)
{
	switch (m_focusIdx)
	{
	case 10:
		if (m_inputStr.size() > 0)
		{
			m_inputStr.pop_back();
			m_textInput->setString(m_inputStr);
			setTextString();
		}
		break;
	case 21:
		m_bUp = !m_bUp;
		m_bSign = false;
		m_gridView->reloadData();
		break;
	case 32:
		m_bSign = true;
		m_gridView->reloadData();
		break;
	case 43:
		this->getParent()->removeChild(this);
		break;
	default:
		if (m_bSign)
		    m_inputStr += m_KeyBoardSign[m_focusIdx];
		else {
			if (m_bUp)
				m_inputStr += m_KeyBoardUP[m_focusIdx];
			else
				m_inputStr += m_keyBoard[m_focusIdx];
		}
		m_textInput->setString(m_inputStr);	
		setTextString();
		break;
	}
}
void KeyBoard::setTextString()
{
	if (m_rootText)
	{
		auto node = dynamic_cast<Text*>(m_rootText);
		if (node)
			node->setString(m_inputStr);
		auto temp = dynamic_cast<Label*>(m_rootText);
		if (temp)
			temp->setString(m_inputStr);
		auto temp1 = dynamic_cast<TextField*>(m_rootText);
		if (temp1)
			temp1->setString(m_inputStr);
	}
}
void KeyBoard::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	if (keyCode <= cocos2d::EventKeyboard::KeyCode::KEY_9 && keyCode >= cocos2d::EventKeyboard::KeyCode::KEY_0)
	{
		unused_event->stopPropagation();
		m_inputStr += m_keyBoardPress[(int)keyCode - 76];
		m_textInput->setString(m_inputStr);
		setTextString();
	}
	else if (keyCode <= cocos2d::EventKeyboard::KeyCode::KEY_Z && keyCode >= cocos2d::EventKeyboard::KeyCode::KEY_A)
	{
		unused_event->stopPropagation();
		m_inputStr += m_keyBoardPress[(int)keyCode - 124 + 10];
		m_textInput->setString(m_inputStr);
		setTextString();
	}
	else if (keyCode <= cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Z && keyCode >= cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A)
	{
		unused_event->stopPropagation();
		m_inputStr += m_keyBoardPress[(int)keyCode - 93 + 10 + 26];
		m_textInput->setString(m_inputStr);
		setTextString();
	}
	else
	    ListFocusLayer::onKeyPressed(keyCode, unused_event);
}