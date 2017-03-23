#ifndef  _EVENT_MANAGER_H
#define  _EVENT_MANAGER_H
#include "EventDispacher_Type.h" 
#include "EventDispacher.h"


class EventDispacherManager
{
public:
	EventDispacherManager();
	~EventDispacherManager();
	static EventDispacherManager* EventManager_Creat(void *p);
	static EventDispacherManager* eventmanager;
	//static void EventCallBackFunction(EventType  EventType_Data, void*param1, void* ptr);
	static void EventCallBackFunction(EventType  EventType_Data, void*param1);
	void*pscence;
	EventType EventType_tmp;
};
#endif