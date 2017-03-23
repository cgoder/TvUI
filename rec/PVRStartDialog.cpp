#include "rec/PVRStartDialog.h"
#include "rec/PVRUI.h"
#include "tvScene.h"
PVRStartDialog::PVRStartDialog()
{
	this->setName("PVRStartDialog");
	log("PVRStartDialog::PVRStartDialog");
}

PVRStartDialog::~PVRStartDialog()
{
	
}

cocos2d::Layer* PVRStartDialog::creatLayer(Node* node)
{
	if (node) {
		Layer* PVRStartDialog = (Layer*)node->getChildByName("PVRStartDialog");
		if (PVRStartDialog) {
			return PVRStartDialog;
		}
		else {
			log("PVRStartDialog:ceart");
			auto pvrthum = PVRStartDialog::create();
			node->addChild(pvrthum);			
			return pvrthum;
		}
	}
	return nullptr;
}
Scene* PVRStartDialog::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PVRStartDialog::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool PVRStartDialog::init()
{
	std::string panelinfo;
	std::string panelstring;
	Sprite* sprite;

	sprite = Sprite::create("general/general_popup_bg.png", Rect(430, 298, 1060, 490));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(430, 298));
	
	ui::ImageView* imageView = ui::ImageView::create("info/info_popup_bg.png");
	imageView->setScale9Enabled(true);	
	imageView->setContentSize(Size(1267,911));
	//imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(560, 355));
	sprite->addChild(imageView);

	panelinfo = "Your reservation will start.\nWould you like to switch to the channel?";
	panelstring = "RECORD_DIALOG_START_RECORDING";
		
	auto label = Label::createWithTTF(panelinfo, "general/SourceHanSansTWHK-Light.ttf", 40);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(137, 280));
	sprite->addChild(label);
	
	imageView = ui::ImageView::create("general/general_button_normal.png");
	imageView->setScale9Enabled(true);
	imageView->setContentSize(Size(300,72));
	imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(203, 87));
	sprite->addChild(imageView);
	
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
	
	addKeyListener(CC_CALLBACK_2(PVRStartDialog::onKeyPressed, this), sprite);
	return true;
}

void PVRStartDialog::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);
	
	Node *node = this->getChildByName("RECORD_DIALOG_START_RECORDING");
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
		{	
			
			if (1) {
				this->removeAllChildren();
				if (this->getParent()) {
					this->getParent()->removeChild(this);
				}
			}
				
			if(position.x == 174)
			{				
				cocos2d::Node* curNode = tvScene::getTvLayer();
				PVRUI*  pvrrecord = (PVRUI*)PVRUI::creatLayer(curNode);
				
				
			}				

			break;
		}
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:
			this->removeChildByName("RECORD_DIALOG_START_RECORDING");
			
			break;
		default:
			break;
	}
}