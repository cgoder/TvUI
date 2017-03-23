#ifndef  _PictureResponse_H_
#define  _PictureResponse_H_
#include "cocos2d.h"
#include "menu/MenuResponse.h"

#include "menu/PictureMenu/PictureMenuExecutor.h"

class PictureResponse:
	public MenuResponse
{
public:
	PictureResponse();
	~PictureResponse();
	virtual void initData(std::vector<MenuControl*> menuvec);
	virtual void addMenuFuncByName(const std::string &funcname );
	void onPicModeSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPicBacklightSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPicContrastSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPicBrightnessSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPicColorSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPicAspectSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPicSharpnessSet( std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	
	void onPicColorTempSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPicDynmicNoiseSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPicMpegNoiseSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPicDynmicContrastSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPicLightSensorSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPictureSensorSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPicFilmModeSet(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);
	void onPictureReset(std::vector<MenuControl*> menuvec, MenuControl* menu, int selidx, cocos2d::Node* rootNode, cocos2d::Node* node);

private:
	void onPictureCommonSet(MenuControl* menu);

private:
	PictureMenuExecutor* m_pictureMenuExecutor;
};
#endif

