#include "ChannelListPageRecorded.h"
#include "CustomTableViewCell.h"

#include "common/common.h"
#include "tvplayer/TvPlayer.h"
#include "tvplayer/CTime.h"


USING_NS_CC;
USING_NS_CC_EXT;


bool ChannelListPageRecorded::init(ElementDisplayListSystem *edls,ssize_t index,bool is_channellist)
{
	
#ifdef USE_PVR_RECORD_DB
	recordDB = PVRRecordDB::getInstance();	
	log("ChannelListPageRecorded:getPvrRecords in");		
	if(recordDB->getPvrRecords(pvrlist) == 0)
		numberofchannels = pvrlist.size();	
	log("ChannelListPageRecorded:getPvrRecords out. pvrlist.size() %d",numberofchannels);		
#else
	CCPvrManager *pPvrManager = CCPvrManager::getInstance();
	numberofchannels = pPvrManager->getPvrFileNumber();
#endif
	
	log("ChannelListPageRecorded:number of recorded %d",numberofchannels);
	
	
	this->is_channellist = is_channellist;  
	this->edls = edls;
	
	
	if(numberofchannels>0)
	{
//	TableView* tableView = TableView::create(this, Size(700, 816));
		ChannelListTableView* tableView = ChannelListTableView::create(this, Size(700, 816));
	
		Size winSize = Director::getInstance()->getWinSize();
	
	
		tableView->setDirection(ScrollView::Direction::VERTICAL);
		//tableView->setPosition(Vec2(100, winSize.height / 2 - 50));
		tableView->setPosition(Vec2(0, 106));
		
		tableView->setDelegate(this);
		tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	
		this->addChild(tableView,0,CHLIST_TAB_TAG+index);
		tableView->reloadData();
	}
	   
    return true;
}

TableViewCell* ChannelListPageRecorded::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();

	std::string channelNumber = StringUtils::format("%ld", idx);
	std::string channelName;
	std::string programName;		
		
#ifdef USE_PVR_RECORD_DB
	channelName = pvrlist[idx].mChannelName;
	programName = pvrlist[idx].mEventName;
	
#else    
    CCPvrFileInfo info;
    CCPvrManager *pPvrManager = CCPvrManager::getInstance();
	pPvrManager->getPvrFileInfo(idx,info);
	
	log("ChannelListPageRecorded:in tableCellAtIndex\n");
	log("ChannelListPageRecorded:info.filename %s",info.filename.c_str());
	pPvrManager->getFileServiceName(info.filename,channelName);
	pPvrManager->getFileEventName(info.filename,programName);    
    //pPvrManager->getFileEventDesc(info.filename,strDesc);    
#endif  
	

    if (!cell) {
        cell = new (std::nothrow) CustomTableViewCell();
        cell->autorelease();

		ui::ImageView *imageView = ui::ImageView::create("general/general_listline.png");
		imageView->setScale9Enabled(true);
		imageView->setContentSize(Size(700,1));
		
		imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(0, 0));
		cell->addChild(imageView);
		imageView->setLocalZOrder(5);

        auto labelChannelNumber = Label::createWithTTF(channelNumber, "general/SourceHanSansTWHK-Light.ttf", 33);
		labelChannelNumber->setName("Channel Number");
		
		if(is_channellist)
        	labelChannelNumber->setPosition(Vec2(42, 68)); 
        else
        	labelChannelNumber->setPosition(Vec2(42, 58));        
		//labelChannelNumber->setTextColor(Color4B::BLACK);
		labelChannelNumber->setTextColor(Color4B(51, 51, 51, 255));
        labelChannelNumber->setTag(123);
        cell->addChild(labelChannelNumber);
		
		// Chinese
		//auto labelChannelName = Label::createWithTTF(chinese, "fonts/HKYuanMini.ttf", 24);
		auto labelChannelName = Label::createWithTTF(channelName, "general/SourceHanSansTWHK-Light.ttf", 36);
		labelChannelName->setName("Channel Name");
#if 1
		labelChannelName->setAnchorPoint(Vec2::ZERO);
		if(is_channellist)
			labelChannelName->setPosition(Vec2(93, 56));
		else
			labelChannelName->setPosition(Vec2(93, 26));
#else		
		labelChannelName->setPosition(Vec2(220, 92));	
#endif			
		labelChannelName->setTextColor(Color4B::BLACK);
		//labelChannelNumber->setTextColor(Color4B(51, 51, 51, 255));
		cell->addChild(labelChannelName);

		if(is_channellist)
		{
		auto labelprogramName = Label::createWithTTF(programName, "general/SourceHanSansTWHK-Light.ttf", 28);
		labelprogramName->setName("Program Name");
#if 0
		labelprogramName->setAnchorPoint(Vec2::ZERO);
		labelChannelName->setPosition(Vec2(93, 30));
#else		
		labelprogramName->setPosition(Vec2(220, 36));
#endif		
		//labelprogramName->setTextColor(Color4B::GRAY);
		labelprogramName->setTextColor(Color4B(153, 153, 153, 255));
		cell->addChild(labelprogramName);
        }
        
        Label *label;
        
#ifdef USE_PVR_RECORD_DB
		log("ChannelListPageRecorded:pvrlist[idx].mState %d",pvrlist[idx].mState);
		if(pvrlist[idx].mState == RECORD_STATE_FAILED)
		{
			
			imageView = ui::ImageView::create("channellist/channellist_recordicon_failed.png");
			imageView->setPosition(Vec2(520, 90));
			cell->addChild(imageView);
			
			label = Label::createWithTTF("Failed", "general/SourceHanSansTWHK-Light.ttf", 28);
			label->setTextColor(Color4B(153, 153, 153, 255));		
			label->setPosition(Vec2(615, 80));	
			cell->addChild(label);	
			
			
		}
		else if(pvrlist[idx].mState == RECORD_STATE_COMPLETED)
#endif
		{			
	        imageView = ui::ImageView::create("channellist/channellist_recordicon_succeed.png");
			imageView->setPosition(Vec2(520, 90));
			cell->addChild(imageView);
			
			label = Label::createWithTTF("Completed", "general/SourceHanSansTWHK-Light.ttf", 28);
			label->setTextColor(Color4B(153, 153, 153, 255));		
			label->setPosition(Vec2(615, 80));	
			cell->addChild(label);		
		}
		
		label = Label::createWithTTF("", "general/SourceHanSansTWHK-Light.ttf", 28);
		label->setTextColor(Color4B(153, 153, 153, 255));			
		label->setPosition(Vec2(570, 36));		
			
#ifdef USE_PVR_RECORD_DB
		log("ChannelListPageRecorded:pvrlist[idx].mMouth %s",pvrlist[idx].mMouth.c_str());
		std::string presentTime = pvrlist[idx].mMouth;
		presentTime += ".";
		presentTime += pvrlist[idx].mDay;				
		presentTime +=  "(";
		presentTime += pvrlist[idx].mStartHour;
		presentTime += ":";
		presentTime += pvrlist[idx].mStartMinute;
		presentTime += " - ";
		presentTime += pvrlist[idx].mEndHour;
		presentTime += ":";
		presentTime += pvrlist[idx].mEndMinute;
		presentTime += ")";
		// presentTime.append(" -- ", strTime.strMinute)
		// printf("\n############### presentTime:%s ############\n", presentTime.c_str());
		label->setString(presentTime.c_str());	
#else		
		int Duration =  pPvrManager->getRecordedFileDurationTime(info.filename);
		log("ChannelListPageRecorded:getRecordedFileDurationTime %d",Duration);
		SkyTvTimeString strTime;
		if (numberofchannels > 0) 
		{
			CTime::seconds2TimeString(info.recordStartTime, strTime);
			std::string presentTime = strTime.strMonth;
			presentTime += ".";
			presentTime += strTime.strDay;				
			presentTime +=  "(";
			presentTime += strTime.strHour;
			presentTime += ":";
			presentTime += strTime.strMinute;
			presentTime += " - ";
			CTime::seconds2TimeString(info.recordStartTime+Duration, strTime);
			presentTime += strTime.strHour;
			presentTime += ":";
			presentTime += strTime.strMinute;
			presentTime += ")";
			// presentTime.append(" -- ", strTime.strMinute)
			// printf("\n############### presentTime:%s ############\n", presentTime.c_str());
			label->setString(presentTime.c_str());			
		}
#endif		
		cell->addChild(label);
	
    }
    else
    {
		if (is_channellist)
		{

			//auto labelChannelNumber = (Label*)cell->getChildByTag(123);
			auto labelChannelNumber = (Label*)cell->getChildByName("Channel Number");
			labelChannelNumber->setString(channelNumber);

			auto labelchannelName = (Label*)cell->getChildByName("Channel Name");
			labelchannelName->setString(channelName);

			auto labelProgName = (Label*)cell->getChildByName("Program Name");
			labelProgName->setString(programName);
		}
    }

	 
    return cell;
}

ssize_t ChannelListPageRecorded::numberOfCellsInTableView(TableView *table)
{
    return numberofchannels;
}
