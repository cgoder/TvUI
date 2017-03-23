#ifndef __TV_SCENE_H__
#define __TV_SCENE_H__

#include "cocos2d.h"
#include "tvplayer/tv_types.h"

class tvScene : public cocos2d::Layer
{
#define SCENE_TV "Scene_tv"
#define LAYER_TV "layer_tv"
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(tvScene);

public:
	/**
	 * [获取root scene上的layer]
	 *
	 * @method getRootLayer
	 *
	 * @return              [!nullptr==成功，nullptr==失败]
	 */
	static cocos2d::Node* getRootLayer(void);

	/**
	 * [获取tv play场景的layer]
	 *
	 * @method getTvLayer
	 *
	 * @return            [!nullptr==成功，nullptr==失败]
	 */
	static cocos2d::Node* getTvLayer(void);

	/**
	 * [信号通道切换。API将实际切换底层通道资源，并同时创建对应的layer node并返回。]
	 *
	 * @method sourceEntry
	 *
	 * @param  source      [信号源枚举]
	 *
	 * @return             [!nullptr==成功，nullptr==失败]
	 */
	static cocos2d::Node* sourceEntry(SKYTV_INPUT_SOURCE_TYPE source);
};

#endif // __TV_SCENE_H__
