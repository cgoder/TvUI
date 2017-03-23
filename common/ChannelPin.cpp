#include "common/ChannelPin.h"
#include "ui/CocosGUI.h"
#include "common/common.h"

USING_NS_CC;

using namespace ui;


ChannelPin::ChannelPin()
{
	this->setName("ChannelPin");
	log("ChannelPin::ChannelPin");
}

ChannelPin::~ChannelPin()
{
	
}

cocos2d::Layer* ChannelPin::creatLayer(Node* node)
{
	if (node) {
		Layer* ChannelPin = (Layer*)node->getChildByName("ChannelPin");
		if (ChannelPin) {
			return ChannelPin;
		}
		else {
			log("ChannelPin:ceart");
			auto channelpin = ChannelPin::create();
			node->addChild(channelpin);			
			return channelpin;
		}
	}
	return nullptr;
}
Scene* ChannelPin::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChannelPin::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



bool ChannelPin::init()
{
	
		std::string infopanelstring = "Enter PIN";
		Sprite* sprite = Sprite::create("general/general_popup_bg.png", Rect(430, 298, 1060, 490));
	    //sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setPosition(Vec2(960, 540));
		
		ui::ImageView* imageView = ui::ImageView::create("info/info_popup_bg.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(1228,658));
		//imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(539, 228));
		sprite->addChild(imageView);
		
		auto label = Label::createWithTTF("Enter PIN", "general/SourceHanSansTWHK-Light.ttf", 40);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(0, 0, 0));	
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(446, 346));
		sprite->addChild(label);
		
		label = Label::createWithTTF("Note:Please enter PIN code to unlock operation.", "general/SourceHanSansTWHK-Light.ttf", 33);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(91, 91, 91));	
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(182, 74));
		sprite->addChild(label);
		
		for(int i = 0;i<4;i++)
		{
			ui::ImageView* imageView = ui::ImageView::create("general/general_input.png");
			imageView->setScale9Enabled(true);	
			imageView->setContentSize(Size(120,120));
			imageView->setAnchorPoint(Vec2(0, 0));
			imageView->setPosition(Vec2(203+i*185, 180));
			sprite->addChild(imageView);
		}
		
		imageView = ui::ImageView::create("general/general_button_focus.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(178,188));
		imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(172, 115));
		sprite->addChild(imageView,2,"general_button_focus_pin");
		
        	
        for(int i = 0;i<4;i++)
        {
        	auto inputlabel = Label::createWithTTF(" ", "general/SourceHanSansTWHK-Light.ttf", 60);
	        inputlabel->setPosition(Vec2(258+i*185, 228));	        
	        inputlabel->setTextColor(Color4B(0,162,232,255));
	        sprite->addChild(inputlabel,2,PIN_TEXT_TAG+i);
	    }
	    
	this->addChild(sprite,2,"channel_pin");
	
	addKeyListener(CC_CALLBACK_2(ChannelPin::onKeyPressed, this), sprite);
	
	
	enter_pin_started = false;
	cur_pin_index = 0;
	return true;
}


void ChannelPin::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);	
	
	Node *node = this->getChildByName("channel_pin");
	Sprite* sprite = static_cast<Sprite*>(node);
	switch(keyCode) 
	{
		case EventKeyboard::KeyCode::KEY_0:
		case EventKeyboard::KeyCode::KEY_1:
		case EventKeyboard::KeyCode::KEY_2:
		case EventKeyboard::KeyCode::KEY_3:
		case EventKeyboard::KeyCode::KEY_4:
		case EventKeyboard::KeyCode::KEY_5:
		case EventKeyboard::KeyCode::KEY_6:
		case EventKeyboard::KeyCode::KEY_7:
		case EventKeyboard::KeyCode::KEY_8:
		case EventKeyboard::KeyCode::KEY_9:
		//if (keyCode >=EventKeyboard::KeyCode::KEY_0&&keyCode <= EventKeyboard::KeyCode::KEY_9)
		{
			//接收数字键，并自动将焦点图片转到下一个
			if(!this->enter_pin_started)
			{
				this->enter_pin_started = true;
	
				Node *node = sprite->getChildByTag(PIN_TEXT_TAG + 0);
				Label *inputlabel = static_cast<Label*>(node);				
				inputlabel->setString(StringUtils::format("%ld", KeyCode2int(keyCode)));
					
				ui::ImageView* img = (ui::ImageView* )sprite->getChildByName("general_button_focus_pin");
				img->setVisible(false);			
				img->setPosition(Vec2(172+(0+1)*185,115));
				img->setVisible(true);
				this->cur_pin_index++;
			}
			else
			{
				
				if(this->cur_pin_index < 4)
				{
					Node *node = sprite->getChildByTag(PIN_TEXT_TAG+this->cur_pin_index);				
					Label *inputlabel = static_cast<Label*>(node);				
					inputlabel->setString(StringUtils::format("%ld", KeyCode2int(keyCode)));
				
					if(this->cur_pin_index<3)
					{
						ui::ImageView* img = (ui::ImageView* )sprite->getChildByName("general_button_focus_pin");
						img->setVisible(false);			
						img->setPosition(Vec2(172+(this->cur_pin_index+1)*185,115));
						img->setVisible(true);
						
						this->cur_pin_index++;
					}
				}
								
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_ENTER:
		case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
		//if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			//Todo:保存pin至数据库
			
			//this->removeChildByTag(PIN_DIALOG_TAG,true);
			if (1) {
				this->removeAllChildren();
				if (this->getParent()) {
					this->getParent()->removeChild(this);
				}
			}
			
			break;
		}
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:
		//if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
		{
						
			//this->removeChildByTag(PIN_DIALOG_TAG,true);
			
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

int ChannelPin::KeyCode2int(cocos2d::EventKeyboard::KeyCode keyCode)
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

