#ifndef  _SoundModeResponse_H_
#define  _SoundModeResponse_H_
#include "cocos2d.h"
#include "menu/MenuResponse.h"

#include "menu/SoundMenu/SoundMenuExecutor.h"
class SoundModeResponse:
	public MenuResponse
{
public:
	SoundModeResponse(SoundMenuExecutor* oundMenuExecutor = NULL);
	~SoundModeResponse();
	virtual void initData(std::vector<MenuControl*> menuvec);
	virtual void addMenuFuncByName(const std::string &funcname );
	void onSoundModeSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onEqualizerSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onSoundBassSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onTrebleSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onSound120HzSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onSound500HzSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onSound1500HzSet( std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onSound5KHzSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onSound10KHzSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);

	void onADSwitchSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onADVolumeSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onADBalanceSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
private:
	void onSoundModeCommonSet(MenuControl* menu);	

private:
	SoundMenuExecutor* m_soundMenuExecutor;


};
#endif

