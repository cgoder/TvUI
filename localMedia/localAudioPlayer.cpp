#include "localMedia/localAudioPlayer.h"

LocalAudioPlayer::LocalAudioPlayer()
{
	this->setName("LocalAudioPlayer");
	log("LocalAudioPlayer::LocalAudioPlayer");
}

LocalAudioPlayer::~LocalAudioPlayer()
{
	
}

cocos2d::Layer* LocalAudioPlayer::creatLayer(Node* node)
{
	if (node) {
		Layer* LocalAudioPlayer = (Layer*)node->getChildByName("LocalAudioPlayer");
		if (LocalAudioPlayer) {
			return LocalAudioPlayer;
		}
		else {
			log("LocalAudioPlayer:ceart");
			auto pAudioPlayer = LocalAudioPlayer::create();
			node->addChild(pAudioPlayer);			
			return pAudioPlayer;
		}
	}
	return nullptr;
}
Scene* LocalAudioPlayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LocalAudioPlayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool LocalAudioPlayer::init()
{
	log("LocalAudioPlayer:init in");
	ui::Layout* layout = ui::Layout::create();
	layout->setContentSize(Size(1920,1080));
	int width = layout->getContentSize().width;
	int height = layout->getContentSize().height;
	
	ui::ImageView* imageView = ui::ImageView::create("general/general_bg.png");
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(0, 0));	
	layout->addChild(imageView,1,"play panel background");
	
	
	imageView = ui::ImageView::create("localMedia/audio_play.png");
	imageView->setPosition(Vec2(960,100));	
	imageView->setVisible(false);
	layout->addChild(imageView,1,"audio_play");
	
	imageView = ui::ImageView::create("localMedia/audio_play_focus.png");
	imageView->setPosition(Vec2(960,100));	
	imageView->setVisible(true);
	layout->addChild(imageView,1,"audio_play_focus");
	
	
	imageView = ui::ImageView::create("localMedia/audio_pause.png");
	imageView->setPosition(Vec2(960,100));	
	imageView->setVisible(false);
	layout->addChild(imageView,1,"audio_pause");
	
	imageView = ui::ImageView::create("localMedia/audio_pause_focus.png");
	imageView->setPosition(Vec2(960,100));	
	imageView->setVisible(false);
	layout->addChild(imageView,1,"audio_pause_focus");
	
	
	imageView = ui::ImageView::create("localMedia/audio_lastitem.png");
	imageView->setPosition(Vec2(800,100));	
	imageView->setVisible(true);
	layout->addChild(imageView,1,"audio_lastitem");
	
	imageView = ui::ImageView::create("localMedia/audio_lastitem_focus.png");
	imageView->setPosition(Vec2(800,100));	
	imageView->setVisible(false);
	layout->addChild(imageView,1,"audio_lastitem_focus");
	
	imageView = ui::ImageView::create("localMedia/audio_nextitem.png");
	imageView->setPosition(Vec2(1120,100));	
	imageView->setVisible(true);
	layout->addChild(imageView,1,"audio_nextitem");
	
	imageView = ui::ImageView::create("localMedia/audio_nextitem_focus.png");
	imageView->setPosition(Vec2(1120,100));	
	imageView->setVisible(false);
	layout->addChild(imageView,1,"audio_nextitem_focus");	
	
	imageView = ui::ImageView::create("localMedia/pic_processbar_grey.png");
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setScale9Enabled(true);
	imageView->setContentSize(Size(444,7));
	imageView->setPosition(Vec2(958, 600));
	layout->addChild(imageView,1,"pic_processbar_grey");
	
	PVRUpdateProgressBar *progressbar_blue = new (std::nothrow) PVRUpdateProgressBar();
	progressbar_blue->setProgressBarParam("localMedia/pic_processbar_blue.png", Vec2(958, 600));
	if (progressbar_blue && progressbar_blue->init())
	{
		progressbar_blue->autorelease();
	}
	progressbar_blue->UpdateProgressBar(12345678,87654321);
	this->addChild(progressbar_blue, 2, "pic_processbar_blue");
	
	play_time = new (std::nothrow) PVRUpdateTime();
	if (play_time && play_time->init())
	{
		play_time->autorelease();
	}
	play_time->setLayoutPosition(Vec2(1438, 585));
	layout->addChild(play_time,1,"cur show time");
	
	
	auto label = Label::createWithTTF("/", "general/SourceHanSansTWHK-Light.ttf", 28);
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));	
	//label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(1530, 600));
	layout->addChild(label);
	
	total_time = new (std::nothrow) PVRUpdateTime();
	if (total_time && total_time->init())
	{
		total_time->autorelease();
	}
	total_time->setLayoutPosition(Vec2(1555, 585));
	layout->addChild(total_time,1,"total show time");
	
	std::string songname = "";
	std::string songsinger = "";
	std::string songcollection = "";
	
	label = Label::createWithTTF(songname, "general/SourceHanSansTWHK-Light.ttf", 56);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x33, 0x33, 0x33));
	label->setPosition(Vec2(956, 850));
	layout->addChild(label,1,"song name");
	
	label = Label::createWithTTF("歌手", "general/SourceHanSansTWHK-Light.ttf", 48);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));
	label->setPosition(Vec2(956, 750));
	layout->addChild(label);
	
	label = Label::createWithTTF(":", "general/SourceHanSansTWHK-Light.ttf", 48);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));
	label->setPosition(Vec2(1066, 750));
	layout->addChild(label);
	
	label = Label::createWithTTF(songsinger, "general/SourceHanSansTWHK-Light.ttf", 48);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));
	label->setPosition(Vec2(1100, 750));
	layout->addChild(label,1,"song singer");
	
	label = Label::createWithTTF("专辑", "general/SourceHanSansTWHK-Light.ttf", 48);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));
	label->setPosition(Vec2(956, 660));
	layout->addChild(label);
	
	label = Label::createWithTTF(":", "general/SourceHanSansTWHK-Light.ttf", 48);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));
	label->setPosition(Vec2(1066, 660));
	layout->addChild(label);
	
	label = Label::createWithTTF(songcollection, "general/SourceHanSansTWHK-Light.ttf", 48);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));
	label->setPosition(Vec2(1100, 660));
	layout->addChild(label,1,"song collection");
	
	
	imageView = ui::ImageView::create("localMedia/audio_cover.png");
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(476,540));	
	layout->addChild(imageView,1,"audio_cover");	
	
		
	addChild(layout,0,"local audio player");
	addKeyListener(CC_CALLBACK_2(LocalAudioPlayer::onKeyPressed, this), layout);
	
	this->schedule(schedule_selector(LocalAudioPlayer::schUpdataCurTime), 1);
	this->schedule(schedule_selector(LocalAudioPlayer::schUpdateProgressBar), 1);
	this->schedule(schedule_selector(LocalAudioPlayer::schUpdataTotalTime), 1);
	log("LocalAudioPlayer:init out");

	cur_icon = AUDIO_PLAY;
	
	return true;
}

void LocalAudioPlayer::localAudioPlayerCallback(MP_MSG_e type, void* pUserData)
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
            	log("LocalAudioPlayer:play start");	
            	CCMediaPlayer::getInstance()->start();
            	log("LocalAudioPlayer:play start out");	
            	
            	updateAudioInfo();
            });			
			break;
		}
		case MP_MSG_COMPLETED:
		{
			
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

void LocalAudioPlayer::closeLayer()
{
	this->unschedule(schedule_selector(LocalAudioPlayer::schUpdataCurTime));
	this->unschedule(schedule_selector(LocalAudioPlayer::schUpdateProgressBar));
	this->unschedule(schedule_selector(LocalAudioPlayer::schUpdataTotalTime));
	
	if (1) {
		if(this->getParent()->getChildByName("localMedia"))
		{
			this->getParent()->getChildByName("localMedia")->setVisible(true);	
		}		

		this->removeAllChildren();
		if (this->getParent()) {
			this->getParent()->removeChild(this);
		}
	}	
}


void LocalAudioPlayer::play(string& path)
{	
	//LayerHide("localMedia");
	if (1) 
	{
		if(this->getParent()->getChildByName("localMedia"))
			this->getParent()->getChildByName("localMedia")->setVisible(false);
	}

	
	
	log("LocalAudioPlayer:play path %s",path.c_str());
	log("LocalAudioPlayer:play getInstance");
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	log("LocalAudioPlayer:play setListener");
	player->setListener(CC_CALLBACK_2(LocalAudioPlayer::localAudioPlayerCallback,this));
	log("LocalAudioPlayer:play reset");	
	player->reset();
	log("LocalAudioPlayer:play setDataSource");	
	player->setDataSource(path,MP_TYPE_MUSIC);
	log("LocalAudioPlayer:play prepareAsync");	
	player->prepareAsync() ;    
	log("LocalAudioPlayer:play prepareAsync out");	
	
	cur_status = PLAYING;
}

void LocalAudioPlayer::play(std::vector<std::string> &m_audioListVec)
{	
	
	audioList = m_audioListVec;
	std::string path = audioList.at(0);
	cur_index = 0;
	
	if (1) 
	{
		if(this->getParent()->getChildByName("localMedia"))
			this->getParent()->getChildByName("localMedia")->setVisible(false);
	}

	
	
	log("LocalAudioPlayer:play path %s",path.c_str());
	log("LocalAudioPlayer:play getInstance");
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	log("LocalAudioPlayer:play setListener");
	player->setListener(CC_CALLBACK_2(LocalAudioPlayer::localAudioPlayerCallback,this));
	log("LocalAudioPlayer:play reset");	
	player->reset();
	log("LocalAudioPlayer:play setDataSource");	
	player->setDataSource(path,MP_TYPE_MUSIC);
	log("LocalAudioPlayer:play prepareAsync");	
	player->prepareAsync() ;    
	log("LocalAudioPlayer:play prepareAsync out");	
	cur_status = PLAYING;
}

void LocalAudioPlayer::stop()
{
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	if(player->isPlaying())
		player->stop();		
	
	closeLayer();
}

void LocalAudioPlayer::updateAudioInfo()
{
	Node *node = this->getChildByName("local audio player");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 

	std::string songname;
	std::string songsinger;
	std::string songcollection;
	
	CCMediaPlayer *player = CCMediaPlayer::getInstance();

	player->getMusicTitle(songname);
	player->getMusicAlbum(songcollection);
	player->getMusicArtist(songsinger);
	
	
	node = layout->getChildByName("song name");	
	Label* label = static_cast<Label*>(node); 
	label->setString(songname);	
	
	node = layout->getChildByName("song singer");	
	label = static_cast<Label*>(node); 
	label->setString(songsinger);	
	
	node = layout->getChildByName("song collection");	
	label = static_cast<Label*>(node); 
	label->setString(songcollection);	
	
}



void LocalAudioPlayer::updateShowTime(int time_ms,RecordShowTimeType type)
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

void LocalAudioPlayer::schUpdateProgressBar(float dt)
{
	Node *node = this->getChildByName("pic_processbar_blue");
	PVRUpdateProgressBar *bar_blue = static_cast<PVRUpdateProgressBar*>(node);
	
	//Todo 从底层得到时间
	int time_ms;
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	
	player->getCurrentPosition(&time_ms);
	player->getDuration(&Duration);
	//time_ms = 2000;
	log("LocalAudioPlayer:ProgressBar getCurrentPosition %d",time_ms);
	bar_blue->UpdateProgressBar(time_ms, Duration);
}

void LocalAudioPlayer::schUpdataCurTime(float dt)
{
	//Todo 从底层得到时间
	int time_ms;
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	player->getCurrentPosition(&time_ms);
	log("LocalAudioPlayer:CurTime getCurrentPosition %d",time_ms);
	updateShowTime(time_ms,SHOW_TIME_CURRENT);
}

void LocalAudioPlayer::schUpdataTotalTime(float dt)
{
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	player->getDuration(&Duration);
	log("LocalAudioPlayer:getDuration %d",Duration);
	updateShowTime(Duration,SHOW_TIME_TOTAL);
	
}



void LocalAudioPlayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);  
    
     switch(keyCode) 
	{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	    case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
	    {
	    	if(cur_icon>0)
	    		cur_icon--;	    		
	    	changeIconImage();	    		
	    	break;
	    }
	    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	    case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
	    {
	    	if(cur_icon<2)
	    		cur_icon++;	    	
	    	changeIconImage();	    	
	    	break;	
	    }
		case EventKeyboard::KeyCode::KEY_ENTER:
	    case EventKeyboard::KeyCode::KEY_DPAD_CENTER:  	
	    {
	    	pictureIconAction();
	    	break;		
		}
			
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:		
		{			
			stop();				
			CCMediaPlayer::destoryInstance();

			break;
		}	
			
		default:
			break;	
		
	}
}

void LocalAudioPlayer::changeIconImage()
{
	Node *node = this->getChildByName("local audio player");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 
	node = layout->getChildByName("audio_play");
	ui::ImageView *audio_play = static_cast<ui::ImageView*>(node);
	node = layout->getChildByName("audio_play_focus");
	ui::ImageView *audio_play_focus = static_cast<ui::ImageView*>(node);
	
	node = layout->getChildByName("audio_pause");
	ui::ImageView *audio_pause = static_cast<ui::ImageView*>(node);
	node = layout->getChildByName("audio_pause_focus");
	ui::ImageView *audio_pause_focus = static_cast<ui::ImageView*>(node);		
		
	node = layout->getChildByName("audio_lastitem");
	ui::ImageView *audio_lastitem = static_cast<ui::ImageView*>(node);	
	node = layout->getChildByName("audio_lastitem_focus");
	ui::ImageView *audio_lastitem_focus = static_cast<ui::ImageView*>(node);
	
	node = layout->getChildByName("audio_nextitem");
	ui::ImageView *audio_nextitem = static_cast<ui::ImageView*>(node);	
	node = layout->getChildByName("audio_nextitem_focus");
	ui::ImageView *audio_nextitem_focus = static_cast<ui::ImageView*>(node);		   
		
	if(cur_icon == AUDIO_LAST)
	{
		audio_lastitem->setVisible(false);	
		audio_lastitem_focus->setVisible(true);
		
		if(cur_status == PLAYING)
		{
			audio_play->setVisible(true);	
			audio_play_focus->setVisible(false);
		}
		if(cur_status == PAUSED)
		{
			audio_pause->setVisible(true);
			audio_pause_focus->setVisible(false);
		}
				
		audio_nextitem->setVisible(true);	
		audio_nextitem_focus->setVisible(false);		
		
	}
	if(cur_icon == AUDIO_PLAY)
	{
		audio_lastitem->setVisible(true);	
		audio_lastitem_focus->setVisible(false);
		audio_play->setVisible(false);	
		audio_play_focus->setVisible(true);	
		
		audio_pause->setVisible(false);
		audio_pause_focus->setVisible(false);
			
		audio_nextitem->setVisible(true);	
		audio_nextitem_focus->setVisible(false);

	}	
	if(cur_icon == AUDIO_NEXT)
	{
		audio_lastitem->setVisible(true);	
		audio_lastitem_focus->setVisible(false);
		
		if(cur_status == PLAYING)
		{
			audio_play->setVisible(true);	
			audio_play_focus->setVisible(false);
		}
		if(cur_status == PAUSED)
		{
			audio_pause->setVisible(true);
			audio_pause_focus->setVisible(false);
		}
				
		audio_nextitem->setVisible(false);	
		audio_nextitem_focus->setVisible(true);
	}	
}

void LocalAudioPlayer::pictureIconAction()
{
	Node *node = this->getChildByName("local audio player");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 
	node = layout->getChildByName("audio_play");
	ui::ImageView *audio_play = static_cast<ui::ImageView*>(node);
	node = layout->getChildByName("audio_play_focus");
	ui::ImageView *audio_play_focus = static_cast<ui::ImageView*>(node);
		
	node = layout->getChildByName("audio_pause");
	ui::ImageView *audio_pause = static_cast<ui::ImageView*>(node);
	node = layout->getChildByName("audio_pause_focus");
	ui::ImageView *audio_pause_focus = static_cast<ui::ImageView*>(node);	
	
	
	if(cur_icon == AUDIO_LAST
		||cur_icon == AUDIO_NEXT)
	{
		audio_play->setVisible(true);
		audio_play_focus->setVisible(false);
		audio_pause->setVisible(false);
		audio_pause_focus->setVisible(false);
		cur_status = PLAYING;
	}	
	
	
	if(cur_icon == AUDIO_LAST)
	{
		if(cur_index == 0)
			cur_index = audioList.size()-1;
		else
			cur_index--; 	
		play_internal(cur_index);
		
	}
	if(cur_icon == AUDIO_PLAY)
	{
		if(cur_status == PLAYING)
		{
			audio_play->setVisible(false);
			audio_play_focus->setVisible(false);
			audio_pause->setVisible(false);
			audio_pause_focus->setVisible(true);
			cur_status = PAUSED;
		}
		else if(cur_status == PAUSED)
		{
			audio_play->setVisible(false);
			audio_play_focus->setVisible(true);
			audio_pause->setVisible(false);
			audio_pause_focus->setVisible(false);
			cur_status = PLAYING;
		}
		
	}	
	if(cur_icon == AUDIO_NEXT)
	{
		if(cur_index == audioList.size()-1)
			cur_index = 0;
		else
			cur_index++; 
		play_internal(cur_index);		
	}	
}

void LocalAudioPlayer::play_internal(int index)
{
	std::string path;
	path = audioList.at(index);
	
	CCMediaPlayer *player = CCMediaPlayer::getInstance();	
	player->stop();
	player->reset();
	player->setDataSource(path,MP_TYPE_PHOTO);
	player->prepareAsync() ;
	cur_status = PLAYING;
}