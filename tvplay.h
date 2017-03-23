#ifndef __TV_PLAY_H__
#define __TV_PLAY_H__

#include "common/SkyLayer.h"

class Tvplay : public SkyLayer
{
#define LAYER_TVPLAY "layer_tvplay"
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Tvplay);
public:
	static SkyLayer* getLayer(cocos2d::Node* node);
};

#endif // __TV_PLAY_H__
