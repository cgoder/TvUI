#include "common/SkyLayer.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/UILayout.h"
#include "ui/UIWidget.h"
USING_NS_CC;
using namespace cocos2d::ui;

SkyLayer::SkyLayer()
{
	allowKey.clear();
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_GREEN, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_GREEN));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_MENU, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_MENU));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_E, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_E));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_SOURCE, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_SOURCE));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_I, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_I));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_HOME, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_HOME));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_H, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_H));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_POWER, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_POWER));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_Q, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_Q));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_MUTE, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_MUTE));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_U, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_U));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_DPAD_LEFT, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_DPAD_LEFT));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_VOLUME_DOWN, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_VOLUME_DOWN));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_DPAD_RIGHT, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_DPAD_RIGHT));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_VOLUME_UP, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_VOLUME_UP));

	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_LIST, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_LIST));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_S, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_S));//auto scan
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_R, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_R));//restore to default
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_ALT, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_ALT));//channel list
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_M, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_M));//MANU_SCAN
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_CTRL, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_CTRL));//channel edit

}

SkyLayer::~SkyLayer()
{
	log("~SkyLayer");
	allowKey.clear();
}

void SkyLayer::removeKeyListener(std::string subname)
{
	CommonApi::getInstance()->removeKeyListener(this->getName() + subname, _eventDispatcher);
}

void SkyLayer::addKeyListener( std::function<void(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*)> keyback, cocos2d::Node* node, std::string subname)
{
	auto listener = EventListenerKeyboard::create();
	listener->setEnabled(true);
	listener->onKeyPressed = keyback;
	if (node) {
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, node);
		//node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
	}
	else {
		_eventDispatcher->removeEventListenersForType(EventListener::Type::KEYBOARD);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}

	//CommonApi::getInstance()->addKeyListener(this->getName() + subname, keyback, _eventDispatcher);
}

void SkyLayer::registKey(cocos2d::EventKeyboard::KeyCode key) {
	allowKey.insert(std::make_pair((unsigned int)key, (unsigned int)key));
}

void SkyLayer::unregistKey(cocos2d::EventKeyboard::KeyCode key) {
	if (allowKey.end() != allowKey.find((unsigned int)key)) {
		allowKey.erase((unsigned int)key);
	}
}

void SkyLayer::stopPropagation(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event, bool without)
{
	if (allowKey.end() != allowKey.find((unsigned int)keyCode)) {
		return;
	}
	else {
		unused_event->stopPropagation();
	}
}
Node* SkyLayer::getRootByName_Common(Node *root, const std::string &name)
{

	if (!root)
	{
		return nullptr;
	}
	if (root->getName() == name)
	{
		return root;
	}

	const auto& arrayNode = root->getChildren();
	for (auto child : arrayNode)
	{
		Node*pNode = dynamic_cast<Node*>(child);
		if (pNode)
		{
			Node *res = getRootByName_Common(pNode, name);
			if (res)
			{
				return res;
			}
		}

	}

	return nullptr;
}
