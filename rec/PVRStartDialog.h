#ifndef __PVR_START_DIALOG__
#define __PVR_START_DIALOG__

#include "cocos2d.h"
#include "common/SkyLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
class PVRStartDialog: public SkyLayer
{
public:
	PVRStartDialog();
	~PVRStartDialog();
	static cocos2d::Scene* createScene();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	virtual bool init();
	CREATE_FUNC(PVRStartDialog);
	
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); 
	
	
	
};


#endif //__PVR_START_DIALOG__