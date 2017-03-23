#ifndef __LOCAL_PICTURE_PLAYER__
#define __LOCAL_PICTURE_PLAYER__

#include "cocos2d.h"
#include "common/SkyLayer.h"
#include "ui/CocosGUI.h"
#include "tvplayer/MediaPlayer.h"

USING_NS_CC;


enum PictueIcon{
    PICTURE_SHRINK,
    PICTURE_ENLARGE,
    PICTURE_PLAY,
    PICTURE_ROTATE,
    PICTURE_DELETE
};


class LocalPicturePlayer: public SkyLayer
{
public:
	LocalPicturePlayer();
	~LocalPicturePlayer();
	static cocos2d::Scene* createScene();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	virtual bool init();
	CREATE_FUNC(LocalPicturePlayer);		
	
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyPressed_slide(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void changeIconImage();	
	void pictureIconAction();		
		
	void localPicturePlayerCallback(MP_MSG_e type, void* pUserData);
	void play(string& path);
	void play(std::vector<std::string> &m_pictureListVec);
	void stop();
	void closeLayer();
	void play_slide(int index);
	
	
	int cur_icon;
	int cur_zoom_time;
	int cur_rotate_degree;
	
	std::vector<std::string> pictureList;
	int cur_index;
	bool is_playing_slide;
	
};



#endif//__LOCAL_PICTURE_PLAYER__
