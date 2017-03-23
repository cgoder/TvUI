#include "cocos2d.h"
#include "menu/MenuBaseUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
#include "menu/MainResponse.h"

#include "tinyxml2/tinyxml2.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
MenuBaseUI::MenuBaseUI()
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
MenuBaseUI::~MenuBaseUI()
{
	if (m_gridView)
	    m_gridView->removeAllChildrenWithCleanup(true);
	if (m_response)
		delete m_response;
	for (auto menu : m_menuCtrlVec)
	{
		if (menu)
		    delete menu;
	}
}
void MenuBaseUI::addMenuStr(char* str)
{
	m_menuNameVec.push_back(str);
	m_menuIdx++;
}

Layer* MenuBaseUI::creatLayer(cocos2d::Node* node, const std::string &xml, MenuResponse* response,Click_CallFun callFunc)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName(xml);
		if (tuning) {
			return tuning;
		}
		else {
			MenuBaseUI* pRet =(MenuBaseUI*) MenuBaseUI::create();
			pRet->setName(xml);
			pRet->addCallBack(callFunc);
			pRet->addResponse(response);
			pRet->initTableView(xml);
			node->addChild(pRet);
			return pRet;
		}
	}
	return nullptr;
}
void MenuBaseUI::parseTable(tinyxml2::XMLElement* ele)
{
	time_ms(__FUNCTION__, __LINE__);
	m_colNums = 1;
	m_cellNums = 1;
	m_rowNums = 1;
	for (auto e = ele->FirstChildElement(); e; e = e->NextSiblingElement()) {
		std::string name = e->Name();
		if (name == "rows")
			m_rowNums = std::atoi(e->GetText());
		else if (name == "cols")
			m_colNums = std::atoi(e->GetText());
		else if (name == "cellwidth")
			m_cellWidth = std::atof(e->GetText());
		else if (name == "cellheight")
			m_cellHeight = std::atof(e->GetText());
		else if (name == "positionx")
			m_positionx = std::atof(e->GetText());
		else if (name == "positiony")
			m_positiony = std::atof(e->GetText());
	}
	time_ms(__FUNCTION__, __LINE__);
}
bool MenuBaseUI::checkSignal(const std::string signal)
{
	if (signal == "All")
		return true;
	bool check = false;
	SKYTV_INPUT_SOURCE_TYPE type = skyTvMw::getInstance()->getInputSource();
	switch (type)
	{
	case SKYTV_INPUT_SOURCE_HDMI1:
		break;
	case SKYTV_INPUT_SOURCE_STORAGE:
		break;
	case SKYTV_INPUT_SOURCE_DTV:
		if (strstr(signal.c_str(), "ATV"))
			check = true;
		break;
	case SKYTV_INPUT_SOURCE_DVBT:
		if (strstr(signal.c_str(), "DVB-T"))
			check = true;
		break;
	case SKYTV_INPUT_SOURCE_ATV:
		if (strstr(signal.c_str(), "ATV"))
			check = true;
		break;
	case SKYTV_INPUT_SOURCE_DVBC:
		if (strstr(signal.c_str(), "DVB-C"))
			check = true;
		break;
	case SKYTV_INPUT_SOURCE_YPBPR:
		break;
	case SKYTV_INPUT_SOURCE_CVBS:
		if (strstr(signal.c_str(), "DVB-S"))
			check = true;
		break;
	case SKYTV_INPUT_SOURCE_VGA:
		break;
	case SKYTV_INPUT_SOURCE_DVBS:
		break;
	case SKYTV_INPUT_SOURCE_HDMI2:
		break;
	case SKYTV_INPUT_SOURCE_HDMI3:
		break;
	}
	return check;
}
void MenuBaseUI::parseMenu(tinyxml2::XMLElement* ele)
{	
	time_ms(__FUNCTION__, __LINE__);
	MenuControl* menu = nullptr;
	int type = 0;
	std::string signal = "All";
	for (auto attr = ele->FirstAttribute(); attr; attr = attr->Next()) {
		std::string attrname = attr->Name();
		if (attrname == "type")
			type = std::atoi(attr->Value());
		else if (attrname == "signal")
			signal = attr->Value();
	}
	if (!checkSignal(signal))
	{
		m_rowNums--;
		if (m_rowNums < 9)
		    m_positiony += m_cellHeight;
		return;
	}
	switch (type)
	{
	case 0:
		menu = new MenuControl();
		break;
	case 1:
		menu = new LFRaidoControl();
		break;
	case 2:
		menu = new SwitchControl();
		break;
	case 3:
		menu = new AdjustControl();
		break;
	case 4:
		menu = new UDRadioControl();
		break;
	case 6:
		menu = new NumsRadioControl();
		break;
	default:
		menu = new MenuControl();
		break;
	}
	menu->setType(type);
	for (auto e = ele->FirstChildElement(); e; e = e->NextSiblingElement()) {
		std::string name = e->Name();
		if (name == "image")
		{
			Node* node = parseImage(e);
			menu->addNode(node);
		}
		else if (name == "button")
		{
			Node* node = parseButton(e);
			menu->addNode(node);
		}
		else if (name == "text")
		{
			Node* node = parseText(e);
			menu->addNode(node);
		}
		else if (name == "id")
		{
			menu->setName(e->GetText());
			m_response->addMenuFuncByName(e->GetText());
		}
		else if (name == "item")
		{
			menu->addItem(e->GetText());//TODO
		}
		else if (name == "min")
		{
			menu->setMinValue(std::atoi(e->GetText()));
		}
		else if (name == "max")
		{
			menu->setMaxValue(std::atoi(e->GetText()));
		}
		else if (name == "cur")
		{
			menu->setItemCur(e->GetText());
		}
		else if (name == "itemcellwidth")
		{
			menu->setItemWidth(std::atof(e->GetText()));
		}
		else if (name == "itemcellheight")
		{
			menu->setItemHeight(std::atof(e->GetText()));
		}
		else if (name == "itemheight")
		{
			menu->setTableHeight(std::atof(e->GetText()));
		}
		else if (name == "assoc")
			menu->addAssocName(e->GetText());
		else if (name == "assocnum")
			menu->addAssocNums(std::atoi(e->GetText()));
	}
	time_ms(__FUNCTION__, __LINE__);
	menu->initNode(m_cellWidth, m_cellHeight);
	m_menuCtrlVec.push_back(menu);
	time_ms(__FUNCTION__, __LINE__);
}
cocos2d::Node* MenuBaseUI::parseText(tinyxml2::XMLElement* ele, cocos2d::Node* rootNode)
{
	time_ms(__FUNCTION__, __LINE__);
	Color3B color(91,91,91);
	Label* node = new (std::nothrow) Label;	
	if (node) {
		node->setSystemFontName("general/SourceHanSansTWHK-Light.ttf");
		Vec2 position;
		Vec2 anchor(0.5, 0.5);
		position.y = m_cellHeight / 2;
		position.x = 0;
		for (auto e = ele->FirstChildElement(); e; e = e->NextSiblingElement()) {
			log("gettext:%s\n", e->GetText());
			std::string name = e->Name();
			if (name == "titleid")
				node->setString(e->GetText());
			else if (name == "fontsize")
				node->setSystemFontSize(std::atof(e->GetText()));
			else if (name == "color")
			{
				int r, g, b, a;
				r = g = b = a = 0;
				sscanf(e->GetText(), "%d %d %d %d", &r, &g, &b, &a);
				color.r = r;
				color.b = b;
				color.g = g;
				node->setColor(color);
			}
			else if (name == "positionx")
				position.x = std::atoi(e->GetText());
			else if (name == "positiony")
				position.y = std::atoi(e->GetText());
			else if (name == "anchorx")
				anchor.x = std::atoi(e->GetText());
			else if (name == "anchory")
				anchor.y = std::atoi(e->GetText());
		}
		node->setAnchorPoint(anchor);
		node->setPosition(position);

		if (rootNode) {
			node->autorelease();
			rootNode->addChild(node);
		}
	}
	time_ms(__FUNCTION__, __LINE__);
	return node;
}
cocos2d::Node* MenuBaseUI::parseButton(tinyxml2::XMLElement* ele, cocos2d::Node* rootNode)
{
	time_ms(__FUNCTION__, __LINE__);
	Button* node = new (std::nothrow) Button();
	if (node && node->init()) {
		Vec2 position;
		Vec2 anchor(0.5, 0.5);
		position.y = m_cellHeight / 2;
		position.x = 0;
		for (auto e = ele->FirstChildElement(); e; e = e->NextSiblingElement()) {
			log("gettext:%s\n", e->GetText());
			std::string name = e->Name();
			if (name == "srcnor")
				node->loadTextureNormal(e->GetText());
			else if (name == "srcsel")
				node->loadTexturePressed(e->GetText());
			else if (name == "srcdis")
				node->loadTextureDisabled(e->GetText());
			else if (name == "width")
			{
				node->setScaleX(std::atof(e->GetText()) / node->getContentSize().width);
			}
			else if (name == "height")
			{
				node->setScaleY(std::atof(e->GetText()) / node->getContentSize().height);
			}
			else if (name == "positionx")
				position.x = std::atoi(e->GetText());
			else if (name == "positiony")
				position.y = std::atoi(e->GetText());
			else if (name == "anchorx")
				anchor.x = std::atoi(e->GetText());
			else if (name == "anchory")
				anchor.y = std::atoi(e->GetText());
		}
		node->setAnchorPoint(anchor);
		node->setPosition(position);
		if (rootNode) {
			node->autorelease();
			rootNode->addChild(node);
		}
	}
	time_ms(__FUNCTION__, __LINE__);
	return node;
}
cocos2d::Node* MenuBaseUI::parseImage(tinyxml2::XMLElement* ele, cocos2d::Node* rootNode)
{
	time_ms(__FUNCTION__, __LINE__);
	ImageView* node = new (std::nothrow) ImageView();
	if (node && node->init())
	{
		Vec2 position;
		Vec2 anchor(0, 0);
		position.y = 0;
		position.x = 0;
		for (auto e = ele->FirstChildElement(); e; e = e->NextSiblingElement()) {
			log("gettext:%s\n", e->GetText());
			std::string name = e->Name();
			if (name == "src")
				node->loadTexture(e->GetText());
			else if (name == "width")
			{
				node->setScaleX(std::atof(e->GetText()) / node->getContentSize().width);
			}
			else if (name == "height")
			{
				node->setScaleY(std::atof(e->GetText()) / node->getContentSize().height);
			}
			else if (name == "positionx")
				position.x = std::atoi(e->GetText());
			else if (name == "positiony")
				position.y = std::atoi(e->GetText());
			else if (name == "anchorx")
				anchor.x = std::atoi(e->GetText());
			else if (name == "anchory")
				anchor.y = std::atoi(e->GetText());
		}
		node->setAnchorPoint(anchor);
		node->setPosition(position);
		if (rootNode) {
			node->autorelease();
			rootNode->addChild(node);
		}
	}
	time_ms(__FUNCTION__, __LINE__);
	return node;
}
void MenuBaseUI::parseBg(tinyxml2::XMLElement* ele)
{
	time_ms(__FUNCTION__, __LINE__);
	for (auto e = ele->FirstChildElement(); e; e = e->NextSiblingElement()) {
		std::string name = e->Name();
		if (name == "image")
		{
			auto node = parseImage(e,this);
		}
		else if (name == "text")
			parseText(e, this);

	}
	time_ms(__FUNCTION__, __LINE__);
}
void MenuBaseUI::initData(const std::string& filename)
{
	time_ms(__FUNCTION__,__LINE__);
	FileUtils * fu = FileUtils::getInstance();
	auto doc = new tinyxml2::XMLDocument();
	doc->Parse(fu->getStringFromFile(filename).c_str());
	time_ms(__FUNCTION__, __LINE__);
	auto root = doc->RootElement();
	if (!root)
	{
		delete doc;
		return;
	}
	for (auto e = root->FirstChildElement(); e; e = e->NextSiblingElement()) {
		std::string str;
		std::string name;
		name = e->Name();
		log("element name :%s,text:%s\n", e->Name(),e->GetText());
		if (name == "bg")
			parseBg(e);
		else if (name == "table")
			parseTable(e);
		else if (name == "menu")
			parseMenu(e);
	}
	time_ms(__FUNCTION__, __LINE__);
	if (m_response)
		m_response->initData(m_menuCtrlVec);
	time_ms(__FUNCTION__, __LINE__);
	for (auto menu : m_menuCtrlVec)
	{
		menu->assocAction(m_menuCtrlVec);
	}
	time_ms(__FUNCTION__, __LINE__);
	delete doc;
}
void MenuBaseUI::initTableView(const std::string &xml)
{	
	initData(xml);	
	m_cellNums = m_rowNums;
	m_focusIdx = 0;// m_rowNums / 2;// (m_rowNums > 2) ? m_rowNums - 2 : m_rowNums;
	int height = m_cellHeight * m_rowNums;
	if (m_rowNums > 9)
		height = m_cellHeight * 9;

	GridView* tableView = GridView::create(this, Size(m_cellWidth, height));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->setPosition(Vec2(m_positionx, m_positiony));
	tableView->setClippingToBounds(false);
	tableView->setColNum(m_colNums);
	tableView->setRowNum(m_rowNums);
	tableView->setDelegate(this);
	m_gridView = tableView;
	this->addChild(tableView);
	tableView->reloadData();
	this->addKeyListener(CC_CALLBACK_2(ListFocusLayer::onKeyPressed, this), this);
	//tableView->scrollStep(m_focusIdx, cocos2d::ui::Widget::FocusDirection::DOWN);
}
bool MenuBaseUI::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		bRet = true;
	} while (0);

	return bRet;
}
void MenuBaseUI::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
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
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
		onKeyLeft();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
		onKeyRight();
		break;
	default:
		m_tempFocusIndex = m_focusIdx;
		ListFocusLayer::onKeyPressed(keyCode, unused_event);
		break;
	}
}
void MenuBaseUI::onKeyLeft()
{
	BaseTableViewCell* cell = dynamic_cast<BaseTableViewCell*> (m_gridView->cellAtIndex(m_focusIdx));
	if (cell)
	{
		MenuControl* ctrl = m_menuCtrlVec.at(m_focusIdx);
		if (ctrl->onKeyLeft(cell))
		{
			cell = dynamic_cast<BaseTableViewCell*> (m_gridView->cellAtIndex(m_focusIdx));
			if (cell)
				cell->onCellClick();
		}
	}
}
void MenuBaseUI::onKeyRight()
{
	BaseTableViewCell* cell = dynamic_cast<BaseTableViewCell*> (m_gridView->cellAtIndex(m_focusIdx));
	if (cell)
	{
		MenuControl* ctrl = m_menuCtrlVec.at(m_focusIdx);
		if (ctrl->onKeyRight(cell))
		{
			cell = dynamic_cast<BaseTableViewCell*> (m_gridView->cellAtIndex(m_focusIdx));
			if (cell)
				cell->onCellClick();
		}
	}
}
bool MenuBaseUI::onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction, bool isscroll )
{
	MenuControl* ctrl = m_menuCtrlVec.at(next);
	while (!ctrl->getEnable())
	{
		m_focusIdx = next;
		if (findNextFocus(next, direction))
			ctrl = m_menuCtrlVec.at(next);
		else
		{
			next = m_tempFocusIndex;
			break;
		}
	}
	m_focusIdx = m_tempFocusIndex;
	ListFocusLayer::onFocusChanged(next, direction, true);
	
	/*if (direction == cocos2d::ui::Widget::FocusDirection::UP)
	    m_gridView->scrollStep(1, cocos2d::ui::Widget::FocusDirection::UP);
	if (direction == cocos2d::ui::Widget::FocusDirection::DOWN)
		m_gridView->scrollStep(1, cocos2d::ui::Widget::FocusDirection::DOWN);*/
	return false;
}
void MenuBaseUI::addTitle(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 60);
	text->setAnchorPoint(Vec2(0, 0));
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(87,947));
	this->addChild(text);
}
void MenuBaseUI::addNote(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 32);
	text->setColor(Color3B(153, 153, 153));
	text->setAnchorPoint(Vec2(0, 0));
	text->setPosition(Vec2(387,964));
	this->addChild(text);
}
void MenuBaseUI::toExtensionsMainLayer(cocos2d::Ref *sender)
{
}

void MenuBaseUI::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
}

Size MenuBaseUI::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(m_cellWidth, m_cellHeight);
}

TableViewCell* MenuBaseUI::tableCellAtIndex(TableView *table, ssize_t idx)
{
	log("tableCellAtIndex,idx:%d,m_focusIdx:%d", idx, m_focusIdx);
	TableViewCell *cell = table->dequeueCell();
	//if (idx < m_menuIdx)
	{	
		if (!cell) {
			cell = new BaseTableViewCell();
			((BaseTableViewCell*)cell)->addBtnlClick((Click_CallFun)&MenuBaseUI::onCellClick, this);
			cell->autorelease();
			cell->setContentSize(Size(m_cellWidth,m_cellHeight));
		}
		if (m_gridView) {
			if (m_menuCtrlVec.size() > 0)
			{
				if (idx < m_menuCtrlVec.size()) {
					MenuControl* ctrl = m_menuCtrlVec.at(idx);
					cell->removeChildByName("ID_PIC_FOCUS");
					cell->removeAllChildrenWithCleanup(false);
					for (auto node : ctrl->getNodes())
					{
						if (node->getParent())
							node->getParent()->removeChild(node, false);
						cell->addChild(node);
					}
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

					Vector<cocos2d::Node*> pChildren = cell->getChildren();
					for (Node *node : pChildren)
					{
						if (dynamic_cast<Button*>(node))
						{
							((Button*)node)->setHighlighted(true);
						}
					}
				}
			}
		}
	}
	return cell;
}

ssize_t MenuBaseUI::numberOfCellsInTableView(TableView *table)
{
	return m_cellNums;
}

void MenuBaseUI::onCellClick(cocos2d::Node* node)
{
	if (m_response) {
		MenuControl* ctrl = m_menuCtrlVec.at(0);
		Menu_CallFun func = nullptr;		
		ctrl = m_menuCtrlVec.at(m_focusIdx);
		ctrl->assocAction(m_menuCtrlVec);
		func = m_response->getFunc(m_focusIdx);		
		if (func)
		{
			(m_response->*func)( m_menuCtrlVec, ctrl,m_focusIdx, this, node);
		}
	}
}
int64_t MenuBaseUI::time_ms(const std::string func, int line)
{
#ifdef PRINTF_TIME
	struct timeval now;
	gettimeofday(&now, NULL);
	int64_t time = now.tv_sec * 1000 + now.tv_usec / 1000;
	log("##############func:%s,line:%d,time: %lld###################\n", func.c_str(), line, time);
	return time;
#else
	return 0;
#endif
}