#include "cocos2d.h"
#include "menu/TimeSubResponse.h"
#include "menu/SoundModeResponse.h"
#include "menu/MenuBaseUI.h"
#include "menu/DropdownUI.h"
USING_NS_CC;
using namespace cocos2d::ui;

TimeSubResponse::TimeSubResponse()
{
}
TimeSubResponse::~TimeSubResponse()
{

}
void TimeSubResponse::initData(std::vector<MenuControl*> menuvec)
{

}
void TimeSubResponse::addMenuFuncByName(const std::string &funcname)
{
	if (funcname == "ID_SET_CLOCK_MODE")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeClockMode);
	else if (funcname == "ID_SET_CLOCK_DAY")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeClockDaySet);
	else if (funcname == "ID_SET_CLOCK_MONTH")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeClockMonthSet);
	else if (funcname == "ID_SET_CLOCK_YEAR")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeClockYearSet);
	else if (funcname == "ID_SET_CLOCK_HOUR")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeClockHourSet);
	else if (funcname == "ID_SET_CLOCK_MINUTES")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeClockMinuteSet);
	else if (funcname == "ID_SET_CLOCK_TIMEZONE")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeClockZoneSet);
	else if (funcname == "ID_SET_SUMMER_TIME")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeClockSummerSet);

	else if (funcname == "ID_SET_ONTIME_REPEAT")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeOntimeRepeatSet);
	else if (funcname == "ID_SET_ONTIME_HOUR")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeOntimeHourSet);
	else if (funcname == "ID_SET_ONTIME_MINUTE")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeOntimeMinuteSet);
	else if (funcname == "ID_SET_ONTIME_INPUT")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeOntimeInputSet);
	else if (funcname == "ID_SET_ONTIME_CHANNEL")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeOntimeChannelMenu);
	else if (funcname == "ID_SET_ONTIME_VOLUME")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeOntimeVolumeSet);

	else if (funcname == "ID_SET_ONTIME_REPEAT")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeOfftimeRepeatSet);
	else if (funcname == "ID_SET_ONTIME_HOUR")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeOfftimeHourSet);
	else if (funcname == "ID_SET_ONTIME_MINUTE")
		addMenuFunc((Menu_CallFun)&TimeSubResponse::onTimeOfftimeMinuteSet);

}

void TimeSubResponse::onTimeClockZoneMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	this->addDropDownFunc((Menu_CallFun)&TimeSubResponse::onTimeClockZoneSet);
	Size cellSize(menu->getItemWidth(), menu->getItemHeight());
	Size tableSize(menu->getItemWidth(), menu->getTableHeight());
	Vec2 position(menu->getCellWidth(), 0);
	auto layer = DropdownUI::creatLayer(node, cellSize, tableSize, position, menuvec, menu, this);
}
void TimeSubResponse::onTimeClockMode(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void TimeSubResponse::onTimeClockDaySet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	
}

void TimeSubResponse::onTimeClockMonthSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}

void TimeSubResponse::onTimeClockYearSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void TimeSubResponse::onTimeClockHourSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
}
void TimeSubResponse::onTimeClockMinuteSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}

void TimeSubResponse::onTimeClockZoneSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void TimeSubResponse::onTimeClockSummerSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}

void TimeSubResponse::onTimeOntimeRepeatSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void TimeSubResponse::onTimeOntimeHourSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}

void TimeSubResponse::onTimeOntimeMinuteSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void TimeSubResponse::onTimeOntimeInputSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void TimeSubResponse::onTimeOntimeChannelMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void TimeSubResponse::onTimeOntimeVolumeSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	
}

void TimeSubResponse::onTimeOfftimeRepeatSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void TimeSubResponse::onTimeOfftimeHourSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	
}
void TimeSubResponse::onTimeOfftimeMinuteSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}