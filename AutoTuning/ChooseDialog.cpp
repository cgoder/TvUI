#include "cocos2d.h"
#include "AutoTuning/ChooseDialog.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
ChooseDialog::ChooseDialog()
{	
	this->setName("ChooseDialog");
	m_btnFocused = nullptr;
	m_focusIdx = 0;
	m_focusCol = 0;
	m_focusRow = 0;
	m_gridView = nullptr;
	m_callFunc = nullptr;
	m_chooseIdx = 0;
}
ChooseDialog::~ChooseDialog()
{

}
void ChooseDialog::addChooseStr(const char* str ,const char* choose)
{
	if (!strcmp(str, choose)) {
		m_chooseIdx = m_chooseVec.size();
		m_focusIdx = m_chooseIdx;
	}
	m_chooseVec.push_back(str);	
	
}

Layer* ChooseDialog::creatLayer(cocos2d::Node* node, int cols,int rows,int cells,Click_CallFun callFunc)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("ChooseDialog");
		if (tuning) {
			return tuning;
		}
		else {
			log("AutoTuning:ceart");
			ChooseDialog* ptuning =(ChooseDialog*) ChooseDialog::create();
			ptuning->addCallBack(callFunc);
			ptuning->setColNum(cols);
			ptuning->setRowNum(rows);
			ptuning->setCellNum(cells);
			node->addChild(ptuning);
			return ptuning;
		}
	}
	return nullptr;
}
void ChooseDialog::initTableView()
{
	int height = 84 * m_rowNums;
	GridView* tableView = GridView::create(this, Size(1544, 600));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
	tableView->setClippingToBounds(false);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setAnchorPoint(Vec2(0, 0));
	if (m_colNums == 1)
	    tableView->setPosition(Vec2(620, 813 - height));
	else if (m_colNums == 2)
		tableView->setPosition(Vec2(290, 813 - height));
	else
		tableView->setPosition(Vec2(190, 813 - height));

	tableView->setColNum(m_colNums);
	tableView->setRowNum(m_rowNums);
	tableView->setDelegate(this);
	tableView->setName("ID_TABLEVIEW_CHOOSE");
	m_gridView = tableView;
	this->addChild(tableView);
	tableView->reloadData();
	tableView->scrollStep(m_chooseIdx / m_rowNums, cocos2d::ui::Widget::FocusDirection::RIGHT);
	this->addKeyListener(CC_CALLBACK_2(ListFocusLayer::onKeyPressed, this), this);
}
bool ChooseDialog::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		bRet = true;
	} while (0);
	ImageView* bg = ImageView::create("general/general_bg.png");
	bg->setPosition(Vec2(960,540));
	this->addChild(bg);

	ImageView* split = ImageView::create("general/general_listline.png");
	split->setAnchorPoint(Vec2(0,0));
	split->setPosition(Vec2(0, 958));
	this->addChild(split);
	
	return bRet;
}
void ChooseDialog::addTitle(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 60);
	text->setAnchorPoint(Vec2(0, 0));
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(87,947));
	this->addChild(text);
}
void ChooseDialog::addNote(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 32);
	text->setColor(Color3B(153, 153, 153));
	text->setAnchorPoint(Vec2(0, 0));
	text->setPosition(Vec2(387,964));
	this->addChild(text);
}
void ChooseDialog::toExtensionsMainLayer(cocos2d::Ref *sender)
{
}

void ChooseDialog::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}

Size ChooseDialog::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(740, 84);
}

TableViewCell* ChooseDialog::tableCellAtIndex(TableView *table, ssize_t idx)
{
	log("tableCellAtIndex,idx:%d,m_focusIdx:%d", idx, m_focusIdx);
	TableViewCell *cell = table->dequeueCell();
	{	
		if (!cell) {
			cell = new BaseTableViewCell();
			cell->autorelease();
		}
		cell->removeAllChildrenWithCleanup(true);
		
		Button* btn = Button::create("broadcast/broadcast_listbutton_normal.png", "broadcast/broadcast_listbutton_bg.png", "broadcast/broadcast_listbutton_focus.png");
		btn->setTitleText("");
		btn->setAnchorPoint(Vec2(0, 0));
		btn->setPosition(Vec2(40, 25));
		btn->setZOrder(2);
		cell->addChild(btn);
		if (idx == m_chooseIdx)
			btn->setEnabled(false);
		if (idx == m_focusIdx)
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
			cell->addChild(focus);
			btn->setHighlighted(true);
		}
		//m_chooseVec
		auto text = Text::create(m_chooseVec.at(idx), "general/SourceHanSansTWHK-Light.ttf", 32);
		//auto text = Text::create(m_chooseStr[idx], "general/SourceHanSansTWHK-Light.ttf", 32); 
		//Lable::createWithTTF(m_chooseStr[idx], "general/SourceHanSansTWHK-Light.ttf", 32);
		text->setAnchorPoint(Vec2(0, 0.5));
		text->setColor(Color3B(91, 91, 91));
		text->setPosition(Vec2(100, 42));
		text->setName("ID_TEXT_NAME");
		text->setZOrder(2);
		cell->addChild(text);
	}
	return cell;
}

ssize_t ChooseDialog::numberOfCellsInTableView(TableView *table)
{
	return m_cellNums;
}
