#ifndef __SET_PASSWORD_H__
#define __SET_PASSWORD_H__

#include "cocos2d.h"
#include "common/SkyLayer.h"
#include "ui/CocosGUI.h"

#define PIN_TEXT_TAG 0x100

class SetPassword : public SkyLayer
{
public:
	SetPassword();
	~SetPassword();
	static cocos2d::Scene* createScene();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	virtual bool init();
	CREATE_FUNC(SetPassword);
	
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); 
	int KeyCode2int(cocos2d::EventKeyboard::KeyCode keyCode);
		
	cocos2d::Sprite* sprite;
	bool enter_pin_started;
	int cur_pin_index;
	
};

#endif // __SET_PASSWORD_H__