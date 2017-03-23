#ifndef __CSCHEDULEMANAGER_H__
#define __CSCHEDULEMANAGER_H__

#include <vector>
// #include <map>
// #include "CChannel.h"
#include "CEpgEvent.h"

class CScheduleManager
{
public:
	// CScheduleManager();
	// ~CScheduleManager();

	static CScheduleManager* getInstance(void);
	bool destoryInstance(void);

	bool getScheduleAll(std::vector<EpgSchedule>& schedules);

	bool getScheduleView(std::vector<EpgSchedule>& schedules);
	bool setScheduleView(Channel ch, EpgEvent event);
	bool cancelScheduleView(EpgSchedule schedule);
	bool cancelScheduleView(Channel ch, EpgEvent event);

	bool getScheduleRec(std::vector<EpgSchedule>& schedules);
	bool setScheduleRec(Channel ch, EpgEvent event);
	bool cancelScheduleRec(EpgSchedule schedule);
	bool cancelScheduleRec(Channel ch, EpgEvent event);
};


#endif // __CSCHEDULEMANAGER_H__
