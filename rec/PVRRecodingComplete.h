#ifndef __PVR_RECORDING_COMPLETE__
#define __PVR_RECORDING_COMPLETE__
#include "cocos2d.h"
#include "common/SkyLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
class PVRRecodingComplete: public SkyLayer
{
public:
	PVRRecodingComplete();
	~PVRRecodingComplete();
	static cocos2d::Scene* createScene();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	virtual bool init();
	CREATE_FUNC(PVRRecodingComplete);
	
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); 
		
};


#endif//__PVR_RECORDING_COMPLETE__