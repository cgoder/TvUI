#ifndef __CEVENT_H__
#define __CEVENT_H__

#include <vector>
#include <string>

typedef struct EpgEvent {
	unsigned short networkId;
	unsigned short tsId;
	unsigned short serviceId;
	unsigned short eventId;
	unsigned short runningStatus;
	bool bFreeCA;
	bool bNvod;
	bool bSchedule;
	bool bScheduleRec;
	unsigned long startTime;
	unsigned long endTime;
	unsigned int duration;
	std::string eventName;
	std::string eventText;
} EpgEventStruct;

typedef struct EpgSchedule {
	std::string chName;
	EpgEvent event;
} EpgScheduleStruct;

typedef enum ScheduleEnum {
	E_SCHEDULE_UNKNOWN = 0,
	E_SCHEDULE_ALL,
	E_SCHEDULE_REMIDER,
	E_SCHEDULE_REC,
} ScheduleTypeEnum;


#endif // __CEVENT_H__
