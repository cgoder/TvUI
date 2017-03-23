#ifndef  _ROOTLAYER_H_
#define  _ROOTLAYER_H_
#include "cocos2d.h"

class RootLayer: public cocos2d::Layer
{
public:
	RootLayer();
	~RootLayer();

	virtual void show() { this->setVisible(true); } ;
	virtual void hide() { this->setVisible(false); } ;
	virtual void remove() { this->removeAllChildren(); if (this->getParent()) { this->getParent()->removeChild(this); } };
	virtual void refresh() {};

	//stop propagate.
	virtual bool stopPropagation(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	//regist keys for propagation.
	virtual bool registKey(cocos2d::EventKeyboard::KeyCode key);
	//unregist keys for propagation.
	virtual bool unregistKey(cocos2d::EventKeyboard::KeyCode key);
private:
	//these keys are allowed to propagate next node.
	std::map<unsigned int, unsigned int> allowKey;
};
#endif

