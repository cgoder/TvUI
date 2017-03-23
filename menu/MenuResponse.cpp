#include "cocos2d.h"
#include "menu/MenuResponse.h"
USING_NS_CC;
using namespace cocos2d::ui;
MenuResponse::MenuResponse()
{
	m_dropDownFunc = nullptr;
}
MenuResponse::~MenuResponse()
{

}
Menu_CallFun MenuResponse::getFunc(int idx)
{
	Menu_CallFun func = nullptr;
	if (idx < m_menuFuncVec.size())
		func = m_menuFuncVec.at(idx);
	return func;
}