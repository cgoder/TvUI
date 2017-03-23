#ifndef __TV_REMINDER_H__
#define __TV_REMINDER_H__

#include "cocos2d.h"
#include "common/SkyLayer.h"

class TvReminder : public SkyLayer
{
#define LAYER_TVPLAYINFO "layer_tvreminder"
public:
	virtual bool init();
	CREATE_FUNC(TvReminder);
public:
	static cocos2d::Layer* getLayer(cocos2d::Node* node);
	static void refresh(cocos2d::Node* node);
	static void show(cocos2d::Node* node);
	static void hide(cocos2d::Node* node);
	static void remove(cocos2d::Node* node);
	static bool visible(cocos2d::Node* node);
};


#endif __TV_REMINDER_H__