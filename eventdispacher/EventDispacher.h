#ifndef  _EVENT_DISPACHER_H
#define  _EVENT_DISPACHER_H

#include "EventDispacher_Type.h" 


class EventDispacher
{
public:
	EventDispacher();
	~EventDispacher();
	static EventDispacher* GetEventDispacherInstance(void);
	//virtual void RegisterEventDispacher(EventCallBack callback, void*  param1,void *p);
//	void *ptr_tmp;
	virtual void RegisterEventDispacher(EventCallBack callback, void*  param1);
	EventCallBack mCallback;
	static EventDispacher* pInstance;


};
#endif