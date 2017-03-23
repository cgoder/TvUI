#include "rec/PVRRecodingThumbnail.h"

PVRRecodingThumbnail::PVRRecodingThumbnail()
{
	this->setName("PVRRecodingThumbnail");
	log("PVRRecodingThumbnail::PVRRecodingThumbnail");
}

PVRRecodingThumbnail::~PVRRecodingThumbnail()
{
	
}

cocos2d::Layer* PVRRecodingThumbnail::creatLayer(Node* node)
{
	if (node) {
		Layer* PVRRecodingThumbnail = (Layer*)node->getChildByName("PVRRecodingThumbnail");
		if (PVRRecodingThumbnail) {
			return PVRRecodingThumbnail;
		}
		else {
			log("PVRRecodingThumbnail:ceart");
			auto pvrthum = PVRRecodingThumbnail::create();
			node->addChild(pvrthum);			
			return pvrthum;
		}
	}
	return nullptr;
}
Scene* PVRRecodingThumbnail::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PVRRecodingThumbnail::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool PVRRecodingThumbnail::init()
{
			
	
	ui::Layout* layout = ui::Layout::create();
	layout->setContentSize(Size(234,85));
	
	Sprite* sprite = Sprite::create("general/general_popup_bg.png", Rect(1686, 995, 234, 85));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(1686, 995));		
	
	
	ui::ImageView* imageView = ui::ImageView::create("general/general_recordicon.png");
	//imageView->setAnchorPoint(Vec2(0, 0));
	imageView->setPosition(Vec2(40, 40));
	sprite->addChild(imageView);
	
	auto label = Label::createWithTTF("Recording", "general/SourceHanSansTWHK-Light.ttf", 30);
	//LabelTTF* label = LabelTTF::create(DefaultPlayStr, "Arial", 36);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0xdb, 0x33, 0x33));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(69, 20));
	sprite->addChild(label);
	
	layout->addChild(sprite);
	
	this->addChild(layout,1,"pvr recording thumbnail");
	
	addKeyListener(CC_CALLBACK_2(PVRRecodingThumbnail::onKeyPressed, this), layout);
	
	return true;
}

void PVRRecodingThumbnail::hidePVRUI()
{
	if (this->getParent()->getChildByName("PVRUI")) {
				this->getParent()->getChildByName("PVRUI")->setVisible(false);
			}
}

void PVRRecodingThumbnail::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);  
    Node *node = this->getChildByName("pvr recording thumbnail");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 
		
	 switch(keyCode) 
	{
		case cocos2d::EventKeyboard::KeyCode::KEY_TV_RECORD:
		case cocos2d::EventKeyboard::KeyCode::KEY_SHIFT:
			if (this->getParent()->getChildByName("PVRUI")) {
				this->getParent()->getChildByName("PVRUI")->setVisible(true);
			}
			if (1) {
				this->removeAllChildren();
				if (this->getParent()) {
					this->getParent()->removeChild(this);
				}
			}
			
			
						
			break;
		
		default:
			break;
	}
}