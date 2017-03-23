#ifndef __PVR_RECORDING_THUMBNAIL__
#define __PVR_RECORDING_THUMBNAIL__
#include "cocos2d.h"
#include "common/SkyLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
class PVRRecodingThumbnail: public SkyLayer
{
public:
	PVRRecodingThumbnail();
	~PVRRecodingThumbnail();
	static cocos2d::Scene* createScene();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	virtual bool init();
	CREATE_FUNC(PVRRecodingThumbnail);
	
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); 
	void hidePVRUI();
	
	
};


#endif//__PVR_RECORDING_THUMBNAIL__