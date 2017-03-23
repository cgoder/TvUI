#ifndef __PVR_UI_H__
#define __PVR_UI_H__

#include "cocos2d.h"
#include "common/SkyLayer.h"
#include "ui/CocosGUI.h"
#include "rec/PVRUpdateProgressBar.h"
#include "rec/PVRUpdateTime.h"
//#include "rec/PVRVideoPlayer.h"
#include "tvplayer/TvPlayer.h"
#include "tvplayer/CCPvrManager.h"


#include "rec/PVRRecordDB.h"


USING_NS_CC;





enum RecordMsgDialogType{
	RECORD_DIALOG_STOP_RECORDING,
	RECORD_DIALOG_RECORDING_COMPLETE,
	RECORD_DIALOG_CHANGE_CHANNEL,
	RECORD_DIALOG_USB_FULL
};


enum RecordMsgBoxType{
	RECORD_BOX_RECORDING_COMPLETE,
	RECORD_BOX_INVALID_OPERATION,
	RECORD_BOX_THUMBNAIL
};



class PVRUI :  public SkyLayer
{
public:
	PVRUI();
	~PVRUI();
    static cocos2d::Scene* createScene();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	virtual bool init();
	CREATE_FUNC(PVRUI);   
	
	void showInvalidOperationInRecoding();
	
	void updateShowTime(int time_ms,RecordShowTimeType type);	
	
	void schUpdateProgressBar(float dt);
	void schUpdataCursorTime(float dt);
	void schUpdataCurTime(float dt);
	void schUpdataRecordingState(float dt);
	
	
	void UpdataTotalTime();
	
	void addMsgDialogPanel(RecordMsgDialogType type);
	void addProgramRecord();
	void addPauseIcon();
	
	void stopRecoding();
	void recodingComplete();
	void changeChannelInRecoding();
	
	void onKeyPressed_stopRecoding(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyPressed_recodingComplete(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyPressed_changeChannelInRecoding(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyPressed_ProgramRecord(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);		
	void onKeyPressed_PauseRecording(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyPressed_recodingUsbFull(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
		
		
	void startRecord();		
	void stopRecord();
	void schStartPlayBack(float dt);
	void pausePlayback();
	void resumePlayback();	
	void stopPvr();
	
	
	PVRUpdateTime *cursor_time1;
	PVRUpdateTime *cursor_time2;
	PVRUpdateTime *play_time;
	PVRUpdateTime *total_time;
	
	std::string lastRecodingFileName;


	int total_rec_ms;
	int total_play_ms;
	

	PVRRecordDB* recordDB;
	PVRRecordInfo cur_info;
	
	bool usb_pop_flag;
};


#endif //__PVR_UI_H__