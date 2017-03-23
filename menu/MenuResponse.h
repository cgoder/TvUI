#ifndef  _MenuResponse_H_
#define  _MenuResponse_H_
#include "cocos2d.h"
#include "menu/MenuControl.h"
typedef void (cocos2d::Ref::*Menu_CallFun)(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
class MenuResponse:public cocos2d::Ref
{
public:
	MenuResponse();
	~MenuResponse();
	virtual void initData(std::vector<MenuControl*> menuvec) = 0;
	virtual void addMenuFuncByName(const std::string &funcname) = 0;
	void addDropDownFunc(Menu_CallFun func) { m_dropDownFunc = func; };
	Menu_CallFun getDropDownFunc() { return m_dropDownFunc; };
	void addMenuFunc(Menu_CallFun func) { m_menuFuncVec.push_back(func); };
	void addMenuFunc(Menu_CallFun func,int index) { m_menuFuncVec.insert(m_menuFuncVec.begin() + index, func); };
	Menu_CallFun getFunc(int idx);
protected:
	std::vector<Menu_CallFun> m_menuFuncVec;
	std::map<std::string, Menu_CallFun> m_menuFuncMap;
	Menu_CallFun m_dropDownFunc;
};
#endif

