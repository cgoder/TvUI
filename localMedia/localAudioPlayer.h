#ifndef __LOCAL_AUDIO_PLAYER__
#define __LOCAL_AUDIO_PLAYER__

#include "cocos2d.h"
#include "common/SkyLayer.h"
#include "ui/CocosGUI.h"
#include "rec/PVRUpdateProgressBar.h"
#include "rec/PVRUpdateTime.h"
#include "tvplayer/MediaPlayer.h"

USING_NS_CC;

enum AudioIcon{
    AUDIO_LAST,
    AUDIO_PLAY,
    AUDIO_NEXT
};

enum PlayStatus{
    PLAYING,
    PAUSED
};


class LocalAudioPlayer: public SkyLayer
{
public:
	LocalAudioPlayer();
	~LocalAudioPlayer();
	static cocos2d::Scene* createScene();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	virtual bool init();
	CREATE_FUNC(LocalAudioPlayer);
	
	void updateShowTime(int time_ms,RecordShowTimeType type);	
	void schUpdateProgressBar(float dt);
	void schUpdataCurTime(float dt);
	void schUpdataTotalTime(float dt);
	
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);	
	void changeIconImage();	
	void pictureIconAction();	
		
	void localAudioPlayerCallback(MP_MSG_e type, void* pUserData);
	void play(string& path);
	void play(std::vector<std::string> &m_audioListVec);
	void stop();
	void closeLayer();
	void play_internal(int index);
	
	void updateAudioInfo();	

	int Duration;
	int cur_time;	
	int cur_icon;
	
	PVRUpdateTime *play_time;
	PVRUpdateTime *total_time;
	
	std::vector<std::string> audioList;
	int cur_index;
	PlayStatus cur_status;
};



#endif//__LOCAL_AUDIO_PLAYER__
