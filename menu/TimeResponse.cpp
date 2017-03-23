#include "cocos2d.h"
#include "menu/TimeResponse.h"
#include "menu/TimeSubResponse.h"
#include "menu/MenuBaseUI.h"
#include "menu/DropdownUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
TimeResponse::TimeResponse()
{
}
TimeResponse::~TimeResponse()
{
}
void TimeResponse::initData(std::vector<MenuControl*> menuvec)
{

}
void TimeResponse::addMenuFuncByName(const std::string &funcname)
{
	if (funcname == "ID_SET_TIME_CLOCK")
		addMenuFunc((Menu_CallFun)&TimeResponse::onTimeClockMenu);
	else if (funcname == "ID_SET_TIME_SLEEP_MENU")
		addMenuFunc((Menu_CallFun)&TimeResponse::onTimeSleepMenu );
	else if (funcname == "ID_SET_TIME_AUTO_POWER")
		addMenuFunc((Menu_CallFun)&TimeResponse::onTimeAutoPower);
	else if (funcname == "ID_SET_TIME_CON_VIEW_TIMER")
		addMenuFunc((Menu_CallFun)&TimeResponse::onTimeContinueViewPower);
	else if (funcname == "ID_SET_TIME_ONTIMER")
		addMenuFunc((Menu_CallFun)&TimeResponse::onTimeOntimer);
	else if (funcname == "ID_SET_TIME_OFFTIMER")
		addMenuFunc((Menu_CallFun)&TimeResponse::onTimeOfftimer);
}
void TimeResponse::onTimeClockMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/timeclock.xml", new TimeSubResponse());
}
void TimeResponse::onTimeSleepMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	this->addDropDownFunc((Menu_CallFun)&TimeResponse::onTimeSleep);
	Size cellSize(menu->getItemWidth(),menu->getItemHeight());
	Size tableSize(menu->getItemWidth(), menu->getTableHeight());
	Vec2 position(menu->getCellWidth(),0);
	auto layer = DropdownUI::creatLayer(node, cellSize,tableSize,position,menuvec,menu, this);
}

void TimeResponse::onTimeSleep(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}

void TimeResponse::onTimeAutoPower(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void TimeResponse::onTimeContinueViewPower(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void TimeResponse::onTimeOntimer(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/timeontime.xml", new TimeResponse());
}

void TimeResponse::onTimeOfftimer(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/timeofftime.xml", new TimeResponse());
}
