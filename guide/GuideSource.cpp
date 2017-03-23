#include "guide/GuideSource.h"
#include "guide/GuideComplete.h"
#include "tvScene.h"
#include "AutoTuning/AutoTuning.h"
USING_NS_CC;

using namespace cocos2d::ui;


GuideSource::GuideSource()
{
	
}
GuideSource::~GuideSource()
{
	
}

cocos2d::Layer* GuideSource::creatLayer(Node* node)
{
	if (node) {
		Layer* pguidesource = (Layer*)node->getChildByName("GuideSource");
		if (pguidesource) {
			return pguidesource;
		}
		else {
			log("GuideSource:ceart");
			auto pguidesource = GuideSource::create();
			node->addChild(pguidesource);
			return pguidesource;
		}
	}
	return nullptr;
}

bool GuideSource::init()
{
       //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //this->is_focus_triggered = false;    		
	initGuideSource();
	return true;
}

void GuideSource::initGuideSource()
{
	this->removeAllChildrenWithCleanup(true);
	
	ui::Layout* layout = ui::Layout::create();
	layout->setContentSize(Size(1920,1080));
	
	ImageView* bg = ImageView::create("general/general_bg.png");
	bg->setName("ID_PIC_BG");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0,0));
	layout->addChild(bg);

	Text* text = Text::create("Auto Tuning", "general/SourceHanSansTWHK-Light.ttf", 60);
	text->setAnchorPoint(Vec2(0, 0.5));
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(87, 992));
	layout->addChild(text);
	
	text = Text::create("Select source to start tuning", "general/SourceHanSansTWHK-Light.ttf", 28);
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(650, 995));
	layout->addChild(text);	
	
	ImageView* split = ImageView::create("general/general_listline.png");
	split->setAnchorPoint(Vec2(0,0));
	split->setPosition(Vec2(0,958.15));
	split->setScaleY(2);
	layout->addChild(split);
	
	ImageView* img = ImageView::create("sources/source_normal_3.png");
	img->setName("dvb-t normal");
	img->setPosition(Vec2(608,662));
	img->setVisible(false);
	layout->addChild(img);
	
	img = ImageView::create("sources/source_focus_3.png");
	img->setName("dvb-t focus");
	img->setPosition(Vec2(608,662));
	img->setVisible(true);
	layout->addChild(img);
	
	text = Text::create("DVB-T", "general/SourceHanSansTWHK-Light.ttf", 28);
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(600, 540));
	layout->addChild(text);
	
	
	img = ImageView::create("sources/source_normal_5.png");
	img->setName("dvb-c normal");
	img->setPosition(Vec2(960,662));
	img->setVisible(true);
	layout->addChild(img);
	
	img = ImageView::create("sources/source_focus_5.png");
	img->setName("dvb-c focus");
	img->setPosition(Vec2(960,662));
	img->setVisible(false);
	layout->addChild(img);
	
	
	text = Text::create("DVB-C", "general/SourceHanSansTWHK-Light.ttf", 28);
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(960, 540));
	layout->addChild(text);
	
	img = ImageView::create("sources/source_normal_4.png");
	img->setName("atv normal");
	img->setPosition(Vec2(1312,662));
	img->setVisible(true);
	layout->addChild(img);
	
	img = ImageView::create("sources/source_focus_4.png");
	img->setName("atv focus");
	img->setPosition(Vec2(1312,662));
	img->setVisible(false);
	layout->addChild(img);
	
	text = Text::create("ATV", "general/SourceHanSansTWHK-Light.ttf", 28);
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(1310, 540));
	layout->addChild(text);
	
	img = ImageView::create("general/general_button_normal.png");
	img->setName("skip auto turning");	
	img->setAnchorPoint(Vec2(0, 0));
	img->setScale9Enabled(true);	
	img->setContentSize(Size(722,100));
	img->setPosition(Vec2(597,210));
	
	ImageView *img1 = ui::ImageView::create("general/general_button_focus.png");
	img1->setName("skip auto turning focus");		
	img1->setScale9Enabled(true);	
	img1->setContentSize(Size(722 + 60, 100 + 60));
	//img1->setPosition(Vec2(597, 190));
	img1->setAnchorPoint(Vec2(0, 0));	
	img1->setPosition(Vec2(-27, -53));	
	img1->setVisible(false);	
	img->addChild(img1);
	
	text = Text::create("Skip Auto Turning", "general/SourceHanSansTWHK-Light.ttf", 28);	
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(340, 45));
	img->addChild(text);
	
			
	layout->addChild(img);	
	
		
	
	this->addChild(layout,1,"guide source panel");
	
	addKeyListener(CC_CALLBACK_2(GuideSource::onKeyPressed, this), layout);
	
	cur_index = GUIDESOURCE_DVB_T;
}


void GuideSource::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);  
			
	switch(keyCode)
	{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
			if(cur_index == GUIDESOURCE_DVB_C||cur_index == GUIDESOURCE_ATV)
			{				
				cur_index++;
				changeIconImage();
			}
			break;
			
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
			if(cur_index == GUIDESOURCE_DVB_T||cur_index == GUIDESOURCE_DVB_C)
			{				
				cur_index--;
				changeIconImage();
			}
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
	    case EventKeyboard::KeyCode::KEY_DPAD_UP:
	    	if(cur_index == GUIDESOURCE_SKIP)
			{				
				cur_index = GUIDESOURCE_DVB_T;
				changeIconImage();
			}
	    	
	    	break;
	    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	    case EventKeyboard::KeyCode::KEY_DPAD_DOWN:
	    	if(cur_index == GUIDESOURCE_DVB_T||cur_index == GUIDESOURCE_DVB_C||cur_index == GUIDESOURCE_ATV)
			{				
				cur_index = GUIDESOURCE_SKIP;
				changeIconImage();
			}
	    	break;
	    		
		case EventKeyboard::KeyCode::KEY_ENTER:
		case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
		{
//			this->removeAllChildren();
//			if (this->getParent()) {
//				this->getParent()->removeChild(this);
//				}			
			
			if(cur_index == GUIDESOURCE_SKIP)
			{
				cocos2d::Node* curNode = tvScene::getTvLayer();
				GuideComplete::creatLayer(curNode);
			}
			else
			{				
				if(cur_index == GUIDESOURCE_DVB_T)
				{
					skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_DVBT);
				}
				if(cur_index == GUIDESOURCE_DVB_C)
				{
					skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_DVBC);
				}
				if(cur_index == GUIDESOURCE_ATV)
				{
					skyTvMw::getInstance()->setInputSoruce(SKYTV_INPUT_SOURCE_ATV);
				}
				
				cocos2d::Node* curNode = tvScene::getRootLayer();	
				AutoTuning::creatLayer(curNode);
			}
			
			break;
		}
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:
		{
			this->removeAllChildren();
				if (this->getParent()) {
					this->getParent()->removeChild(this);
					}
					
					
			break;
		}
		default:
			break;
	}
	
	
	
}

void GuideSource::changeIconImage()
{
	Node *node = this->getChildByName("guide source panel");
	ui::Layout* layout = static_cast<ui::Layout*>(node);    
    
    node = layout->getChildByName("dvb-t normal");
	ui::ImageView *img_dvbt = static_cast<ui::ImageView*>(node);  
		
	node = layout->getChildByName("dvb-t focus");
	ui::ImageView *img_dvbt_focus = static_cast<ui::ImageView*>(node);	
		
	node = layout->getChildByName("dvb-c normal");
	ui::ImageView *img_dvbc = static_cast<ui::ImageView*>(node);
	
	node = layout->getChildByName("dvb-c focus");
	ui::ImageView *img_dvbc_focus = static_cast<ui::ImageView*>(node);
		
	node = layout->getChildByName("atv normal");
	ui::ImageView *img_atv = static_cast<ui::ImageView*>(node);  
		
	node = layout->getChildByName("atv focus");
	ui::ImageView *img_atv_focus = static_cast<ui::ImageView*>(node);	
		
	node = layout->getChildByName("skip auto turning");
	ui::ImageView *img_skip = static_cast<ui::ImageView*>(node);
	
	//node = layout->getChildByName("skip auto turning focus");
	node = img_skip->getChildByName("skip auto turning focus");
	ui::ImageView *img_skip_focus = static_cast<ui::ImageView*>(node);	
		
	if(cur_index == GUIDESOURCE_DVB_T)	
	{		
		img_dvbt->setVisible(false);	
		img_dvbt_focus->setVisible(true);
		img_dvbc->setVisible(true);	
		img_dvbc_focus->setVisible(false);
		img_atv->setVisible(true);	
		img_atv_focus->setVisible(false);
		//img_skip->setVisible(true);	
		img_skip_focus->setVisible(false);
		
	}
	if(cur_index == GUIDESOURCE_DVB_C)	
	{
		img_dvbt->setVisible(true);	
		img_dvbt_focus->setVisible(false);
		img_dvbc->setVisible(false);	
		img_dvbc_focus->setVisible(true);
		img_atv->setVisible(true);	
		img_atv_focus->setVisible(false);
		//img_skip->setVisible(true);	
		img_skip_focus->setVisible(false);
	}
	if(cur_index == GUIDESOURCE_ATV)	
	{
		img_dvbt->setVisible(true);	
		img_dvbt_focus->setVisible(false);
		img_dvbc->setVisible(true);	
		img_dvbc_focus->setVisible(false);
		img_atv->setVisible(false);	
		img_atv_focus->setVisible(true);
		//img_skip->setVisible(true);	
		img_skip_focus->setVisible(false);
	}
	if(cur_index == GUIDESOURCE_SKIP)	
	{
		img_dvbt->setVisible(true);	
		img_dvbt_focus->setVisible(false);
		img_dvbc->setVisible(true);	
		img_dvbc_focus->setVisible(false);
		img_atv->setVisible(true);	
		img_atv_focus->setVisible(false);
		//img_skip->setVisible(false);	
		img_skip_focus->setVisible(true);
	}
}