#ifndef __LOCAL_VIDEO_PLAYER__
#define __LOCAL_VIDEO_PLAYER__

#include "cocos2d.h"
#include "common/SkyLayer.h"
#include "ui/CocosGUI.h"
#include "rec/PVRUpdateProgressBar.h"
#include "rec/PVRUpdateTime.h"
#include "tvplayer/MediaPlayer.h"

USING_NS_CC;
class LocalVideoPlayer: public SkyLayer
{
public:
	LocalVideoPlayer();
//	LocalVideoPlayer(string& path,MP_TYPE_e type);
	~LocalVideoPlayer();
	static cocos2d::Scene* createScene();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	virtual bool init();
	CREATE_FUNC(LocalVideoPlayer);
		
	void updateShowTime(int time_ms,RecordShowTimeType type);	
	void schUpdateProgressBar(float dt);
	void schUpdataCursorTime(float dt);
	void schUpdataCurTime(float dt);
	
	void schUpdataTotalTime(float dt);	
	
	void addPauseIcon();
	void onKeyPressed_PausePlaying(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);				
	void onKeyPressed_PlayPanel(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void closeLayer();
		
	void localVideoPlayerCallback(MP_MSG_e type, void* pUserData);
	void play(string& path);
	void stop();
	
	void play_pvr(string filename);
	void stop_pvr();
		
	PVRUpdateTime *cursor_time1;
	PVRUpdateTime *cursor_time2;
	PVRUpdateTime *play_time;
	PVRUpdateTime *total_time;
	
	int Duration;
	int cur_time;	
	bool is_pvr;
};



#endif//__LOCAL_VIDEO_PLAYER__
