#include "common/RootLayer.h"

using namespace cocos2d::ui;

RootLayer::RootLayer()
{
	allowKey.clear();
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_MENU, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_MENU));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_HOME, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_HOME));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_POWER, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_POWER));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_SOURCE, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_SOURCE));
	allowKey.insert(std::make_pair((unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_MUTE, (unsigned int)cocos2d::EventKeyboard::KeyCode::KEY_TV_MUTE));
}

RootLayer::~RootLayer()
{
	allowKey.clear();
}

bool RootLayer::registKey(cocos2d::EventKeyboard::KeyCode key) {
	allowKey.insert(std::make_pair((unsigned int)key, (unsigned int)key));
	return true;
}

bool RootLayer::unregistKey(cocos2d::EventKeyboard::KeyCode key) {
	if (allowKey.end() != allowKey.find((unsigned int)key)) {
		allowKey.erase((unsigned int)key);
		return true;
	}
	return false;
}

bool RootLayer::stopPropagation(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (allowKey.end() != allowKey.find((unsigned int)keyCode)) {
		return true;
	}
	else {
		event->stopPropagation();
	}
	return true;

}
