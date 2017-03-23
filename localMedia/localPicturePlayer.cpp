#include "localMedia/localPicturePlayer.h"

LocalPicturePlayer::LocalPicturePlayer()
{
	this->setName("LocalPicturePlayer");
	log("LocalPicturePlayer::LocalPicturePlayer");
}

LocalPicturePlayer::~LocalPicturePlayer()
{
	
}

cocos2d::Layer* LocalPicturePlayer::creatLayer(Node* node)
{
	if (node) {
		Layer* LocalPicturePlayer = (Layer*)node->getChildByName("LocalPicturePlayer");
		if (LocalPicturePlayer) {
			return LocalPicturePlayer;
		}
		else {
			log("LocalPicturePlayer:ceart");
			auto pPicturePlayer = LocalPicturePlayer::create();
			node->addChild(pPicturePlayer);			
			return pPicturePlayer;
		}
	}
	return nullptr;
}
Scene* LocalPicturePlayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LocalPicturePlayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool LocalPicturePlayer::init()
{
	this->removeAllChildrenWithCleanup(true);
	log("LocalPicturePlayer:init in");
	ui::Layout* layout = ui::Layout::create();
	layout->setContentSize(Size(1920,1080));
	int width = layout->getContentSize().width;
	int height = layout->getContentSize().height;	
	
	Sprite* sprite = Sprite::create("general/general_popup_bg.png", Rect(0, 0, 1920, 216));
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(0, 0));		
	layout->addChild(sprite);
	
	//Todo
	auto label = Label::createWithTTF("", "general/SourceHanSansTWHK-Light.ttf", 36);
	//LabelTTF* label = LabelTTF::create(DefaultPlayStr, "Arial", 36);
	label->setAnchorPoint(Vec2(0, 0));
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(58, 1000));
	layout->addChild(label,1,"media file name");
	
	
	ui::ImageView* imageView = ui::ImageView::create("localMedia/pic_shrink.png");
	imageView->setPosition(Vec2(400,105));	
	imageView->setVisible(true);
	layout->addChild(imageView,1,"pic_shrink");
	
	imageView = ui::ImageView::create("localMedia/pic_shrink_focus.png");
	imageView->setPosition(Vec2(400,105));	
	imageView->setVisible(false);
	layout->addChild(imageView,1,"pic_shrink_focus");
	
	imageView = ui::ImageView::create("localMedia/pic_enlarge.png");
	imageView->setPosition(Vec2(680,105));	
	imageView->setVisible(true);
	layout->addChild(imageView,1,"pic_enlarge");
	
	imageView = ui::ImageView::create("localMedia/pic_enlarge_focus.png");
	imageView->setPosition(Vec2(680,105));	
	imageView->setVisible(false);
	layout->addChild(imageView,1,"pic_enlarge_focus");
	
	imageView = ui::ImageView::create("localMedia/pic_play.png");
	imageView->setPosition(Vec2(960,105));	
	imageView->setVisible(false);
	layout->addChild(imageView,1,"pic_play");
	
	imageView = ui::ImageView::create("localMedia/pic_play_focus.png");
	imageView->setPosition(Vec2(960,105));	
	imageView->setVisible(true);
	layout->addChild(imageView,1,"pic_play_focus");
		
	imageView = ui::ImageView::create("localMedia/pic_rotate.png");
	imageView->setPosition(Vec2(1240,105));	
	imageView->setVisible(true);
	layout->addChild(imageView,1,"pic_rotate");
	
	imageView = ui::ImageView::create("localMedia/pic_rotate_focus.png");
	imageView->setPosition(Vec2(1240,105));	
	imageView->setVisible(false);
	layout->addChild(imageView,1,"pic_rotate_focus");	
		
	imageView = ui::ImageView::create("localMedia/pic_delete.png");
	imageView->setPosition(Vec2(1520,105));	
	imageView->setVisible(true);
	layout->addChild(imageView,1,"pic_delete");
	
	imageView = ui::ImageView::create("localMedia/pic_delete_focus.png");
	imageView->setPosition(Vec2(1520,105));	
	imageView->setVisible(false);
	layout->addChild(imageView,1,"pic_delete_focus");
			
	addChild(layout,0,"local picture player");
	addKeyListener(CC_CALLBACK_2(LocalPicturePlayer::onKeyPressed, this), layout);
	
	cur_icon = PICTURE_PLAY;
	cur_zoom_time = 3;//
	cur_rotate_degree = 0;
	is_playing_slide = false;
	return true;
}

void LocalPicturePlayer::localPicturePlayerCallback(MP_MSG_e type, void* pUserData)
{
	Node *node = this->getChildByName("local picture player");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 
	switch(type)
	{
		case MP_MSG_ERROR:
		{
			this->removeAllChildrenWithCleanup(true);
			ui::ImageView* imageView = ui::ImageView::create("general/general_bg.png");
			imageView->setAnchorPoint(Vec2(0, 0));
			imageView->setPosition(Vec2(0, 0));
			layout->addChild(imageView,1,"picture background");
			
			imageView = ui::ImageView::create("localMedia/sorry.png");
			//imageView->setAnchorPoint(Vec2(0, 0));
			imageView->setPosition(Vec2(960, 540));
			layout->addChild(imageView,1,"picture sorry");			
			
			 break;
		}		
		case MP_MSG_PREPARED:
		{
			
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([this]
            {
            	log("LocalPicturePlayer:play start");	
            	CCMediaPlayer::getInstance()->start();
            	log("LocalPicturePlayer:play start out");            		
            });	               
            		
			break;
		}
		case MP_MSG_COMPLETED:
		{
			if(is_playing_slide)
			{
				std::this_thread::sleep_for(std::chrono::microseconds(1000 * 1000 * 2));  
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([this]
	            {
	            	
	            	if(cur_index == pictureList.size()-1)
					{
						cur_index = 0;						
					}
					else
	            		cur_index++;      
	            	play_slide(cur_index);
					    		
	            });	
	        }
				
			 break;
		}
		
		default:
			break;
	}
}

void LocalPicturePlayer::closeLayer()
{
	if (1) {
				if(this->getParent()->getChildByName("localMedia"))
					this->getParent()->getChildByName("localMedia")->setVisible(true);

				this->removeAllChildren();
				if (this->getParent()) {
					this->getParent()->removeChild(this);
				}
			}	
}
	
	
void LocalPicturePlayer::play(string& path)
{	
	if (1) 
	{
		if(this->getParent()->getChildByName("localMedia"))
			this->getParent()->getChildByName("localMedia")->setVisible(false);
	}
	
	log("LocalPicturePlayer:play path %s",path.c_str());
	log("LocalPicturePlayer:play getInstance");
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	log("LocalPicturePlayer:play setListener");
	player->setListener(CC_CALLBACK_2(LocalPicturePlayer::localPicturePlayerCallback,this));
	log("LocalPicturePlayer:play reset");	
	player->reset();
	log("LocalPicturePlayer:play setDataSource");	
	player->setDataSource(path,MP_TYPE_PHOTO);
	log("LocalPicturePlayer:play prepareAsync");	
	player->prepareAsync() ;    
	log("LocalPicturePlayer:play prepareAsync out");	
}

void LocalPicturePlayer::play(std::vector<std::string> &m_pictureListVec)
{	
	
	pictureList = m_pictureListVec;
	std::string path = pictureList.at(0);
	cur_index = 0;
	
	if (1) 
	{
		if(this->getParent()->getChildByName("localMedia"))
			this->getParent()->getChildByName("localMedia")->setVisible(false);
	}
	
	log("LocalPicturePlayer:play path %s",path.c_str());
	log("LocalPicturePlayer:play getInstance");
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	log("LocalPicturePlayer:play setListener");
	player->setListener(CC_CALLBACK_2(LocalPicturePlayer::localPicturePlayerCallback,this));
	log("LocalPicturePlayer:play reset");	
	player->reset();
	log("LocalPicturePlayer:play setDataSource");	
	player->setDataSource(path,MP_TYPE_PHOTO);
	log("LocalPicturePlayer:play prepareAsync");	
	player->prepareAsync() ;    
	log("LocalPicturePlayer:play prepareAsync out");	
}

void LocalPicturePlayer::stop()
{
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	if(player->isPlaying())
		player->stop();
	
	closeLayer();
}


void LocalPicturePlayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);  
    
    switch(keyCode) 
	{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	    case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
	    {
	    	if(cur_icon>0)
	    		cur_icon--;	    		
	    	changeIconImage();	    		
	    	break;
	    }
	    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	    case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
	    {
	    	if(cur_icon<4)
	    		cur_icon++;	    	
	    	changeIconImage();	    	
	    	break;	
	    }
		case EventKeyboard::KeyCode::KEY_ENTER:
	    case EventKeyboard::KeyCode::KEY_DPAD_CENTER:  	
	    {
	    	pictureIconAction();
	    	break;		
		}
			
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:		
		{
			stop();				
			CCMediaPlayer::destoryInstance();
				
			break;
		}	
			
		default:
			break;	
		
	}
}

void LocalPicturePlayer::onKeyPressed_slide(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	stopPropagation(keyCode, event, false);      	 		
    
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
	case EventKeyboard::KeyCode::KEY_BACK:
	case EventKeyboard::KeyCode::KEY_TV_BACK:
	case EventKeyboard::KeyCode::KEY_TV_EXIT:
	{
		this->removeChildByName("local picture slide playing");

		CCMediaPlayer *player = CCMediaPlayer::getInstance();
		//			if(player->isPlaying())
		//				player->stop();

		is_playing_slide = false;

		Node *node = this->getChildByName("local picture player");
		ui::Layout* layout = static_cast<ui::Layout*>(node);
		layout->setVisible(true);

		break;
	}
		default:
			break;	
		
	}
}


void LocalPicturePlayer::changeIconImage()
{
	Node *node = this->getChildByName("local picture player");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 
	node = layout->getChildByName("pic_shrink");
	ui::ImageView *img_shrink = static_cast<ui::ImageView*>(node);
	node = layout->getChildByName("pic_shrink_focus");
	ui::ImageView *img_shrink_focus = static_cast<ui::ImageView*>(node);	
		
	node = layout->getChildByName("pic_enlarge");
	ui::ImageView *img_enlarge = static_cast<ui::ImageView*>(node);	
	node = layout->getChildByName("pic_enlarge_focus");
	ui::ImageView *img_enlarge_focus = static_cast<ui::ImageView*>(node);
	
	node = layout->getChildByName("pic_play");
	ui::ImageView *img_play = static_cast<ui::ImageView*>(node);	
	node = layout->getChildByName("pic_play_focus");
	ui::ImageView *img_play_focus = static_cast<ui::ImageView*>(node);
		
	node = layout->getChildByName("pic_rotate");
	ui::ImageView *img_rotate = static_cast<ui::ImageView*>(node);	
	node = layout->getChildByName("pic_rotate_focus");
	ui::ImageView *img_rotate_focus = static_cast<ui::ImageView*>(node);
	
	node = layout->getChildByName("pic_delete");
	ui::ImageView *img_delete = static_cast<ui::ImageView*>(node);	
	node = layout->getChildByName("pic_delete_focus");
	ui::ImageView *img_delete_focus = static_cast<ui::ImageView*>(node);	   
		
	if(cur_icon == PICTURE_SHRINK)
	{
		img_shrink->setVisible(false);	
		img_shrink_focus->setVisible(true);
		
		img_enlarge->setVisible(true);	
		img_enlarge_focus->setVisible(false);
		img_play->setVisible(true);	
		img_play_focus->setVisible(false);
		img_rotate->setVisible(true);	
		img_rotate_focus->setVisible(false);			
		img_delete->setVisible(true);	
		img_delete_focus->setVisible(false);			
		
	}
	if(cur_icon == PICTURE_ENLARGE)
	{
		img_shrink->setVisible(true);	
		img_shrink_focus->setVisible(false);
		img_enlarge->setVisible(false);	
		img_enlarge_focus->setVisible(true);
		img_play->setVisible(true);	
		img_play_focus->setVisible(false);
		img_rotate->setVisible(true);	
		img_rotate_focus->setVisible(false);			
		img_delete->setVisible(true);	
		img_delete_focus->setVisible(false);
	}	
	if(cur_icon == PICTURE_PLAY)
	{
		img_shrink->setVisible(true);	
		img_shrink_focus->setVisible(false);
		img_enlarge->setVisible(true);	
		img_enlarge_focus->setVisible(false);
		img_play->setVisible(false);	
		img_play_focus->setVisible(true);
		img_rotate->setVisible(true);	
		img_rotate_focus->setVisible(false);			
		img_delete->setVisible(true);	
		img_delete_focus->setVisible(false);
	}	
	if(cur_icon == PICTURE_ROTATE)
	{
		img_shrink->setVisible(true);	
		img_shrink_focus->setVisible(false);
		img_enlarge->setVisible(true);	
		img_enlarge_focus->setVisible(false);
		img_play->setVisible(true);	
		img_play_focus->setVisible(false);
		img_rotate->setVisible(false);	
		img_rotate_focus->setVisible(true);			
		img_delete->setVisible(true);	
		img_delete_focus->setVisible(false);
	}		
	if(cur_icon == PICTURE_DELETE)
	{
		img_shrink->setVisible(true);	
		img_shrink_focus->setVisible(false);
		img_enlarge->setVisible(true);	
		img_enlarge_focus->setVisible(false);
		img_play->setVisible(true);	
		img_play_focus->setVisible(false);
		img_rotate->setVisible(true);	
		img_rotate_focus->setVisible(false);			
		img_delete->setVisible(false);	
		img_delete_focus->setVisible(true);
	}
}

void LocalPicturePlayer::pictureIconAction()
{
	CCMediaPlayer *player = CCMediaPlayer::getInstance();
	if(cur_icon == PICTURE_SHRINK)
	{	
		if(cur_zoom_time == 1)
		{
			player->zoom(MP_ZOOM_SCALE_1_8);
			cur_zoom_time = 0;
		}
		if(cur_zoom_time == 2)
		{
			player->zoom(MP_ZOOM_SCALE_1_4);
			cur_zoom_time = 1;
		}
		if(cur_zoom_time == 3)
		{
			player->zoom(MP_ZOOM_SCALE_1_2);
			cur_zoom_time = 2;
		}
		if(cur_zoom_time == 4)
		{
			player->zoom(MP_ZOOM_SCALE_1);
			cur_zoom_time = 3;
		}
		if(cur_zoom_time == 5)
		{
			player->zoom(MP_ZOOM_SCALE_2);
			cur_zoom_time = 4;
		}
		if(cur_zoom_time == 6)
		{
			player->zoom(MP_ZOOM_SCALE_4);
			cur_zoom_time = 5;
		}
	}
	if(cur_icon == PICTURE_ENLARGE)
	{
		if(cur_zoom_time == 0)
		{
			player->zoom(MP_ZOOM_SCALE_1_4);
			cur_zoom_time = 1;
		}
		if(cur_zoom_time == 1)
		{
			player->zoom(MP_ZOOM_SCALE_1_2);
			cur_zoom_time = 2;
		}
		if(cur_zoom_time == 2)
		{
			player->zoom(MP_ZOOM_SCALE_1);
			cur_zoom_time = 3;
		}
		if(cur_zoom_time == 3)
		{
			player->zoom(MP_ZOOM_SCALE_2);
			cur_zoom_time = 4;
		}
		if(cur_zoom_time == 4)
		{
			player->zoom(MP_ZOOM_SCALE_4);
			cur_zoom_time = 5;
		}
		if(cur_zoom_time == 5)
		{
			player->zoom(MP_ZOOM_SCALE_8);
			cur_zoom_time = 6;
		}		
	}	
	if(cur_icon == PICTURE_PLAY)
	{
		Node *node = this->getChildByName("local picture player");
		ui::Layout* layout = static_cast<ui::Layout*>(node); 
		layout->setVisible(false);		
		
		play_slide(cur_index);
		cur_index++;
		
		is_playing_slide = true;
		
		ui::Layout* layout1 = ui::Layout::create();
		layout1->setContentSize(Size(1920,1080));
		addChild(layout1,0,"local picture slide playing");
		addKeyListener(CC_CALLBACK_2(LocalPicturePlayer::onKeyPressed_slide, this), layout1);	
				
	}	
	if(cur_icon == PICTURE_ROTATE)
	{
		if(cur_rotate_degree == 0)
		{
			player->rotate(MP_DEGREE_270);
			cur_rotate_degree = 1;
		}
		
		if(cur_rotate_degree == 1)
		{
			player->rotate(MP_DEGREE_180);
			cur_rotate_degree = 2;
		}
		if(cur_rotate_degree == 2)
		{
			player->rotate(MP_DEGREE_90);
			cur_rotate_degree = 3;
		}
		if(cur_rotate_degree == 3)
		{
			player->rotate(MP_DEGREE_0);
			cur_rotate_degree = 0;
		}
		
	}		
	if(cur_icon == PICTURE_DELETE)
	{
		
	}
}

void LocalPicturePlayer::play_slide(int index)
{
	std::string path;
	path = pictureList.at(index);

	cur_zoom_time = 0;
	cur_rotate_degree = 0;
	
	CCMediaPlayer *player = CCMediaPlayer::getInstance();	
	player->stop();
	player->reset();
	player->setDataSource(path,MP_TYPE_PHOTO);
	player->prepareAsync() ;
}

