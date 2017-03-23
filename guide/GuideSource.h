#ifndef  _TV_GUIDE_SOURCE_H_
#define  _TV_GUIDE_SOURCE_H_
#include "cocos2d.h"
#include "common/SkyLayer.h"
#include "ui/CocosGUI.h"
#include "tvplayer/TvPlayer.h"

enum
{
	GUIDESOURCE_ATV,
	GUIDESOURCE_DVB_C,
	GUIDESOURCE_DVB_T,	
	GUIDESOURCE_SKIP
};


class GuideSource :public SkyLayer
{
public:
	GuideSource();
	~GuideSource();
	virtual bool init();
   	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	CREATE_FUNC(GuideSource);	
	void initGuideSource();  
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void changeIconImage();
	int cur_index;

};
#endif //_TV_GUIDE_SOURCE_H_

