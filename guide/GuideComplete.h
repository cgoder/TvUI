#ifndef  _TV_GUIDE_COMPLETE_H_
#define  _TV_GUIDE_COMPLETE_H_
#include "cocos2d.h"
#include "common/SkyLayer.h"
#include "ui/CocosGUI.h"
#include "tvplayer/TvPlayer.h"

class GuideComplete :public SkyLayer
{
public:
	GuideComplete();
	~GuideComplete();
	virtual bool init();
   	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	CREATE_FUNC(GuideComplete);	
	void initGuideComplete();  
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

};
#endif //_TV_GUIDE_COMPLETE_H_

