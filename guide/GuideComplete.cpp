#include "guide/GuideComplete.h"

USING_NS_CC;

using namespace cocos2d::ui;


GuideComplete::GuideComplete()
{
	
}
GuideComplete::~GuideComplete()
{
	
}

cocos2d::Layer* GuideComplete::creatLayer(Node* node)
{
	if (node) {
		Layer* pguidecomplete = (Layer*)node->getChildByName("GuideComplete");
		if (pguidecomplete) {
			return pguidecomplete;
		}
		else {
			log("GuideComplete:ceart");
			auto pguidecomplete = GuideComplete::create();
			node->addChild(pguidecomplete);
			return pguidecomplete;
		}
	}
	return nullptr;
}

bool GuideComplete::init()
{
       //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //this->is_focus_triggered = false;    		
	initGuideComplete();
	return true;
}

void GuideComplete::initGuideComplete()
{
	this->removeAllChildrenWithCleanup(true);
	
	ui::Layout* layout = ui::Layout::create();
	layout->setContentSize(Size(1920,1080));
	
	ImageView* bg = ImageView::create("general/general_bg.png");
	bg->setName("ID_PIC_BG");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0,0));
	layout->addChild(bg);
	
	Text* text = Text::create("Guide Complete", "general/SourceHanSansTWHK-Light.ttf", 60);
	text->setAnchorPoint(Vec2(0, 0.5));
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(87, 992));
	layout->addChild(text);	
	
	ImageView* split = ImageView::create("general/general_listline.png");
	split->setAnchorPoint(Vec2(0,0));
	split->setPosition(Vec2(0,958.15));
	split->setScaleY(2);
	layout->addChild(split);
	
	ImageView* img = ImageView::create("general/general_button_normal.png");
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
	img1->setVisible(true);	
	img->addChild(img1);	
	
	text = Text::create("Complete", "general/SourceHanSansTWHK-Light.ttf", 28);	
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(340, 45));
	img->addChild(text);
		
	layout->addChild(img);
		
	
	this->addChild(layout);
	
	addKeyListener(CC_CALLBACK_2(GuideComplete::onKeyPressed, this), layout);
}


void GuideComplete::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);  
	
	switch(keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ENTER:
		case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
		{
			
			if (this->getParent()) {
				this->getParent()->removeAllChildren();
//				if(this->getParent()->getChildByName("GuideSource"))
//					this->getParent()->removeChildByName("GuideSource");
//					
//				if(this->getParent()->getChildByName("GuideCountry"))
//					this->getParent()->removeChildByName("GuideCountry");					
					}
			
			
//			this->removeAllChildren();
//				if (this->getParent()) {
//					this->getParent()->removeChild(this);
//					}
			
						
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