#ifndef __CHANNEL_PIN_H__
#define __CHANNEL_PIN_H__

#include "cocos2d.h"
#include "common/SkyLayer.h"
#include "ui/CocosGUI.h"

#define PIN_TEXT_TAG 0x100
#define PIN_DIALOG_TAG 0x150


class ChannelPin : public SkyLayer
{
public:
	ChannelPin();
	~ChannelPin();
	static cocos2d::Scene* createScene();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	virtual bool init();
	CREATE_FUNC(ChannelPin);
	
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event); 
	int KeyCode2int(cocos2d::EventKeyboard::KeyCode keyCode);
		
	cocos2d::Sprite* sprite;
	bool enter_pin_started;
	int cur_pin_index;
	
};

#endif // __CHANNEL_PIN_H__