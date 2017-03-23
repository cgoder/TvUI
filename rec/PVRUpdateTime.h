#ifndef __PVR_UPDATE_TIME__
#define __PVR_UPDATE_TIME__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;


enum RecordShowTimeType{
	SHOW_TIME_CURSOR,
	SHOW_TIME_CURRENT,
	SHOW_TIME_TOTAL,
};

class PVRUpdateTime: public cocos2d::Layer
{
public:
	virtual bool init();	
	
	void updateShowTime(int cur_hour,int cur_min,int cur_sec);	
	
	void setLayoutPosition(const Vec2 &pos);
	
};
#endif//__PVR_UPDATE_TIME__
