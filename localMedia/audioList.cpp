#include "cocos2d.h"
#include "localMedia/audioList.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
#include "localMedia/localAudioPlayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
#define CELL_WIDTH 1500
#define CELL_HEIGHT 165
audioList::audioList()
{
	m_btnFocused = nullptr;
	m_focusIdx = 0;
	m_focusCol = 0;
	m_focusRow = 0;
	m_gridView = nullptr;
	m_callFunc = nullptr;
	m_menuIdx = 0;
}
audioList::~audioList()
{
	
}
void audioList::addMenuStr(char* str)
{
	m_menuNameVec.push_back(str);
	m_menuIdx++;
}

Layer* audioList::creatLayer(cocos2d::Node* node, int cols,int rows,int cells,Click_CallFun callFunc)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("audioList");
		if (tuning) {
			return tuning;
		}
		else {
			audioList* pRet =(audioList*) audioList::create();
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
void audioList::initTableView()
{	
	//m_focusIdx = m_rowNums / 2;// (m_rowNums > 2) ? m_rowNums - 2 : m_rowNums;
	addNumsText(m_audioListVec.size());
	if (m_cellNums == 0)
	{
		ImageView* sorry = ImageView::create("localMedia/sorry.png");
		sorry->setName("ID_PIC_SORRY");
		sorry->setPosition(Vec2(1920 / 2, 1080 / 2));
		this->addChild(sorry);
		Text* sorry_t = Text::create("no audio file", "general/SourceHanSansTWHK-Light.ttf", 32);
		sorry_t->setPosition(Vec2(1920 / 2, 1080 / 2 - 200));
		sorry_t->setName("ID_TEXT_SORRY");
		sorry_t->setColor(Color3B(153, 153, 153));
		this->addChild(sorry_t);
		this->addKeyListener(CC_CALLBACK_2(ListFocusLayer::onKeyPressed, this), this);
		return;
	}
	int height = m_rowNums > 2 ? 890 :CELL_HEIGHT * m_rowNums;
	GridView* tableView = GridView::create(this, Size(CELL_WIDTH, height));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::BOTH);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setAnchorPoint(Vec2(0,0));
	tableView->setPosition(Vec2(215, 1080 - height - 170));
	tableView->setColNum(m_colNums);
	tableView->setRowNum(m_rowNums);
	tableView->setDelegate(this);
	m_gridView = tableView;
	this->addChild(tableView);
	tableView->reloadData();
	this->addKeyListener(CC_CALLBACK_2(ListFocusLayer::onKeyPressed, this), this);
//	addNote(m_audioListVec.at(m_focusIdx).c_str());
//	tableView->scrollStep(m_focusIdx, cocos2d::ui::Widget::FocusDirection::DOWN);
}
bool audioList::init()
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

	addTitle("Audio");
	ImageView* split = ImageView::create("general/general_listline.png");
	split->setAnchorPoint(Vec2(0,0));
	split->setPosition(Vec2(0,958.15));
	split->setScaleY(2);
	this->addChild(split);	
	return bRet;
}
void audioList::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
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
bool audioList::onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll )
{
	GridView* table = m_gridView;
//	addNote(m_audioListVec.at(next).c_str());
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
			focus->setContentSize(Size(w + 76, h + 80));
			focus->setPosition(Vec2(w / 2, h / 2 - 27));
			focus->setZOrder(-1);
			cell->addChild(focus);
			/*TODO 焦点动画效果*/
			CCActionInterval*  action = CCFadeIn::create(3.0f);
			focus->runAction(CCSequence::create(action, NULL));

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
void audioList::addTitle(const char* str)
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
void audioList::addNote(const char* str)
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
void audioList::addNumsText(int nums)
{
	char str[64] = { 0 };
	sprintf(str,"%d audios",nums);
	Text* text = (Text*) this->getChildByName("ID_TEXT_NUMS");
	if (text) {
		text->setString(str);
	}
	else {
		text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 32);
		text->setColor(Color3B(153, 153, 153));
		text->setAnchorPoint(Vec2(1, 0.5));
		text->setPosition(Vec2(1655, 988));
		text->setName("ID_TEXT_NUMS");
		this->addChild(text);
	}
}
void audioList::toExtensionsMainLayer(cocos2d::Ref *sender)
{
}

void audioList::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}

Size audioList::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(CELL_WIDTH, CELL_HEIGHT);
}

TableViewCell* audioList::tableCellAtIndex(TableView *table, ssize_t idx)
{
	log("tableCellAtIndex,idx:%d,m_focusIdx:%d", idx, m_focusIdx);
	TableViewCell *cell = table->dequeueCell();
	//if (idx < m_menuIdx)
	{	
		if (!cell) {
			cell = new BaseTableViewCell();
			((BaseTableViewCell*)cell)->addBtnlClick((Click_CallFun)&audioList::onCellClick, this);
			cell->autorelease();
		}
		cell->removeAllChildrenWithCleanup(true);
		Size size = tableCellSizeForIndex(table, idx);
		int w = size.width;
		int h = size.height;	

		ImageView* img = ImageView::create("localMedia/filebg.png");
		img->setAnchorPoint(Vec2(0, 0.5));
		img->setPosition(Vec2(40, h/2));
		cell->addChild(img); 

		ImageView* split = ImageView::create("localMedia/split_line.png");
		split->setAnchorPoint(Vec2(0.5, 0.5));
		split->setPosition(Vec2(w / 2, 0));
		cell->addChild(split);

		Button* btn = Button::create("localMedia/audio_list_normal.png","localMedia/audio_list_focus.png");
		btn->setAnchorPoint(Vec2(0,0.5));
		btn->setPosition(Vec2(110,h/2));
		cell->addChild(btn);

		if (idx == m_focusIdx)
		{
			m_focusCell = cell;
			ImageView* focus = ImageView::create("general/general_button_focus.png");
			focus->setScale9Enabled(true);	
			focus->setCapInsets(Rect(40, 16, 135, 73));
			focus->setContentSize(Size(w + 76, h + 80));
			focus->setPosition(Vec2(w / 2, h / 2 - 27));
			focus->setName("ID_PIC_FOCUS");
			focus->setZOrder(-1);
			cell->addChild(focus);

			btn->setHighlighted(true);
		}	

		Text* text = Text::create(m_audioListVec.at(idx), "general/SourceHanSansTWHK-Light.ttf", 32);
		text->setColor(Color3B(153, 153, 153));
		text->setAnchorPoint(Vec2(0,0.5));
		text->setPosition(Vec2(285,CELL_HEIGHT / 2));
		cell->addChild(text);

		Text* texttime = Text::create("00:03:45", "general/SourceHanSansTWHK-Light.ttf", 32);
		texttime->setColor(Color3B(153, 153, 153));
		texttime->setName("ID_TEXT_TIME");
		texttime->setAnchorPoint(Vec2(1, 0.5));
		texttime->setPosition(Vec2(1450, CELL_HEIGHT / 2));
		cell->addChild(texttime);
	}
	return cell;
}

ssize_t audioList::numberOfCellsInTableView(TableView *table)
{
	return m_cellNums;
}

void audioList::onCellClick(cocos2d::Node* node)
{
	//TODO
	auto scene = Director::getInstance()->getRunningScene();
	LocalAudioPlayer*  player = (LocalAudioPlayer*)LocalAudioPlayer::creatLayer(scene);
	//player->play(m_audioListVec.at(m_focusIdx));
	player->play(m_audioListVec);
}