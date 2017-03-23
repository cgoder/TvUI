#include "ChannelEdit.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/UIPageView.h"
#include "ChannelList/ChannelListPage.h"
#include "common/ChannelPin.h"
#include "tvScene.h"
USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocostudio::timeline;

ChannelEdit::ChannelEdit()
{
	this->setName("ChannelEdit");
	log("ChannelEdit::ChannelEdit");
}

ChannelEdit::~ChannelEdit()
{
	
}


bool ChannelEdit::skyShow(cocos2d::Node* node)
{
	if (node) {
		auto layer = node->getChildByName("ChannelEdit");
		if (layer) {
			layer->setVisible(true);
		}			
		else {
			auto player = ChannelEdit::create();
			node->addChild(player);
			player->setVisible(true);
		}
		return true;
	}
	return false;
}
void ChannelEdit::skyHide(cocos2d::Node* node)
{
	if (node) {
		auto layer = node->getChildByName("ChannelEdit");
		if (layer)
			layer->setVisible(false);
	}
}

void ChannelEdit::skyRefresh()
{

}

cocos2d::Layer* ChannelEdit::creatLayer(Node* node)
{
	if (node) {
		Layer* ChannelEdit = (Layer*)node->getChildByName("ChannelEdit");
		if (ChannelEdit) {
			return ChannelEdit;
		}
		else {
			log("ChannelEdit:ceart");
			auto pChannelEdit = ChannelEdit::create();
			node->addChild(pChannelEdit);
			return pChannelEdit;
		}
	}
	return nullptr;
}



Scene* ChannelEdit::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChannelEdit::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChannelEdit::init()
{
	log("ChannelEdit::init() in");
       //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //this->is_focus_triggered = false;    		
	initChannelEdit();
	log("ChannelEdit::init() out");
	return true;
}

void ChannelEdit::initChannelEdit()
{
	this->removeAllChildrenWithCleanup(true);
	
	changing_number = false;
	
	ElementDisplayListSystem *edls = new (std::nothrow) ElementDisplayListSystem();
	if (edls && edls->init())
	{
		edls->autorelease();
	}
	
	this->addChild(edls, 0, "ElementDisplayListSystem");
	
	log("ChannelEdit::initChannelEdit 1");	
	// Create the page view
	Size size(700, 1080);	
	
	ui::Layout* layout = ui::Layout::create();
	layout->setContentSize(size);
	int width = layout->getContentSize().width;
	int height = layout->getContentSize().height;
//top
	ui::ImageView* imageView = ui::ImageView::create("channellist/channellist_bg.png");
	imageView->setPosition(Vec2(width / 2.0f, height / 2.0f));
	layout->addChild(imageView);		
		
	imageView = ui::ImageView::create("channellist/channellist_bar_up.png");
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(0, 922));
	layout->addChild(imageView);

	imageView = ui::ImageView::create("channellist/channellist_bar_down.png");
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(0, 76));
	layout->addChild(imageView);

	if(edls->validChannelCount()>0)
	{		
		imageView = ui::ImageView::create("channellist/channellist_turnup.png");
		imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(340, 932));
		imageView->setVisible(false);
		layout->addChild(imageView,1,"channellist_turnup");
	
		imageView = ui::ImageView::create("channellist/channellist_turndown.png");
		imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(340, 85));
		imageView->setVisible(false);
		layout->addChild(imageView,1,"channellist_turndown");
		
		//channel list focus
		imageView = ui::ImageView::create("channellist/channellist_list_focus.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(700,211));
		imageView->setAnchorPoint(Vec2::ZERO);
		imageView->setPosition(Vec2(0, CHEDIT_FOCUS_IMG_POS));	
		imageView->setVisible(false);
		
		//change number	
		ui::ImageView *imageView1 = ui::ImageView::create("channellist/channellist_turnup.png");
		imageView1->setAnchorPoint(Vec2(0, 0));
		imageView1->setPosition(Vec2(38, 200));
		imageView1->setColor(Color3B(0x57, 0xc9, 0x11));
		imageView1->setScale9Enabled(true);
		imageView1->setContentSize(Size(24,14));
		imageView1->setVisible(false);
		imageView->addChild(imageView1,1,"change number up");
			
		imageView1 = ui::ImageView::create("channellist/channellist_turndown.png");
		imageView1->setAnchorPoint(Vec2(0, 0));
		imageView1->setPosition(Vec2(38, 60));
		imageView1->setColor(Color3B(0x57, 0xc9, 0x11));
		imageView1->setScale9Enabled(true);
		imageView1->setContentSize(Size(24,14));
		imageView1->setVisible(false);
		imageView->addChild(imageView1,1,"change number down");
		
		layout->addChild(imageView,0,CHEDIT_FOCUS_IMG_TAG);
		
	//channel edit icons
	
		imageView = ui::ImageView::create("general/general_button_focus.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(145,146));
		imageView->setAnchorPoint(Vec2::ZERO);
		imageView->setPosition(Vec2(704, 768));
		imageView->setVisible(false);
		layout->addChild(imageView,0,"channel attr focus");
		
		
		imageView = ui::ImageView::create("general/general_button_normal.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(90,90));
		imageView->setAnchorPoint(Vec2::ZERO);
		imageView->setPosition(Vec2(730+0*120, 820));
		imageView->setVisible(false);		
		
		imageView1 = ui::ImageView::create("channeledit/channeledit_change-number_select.png");
		imageView1->setPosition(Vec2(45, 45));
		imageView1->setVisible(false);
		imageView->addChild(imageView1,1,"change-number_select");
		imageView1 = ui::ImageView::create("channeledit/channeledit_change-number_normal.png");
		imageView1->setPosition(Vec2(45, 45));
		imageView->addChild(imageView1,1,"change-number_normal");
		
		
		auto label = Label::createWithTTF("Change Number", "general/SourceHanSansTWHK-Light.ttf", 33);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(0, 0, 0));	
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(80, 16));
		label->setVisible(false);
		imageView->addChild(label,1,"Change Number");
		
		layout->addChild(imageView,0,CHEDIT_ATTR_TAG+0);
		
		imageView = ui::ImageView::create("general/general_button_normal.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(90,90));
		imageView->setAnchorPoint(Vec2::ZERO);
		imageView->setPosition(Vec2(730+1*120, 820));
		imageView->setVisible(false);			
	
		
		imageView1 = ui::ImageView::create("channeledit/channeledit_unlock_select.png");
		imageView1->setPosition(Vec2(45, 45));
		imageView1->setVisible(false);	
		imageView->addChild(imageView1,1,"unlock_select");
		ui::ImageView *imageView2 = ui::ImageView::create("channeledit/channeledit_lock_select.png");
		imageView2->setPosition(Vec2(45, 45));
		imageView2->setVisible(false);
		imageView->addChild(imageView2,1,"lock_select");
		
		imageView1 = ui::ImageView::create("channeledit/channeledit_unlock_normal.png");
		imageView1->setPosition(Vec2(45, 45));
		imageView->addChild(imageView1,1,"unlock_normal");
		imageView2 = ui::ImageView::create("channeledit/channeledit_lock_normal.png");
		imageView2->setPosition(Vec2(45, 45));
		imageView->addChild(imageView2,1,"lock_normal");
		//Todo:根据数据库判断当前频道是否加锁，显示相应的图片
		if(edls->getLockAttr(0))
		{
			imageView1->setVisible(false);		
		}
		else
		{	
			imageView2->setVisible(false);
		}
		
		label = Label::createWithTTF("Unlock", "general/SourceHanSansTWHK-Light.ttf", 33);
			label->setAnchorPoint(Vec2(0, 0));
			label->setColor(Color3B(0, 0, 0));	
			label->setAlignment(TextHAlignment::LEFT);
			label->setPosition(Vec2(80, 16));
			label->setVisible(false);
			imageView->addChild(label,1,"Unlock");
		
		label = Label::createWithTTF("Lock", "general/SourceHanSansTWHK-Light.ttf", 33);
			label->setAnchorPoint(Vec2(0, 0));
			label->setColor(Color3B(0, 0, 0));	
			label->setAlignment(TextHAlignment::LEFT);
			label->setPosition(Vec2(80, 16));
			label->setVisible(false);
			imageView->addChild(label,1,"Lock");
		
		layout->addChild(imageView,0,CHEDIT_ATTR_TAG+1);
		
		imageView = ui::ImageView::create("general/general_button_normal.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(90,90));
		imageView->setAnchorPoint(Vec2::ZERO);
		imageView->setPosition(Vec2(730+2*120, 820));
		imageView->setVisible(false);	
		
		imageView1 = ui::ImageView::create("channeledit/channeledit_fav_select.png");
		imageView1->setPosition(Vec2(45, 45));
		imageView1->setVisible(false);
		imageView->addChild(imageView1,1,"fav_select");
		
		imageView1 = ui::ImageView::create("channeledit/channeledit_fav_normal.png");
		imageView1->setPosition(Vec2(45, 45));
		imageView->addChild(imageView1,1,"fav_normal");
		
		label = Label::createWithTTF("Favourite", "general/SourceHanSansTWHK-Light.ttf", 33);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(0, 0, 0));	
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(80, 16));
		label->setVisible(false);
		imageView->addChild(label,1,"Favourite");
		
		layout->addChild(imageView,0,CHEDIT_ATTR_TAG+2);
		
		
		imageView = ui::ImageView::create("general/general_button_normal.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(90,90));
		imageView->setAnchorPoint(Vec2::ZERO);
		imageView->setPosition(Vec2(730+3*120, 820));
		imageView->setVisible(false);	
		
		imageView1 = ui::ImageView::create("channeledit/channeledit_del_select.png");
		imageView1->setPosition(Vec2(45, 45));
		imageView1->setVisible(false);
		imageView->addChild(imageView1,1,"del_select");
		imageView1 = ui::ImageView::create("channeledit/channeledit_del_normal.png");
		imageView1->setPosition(Vec2(45, 45));
		imageView->addChild(imageView1,1,"del_normal");
		
		label = Label::createWithTTF("Delete", "general/SourceHanSansTWHK-Light.ttf", 33);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(0, 0, 0));	
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(80, 16));
		label->setVisible(false);
		imageView->addChild(label,1,"Delete");	
		
		layout->addChild(imageView,0,CHEDIT_ATTR_TAG+3);
	}


//bottom
	imageView = ui::ImageView::create("channellist/channellist_selectchannel.png");
	imageView->setPosition(Vec2(40, 36));
	layout->addChild(imageView);

	ui::Text* text = ui::Text::create("Select Channel", "general/SourceHanSansTWHK-Light.ttf", 33);
	text->setColor(Color3B(91, 91, 91));
	text->setPosition(Vec2(170, 36));
	layout->addChild(text);


	text = ui::Text::create("Edit Channel", "general/SourceHanSansTWHK-Light.ttf", 33);
	text->setTextHorizontalAlignment(TextHAlignment::CENTER);
	text->setColor(Color3B(91, 91, 91));
	text->setAnchorPoint(Vec2::ZERO);
	text->setPosition(Vec2(90, 986));	
	layout->addChild(text);
	
	log("ChannelEdit::initChannelEdit 2");	
	
	if(edls->validChannelCount()>0)
		addChannelList(layout,2);//获取所有channel的数据库
log("ChannelEdit::initChannelEdit 3");			
	addChild(layout,0,"Channel Edit Panel");		
    addKeyListener(CC_CALLBACK_2(ChannelEdit::onKeyPressed, this), layout);
    	
 log("ChannelEdit::initChannelEdit 4");	   
    

}

void ChannelEdit::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    stopPropagation(keyCode, event, false);    
    Node *node = this->getChildByName("Channel Edit Panel");
	ui::Layout* layout = static_cast<ui::Layout*>(node);    
    node = layout->getChildByName("All Channels");
    ChannelListPageView *clpv = static_cast<ChannelListPageView*>(node);
    
    node = layout->getChildByTag(CHEDIT_FOCUS_IMG_TAG);
    ui::ImageView *img = static_cast<ui::ImageView*>(node);      
    
    switch(keyCode) 
	{
	    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	    case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
	    //if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			if(!clpv)
				break;
			if (clpv->is_focus_triggered)
			{
				if(clpv)
				{
	
					//焦点左移，参数
					/*enum
					{
						CHEDIT_NULL,
						CHEDIT_CHANNEL_NUMBER,
						CHEDIT_LOCK,
						CHEDIT_FAVOURITE,
						CHEDIT_DELETE,
					};*/
					
					if(clpv->x_position >= 730&&clpv->x_position <= 1090)
					{
						modifyChannelAttr(layout,(clpv->x_position - 730)/120,clpv->cur_idx);
						clpv->x_position -= 120;
						if(clpv->x_position < 730)
							clpv->x_position = 0;
					}		    	
			    }			
			}
			break;
		}
	
	    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	    case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
	    //if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	    {
			if(!clpv)
				break;
			if (clpv->is_focus_triggered)
			{
				if(clpv)
				{
	
					//焦点右移，参数
					/*enum
					{
						CHEDIT_NULL,
						CHEDIT_CHANNEL_NUMBER,
						CHEDIT_LOCK,
						CHEDIT_FAVOURITE,
						CHEDIT_DELETE,
					};*/
					if(clpv->x_position == 0)
					{
						modifyChannelAttr(layout,CHEDIT_CHANNEL_NUMBER,clpv->cur_idx);
						clpv->x_position = 730;
					}
					else if(clpv->x_position >= 730 &&clpv->x_position <= 970)
					{
						modifyChannelAttr(layout,(clpv->x_position - 730)/120 + 2,clpv->cur_idx);
						clpv->x_position += 120;
					}		    	
			    }			
			}
	    	break;
	    }
	    case EventKeyboard::KeyCode::KEY_UP_ARROW:
	    case EventKeyboard::KeyCode::KEY_DPAD_UP:
	    //if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			if(!clpv)
				break;
			node = clpv->getChildByTag(CHLIST_TAB_TAG+2);
			ChannelListTableView *table = static_cast<ChannelListTableView*>(node);		
			
				
			if (clpv->is_focus_triggered)
			{
				if(changing_number)
				{
					Node *node = this->getChildByName("ElementDisplayListSystem");
					ElementDisplayListSystem *edls = static_cast<ElementDisplayListSystem*>(node);
					edls->exchangeElement(edls->allChannels,clpv->cur_idx,true);
	    			//table->reloadData();
	    			table->updateCellAtIndex(clpv->cur_idx-1);
	    			table->updateCellAtIndex(clpv->cur_idx);
				}
				
				
				if(clpv->cur_idx>0)
					clpv->cur_idx--;			
				
				if(clpv->y_position + 117 >CHEDIT_FOCUS_IMG_POS)////need scroll to last cell
				{
					if(clpv->cur_idx>=0)
					{
						table->scrollToIndex(clpv->cur_idx+CHEDIT_ITEM_NUM-1);//7 cell visible
						//Todo:根据数据库中锁定信息使用资源图lock或unlock
	    				//updateChannelAttr(layout,false);
	    				modifyChannelAttr(layout,CHEDIT_NULL,clpv->cur_idx);
	    				clpv->x_position = 0;
					}
						
				}
				else
				{
					clpv->y_position += 117;
					if(clpv->y_position<=CHEDIT_FOCUS_IMG_POS&&clpv->y_position>0)
					{
						img->setVisible(false);			
						img->setPosition(Vec2(0, clpv->y_position));
						img->setVisible(true);
						
						
						modifyChannelAttr(layout,CHEDIT_NULL,clpv->cur_idx);
	    						clpv->x_position = 0;
						for(int i = 0;i < 4;i++)
						{
//							if(i == 1)//lock
//	    					{
//	    						//Todo:根据数据库中锁定信息使用资源图lock或unlock
//	    						//updateChannelAttr(layout,false);
//	    						modifyChannelAttr(layout,CHEDIT_NULL,clpv->cur_idx);
//	    						clpv->x_position = 0;
//	    						
//	    					}
							node = layout->getChildByTag(CHEDIT_ATTR_TAG+i);
	    					ui::ImageView *img_attr = static_cast<ui::ImageView*>(node); 
	    					img_attr->setVisible(false);
	    								
							img_attr->setPosition(Vec2(730+i*120, clpv->y_position+96));//96=820-CHEDIT_FOCUS_IMG_POS
							if(changing_number)
								img_attr->setVisible(false);	 
							else
								img_attr->setVisible(true);	 
							
						}
					}
				}
				
				//决定是否有上下箭头
				
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
				if(clpv->cur_idx <total_num-CHEDIT_ITEM_NUM)
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
			node = clpv->getChildByTag(CHLIST_TAB_TAG+2);
			ChannelListTableView *table = static_cast<ChannelListTableView*>(node);
					
	    	if (!clpv->is_focus_triggered)
			{
				clpv->is_focus_triggered = true;
				img->setVisible(true);
				clpv->x_position = 0; 
				clpv->y_position = CHEDIT_FOCUS_IMG_POS;    
				clpv->cur_idx = 0;
				img->setPosition(Vec2(0, clpv->y_position));
				
				modifyChannelAttr(layout,CHEDIT_NULL,clpv->cur_idx);
						clpv->x_position = 0;
				
				for(int i = 0;i < 4;i++)
				{
					node = layout->getChildByTag(CHEDIT_ATTR_TAG+i);
					ui::ImageView *img_attr = static_cast<ui::ImageView*>(node); 
					//img_attr->setVisible(false);			
					//img_attr->setPosition(Vec2(730+i*120, clpv->y_position+96));//96=820-CHEDIT_FOCUS_IMG_POS
//					if(i == 1)//lock
//					{
//						//Todo:根据数据库中锁定信息使用资源图lock或unlock
//						//updateChannelAttr(layout,false);
//						modifyChannelAttr(layout,CHEDIT_NULL,clpv->cur_idx);
//						clpv->x_position = 0;
//					}	
					img_attr->setVisible(true);	 
					
				}		
	    	}
	    	else
			{
				if(changing_number)
				{
					Node *node = this->getChildByName("ElementDisplayListSystem");
					ElementDisplayListSystem *edls = static_cast<ElementDisplayListSystem*>(node);
					edls->exchangeElement(edls->allChannels,clpv->cur_idx,false);
	    			//table->reloadData();
	    			table->updateCellAtIndex(clpv->cur_idx);
	    			table->updateCellAtIndex(clpv->cur_idx+1);
				}
				
				
				ssize_t total_num = clpv->numberOfCellsInTableView(table);
				if(clpv->cur_idx<total_num-1)
					clpv->cur_idx++;
				if(clpv->y_position - 117 <0)//need scroll to next cell
				{
					
					if(clpv->cur_idx<total_num)
					{
						table->scrollToIndex(clpv->cur_idx);
						
						//Todo:根据数据库中锁定信息使用资源图lock或unlock
						//updateChannelAttr(layout,false);
						modifyChannelAttr(layout,CHEDIT_NULL,clpv->cur_idx);
						clpv->x_position = 0;
					}
				}
				else
				{
				
					clpv->y_position -= 117;
					if(clpv->y_position<=CHEDIT_FOCUS_IMG_POS&&clpv->y_position>0)
					{
						img->setVisible(false);			
						img->setPosition(Vec2(0, clpv->y_position));
						img->setVisible(true);	
						
						
						modifyChannelAttr(layout,CHEDIT_NULL,clpv->cur_idx);
								clpv->x_position = 0;		
						for(int i = 0;i < 4;i++)
						{
//							if(i == 1)//lock
//							{
//								//Todo:根据数据库中锁定信息使用资源图lock或unlock
//								//updateChannelAttr(layout,false);
//								modifyChannelAttr(layout,CHEDIT_NULL,clpv->cur_idx);
//								clpv->x_position = 0;
//							}
							node = layout->getChildByTag(CHEDIT_ATTR_TAG+i);
	    					ui::ImageView *img_attr = static_cast<ui::ImageView*>(node); 
	    					img_attr->setVisible(false);
	    					
							img_attr->setPosition(Vec2(730+i*120, clpv->y_position+96));//96=820-CHEDIT_FOCUS_IMG_POS
							if(changing_number)
								img_attr->setVisible(false);
							else
								img_attr->setVisible(true);	 
							
						}
					}
				}
				
				//决定是否有上下箭头
				
				Node *node1 = layout->getChildByName("channellist_turndown");
				ui::ImageView* img1 = static_cast<ui::ImageView*>(node1);
				Node *node2 = layout->getChildByName("channellist_turnup");
				ui::ImageView* img2 = static_cast<ui::ImageView*>(node2);
				if(total_num>CHEDIT_ITEM_NUM)
				{
					if(clpv->cur_idx == total_num-1)
					{
						img1->setVisible(false);
					}
					else
					{
						img1->setVisible(true);
					}
					
					if(clpv->cur_idx >CHEDIT_ITEM_NUM-1)
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
			node = clpv->getChildByTag(CHLIST_TAB_TAG+2);
			ChannelListTableView *table = static_cast<ChannelListTableView*>(node);
			int cur_attr_index;
			
			if (clpv->is_focus_triggered)
			{
				
				node = img->getChildByName("change number up");
			    ui::ImageView *img_up = static_cast<ui::ImageView*>(node);
			    
			    node = img->getChildByName("change number down");
			    ui::ImageView *img_down = static_cast<ui::ImageView*>(node);
				if(changing_number)
				{					
					changing_number = false;
					img_up->setVisible(false);	
					img_down->setVisible(false);
					modifyChannelAttr(layout,CHEDIT_NULL,clpv->cur_idx);
				}				
				
				if(clpv->x_position >= 730)
				{
					cur_attr_index = (clpv->x_position - 730)/120 + 1;
					switch (cur_attr_index)
					{
					case CHEDIT_CHANNEL_NUMBER:
					{
						//频道上下移动				
					    					    	
					    
						if(!changing_number)
						{
							changing_number = true;
							img_up->setVisible(true);	
							img_down->setVisible(true);
						}
						
						//moveChannel(table, clpv->cur_idx);
						break;
					}
					case CHEDIT_LOCK:
					{
						setLock(table, clpv->cur_idx);
						break;
					}
					case CHEDIT_FAVOURITE:
					{
						setFavourite(table, clpv->cur_idx);

						
						break;
					}
						case CHEDIT_DELETE:
							//频道删除
							deleteChannel(table, clpv->cur_idx);
							break;
						default:
							break;					
					}
				}				
				
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:
		{
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

void ChannelEdit::addChannelList(ui::Layout* layout, ssize_t index)
{
	Node *node = this->getChildByName("ElementDisplayListSystem");
	ElementDisplayListSystem *edls = static_cast<ElementDisplayListSystem*>(node);
	
	ChannelListPageView* ChannelListPageViewScene;
	ChannelListPageViewScene = new (std::nothrow) ChannelListPageView();
	if (ChannelListPageViewScene && ChannelListPageViewScene->init(edls,index,false))
	{
		ChannelListPageViewScene->autorelease();					
	}
	ChannelListPageViewScene->is_focus_triggered = false;

	layout->addChild(ChannelListPageViewScene, 1, "All Channels");
	
	node = ChannelListPageViewScene->getChildByTag(CHLIST_TAB_TAG + 2);
	ChannelListTableView *table = static_cast<ChannelListTableView*>(node);
	
	//Todo:根据频道总数决定是否显示下翻箭头，默认从条目0开始显示，故先没有上翻箭头
	if(ChannelListPageViewScene->numberOfCellsInTableView(table)>CHEDIT_ITEM_NUM)
	{
		Node *node = layout->getChildByName("channellist_turndown");
		ui::ImageView* img = static_cast<ui::ImageView*>(node);
		img->setVisible(true);
	}
		
			
}


void ChannelEdit::updateChannelAttr(ui::Layout* layout,bool is_locked)
{
	Node *node = layout->getChildByTag(CHEDIT_ATTR_TAG+1);
    ui::ImageView *img_attr = static_cast<ui::ImageView*>(node); 
	node = img_attr->getChildByName("lock_normal");
	ui::ImageView *img1 = static_cast<ui::ImageView*>(node); 
	node = img_attr->getChildByName("unlock_normal");
	ui::ImageView *img2 = static_cast<ui::ImageView*>(node); 
	//锁定显示解锁图标，否则显示锁住图标	
	if(is_locked)
	{
		img1->setVisible(false);
		img2->setVisible(true);
	}
	else
	{
		img1->setVisible(true);
		img2->setVisible(false);
	}
}

void ChannelEdit::modifyChannelAttr(ui::Layout* layout,int type_index,int table_index)
{	
	Node *node = this->getChildByName("ElementDisplayListSystem");
	ElementDisplayListSystem *edls = static_cast<ElementDisplayListSystem*>(node);
			
	bool is_locked = edls->getLockAttr(table_index);//Todo:获取当前频道是否locked,锁定显示解锁图标，否则显示锁住图标
	node = layout->getChildByName("channel attr focus");
	ui::ImageView *img_attr_focus = static_cast<ui::ImageView*>(node);
		
	node = layout->getChildByTag(CHEDIT_ATTR_TAG+0);
    ui::ImageView *img_attr0 = static_cast<ui::ImageView*>(node); 
	node = img_attr0->getChildByName("change-number_normal");
	ui::ImageView *img_change_normal = static_cast<ui::ImageView*>(node); 
	node = img_attr0->getChildByName("change-number_select");
	ui::ImageView *img_change_select = static_cast<ui::ImageView*>(node);
	
	node = img_attr0->getChildByName("Change Number");
	Label *label_change_number = static_cast<Label*>(node); 
	
		
	node = layout->getChildByTag(CHEDIT_ATTR_TAG+1);
    ui::ImageView *img_attr1 = static_cast<ui::ImageView*>(node);		
	node = img_attr1->getChildByName("lock_normal");
	ui::ImageView *img_lock_normal = static_cast<ui::ImageView*>(node); 
	node = img_attr1->getChildByName("unlock_normal");
	ui::ImageView *img_unlock_normal = static_cast<ui::ImageView*>(node); 
	
	node = img_attr1->getChildByName("lock_select");
	ui::ImageView *img_lock_select = static_cast<ui::ImageView*>(node); 
	node = img_attr1->getChildByName("unlock_select");
	ui::ImageView *img_unlock_select = static_cast<ui::ImageView*>(node);
		
	node = img_attr1->getChildByName("Lock");	
	Label *label_lock = static_cast<Label*>(node); 
	
	node = img_attr1->getChildByName("Unlock");
	Label *label_unlock = static_cast<Label*>(node); 
	
	node = layout->getChildByTag(CHEDIT_ATTR_TAG+2);
    ui::ImageView *img_attr2 = static_cast<ui::ImageView*>(node); 
	node = img_attr2->getChildByName("fav_normal");
	ui::ImageView *img_fav_normal = static_cast<ui::ImageView*>(node); 
	node = img_attr2->getChildByName("fav_select");
	ui::ImageView *img_fav_select = static_cast<ui::ImageView*>(node);
		
	node = img_attr2->getChildByName("Favourite");
	Label *label_favourite = static_cast<Label*>(node); 
	
	
	node = layout->getChildByTag(CHEDIT_ATTR_TAG+3);
    ui::ImageView *img_attr3 = static_cast<ui::ImageView*>(node); 
	node = img_attr3->getChildByName("del_normal");
	ui::ImageView *img_del_normal = static_cast<ui::ImageView*>(node); 
	node = img_attr3->getChildByName("del_select");
	ui::ImageView *img_del_select = static_cast<ui::ImageView*>(node);	
		
	node = img_attr3->getChildByName("Delete");
	Label *label_delete = static_cast<Label*>(node); 
	
	
	Vec2 pos,pos_focus;
	
	switch(type_index)
	{
		case CHEDIT_NULL:
		{
			
			label_change_number->setVisible(false);
			label_lock->setVisible(false);
			label_unlock->setVisible(false);
			label_favourite->setVisible(false);
			label_delete->setVisible(false);
			
			img_change_normal->setVisible(true);
			img_change_select->setVisible(false);
			
			img_attr0->setContentSize(Size(90,90));
			img_attr0->setVisible(true);
			pos = img_attr0->getPosition();
			pos.x = CHNUM_X_POS;
			img_attr0->setPosition(pos);
			
			
			img_attr_focus->setContentSize(Size(145,146));
			pos_focus = img_attr_focus->getPosition();
			pos_focus.x = CHNUM_X_POS - 28;
			pos_focus.y = pos.y - 52;
			img_attr_focus->setPosition(pos_focus);
			img_attr_focus->setVisible(false);
			
			
			img_lock_select->setVisible(false);
			img_unlock_select->setVisible(false);
			if(is_locked)
			{
				img_lock_normal->setVisible(false);
				img_unlock_normal->setVisible(true);				
				
			}
			else
			{
				img_lock_normal->setVisible(true);
				img_unlock_normal->setVisible(false);				
			}
			
			img_attr1->setContentSize(Size(90,90));
			img_attr1->setVisible(true);
			pos = img_attr1->getPosition();
			pos.x = CHNUM_X_POS + 1*120;
			img_attr1->setPosition(pos);
			
			img_fav_normal->setVisible(true);
			img_fav_select->setVisible(false);
			
			img_attr2->setContentSize(Size(90,90));
			img_attr2->setVisible(true);
			pos = img_attr2->getPosition();
			pos.x = CHNUM_X_POS + 2*120;
			img_attr2->setPosition(pos);
			
			img_del_normal->setVisible(true);
			img_del_select->setVisible(false);
			
			img_attr3->setContentSize(Size(90,90));
			img_attr3->setVisible(true);
			pos = img_attr3->getPosition();
			pos.x = CHNUM_X_POS + 3*120;
			img_attr3->setPosition(pos);
			
			
			break;
		}
		
		case CHEDIT_CHANNEL_NUMBER:
		{
			label_change_number->setVisible(true);
			label_lock->setVisible(false);
			label_unlock->setVisible(false);
			label_favourite->setVisible(false);
			label_delete->setVisible(false);
			
			img_change_normal->setVisible(false);
			img_change_select->setVisible(true);
			
			img_attr0->setContentSize(Size(385,90));
			img_attr0->setVisible(true);
			pos = img_attr0->getPosition();
			pos.x = CHNUM_X_POS;
			img_attr0->setPosition(pos);
			
			
			img_attr_focus->setContentSize(Size(440,148));
			img_attr_focus->setVisible(true);
			pos_focus = img_attr_focus->getPosition();
			pos_focus.x = CHNUM_X_POS - 28;
			pos_focus.y = pos.y - 52;
			img_attr_focus->setPosition(pos_focus);
			
			
			
			img_lock_select->setVisible(false);
			img_unlock_select->setVisible(false);
			if(is_locked)
			{
				img_lock_normal->setVisible(false);
				img_unlock_normal->setVisible(true);				
				
			}
			else
			{
				img_lock_normal->setVisible(true);
				img_unlock_normal->setVisible(false);				
			}
			
			img_attr1->setContentSize(Size(90,90));
			img_attr1->setVisible(true);
			pos = img_attr1->getPosition();
			pos.x = CHNUM_X_POS + 1*120 + 298;
			img_attr1->setPosition(pos);
			
			img_fav_normal->setVisible(true);
			img_fav_select->setVisible(false);
			
			img_attr2->setContentSize(Size(90,90));
			img_attr2->setVisible(true);
			pos = img_attr2->getPosition();
			pos.x = CHNUM_X_POS + 2*120 + 298;
			img_attr2->setPosition(pos);
			
			img_del_normal->setVisible(true);
			img_del_select->setVisible(false);
			
			img_attr3->setContentSize(Size(90,90));
			img_attr3->setVisible(true);
			pos = img_attr3->getPosition();
			pos.x = CHNUM_X_POS + 3*120 + 298;
			img_attr3->setPosition(pos);
			
			
			break;
		}
		case CHEDIT_LOCK:
		{
			label_change_number->setVisible(false);			
			label_favourite->setVisible(false);
			label_delete->setVisible(false);
			
			
			img_change_normal->setVisible(true);
			img_change_select->setVisible(false);
			
			img_attr0->setContentSize(Size(90,90));
			img_attr0->setVisible(true);
			pos = img_attr0->getPosition();
			pos.x = CHNUM_X_POS;
			img_attr0->setPosition(pos);			
			
			img_lock_normal->setVisible(false);
			img_unlock_normal->setVisible(false);
			
			if(is_locked)
			{
				
				label_lock->setVisible(false);
				label_unlock->setVisible(true);				


				img_attr_focus->setContentSize(Size(280,148));
				img_attr_focus->setVisible(true);
				pos_focus = img_attr_focus->getPosition();
				pos_focus.x = CHNUM_X_POS +1*120 - 28;
				pos_focus.y = pos.y - 52;
				img_attr_focus->setPosition(pos_focus);
			
				img_lock_select->setVisible(false);
				img_unlock_select->setVisible(true);
				
				img_attr1->setContentSize(Size(225,90));
							
				
			}
			else
			{
				
				label_lock->setVisible(true);
				label_unlock->setVisible(false);
								
				
				img_attr_focus->setContentSize(Size(250,148));
				img_attr_focus->setVisible(true);
				pos_focus = img_attr_focus->getPosition();
				pos_focus.x = CHNUM_X_POS +1*120 - 28;
				pos_focus.y = pos.y - 52;
				img_attr_focus->setPosition(pos_focus);
				
				img_lock_select->setVisible(true);
				img_unlock_select->setVisible(false);
				
				img_attr1->setContentSize(Size(195,90));
					
			}
			
			img_attr1->setVisible(true);
			pos = img_attr1->getPosition();
			pos.x = CHNUM_X_POS + 1*120;
			img_attr1->setPosition(pos);
			
			img_fav_normal->setVisible(true);
			img_fav_select->setVisible(false);
			
			img_attr2->setContentSize(Size(90,90));
			img_attr2->setVisible(true);
			pos = img_attr2->getPosition();
			if(is_locked)
				pos.x = CHNUM_X_POS + 2*120 + 135;
			else
				pos.x = CHNUM_X_POS + 2*120 + 105;
			img_attr2->setPosition(pos);
			
			img_del_normal->setVisible(true);
			img_del_select->setVisible(false);
			
			img_attr3->setContentSize(Size(90,90));
			img_attr3->setVisible(true);
			pos = img_attr3->getPosition();
			if(is_locked)
				pos.x = CHNUM_X_POS + 3*120 + 135;
			else
				pos.x = CHNUM_X_POS + 3*120 + 105;
			img_attr3->setPosition(pos);
			
			break;
		}
		case CHEDIT_FAVOURITE:
		{
			
			label_change_number->setVisible(false);
			label_lock->setVisible(false);
			label_unlock->setVisible(false);
			label_favourite->setVisible(true);
			label_delete->setVisible(false);
			
			img_change_normal->setVisible(true);
			img_change_select->setVisible(false);
			
			img_attr0->setContentSize(Size(90,90));
			img_attr0->setVisible(true);
			pos = img_attr0->getPosition();
			pos.x = CHNUM_X_POS;
			img_attr0->setPosition(pos);			
			
			
			
			img_attr_focus->setContentSize(Size(320,148));
			img_attr_focus->setVisible(true);
			pos_focus = img_attr_focus->getPosition();
			pos_focus.x = CHNUM_X_POS +2*120 - 28;
			pos_focus.y = pos.y - 52;
			img_attr_focus->setPosition(pos_focus);
			
			img_lock_select->setVisible(false);
			img_unlock_select->setVisible(false);	
			if(is_locked)
			{
				img_lock_normal->setVisible(false);
				img_unlock_normal->setVisible(true);				
				
			}
			else
			{
				img_lock_normal->setVisible(true);
				img_unlock_normal->setVisible(false);		
			}
			
			img_attr1->setContentSize(Size(90,90));
			img_attr1->setVisible(true);
			pos = img_attr1->getPosition();
			pos.x = CHNUM_X_POS + 1*120;
			img_attr1->setPosition(pos);
			
			img_fav_normal->setVisible(false);
			img_fav_select->setVisible(true);
			
			img_attr2->setContentSize(Size(260,90));
			img_attr2->setVisible(true);
			pos = img_attr2->getPosition();
			pos.x = CHNUM_X_POS + 2*120;
			img_attr2->setPosition(pos);
			
			img_del_normal->setVisible(true);
			img_del_select->setVisible(false);
			
			img_attr3->setContentSize(Size(90,90));
			img_attr3->setVisible(true);
			pos = img_attr3->getPosition();
			pos.x = CHNUM_X_POS + 3*120 + 174;
			img_attr3->setPosition(pos);
			
			break;
		}
		case CHEDIT_DELETE:
		{
			
			label_change_number->setVisible(false);
			label_lock->setVisible(false);
			label_unlock->setVisible(false);
			label_favourite->setVisible(false);
			label_delete->setVisible(true);
			
			img_change_normal->setVisible(true);
			img_change_select->setVisible(false);
			
			img_attr0->setContentSize(Size(90,90));
			img_attr0->setVisible(true);
			pos = img_attr0->getPosition();
			pos.x = CHNUM_X_POS;
			img_attr0->setPosition(pos);
			
			
			
			img_attr_focus->setContentSize(Size(280,148));
			img_attr_focus->setVisible(true);
			pos_focus = img_attr_focus->getPosition();
			pos_focus.x = CHNUM_X_POS +3*120 - 28;
			pos_focus.y = pos.y - 52;
			img_attr_focus->setPosition(pos_focus);			
			
			img_lock_select->setVisible(false);
			img_unlock_select->setVisible(false);	
			if(is_locked)
			{
				img_lock_normal->setVisible(false);
				img_unlock_normal->setVisible(true);				
				
			}
			else
			{
				img_lock_normal->setVisible(true);
				img_unlock_normal->setVisible(false);		
			}
			
			img_attr1->setContentSize(Size(90,90));
			img_attr1->setVisible(true);
			pos = img_attr1->getPosition();
			pos.x = CHNUM_X_POS + 1*120;
			img_attr1->setPosition(pos);
			
			img_fav_normal->setVisible(true);
			img_fav_select->setVisible(false);
			
			img_attr2->setContentSize(Size(90,90));
			img_attr2->setVisible(true);
			pos = img_attr2->getPosition();
			pos.x = CHNUM_X_POS + 2*120;
			img_attr2->setPosition(pos);
			
			img_del_normal->setVisible(true);
			img_del_select->setVisible(false);
			
			img_attr3->setContentSize(Size(220,90));
			img_attr3->setVisible(true);
			pos = img_attr3->getPosition();
			pos.x = CHNUM_X_POS + 3*120;
			img_attr3->setPosition(pos);
			
			break;
		}
		default:
			break;
	}
	
}


void ChannelEdit::moveChannel(TableView* table,ssize_t idx)
{
	changing_number = true;
	/*
	//
	Node *node = this->getChildByName("Channel Edit Panel");
	ui::Layout* layout = static_cast<ui::Layout*>(node);    
    node = layout->getChildByName("All Channels");
    ChannelListPageView *clpv = static_cast<ChannelListPageView*>(node);
    
    node = layout->getChildByTag(CHEDIT_FOCUS_IMG_TAG);
    ui::ImageView *img = static_cast<ui::ImageView*>(node); 
	
	addKeyListener(CC_CALLBACK_2(ChannelEdit::onKeyPressed_moveChannel, this), img);
	*/
}
void ChannelEdit::setLock(TableView* table,ssize_t idx)
{
	TableViewCell* cell;
	cell = table->cellAtIndex(idx);
	
	Sprite* lock_icon = (Sprite*)cell->getChildByName("lock icon");
	
	Node *node = this->getChildByName("ElementDisplayListSystem");
	ElementDisplayListSystem *edls = static_cast<ElementDisplayListSystem*>(node);
	if(edls->getLockAttr(idx))//已锁上，解锁需输入pin码
	{
		lock_icon->setVisible(false);
				
		cocos2d::Node* curNode = tvScene::getTvLayer();
		ChannelPin::creatLayer(curNode);		
					
		edls->updateLockAttr(idx,false);
	}
	else
	{
		lock_icon->setVisible(true);
		edls->updateLockAttr(idx,true);
	}	
	
	
	
}
void ChannelEdit::setFavourite(TableView* table,ssize_t idx)
{
	
	TableViewCell* cell;
	cell = table->cellAtIndex(idx);
	
	Sprite* fav_icon = (Sprite*)cell->getChildByName("favourite icon");
	Node *node = this->getChildByName("ElementDisplayListSystem");
	ElementDisplayListSystem *edls = static_cast<ElementDisplayListSystem*>(node);
	
	if(edls->getFavAttr(idx))
	{
		fav_icon->setVisible(false);
		edls->updateFavAttr(idx,false);
	}
	else
	{
		fav_icon->setVisible(true);
		edls->updateFavAttr(idx,true);
	}
	
	
}
void ChannelEdit::deleteChannel(TableView* table,ssize_t idx)
{	
	//table->removeCellAtIndex(idx);
	Node *node = this->getChildByName("ElementDisplayListSystem");
	ElementDisplayListSystem *edls = static_cast<ElementDisplayListSystem*>(node);
	
	//删除最后的元素
	table->removeCellAtIndex(edls->validChannelCount()-1);
	
	edls->eraseElement(edls->allChannels,idx,true);	
	edls->updateElement();	
	
	for (int i = idx;i<edls->validChannelCount();i++)
		table->updateCellAtIndex(i);	
	//table->reloadData();
	
}

