#include "CChannel.h"


CChannel::CChannel()
{
	channel.logic.chNo = "";
	channel.logic.chName = "";
	channel.logic.isFavorite = false;
	channel.logic.isLock = false;
	channel.logic.isHide = false;
	channel.logic.isDelete = false;

	channel.physics.source = SOURCE_TYPE_UNKNOWN;
	channel.physics.serviceType = SERVICE_TYPE_UNKNOWN;
	channel.physics.serviceId = 0x1fff;
	channel.physics.networkId = 0x1fff;
	channel.physics.tsId = 0x1fff;
	channel.physics.pmtPid = 0x1fff;
	channel.physics.serviceName = channel.logic.chName;
	channel.physics.eventPf = NULL;
	channel.physics.eventAll = NULL;
	channel.physics.services.isEncrypted = false;
	channel.physics.services.ecmPid = 0x1fff;
	channel.physics.services.videoPid = 0x1fff;
	channel.physics.services.videoType = VIDEO_TYPE_UNKNOWN;
	channel.physics.services.pcrPid = 0x1fff;
	channel.physics.services.audioCount = 0;
	channel.physics.services.audioList = NULL;
}

CChannel::~CChannel()
{
	if (channel.physics.eventPf) {
		delete channel.physics.eventPf;
		channel.physics.eventPf = NULL;
	}
	if (channel.physics.eventAll) {
		delete channel.physics.eventAll;
		channel.physics.eventAll = NULL;
	}
	if (channel.physics.services.audioList) {
		delete channel.physics.services.audioList;
		channel.physics.services.audioList = NULL;
	}
}

