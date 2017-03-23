#include "pf/PfInfo.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "common/common.h"
#include "tvplayer/CEpgManager.h"
#include "tvplayer/tv_common.h"
#include "tvplayer/CTime.h"
#include "tvScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
int64_t time_ms(void)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return (now.tv_sec  * 1000 + now.tv_usec / 1000);
}

SkyLayer* PfInfo::getLayer(cocos2d::Node* node)
{
	if (!skyTvMw::getInstance()->isDtvSource()) {
		return nullptr;
	}

	SkyLayer* pf = nullptr;
	if (node) {
		pf = (SkyLayer*)node->getChildByName(LAYER_PFINFO);
		if (pf) {
			return pf;
		}
		else {
			// printf("\n!!!!!!!!!!!! creat PfInfo !!!!!!!!!!!!\n");

			pf = PfInfo::create();
			if (pf) {
				pf->setName(LAYER_PFINFO);
				node->addChild(pf);
			}
			return pf;
		}
	}
	return pf;
}

bool PfInfo::init()
{
	FUNC_ENTRY();
	if (!Layer::init())
	{
		return false;
	}


	return true;
}

void PfInfo::hidePf(float dt) {
	//this->setVisible(false);
	PfInfo::remove(tvScene::getRootLayer());
}

void refresh(float dt) {
	FUNC_ENTRY();

	if (!Get_TvPlayer()) {
		printf("Can not get Get_TvPlayer().");
		return;
	}

	SkyLayer* pf = PfInfo::getLayer(tvScene::getRootLayer());
	if (!pf) {
		return;
	}

	auto rootNode = pf->getChildByName("pfroot");
	if (!rootNode) {
		rootNode = CSLoader::createNode("PfInfo.csb");
		if (!rootNode) {
			return;
		}
		else {
			rootNode->setName("pfroot");
			pf->addChild(rootNode);
		}

		if (1) {
			//regist key for propagation.
			pf->registKey(cocos2d::EventKeyboard::KeyCode::KEY_CHANNEL_UP);
			pf->registKey(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW);
			pf->registKey(cocos2d::EventKeyboard::KeyCode::KEY_DPAD_UP);
			pf->registKey(cocos2d::EventKeyboard::KeyCode::KEY_DPAD_DOWN);
			pf->registKey(cocos2d::EventKeyboard::KeyCode::KEY_CHANNEL_DOWN);
			pf->registKey(cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW);

			//注册按键响应listener
			auto listener = EventListenerKeyboard::create();
			listener->onKeyPressed = [pf](EventKeyboard::KeyCode keyCode, Event * event) {
				cocos2d::ui::ImageView* lock = nullptr;
				cocos2d::ui::ImageView* fav = nullptr;
				pf->stopPropagation(keyCode, event);
				unsigned int index = Get_TvPlayer()->getLastChannelIndex();


				switch (keyCode)
				{
#ifndef _WIN32
				case cocos2d::EventKeyboard::KeyCode::KEY_TV_BACK:
				case cocos2d::EventKeyboard::KeyCode::KEY_TV_EXIT:
				case cocos2d::EventKeyboard::KeyCode::KEY_TV_INFO:
#else
				case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
				case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
#endif
					PfInfo::remove(pf->getParent());
					break;
#ifndef _WIN32
				case cocos2d::EventKeyboard::KeyCode::KEY_TV_RED:
#else
				case cocos2d::EventKeyboard::KeyCode::KEY_F:
#endif
					if (0 == Get_TvPlayer()->getChannelCount()) {
						break;
					}

					if (!pf->isVisible()) {
						break;
					}
					fav = pf->getChildByName("pfroot")
					      ->getChildByName<ui::Layout*>("ChPf_ve")
					      ->getChildByName<ui::ImageView*>("ChPf_bg")
					      ->getChildByName<ui::Text*>("ChPf_index")
					      ->getChildByName<ui::ImageView*>("ChPf_chFav");
					if (!fav) {
						break;
					}
					if (nullptr == Get_TvPlayer()->getCurChannel()) {
						break;
					}

					if (Get_TvPlayer()->getCurChannel()->isFav()) {
						Get_TvPlayer()->setChannelStatus(index, SKYTV_CHANNEL_OPT_FAV, false);
						fav->setVisible(false);
					}
					else {
						Get_TvPlayer()->setChannelStatus(index, SKYTV_CHANNEL_OPT_FAV, true);
						fav->setVisible(true);
					}
					break;
#ifndef _WIN32
				case cocos2d::EventKeyboard::KeyCode::KEY_TV_YELLOW:
#else
				case cocos2d::EventKeyboard::KeyCode::KEY_L:
#endif
					if (0 == Get_TvPlayer()->getChannelCount()) {
						break;
					}

					if (!pf->isVisible()) {
						break;
					}
					lock = pf->getChildByName("pfroot")
					       ->getChildByName<ui::Layout*>("ChPf_ve")
					       ->getChildByName<ui::ImageView*>("ChPf_bg")
					       ->getChildByName<ui::Text*>("ChPf_index")
					       ->getChildByName<ui::ImageView*>("ChPf_chLock");
					if (!lock) {
						break;
					}
					if (nullptr == Get_TvPlayer()->getCurChannel()) {
						break;
					}

					if (Get_TvPlayer()->getCurChannel()->isLock()) {
						Get_TvPlayer()->setChannelStatus(index, SKYTV_CHANNEL_OPT_LOCK, false);
						lock->setVisible(false);
					}
					else {
						Get_TvPlayer()->setChannelStatus(index, SKYTV_CHANNEL_OPT_LOCK, true);
						lock->setVisible(true);
					}
					break;
				default:
					break;
				}

			};
			pf->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pf);
		}
	}


	// pf->scheduleOnce(schedule_selector(removePf), 3.0f);
	//::获取当前频道数据
	CChannel* pCh = Get_TvPlayer()->getCurChannel();
	if (!pCh) {
		if (pf->isVisible()) {
			pf->setVisible(false);
		}
		printf("Can not get Cur Channel from DB.");
		return;
	}

	std::vector<EpgEvent> pfEvents;
	unsigned short pfSize = 0;
	Channel tmpCh = pCh->get();
	if (CEpgManager::getInstance()->getEventPf(tmpCh, pfEvents)) {
		pfSize = pfEvents.size();
		// printf("\n############### pfSize:%d ############\n", pfSize);
	}

	SkyTvTimeString strTime;

	//cocos2d::Node* rootNode = pf->getChildByName("pfroot");
	//if (!rootNode) {
	//	printf("\n!!!!!!!!!!!! can't get pfroot !!!!!!!!!!!!\n");
	//	return;
	//}

	//::屏幕右上角频道号
	auto chNum = rootNode->getChildByName<ui::Layout*>("ChPf_ve")->getChildByName<ui::Text*>("ChPf_num");
	if (chNum) {
		chNum->setString(pCh->getNo());
		chNum->setVisible(true);
	}

	auto curLayoutRoot = rootNode->getChildByName<ui::Layout*>("ChPf_ve")->getChildByName<ui::ImageView*>("ChPf_bg");
	if (!curLayoutRoot) {
		printf("Can not get Cur layout from rootNode");
		return;
	}

	//::channel index/no.
	auto curLayoutChIndex = curLayoutRoot->getChildByName<ui::Text*>("ChPf_index");
	if (curLayoutChIndex) {
		curLayoutChIndex->setString(pCh->getNo());
		curLayoutChIndex->setVisible(true);

		//::fav status
		auto curLayoutChFav = curLayoutChIndex->getChildByName<ui::ImageView*>("ChPf_chFav");
		if (curLayoutChFav) {
			if (pCh->isFav()) {
				curLayoutChFav->setVisible(true);
			}
			else {
				curLayoutChFav->setVisible(false);
			}
		}
		//::lock status
		auto curLayoutChLock = curLayoutChIndex->getChildByName<ui::ImageView*>("ChPf_chLock");
		if (curLayoutChLock) {
			if (pCh->isLock()) {
				curLayoutChLock->setVisible(true);
			}
			else {
				curLayoutChLock->setVisible(false);
			}
		}


		//::channel name
		auto curLayoutChName = curLayoutChIndex->getChildByName<ui::Text*>("ChPf_name");
		if (curLayoutChName) {
			// if (pCh->getName()) {
			curLayoutChName->setString(pCh->getName());
			curLayoutChName->setVisible(true);
		}

		//::current event
		if (pfSize > 0) {
			auto curLayoutChCurEventDur = curLayoutChName->getChildByName<ui::Text*>("ChPf_curDur");
			if (curLayoutChCurEventDur) {
				{
					CTime::seconds2TimeString(pfEvents[0].startTime, strTime);
					std::string presentTime = strTime.strHour;
					presentTime += ":";
					presentTime += strTime.strMinute;
					presentTime += " - ";
					CTime::seconds2TimeString(pfEvents[0].endTime, strTime);
					presentTime += strTime.strHour;
					presentTime += ":";
					presentTime += strTime.strMinute;
					// presentTime.append(" -- ", strTime.strMinute)
					// printf("\n############### presentTime:%s ############\n", presentTime.c_str());
					curLayoutChCurEventDur->setString(presentTime.c_str());
					curLayoutChCurEventDur->setVisible(true);
				}
			}
			auto curLayoutChCurEvent = curLayoutChCurEventDur->getChildByName<ui::Text*>("ChPf_curEvent");
			if (curLayoutChCurEvent) {
				// printf("\n############### eventName:%s ############\n", pfEvents[0].eventName.c_str());
				if (NULL != pfEvents[0].eventName.c_str()) {
					curLayoutChCurEvent->setString(pfEvents[0].eventName.c_str());
					curLayoutChCurEvent->setVisible(true);
				}
			}
			auto curLayoutChPercentBg = curLayoutChCurEventDur->getChildByName<ui::LoadingBar*>("ChPf_progressBg");
			if (curLayoutChPercentBg) {
				curLayoutChPercentBg->setPercent((float)100);
				curLayoutChPercentBg->setVisible(true);
			}
			auto curLayoutChPercent = curLayoutChPercentBg->getChildByName<ui::LoadingBar*>("ChPf_progress");
			if (curLayoutChPercent) {
				//TODO：计算时间百分比
				//char percent = getPercent((curTime-dur.start),(dur.end-dur.start);
				unsigned int u32CurClock = CTime::getClock();
				printf("\n u32CurClock:%d, st:%d, du:%d \n", u32CurClock, pfEvents[0].startTime, pfEvents[0].duration);
				u32CurClock -= pfEvents[0].startTime;
				u32CurClock = u32CurClock * 100 / pfEvents[0].duration;
				curLayoutChPercent->setPercent((float)u32CurClock);
				curLayoutChPercent->setVisible(true);
			}
		}
	}

	//::PF pre
	auto curLayoutBgPre = curLayoutRoot->getChildByName<ui::ImageView*>("ChPf_bgPre");
	if (curLayoutBgPre) {
		auto curLayoutBgPreText = curLayoutBgPre->getChildByName<ui::Text*>("ChPf_preText");
		if (curLayoutBgPreText) {
			if ((pfSize > 0) && (NULL != pfEvents[0].eventName.c_str())) {
				curLayoutBgPreText->setString(pfEvents[0].eventName.c_str());
				curLayoutBgPreText->setVisible(true);
			}
		}
	}

	//::PF next
	auto curLayoutBgNext = curLayoutRoot->getChildByName<ui::ImageView*>("ChPf_bgNext");
	if (curLayoutBgNext) {
		auto curLayoutBgNextText = curLayoutBgNext->getChildByName<ui::Text*>("ChPf_nextText");
		if (curLayoutBgNextText) {
			if ((pfSize > 1) && (NULL != pfEvents[1].eventName.c_str())) {
				/*Size tmpSize(curLayoutBgNextText->getContentSize().width, 0);
				curLayoutBgNextText->setTextAreaSize(tmpSize);*/
				curLayoutBgNextText->setString(pfEvents[1].eventName.c_str());
				curLayoutBgNextText->setVisible(true);
			}
		}
	}

	//::Current Time
	auto curLayoutCurTime = curLayoutRoot->getChildByName<ui::Text*>("ChPf_curTime");
	if (curLayoutCurTime) {
		//TODO:获取当前时间
		SkyTvTimeString strTime;
		CTime::getLocalTime(strTime);

		std::string localTime = strTime.strYear;
		localTime += "/";
		localTime += strTime.strMonth;
		localTime += "/";
		localTime += strTime.strDay;
		localTime += "  ";
		localTime += strTime.strHour;
		localTime += ":";
		localTime += strTime.strMinute;
		curLayoutCurTime->setString(localTime.c_str());
		curLayoutCurTime->setVisible(true);

		auto curLayoutCruSource = curLayoutCurTime->getChildByName<ui::Text*>("ChPf_curSource");
		if (curLayoutCruSource) {
			/*if (pCh->source）*/ {
				//String curSource(pCh->source);
				if (SOURCE_TYPE_ATV == pCh->getSource()) {
					curLayoutCruSource->setString("ATV");
				} else if (SOURCE_TYPE_DVBC == pCh->getSource()) {
					curLayoutCruSource->setString("DTV-C");
				} else if (SOURCE_TYPE_DVBT == pCh->getSource()) {
					curLayoutCruSource->setString("DTV-T");
				} else if (SOURCE_TYPE_DVBS == pCh->getSource()) {
					curLayoutCruSource->setString("DTV-S");
				} else {
					curLayoutCruSource->setString("DTV");
				}
				curLayoutCruSource->setVisible(true);
			}

			auto curLayoutCruResolution = curLayoutCruSource->getChildByName<ui::Text*>("ChPf_curResolution");
			if (curLayoutCruResolution) {
				/*if (pCh->Resolution）*/ {
					//String curResolution(pCh->ratio);
					curLayoutCruResolution->setString("1920x1080"/*curResolution*/);
					curLayoutCruResolution->setVisible(true);
				}

				auto curLayoutCruRatio = curLayoutCruResolution->getChildByName<ui::Text*>("ChPf_curRatio");
				if (curLayoutCruRatio) {
					/*if (pCh->ratio）*/ {
						//String curRatio(pCh->ratio);
						curLayoutCruRatio->setString("16:9"/*curRatio*/);
						curLayoutCruRatio->setVisible(true);
					}
				}
			}
		}
	}

	FUNC_EXIT();
}

void PfInfo::show(cocos2d::Node* node) {
	FUNC_ENTRY();

	if (PfInfo::getLayer(node)) {
		PfInfo::getLayer(node)->setVisible(true);
	} else {
		return;
	}

	refresh(0);

	PfInfo::getLayer(node)->scheduleOnce(schedule_selector(PfInfo::hidePf), 2.0f);
}

void PfInfo::hide(cocos2d::Node* node) {
	if (PfInfo::getLayer(node)) {
		PfInfo::getLayer(node)->setVisible(false);
	} else {
		return;
	}
}

void PfInfo::remove(cocos2d::Node* node) {
	if (PfInfo::getLayer(node)) {
		PfInfo::getLayer(node)->removeAllChildren();
		if (PfInfo::getLayer(node)->getParent()) {
			PfInfo::getLayer(node)->getParent()->removeChild(PfInfo::getLayer(node));
		}
	} else {
		return;
	}

}

bool PfInfo::visible(cocos2d::Node* node) {
	if (PfInfo::getLayer(node)) {
		return PfInfo::getLayer(node)->isVisible();
	} else {
		return false;
	}
}

