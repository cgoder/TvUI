#include "rec/PVRUI.h"
//#include "cocostudio/CocoStudio.h"
#include "localMedia/localVideoPlayer.h"
#include "rec/PVRRecodingThumbnail.h"
#include "localMedia/deviceDetect.h"
#include "tvplayer/CEpgManager.h"
#include "tvplayer/CTime.h"
#include "tvScene.h"
#include "localMedia/localMedia.h"
#include "rec/PVRRecodingComplete.h"


PVRUI::PVRUI()
{
	this->setName("PVRUI");
	log("PVRUI::PVRUI");
}

PVRUI::~PVRUI()
{
	
}

cocos2d::Layer* PVRUI::creatLayer(Node* node)
{
	if (node) {
		Layer* PVRUI = (Layer*)node->getChildByName("PVRUI");
		if (PVRUI) {
			return PVRUI;
		}
		else {
			log("PVRUI:ceart");
			auto pvrui = PVRUI::create();
			node->addChild(pvrui);			
			return pvrui;
		}
	}
	return nullptr;
}
Scene* PVRUI::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PVRUI::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool PVRUI::init()
{
	//查询所有预约录制的情况并记录
	//获取当前播放台的录制状态
	
//	if ( !Layer::init() )
//    {
//        return false;
//    }

#ifdef USE_PVR_RECORD_DB
	recordDB = PVRRecordDB::getInstance();
#endif
	log("PVRUI:init in");	
	addProgramRecord();	
	log("PVRUI:init end");
	
	
	UpdataTotalTime();
	startRecord();
	usb_pop_flag = false;
	return true;
	
	
}

void PVRUI::showInvalidOperationInRecoding()
{
	Sprite* sprite = Sprite::create("general/general_popup_bg.png", Rect(512, 108, 896, 67));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(635, 108));
	
	ui::ImageView* imageView = ui::ImageView::create("info/info_popup_bg.png");
	imageView->setScale9Enabled(true);	
	imageView->setContentSize(Size(1064,232));
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(-74, -97));
	sprite->addChild(imageView);
	
	std::string panelinfo = "Now recording,the current operation is invalid.";
	auto label = Label::createWithTTF(panelinfo, "general/SourceHanSansTWHK-Light.ttf", 32);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(74, 6));
	sprite->addChild(label);
	
	this->addChild(sprite,1,"pvr invalid operation in recording");	
	
//	auto fadeout = FadeOut::create(2);
//	sprite->runAction(fadeout);
}


void PVRUI::updateShowTime(int time_ms,RecordShowTimeType type)
{
	int cur_second = time_ms/1000;
	int cur_minute = cur_second/60;
	int cur_hour = cur_minute/60;
	
	cur_minute -= cur_hour*60;
	
	cur_second -= cur_hour*60*60 + cur_minute*60;	
	

	Node *node;

	node = this->getChildByName("ProgramRecord Layout");
	
		
	ui::Layout* layout = static_cast<ui::Layout*>(node); 			
		
	switch(type)
	{
		case SHOW_TIME_CURSOR:
		{
			time_ms /= 1000;
			int tmp_Duration = total_rec_ms/1000;
	
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
void PVRUI::schUpdateProgressBar(float dt)
{
	Node *node = this->getChildByName("ProgramRecord Layout");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 
	node = layout->getChildByName("progressbar_red");
	PVRUpdateProgressBar* bar_red = static_cast<PVRUpdateProgressBar*>(node); 
	
	int time_ms = CCPvrManager::getInstance()->getCurRecordTime(); // update time
	log("PVRUI:CurRecordTime %d",time_ms);
	time_ms = time_ms*1000;
	
//	total_rec_ms = pPvrManager->getEstimateRecordRemainingTime(); 
//	total_rec_ms = total_rec_ms*1000;

	
	bar_red->UpdateProgressBar(time_ms,total_rec_ms);	
	
	node = layout->getChildByName("progressbar_blue");
	PVRUpdateProgressBar *bar_blue = static_cast<PVRUpdateProgressBar*>(node);
	
//	total_play_ms = pPvrManager->getEstimateRecordRemainingTime(); 
//	total_play_ms = total_play_ms*1000;
	time_ms = CCPvrManager::getInstance()->getCurPlaybackTime();
	log("PVRUI:CurPlaybackTime %d",time_ms);
	time_ms = time_ms*1000;
	
	bar_blue->UpdateProgressBar(time_ms,total_play_ms);
		
}

void PVRUI::schUpdataCursorTime(float dt)
{
	int time_ms = CCPvrManager::getInstance()->getCurPlaybackTime(); // update time
	time_ms = time_ms*1000;
	
	updateShowTime(time_ms,SHOW_TIME_CURSOR);	
	
	
	Node *node = this->getChildByName("ProgramRecord Layout");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 
	node = layout->getChildByName("showtime cursor2");
	ui::ImageView *img2 = static_cast<ui::ImageView*>(node); 
	
	node = layout->getChildByName("showtime cursor1");
	ui::ImageView *img1 = static_cast<ui::ImageView*>(node); 
	
	time_ms /= 1000;
	int tmp_Duration = total_rec_ms/1000;
	
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

void PVRUI::schUpdataCurTime(float dt)
{
	int time_ms = CCPvrManager::getInstance()->getCurPlaybackTime(); // update time
	
	time_ms = time_ms*1000;
	updateShowTime(time_ms,SHOW_TIME_CURRENT);
}


void PVRUI::schUpdataRecordingState(float dt)
{
	//usb
	int time_s = CCPvrManager::getInstance()->getEstimateRecordRemainingTime();
		
	//schedule end time accessed 
	int time_rec = CCPvrManager::getInstance()->getCurRecordTime();	
	
	log("PVRUI:getEstimateRecordRemainingTime %d\n",time_s);
	log("PVRUI:getCurRecordTime %d\n",time_rec);
		
	if(time_s<5 ||time_rec>=(total_rec_ms/1000))//5s spare usb space,or schedule end,record must be ended
	{		
		stopPvr();
		
		if (1) {
				this->removeAllChildren();
				if (this->getParent()) {
					this->getParent()->removeChild(this);
					}
			}
		cocos2d::Node* curNode = tvScene::getTvLayer();				
		PVRRecodingComplete*  thumb = (PVRRecodingComplete*)PVRRecodingComplete::creatLayer(curNode);	
			
		log("PVRUI:pvr out,Get_TvPlayer()->playCur() in");
		Get_TvPlayer()->playCur();
		log("PVRUI:pvr out,Get_TvPlayer()->playCur() out");
	}	
	else if(time_s<30 && !usb_pop_flag)//30s spare usb space
	{
		usb_pop_flag = true;
		addMsgDialogPanel(RECORD_DIALOG_USB_FULL);
		Node *node = this->getChildByName("RECORD_DIALOG_USB_FULL");
		Sprite* sprite = static_cast<Sprite*>(node);
		addKeyListener(CC_CALLBACK_2(PVRUI::onKeyPressed_recodingUsbFull, this), sprite);
	}
	 
}


void PVRUI::UpdataTotalTime()
{

	updateShowTime(total_rec_ms,SHOW_TIME_TOTAL);
	
}


void PVRUI::addMsgDialogPanel(RecordMsgDialogType type)
{
	std::string panelinfo;
	std::string panelstring;
	Sprite* sprite;
	if(type == RECORD_DIALOG_RECORDING_COMPLETE)
	{
		sprite = Sprite::create("general/general_popup_bg.png", Rect(430, 272, 1060, 536));
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setPosition(Vec2(430, 272));
		
		ui::ImageView* imageView = ui::ImageView::create("info/info_popup_bg.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(1267,911));
		//imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(560, 355));
		sprite->addChild(imageView);
	
	}
	else
	{
		sprite = Sprite::create("general/general_popup_bg.png", Rect(430, 298, 1060, 490));
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setPosition(Vec2(430, 298));
		
		ui::ImageView* imageView = ui::ImageView::create("info/info_popup_bg.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(1267,911));
		//imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(560, 355));
		sprite->addChild(imageView);
	}
		
	
	if(type == RECORD_DIALOG_STOP_RECORDING)
	{
		panelinfo = "Now Recording,Are you sure you want to\nstop the recording?";
		panelstring = "RECORD_DIALOG_STOP_RECORDING";
	}
	if(type == RECORD_DIALOG_RECORDING_COMPLETE)
	{
		panelinfo = "Recording complete.";
		panelstring = "RECORD_DIALOG_RECORDING_COMPLETE";
	}
	if(type == RECORD_DIALOG_CHANGE_CHANNEL)
	{
		panelinfo = "Would you like to stop the recording and\nchange the channel?";
		panelstring = "RECORD_DIALOG_CHANGE_CHANNEL";
	}
	if(type == RECORD_DIALOG_USB_FULL)
	{
		panelinfo = "There isn't enough space.Do want to\n delete some saved files";
		panelstring = "RECORD_DIALOG_USB_FULL";
	}
		
	auto label = Label::createWithTTF(panelinfo, "general/SourceHanSansTWHK-Light.ttf", 40);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	label->setAlignment(TextHAlignment::LEFT);
	if(type == RECORD_DIALOG_RECORDING_COMPLETE)
			label->setPosition(Vec2(137, 385));
		else
			label->setPosition(Vec2(137, 280));
	sprite->addChild(label);
	
	
	if(type == RECORD_DIALOG_RECORDING_COMPLETE)
	{
		CChannel* pCh = Get_TvPlayer()->getCurChannel();
		std::vector<EpgEvent> pfEvents;
		unsigned short pfSize = 0;
		Channel tmpCh = pCh->get();
		if (CEpgManager::getInstance()->getEventPf(tmpCh, pfEvents)) {
			pfSize = pfEvents.size();
			// printf("\n############### pfSize:%d ############\n", pfSize);
		}
		
		auto label = Label::createWithTTF(pCh->getName(), "general/SourceHanSansTWHK-Light.ttf", 26);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(0x5b, 0x5b, 0x5b));	
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(136, 300));
		sprite->addChild(label);
		
		label = Label::createWithTTF("", "general/SourceHanSansTWHK-Light.ttf", 26);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(0x5b, 0x5b, 0x5b));	
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(136, 252));
		
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
		label->setPosition(Vec2(570, 252));
		
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
	}
	
	
	ui::ImageView* imageView = ui::ImageView::create("general/general_button_normal.png");
	imageView->setScale9Enabled(true);
	imageView->setContentSize(Size(300,72));
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(203, 87));
	sprite->addChild(imageView);
	
	if(type == RECORD_DIALOG_RECORDING_COMPLETE)	
		label = Label::createWithTTF("Play", "general/SourceHanSansTWHK-Light.ttf", 36);
	else
		label = Label::createWithTTF("Ok", "general/SourceHanSansTWHK-Light.ttf", 36);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(320, 90));
	sprite->addChild(label);	
	label->setLocalZOrder(3);	
	
	imageView = ui::ImageView::create("general/general_button_normal.png");
	imageView->setScale9Enabled(true);
	imageView->setContentSize(Size(300,72));
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(559, 87));
	sprite->addChild(imageView);
	if(type == RECORD_DIALOG_RECORDING_COMPLETE)		
		label = Label::createWithTTF("Brow", "general/SourceHanSansTWHK-Light.ttf", 33);
	else
		label = Label::createWithTTF("Cancel", "general/SourceHanSansTWHK-Light.ttf", 33);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x5b, 0x5b, 0x5b));
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(670, 90));
	sprite->addChild(label);
	label->setLocalZOrder(3);	
		
	imageView = ui::ImageView::create("general/general_button_focus.png");
	imageView->setScale9Enabled(true);	
	imageView->setContentSize(Size(360,120));
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(530, 42));			
	sprite->addChild(imageView,1,"general_button_focus");	
	
	this->addChild(sprite,1,panelstring);	
	
}



void PVRUI::addProgramRecord()
{
	Size size(1920, 169);	//162+7
	
	ui::Layout* layout = ui::Layout::create();
	layout->setContentSize(size);
	int width = layout->getContentSize().width;
	int height = layout->getContentSize().height;
	
	Sprite* sprite = Sprite::create("general/general_popup_bg.png", Rect(0, 0, 1920, 162));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(0, 0));		
	layout->addChild(sprite);
	
	
	sprite = Sprite::create("general/general_bg.png", Rect(0, 0, 1920, 66));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(0, 0));		
	layout->addChild(sprite);
	
	
	log("PVRUI:addProgramRecord 1");	
	
	CChannel* pCh = Get_TvPlayer()->getCurChannel();
	
	log("PVRUI:addProgramRecord 2");
	std::vector<EpgEvent> pfEvents;
	unsigned short pfSize = 0;
	Channel tmpCh = pCh->get();
	
	log("PVRUI:addProgramRecord 3");
	if (CEpgManager::getInstance()->getEventPf(tmpCh, pfEvents)) {
		pfSize = pfEvents.size();
		 printf("\n############### pfSize:%d ############\n", pfSize);
	}
	log("PVRUI:addProgramRecord 4");
	
	
	auto label = Label::createWithTTF(pCh->getNo(), "general/SourceHanSansTWHK-Light.ttf", 36);
	//LabelTTF* label = LabelTTF::create(DefaultPlayStr, "Arial", 36);
	//label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	//label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(40, 110));	
	layout->addChild(label,1,"channel No");
	
	log("PVRUI:addProgramRecord 5");
	
	ui::ImageView* imageView = ui::ImageView::create("general/general_listline.png");
	imageView->setScale9Enabled(true);
	imageView->setContentSize(Size(1,60));
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(70, 84));
	layout->addChild(imageView);
	
	label = Label::createWithTTF(pCh->getName(), "general/SourceHanSansTWHK-Light.ttf", 36);
	//LabelTTF* label = LabelTTF::create(DefaultPlayStr, "Arial", 36);
	//label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	//label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(200, 110));	
	layout->addChild(label,1,"Channel Name");
	
	log("PVRUI:addProgramRecord 6");
	
	//Programe Name
	label = Label::createWithTTF("", "general/SourceHanSansTWHK-Light.ttf", 36);
	//LabelTTF* label = LabelTTF::create(DefaultPlayStr, "Arial", 36);
	//label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(520, 110));
	if (pfSize > 0) 
	{
		if (NULL != pfEvents[0].eventName.c_str()) {
			label->setString(pfEvents[0].eventName.c_str());
		}
	}
		
	layout->addChild(label,1,"Programe Name");
	
	log("PVRUI:addProgramRecord 7");
	
	//Programe start time and end time
	
	label = Label::createWithTTF("", "general/SourceHanSansTWHK-Light.ttf", 26);
	label->setColor(Color3B(0, 0, 0));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(810, 110));	
	
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
		
		total_rec_ms = total_play_ms = 1000*pfEvents[0].duration;
		
	}
	log("PVRUI:addProgramRecord 8");
	layout->addChild(label);	
	
#ifdef USE_PVR_RECORD_DB
	
	//info.mRecordName = ;
    cur_info.mChannelName = pCh->getName();
    if (pfSize > 0)
        cur_info.mEventName = pfEvents[0].eventName;
    cur_info.mMouth = s_strTime.strMonth;
    cur_info.mDay = s_strTime.strDay;
    cur_info.mStartHour = s_strTime.strHour;
    cur_info.mStartMinute = s_strTime.strMinute;
    cur_info.mEndHour = e_strTime.strHour;
    cur_info.mEndMinute = e_strTime.strMinute;
    cur_info.mState = RECORD_STATE_COMPLETED;	
	
#endif	
	
	log("PVRUI:addProgramRecord 9");
	
	imageView = ui::ImageView::create("general/general_recordicon.png");
	//imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(1388, 114));
	layout->addChild(imageView);
	
	
	
	label = Label::createWithTTF("Recording", "general/SourceHanSansTWHK-Light.ttf", 36);
	//LabelTTF* label = LabelTTF::create(DefaultPlayStr, "Arial", 36);
	//label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0xdb, 0x33, 0x33));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(1490, 110));
	layout->addChild(label);
	
	
	
	imageView = ui::ImageView::create("rec/record_rec.png");
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(1111, 14));
	layout->addChild(imageView);		
	
	imageView = ui::ImageView::create("rec/record_ok.png");
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(1284, 14));
	layout->addChild(imageView);
	
	
	imageView = ui::ImageView::create("rec/record_rewinging.png");
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(1474, 24));
	layout->addChild(imageView);
	
	
	imageView = ui::ImageView::create("rec/record_fastforward.png");
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(1659, 24));
	layout->addChild(imageView);
	
	
	label = Label::createWithTTF(":Stop", "general/SourceHanSansTWHK-Light.ttf", 36);
	//label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0, 0, 0));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(1200, 25));
	layout->addChild(label);
	
	label = Label::createWithTTF(":Pause", "general/SourceHanSansTWHK-Light.ttf", 36);
	//label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0, 0, 0));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(1380, 25));
	layout->addChild(label);
	
	label = Label::createWithTTF(":Rewind", "general/SourceHanSansTWHK-Light.ttf", 36);
	//label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0, 0, 0));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(1560, 28));
	layout->addChild(label);
	
	label = Label::createWithTTF(":Fast Forward", "general/SourceHanSansTWHK-Light.ttf", 36);
	//label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0, 0, 0));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(1790, 28));
	layout->addChild(label);
	
	imageView = ui::ImageView::create("rec/record_progressbar_transparent.png");
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setScale9Enabled(true);
	imageView->setContentSize(Size(1920,7));
	imageView->setPosition(Vec2(0, 162));
	layout->addChild(imageView,0,"progressbar_transparent");
	
	PVRUpdateProgressBar *progressbar_red = new (std::nothrow) PVRUpdateProgressBar();
	progressbar_red->setProgressBarParam("rec/record_progressbar_red.png",Vec2(0,162));
	if (progressbar_red && progressbar_red->init())
	{
		progressbar_red->autorelease();
	}
	progressbar_red->UpdateProgressBar(22345678,87654321);
	layout->addChild(progressbar_red, 2, "progressbar_red");
	
	PVRUpdateProgressBar *progressbar_blue = new (std::nothrow) PVRUpdateProgressBar();
	progressbar_blue->setProgressBarParam("rec/record_progressbar_blue.png",Vec2(0,162));
	if (progressbar_blue && progressbar_blue->init())
	{
		progressbar_blue->autorelease();
	}
	progressbar_blue->UpdateProgressBar(12345678,87654321);
	layout->addChild(progressbar_blue, 3, "progressbar_blue");
	
	
	play_time = new (std::nothrow) PVRUpdateTime();
	if (play_time && play_time->init())
	{
		play_time->autorelease();
	}
	play_time->setLayoutPosition(Vec2(1615, 85));
	layout->addChild(play_time,1,"cur play show time");
	
	
	label = Label::createWithTTF("/", "general/SourceHanSansTWHK-Light.ttf", 28);
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	//label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(1772, 105));
	layout->addChild(label);
	
	total_time = new (std::nothrow) PVRUpdateTime();
	if (total_time && total_time->init())
	{
		total_time->autorelease();
	}
	total_time->setLayoutPosition(Vec2(1755, 85));
	layout->addChild(total_time,1,"total record show time");
	
	//showtime cursor
	
	imageView = ui::ImageView::create("rec/record_showtime1.png");
	imageView->setAnchorPoint(Vec2(0, 0));	
	imageView->setPosition(Vec2(1347, 173));
	
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
	imageView->setPosition(Vec2(1347, 173));
	
	cursor_time2 = new (std::nothrow) PVRUpdateTime();
	if (cursor_time2 && cursor_time2->init())
	{
		cursor_time2->autorelease();
	}
	cursor_time2->setLayoutPosition(Vec2(0, 0));
	
	imageView->addChild(cursor_time2,1,"showtime cursor inside");
	imageView->setVisible(true);	
	layout->addChild(imageView,1,"showtime cursor2");
	
	
	addChild(layout,0,"ProgramRecord Layout");	
	addKeyListener(CC_CALLBACK_2(PVRUI::onKeyPressed_ProgramRecord, this), layout);

		
	this->schedule(schedule_selector(PVRUI::schUpdataCursorTime), 1);
	this->schedule(schedule_selector(PVRUI::schUpdataCurTime), 1);
	this->schedule(schedule_selector(PVRUI::schUpdateProgressBar), 1);
	this->schedule(schedule_selector(PVRUI::schUpdataRecordingState), 1);
}

void PVRUI::addPauseIcon()
{
	this->unschedule(schedule_selector(PVRUI::schUpdataCursorTime));
	this->unschedule(schedule_selector(PVRUI::schUpdataCurTime));
	this->unschedule(schedule_selector(PVRUI::schUpdateProgressBar));
	this->unschedule(schedule_selector(PVRUI::schUpdataRecordingState));			
	ui::ImageView* imageView = ui::ImageView::create("rec/record_pause_normal.png");
	imageView->setPosition(Vec2(960, 560));
	
	addChild(imageView,0,"PVR pause icon recoding");
	
	
	pausePlayback();
	
	addKeyListener(CC_CALLBACK_2(PVRUI::onKeyPressed_PauseRecording, this), imageView);
	
}

void PVRUI::stopRecoding()
{	
	addMsgDialogPanel(RECORD_DIALOG_STOP_RECORDING);	
	Node *node = this->getChildByName("RECORD_DIALOG_STOP_RECORDING");
	Sprite* sprite = static_cast<Sprite*>(node);
	addKeyListener(CC_CALLBACK_2(PVRUI::onKeyPressed_stopRecoding, this), sprite);
}
void PVRUI::recodingComplete()
{
	addMsgDialogPanel(RECORD_DIALOG_RECORDING_COMPLETE);
	Node *node = this->getChildByName("RECORD_DIALOG_RECORDING_COMPLETE");
	Sprite* sprite = static_cast<Sprite*>(node);
	addKeyListener(CC_CALLBACK_2(PVRUI::onKeyPressed_recodingComplete, this), sprite);
}	
void PVRUI::changeChannelInRecoding()
{
	addMsgDialogPanel(RECORD_DIALOG_CHANGE_CHANNEL);
	Node *node = this->getChildByName("RECORD_DIALOG_CHANGE_CHANNEL");
	Sprite* sprite = static_cast<Sprite*>(node);
	addKeyListener(CC_CALLBACK_2(PVRUI::onKeyPressed_changeChannelInRecoding, this), sprite);
}


void PVRUI::onKeyPressed_stopRecoding(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{	
	stopPropagation(keyCode, event, false);
	
	Node *node = this->getChildByName("RECORD_DIALOG_STOP_RECORDING");
	Sprite* sprite = static_cast<Sprite*>(node);
	node = sprite->getChildByName("general_button_focus");
	ui::ImageView* img = static_cast<ui::ImageView*>(node);
	
	Vec2 position = img->getPosition();
	
	switch(keyCode)
	{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
			if(position.x == 530)
			{
				img->setVisible(false);			
				img->setPosition(Vec2(174,42));
				img->setVisible(true);
				
			}
			break;
			
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
			if(position.x == 174)
			{
				img->setVisible(false);			
				img->setPosition(Vec2(530,42));
				img->setVisible(true);
				
			}
			break;
		
		case EventKeyboard::KeyCode::KEY_ENTER:
		case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
			this->removeChildByName("RECORD_DIALOG_STOP_RECORDING");
			
			if(position.x == 174)
			{
				stopPvr();
				this->removeChildByName("ProgramRecord Layout");
				//Todo stop recoding
				recodingComplete();
			}
			
						
			break;
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:			
			this->removeChildByName("RECORD_DIALOG_STOP_RECORDING");
			break;
		default:
			break;
	}
}

void PVRUI::onKeyPressed_recodingComplete(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);
	
	Node *node = this->getChildByName("RECORD_DIALOG_RECORDING_COMPLETE");
	Sprite* sprite = static_cast<Sprite*>(node);
	node = sprite->getChildByName("general_button_focus");
	ui::ImageView* img = static_cast<ui::ImageView*>(node);
	
	Vec2 position = img->getPosition();
	
	
	switch(keyCode)
	{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
			if(position.x == 530)
			{
				img->setVisible(false);			
				img->setPosition(Vec2(174,42));
				img->setVisible(true);
				
			}
			break;
			
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
			if(position.x == 174)
			{
				img->setVisible(false);			
				img->setPosition(Vec2(530,42));
				img->setVisible(true);
				
			}
			break;
		case EventKeyboard::KeyCode::KEY_ENTER:
		case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
			//this->removeChildByName("RECORD_DIALOG_RECORDING_COMPLETE");
			
			
			if(position.x == 174)
			{
								
				std::string mountpath;
				CCPvrManager *pPvrManager = CCPvrManager::getInstance();
				pPvrManager->getPvrMountPath(mountpath);				
				log("PVRUI:mountpath %s\n",mountpath.c_str());
				mountpath +="/_MSTPVR/";
#ifdef USE_PVR_RECORD_DB
				
				mountpath += cur_info.mRecordName;	
#else				
			
				mountpath += lastRecodingFileName;	
#endif			
				log("PVRUI:play %s",mountpath.c_str());				
						
				cocos2d::Node* curNode = tvScene::getTvLayer();
				LocalVideoPlayer*  player = (LocalVideoPlayer*)LocalVideoPlayer::creatLayer(curNode);
				//player->play(mountpath);
				player->play_pvr(cur_info.mRecordName);
	
			}
			else
			{
				//Todo browse recorded file
				auto scene = Director::getInstance()->getRunningScene();
				localMedia::creatLayer(scene);
						
				
			}
			
			if (1) {
				this->removeAllChildren();
				if (this->getParent()) {
					this->getParent()->removeChild(this);
					}
					}
			break;
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:
			
			//this->removeChildByName("RECORD_DIALOG_RECORDING_COMPLETE");
			if (1) {
				this->removeAllChildren();
				if (this->getParent()) {
					this->getParent()->removeChild(this);
					}
					}
			log("PVRUI:pvr out,Get_TvPlayer()->playCur() in");
			Get_TvPlayer()->playCur();
			log("PVRUI:pvr out,Get_TvPlayer()->playCur() out");
			break;
		default:
			break;
	}
}
void PVRUI::onKeyPressed_changeChannelInRecoding(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);
	
	Node *node = this->getChildByName("RECORD_DIALOG_CHANGE_CHANNEL");
	Sprite* sprite = static_cast<Sprite*>(node);
	node = sprite->getChildByName("general_button_focus");
	ui::ImageView* img = static_cast<ui::ImageView*>(node);
	
	Vec2 position = img->getPosition();
	
	switch(keyCode)
	{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
			if(position.x == 530)
			{
				img->setVisible(false);			
				img->setPosition(Vec2(174,42));
				img->setVisible(true);
				
			}
			break;
			
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
			if(position.x == 174)
			{
				img->setVisible(false);			
				img->setPosition(Vec2(530,42));
				img->setVisible(true);
				
			}
			break;
		case EventKeyboard::KeyCode::KEY_ENTER:
		case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
			this->removeChildByName("RECORD_DIALOG_CHANGE_CHANNEL");
			if(position.x == 174)
			{
				//Todo change channel
			}
			
			break;
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:
			this->removeChildByName("RECORD_DIALOG_CHANGE_CHANNEL");
			
			break;
		default:
			break;
	}
}

void PVRUI::onKeyPressed_ProgramRecord(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);  
    
    Node *node = this->getChildByName("ProgramRecord Layout");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 
		
    
    switch(keyCode) 
	{
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_DOWN:
		{
				cocos2d::Node* curNode = tvScene::getTvLayer();
				//PVRRecodingThumbnail::creatLayer(scene);
				PVRRecodingThumbnail*  thumb = (PVRRecodingThumbnail*)PVRRecodingThumbnail::creatLayer(curNode);
				thumb->hidePVRUI();
				break;
		}
		
		case EventKeyboard::KeyCode::KEY_TV_RECORD:
		case EventKeyboard::KeyCode::KEY_SHIFT:
			//Todo stop recording
			stopRecoding();
			break;
			
		case EventKeyboard::KeyCode::KEY_ENTER:
	    case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
	    	addPauseIcon();
	    	
	    	break;
		
		case EventKeyboard::KeyCode::KEY_TV_REWIND:
			//Todo 
			break;
		
		case EventKeyboard::KeyCode::KEY_TV_FASTFORWARD:
			//Todo
			break;			
		
				
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:		
		{						
			this->removeChildByName("ProgramRecord Layout");
			
			this->unschedule(schedule_selector(PVRUI::schUpdataCursorTime));
			this->unschedule(schedule_selector(PVRUI::schUpdataCurTime));
			this->unschedule(schedule_selector(PVRUI::schUpdateProgressBar));
			this->unschedule(schedule_selector(PVRUI::schUpdataRecordingState));	
			if (1) {
				this->removeAllChildren();
				if (this->getParent()) {
					this->getParent()->removeChild(this);
					}
					}
			
			break;
		}	
			
		default:
			break;	
		
	}
      
    
}

void PVRUI::onKeyPressed_PauseRecording(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);  
    
    Node *node = this->getChildByName("PVR pause icon recoding");
	ui::ImageView* img = static_cast<ui::ImageView*>(node); 
		
    
    switch(keyCode) 
	{
		case EventKeyboard::KeyCode::KEY_ENTER:
	    case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
	    	//Todo resume recoding
	    	this->removeChildByName("PVR pause icon recoding");
	    	
	    	resumePlayback();
	    	
	    	
	    	this->schedule(schedule_selector(PVRUI::schUpdataCursorTime), 1);
			this->schedule(schedule_selector(PVRUI::schUpdataCurTime), 1);
			this->schedule(schedule_selector(PVRUI::schUpdateProgressBar), 1);
			this->schedule(schedule_selector(PVRUI::schUpdataRecordingState), 1);
	    	break;
			
		default:
			break;	
		
	}
	
}


void PVRUI::onKeyPressed_recodingUsbFull(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);
	
	Node *node = this->getChildByName("RECORD_DIALOG_USB_FULL");
	Sprite* sprite = static_cast<Sprite*>(node);
	node = sprite->getChildByName("general_button_focus");
	ui::ImageView* img = static_cast<ui::ImageView*>(node);
	
	Vec2 position = img->getPosition();
	
	switch(keyCode)
	{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
			if(position.x == 530)
			{
				img->setVisible(false);			
				img->setPosition(Vec2(174,42));
				img->setVisible(true);
				
			}
			break;
			
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
			if(position.x == 174)
			{
				img->setVisible(false);			
				img->setPosition(Vec2(530,42));
				img->setVisible(true);
				
			}
			break;
		
		case EventKeyboard::KeyCode::KEY_ENTER:
		case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
			
			this->removeChildByName("RECORD_DIALOG_USB_FULL");
			if(position.x == 174)
			{
				stopPvr();
				
				{
					auto scene = Director::getInstance()->getRunningScene();
					localMedia::creatLayer(scene);				
				}
				
				if (1) {
					this->removeAllChildren();
					if (this->getParent()) {
						this->getParent()->removeChild(this);
						}
						}
			}				
						
			break;
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:			
			
			break;
		default:
			break;
	}
	
	
}




void PVRUI::startRecord()
{

log("PVRUI:startRecord in");
	std::string path;
	
	std::map<std::string, std::string>  usbPathMap; 
	usbPathMap = deviceDetect::getInstance()->getUsbPath();
	std::map<std::string, std::string>::iterator it;
	for (it = usbPathMap.begin(); it != usbPathMap.end(); ++it)
	{
		path = it->second;
		//getDirList(path.c_str(), GET_TYPE_ALL, m_pictureVec, m_audioVec, m_videoVec, m_fileVec);
	}
	
	CCPvrManager *pPvrManager = CCPvrManager::getInstance();
log("PVRUI:usb path %s",path.c_str());
	pPvrManager->setPvrParams(path.c_str(),0);

	if(pPvrManager->isTimeShift() == TRUE)
	{
		log("PVRUI:startTimeShiftRecord in");
		pPvrManager->startTimeShift();
		log("PVRUI:startTimeShiftRecord out");
	}
	else
	{
		log("PVRUI:startRecord in");
		pPvrManager->startRecord();
		log("PVRUI:startRecord out");
	}
	
	pPvrManager->getCurRecordingFileName(cur_info.mRecordName);	
	
#ifdef USE_PVR_RECORD_DB	
	log("PVRUI:addPvrRecord in. getCurRecordingFileName %s",cur_info.mRecordName.c_str());	
	log("PVRUI:addPvrRecord in. cur_info.mChannelName %s",cur_info.mChannelName.c_str());	
	log("PVRUI:addPvrRecord in. cur_info.mEventName %s",cur_info.mEventName.c_str());	
	log("PVRUI:addPvrRecord in. cur_info.mMouth %s",cur_info.mMouth.c_str());	
	log("PVRUI:addPvrRecord in. cur_info.mDay %s",cur_info.mDay.c_str());	
	log("PVRUI:addPvrRecord in. cur_info.mStartHour %s",cur_info.mStartHour.c_str());	
	log("PVRUI:addPvrRecord in. cur_info.mStartMinute %s",cur_info.mStartMinute.c_str());	
	log("PVRUI:addPvrRecord in. cur_info.mEndHour %s",cur_info.mEndHour.c_str());	
	log("PVRUI:addPvrRecord in. cur_info.mEndMinute %s",cur_info.mEndMinute.c_str());	
	log("PVRUI:addPvrRecord in. cur_info.mState %d",cur_info.mState);	
			
	recordDB->addPvrRecord(cur_info);
	log("PVRUI:addPvrRecord out");	
#endif	
	//30s
	this->scheduleOnce(schedule_selector(PVRUI::schStartPlayBack), 10);	
	

}
void PVRUI::stopRecord()
{
	CCPvrManager *pPvrManager = CCPvrManager::getInstance();
log("PVRUI:stop in");
	if(pPvrManager->isPlaybacking())
	{
		log("PVRUI:isPlaybacking true");	
		if(pPvrManager->isTimeShift() == TRUE)
		{
			log("PVRUI:stopTimeShiftPlayback in");
			pPvrManager->stopTimeShiftPlayback();
			log("PVRUI:stopTimeShiftPlayback out");
		}
		else
		{
			log("PVRUI:stopPlayback in");
			pPvrManager->stopPlayback();
			log("PVRUI:stopPlayback out");
		}
	}
	

	
	if(pPvrManager->isRecording())
	{
		log("PVRUI:stopRecord in");
		pPvrManager->stopRecord();
		log("PVRUI:stopRecord out");
	}
	else if(pPvrManager->isTimeShift())
	{
		log("PVRUI:stopTimeShiftRecord in");
		pPvrManager->stopTimeShift();
		log("PVRUI:stopTimeShiftRecord out");
	}

		
}


void PVRUI::schStartPlayBack(float dt)
{
	CCPvrManager *pPvrManager = CCPvrManager::getInstance();
	log("PVRUI:getCurRecordingFileName");
	std::string strFileName;
	pPvrManager->getCurRecordingFileName(strFileName);
	
	log("PVRUI:getCurRecordingFileName %s",strFileName.c_str());
	//停止dtv播放
	log("PVRUI:Get_TvPlayer()->stop()");
	Get_TvPlayer()->stop();

	if(pPvrManager->isTimeShift() == TRUE)
	{
		log("PVRUI:startTimeShiftPlayback in");
		pPvrManager->startTimeShiftPlayback();
		log("PVRUI:startTimeShiftPlayback out");
	}
	else
	{
		log("PVRUI:startPlayback in");
		log("PVRUI:play filename %s",strFileName.c_str());
		pPvrManager->startPlayback(strFileName.c_str());
		log("PVRUI:startPlayback out");
	}
	
	

}

void PVRUI::pausePlayback()
{
	CCPvrManager *pPvrManager = CCPvrManager::getInstance();
	log("PVRUI:pause in");
	if(pPvrManager->isPlaybacking() && (!pPvrManager->isPlaybackPaused()))
	{
		log("PVRUI:pausePlayback in");
		pPvrManager->pausePlayback();
		log("PVRUI:pausePlayback out");
	}
	

}

void PVRUI::resumePlayback()
{
	CCPvrManager *pPvrManager = CCPvrManager::getInstance();
	log("PVRUI:resume in");
    if(pPvrManager->isPlaybackPaused())
    { 
    	log("PVRUI:resumePlayback in");   
		pPvrManager->resumePlayback();
		log("PVRUI:resumePlayback out");  
	}

}
void PVRUI::stopPvr()
{	
	this->unschedule(schedule_selector(PVRUI::schUpdataCursorTime));
	this->unschedule(schedule_selector(PVRUI::schUpdataCurTime));
	this->unschedule(schedule_selector(PVRUI::schUpdateProgressBar));
	this->unschedule(schedule_selector(PVRUI::schUpdataRecordingState));
#ifdef USE_PVR_RECORD_DB
	log("PVRUI:updateRecordStatus in.mRecordName %s",cur_info.mRecordName.c_str());	
	recordDB->updateRecordStatus(cur_info.mRecordName.c_str(),RECORD_STATE_COMPLETED);						
	log("PVRUI:updateRecordStatus out");	
#endif			

	stopRecord();	
}

