#ifndef __PVR_UPDATE_PROGRESSBAR__
#define __PVR_UPDATE_PROGRESSBAR__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class PVRUpdateProgressBar: public cocos2d::Layer
{
public:
//	PVRUpdateProgressBar(const std::string &FileName,const Vec2 &pos);
//	~PVRUpdateProgressBar();
	virtual bool init();
	
	void setProgressBarParam(const std::string &FileName,const Vec2 &pos);
	void UpdateProgressBar(int time_ms,int total_time_ms);	
	
	std::string FileName;
	Vec2 pos;
};



#endif //__PVR_UPDATE_PROGRESSBAR__