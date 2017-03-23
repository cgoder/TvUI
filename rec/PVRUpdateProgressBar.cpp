#include "rec/PVRUpdateProgressBar.h"


bool PVRUpdateProgressBar::init()
{
	ui::LoadingBar *loadingbar = ui::LoadingBar::create(FileName);
	loadingbar->setAnchorPoint(Vec2(0, 0));
	loadingbar->setScale9Enabled(true);
	loadingbar->setContentSize(Size(1920,7));
    loadingbar->setPercent(80);
    loadingbar->setDirection(ui::LoadingBar::Direction::LEFT); 
	loadingbar->setPosition(pos);
	loadingbar->setZOrder(2);
	this->addChild(loadingbar,1,"progressbar");
	return true;
}
void PVRUpdateProgressBar::setProgressBarParam(const std::string &FileName, const Vec2 &pos)
{
	this->FileName = FileName;
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

void PVRUpdateProgressBar::UpdateProgressBar(int time_ms,int total_time_ms)
{
	Node *node = this->getChildByName("progressbar");
	ui::LoadingBar* loadingbar = static_cast<ui::LoadingBar*>(node); 
	float percent = (float)time_ms * 100 / (float)total_time_ms;
	loadingbar->setPercent(percent);	
}