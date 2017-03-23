#include "rec/PVRRecodingComplete.h"
#include "tvplayer/CEpgManager.h"
#include "tvplayer/CTime.h"

PVRRecodingComplete::PVRRecodingComplete()
{
	this->setName("PVRRecodingComplete");
	log("PVRRecodingComplete::PVRRecodingComplete");
}

PVRRecodingComplete::~PVRRecodingComplete()
{
	
}

cocos2d::Layer* PVRRecodingComplete::creatLayer(Node* node)
{
	if (node) {
		Layer* PVRRecodingComplete = (Layer*)node->getChildByName("PVRRecodingComplete");
		if (PVRRecodingComplete) {
			return PVRRecodingComplete;
		}
		else {
			log("PVRRecodingComplete:ceart");
			auto pvrcomplete = PVRRecodingComplete::create();
			node->addChild(pvrcomplete);			
			return pvrcomplete;
		}
	}
	return nullptr;
}
Scene* PVRRecodingComplete::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PVRRecodingComplete::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool PVRRecodingComplete::init()
{
	Sprite* sprite = Sprite::create("general/general_popup_bg.png", Rect(636, 108, 650, 145));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(636, 108));
	
	ui::ImageView* imageView = ui::ImageView::create("info/info_popup_bg.png");
	imageView->setScale9Enabled(true);	
	imageView->setContentSize(Size(815,311));
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(-72, -99));
	sprite->addChild(imageView);	
	
	auto label = Label::createWithTTF("Recording complete.", "general/SourceHanSansTWHK-Light.ttf", 32);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(77, 90));
	sprite->addChild(label);
	
	CChannel* pCh = Get_TvPlayer()->getCurChannel();
	std::vector<EpgEvent> pfEvents;
	unsigned short pfSize = 0;
	Channel tmpCh = pCh->get();
	if (CEpgManager::getInstance()->getEventPf(tmpCh, pfEvents)) {
		pfSize = pfEvents.size();
		// printf("\n############### pfSize:%d ############\n", pfSize);
	}
	
	label = Label::createWithTTF(pCh->getName(), "general/SourceHanSansTWHK-Light.ttf", 26);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(77, 40));
	sprite->addChild(label);
	
	label = Label::createWithTTF("", "general/SourceHanSansTWHK-Light.ttf", 26);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(77, 10));
	
	if (pfSize > 0) 
	{
		if (NULL != pfEvents[0].eventName.c_str()) {
			label->setString(pfEvents[0].eventName.c_str());
		}
	}	
	sprite->addChild(label);
	
	label = Label::createWithTTF("", "general/SourceHanSansTWHK-Light.ttf", 26);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(430, 10));
	
	SkyTvTimeString s_strTime;
	SkyTvTimeString e_strTime;
	if (pfSize > 0) 
	{
		CTime::seconds2TimeString(pfEvents[0].startTime, s_strTime);
		std::string presentTime = s_strTime.strHour;
		presentTime += ":";
		presentTime += s_strTime.strMinute;
		presentTime += " - ";
		CTime::seconds2TimeString(pfEvents[0].endTime, e_strTime);
		presentTime += e_strTime.strHour;
		presentTime += ":";
		presentTime += e_strTime.strMinute;
		// presentTime.append(" -- ", strTime.strMinute)
		// printf("\n############### presentTime:%s ############\n", presentTime.c_str());
		label->setString(presentTime.c_str());		
	}
	sprite->addChild(label);	
	
	auto fadeout = FadeOut::create(10);
	sprite->runAction(fadeout);	
	
	this->addChild(sprite,1,"pvr recording complete");
	
	addKeyListener(CC_CALLBACK_2(PVRRecodingComplete::onKeyPressed, this), sprite);
	
	return true;
}

void PVRRecodingComplete::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);  
    Node *node = this->getChildByName("pvr recording complete");
	Sprite* sprite = static_cast<Sprite*>(node); 
		
	 switch(keyCode) 
	{
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:	
			
			if (1) {
				this->removeAllChildren();
				if (this->getParent()) {
					this->getParent()->removeChild(this);
				}
			}
									
			break;
		
		default:
			break;
	}
}