#include "CEpgService.h" //skytvmw UAPI

// #define IEPG_MANAGER "mstar.IEpgManager"
#define EPG_EVENT_REMIDER	(1)// typedef enum EN_EPG_TIMER_EVENT_TYPE
#define EPG_EVENT_RECORDER	(2)

#define EVENT_NUM_MAX (10)

static CEpgService* _gEpgService = NULL;

// ToEPGTimerInfo();
// CreateEPGScheduleList();
// OnEPGUpdate();
// ConstructProgrameGuideListChannel();

// CEpgService::CEpgService() {
// 	CMstarService::getEpgManager()->enableEpgBarkerChannel();
// }

// CEpgService::~CEpgService() {
// 	CMstarService::getEpgManager()->disableEpgBarkerChannel();
// }

bool CEpgService::creat(Channel ch) {
	return true;
}

bool CEpgService::update(Channel ch) {

	return true;
}

bool CEpgService::destory(Channel ch) {

	return true;
}


CEpgService* CEpgService::getInstance(void) {
	if (NULL == _gEpgService) {
		_gEpgService = new CEpgService();
	}
	return _gEpgService;
}

bool CEpgService::destoryInstance(void) {
	if (_gEpgService) {
		delete _gEpgService;
		_gEpgService = NULL;
	}
	return true;
}

bool CEpgService::getEventInfoByTime(unsigned short svcType, unsigned short svcNumber, unsigned long utcTime, EpgEvent& event) {


	EpgEvent tmpEvent = {0};
	if (1) {
		// memset(&tmpEvent, 0, sizeof(EpgEvent));
		tmpEvent.startTime = 12345678;
		tmpEvent.endTime = 12345678;
		tmpEvent.duration = 10000;
		tmpEvent.eventName = "测试EPG";
		tmpEvent.eventId = 1024;
		tmpEvent.bFreeCA = false;
		tmpEvent.networkId = 0x1FFF;
		tmpEvent.eventText = "测试EPG详情说明";
		tmpEvent.networkId = 0x1FFF;
		tmpEvent.tsId = 0x1FFF;
		tmpEvent.serviceId = svcNumber;
		tmpEvent.runningStatus = 0;
		tmpEvent.bNvod = false;
		tmpEvent.bSchedule = false;
		tmpEvent.bScheduleRec = false;

		getEventScheduleStatus(tmpEvent);

		event = tmpEvent;
		return true;
	}

	return false;
}

bool CEpgService::getEventScheduleStatus(EpgEvent& event) {
	//get schedule list
	unsigned int u32EventCount = EVENT_NUM_MAX;
	for (unsigned int u16idx = 0; u16idx < u32EventCount; ++u16idx) {

	}
	return false;
}


unsigned int CEpgService::getEventCount(Channel ch) {
	return getEventCount(ch, 0);
}

unsigned int CEpgService::getEventCount(Channel ch, unsigned long utcTime) {
	if (ch.physics.source != SOURCE_TYPE_DTV) {
		return 0;
	}

	unsigned int u32EventCount = EVENT_NUM_MAX;
	return u32EventCount;
}

bool CEpgService::getEventPf(Channel ch, std::vector<EpgEvent>& events) {
	// _getPFEventSpecificInfo()

	return getEventAll(ch, 2, 0, events);
}

bool CEpgService::getEventAll(Channel ch, unsigned int count, std::vector<EpgEvent>& events) {
	return getEventAll(ch, count, 0, events);
}

bool CEpgService::getEventAll(Channel ch, unsigned int count, unsigned long utcTime, std::vector<EpgEvent>& events) {
	if (ch.physics.source != SOURCE_TYPE_DTV) {
		return false;
	}

	EpgEvent tmpEvent = {0};
	char tmpChar[8];
	for (int i = 0; i < EVENT_NUM_MAX; ++i)
	{
		tmpEvent.duration = 10000;
		tmpEvent.startTime = i;
		tmpEvent.endTime = tmpEvent.duration + i;
		sprintf(tmpChar, "%d", i);
		tmpEvent.eventName = "测试EPG";
		tmpEvent.eventName += tmpChar;
		tmpEvent.eventId = i;
		tmpEvent.bFreeCA = false;
		tmpEvent.networkId = 0x1FFF;
		tmpEvent.eventText = "测试EPG详情说明";
		tmpEvent.eventText += tmpChar;
		tmpEvent.networkId = 0x1FFF;
		tmpEvent.tsId = 0x1FFF;
		tmpEvent.serviceId = i;
		tmpEvent.runningStatus = 0;
		tmpEvent.bNvod = false;
		tmpEvent.bSchedule = false;
		tmpEvent.bScheduleRec = false;

		getEventScheduleStatus(tmpEvent);

		events.push_back(tmpEvent);
	}

	return true;
}

bool CEpgService::getSchedules(std::vector<EpgSchedule>& schedules) {

	EpgSchedule tmpSch = {0};
	char tmpChar[8];
	for (int i = 0; i < EVENT_NUM_MAX; ++i)
	{
		tmpSch.event.duration = 10000;
		tmpSch.event.startTime = i;
		tmpSch.event.endTime = tmpSch.event.duration + i;
		sprintf(tmpChar, "%d", i);
		tmpSch.event.eventName = "测试EPG";
		tmpSch.event.eventName += tmpChar;
		tmpSch.event.eventId = i;
		tmpSch.event.bFreeCA = false;
		tmpSch.event.networkId = 0x1FFF;
		tmpSch.event.eventText = "测试EPG详情说明";
		tmpSch.event.eventText += tmpChar;
		tmpSch.event.networkId = 0x1FFF;
		tmpSch.event.tsId = 0x1FFF;
		tmpSch.event.serviceId = i;
		tmpSch.event.runningStatus = 0;
		tmpSch.event.bNvod = false;
		tmpSch.event.bSchedule = true;
		tmpSch.event.bScheduleRec = false;
		tmpSch.chName = "测试频道";

		schedules.push_back(tmpSch);
	}
	return true;
}

bool CEpgService::getSchedulesView(std::vector<EpgSchedule>& schedules) {
	EpgSchedule tmpSch;
	char tmpChar[8];
	for (int i = 0; i < EVENT_NUM_MAX / 2; ++i)
	{
		tmpSch.event.duration = 10000;
		tmpSch.event.startTime = i;
		tmpSch.event.endTime = tmpSch.event.duration + i;
		sprintf(tmpChar, "%d", i);
		tmpSch.event.eventName = "测试EPG";
		tmpSch.event.eventName += tmpChar;
		tmpSch.event.eventId = i;
		tmpSch.event.bFreeCA = false;
		tmpSch.event.networkId = 0x1FFF;
		tmpSch.event.eventText = "测试EPG详情说明";
		tmpSch.event.eventText += tmpChar;
		tmpSch.event.networkId = 0x1FFF;
		tmpSch.event.tsId = 0x1FFF;
		tmpSch.event.serviceId = i;
		tmpSch.event.runningStatus = 0;
		tmpSch.event.bNvod = false;
		tmpSch.event.bSchedule = true;
		tmpSch.event.bScheduleRec = false;
		tmpSch.chName = "测试频道";

		schedules.push_back(tmpSch);
	}
	return true;
}

bool CEpgService::getSchedulesRec(std::vector<EpgSchedule>& schedules) {
	EpgSchedule tmpSch;
	char tmpChar[8];
	for (int i = 0; i < EVENT_NUM_MAX / 2; ++i)
	{
		tmpSch.event.duration = 10000;
		tmpSch.event.startTime = i;
		tmpSch.event.endTime = tmpSch.event.duration + i;
		sprintf(tmpChar, "%d", i);
		tmpSch.event.eventName = "测试EPG";
		tmpSch.event.eventName += tmpChar;
		tmpSch.event.eventId = i;
		tmpSch.event.bFreeCA = false;
		tmpSch.event.networkId = 0x1FFF;
		tmpSch.event.eventText = "测试EPG详情说明";
		tmpSch.event.eventText += tmpChar;
		tmpSch.event.networkId = 0x1FFF;
		tmpSch.event.tsId = 0x1FFF;
		tmpSch.event.serviceId = i;
		tmpSch.event.runningStatus = 0;
		tmpSch.event.bNvod = false;
		tmpSch.event.bSchedule = true;
		tmpSch.event.bScheduleRec = true;
		tmpSch.chName = "测试频道";

		schedules.push_back(tmpSch);
	}
	return true;
}

bool CEpgService::setScheduleView(Channel ch, EpgEvent event) {
	return false;
}

bool CEpgService::setScheduleRec(Channel ch, EpgEvent event) {
	return false;
}

bool CEpgService::cancelScheduleView(EpgSchedule schedule) {
	return false;
}

bool CEpgService::cancelScheduleRec(EpgSchedule schedule) {
	return false;
}

bool CEpgService::cancelScheduleView(Channel ch, EpgEvent event) {
	return false;
}

bool CEpgService::cancelScheduleRec(Channel ch, EpgEvent event) {
	return false;

}
