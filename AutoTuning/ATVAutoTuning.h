#ifndef  _AUTO_TUNING_ATV_H_
#define  _AUTO_TUNING_ATV_H_
#include "cocos2d.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h" 
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
#include "common/common.h"
#include "common/SkyLayer.h"

#include "common/BtnFocusLayer.h"
#include "skyscanapi/skyScanUiApi.h"
#include "AutoTuning/AutoTuning.h"
class ATVAutoTuning :
	public AutoTuning
{
public:
	ATVAutoTuning();
	~ATVAutoTuning();
	virtual bool init();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node,int type = 0);

	// implement the "static create()" method manually
	CREATE_FUNC(ATVAutoTuning);
	
protected:
	void initATVAutoTuning();
	void onBtnScan(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
protected:

};
#endif

