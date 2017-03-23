#include "common/common.h"
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
CommonApi* CommonApi::sm_pCommonApi = nullptr;
CommonApi::CommonApi()
{
	_keydeal = false;
	_keypriority = 100;
}

CommonApi::~CommonApi()
{
	sm_pCommonApi = nullptr;
	log("~CommonApi");
}
CommonApi* CommonApi::getInstance()
{
	if (sm_pCommonApi == nullptr) {
		sm_pCommonApi = new CommonApi();
	}
	return sm_pCommonApi;
}
void CommonApi::removeKeyListener(std::string name, cocos2d::EventDispatcher* dispatcher)
{
	std::vector<std::string> mapKeyVec;
	mapKeyVec = keymap.keys();
	for (auto key : mapKeyVec)
	{
		log("key:%s,name:%s", key.c_str(), name.c_str());
		if (!key.find( name))
		{
			log("remove listener");
			auto listener = keymap.at(key);
			dispatcher->removeEventListener(listener);
			_keypriority++;
			keymap.erase(key);
			log("removeKeyListener _keypriority++:%d", _keypriority);
		}
	}
}
void CommonApi::addKeyListener(std::string name, cocos2d::EventListener* listener, cocos2d::EventDispatcher* dispatcher)
{
	auto _listener = keymap.at(name);
	if (_listener)
	{
		dispatcher->removeEventListener(_listener);
		_keypriority++;
		keymap.erase(name);
		log("add _keypriority++:%d", _keypriority);
	}
	_keypriority--;
	log("_keypriority:%d,name:%s", _keypriority, name.c_str());
	keymap.insert(name, listener);
	dispatcher->addEventListenerWithFixedPriority(listener, _keypriority);
}
void CommonApi::addKeyListener(std::string name, std::function<void(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*)> keyback, EventDispatcher* dispatcher)
{
	auto listener = EventListenerKeyboard::create();
	listener->setEnabled(true);
	listener->onKeyPressed = keyback;
	addKeyListener(name, listener, dispatcher);
}
