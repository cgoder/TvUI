#include "cocos2d.h"
#include "menu/SoundModeResponse.h"
#include "menu/MenuBaseUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
SoundModeResponse::SoundModeResponse(SoundMenuExecutor* soundMenuExecutor)
{
	m_soundMenuExecutor = soundMenuExecutor;
}
SoundModeResponse::~SoundModeResponse()
{

}
void SoundModeResponse::initData(std::vector<MenuControl*> menuvec)
{
	m_soundMenuExecutor->SoundModeRefresh();

	for (auto menu : menuvec)
	{
		std::string name = menu->getName();

		auto itor = m_soundMenuExecutor->m_sound_setting.find(name);
		if(itor != m_soundMenuExecutor->m_sound_setting.end())
		{
			menu->setItemCur(itor->second);
			continue;
		}

		auto itor1 = m_soundMenuExecutor->m_ms_ui_Sound.find(name);
		if(itor1 != m_soundMenuExecutor->m_ms_ui_Sound.end())
			menu->setCurValue(itor1->second);
	}

}
void SoundModeResponse::addMenuFuncByName(const std::string &funcname)
{
	if (funcname == "ID_SET_SOUND_MODE1")
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onSoundModeSet);
	else if (funcname == "ID_SET_SOUND_EQU")
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onEqualizerSet );
	else if (funcname == "ID_SET_SOUND_BASS")
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onSoundBassSet);
	else if (funcname == "ID_SET_SOUND_TREBLE")
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onTrebleSet);
	else if (funcname == "ID_SET_SOUND_120HZ")
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onSound120HzSet);
	else if (funcname == "ID_SET_SOUND_500HZ")
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onSound500HzSet);
	else if (funcname == "ID_SET_SOUND_1.5KHZ")
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onSound1500HzSet);
	else if (funcname == "ID_SET_SOUND_5KHZ")
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onSound5KHzSet);
	else if (funcname == "ID_SET_SOUND_10KHZ")
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onSound10KHzSet);


	else if (funcname == "ID_SET_AD_SWITCH")
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onADSwitchSet);
	else if (funcname == "ID_SET_AD_VOLUME")
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onADVolumeSet);
	else if (funcname == "ID_SET_AD_BALANCE")
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onADBalanceSet);


	else 
		addMenuFunc((Menu_CallFun)&SoundModeResponse::onTrebleSet);
}
void SoundModeResponse::onSoundModeSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	std::string selectedItemMenuName, optionName;

	selectedItemMenuName = menu->getName();
	menu->getItemCur(optionName);
	m_soundMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
}

void SoundModeResponse::onEqualizerSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	std::string selectedItemMenuName, optionName;

	selectedItemMenuName = menu->getName();
	menu->getItemCur(optionName);
	m_soundMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
}

void SoundModeResponse::onSoundBassSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onSoundModeCommonSet(menu);
}
void SoundModeResponse::onTrebleSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onSoundModeCommonSet(menu);
}
void SoundModeResponse::onSound120HzSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onSoundModeCommonSet(menu);
}

void SoundModeResponse::onSound500HzSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onSoundModeCommonSet(menu);
}
void SoundModeResponse::onSound1500HzSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onSoundModeCommonSet(menu);
}
void SoundModeResponse::onSound5KHzSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onSoundModeCommonSet(menu);
}
void SoundModeResponse::onSound10KHzSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onSoundModeCommonSet(menu);
}
void SoundModeResponse::onADSwitchSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SoundModeResponse::onADVolumeSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}
void SoundModeResponse::onADBalanceSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}

void SoundModeResponse::onSoundModeCommonSet(MenuControl* menu)
{
	std::string selectedItemMenuName, optionName;
	int curValue;

	selectedItemMenuName = menu->getName();
	curValue = menu->getCurValue();
	optionName = to_string(curValue);
	m_soundMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
}

