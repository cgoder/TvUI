#include "cocos2d.h"
#include "menu/MenuControl.h"
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "ui/UIImageView.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
MenuControl::MenuControl()
{
	m_type = 0;
	m_enable = true;
}
MenuControl::~MenuControl()
{
	//TODO 
	for (auto node : m_nodes)
	{
		if (node->getParent())
			node->getParent()->removeChild(node);
		delete node;
	}
}
void MenuControl::assocAction(std::vector<MenuControl*> menuvec)
{
	std::string cur;
	if (getItemCur(cur)) {
		for (auto num : m_assocVec) {
			MenuControl* menu = menuvec.at(num-1);
			bool bassoc = false;
			for (auto assoc : m_assocNameVec)
			{
				if (assoc == cur)
				{
					bassoc = true;
					break;
				}
			}
			if (bassoc)
			{
				if (!menu->getEnable()) {
					menu->setEnable(true);
					for (auto node : menu->getNodes())
					{
						if (dynamic_cast<Label*>(node))
							((Label*)node)->setColor(Color3B(91, 91, 91));
					}
				}
			}
			else
			{
				if (menu->getEnable())
				{
					menu->setEnable(false);
					for (auto node : menu->getNodes())
					{
						if (dynamic_cast<Label*>(node))
							((Label*)node)->setColor(Color3B(153, 153, 153));					
					}
				}
			}
		}
	}
}

bool LFRaidoControl::onKeyLeft(cocos2d::Node* rootNode)
{
	std::string itemname;
	bool ret;
	if (this->getItemLast(itemname))
	{
		Label* text = (Label*)rootNode->getChildByName("ID_TEXT_VALUE");
		if (text)
			text->setString(itemname);
		Button* btn = (Button*)rootNode->getChildByName("ID_BUT_ARROW_R");
		btn->setHighlighted(false);
		btn = (Button*)rootNode->getChildByName("ID_BUT_ARROW_L");
		btn->setHighlighted(true);		
		return true;
	}
	return false;
}
bool LFRaidoControl::onKeyRight(cocos2d::Node* rootNode)
{
	std::string itemname;
	bool ret;
	if (this->getItemNext(itemname))
	{
		Label* text = (Label*)rootNode->getChildByName("ID_TEXT_VALUE");
		if (text)
			text->setString(itemname);
		Button* btn = (Button*)rootNode->getChildByName("ID_BUT_ARROW_R");
		btn->setHighlighted(true);
		btn = (Button*)rootNode->getChildByName("ID_BUT_ARROW_L");
		btn->setHighlighted(false);
		return true;
	}
	return false;
}
bool LFRaidoControl::setItemCur(const std::string& str)
{
	int i = 0;
	for (auto item : m_itemName)
	{
		if (item == str)
		{
			m_index = i;
			for (auto node : m_nodes)
			{
				if (node->getName() == "ID_TEXT_VALUE")
				{
					((Label*)node)->setString(item);
				}
			}
			break;
		}
		i++;
	}
	return true;
}
void LFRaidoControl::initNode(float cellWidth, float cellHeight)
{
	Button* btnl = new (std::nothrow) Button();
	if (btnl && btnl->init()) {
		btnl->loadTextures("epgturning/epg_arrow_turnleft_normal.png", "epgturning/epg_arrow_turnleft_focus.png");
		btnl->setPosition(Vec2(cellWidth - 270, cellHeight / 2));
		btnl->setName("ID_BUT_ARROW_L");
		this->addNode(btnl);
	}

	Button* btnr = new (std::nothrow) Button();
	if (btnr && btnr->init()) {
		btnr->loadTextures("epgturning/epg_arrow_turnright_normal.png", "epgturning/epg_arrow_turnright_focus.png");
		btnr->setPosition(Vec2(cellWidth  - 55, cellHeight / 2));
		btnr->setName("ID_BUT_ARROW_R");
		this->addNode(btnr);
	}

	Color3B color(91, 91, 91);
	Label* node = new (std::nothrow) Label;
	if (node)
	{
		node->setSystemFontName("general/SourceHanSansTWHK-Light.ttf");
		node->setSystemFontSize(32);
		std::string title;
		if (this->getItemCur(title))
			node->setString(title);
		node->setColor(color);
		node->setPosition(Vec2(cellWidth - 160, cellHeight / 2));
		node->setName("ID_TEXT_VALUE");
		this->addNode(node);
	}
}

void UDRadioControl::initNode(float cellWidth, float cellHeight)
{
	m_cellWidth = cellWidth;
	m_cellHeight = cellHeight;
	Color3B color(91, 91, 91);
	Label* node = new (std::nothrow) Label;
	if (node)
	{
		node->setSystemFontName("general/SourceHanSansTWHK-Light.ttf");
		node->setSystemFontSize(32);
		std::string title;
		if (this->getItemCur(title))
			node->setString(title);
		node->setColor(color);
		node->setPosition(Vec2(cellWidth - 160, cellHeight / 2));
		node->setName("ID_TEXT_VALUE");
		this->addNode(node);
	}
}


bool NumsRadioControl::onKeyLeft(cocos2d::Node* rootNode)
{
	m_curValue -= 1;
	if (m_curValue < m_minValue)
		m_curValue = m_maxValue;
	std::string itemname = std::to_string(m_curValue);
	Label* text = (Label*)rootNode->getChildByName("ID_TEXT_VALUE");
	if (text)
		text->setString(itemname);
	Button* btn = (Button*)rootNode->getChildByName("ID_BUT_ARROW_R");
	btn->setHighlighted(false);
	btn = (Button*)rootNode->getChildByName("ID_BUT_ARROW_L");
	btn->setHighlighted(true);
	return true;
}
bool NumsRadioControl::onKeyRight(cocos2d::Node* rootNode)
{
	m_curValue += 1;
	if (m_curValue > m_maxValue)
		m_curValue = m_minValue;
	std::string itemname = std::to_string(m_curValue);
	Label* text = (Label*)rootNode->getChildByName("ID_TEXT_VALUE");
	if (text)
		text->setString(itemname);
	Button* btn = (Button*)rootNode->getChildByName("ID_BUT_ARROW_R");
	btn->setHighlighted(true);
	btn = (Button*)rootNode->getChildByName("ID_BUT_ARROW_L");
	btn->setHighlighted(false);	
	return true;
}

void NumsRadioControl::setCurValue(int value, cocos2d::Node* rootNode)
{
	m_curValue = value;
	std::string title = std::to_string(m_curValue);
	for (auto node : m_nodes)
	{
		if (node->getName() == "ID_TEXT_VALUE")
		{
			((Label*)node)->setString(title);
		}
	}
}

void NumsRadioControl::initNode(float cellWidth, float cellHeight)
{
	Button* btnl = new (std::nothrow) Button();
	if (btnl && btnl->init()) {
		btnl->loadTextures("epgturning/epg_arrow_turnleft_normal.png", "epgturning/epg_arrow_turnleft_focus.png");
		btnl->setPosition(Vec2(cellWidth - 270, cellHeight / 2));
		btnl->setName("ID_BUT_ARROW_L");
		this->addNode(btnl);
	}

	Button* btnr = new (std::nothrow) Button();
	if (btnr && btnr->init()) {
		btnr->loadTextures("epgturning/epg_arrow_turnright_normal.png", "epgturning/epg_arrow_turnright_focus.png");
		btnr->setPosition(Vec2(cellWidth - 55, cellHeight / 2));
		btnr->setName("ID_BUT_ARROW_R");
		this->addNode(btnr);
	}

	Color3B color(91, 91, 91);
	Label* node = new (std::nothrow) Label;
	if (node)
	{
		node->setSystemFontName("general/SourceHanSansTWHK-Light.ttf");
		node->setSystemFontSize(32);
		std::string title = std::to_string(m_curValue);
		node->setString(title);
		node->setColor(color);
		node->setPosition(Vec2(cellWidth - 160, cellHeight / 2));
		node->setName("ID_TEXT_VALUE");
		this->addNode(node);
	}
}



bool AdjustControl::onKeyLeft(cocos2d::Node* rootNode)
{
	if (m_curValue > m_minValue) {
		m_curValue -= 1;
		if (m_curValue < m_minValue)
			m_curValue = m_minValue;
		setCurValue(m_curValue, rootNode);
		return true;
	}
	return false;
}
bool AdjustControl::onKeyRight(cocos2d::Node* rootNode)
{	
	if (m_curValue < m_maxValue) {
		m_curValue += 1;
		if (m_curValue > m_maxValue)
			m_curValue = m_maxValue;
		setCurValue(m_curValue, rootNode);
		return true;
	}
	return false;
}
bool AdjustControl::getItemCur(std::string& str)
{
	str = std::to_string(m_curValue);
	return true;
}
bool AdjustControl::setItemCur(const std::string& str)
{
	int value = std::atoi(str.c_str());
	if (value <= m_maxValue && value >= m_minValue)
	{
		m_curValue = value;
		setCurValue(m_curValue);
		return true;
	}
	return false;
}
void AdjustControl::setCurValue(int value, cocos2d::Node* rootNode)
{
	m_curValue = value;
	float width = (float)(m_curValue - m_minValue) / (float)(m_maxValue - m_minValue) * 400;
	std::string title = std::to_string(m_curValue);
	for (auto node : m_nodes)
	{
		if (node->getName() == "ID_TEXT_VALUE")
		{
			((Label*)node)->setString(title);
		}
		else if (node->getName() == "ID_PIC_SEEK_VALUE")
		{
			node->setPositionX(m_startPosition + width);
		}
	}
}

void AdjustControl::initNode(float cellWidth, float cellHeight)
{
	ImageView* seekbg = new (std::nothrow) ImageView();
	if (seekbg && seekbg->init())
	{
		seekbg->loadTexture("menu/seek_bkg.png");
		seekbg->setScale9Enabled(true);
		seekbg->setContentSize(Size(400,10));
		seekbg->setAnchorPoint(Vec2(0,0.5));
		m_startPosition = cellWidth - 510;
		seekbg->setPosition(Vec2(m_startPosition,cellHeight / 2 ));		
		this->addNode(seekbg);
	}

	ImageView* seek = new (std::nothrow) ImageView();
	if (seek && seek->init())
	{
		seek->loadTexture("menu/seek_thumb.png");
		float width = (float)(m_curValue - m_minValue) / (float)(m_maxValue - m_minValue) * 400;
		seek->setAnchorPoint(Vec2(0, 0.5));
		m_startPosition -= 20;
		seek->setPosition(Vec2(m_startPosition + width, cellHeight / 2));
		seek->setName("ID_PIC_SEEK_VALUE");
		this->addNode(seek);
	}

	Color3B color(91, 91, 91);
	Label* node = new (std::nothrow) Label;
	if (node)
	{
		node->setSystemFontName("general/SourceHanSansTWHK-Light.ttf");
		node->setSystemFontSize(32);
		std::string title = std::to_string(m_curValue);
		node->setString(title);
		node->setColor(color);
		node->setAnchorPoint(Vec2(1, 0.5));
		node->setPosition(Vec2(cellWidth - 45, cellHeight / 2));
		node->setName("ID_TEXT_VALUE");
		this->addNode(node);
	}

}