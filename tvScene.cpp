#include "tvScene.h"
#include "tvplay.h"
#include "sources/SignalSources.h"
#include "menu/firstMenu.h"
#include "eventdispacher/EventManager.h"
USING_NS_CC;


Scene* tvScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	scene->setName(SCENE_TV);

	// 'layer' is an autorelease object
	auto layer = tvScene::create();
	layer->setName(LAYER_TV);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool tvScene::init() {
	if ( !Layer::init() )
	{
		return false;
	}


	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event * event) {
		printf("\n\n\n######## tv,keyCode: %d ########\n\n\n", keyCode);

		switch (keyCode)
		{
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_TV_POWER:
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_Q:
#endif
			//TODO:: release all res.
			log("exit app...");
			Director::getInstance()->end();
			break;
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_TV_MUTE:
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_U:
#endif
			//TODO:: volume mute
			break;
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_TV_GREEN:
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_E:
#endif
			firstMenu::creatLayer(this, 1, 5, 5);
			break;
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_TV_SOURCE:
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_I:
#endif
			SignalSources::creatLayer(this);
			break;
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_VOLUME_UP:
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
#endif
			//TODO:: volume+
			break;
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_VOLUME_DOWN:
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_LEFT:
#endif
			//TODO:: volume-
			break;
		default:
			break;
		}

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Tvplay::getLayer(this);
	EventDispacherManager::EventManager_Creat(this);
	return true;

}

cocos2d::Node* tvScene::sourceEntry(SKYTV_INPUT_SOURCE_TYPE source) {
	cocos2d::Node* curNode = tvScene::getRootLayer();
	if (nullptr == curNode) {
		return nullptr;
	}

	switch (source) {
	case SKYTV_INPUT_SOURCE_ATV:
	case SKYTV_INPUT_SOURCE_DVBC:
	case SKYTV_INPUT_SOURCE_DVBC2:
	case SKYTV_INPUT_SOURCE_DVBS:
	case SKYTV_INPUT_SOURCE_DVBS2:
	case SKYTV_INPUT_SOURCE_DVBT:
	case SKYTV_INPUT_SOURCE_DVBT2:
	case SKYTV_INPUT_SOURCE_DTMB:
	case SKYTV_INPUT_SOURCE_ATSC:
	case SKYTV_INPUT_SOURCE_ISDB:
		skyTvMw::getInstance()->setInputSoruce(source);
		if (curNode->getChildrenCount() > 0) {
			curNode->removeAllChildren();
		}
		return Tvplay::getLayer(curNode);/*tv layer*/
	case SKYTV_INPUT_SOURCE_CVBS:
	case SKYTV_INPUT_SOURCE_CVBS2:
	case SKYTV_INPUT_SOURCE_CVBS3:
	case SKYTV_INPUT_SOURCE_CVBS4:
		skyTvMw::getInstance()->setInputSoruce(source);
		if (curNode->getChildrenCount() > 0) {
			curNode->removeAllChildren();
		}
		return nullptr;
	//return CVBS::creatLayer(curNode);
	case SKYTV_INPUT_SOURCE_YPBPR:
	case SKYTV_INPUT_SOURCE_YPBPR2:
	case SKYTV_INPUT_SOURCE_YPBPR3:
	case SKYTV_INPUT_SOURCE_YPBPR4:
		skyTvMw::getInstance()->setInputSoruce(source);
		if (curNode->getChildrenCount() > 0) {
			curNode->removeAllChildren();
		}
		return nullptr;
	//return YPBPR::creatLayer(curNode);
	case SKYTV_INPUT_SOURCE_SVIDEO:
	case SKYTV_INPUT_SOURCE_SVIDEO2:
	case SKYTV_INPUT_SOURCE_SVIDEO3:
	case SKYTV_INPUT_SOURCE_SVIDEO4:
		skyTvMw::getInstance()->setInputSoruce(source);
		if (curNode->getChildrenCount() > 0) {
			curNode->removeAllChildren();
		}
		return nullptr;
	//return SVIDEO::creatLayer(curNode);
	case SKYTV_INPUT_SOURCE_DVI:
	case SKYTV_INPUT_SOURCE_DVI2:
	case SKYTV_INPUT_SOURCE_DVI3:
	case SKYTV_INPUT_SOURCE_DVI4:
		skyTvMw::getInstance()->setInputSoruce(source);
		if (curNode->getChildrenCount() > 0) {
			curNode->removeAllChildren();
		}
		return nullptr;
	//return DVI::creatLayer(curNode);
	case SKYTV_INPUT_SOURCE_VGA:
		skyTvMw::getInstance()->setInputSoruce(source);
		if (curNode->getChildrenCount() > 0) {
			curNode->removeAllChildren();
		}
		return nullptr;
	//return VGA::creatLayer(curNode);
	case SKYTV_INPUT_SOURCE_HDMI1:
	case SKYTV_INPUT_SOURCE_HDMI2:
	case SKYTV_INPUT_SOURCE_HDMI3:
	case SKYTV_INPUT_SOURCE_HDMI4:
		skyTvMw::getInstance()->setInputSoruce(source);
		if (curNode->getChildrenCount() > 0) {
			curNode->removeAllChildren();
		}
		return nullptr;
	//return HDMI::creatLayer(curNode);
	case SKYTV_INPUT_SOURCE_STORAGE:
	case SKYTV_INPUT_SOURCE_STORAGE2:
	case SKYTV_INPUT_SOURCE_STORAGE3:
	case SKYTV_INPUT_SOURCE_STORAGE4:
		skyTvMw::getInstance()->setInputSoruce(source);
		if (curNode->getChildrenCount() > 0) {
			curNode->removeAllChildren();
		}
		return nullptr;
	//return USB::creatLayer(curNode);
	default:
		return nullptr;
	}
	return nullptr;
}

cocos2d::Node* tvScene::getRootLayer(void) {
	cocos2d::Scene* curScene = Director::getInstance()->getRunningScene();
	if (curScene) {
		cocos2d::Node* tvSysLayer = curScene->getChildByName(LAYER_TV);
		return tvSysLayer;
	} else {
		return nullptr;
	}
	return nullptr;
}

cocos2d::Node* tvScene::getTvLayer(void) {
	cocos2d::Node* rooLayer = getRootLayer();
	if (rooLayer) {
		cocos2d::Node* tvLayer = rooLayer->getChildByName(LAYER_TVPLAY);
		return tvLayer;
	} else {
		return nullptr;
	}
	return nullptr;
}
