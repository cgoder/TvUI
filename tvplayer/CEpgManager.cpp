#include "CEpgService.h"
#include "CSystemService.h"
#include "CEpgManager.h"
// #include <iostream>
// #include <sstream>
#include <string>
#include <stdio.h>

#define FLAG_NO_CACHE	(1)

#define DEFAULT_EPG_CACHE_NUM	(10)

static CEpgManager* _gEpgManager = NULL;

// CEpgManager::CEpgManager() {

// }

// CEpgManager::~CEpgManager() {

// }

CEpgManager* CEpgManager::getInstance(void) {
	if (NULL == _gEpgManager) {
		_gEpgManager = new CEpgManager();
	}
	return _gEpgManager;
}

bool CEpgManager::destoryInstance(void) {
	std::map<unsigned short, std::vector<EpgEvent> >::iterator it;
	for (it = epgAll.begin(); it != epgAll.end();) {
		it->second.clear();
		std::vector<EpgEvent>().swap(it->second);
		epgAll.erase(it++);
	}
	// for (it = epgPf.begin(); i != epgPf.end();)
	// {
	// 	stop(it->first);
	// 	it->second.clear();
	// 	std::vector<EpgEvent>().swap(it->second);
	// 	epgPf.erase(it++);
	// }

	if (_gEpgManager) {
		delete _gEpgManager;
		_gEpgManager = NULL;
	}
	return true;
}

bool CEpgManager::start(Channel ch) {
	if (ch.physics.serviceId == 0x1FFF) {
		return false;
	}
#if FLAG_NO_CACHE
#else
	unsigned int u32Time = CSystemService::getUTCClock();

	std::pair< std::map<unsigned short, std::vector<EpgEvent> >::iterator, bool > ret;
	std::map<unsigned short, std::vector<EpgEvent> >::iterator it = epgAll.find(ch.physics.serviceId);
	if (it == epgAll.end()) {
		std::vector<EpgEvent> tmpVct;
		ret = epgAll.insert(std::pair<unsigned short, std::vector<EpgEvent> >(ch.physics.serviceId, tmpVct));
		CEpgService::getInstance()->creat(ch);
		it = ret.first;

		CEpgService::getInstance()->getEventAll(ch, DEFAULT_EPG_CACHE_NUM, u32Time, it->second);
	} else {
		CEpgService::getInstance()->update(ch);
		if (!ret.second) {
			return false;
		}
		std::vector<EpgEvent>::iterator eIter = it->second.begin();
		for (; eIter != it->second.end();)
		{
			if (u32Time > (*eIter).endTime) {
				it->second.erase(eIter);
			}
			++eIter;
		}

		if (it->second.size() < 6) {
			printf("\n###### oho,get Epg again... #####\n");
			CEpgService::getInstance()->getEventAll(ch, DEFAULT_EPG_CACHE_NUM, u32Time, it->second);
		}

	}
#endif
	return true;
}

bool CEpgManager::stop(Channel ch) {
	if (ch.physics.serviceId == 0x1FFF) {
		return false;
	}
#if FLAG_NO_CACHE
#else
	std::map<unsigned short, std::vector<EpgEvent> >::iterator it = epgAll.find(ch.physics.serviceId);
	if (it != epgAll.end()) {
		CEpgService::getInstance()->destory(ch);

		// it->second.clear();
		// std::vector<EpgEvent>().swap(it->second);
		// epgAll.erase(it);
	}
#endif
	return true;
}

unsigned int CEpgManager::getEventCount(Channel ch) {
	if (ch.physics.serviceId == 0x1FFF) {
		return 0;
	}
#if FLAG_NO_CACHE
	return CEpgService::getInstance()->getEventCount(ch);
#else
	std::map<unsigned short, std::vector<EpgEvent> >::iterator it = epgAll.find(ch.physics.serviceId);
	if (it != epgAll.end()) {
		return it->second.size();
	}
	return 0;
#endif
}

unsigned int CEpgManager::getEventCount(Channel ch, unsigned long utcTime) {
	if (ch.physics.serviceId == 0x1FFF) {
		return false;
	}
#if FLAG_NO_CACHE
	unsigned int u32Time = CSystemService::getUTCClock();
	return CEpgService::getInstance()->getEventCount(ch, u32Time);
#else
	std::map<unsigned short, std::vector<EpgEvent> >::iterator it = epgAll.find(ch.physics.serviceId);
	if (it != epgAll.end()) {
		return it->second.size();
	} else {
		return 0;
	}
#endif
}

bool CEpgManager::getEventAll(Channel ch, std::vector<EpgEvent>& events) {
	if (ch.physics.serviceId == 0x1FFF) {
		return false;
	}

#if FLAG_NO_CACHE
	CEpgService::getInstance()->getEventAll(ch, 0, 0, events);
	return true;
#else
	std::map<unsigned short, std::vector<EpgEvent> >::iterator it = epgAll.find(ch.physics.serviceId);
	if (it != epgAll.end()) {
		events = it->second;
		return true;
	} else {
		return false;
	}
#endif
}

bool CEpgManager::getEventAll(Channel ch, unsigned int& needEpgCount, std::vector<EpgEvent>& events) {
	if (ch.physics.serviceId == 0x1FFF) {
		return false;
	}

#if FLAG_NO_CACHE
	unsigned int u32Time = CSystemService::getUTCClock();
	unsigned int u32EpgCount = 0;
	if (0 != needEpgCount) {
		u32EpgCount = needEpgCount;
	} else {
		u32EpgCount = getEventCount(ch, u32Time);
	}
	CEpgService::getInstance()->getEventAll(ch, u32EpgCount/*DEFAULT_EPG_CACHE_NUM*/, u32Time, events);
	needEpgCount = events.size();
	return true;
#else
	std::map<unsigned short, std::vector<EpgEvent> >::iterator it = epgAll.find(ch.physics.serviceId);
	if (it != epgAll.end()) {
		events = it->second;
		return true;
	} else {
		return false;
	}
#endif
}


bool CEpgManager::getEventAll(Channel ch, unsigned int& needEpgCount, unsigned long utcTime, std::vector<EpgEvent>& events) {
	if (ch.physics.serviceId == 0x1FFF) {
		return false;
	}

#if FLAG_NO_CACHE
	unsigned int u32Time = 0;
	unsigned int u32EpgCount = 0;
	if (0 != needEpgCount) {
		u32EpgCount = needEpgCount;
	} else {
		u32EpgCount = getEventCount(ch, u32Time);
	}
	if (0 != utcTime) {
		u32Time = utcTime;
	} else {
		u32Time = CSystemService::getUTCClock();
	}
	CEpgService::getInstance()->getEventAll(ch, u32EpgCount/*DEFAULT_EPG_CACHE_NUM*/, u32Time, events);
	needEpgCount = events.size();
	return true;
#else
	std::map<unsigned short, std::vector<EpgEvent> >::iterator it = epgAll.find(ch.physics.serviceId);
	if (it != epgAll.end()) {
		events = it->second;
		return true;
	} else {
		return false;
	}
#endif
}

bool CEpgManager::getEventPf(Channel ch, std::vector<EpgEvent>& events) {
	if (ch.physics.serviceId == 0x1FFF) {
		return false;
	}

	CEpgService::getInstance()->getEventPf(ch, events);

	// std::map<unsigned short, std::vector<EpgEvent> >::iterator it = epgPf.find(ch.physics.serviceId);
	// if (it == epgPf.end()) {
	// 	return false;
	// } else {
	// 	events = it->second;
	// 	return true;
	// }

	return true;
}
