#ifndef  _SoundResponse_H_
#define  _SoundResponse_H_
#include "cocos2d.h"
#include "menu/MenuResponse.h"

#include "menu/SoundMenu/SoundMenuExecutor.h"

class SoundResponse:
	public MenuResponse
{
public:
	SoundResponse();
	~SoundResponse();
	virtual void initData(std::vector<MenuControl*> menuvec);
	virtual void addMenuFuncByName(const std::string &funcname );
	void onSoundModeMenu(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onBalanceSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onAutoVulumeSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onSurroundSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onAnalogOutSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onDigitalOutSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onHDMISet( std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onDescription(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onAudioReset(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);

private:
	void onSoundCommonSet(MenuControl* menu);	

private:
	SoundMenuExecutor* m_soundMenuExecutor;

};
#endif

