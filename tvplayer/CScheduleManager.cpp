#include "CEpgService.h"
#include "CSystemService.h"
#include "CScheduleManager.h"

#define DEFAULT_EPG_CACHE_NUM	(10)

static CScheduleManager* _gScheduleManager = NULL;

// CScheduleManager::CScheduleManager() {

// }

// CScheduleManager::~CScheduleManager() {

// }

CScheduleManager* CScheduleManager::getInstance(void) {
	if (NULL == _gScheduleManager) {
		_gScheduleManager = new CScheduleManager();
	}
	return _gScheduleManager;
}

bool CScheduleManager::destoryInstance(void) {

	if (_gScheduleManager) {
		delete _gScheduleManager;
		_gScheduleManager = NULL;
	}
	return true;
}


bool CScheduleManager::getScheduleAll(std::vector<EpgSchedule>& schedules) {
	return CEpgService::getInstance()->getSchedules(schedules);
}

bool CScheduleManager::getScheduleView(std::vector<EpgSchedule>& schedules) {
	return CEpgService::getInstance()->getSchedulesView(schedules);
}

bool CScheduleManager::getScheduleRec(std::vector<EpgSchedule>& schedules) {
	return CEpgService::getInstance()->getSchedulesRec(schedules);
}

bool CScheduleManager::setScheduleView(Channel ch, EpgEvent event) {
	return CEpgService::getInstance()->setScheduleView(ch, event);
}

bool CScheduleManager::setScheduleRec(Channel ch, EpgEvent event) {
	return CEpgService::getInstance()->setScheduleRec(ch, event);
}

bool CScheduleManager::cancelScheduleView(EpgSchedule schedule) {
	return CEpgService::getInstance()->cancelScheduleView(schedule);
}

bool CScheduleManager::cancelScheduleRec(EpgSchedule schedule) {
	return CEpgService::getInstance()->cancelScheduleRec(schedule);
}

bool CScheduleManager::cancelScheduleView(Channel ch, EpgEvent event) {
	return CEpgService::getInstance()->cancelScheduleView(ch, event);
}

bool CScheduleManager::cancelScheduleRec(Channel ch, EpgEvent event) {
	return CEpgService::getInstance()->cancelScheduleRec(ch, event);
}
