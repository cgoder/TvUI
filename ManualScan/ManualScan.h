#ifndef __MANUALSCAN_SCENE_H__
#define __MANUALSCAN_SCENE_H__

#include "cocos2d.h"
#include "ui/UIImageView.h"
#include "ui/UIListView.h"
#include "common/common.h"
#include "common/SkyLayer.h"
#include "ManualScan/ATV_ManualScan.h"
#include "ManualScan/DVBC_ManualScan.h"
#include "ManualScan/DVBT_ManualScan.h"
#include "skyscanapi/skyScanType.h"
USING_NS_CC;
using namespace ui;



class Manual_Scan : public SkyLayer
{
public:
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
};

#endif // __HELLOWORLD_SCENE_H__
