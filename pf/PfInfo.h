#ifndef __PFINFO_SCENE_H__
#define __PFINFO_SCENE_H__

#include "cocos2d.h"
#include "common/SkyLayer.h"
class PfInfo : public SkyLayer
{
#define LAYER_PFINFO "layer_pfinfo"
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(PfInfo);
public:
	static SkyLayer* getLayer(cocos2d::Node* node);
	static void show(cocos2d::Node* node);
	static void hide(cocos2d::Node* node);
	static void remove(cocos2d::Node* node);
	static bool visible(cocos2d::Node* node);
	// void refresh(float dt);
	void hidePf(float dt);
};

#endif // __PFINFO_SCENE_H__
