#include "EventManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "rec/PVRStartDialog.h"


#include "cocos2d.h"
USING_NS_CC;
EventDispacherManager* EventDispacherManager::eventmanager = nullptr;
//void *EventDispacherManager::pscence = nullptr;
EventDispacherManager::EventDispacherManager()
{

	return;
}
EventDispacherManager::~EventDispacherManager()
{
	eventmanager = nullptr;
	return;
}
EventDispacherManager* EventDispacherManager::EventManager_Creat(void *p)
{
	if (eventmanager == nullptr)
	{
		eventmanager = new EventDispacherManager;
		eventmanager->pscence = p;
		auto eventinstance = EventDispacher::GetEventDispacherInstance();
		if (eventinstance != nullptr)
		{
			log("\n EventManager_Creat%x \n", p);
			eventinstance->RegisterEventDispacher(EventCallBackFunction, eventmanager);

		}
	}

	return eventmanager;
}

//void EventDispacherManager::EventCallBackFunction(EventType  EventType_Data, void*param1,void *p)
void EventDispacherManager::EventCallBackFunction(EventType  EventType_Data, void*param1)
{
	eventmanager->EventType_tmp = EventType_Data;
	log("\n EventCallBackFunction %x \n", param1);
	log("\n++EventTypeout %d ++\n", EventType_Data);
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([&]
	{
		switch (eventmanager->EventType_tmp)
		{

		case ENUM_EPGTIMER_COUNTDOWN:
			PVRStartDialog::creatLayer((cocos2d::Node *)eventmanager->pscence);
			break;
		default:
			break;

		}

	});

}
