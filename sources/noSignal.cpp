#include "cocos2d.h"
#include "sources/noSignal.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
noSignal::noSignal()
{	
	this->setName("noSignal");
//	m_btnFocused = nullptr;
}
noSignal::~noSignal()
{

}

Layer* noSignal::creatLayer(cocos2d::Node* node,Click_CallFun callFunc)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("noSignal");
		if (tuning) {
			return tuning;
		}
		else {
			log("AutoTuning:ceart");
			noSignal* pRet =(noSignal*) noSignal::create();
			pRet->setAnchorPoint(Vec2(0, 0));
			pRet->setPosition(Vec2(0,0));
			node->addChild(pRet);
			return pRet;
		}
	}
	return nullptr;
}
bool noSignal::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		bRet = true;
	} while (0);
	this->setContentSize(Size(1920,1080));
	ImageView* bg = ImageView::create("general/general_bg.png");
	bg->setAnchorPoint(Vec2(0,0));
	bg->setPosition(Vec2(0,0));
	this->addChild(bg);
		
	this->addKeyListener(CC_CALLBACK_2(noSignal::onKeyPressed, this), this);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create("sources/noSignal.png");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite);
	auto label = Label::createWithTTF("no signal","SourceHanSansTWHK-Light.ttf",40);
	Size size = sprite->getContentSize();
	label->setPosition(Vec2(size.width / 2, -50));
	sprite->addChild(label);
	return bRet;
}
void noSignal::menuCallback(cocos2d::Ref* pSender)
{

}
#if 0
void noSignal::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	 ListFocusLayer::onKeyPressed(keyCode, unused_event);
}
bool noSignal::onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll)
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
#endif