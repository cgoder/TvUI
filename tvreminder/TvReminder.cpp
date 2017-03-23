#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "tvreminder/TvReminder.h"
#include "common/common.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

static std::string DefaultPlayStr("No Signal\n\nPress key 'S' to scan");

cocos2d::Layer* TvReminder::getLayer(cocos2d::Node* node)
{
	cocos2d::Layer* tvReminder = nullptr;
	if (node) {
		tvReminder = (cocos2d::Layer*)node->getChildByName(LAYER_TVPLAYINFO);
		if (tvReminder) {
			return tvReminder;
		}
		else {
			tvReminder = TvReminder::create();
			if (tvReminder) {
				node->setName(LAYER_TVPLAYINFO);
				node->addChild(tvReminder);
			}
			return tvReminder;
		}
	}
	return tvReminder;
}


bool TvReminder::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size vSize = Director::getInstance()->getVisibleSize();

	TvPlayer* tvPlayer = Get_TvPlayer();

	auto label = Label::createWithTTF("", "general/SourceHanSansTWHK-Light.ttf", 60);
	if (label) {
		label->setPosition(Vec2(vSize.width / 2, vSize.height / 2));
		label->setName("Label_Info");
		addChild(label);
	}

	return true;
}

void TvReminder::show(cocos2d::Node* node) {
	if (TvReminder::getLayer(node)) {
		TvReminder::getLayer(node)->setVisible(true);
	}

	refresh(node);
}

void TvReminder::hide(cocos2d::Node* node) {
	if (TvReminder::getLayer(node)) {
		TvReminder::getLayer(node)->setVisible(false);
	}
}

void TvReminder::remove(cocos2d::Node* node) {
	if (TvReminder::getLayer(node)) {
		TvReminder::getLayer(node)->removeAllChildren();
		if (TvReminder::getLayer(node)->getParent()) {
			TvReminder::getLayer(node)->getParent()->removeChild(TvReminder::getLayer(node));
		}
	}
}


bool TvReminder::visible(cocos2d::Node* node) {
	if (TvReminder::getLayer(node)) {
		return TvReminder::getLayer(node)->isVisible();
	} else {
		return false;
	}
}

void TvReminder::refresh(cocos2d::Node* node) {
	auto tvReminder = TvReminder::getLayer(node);
	if (nullptr == tvReminder) {
		return;
	}

	TvPlayer* tvPlayer = Get_TvPlayer();
	if (!tvPlayer) {
		log("Can not get tvPlayer.");
		return;
	}
	else if (0 == tvPlayer->getChannelCount()) {
		auto label = tvReminder->getChildByName<Label*>("Label_Info");
		if (label) {
			label->setString(DefaultPlayStr);
		}
	}
	else {
		CChannel* tmpCh = tvPlayer->getCurChannel();
		if (tmpCh) {
			// auto label = tvReminder->getChildByName<Label*>("Label_Info");
			// if (label) {
			// 	label->setString(tmpCh->getName());
			// }
		}
		else {
			//TODO::ÏÔÊ¾´íÎóÌáÊ¾
		}
	}
}
