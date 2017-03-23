#include "common/SetPassword.h"
#include "ui/CocosGUI.h"
#include "common/common.h"

USING_NS_CC;

using namespace ui;


SetPassword::SetPassword()
{
	this->setName("SetPassword");
	log("SetPassword::SetPassword");
}

SetPassword::~SetPassword()
{
	
}

cocos2d::Layer* SetPassword::creatLayer(Node* node)
{
	if (node) {
		Layer* SetPassword = (Layer*)node->getChildByName("SetPassword");
		if (SetPassword) {
			return SetPassword;
		}
		else {
			log("SetPassword:ceart");
			auto setpsw = SetPassword::create();
			node->addChild(setpsw);			
			return setpsw;
		}
	}
	return nullptr;
}
Scene* SetPassword::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SetPassword::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



bool SetPassword::init()
{
	
		Sprite* sprite = Sprite::create("general/general_popup_bg.png", Rect(430, 190, 1060, 700));
	    sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setPosition(Vec2(430, 190));
		
		ui::ImageView* imageView = ui::ImageView::create("info/info_popup_bg.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(1228,868));
		//imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(539, 333));
		sprite->addChild(imageView);
		
		auto label = Label::createWithTTF("Set PassWord", "general/SourceHanSansTWHK-Light.ttf", 40);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(0x33, 0x33, 0x33));			
		label->setPosition(Vec2(446, 590));
		sprite->addChild(label);
		
		label = Label::createWithTTF("New PassWord:", "general/SourceHanSansTWHK-Light.ttf", 33);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(91, 91, 91));	
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(210, 480));
		sprite->addChild(label);
		
		label = Label::createWithTTF("Confirm PassWord:", "general/SourceHanSansTWHK-Light.ttf", 33);
		label->setAnchorPoint(Vec2(0, 0));
		label->setColor(Color3B(91, 91, 91));	
		label->setAlignment(TextHAlignment::LEFT);
		label->setPosition(Vec2(210, 240));
		sprite->addChild(label);		
		
		for(int i = 0;i<4;i++)
		{
			ui::ImageView* imageView = ui::ImageView::create("general/general_input.png");
			imageView->setScale9Enabled(true);	
			imageView->setContentSize(Size(120,120));
			imageView->setAnchorPoint(Vec2(0, 0));
			imageView->setPosition(Vec2(203+i*185, 364));
			sprite->addChild(imageView);
			
			
			
			imageView = ui::ImageView::create("general/general_input.png");
			imageView->setScale9Enabled(true);	
			imageView->setContentSize(Size(120,120));
			imageView->setAnchorPoint(Vec2(0, 0));
			imageView->setPosition(Vec2(203+i*185, 126));
			sprite->addChild(imageView);
			
			
		}
		
		
		imageView = ui::ImageView::create("general/general_button_focus.png");
		imageView->setScale9Enabled(true);	
		imageView->setContentSize(Size(178,188));
		imageView->setAnchorPoint(Vec2(0, 0));
		imageView->setPosition(Vec2(172, 299));
		sprite->addChild(imageView,2,"general_button_focus_pin");
		
        int y_pos;
        int x_pos;	
        for(int i = 0;i<8;i++)
        {
        	if(i>3)
        	{
        		x_pos = 258+(i-4)*185;
	        	y_pos = 174;
	        }
	        else
        	{
        		x_pos = 258+i*185;
        		y_pos = 416;
        	}
	        	
        	auto inputlabel = Label::createWithTTF(" ", "general/SourceHanSansTWHK-Light.ttf", 60);
	        inputlabel->setPosition(Vec2(x_pos, y_pos));	        
	        inputlabel->setTextColor(Color4B(0,162,232,255));
	        sprite->addChild(inputlabel,2,PIN_TEXT_TAG+i);
	        
	        
	    }
	    
	this->addChild(sprite,2,"set_password");
	
	addKeyListener(CC_CALLBACK_2(SetPassword::onKeyPressed, this), sprite);
	
	
	enter_pin_started = false;
	cur_pin_index = 0;
	return true;
}


void SetPassword::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);	
	
	Node *node = this->getChildByName("set_password");
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
				img->setPosition(Vec2(172+(0+1)*185,299));
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
						img->setPosition(Vec2(172+(this->cur_pin_index+1)*185,299));
						img->setVisible(true);
						
						
					}
				}				
				else if(this->cur_pin_index < 8)
				{
					Node *node = sprite->getChildByTag(PIN_TEXT_TAG+this->cur_pin_index);				
					Label *inputlabel = static_cast<Label*>(node);				
					inputlabel->setString(StringUtils::format("%ld", KeyCode2int(keyCode)));
				
					//if(this->cur_pin_index<7)
					{
						ui::ImageView* img = (ui::ImageView* )sprite->getChildByName("general_button_focus_pin");
						img->setVisible(false);			
						img->setPosition(Vec2(172+(this->cur_pin_index+1-5)*185,61));
						img->setVisible(true);
						
						
					}
				}
				
				if(this->cur_pin_index<7)
					this->cur_pin_index++;
							
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_ENTER:
		case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
		//if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			//Todo:保存pin至数据库

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

int SetPassword::KeyCode2int(cocos2d::EventKeyboard::KeyCode keyCode)
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

