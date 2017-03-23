#include "cocos2d.h"
#include "menu/SoundResponse.h"
#include "menu/SoundModeResponse.h"
#include "menu/MenuBaseUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
SoundResponse::SoundResponse()
{
	m_soundMenuExecutor = new SoundMenuExecutor;
}
SoundResponse::~SoundResponse()
{
	if (m_soundMenuExecutor != NULL){
		delete m_soundMenuExecutor;
		m_soundMenuExecutor = NULL;
	}
}

void SoundResponse::initData(std::vector<MenuControl*> menuvec)
{
	m_soundMenuExecutor->SoundSettingRefresh();
	//m_soundMenuExecutor->SoundModeRefresh();

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

void SoundResponse::addMenuFuncByName(const std::string &funcname)
{
	if (funcname == "ID_SET_SOUND_MODE")
		addMenuFunc((Menu_CallFun)&SoundResponse::onSoundModeMenu);
	else if (funcname == "ID_SET_SOUND_BALANCE")
		addMenuFunc((Menu_CallFun)&SoundResponse::onBalanceSet );
	else if (funcname == "ID_SET_SOUND_AUTO_VULUME")
		addMenuFunc((Menu_CallFun)&SoundResponse::onAutoVulumeSet);
	else if (funcname == "ID_SET_SOUND_SURROUND")
		addMenuFunc((Menu_CallFun)&SoundResponse::onSurroundSet);
	else if (funcname == "ID_SET_SOUND_AAOUTPUT")
		addMenuFunc((Menu_CallFun)&SoundResponse::onAnalogOutSet);
	else if (funcname == "ID_SET_SOUND_DAOUTPUT")
		addMenuFunc((Menu_CallFun)&SoundResponse::onDigitalOutSet);
	else if (funcname == "ID_SET_SOUND_HDMI")
		addMenuFunc((Menu_CallFun)&SoundResponse::onHDMISet);
	else if (funcname == "ID_SET_SOUND_DES")
		addMenuFunc((Menu_CallFun)&SoundResponse::onDescription);
	else if (funcname == "ID_SET_SOUND_RESET")
		addMenuFunc((Menu_CallFun)&SoundResponse::onAudioReset);
	else 
		addMenuFunc((Menu_CallFun)&SoundResponse::onDescription);
}
void SoundResponse::onSoundModeMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	auto layer = MenuBaseUI::creatLayer(rootNode, "xml/soundmode.xml", new SoundModeResponse(m_soundMenuExecutor));
}
void SoundResponse::onBalanceSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	std::string selectedItemMenuName, optionName;
	int curValue;

	selectedItemMenuName = menu->getName();
	curValue = menu->getCurValue();
	optionName = to_string(curValue);
	m_soundMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
}
void SoundResponse::onAutoVulumeSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onSoundCommonSet(menu);
}
void SoundResponse::onSurroundSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onSoundCommonSet(menu);
}
void SoundResponse::onAnalogOutSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onSoundCommonSet(menu);
}

void SoundResponse::onDigitalOutSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onSoundCommonSet(menu);
}
void SoundResponse::onHDMISet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	onSoundCommonSet(menu);
}
void SoundResponse::onDescription(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{
	//auto layer = MenuBaseUI::creatLayer(rootNode, "xml/sounddes.xml", new SoundModeResponse());
}
void SoundResponse::onAudioReset(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node)
{

}

void SoundResponse::onSoundCommonSet(MenuControl* menu)
{
	std::string selectedItemMenuName, optionName;

	selectedItemMenuName = menu->getName();
	menu->getItemCur(optionName);
	m_soundMenuExecutor->menuRelativeOptionCallbackFun(selectedItemMenuName, optionName);
}


