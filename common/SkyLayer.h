#ifndef  _SKYLAYER_H_
#define  _SKYLAYER_H_
#include "cocos2d.h"
#include "common/common.h"
class SkyLayer: public cocos2d::Layer
{
public:
	SkyLayer();
	~SkyLayer();
	void removeKeyListener(std::string subname = "KEY");
	void addKeyListener(std::function<void(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*)> keyback, cocos2d::Node* node = nullptr, std::string subname = "KEY");

	virtual bool skyShow(cocos2d::Node* node) { if (node) { node->setVisible(true); } return true; };
	virtual void skyHide(cocos2d::Node* node) { if (node) { node->setVisible(false); } };
	virtual void skyRemove() { this->removeAllChildren(); if (this->getParent()) { this->getParent()->removeChild(this); } };
	virtual void skyRefresh() {};

	//stop propagate.
	void stopPropagation(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event, bool without = true);

	//regist keys for propagation.
	virtual void registKey(cocos2d::EventKeyboard::KeyCode key);
	//unregist keys for propagation.
	virtual void unregistKey(cocos2d::EventKeyboard::KeyCode key);
	Node* getRootByName_Common(Node *root, const std::string &name);
private:
	//these keys are allowed to propagate next node.
	std::map<unsigned int, unsigned int> allowKey;
};
#endif

