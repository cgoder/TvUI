#include"EventDispacher.h"

EventDispacher* EventDispacher::pInstance = nullptr;

EventDispacher::EventDispacher()
{
	return;
}

EventDispacher::~EventDispacher()
{
	return;
}

EventDispacher *EventDispacher::GetEventDispacherInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new EventDispacher;

	}
	return pInstance;
}

void EventDispacher::RegisterEventDispacher(EventCallBack callback, void*  ptr)
{
	//ptr_tmp = ptr;
	mCallback = callback;
	return;
}