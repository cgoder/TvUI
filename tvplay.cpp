#include "tvplay.h"
#include "tvplayer/TvPlayer.h"
#include "tvplayer/tv_common.h"
#include "tvreminder/TvReminder.h"
#include "tvplayer/tv_types.h"
#include "pf/PfInfo.h"
#include "AutoTuning/AutoTuning.h"
// #include "cocostudio/CocoStudio.h"
// #include "ui/CocosGUI.h"
#include "ChannelList/ChannelList.h"
#include "ManualScan/ManualScan.h"
#include "ChannelEdit/ChannelEdit.h"
#include "epg/EpgList.h"
#include "rec/PVRUI.h"
#include "localMedia/deviceDetect.h"
#include "guide/GuideCountry.h"
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

SkyLayer* Tvplay::getLayer(cocos2d::Node* node) {
	SkyLayer* Tvplay = nullptr;
	if (node) {
		Tvplay = (SkyLayer*)node->getChildByName(LAYER_TVPLAY);
		if (Tvplay) {
			return Tvplay;
		}
		else {
			printf("\n!!!!!!!!!!!! creat Tvplay !!!!!!!!!!!!\n");

			Tvplay = Tvplay::create();
			if (Tvplay) {
				Tvplay->setName(LAYER_TVPLAY);
				node->addChild(Tvplay);
			}
			return Tvplay;
		}
	}
	return Tvplay;
}

bool Tvplay::init() {
	if (!Layer::init())
	{
		return false;
	}

	// Get_TvPlayer()->playCur();
	// TvReminder::show(this);
	// PfInfo::show(this);
#ifndef _WIN32
	deviceDetect::getInstance()->startDeviceDetect();
#endif

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event * event) {
		this->stopPropagation(keyCode, event);
		printf("\n\n\n######## tvplayer,keyCode: %d ########\n\n\n", keyCode);
		// std::vector<CChannel*> tmpAll;

		switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_0:
		case cocos2d::EventKeyboard::KeyCode::KEY_1:
		case cocos2d::EventKeyboard::KeyCode::KEY_2:
		case cocos2d::EventKeyboard::KeyCode::KEY_3:
		case cocos2d::EventKeyboard::KeyCode::KEY_4:
		case cocos2d::EventKeyboard::KeyCode::KEY_5:
		case cocos2d::EventKeyboard::KeyCode::KEY_6:
		case cocos2d::EventKeyboard::KeyCode::KEY_7:
		case cocos2d::EventKeyboard::KeyCode::KEY_8:
		case cocos2d::EventKeyboard::KeyCode::KEY_9:
			if (Get_TvPlayer()) {
				if (0 != Get_TvPlayer()->getChannelCount()) {
					break;
				}
			}

			//tvPlayer->play(keyCode-cocos2d::EventKeyboard::KeyCode::KEY_0);
			break;
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_TV_INFO:
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
#endif
			if (skyTvMw::getInstance()->isDtvSource()) {
				if (Get_TvPlayer()) {
					if (0 != Get_TvPlayer()->getChannelCount()) {
						if (PfInfo::visible(this)) {
							PfInfo::show(this);
						}
					}
					// printf("######### count:%d ########\n", Get_TvPlayer()->getChannelCount());
				}
			}
			break;
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_TV_BACK:
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:
#endif
			if (Get_TvPlayer()) {
				if (0 != Get_TvPlayer()->getChannelCount()) {
					Get_TvPlayer()->playBack();
					TvReminder::show(this);
					PfInfo::show(this);
				}
			}
			break;
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_UP:
		case cocos2d::EventKeyboard::KeyCode::KEY_CHANNEL_UP:
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
#endif
			if (Get_TvPlayer()) {
				if (0 != Get_TvPlayer()->getChannelCount()) {
					Get_TvPlayer()->playNext();
					TvReminder::show(this);
					PfInfo::show(this);
				}
			}
			break;
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_DOWN:
		case cocos2d::EventKeyboard::KeyCode::KEY_CHANNEL_DOWN:
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
#endif
			if (Get_TvPlayer()) {
				if (0 != Get_TvPlayer()->getChannelCount()) {
					Get_TvPlayer()->playPrev();
					TvReminder::show(this);
					PfInfo::show(this);
				}
			}
			break;
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_TV_EPG:
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_G:
#endif
			if (skyTvMw::getInstance()->isDtvSource()) {
				EpgList::creatLayer(this);
			}
			break;
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_TV_LIST://ChannelList
//M by frank for cross platforms of windows and linux.
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_ALT://ChannelList
#endif
			if (this->getChildrenCount() > 0) {
				this->removeAllChildren();
			}
			ChannelList::creatLayer(this);
			break;
#ifndef _WIN32
		case cocos2d::EventKeyboard::KeyCode::KEY_TV_RECORD:
#else
		case cocos2d::EventKeyboard::KeyCode::KEY_SHIFT:
#endif
		{

			if (this->getChildrenCount() > 0) {
				this->removeAllChildren();
			}
			PVRUI::creatLayer(this);
//			Node *node = this->getChildByName("PVRUI");
//			PVRUI* pvr = static_cast<PVRUI*>(node);
//			pvr->addProgramRecord();

			break;
		}
		
		
		case cocos2d::EventKeyboard::KeyCode::KEY_B:
		{
			if (this->getChildrenCount() > 0) {
				this->removeAllChildren();
			}
			std::vector<std::string> countrylist;
			countrylist.push_back("French");
			countrylist.push_back("Germany");
			countrylist.push_back("Spain");
			countrylist.push_back("Italy");
			countrylist.push_back("Russia");
			countrylist.push_back("Czech");
			countrylist.push_back("Bulgaria");
			countrylist.push_back("UK");
			
			countrylist.push_back("Hungary");
			countrylist.push_back("Lithuania");
			countrylist.push_back("Kazakhstan");
			countrylist.push_back("Latvia");
			countrylist.push_back("Ireland");
			countrylist.push_back("Portugal");
			countrylist.push_back("Switzerland");
			countrylist.push_back("Turkey");
			
			countrylist.push_back("Saudi");
			countrylist.push_back("Jordan");
			countrylist.push_back("Vietnam");
			countrylist.push_back("India");
			countrylist.push_back("Aaaa");
			countrylist.push_back("Bbbb");
			countrylist.push_back("Cccc");
			countrylist.push_back("Dddd");
			
			countrylist.push_back("Eeee");
			countrylist.push_back("Ffff");
			countrylist.push_back("Gggg");
			countrylist.push_back("Hhhh");
			countrylist.push_back("Iiii");
			countrylist.push_back("Jjjj");
			countrylist.push_back("Kkkk");
			countrylist.push_back("Llll");
			
			int cols = (countrylist.size() % 5) == 0 ? (countrylist.size() / 5) : (countrylist.size() / 5 + 1);
			
			GuideCountry* pRet = (GuideCountry*)GuideCountry::creatLayer(this,cols,5,countrylist.size());
				
			pRet->setCountryVec(countrylist);
			pRet->initTableView();
			break;
		}
		

		case cocos2d::EventKeyboard::KeyCode::KEY_TV_YELLOW:
			if (this->getChildrenCount() > 0) {
				this->removeAllChildren();
			}
			Manual_Scan::creatLayer(this);
		default:
			break;
		}

	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;

}
