#include "ChannelListPage.h"
#include "CustomTableViewCell.h"

#include "common/common.h"
#include "tvplayer/TvPlayer.h"

USING_NS_CC;
USING_NS_CC_EXT;




// on "init" you need to initialize your instance
bool ChannelListPageView::init(ElementDisplayListSystem *edls,ssize_t index,bool is_channellist)
{
	
	numberofchannels = edls->validChannelCount();
	cellcurrentPlayedChannelIndex = 0;
	this->is_channellist = is_channellist;  
	this->edls = edls;
#if 0
	favorite = new bool[numberofchannels];
	locked = new bool[numberofchannels];

	for (ssize_t i = 0; i < numberofchannels; i++)
	{
		if (random(0, 1) != 0)
			favorite[i] = false;
		if (random(0, 1) != 0)
			locked[i] = false;
	}
	
#endif

//	TableView* tableView = TableView::create(this, Size(700, 816));
	ChannelListTableView* tableView = ChannelListTableView::create(this, Size(700, 816));

	Size winSize = Director::getInstance()->getWinSize();


	tableView->setDirection(ScrollView::Direction::VERTICAL);
	//tableView->setPosition(Vec2(100, winSize.height / 2 - 50));
	tableView->setPosition(Vec2(0, 106));
	
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		
		
//	Vec2 vec = tableView->minContainerOffset();
//	Size size = tableView->getViewSize();
//	Size size1 = tableView->getContentSize();
	this->addChild(tableView,0,CHLIST_TAB_TAG+index);
	tableView->reloadData();
	
//	//ChannelListPageView keyboard listener
//	auto listener = EventListenerKeyboard::create();
//    listener->onKeyPressed = CC_CALLBACK_2(ChannelListPageView::onKeyPressed, this);
//    listener->onKeyReleased = CC_CALLBACK_2(ChannelListPageView::onKeyReleased, this);	
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	   
    return true;
}

void ChannelListPageView::tableCellTouched(TableView* table, TableViewCell* cell)
{
    CCLOG("cell touched at index: %ld", cell->getIdx());

	if (cell->getIdx() != cellcurrentPlayedChannelIndex)
	{
		TableViewCell* previewCell;
		Label* labelChannelNumber;
		Label* labelChannelName;
		using namespace cocos2d::ui;
        LoadingBar* loadingBarProgress;

		previewCell = table->cellAtIndex(cellcurrentPlayedChannelIndex);

		if (previewCell != NULL)
		{/*
			labelChannelNumber = (Label*)previewCell->getChildByName("ChannelName");
			labelChannelNumber->setTextColor(Color4B::BLACK);
			labelChannelName = (Label*)previewCell->getChildByName("ChannelNumber");
			labelChannelName->setTextColor(Color4B::BLACK);
			loadingBarProgress = (LoadingBar*)previewCell->getChildByName("Progress");
			loadingBarProgress->setHighlighted(false);
			*/
		}
		cellcurrentPlayedChannelIndex = cell->getIdx();


	}
}

Size ChannelListPageView::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    //if (idx == cellcurrentPlayedChannelIndex) {
    //    return Size(100, 100);
    //}
    //return Size(80, 80);
    if(is_channellist)
    	return Size(700, 136);
    else
    	return Size(700, 117);
}

TableViewCell* ChannelListPageView::tableCellAtIndex(TableView *table, ssize_t idx)
{
    //auto string = StringUtils::format("%ld", idx);
    //auto string = tmpCh->getName();
    TableViewCell *cell = table->dequeueCell();
	CChannel* tmpCh = edls->getChannel(idx);

	//std::string channelName = "Channel Name";
	//std::string channelNumber = tmpCh->getNo();
	std::string channelNumber = StringUtils::format("%ld", idx);
	
	std::string channelName = tmpCh->getName();
	std::string programName = tmpCh->getName();

    if (!cell) {
        cell = new (std::nothrow) CustomTableViewCell();
        cell->autorelease();

		ui::ImageView *imageView = ui::ImageView::create("general/general_listline.png");
		//imageView = ui::ImageView::create("channellist/channellist_line_px2.png");
		imageView->setScale9Enabled(true);
		imageView->setContentSize(Size(700,1));

	
		//ui::ImageView* imageView = ui::ImageView::create("channellist/channellist_line_px2.png");
		imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(0, 0));
		cell->addChild(imageView);
		imageView->setLocalZOrder(5);

        //auto labelChannelNumber = Label::createWithSystemFont(string, "Helvetica", 33);
        auto labelChannelNumber = Label::createWithTTF(channelNumber, "general/SourceHanSansTWHK-Light.ttf", 33);
		labelChannelNumber->setName("ChannelNumber");
		
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
		labelChannelName->setName("ChannelName");
#if 1
		labelChannelName->setAnchorPoint(Vec2::ZERO);
		if(is_channellist)
			labelChannelName->setPosition(Vec2(93, 56));
		else
			labelChannelName->setPosition(Vec2(93, 26));
#else		
		labelChannelName->setPosition(Vec2(190, 92));	
#endif			
		labelChannelName->setTextColor(Color4B::BLACK);
		//labelChannelNumber->setTextColor(Color4B(51, 51, 51, 255));
		cell->addChild(labelChannelName);

		if(is_channellist)
		{
		auto labelprogramName = Label::createWithTTF(programName, "general/SourceHanSansTWHK-Light.ttf", 28);
		labelprogramName->setName("ProgramName");
#if 0
		labelprogramName->setAnchorPoint(Vec2::ZERO);
		labelChannelName->setPosition(Vec2(93, 30));
#else		
		labelprogramName->setPosition(Vec2(190, 36));
#endif		
		//labelprogramName->setTextColor(Color4B::GRAY);
		labelprogramName->setTextColor(Color4B(153, 153, 153, 255));
		cell->addChild(labelprogramName);
        }
		
		//if(locked[idx])
		//if(tmpCh->isLock())
		{
			auto spriteLock = Sprite::create("general/general_lockicon.png", Rect(0.0, 0.0, 43, 35));
			
			//spriteLock->setPosition(400.0, 0);
			if(is_channellist)
				spriteLock->setPosition(Vec2(590, 92));
			else
				spriteLock->setPosition(Vec2(590, 52));	
				
			if(tmpCh->isLock())
				spriteLock->setVisible(true);
			else
				spriteLock->setVisible(false);
				
			cell->addChild(spriteLock,1,"lock icon");
		}

		//if(favorite[idx])
		//if(tmpCh->isFav())
		{
		    //auto spriteFavorite = Sprite::create("Images/favorite.png", Rect(85*0, 121*1, 43, 35));
			auto spriteFavorite = Sprite::create("general/general_favicon.png", Rect(0.0, 0.0, 43, 35));
			
			//spriteFavorite->setPosition(450.0, 0);
			if(is_channellist)
				spriteFavorite->setPosition(Vec2(650, 92));
			else
				spriteFavorite->setPosition(Vec2(650, 52));
		    
		    auto action = FadeIn::create(2);
		    auto action_back = action->reverse();
		    auto fade = RepeatForever::create( Sequence::create( action, action_back, nullptr) );
		    
		    auto tintred = TintBy::create(2, 0, -255, -255);
		    auto tintred_back = tintred->reverse();
		    auto red = RepeatForever::create( Sequence::create( tintred, tintred_back, nullptr) );
		        
		    auto tintblue = TintBy::create(2, -255, -255, 0);
		    auto tintblue_back = tintblue->reverse();
		    auto blue = RepeatForever::create( Sequence::create( tintblue, tintblue_back, nullptr) );
		    
			spriteFavorite->runAction(red);
		    //sprite6->runAction(green);
		    //sprite7->runAction(blue);
		    //sprite8->runAction(fade);
		    
		    
		    if(tmpCh->isFav())
		    	spriteFavorite->setVisible(true);
		    else
		    	spriteFavorite->setVisible(false);
		    // late add: test dirtyColor and dirtyPosition
		    cell->addChild(spriteFavorite,1,"favourite icon");
		}
		
		if(is_channellist)
		{
		using namespace cocos2d::ui;
        // Create the loading bar
        LoadingBar* loadingBarProgress = LoadingBar::create("channellist/channellist_program_progress.png");
        loadingBarProgress->setTag(0);
        loadingBarProgress->setName("Progress");
		loadingBarProgress->setHighlighted(false);
        loadingBarProgress->setPercent(random(0, 100));
        //loadingBarProgress->setPosition(Vec2(400.0, -30.0));
        loadingBarProgress->setPosition(Vec2(590, 46));
		cell->addChild(loadingBarProgress);

		}

		
    }
    else
    {
		
		{

			//auto labelChannelNumber = (Label*)cell->getChildByTag(123);
			auto labelChannelNumber = (Label*)cell->getChildByName("ChannelNumber");
			labelChannelNumber->setString(channelNumber);

			auto labelchannelName = (Label*)cell->getChildByName("ChannelName");
			labelchannelName->setString(channelName);
			if (is_channellist)
			{
				auto labelProgName = (Label*)cell->getChildByName("ProgramName");
				labelProgName->setString(programName);
			}
			
			
			Sprite* spriteFavorite = (Sprite*)cell->getChildByName("favourite icon");
			if(tmpCh->isFav())
		    	spriteFavorite->setVisible(true);
		    else
		    	spriteFavorite->setVisible(false);
			
			Sprite* spriteLock = (Sprite*)cell->getChildByName("lock icon");
			if(tmpCh->isLock())
				spriteLock->setVisible(true);
			else
				spriteLock->setVisible(false);
			
		}
    }

	 
    return cell;
}

ssize_t ChannelListPageView::numberOfCellsInTableView(TableView *table)
{
    //return numberofchannels;
    return edls->validChannelCount();
}

void ChannelListPageView::tableCellHighlight(TableView *table, TableViewCell *cell)
{  
	Label* labelChannelNumber;
	Label* labelChannelName;
	using namespace cocos2d::ui;
	LoadingBar* loadingBarProgress;

	CCLOG("cell Highlight at index: %ld", cell->getIdx());
	
	labelChannelNumber = (Label*)cell->getChildByName("ChannelNumber");
	labelChannelNumber->setTextColor(Color4B::GREEN);
	
	labelChannelName = (Label*)cell->getChildByName("ChannelName");
	labelChannelName->setTextColor(Color4B::GREEN);
	//labelChannelName->enableOutline(Color4B::RED);
	
	loadingBarProgress = (LoadingBar*)cell->getChildByName("Progress");
	loadingBarProgress->setHighlighted(true);
	
}  
  
void ChannelListPageView::tableCellUnhighlight(TableView *table, TableViewCell *cell)
{  
    CCLOG("cell Unhighlight at index: %ld", cell->getIdx());
	
	Label* labelChannelNumber;
	Label* labelChannelName;
	using namespace cocos2d::ui;
	LoadingBar* loadingBarProgress;

	labelChannelNumber = (Label*)cell->getChildByName("ChannelName");
	labelChannelNumber->setTextColor(Color4B::BLACK);
	labelChannelName = (Label*)cell->getChildByName("ChannelNumber");
	labelChannelName->setTextColor(Color4B::BLACK);
	loadingBarProgress = (LoadingBar*)cell->getChildByName("Progress");
	loadingBarProgress->setHighlighted(false);
      
}  

void ChannelListPageView::tableCellWillRecycle(TableView *table, TableViewCell *cell)
{  
    CCLOG("cell CellWillRecycle at index: %ld", cell->getIdx());
      
}  

