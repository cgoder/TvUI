#ifndef __CEPGSERVICE_H__
#define __CEPGSERVICE_H__

#include "CEpgEvent.h"
#include "CChannel.h"

class CEpgService
{
public:
	// CEpgService();
	// ~CEpgService();


	static CEpgService* getInstance(void);
	bool destoryInstance(void);

	bool creat(Channel ch);
	bool update(Channel ch);
	bool destory(Channel ch);
	unsigned int getEventCount(Channel ch);
	unsigned int getEventCount(Channel ch, unsigned long utcTime);
	bool getEventInfoByTime(unsigned short svcType, unsigned short svcNumber, unsigned long utcTime, EpgEvent& event);
	bool getEventScheduleStatus(EpgEvent& event);
	bool getEventPf(Channel ch, std::vector<EpgEvent>& events);
	bool getEventAll(Channel ch, unsigned int count, std::vector<EpgEvent>& events);
	bool getEventAll(Channel ch, unsigned int count, unsigned long utcTime, std::vector<EpgEvent>& events);
	bool getSchedules(std::vector<EpgSchedule>& schedules);

	bool getSchedulesView(std::vector<EpgSchedule>& schedules);
	bool getSchedulesRec(std::vector<EpgSchedule>& schedules);
	bool setScheduleView(Channel ch, EpgEvent event);
	bool setScheduleRec(Channel ch, EpgEvent event);
	bool cancelScheduleView(EpgSchedule schedule);
	bool cancelScheduleRec(EpgSchedule schedule);
	bool cancelScheduleView(Channel ch, EpgEvent event);
	bool cancelScheduleRec(Channel ch, EpgEvent event);
};


#endif // __CEPGSERVICE_H__
