#include <stdio.h>
#include "CChannelService.h"
#include "CChannelManager.h"

CChannelManager::CChannelManager(SKYTV_INPUT_SOURCE_TYPE inputSource)
{
	size_t size = channels.size();
	for (size_t i = 0; i < size; i++)
	{
		if (channels[i]) {
			delete channels[i];
		}
	}
	channels.clear();
	std::vector<CChannelInner*>().swap(channels);

	u32LastChIndex = 0;
	curSource = inputSource;
	init(curSource);
}

CChannelManager::~CChannelManager()
{
	size_t size = channels.size();
	for (size_t i = 0; i < size; i++)
	{
		if (channels[i]) {
			delete channels[i];
		}
	}
	channels.clear();
	std::vector<CChannelInner*>().swap(channels);
}

void CChannelManager::showChannelList(void) {
	Channel tmpCh;

	printf("\n##### Show Channel List begin... ####\n");
	unsigned int count = getChannelCount();
	for (unsigned int i = 0; i < count; ++i)
	{
		tmpCh = getChannelInfo(i);
		printf("\n[%s/%d]type:%d, svcid:%d/0x%04X, isEncrypted:%d, name:%s \n", tmpCh.logic.chNo.c_str(), tmpCh.physics.number, tmpCh.physics.serviceType, tmpCh.physics.serviceId, tmpCh.physics.serviceId, tmpCh.physics.services.isEncrypted, tmpCh.logic.chName.c_str());
	}
	printf("\n##### Show Channel List end... ####\n");
}

bool CChannelManager::init(SKYTV_INPUT_SOURCE_TYPE input) {
	std::vector<Channel> allCh;

	Channel tmpCh;
#if 1
	switch (input) {
	case SKYTV_INPUT_SOURCE_ATV:
		CChannelService::getInstance()->getAllChannel(SOURCE_TYPE_ATV, allCh);
		break;
	case SKYTV_INPUT_SOURCE_DTV:
	case SKYTV_INPUT_SOURCE_ATSC:
	case SKYTV_INPUT_SOURCE_ISDB:
		CChannelService::getInstance()->getAllChannel(SOURCE_TYPE_DTV, allCh);
		break;
	case SKYTV_INPUT_SOURCE_DVBC:
	case SKYTV_INPUT_SOURCE_DVBC2:
		CChannelService::getInstance()->getAllChannel(SOURCE_TYPE_DVBC, allCh);
		break;
	case SKYTV_INPUT_SOURCE_DVBS:
	case SKYTV_INPUT_SOURCE_DVBS2:
		CChannelService::getInstance()->getAllChannel(SOURCE_TYPE_DVBS, allCh);
		break;
	case SKYTV_INPUT_SOURCE_DVBT:
	case SKYTV_INPUT_SOURCE_DVBT2:
	case SKYTV_INPUT_SOURCE_DTMB:
		CChannelService::getInstance()->getAllChannel(SOURCE_TYPE_DVBT, allCh);
		break;
	case SKYTV_INPUT_SOURCE_HDMI1:
	case SKYTV_INPUT_SOURCE_HDMI2:
	case SKYTV_INPUT_SOURCE_HDMI3:
	case SKYTV_INPUT_SOURCE_HDMI4:
	default:
		break;
	}

	for (std::vector<Channel>::iterator i = allCh.begin(); i != allCh.end(); ++i) {
		tmpCh = *i;
		CChannelInner* ch = new CChannelInner();
		ch->set(tmpCh);
		addChannel(ch);
	}

#else
	if (!CChannelService::getInstance()->getAllChannel(allCh)) {
		return false;
	}

	for (std::vector<Channel>::iterator i = allCh.begin(); i != allCh.end(); ++i)
	{
		tmpCh = *i;
		{
			switch (input) {
			case SKYTV_INPUT_SOURCE_ATV:
				if (SOURCE_TYPE_ATV == tmpCh.physics.source) {
					CChannelInner* ch = new CChannelInner();
					ch->set(tmpCh);
					addChannel(ch);
				}
				break;
			case SKYTV_INPUT_SOURCE_DTV:
			case SKYTV_INPUT_SOURCE_DVBC:
			case SKYTV_INPUT_SOURCE_DVBC2:
			case SKYTV_INPUT_SOURCE_DVBS:
			case SKYTV_INPUT_SOURCE_DVBS2:
			case SKYTV_INPUT_SOURCE_DVBT:
			case SKYTV_INPUT_SOURCE_DVBT2:
			case SKYTV_INPUT_SOURCE_DTMB:
			case SKYTV_INPUT_SOURCE_ATSC:
			case SKYTV_INPUT_SOURCE_ISDB:
				if ((SOURCE_TYPE_DTV == tmpCh.physics.source) || (SOURCE_TYPE_ATV == tmpCh.physics.source)) {
					CChannelInner* ch = new CChannelInner();
					ch->set(tmpCh);
					addChannel(ch);
				}
				break;
			case SKYTV_INPUT_SOURCE_HDMI1:
			case SKYTV_INPUT_SOURCE_HDMI2:
			case SKYTV_INPUT_SOURCE_HDMI3:
			case SKYTV_INPUT_SOURCE_HDMI4:
			default:
				break;
			}
		}
	}
#endif

	unsigned int tmpIndex = 0;
	CChannelService::getInstance()->getCurrentChannel(tmpCh);
	if (findChannel(tmpCh, tmpIndex)) {
		u32LastChIndex = tmpIndex;
	}
	printf("\n\n\n########## u32LastChIndex:%d #############\n\n\n\n", u32LastChIndex);
	return true;
}

bool CChannelManager::addChannel(CChannelInner* ch) {
	Channel tmpCh = ch->get();
	//for test
	// if ((!tmpCh.physics.services.isEncrypted) && (tmpCh.physics.serviceType != SERVICE_TYPE_ATV)) {
	// 	channels.insert(channels.begin(), ch);
	// }
	// else
	{
		channels.push_back(ch);
	}
	return true;
}

bool CChannelManager::deletChannel(CChannelInner* ch)
{
	if (channels.empty()) {
		return false;
	}
	std::vector<CChannelInner*>::iterator it = channels.begin();
	for (it = channels.begin(); it != channels.end(); ++it)
	{
		CChannelInner* tmpCh = *it;
		if (ch->getName() == tmpCh->getName()) {
			channels.erase(it);
		}
	}
	return true;
}

bool CChannelManager::deletChannel(unsigned int chIndex)
{
	if (channels.empty()) {
		return false;
	}
	if (chIndex >= channels.size()) {
		return false;
	}

	std::vector<CChannelInner*>::iterator it = channels.begin() + chIndex;
	channels.erase(channels.begin() + chIndex);

	return true;
}


Channel& CChannelManager::getChannelInfo(unsigned int chIndex) {
	//if (channels.empty()) {
	//	return NULL;
	//}
	//if (chIndex > channels.size()) {
	//	return NULL;
	//}
	return channels[chIndex]->get();
}

CChannelInner* CChannelManager::getChannel(unsigned int chIndex) {
	if (channels.empty()) {
		return NULL;
	}
	if (chIndex > channels.size()) {
		return NULL;
	}
	return channels[chIndex];
}

bool CChannelManager::getAllChannel(std::vector<CChannelInner*>& allCh)
{
	allCh = channels;
	return true;
}

bool CChannelManager::swap(unsigned int firstChannelIndex, unsigned int secondChannelIndex) {
	unsigned int count = channels.size();

	if ((firstChannelIndex > count) || (secondChannelIndex > count)) {
		return false;
	}

	std::swap(channels[firstChannelIndex], channels[secondChannelIndex]);

	return true;
}

bool CChannelManager::sort(SortType sortType)
{
	unsigned int i = 0;
	CChannelInner* tmpCh;
	std::vector<CChannelInner*>::iterator it = channels.begin();
	for (it = channels.begin(), i = 0; it != channels.end(); ++it)
	{
		tmpCh = *it;

		char tmpString[32] = {0};
		sprintf(tmpString, "%c", i + 1);
		tmpCh->setNo(tmpString);
	}
	return true;
}

bool CChannelManager::findChannel(Channel ch, unsigned int& chIndex) {
	Channel tmpCh;
	unsigned int tmpIndex = 0;
	for (std::vector<CChannelInner*>::iterator i = channels.begin(); i != channels.end(); ++i)
	{
		tmpCh = (*i)->get();
		if ((ch.physics.number == tmpCh.physics.number)
		        && (ch.physics.serviceType == tmpCh.physics.serviceType))
		{
			chIndex = tmpIndex;
			return true;
		}
		tmpIndex++;
	}
	chIndex = tmpIndex;
	return false;
}
