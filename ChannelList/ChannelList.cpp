#include "ChannelList.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/UIPageView.h"
#include "ChannelListPage.h"
#include "common/ChannelPin.h"
#include "tvScene.h"
#include "localMedia/localVideoPlayer.h"
#include "tvplayer/CTime.h"


USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocostudio::timeline;


ChannelList::ChannelList()
{
	this->setName("ChannelList");
	log("ChannelList::ChannelList");
}

ChannelList::~ChannelList()
{
	
}


bool ChannelList::skyShow(cocos2d::Node* node)
{
	if (node) {
		auto layer = node->getChildByName("ChannelList");
		if (layer) {
			layer->setVisible(true);
		}			
		else {
			auto player = ChannelList::create();
			node->addChild(player);
			player->setVisible(true);
		}
		return true;
	}
	return false;
}
void ChannelList::skyHide(cocos2d::Node* node)
{
	if (node) {
		auto layer = node->getChildByName("ChannelList");
		if (layer)
			layer->setVisible(false);
	}
}

void ChannelList::skyRefresh()
{

}

cocos2d::Layer* ChannelList::creatLayer(Node* node)
{
	if (node) {
		Layer* channellist = (Layer*)node->getChildByName("ChannelList");
		if (channellist) {
			return channellist;
		}
		else {
			log("ChannelList:ceart");
			auto pchannellist = ChannelList::create();
			node->addChild(pchannellist);
			return pchannellist;
		}
	}
	return nullptr;
}



Scene* ChannelList::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChannelList::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChannelList::init()
{
       //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //this->is_focus_triggered = false;    		
	initChannelList();
	return true;
}

void ChannelList::initChannelList()
{
	this->removeAllChildrenWithCleanup(true);	
	// Create the page view
	Size size(700, 1080);
	ui::PageView* pageView = ui::PageView::create();
	pageView->setDirection(ui::PageView::Direction::HORIZONTAL);
	pageView->setContentSize(size);
	pageView->removeAllItems();
	pageView->setIndicatorEnabled(true);
	pageView->setIndicatorSelectedIndexColor(Color3B(144, 144, 144));
	pageView->setIndicatorSpaceBetweenIndexNodes(10);
	pageView->setIndicatorPosition(Vec2(350, 960));
	
	
	ElementDisplayListSystem *edls = new (std::nothrow) ElementDisplayListSystem();
	if (edls && edls->init())
	{
		edls->autorelease();
	}
	
	this->addChild(edls, 0, "ElementDisplayListSystem");

	int pageCount = CHLIST_PAGECOUNT;
	for (int i = 0; i < pageCount; ++i)
	{
		ui::Layout* layout = ui::Layout::create();
		layout->setContentSize(size);
		int width = layout->getContentSize().width;
		int height = layout->getContentSize().height;

		ui::ImageView* imageView = ui::ImageView::create("channellist/channellist_bg.png");
		imageView->setPosition(Vec2(width / 2.0f, height / 2.0f));
		layout->addChild(imageView);
		
		
		ui::ImageView* imageView1 = ui::ImageView::create("channellist/channellist_bar_up.png");
		imageView1->setAnchorPoint(Vec2(0, 0));
		imageView1->setPosition(Vec2(0, 922));
		layout->addChild(imageView1);
		
		imageView1 = ui::ImageView::create("channellist/channellist_turnup.png");
		imageView1->setAnchorPoint(Vec2(0, 0));
		imageView1->setPosition(Vec2(340, 932));
		imageView1->setVisible(false);
		layout->addChild(imageView1,1,"channellist_turnup");

		ui::ImageView* imageView2 = ui::ImageView::create("channellist/channellist_bar_down.png");
		imageView2->setAnchorPoint(Vec2(0, 0));
		imageView2->setPosition(Vec2(0, 76));
		layout->addChild(imageView2);
		
		imageView2 = ui::ImageView::create("channellist/channellist_turndown.png");
		imageView2->setAnchorPoint(Vec2(0, 0));
		imageView2->setPosition(Vec2(340, 85));
		imageView2->setVisible(false);
		layout->addChild(imageView2,1,"channellist_turndown");
		

//			for(int j=1;j<6;j++)
//			{
//				imageView = ui::ImageView::create("channellist/channellist_line_px2.png");
//				//imageView->setScale9Enabled(true);
//				imageView->setAnchorPoint(Vec2(0, 0));
//				imageView->setPosition(Vec2(0, 106+136*j));
//				layout->addChild(imageView);
//			}						
		
		//ui::ImageView* imageView0 = ui::ImageView::create("channellist/channellist_list_focus_extend.png");
		ui::ImageView* imageView0 = ui::ImageView::create("channellist/channellist_list_focus.png");
		imageView0->setScale9Enabled(true);	
		imageView0->setContentSize(Size(700,235));
		imageView0->setAnchorPoint(Vec2::ZERO);
		imageView0->setPosition(Vec2(0, FOCUS_IMG_POS));
		imageView0->setVisible(false);
		layout->addChild(imageView0,0,CHLIST_FOCUS_IMG_TAG);


		ui::ImageView* imageView3 = ui::ImageView::create("channellist/channellist_selecttitle.png");
		imageView3->setAnchorPoint(Vec2::ZERO);
		imageView3->setPosition(Vec2(29, 25));
		layout->addChild(imageView3);

		ui::ImageView* imageView4 = ui::ImageView::create("channellist/channellist_selectchannel.png");
		imageView4->setAnchorPoint(Vec2::ZERO);
		imageView4->setPosition(Vec2(246, 25));
		layout->addChild(imageView4);


		ui::Text* label1 = ui::Text::create("Change Title", "general/SourceHanSansTWHK-Light.ttf", 26);
		label1->setAnchorPoint(Vec2::ZERO);
		label1->setColor(Color3B(91, 91, 91));
		label1->setPosition(Vec2(73, 15));			
		layout->addChild(label1);

		ui::Text* label2 = ui::Text::create("Select Channel", "general/SourceHanSansTWHK-Light.ttf", 26);
		label2->setAnchorPoint(Vec2::ZERO);
		label2->setColor(Color3B(91, 91, 91));
		label2->setPosition(Vec2(278, 15));
		layout->addChild(label2);


		if (i == 0)//Recorded
		{
			ui::Text* label1 = ui::Text::create("Recorded", "general/SourceHanSansTWHK-Light.ttf", 33);
			label1->setTextHorizontalAlignment(TextHAlignment::CENTER);
			label1->setColor(Color3B(91, 91, 91));
			label1->setPosition(Vec2(350, 1015));			
			layout->addChild(label1);							
			
			//ui::Text* label2 = ui::Text::create("Schedule\nRecording", "SourceHanSansTWHK-Light.ttf", 33);
			//label2->setTextHorizontalAlignment(TextHAlignment::RIGHT);
			auto label2 = Label::createWithTTF("Schedule\nRecording", "general/SourceHanSansTWHK-Light.ttf", 33);
			label2->setColor(Color3B(91, 91, 91));
			label2->setLineHeight(40);
			label2->setAlignment(TextHAlignment::RIGHT);
			label2->setPosition(Vec2(560/*610*/, 1015));			
			layout->addChild(label2);

			ui::ImageView* imageView = ui::ImageView::create("channellist/channellist_turnright.png");
			imageView->setPosition(Vec2(670, 1015));
			layout->addChild(imageView);

		}
		if (i>0 && i<pageCount-1)
		{

			ui::ImageView* imageView = ui::ImageView::create("channellist/channellist_turnright.png");
			imageView->setPosition(Vec2(670, 1015));
			layout->addChild(imageView);

			ui::ImageView* imageView1 = ui::ImageView::create("channellist/channellist_turnleft.png");
			imageView1->setPosition(Vec2(30, 1015));
			layout->addChild(imageView1);


		if (i == CHLIST_PAGEVIEW_SCH_RECORDING)//Schedule Recording
		{
			ui::Text* label1 = ui::Text::create("Recorded", "general/SourceHanSansTWHK-Light.ttf", 33);
			label1->setTextHorizontalAlignment(TextHAlignment::LEFT);
			label1->setColor(Color3B(91, 91, 91));
			label1->setPosition(Vec2(135/*110*/, 1015));
			
			layout->addChild(label1);				
			
			//ui::Text* label2 = ui::Text::create("Schedule\nRecording", "SourceHanSansTWHK-Light.ttf", 33);
			//label2->setTextHorizontalAlignment(TextHAlignment::LEFT);
			auto label2 = Label::createWithTTF("Schedule\nRecording", "general/SourceHanSansTWHK-Light.ttf", 33);
			label2->setColor(Color3B(91, 91, 91));
			label2->setLineHeight(40);
			label2->setAlignment(TextHAlignment::CENTER);
			label2->setPosition(Vec2(350, 1015));
			
			layout->addChild(label2);

			ui::Text* label3 = ui::Text::create("All", "general/SourceHanSansTWHK-Light.ttf", 33);
			label3->setTextHorizontalAlignment(TextHAlignment::RIGHT);
			label3->setColor(Color3B(91, 91, 91));
			label3->setPosition(Vec2(625/*610*/, 1015));
			
			layout->addChild(label3);
		}
		if (i == CHLIST_PAGEVIEW_ALL)//All
		{
//				ui::Text* label1 = ui::Text::create("Schedule\nRecording", "SourceHanSansTWHK-Light.ttf", 33);
//				label1->setTextHorizontalAlignment(TextHAlignment::LEFT);
			auto label1 = Label::createWithTTF("Schedule\nRecording", "general/SourceHanSansTWHK-Light.ttf", 33);
			label1->setColor(Color3B(91, 91, 91));
			label1->setLineHeight(40);
			label1->setAlignment(TextHAlignment::LEFT);
			label1->setPosition(Vec2(135/*110*/, 1015));
			
			layout->addChild(label1);

			ui::Text* label2 = ui::Text::create("All", "general/SourceHanSansTWHK-Light.ttf", 33);
			label2->setTextHorizontalAlignment(TextHAlignment::CENTER);
			label2->setColor(Color3B(91, 91, 91));
			label2->setPosition(Vec2(350, 1015));
			
			layout->addChild(label2);

//				ui::Text* label3 = ui::Text::create("Schedule\nViewing", "SourceHanSansTWHK-Light.ttf", 33);
//				label3->setTextHorizontalAlignment(TextHAlignment::RIGHT);
			auto label3 = Label::createWithTTF("Schedule\nViewing", "general/SourceHanSansTWHK-Light.ttf", 33);
			label3->setColor(Color3B(91, 91, 91));
			label3->setLineHeight(40);
			label3->setAlignment(TextHAlignment::RIGHT);
			label3->setPosition(Vec2(560/*610*/, 1015));
			
			layout->addChild(label3);
			


			addChannelList(layout,i);
		
				

		}
		if (i == CHLIST_PAGEVIEW_SCH_VIEWING)//Schedule Viewing
		{
			ui::Text* label1 = ui::Text::create("All", "general/SourceHanSansTWHK-Light.ttf", 33);
			label1->setTextHorizontalAlignment(TextHAlignment::LEFT);
			label1->setColor(Color3B(91, 91, 91));
			label1->setPosition(Vec2(80/*110*/, 1015));
			
			layout->addChild(label1);

//				ui::Text* label2 = ui::Text::create("Schedule\nViewing", "SourceHanSansTWHK-Light.ttf", 33);
//				label2->setTextHorizontalAlignment(TextHAlignment::LEFT);
			auto label2 = Label::createWithTTF("Schedule\nViewing", "general/SourceHanSansTWHK-Light.ttf", 33);
			label2->setColor(Color3B(91, 91, 91));
			label2->setLineHeight(40);
			label2->setAlignment(TextHAlignment::CENTER);
			label2->setPosition(Vec2(350, 1015));
			
			layout->addChild(label2);

			ui::Text* label3 = ui::Text::create("Favourites", "general/SourceHanSansTWHK-Light.ttf", 33);
			label3->setTextHorizontalAlignment(TextHAlignment::RIGHT);
			label3->setColor(Color3B(91, 91, 91));
			label3->setPosition(Vec2(560/*610*/, 1015));
			
			layout->addChild(label3);
		}
	}
		if (i == CHLIST_PAGEVIEW_FAVOURITE)//Favourites
		{
			ui::ImageView* imageView = ui::ImageView::create("channellist/channellist_turnleft.png");
			imageView->setPosition(Vec2(30, 1015));
			layout->addChild(imageView);

//				ui::Text* label1 = ui::Text::create("Schedule\nViewing", "SourceHanSansTWHK-Light.ttf", 33);
//				label1->setTextHorizontalAlignment(TextHAlignment::LEFT);
			auto label1 = Label::createWithTTF("Schedule\nViewing", "general/SourceHanSansTWHK-Light.ttf", 33);
			label1->setColor(Color3B(91, 91, 91));
			label1->setLineHeight(40);
			label1->setAlignment(TextHAlignment::LEFT);
			label1->setPosition(Vec2(135/*110*/, 1015));
			
			layout->addChild(label1);

			ui::Text* label2 = ui::Text::create("Favourites", "general/SourceHanSansTWHK-Light.ttf", 33);
			label2->setTextHorizontalAlignment(TextHAlignment::CENTER);
			label2->setColor(Color3B(91, 91, 91));
			label2->setPosition(Vec2(350, 1015));
			
			layout->addChild(label2);
		}
					
		
		pageView->insertCustomItem(layout, i);
	}

	pageView->setCurrentPageIndex(CHLIST_PAGEVIEW_ALL);
	addChild(pageView,0,CHLIST_PAGEVIEW_TAG);		
	
	if(edls->validChannelCount()>0)
	{
		//将开机前保存的最后看的频道放在列表最上面，并焦点
		ui::Widget *widget = pageView->getItem(CHLIST_PAGEVIEW_ALL);//layout
	    Node *node = widget->getChildByTag(CHLIST_CHLIST_TAG+CHLIST_PAGEVIEW_ALL);
	    ChannelListPageView *clpv = static_cast<ChannelListPageView*>(node);
	    node = widget->getChildByTag(CHLIST_FOCUS_IMG_TAG);
	    ui::ImageView *img = static_cast<ui::ImageView*>(node);
		node = clpv->getChildByTag(CHLIST_TAB_TAG + CHLIST_PAGEVIEW_ALL);
		ChannelListTableView *table = static_cast<ChannelListTableView*>(node);	
					
	    clpv->cur_idx = Get_TvPlayer()->getLastChannelIndex();;
	    clpv->is_focus_triggered = true;
		img->setVisible(true);
		clpv->y_position = FOCUS_IMG_POS;    
		img->setPosition(Vec2(0, clpv->y_position));	
		table->scrollToIndex(clpv->cur_idx+CHLIST_ITEM_NUM-1);//6 cell visible
	}
	
    addKeyListener(CC_CALLBACK_2(ChannelList::onKeyPressed_PageView, this), pageView);

	    
}

void ChannelList::onKeyPressed_PageView(EventKeyboard::KeyCode keyCode, Event* event)
{
    stopPropagation(keyCode, event, false);    
    Node *node = this->getChildByTag(CHLIST_PAGEVIEW_TAG);
	ui::PageView* pageView = static_cast<ui::PageView*>(node);
    ssize_t curindex = pageView->getCurrentPageIndex();
    
    ui::Widget *widget = pageView->getItem(curindex);//layout
    node = widget->getChildByTag(CHLIST_CHLIST_TAG+curindex);
    ChannelListPageView *clpv = static_cast<ChannelListPageView*>(node);
    node = widget->getChildByTag(CHLIST_FOCUS_IMG_TAG);
    ui::ImageView *img = static_cast<ui::ImageView*>(node);
    
    switch(keyCode)
	{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_LEFT:	
	    //if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{			
			if(curindex>0)
			{
				if(clpv)
				{
					img->setVisible(false);
									
					node = clpv->getChildByTag(CHLIST_TAB_TAG+curindex);
					TableView *table = static_cast<TableView*>(node);
			    	widget->removeChildByTag(CHLIST_CHLIST_TAG+curindex,true);
	//		    	clpv->onExit();
	//		    	clpv->release();
			    	
			    }			
				widget = pageView->getItem(curindex-1);		
				ui::Layout* layout = static_cast<ui::Layout*>(widget);
				
//M by frank for channel favorite.
#if 0
				if((curindex - 1) == CHLIST_PAGEVIEW_FAVOURITE)
				{
					
					ChannelListPageView* ChannelListPageViewScene;
					ChannelListPageViewScene = new (std::nothrow) ChannelListPageViewFavorite();
					this->addChannelList(layout, ChannelListPageViewScene, curindex - 1);
				}else	
					this->addChannelList(layout,curindex - 1);
#else
				if((curindex - 1) == CHLIST_PAGEVIEW_RECORDED)
					this->addChannelList(layout,new (std::nothrow) ChannelListPageRecorded(),curindex - 1);
				if((curindex - 1) == CHLIST_PAGEVIEW_SCH_RECORDING)
					this->addChannelList(layout,new (std::nothrow) ChannelListPageSchRecording(),curindex - 1);
				if((curindex - 1) == CHLIST_PAGEVIEW_ALL)
					this->addChannelList(layout,curindex - 1);	
				if((curindex - 1) == CHLIST_PAGEVIEW_SCH_VIEWING)
					this->addChannelList(layout,new (std::nothrow) ChannelListPageSchViewing(),curindex - 1);
				if((curindex - 1) == CHLIST_PAGEVIEW_FAVOURITE)
					this->addChannelList(layout,new (std::nothrow) ChannelListPageViewFavorite(),curindex - 1);
#endif			
				pageView->setCurrentPageIndex(curindex - 1);
			}
			break;
		}
	
	    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	    case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
	    //if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	    {		
			if(curindex<CHLIST_PAGECOUNT-1)
	    	{
				if(clpv)
				{
					img->setVisible(false);	
					
					node = clpv->getChildByTag(CHLIST_TAB_TAG+curindex);
					TableView *table = static_cast<TableView*>(node);
			    	widget->removeChildByTag(CHLIST_CHLIST_TAG+curindex,true);
		    				
			    }
	    	    widget = pageView->getItem(curindex+1);				
				ui::Layout* layout = static_cast<ui::Layout*>(widget);
#if 0
//M by frank for channel favorite.
				if ((curindex + 1) == CHLIST_PAGEVIEW_FAVOURITE)
				{

					ChannelListPageView* ChannelListPageViewScene;
					ChannelListPageViewScene = new (std::nothrow) ChannelListPageViewFavorite();
					this->addChannelList(layout, ChannelListPageViewScene, curindex + 1);
				}
				else
					this->addChannelList(layout, curindex + 1);
#else
				if((curindex + 1) == CHLIST_PAGEVIEW_RECORDED)
					this->addChannelList(layout,new (std::nothrow) ChannelListPageRecorded(),curindex + 1);
				if((curindex + 1) == CHLIST_PAGEVIEW_SCH_RECORDING)
					this->addChannelList(layout,new (std::nothrow) ChannelListPageSchRecording(),curindex + 1);
				if((curindex + 1) == CHLIST_PAGEVIEW_ALL)
					this->addChannelList(layout,curindex + 1);	
				if((curindex + 1) == CHLIST_PAGEVIEW_SCH_VIEWING)
					this->addChannelList(layout,new (std::nothrow) ChannelListPageSchViewing(),curindex + 1);
				if((curindex + 1) == CHLIST_PAGEVIEW_FAVOURITE)
					this->addChannelList(layout,new (std::nothrow) ChannelListPageViewFavorite(),curindex + 1);
#endif
	    		pageView->setCurrentPageIndex(curindex + 1);
	    	}
	    	
	    	break;
	    }
	    case EventKeyboard::KeyCode::KEY_UP_ARROW:
	    case EventKeyboard::KeyCode::KEY_DPAD_UP:
	    //if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			if(!clpv)
				break;
			
			node = clpv->getChildByTag(CHLIST_TAB_TAG+curindex);
			ChannelListTableView *table = static_cast<ChannelListTableView*>(node);		
			
			ssize_t total_num = clpv->numberOfCellsInTableView(table);
				
			if (clpv->is_focus_triggered)
			{
				if(clpv->cur_idx>0)
					clpv->cur_idx--;			
				
				if(clpv->y_position + 136 >FOCUS_IMG_POS)////need scroll to last cell
				{
					if(clpv->cur_idx==0 && total_num <= CHLIST_ITEM_NUM)
						break;
					
					if(clpv->cur_idx>=0)
						table->scrollToIndex(clpv->cur_idx+CHLIST_ITEM_NUM-1);//6 cell visible
						
				}
				else
				{
					clpv->y_position += 136;
					if(clpv->y_position<=FOCUS_IMG_POS&&clpv->y_position>0)
					{
						img->setVisible(false);			
						img->setPosition(Vec2(0, clpv->y_position));
						img->setVisible(true);
						
					}
				}
				
				//决定是否有上下箭头
				ui::Layout* layout = static_cast<ui::Layout*>(widget);
				Node *node1 = layout->getChildByName("channellist_turndown");
				ui::ImageView* img1 = static_cast<ui::ImageView*>(node1);
				Node *node2 = layout->getChildByName("channellist_turnup");
				ui::ImageView* img2 = static_cast<ui::ImageView*>(node2);
				if(clpv->cur_idx == 0)
				{				
					img2->setVisible(false);
				}
				else
				{
					img2->setVisible(true);
				}
				ssize_t total_num = clpv->numberOfCellsInTableView(table);
				if(clpv->cur_idx <total_num-CHLIST_ITEM_NUM)
					img1->setVisible(true);
				
			}
			break;	
		}
	
	    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	    case EventKeyboard::KeyCode::KEY_DPAD_DOWN:
	    //if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	    { 
	    	if(!clpv)
				break;
				
			node = clpv->getChildByTag(CHLIST_TAB_TAG+curindex);
			ChannelListTableView *table = static_cast<ChannelListTableView*>(node);
			
			ssize_t total_num = clpv->numberOfCellsInTableView(table);
			ssize_t offset_margin = 0;

			if(total_num == 0)
				break;
			
			if(total_num < CHLIST_ITEM_NUM)
			{
				offset_margin = 136 * (CHLIST_ITEM_NUM - total_num);
			}
			
			if (!clpv->is_focus_triggered)
			{
				clpv->is_focus_triggered = true;
				img->setVisible(true);
				clpv->y_position = FOCUS_IMG_POS;    
				clpv->cur_idx = 0;
				img->setPosition(Vec2(0, clpv->y_position));		
	    	}
	    	else
			{
				total_num = clpv->numberOfCellsInTableView(table);
				if(clpv->cur_idx<total_num-1)
					clpv->cur_idx++;
				if(clpv->y_position - 136 < offset_margin )//need scroll to next cell
				{
					
					if(clpv->cur_idx<total_num)
						table->scrollToIndex(clpv->cur_idx);
				}
				else
				{
				
					clpv->y_position -= 136;
					if(clpv->y_position<=FOCUS_IMG_POS&&clpv->y_position>0)
					{
						img->setVisible(false);			
						img->setPosition(Vec2(0, clpv->y_position));
						img->setVisible(true);					
						
					}
				}
				
				//决定是否有上下箭头
				ui::Layout* layout = static_cast<ui::Layout*>(widget);
				Node *node1 = layout->getChildByName("channellist_turndown");
				ui::ImageView* img1 = static_cast<ui::ImageView*>(node1);
				Node *node2 = layout->getChildByName("channellist_turnup");
				ui::ImageView* img2 = static_cast<ui::ImageView*>(node2);
				if(total_num>CHLIST_ITEM_NUM)
				{
					if(clpv->cur_idx == total_num-1)
					{
						img1->setVisible(false);
					}
					else
					{
						img1->setVisible(true);
					}
					
					if(clpv->cur_idx >CHLIST_ITEM_NUM-1)
						img2->setVisible(true);
					
					
				}
				else
				{
					img1->setVisible(false);
					img2->setVisible(false);
				}
				
				
				
				
				
			}
			break;    	
	    }
	    case EventKeyboard::KeyCode::KEY_ENTER:
	    case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
	    //if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			if(!clpv)
				break;
			node = clpv->getChildByTag(CHLIST_TAB_TAG+curindex);
			ChannelListTableView *table = static_cast<ChannelListTableView*>(node);
			
			if (clpv->is_focus_triggered)
			{
				if(curindex == CHLIST_PAGEVIEW_RECORDED)//Recorded:index 0
				{			
		
						//Todo:根据是否录制成功决定调play/del还是del弹出框
						//if(table->)
#ifdef USE_PVR_RECORD_DB	
		std::vector<PVRRecordInfo> pvrlist;
		log("ChannelList:getPvrRecords in");
		PVRRecordDB::getInstance()->getPvrRecords(pvrlist);	
		log("ChannelList:getPvrRecords out size %d",pvrlist.size());
		if(pvrlist.size()>0)
		{
			if(pvrlist[clpv->cur_idx].mState == RECORD_STATE_COMPLETED)
			{
				addInfoPanel(CHLIST_RECORDED_PLAY,CHLIST_PAGEVIEW_RECORDED,clpv->cur_idx);
			}
			if(pvrlist[clpv->cur_idx].mState == RECORD_STATE_FAILED)
			{
				addInfoPanel(CHLIST_RECORDED_DEL,CHLIST_PAGEVIEW_RECORDED,clpv->cur_idx);
			}
		}
			
#else							
					addInfoPanel(CHLIST_RECORDED_PLAY,CHLIST_PAGEVIEW_RECORDED,clpv->cur_idx);
						//addInfoPanel(CHLIST_RECORDED_DEL,CHLIST_PAGEVIEW_RECORDED,clpv->cur_idx);
#endif						
					
				}	
				
				if(curindex == CHLIST_PAGEVIEW_SCH_RECORDING)//Schedule Recording:index 1
				{
					addInfoPanel(CHLIST_SCH_REC_CANCEL,CHLIST_PAGEVIEW_SCH_RECORDING,clpv->cur_idx);
				}
				
				if(curindex == CHLIST_PAGEVIEW_ALL||curindex == CHLIST_PAGEVIEW_FAVOURITE)//All,Favourites
				{
					Node *node = this->getChildByName("ElementDisplayListSystem");
					ElementDisplayListSystem *edls = static_cast<ElementDisplayListSystem*>(node);
					
					if(edls->getLockAttr(clpv->cur_idx))
					//Todo,若锁定，则pin码校验
						addInfoPanel(CHLIST_ENTER_PIN,curindex,clpv->cur_idx);
					
					
					
					//Todo,play,电视播放
					edls->play(clpv->cur_idx);
					
					
					
					
				}
				if(curindex == CHLIST_PAGEVIEW_SCH_VIEWING)//Schedule Viewing:index 3
				{
					addInfoPanel(CHLIST_SCH_VIEWING_CANCEL,CHLIST_PAGEVIEW_SCH_VIEWING,clpv->cur_idx);
				}
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:
		{
			//if (!clpv->is_focus_triggered)
			{
				if (1) {
				this->removeAllChildren();
				if (this->getParent()) {
					this->getParent()->removeChild(this);
				}
			}
			}	
			break;
		}
		default:
			break;
	    
	}
    
}

void ChannelList::addChannelList(ui::Layout* layout, ssize_t index)
{	
	Node *node = this->getChildByName("ElementDisplayListSystem");
	ElementDisplayListSystem *edls = static_cast<ElementDisplayListSystem*>(node);
	if(edls->validChannelCount()>0)
	{
		ChannelListPageView* clpv;
		clpv = new (std::nothrow) ChannelListPageView();
		if (clpv && clpv->init(edls,index,true))
		{
			clpv->autorelease();					
		}
		clpv->is_focus_triggered = false;
		layout->addChild(clpv, 1, CHLIST_CHLIST_TAG + index);
		
		Node *node = clpv->getChildByTag(CHLIST_TAB_TAG + index);
		ChannelListTableView *table = static_cast<ChannelListTableView*>(node);
		
		//Todo:根据频道总数决定是否显示下翻箭头，默认从条目0开始显示，故先没有上翻箭头
		if(clpv->numberOfCellsInTableView(table)>CHLIST_ITEM_NUM)
		{
			Node *node = layout->getChildByName("channellist_turndown");
			ui::ImageView* img = static_cast<ui::ImageView*>(node);
			img->setVisible(true);
		}
			
		//将开机前保存的最后看的频道放在列表最上面，并焦点
		if(index == CHLIST_PAGEVIEW_ALL)
		{
		    Node *node = layout->getChildByTag(CHLIST_FOCUS_IMG_TAG);
		    ui::ImageView *img = static_cast<ui::ImageView*>(node);
		    clpv->cur_idx = Get_TvPlayer()->getLastChannelIndex();;
		    clpv->is_focus_triggered = true;
			img->setVisible(true);
			clpv->y_position = FOCUS_IMG_POS;    
			img->setPosition(Vec2(0, clpv->y_position));	
			table->scrollToIndex(clpv->cur_idx+CHLIST_ITEM_NUM-1);//6 cell visible		
		}	
	}
}
//add base element

//M by frank for channel favorite.
void ChannelList::addChannelList(ui::Layout* layout, ChannelListPageView* ChannelListPageViewScene ,ssize_t index)
{
	Node *node = this->getChildByName("ElementDisplayListSystem");
	ElementDisplayListSystem *edls = static_cast<ElementDisplayListSystem*>(node);

	if (ChannelListPageViewScene && ChannelListPageViewScene->init(edls,index,true))
	{
		ChannelListPageViewScene->autorelease();					
	}
	ChannelListPageViewScene->is_focus_triggered = false;
	ChannelListPageViewScene->play_or_del = true;//default
	layout->addChild(ChannelListPageViewScene, 1, CHLIST_CHLIST_TAG + index);
	
	node = ChannelListPageViewScene->getChildByTag(CHLIST_TAB_TAG + index);
	ChannelListTableView *table = static_cast<ChannelListTableView*>(node);
	
	//Todo:根据频道总数决定是否显示下翻箭头，默认从条目0开始显示，故先没有上翻箭头
	if(table)
	if(ChannelListPageViewScene->numberOfCellsInTableView(table)>CHLIST_ITEM_NUM)
	{
		Node *node = layout->getChildByName("channellist_turndown");
		ui::ImageView* img = static_cast<ui::ImageView*>(node);
		img->setVisible(true);
	}	
			
}
//add base element

void ChannelList::addInfoPanel(int type_index,int cur_page_index,int tableindex)
{
	//Recorded ok
	//info background
	std::string infopanelstring = "Recorded ok";	
	Sprite* sprite;	

	if(type_index == CHLIST_ENTER_PIN)
	{
	
		cocos2d::Node* curNode = tvScene::getTvLayer();
		ChannelPin::creatLayer(curNode);		

	}
	else
	{
		sprite = Sprite::create("general/general_popup_bg.png", Rect(410, 124, 1100, 744));
	    //sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setPosition(Vec2(960, 496));
		
		ui::ImageView* imageView = ui::ImageView::create("info/info_popup_bg.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(1267,911));
		//imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(560, 355));
		sprite->addChild(imageView);
		
		
		//line 3hori,1vert
		imageView = ui::ImageView::create("general/general_listline.png");
			//imageView = ui::ImageView::create("channellist/channellist_line_px2.png");
		imageView->setScale9Enabled(true);
		imageView->setContentSize(Size(1100,1));
		imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(0, 639));
		sprite->addChild(imageView);
		
		
		imageView = ui::ImageView::create("general/general_listline.png");
			//imageView = ui::ImageView::create("channellist/channellist_line_px2.png");
		imageView->setScale9Enabled(true);
		imageView->setContentSize(Size(1100,1));
		imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(0, 434));
		sprite->addChild(imageView);
		
		imageView = ui::ImageView::create("general/general_listline.png");
			//imageView = ui::ImageView::create("channellist/channellist_line_px2.png");
		imageView->setScale9Enabled(true);
		imageView->setContentSize(Size(1100,1));
		imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(0, 361));
		sprite->addChild(imageView);
		
		//imageView = ui::ImageView::create("channellist/channellist_line_updown2px.png");
		imageView = ui::ImageView::create("general/general_listline.png");		
		imageView->setScale9Enabled(true);
		imageView->setContentSize(Size(2,150));
		imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(160, 460));
		sprite->addChild(imageView);
		
		//text/label 7	
		auto label = Label::createWithTTF("information", "general/SourceHanSansTWHK-Light.ttf", 33);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(51, 51, 51));	
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(440, 663));
		sprite->addChild(label);
		
		std::string channelNumber;
		std::string channelName;
		std::string programName;
		unsigned int u32Seconds_start;
		unsigned int u32Seconds_end;
		std::vector<EpgSchedule> schedules;	
		int cellnum;	
			
		if(type_index == CHLIST_RECORDED_PLAY||type_index == CHLIST_RECORDED_DEL)
		{
			
			CCPvrFileInfo info;
			CCPvrManager *pPvrManager = CCPvrManager::getInstance();
			pPvrManager->getPvrFileInfo(tableindex, info);
			pPvrManager->getFileServiceName(info.filename,channelName);
			pPvrManager->getFileEventName(info.filename,programName); 
			
			channelNumber = StringUtils::format("%ld", tableindex);
			
			
			u32Seconds_start = info.recordStartTime;
			int Duration =  pPvrManager->getRecordedFileDurationTime(info.filename);
			u32Seconds_end = info.recordStartTime + Duration;
			
			cellnum = pPvrManager->getPvrFileNumber();
			
		}
		if(type_index == CHLIST_SCH_REC_CANCEL)
		{			
			CScheduleManager::getInstance()->getScheduleRec(schedules);
			channelNumber = StringUtils::format("%ld", tableindex);
			channelName = schedules[tableindex].chName;
			programName = schedules[tableindex].event.eventName;
			
			u32Seconds_start = schedules[tableindex].event.startTime;			
			u32Seconds_end = schedules[tableindex].event.endTime;
			cellnum = schedules.size();
			
		}
		if(type_index == CHLIST_SCH_VIEWING_CANCEL)
		{			
			CScheduleManager::getInstance()->getScheduleView(schedules);
			channelNumber = StringUtils::format("%ld", tableindex);
			channelName = schedules[tableindex].chName;
			programName = schedules[tableindex].event.eventName;
			
			u32Seconds_start = schedules[tableindex].event.startTime;			
			u32Seconds_end = schedules[tableindex].event.endTime;
			cellnum = schedules.size();
		}
		
		{			
			auto label = Label::createWithTTF("", "general/SourceHanSansTWHK-Light.ttf", 28);
			label->setTextColor(Color4B(153, 153, 153, 255));	
			label->setPosition(Vec2(600, 524));	
			
			SkyTvTimeString strTime;
			if (cellnum > 0) 
			{
				CTime::seconds2TimeString(u32Seconds_start, strTime);
				std::string presentTime = "(";
				presentTime += strTime.strHour;
				presentTime += ":";
				presentTime += strTime.strMinute;
				presentTime += " - ";
				CTime::seconds2TimeString(u32Seconds_end, strTime);				
				presentTime += strTime.strHour;
				presentTime += ":";
				presentTime += strTime.strMinute;
				presentTime += ")";
				// presentTime.append(" -- ", strTime.strMinute)
				// printf("\n############### presentTime:%s ############\n", presentTime.c_str());
				label->setString(presentTime.c_str());			
			}		
			sprite->addChild(label);			
		}
		
		
		
				
		
		label = Label::createWithTTF(channelNumber, "general/SourceHanSansTWHK-Light.ttf", 45);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(51, 51, 51));
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(48, 500));
		sprite->addChild(label);
		
		label = Label::createWithTTF(channelName, "general/SourceHanSansTWHK-Light.ttf", 40);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(51, 51, 51));
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(180, 553));
		sprite->addChild(label);
		Size ch_size = label->getContentSize();
		
		label = Label::createWithTTF(programName, "general/SourceHanSansTWHK-Light.ttf", 33);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(91, 91, 91));
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(180, 500));
		sprite->addChild(label);
		
		label = Label::createWithTTF("Source", "general/SourceHanSansTWHK-Light.ttf", 33);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(91, 91, 91));
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(180, 451));
		sprite->addChild(label);
		
		label = Label::createWithTTF("Unclassified", "general/SourceHanSansTWHK-Light.ttf", 30);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(91, 91, 91));
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(48, 369));
		sprite->addChild(label);
		
		label = Label::createWithTTF("Monitoring and reflecting the pulse of our world press TV presents\nthe global audience with outstanding coverage of world events\nfollowed by sports news.", "general/SourceHanSansTWHK-Light.ttf", 30);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(91, 91, 91));
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(48, 216));
		sprite->addChild(label);		
			
#ifdef USE_PVR_RECORD_DB	
		std::vector<PVRRecordInfo> pvrlist;
		log("ChannelList:getPvrRecords in");
		PVRRecordDB::getInstance()->getPvrRecords(pvrlist);	
		log("ChannelList:getPvrRecords out size %d",pvrlist.size());
		if(pvrlist.size()>0
			&& pvrlist[tableindex].mState == RECORD_STATE_COMPLETED)
#else						
		//Todo:sprite 1,according to channel database	
		if(1)
#endif			
		{
			imageView = ui::ImageView::create("channellist/channellist_recordicon_succeed.png");
		}
		else
		{
			imageView = ui::ImageView::create("channellist/channellist_recordicon_failed.png");
		}
		
		
		
		imageView->setPosition(Vec2(180+ch_size.width+30, 587));
		sprite->addChild(imageView);		
		
		if(type_index == CHLIST_RECORDED_PLAY)
		{
			//recorded ok,button 2:play,delete;
			//infopanelstring = "Recorded ok";		
			ui::ImageView* imageView = ui::ImageView::create("general/general_button_normal.png");
			imageView->setScale9Enabled(true);
			imageView->setContentSize(Size(300,72));
			imageView->setAnchorPoint(Vec2(0, 0));
			imageView->setPosition(Vec2(221, 86));
			sprite->addChild(imageView);
			
			auto label = Label::createWithTTF("Play", "general/SourceHanSansTWHK-Light.ttf", 33);
			label->setAnchorPoint(Vec2(0, 0));
			label->setColor(Color3B(91, 91, 91));
			label->setAlignment(TextHAlignment::LEFT);
			label->setPosition(Vec2(337, 94));
			sprite->addChild(label);	
			label->setLocalZOrder(3);	
			
			imageView = ui::ImageView::create("general/general_button_focus.png");
			imageView->setScale9Enabled(true);	
			imageView->setContentSize(Size(360,120));
			imageView->setAnchorPoint(Vec2(0, 0));
			imageView->setPosition(Vec2(192, 44));			
			
			sprite->addChild(imageView,1,"general_button_focus");		
			
			imageView = ui::ImageView::create("general/general_button_normal.png");
			imageView->setScale9Enabled(true);
			imageView->setContentSize(Size(300,72));
			imageView->setAnchorPoint(Vec2(0, 0));
			imageView->setPosition(Vec2(580, 86));
			sprite->addChild(imageView);
			
			label = Label::createWithTTF("Delete", "general/SourceHanSansTWHK-Light.ttf", 33);
			label->setAnchorPoint(Vec2(0, 0));
			label->setColor(Color3B(91, 91, 91));
			label->setAlignment(TextHAlignment::LEFT);
			label->setPosition(Vec2(677, 94));
			sprite->addChild(label);
			label->setLocalZOrder(3);
			
			
		}
		if(type_index == CHLIST_RECORDED_DEL)
		{
			infopanelstring = "Recorded failed";
			//recorded failed,button 1:delete
			ui::ImageView* imageView = ui::ImageView::create("general/general_button_normal.png");
			imageView->setScale9Enabled(true);
			imageView->setContentSize(Size(300,72));
			imageView->setAnchorPoint(Vec2(0, 0));
			imageView->setPosition(Vec2(400, 86));
			sprite->addChild(imageView);
			
			auto label = Label::createWithTTF("Delete", "general/SourceHanSansTWHK-Light.ttf", 33);
			label->setAnchorPoint(Vec2(0, 0));
			label->setColor(Color3B(51, 51, 51));
			label->setAlignment(TextHAlignment::LEFT);
			label->setPosition(Vec2(500, 94));
			sprite->addChild(label);	
			label->setLocalZOrder(3);
			
			imageView = ui::ImageView::create("general/general_button_focus.png");
			imageView->setScale9Enabled(true);	
			imageView->setContentSize(Size(360,120));
			imageView->setAnchorPoint(Vec2(0, 0));
			imageView->setPosition(Vec2(371, 44));
			sprite->addChild(imageView);
			
			
		}
		if(type_index == CHLIST_SCH_REC_CANCEL||type_index == CHLIST_SCH_VIEWING_CANCEL)
		{
			infopanelstring = "Cancel Schedule Recoding";
			if(type_index == CHLIST_SCH_VIEWING_CANCEL)
			{
				//schedule viewing,button 1
				infopanelstring = "Cancel Schedule Viewing";
				
			}
			
				
			//schedule recording,button 1
			ui::ImageView* imageView = ui::ImageView::create("general/general_button_normal.png");
			imageView->setScale9Enabled(true);
			imageView->setContentSize(Size(518,72));
			imageView->setAnchorPoint(Vec2(0, 0));
			imageView->setPosition(Vec2(290, 86));
			sprite->addChild(imageView);
			
			auto label = Label::createWithTTF(infopanelstring, "general/SourceHanSansTWHK-Light.ttf", 33);
			label->setAnchorPoint(Vec2(0, 0));
			label->setColor(Color3B(51, 51, 51));
			label->setAlignment(TextHAlignment::LEFT);
			label->setPosition(Vec2(345, 94));
			sprite->addChild(label);	
			label->setLocalZOrder(3);
			
			
			imageView = ui::ImageView::create("general/general_button_focus.png");
			imageView->setScale9Enabled(true);	
			imageView->setContentSize(Size(578,120));
			imageView->setAnchorPoint(Vec2(0, 0));
			imageView->setPosition(Vec2(261, 44));
			sprite->addChild(imageView);
		}
		this->addChild(sprite,1,infopanelstring);
		addKeyListener(CC_CALLBACK_2(ChannelList::onKeyPressed_ChannelInfo, this), sprite);
	}	
	
	
	
}

static int KeyCode2int(cocos2d::EventKeyboard::KeyCode keyCode)
{
	int index = 0;
	 switch(keyCode)
	 {
	case EventKeyboard::KeyCode::KEY_0:
		index = 0;
		break;
	case EventKeyboard::KeyCode::KEY_1:
		index = 1;
		break;
	case EventKeyboard::KeyCode::KEY_2:
		index = 2;
		break;		
	case EventKeyboard::KeyCode::KEY_3:
		index = 3;
		break;
	case EventKeyboard::KeyCode::KEY_4:
		index = 4;
		break;
	case EventKeyboard::KeyCode::KEY_5:
		index = 5;
		break;
	case EventKeyboard::KeyCode::KEY_6:
		index = 6;
		break;
	case EventKeyboard::KeyCode::KEY_7:
		index = 7;
		break;
	case EventKeyboard::KeyCode::KEY_8:
		index = 8;
		break;
	case EventKeyboard::KeyCode::KEY_9:
		index = 9;
		break;
	default:
		break;
	}
	return index;
}

void ChannelList::onKeyPressed_ChannelInfo(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);
	Node *node = this->getChildByTag(CHLIST_PAGEVIEW_TAG);
	ui::PageView* pageView = static_cast<ui::PageView*>(node);
    ssize_t curindex = pageView->getCurrentPageIndex();
      
    ui::Widget *widget = pageView->getItem(curindex);//layout
    node = widget->getChildByTag(CHLIST_CHLIST_TAG+curindex);
    ChannelListPageView *clpv = static_cast<ChannelListPageView*>(node);
    
    	
	if(curindex == CHLIST_PAGEVIEW_RECORDED)//Recorded:index 0
	{
		//Todo:加是否录像成功的判断	
		Node *node = clpv->getChildByTag(CHLIST_TAB_TAG + 0);
    	if(node)
	    {
	    	TableView *table = static_cast<TableView*>(node);
	    	
#ifdef USE_PVR_RECORD_DB	
			std::vector<PVRRecordInfo> pvrlist;
			log("ChannelList:getPvrRecords in");
			PVRRecordDB::getInstance()->getPvrRecords(pvrlist);	
			log("ChannelList:getPvrRecords out size %d",pvrlist.size());
			if(pvrlist.size()>0
				&&pvrlist[clpv->cur_idx].mState == RECORD_STATE_COMPLETED)
#else	    	
			if(1)
#endif				
			{
				Node *node = this->getChildByName("Recorded ok");
				Sprite* sprite = static_cast<Sprite*>(node);
				ui::ImageView* img = (ui::ImageView* )sprite->getChildByName("general_button_focus");
				Vec2 position = img->getPosition();
		
				if (keyCode == EventKeyboard::KeyCode::KEY_ENTER
					||keyCode == EventKeyboard::KeyCode::KEY_DPAD_CENTER
					||keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE
					||keyCode == EventKeyboard::KeyCode::KEY_BACK
					||keyCode == EventKeyboard::KeyCode::KEY_TV_BACK
					||keyCode == EventKeyboard::KeyCode::KEY_TV_EXIT)
				{
					//Todo:调用播放或删除接口
					std::string mountpath;
					CCPvrManager *pPvrManager = CCPvrManager::getInstance();
					pPvrManager->getPvrMountPath(mountpath);
					mountpath +="/_MSTPVR/";
					log("ChannelList:mountpath %s\n",mountpath.c_str());
					
#ifdef USE_PVR_RECORD_DB	

					mountpath += pvrlist[clpv->cur_idx].mRecordName;					

#else					
					CCPvrFileInfo info;				
					pPvrManager->getPvrFileInfo(clpv->cur_idx,info);					
					mountpath += info.filename;		
					
#endif						
					log("ChannelList: play mountpath %s\n",mountpath.c_str());
					log("ChannelList:play_or_del %d",clpv->play_or_del);
					if (clpv->play_or_del)
					{
						//play,本地播放
						cocos2d::Node* curNode = tvScene::getTvLayer();
						LocalVideoPlayer*  player = (LocalVideoPlayer*)LocalVideoPlayer::creatLayer(curNode);
						//player->play(mountpath);
						player->play_pvr(pvrlist[clpv->cur_idx].mRecordName);
					}
					else
					{
						//delete
						//pPvrManager->deleteFile(0,info.filename);
#ifdef USE_PVR_RECORD_DB	
						log("ChannelList:deleteRecord in.CurRecordingFileName %s",pvrlist[clpv->cur_idx].mRecordName.c_str());	
						PVRRecordDB::getInstance()->deleteRecord(pvrlist[clpv->cur_idx].mRecordName.c_str());
#endif					log("ChannelList:deleteRecord out");		
					
						table->reloadData();
					
					}
					
					
					this->removeChildByName("Recorded ok");
				}
			
				if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW
					||keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT)
				{
					if(position.x == 192)
					{
						img->setVisible(false);			
						img->setPosition(Vec2(551,44));
						img->setVisible(true);
						clpv->play_or_del = false;
					}
					
				}	
				if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW
					||keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT)
				{
					if(position.x == 551)//551
					{
						img->setVisible(false);			
						img->setPosition(Vec2(192,44));
						img->setVisible(true);
						clpv->play_or_del = true;
					}
				}
				
			}
			else
			{
				this->getChildByName("Recorded failed");
				if (keyCode == EventKeyboard::KeyCode::KEY_ENTER
					||keyCode == EventKeyboard::KeyCode::KEY_DPAD_CENTER
					||keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE
					||keyCode == EventKeyboard::KeyCode::KEY_BACK
					||keyCode == EventKeyboard::KeyCode::KEY_TV_BACK
					||keyCode == EventKeyboard::KeyCode::KEY_TV_EXIT)
				{	
					//Todo:调用删除接口
					
#ifdef USE_PVR_RECORD_DB	

					log("ChannelList:deleteRecord in.CurRecordingFileName %s",pvrlist[clpv->cur_idx].mRecordName.c_str());	
					PVRRecordDB::getInstance()->deleteRecord(pvrlist[clpv->cur_idx].mRecordName.c_str());
					log("ChannelList:deleteRecord out");	
#endif
					table->reloadData();
					this->removeChildByName("Recorded failed");
				}
			}
		}
	
		
	}	
	if(curindex == CHLIST_PAGEVIEW_SCH_RECORDING)//Schedule Recording:index 1
	{
		Node *node = clpv->getChildByTag(CHLIST_TAB_TAG + 1);
    	if(node)
	    {
			TableView *table = static_cast<TableView*>(node);
	    	
			this->getChildByName("Cancel Schedule Recoding");
			if (keyCode == EventKeyboard::KeyCode::KEY_ENTER
				||keyCode == EventKeyboard::KeyCode::KEY_DPAD_CENTER
				||keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE
				||keyCode == EventKeyboard::KeyCode::KEY_BACK
				||keyCode == EventKeyboard::KeyCode::KEY_TV_BACK
				||keyCode == EventKeyboard::KeyCode::KEY_TV_EXIT)
			{
				//Todo：调用取消预约录制接口
				std::vector<EpgSchedule> schedules;	
				CScheduleManager::getInstance()->getScheduleRec(schedules);
				std::string channelNumber = StringUtils::format("%ld", clpv->cur_idx);
				std::string channelName = schedules[clpv->cur_idx].chName;
				std::string programName = schedules[clpv->cur_idx].event.eventName;			
			
				CScheduleManager::getInstance()->cancelScheduleRec(schedules[clpv->cur_idx]);				
				this->removeChildByName("Cancel Schedule Recoding");
				
				table->reloadData();
			}
		}
	}
	
	if(curindex == CHLIST_PAGEVIEW_SCH_VIEWING)//Schedule Viewing:index 3
	{
		Node *node = clpv->getChildByTag(CHLIST_TAB_TAG + 3);
    	if(node)
	    {
	    	TableView *table = static_cast<TableView*>(node);
			this->getChildByName("Cancel Schedule Viewing");
			if (keyCode == EventKeyboard::KeyCode::KEY_ENTER
				||keyCode == EventKeyboard::KeyCode::KEY_DPAD_CENTER
				||keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE
				||keyCode == EventKeyboard::KeyCode::KEY_BACK
				||keyCode == EventKeyboard::KeyCode::KEY_TV_BACK
				||keyCode == EventKeyboard::KeyCode::KEY_TV_EXIT)
			{
				//Todo：调用取消预约接口
				std::vector<EpgSchedule> schedules;	
				CScheduleManager::getInstance()->getScheduleView(schedules);
				std::string channelNumber = StringUtils::format("%ld", clpv->cur_idx);
				std::string channelName = schedules[clpv->cur_idx].chName;
				std::string programName = schedules[clpv->cur_idx].event.eventName;				
							
				CScheduleManager::getInstance()->cancelScheduleView(schedules[clpv->cur_idx]);
				this->removeChildByName("Cancel Schedule Viewing");
				
				table->reloadData();
			}
		}
	}

}






	