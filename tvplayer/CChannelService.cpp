#include "CChannelService.h" //skytvmw UAPI
#include "CChannel.h"
#include <stdio.h>

#define CH_MAX (32)

static CChannelService* _gChannelService = NULL;

// CChannelService::CChannelService() {

// }

// CChannelService::~CChannelService() {

// }

CChannelService* CChannelService::getInstance(void) {
	if (NULL == _gChannelService) {
		_gChannelService = new CChannelService();
	}
	return _gChannelService;

}

bool CChannelService::destoryInstance(void) {
	if (_gChannelService) {
		delete _gChannelService;
		_gChannelService = NULL;
	}
	return true;
}

unsigned int CChannelService::getAllChannelCount(void) {

	return CH_MAX;
}

unsigned int CChannelService::getChannelCount(ServiceType chType) {

	return CH_MAX;
}

unsigned int CChannelService::getChannelCount(SourceType source) {

	return CH_MAX;
}

bool CChannelService::getAllChannel(ServiceType chType, std::vector<Channel>& channels) {
	return getAllChannel(channels);
}

bool CChannelService::getAllChannel(SourceType source, std::vector<Channel>& channels) {
	return getAllChannel(channels);
}

bool CChannelService::getAllChannel(std::vector<Channel>& channels) {

	for (int i = 0; i < CH_MAX; ++i) {
		Channel tmpCh;
		std::string chName("SKYTV-Test ");
		char tmpS[8] = {0};
		sprintf(tmpS, "%d", i + 1);
		chName.append(tmpS);
		tmpCh.logic.chName = chName;
		tmpCh.logic.chNo = tmpS;
		tmpCh.logic.isDelete = false;
		tmpCh.logic.isFavorite = false;
		tmpCh.logic.isHide = false;
		tmpCh.logic.isLock = false;
		tmpCh.physics.source = SOURCE_TYPE_DTV;
		tmpCh.physics.serviceId = i + 1;
		channels.push_back(tmpCh);
	}

	return true;
}

bool CChannelService::getChannelByIndex(unsigned int index, Channel& channel) {

	std::string chName("SKYTV-Test ");
	char tmpS[8] = {0};
	sprintf(tmpS, "%d", index + 1);
	chName.append(tmpS);
	channel.logic.chName = chName;
	channel.logic.chNo = tmpS;
	channel.logic.isDelete = false;
	channel.logic.isFavorite = false;
	channel.logic.isHide = false;
	channel.logic.isLock = false;

	channel.physics.source = SOURCE_TYPE_DTV;
	channel.physics.serviceId = index + 1;

	return true;
}

bool CChannelService::getCurrentChannel(Channel& channel) {
	getChannelByIndex(0, channel);
	return true;
}
