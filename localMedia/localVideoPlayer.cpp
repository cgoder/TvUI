#include "localMedia/localVideoPlayer.h"
#include "tvplayer/CCPvrManager.h"


LocalVideoPlayer::LocalVideoPlayer()
{
	this->setName("LocalVideoPlayer");
	log("LocalVideoPlayer::LocalVideoPlayer");
}

LocalVideoPlayer::~LocalVideoPlayer()
{
	
}

cocos2d::Layer* LocalVideoPlayer::creatLayer(Node* node)
{
	if (node) {	
				
		Layer* LocalVideoPlayer = (Layer*)node->getChildByName("LocalVideoPlayer");
		if (LocalVideoPlayer) {
			return LocalVideoPlayer;
		}
		else {
			log("LocalVideoPlayer:ceart");
			auto pVideoPlayer = LocalVideoPlayer::create();
			node->addChild(pVideoPlayer);			
			return pVideoPlayer;
		}
	}
	return nullptr;
}
Scene* LocalVideoPlayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LocalVideoPlayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool LocalVideoPlayer::init()
{
	log("LocalVideoPlayer:init in");
	ui::Layout* layout = ui::Layout::create();
	layout->setContentSize(Size(1920,1080));
	int width = layout->getContentSize().width;
	int height = layout->getContentSize().height;
	
	ui::ImageView* imageView = ui::ImageView::create("general/general_bg.png");
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(0, 0));
	imageView->setVisible(false);
	layout->addChild(imageView,1,"play panel background");
	
	
	Sprite* sprite = Sprite::create("general/general_popup_bg.png", Rect(0, 0, 1920, 97));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(0, 0));		
	layout->addChild(sprite);
	
	//Todo
	auto label = Label::createWithTTF("", "general/SourceHanSansTWHK-Light.ttf", 36);
	//LabelTTF* label = LabelTTF::create(DefaultPlayStr, "Arial", 36);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(40, 20));
	layout->addChild(label,1,"media file name");
		

	imageView = ui::ImageView::create("rec/record_progressbar_transparent.png");
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setScale9Enabled(true);
	imageView->setContentSize(Size(1920,7));
	imageView->setPosition(Vec2(0, 97));
	layout->addChild(imageView,1,"progressbar_transparent");
	
	PVRUpdateProgressBar *progressbar_blue = new (std::nothrow) PVRUpdateProgressBar();
	progressbar_blue->setProgressBarParam("rec/record_progressbar_blue.png", Vec2(0, 97));
	if (progressbar_blue && progressbar_blue->init())
	{
		progressbar_blue->autorelease();
	}
	progressbar_blue->UpdateProgressBar(12345678,87654321);
	this->addChild(progressbar_blue, 2, "progressbar_blue");
	
	play_time = new (std::nothrow) PVRUpdateTime();
	if (play_time && play_time->init())
	{
		play_time->autorelease();
	}
	play_time->setLayoutPosition(Vec2(1615, 20));
	layout->addChild(play_time,1,"cur record show time");
	
	
	label = Label::createWithTTF("/", "general/SourceHanSansTWHK-Light.ttf", 28);
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	//label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(1772, 45));
	layout->addChild(label);
	
	total_time = new (std::nothrow) PVRUpdateTime();
	if (total_time && total_time->init())
	{
		total_time->autorelease();
	}
	total_time->setLayoutPosition(Vec2(1755, 20));
	layout->addChild(total_time,1,"total record show time");
		
	//showtime cursor
	
	imageView = ui::ImageView::create("rec/record_showtime1.png");
	imageView->setAnchorPoint(Vec2(0, 0));	
	imageView->setPosition(Vec2(1347, 108));
	
	cursor_time1 = new (std::nothrow) PVRUpdateTime();
	if (cursor_time1 && cursor_time1->init())
	{
		cursor_time1->autorelease();
	}
	cursor_time1->setLayoutPosition(Vec2(0, 0));
	
	imageView->addChild(cursor_time1,1,"showtime cursor inside");	
	imageView->setVisible(false);
	layout->addChild(imageView,1,"showtime cursor1");
	
	
	imageView = ui::ImageView::create("rec/record_showtime2.png");
	imageView->setAnchorPoint(Vec2(0, 0));	
	imageView->setPosition(Vec2(1347, 108));
	
	cursor_time2 = new (std::nothrow) PVRUpdateTime();
	if (cursor_time2 && cursor_time2->init())
	{
		cursor_time2->autorelease();
	}
	cursor_time2->setLayoutPosition(Vec2(0, 0));
	
	imageView->addChild(cursor_time2,1,"showtime cursor inside");
	imageView->setVisible(true);	
	layout->addChild(imageView,1,"showtime cursor2");
	


	
	addChild(layout,0,"PVR play panel");
	addKeyListener(CC_CALLBACK_2(LocalVideoPlayer::onKeyPressed_PlayPanel, this), layout);
	
//	this->schedule(schedule_selector(LocalVideoPlayer::schUpdataCursorTime), 1);
//	this->schedule(schedule_selector(LocalVideoPlayer::schUpdataCurTime), 1);
//	this->schedule(schedule_selector(LocalVideoPlayer::schUpdateProgressBar), 1);
//	if(!is_pvr)
//		this->schedule(schedule_selector(LocalVideoPlayer::schUpdataTotalTime), 1);
	log("LocalVideoPlayer:init out");
	
	//Duration = 192000;
	return true;
}

void LocalVideoPlayer::localVideoPlayerCallback(MP_MSG_e type, void* pUserData)
{
	switch(type)
	{
		case MP_MSG_ERROR:
		{
			 break;
		}		
		case MP_MSG_PREPARED:
		{
			
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([this]
            {
            	CCMediaPlayer *player = CCMediaPlayer::getInstance();
            	log("LocalVideoPlayer:play start");	
            	player->start();
            	log("LocalVideoPlayer:play start out");	
            });			
			break;
		}
		case MP_MSG_COMPLETED:
		{
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([this]
            {
            	log("LocalVideoPlayer:complete stop in");	
            	stop();
            	log("LocalVideoPlayer:complete stop out");	
            });
			 break;
		}
		case MP_MSG_VIDEO_SIZE_CHANGED:
		{    		
			break;
		}
		case MP_MSG_SEEK_COMPLETE:
		{
			break;
		}
		
		default:
			break;
	}
}

void LocalVideoPlayer::closeLayer()
{
	this->unschedule(schedule_selector(LocalVideoPlayer::schUpdataCursorTime));
	this->unschedule(schedule_selector(LocalVideoPlayer::schUpdataCurTime));
	this->unschedule(schedule_selector(LocalVideoPlayer::schUpdateProgressBar));
	if(!is_pvr)
		this->unschedule(schedule_selector(LocalVideoPlayer::schUpdataTotalTime));
	
	//LayerShow("localMedia");
	if (1) {
		if(this->getParent()->getChildByName("localMedia"))
		{
			this->getParent()->getChildByName("localMedia")->setVisible(true);	
		}	
		else if(this->getParent()->getChildByName("ChannelList"))
		{
			this->getParent()->getChildByName("ChannelList")->setVisible(true);
		}			
		else//from pvr ui
		{
			log("LocalVideoPlayer:play out,Get_TvPlayer()->playCur() in");
			Get_TvPlayer()->playCur();
			log("LocalVideoPlayer:play out,Get_TvPlayer()->playCur() out");
		}
	}
			
	if (1) {
		this->removeAllChildren();
		if (this->getParent()) {
			this->getParent()->removeChild(this);
		}
	}
}



void LocalVideoPlayer::play(string& path)
{	
	is_pvr = false;
	
	CCPvrManager::destoryInstance();
		
	this->schedule(schedule_selector(LocalVideoPlayer::schUpdataCursorTime), 1);
	this->schedule(schedule_selector(LocalVideoPlayer::schUpdataCurTime), 1);
	this->schedule(schedule_selector(LocalVideoPlayer::schUpdateProgressBar), 1);	
	this->schedule(schedule_selector(LocalVideoPlayer::schUpdataTotalTime), 1);	
		
	//LayerHide("localMedia");
	if (1) {
				if(this->getParent()->getChildByName("localMedia"))
				{
					this->getParent()->getChildByName("localMedia")->setVisible(false);
				}				
				else if(this->getParent()->getChildByName("ChannelList"))
				{
					this->getParent()->getChildByName("ChannelList")->setVisible(false);
				}
				else
				{
					log("LocalVideoPlayer:Get_TvPlayer()->stop() in");
					Get_TvPlayer()->stop();
					log("LocalVideoPlayer:Get_TvPlayer()->stop() out");
				}
			}
	
	Node *node = this->getChildByName("PVR play panel");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 
				
	node = layout->getChildByName("media file name");	
	Label* label = static_cast<Label*>(node); 
	label->setString(path.c_str());			

	log("LocalVideoPlayer:play path %s",path.c_str());
	log("LocalVideoPlayer:play getInstance");
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	log("LocalVideoPlayer:play setListener");
	player->setListener(CC_CALLBACK_2(LocalVideoPlayer::localVideoPlayerCallback,this));
	log("LocalVideoPlayer:play reset");	
	player->reset();
	log("LocalVideoPlayer:play setDataSource");	
	player->setDataSource(path,MP_TYPE_VIDEO);
	log("LocalVideoPlayer:play prepareAsync");	
	player->prepareAsync() ;    
	log("LocalVideoPlayer:play prepareAsync out");	
}

void LocalVideoPlayer::stop()
{
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	if(player->isPlaying())
	{
		log("LocalVideoPlayer: player->stop");
		player->stop();
	}

	closeLayer();
}

void LocalVideoPlayer::play_pvr(string filename)
{
	is_pvr = true;
	Duration =  CCPvrManager::getInstance()->getRecordedFileDurationTime(filename);
	Duration *= 1000;//s->ms
	
	updateShowTime(Duration,SHOW_TIME_TOTAL);
	
	this->schedule(schedule_selector(LocalVideoPlayer::schUpdataCursorTime), 1);
	this->schedule(schedule_selector(LocalVideoPlayer::schUpdataCurTime), 1);
	this->schedule(schedule_selector(LocalVideoPlayer::schUpdateProgressBar), 1);
	
		
	if (1) {
				if(this->getParent()->getChildByName("ChannelList"))
				{
					this->getParent()->getChildByName("ChannelList")->setVisible(false);
				}
				else
				{
					log("LocalVideoPlayer:Get_TvPlayer()->stop() in");
					Get_TvPlayer()->stop();
					log("LocalVideoPlayer:Get_TvPlayer()->stop() out");
				}
			}
	
	Node *node = this->getChildByName("PVR play panel");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 
				
	node = layout->getChildByName("media file name");	
	Label* label = static_cast<Label*>(node); 
	label->setString(filename);		
	
	CCPvrManager::getInstance()->startPlayback(filename);	
	log("LocalVideoPlayer:startPlayback ok.Duration %d ms",Duration);
}

void LocalVideoPlayer::stop_pvr()
{
	CCPvrManager *pPvrManager = CCPvrManager::getInstance();

	if(pPvrManager->isPlaybacking())
	{		
		log("LocalVideoPlayer:stopPlayback in");
		pPvrManager->stopPlayback();
		log("LocalVideoPlayer:stopPlayback out");

	}
	closeLayer();
}



void LocalVideoPlayer::updateShowTime(int time_ms,RecordShowTimeType type)
{
	int cur_second = time_ms/1000;
	int cur_minute = cur_second/60;
	int cur_hour = cur_minute/60;
	
	cur_minute -= cur_hour*60;
	
	cur_second -= cur_hour*60*60 + cur_minute*60;	
	

	Node *node;

	node = this->getChildByName("PVR play panel");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 			
	
	//time_ms = 2000;
		
	switch(type)
	{
		case SHOW_TIME_CURSOR:
		{
			time_ms /= 1000;
			int tmp_Duration = Duration/1000;
	
			if((float)time_ms * 1920 / (float)tmp_Duration<165)
				cursor_time2->updateShowTime(cur_hour,cur_minute,cur_second); 
			else
				cursor_time1->updateShowTime(cur_hour,cur_minute,cur_second); 
						
			break;
		}
		case SHOW_TIME_CURRENT:
		{
			play_time->updateShowTime(cur_hour,cur_minute,cur_second); 
			break;
		}
		case SHOW_TIME_TOTAL:
		{
			total_time->updateShowTime(cur_hour,cur_minute,cur_second); 
			break;
		}
		default:
			break;
	}		
	
}

void LocalVideoPlayer::schUpdateProgressBar(float dt)
{
//	Node *node = this->getChildByName("PVR play panel");
//	ui::Layout* layout = static_cast<ui::Layout*>(node);
	Node *node = this->getChildByName("progressbar_blue");
	PVRUpdateProgressBar *bar_blue = static_cast<PVRUpdateProgressBar*>(node);
	
	//Todo 从底层得到时间
	int time_ms;
	if(is_pvr)
	{		
		time_ms = CCPvrManager::getInstance()->getCurPlaybackTime();
		time_ms *= 1000;
	}
	else
	{			
		CCMediaPlayer *player = CCMediaPlayer::getInstance();
		player->getCurrentPosition(&time_ms);
		player->getDuration(&Duration);

	}
	log("LocalVideoPlayer:ProgressBar getCurrentPosition %d",time_ms);
	bar_blue->UpdateProgressBar(time_ms, Duration);
}

void LocalVideoPlayer::schUpdataCursorTime(float dt)
{
	int time_ms;
	
	if(is_pvr)
	{
		time_ms = CCPvrManager::getInstance()->getCurPlaybackTime();
		time_ms *= 1000;
	}
	else
	{	
		CCMediaPlayer *player = CCMediaPlayer::getInstance();
		player->getCurrentPosition(&time_ms);
		player->getDuration(&Duration);
	}
	log("LocalVideoPlayer:CursorTime getCurrentPosition %d",time_ms);
	updateShowTime(time_ms,SHOW_TIME_CURSOR);	
	
	
	Node *node = this->getChildByName("PVR play panel");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 
		
	node = layout->getChildByName("showtime cursor2");
	ui::ImageView *img2 = static_cast<ui::ImageView*>(node);	
	
	node = layout->getChildByName("showtime cursor1");
	ui::ImageView *img1 = static_cast<ui::ImageView*>(node); 
	
	time_ms /= 1000;
	int tmp_Duration = Duration/1000;
	
	if ((float)time_ms * 1920 / (float)tmp_Duration<165)
	{
		Vec2 position = img2->getPosition();
		position.x = (float)time_ms * 1920 / (float)tmp_Duration;
		img2->setPosition(position);

		img2->setVisible(true);
		img1->setVisible(false);
		
	}
	else
	{
		Vec2 position = img1->getPosition();
		position.x = (float)time_ms * 1920 / (float)tmp_Duration - 165;
		img1->setPosition(position);

		img2->setVisible(false);
		img1->setVisible(true);
	}
}

void LocalVideoPlayer::schUpdataCurTime(float dt)
{
	//Todo 从底层得到时间
	int time_ms;
	if(is_pvr)
	{
		time_ms = CCPvrManager::getInstance()->getCurPlaybackTime();
		time_ms *= 1000;
	}
	else
	{	
		CCMediaPlayer *player = CCMediaPlayer::getInstance();
		player->getCurrentPosition(&time_ms);
	}
	log("LocalVideoPlayer:CurTime getCurrentPosition %d",time_ms);
	updateShowTime(time_ms,SHOW_TIME_CURRENT);
}

void LocalVideoPlayer::schUpdataTotalTime(float dt)
{	
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	player->getDuration(&Duration);
	log("LocalVideoPlayer:getDuration %d",Duration);
	updateShowTime(Duration,SHOW_TIME_TOTAL);
	
}
void LocalVideoPlayer::addPauseIcon()
{
	ui::ImageView* imageView = ui::ImageView::create("rec/record_pause_normal.png");
	imageView->setPosition(Vec2(960, 560));

	addChild(imageView,0,"PVR pause icon play");
	addKeyListener(CC_CALLBACK_2(LocalVideoPlayer::onKeyPressed_PausePlaying, this), imageView);

}


void LocalVideoPlayer::onKeyPressed_PlayPanel(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);  
    
    Node *node = this->getChildByName("PVR play panel");
	ui::ImageView* img = static_cast<ui::ImageView*>(node); 
	
	CCPvrManager *pPvrManager;
	CCMediaPlayer *player;
	
	if(is_pvr)
	{
		pPvrManager = CCPvrManager::getInstance();
	}
	else
	{	
    	player = CCMediaPlayer::getInstance();
    }
    switch(keyCode) 
	{
		case EventKeyboard::KeyCode::KEY_ENTER:
	    case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
	    	//Toso pause?
	    	addPauseIcon();
	    	if(is_pvr)
			{
				pPvrManager->pausePlayback();
			}
			else
			{
		    	player->pause();
		    }
	    	break;
		
		case EventKeyboard::KeyCode::KEY_TV_REWIND:
			
			if(is_pvr)
			{
				cur_time = pPvrManager->getCurPlaybackTime();
				cur_time *= 1000;
				
				if(cur_time >= 2000 && pPvrManager->isPlaybacking())	
				{
					log("LocalVideoPlayer:onKeyPressed_PlayPanel seekTo %d",cur_time-2000);
					pPvrManager->seektoPlaybackTime(cur_time - 2000);
				}
			}
			else
			{			
				player->getCurrentPosition(&cur_time);
				
				if(cur_time >= 2000 && player->isPlaying())	
				{
					log("LocalVideoPlayer:onKeyPressed_PlayPanel seekTo %d",cur_time-2000);
					player->seekTo(cur_time - 2000);
				}
			}
			
			break;
		
		case EventKeyboard::KeyCode::KEY_TV_FASTFORWARD:
			
			if(is_pvr)
			{
				cur_time = pPvrManager->getCurPlaybackTime();
				cur_time *= 1000;
				
				if(cur_time <= Duration - 2000 && pPvrManager->isPlaybacking())	
				{
					log("LocalVideoPlayer:onKeyPressed_PlayPanel seekTo %d",cur_time+2000);
					pPvrManager->seektoPlaybackTime(cur_time + 2000);
				}
			}
			else
			{	
			
				player->getCurrentPosition(&cur_time);
				if(cur_time <= Duration - 2000 && player->isPlaying())
				{
					log("LocalVideoPlayer:onKeyPressed_PlayPanel seekTo %d",cur_time+2000);
					pPvrManager->seektoPlaybackTime(cur_time + 2000);
				}
			}
			break;
			
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:		
		{
			if(is_pvr)
			{
				stop_pvr();
				CCPvrManager::destoryInstance();
			}
			else
			{
				stop();				
				CCMediaPlayer::destoryInstance();
			}
			break;
		}	
			
		default:
			break;	
		
	}
}

void LocalVideoPlayer::onKeyPressed_PausePlaying(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);  
    
    Node *node = this->getChildByName("PVR pause icon play");
	ui::ImageView* img = static_cast<ui::ImageView*>(node); 
		
    
    switch(keyCode) 
	{
		case EventKeyboard::KeyCode::KEY_ENTER:
	    case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
	    	//Todo resume playing
	    	this->removeChildByName("PVR pause icon play");
	    	log("LocalVideoPlayer:onKeyPressed_PausePlaying resume");
	    	
	    	if(is_pvr)
			{
				CCPvrManager::getInstance()->resumePlayback();
			}
			else
			{				
		    	CCMediaPlayer::getInstance()->start();
		    }
	    	log("LocalVideoPlayer:onKeyPressed_PausePlaying out");
	    	break;
			
		default:
			break;	
		
	}
	
}
