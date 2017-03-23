#include "rec/PVRUpdateTime.h"


bool PVRUpdateTime::init()
{
	std::string cur_hour = StringUtils::format("%ld", 0);
	std::string cur_minute = StringUtils::format("%ld", 18);
	std::string cur_second = StringUtils::format("%ld", 55);
		
	ui::Layout* layout = ui::Layout::create();
	layout->setContentSize(Size(165,42));		
	
	auto label = Label::createWithTTF(cur_hour, "general/SourceHanSansTWHK-Light.ttf", 28);
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	//label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(45, 21));
	layout->addChild(label,1,"cur hour");
	
	label = Label::createWithTTF(":", "general/SourceHanSansTWHK-Light.ttf", 28);
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	//label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(64, 21));
	layout->addChild(label);
	
	label = Label::createWithTTF(cur_minute, "general/SourceHanSansTWHK-Light.ttf", 28);
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	//label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(82, 21));
	layout->addChild(label,1,"cur minute");
	
	label = Label::createWithTTF(":", "general/SourceHanSansTWHK-Light.ttf", 28);
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	//label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(102, 21));
	layout->addChild(label);
	
	label = Label::createWithTTF(cur_second, "general/SourceHanSansTWHK-Light.ttf", 28);
	label->setColor(Color3B(0x33, 0x33, 0x33));	
	//label->setAlignment(TextHAlignment::LEFT);
	label->setPosition(Vec2(119, 21));
	layout->addChild(label,1,"cur second");
	
	this->addChild(layout,1,"time layout");
	return true;
}


void PVRUpdateTime::updateShowTime(int cur_hour,int cur_min,int cur_sec)
{
	std::string hour = StringUtils::format("%ld", cur_hour);
	std::string minute = StringUtils::format("%ld", cur_min);
	std::string second = StringUtils::format("%ld", cur_sec);
	
	Node *node = this->getChildByName("time layout");
	ui::Layout* layout = static_cast<ui::Layout*>(node); 
			
	node = layout->getChildByName("cur second");
	Label *label = static_cast<Label*>(node); 
	label->setString(second);
	
	node = layout->getChildByName("cur minute");
	label = static_cast<Label*>(node); 
	label->setString(minute);
	
	node = layout->getChildByName("cur hour");
	label = static_cast<Label*>(node); 
	label->setString(hour);
	
	
}
void PVRUpdateTime::setLayoutPosition(const Vec2 &pos)
{
	Node *node = this->getChildByName("time layout");
	ui::Layout* layout = static_cast<ui::Layout*>(node);
	layout->setPosition(pos);
}
