#include <string>
#include <stdio.h>
#include "atvplayer.h"
#include "CChannelinner.h"
#include "CChannelManager.h"
#include "CPlayerService.h" //skytvmw UAPI
//#include "CEpgManager.h"


AtvPlayer::AtvPlayer()
{
	FUNC_ENTRY();
	_source = SKYTV_INPUT_SOURCE_ATV;
	_chIndexCur = 0;
	_chIndexOld = 0;
	_chManager = NULL;

	_chManager = new CChannelManager(_source);
	//assert(_chManager);
	_chIndexCur = _chIndexOld = _chManager->getLastChannel();

	// _chManager->showChannelList();

	FUNC_EXIT();
}

AtvPlayer::~AtvPlayer()
{
	FUNC_ENTRY();
	_chIndexCur = 0;
	_chIndexOld = 0;
	_chManager = NULL;
	_source = SKYTV_INPUT_SOURCE_ATV;

	if (_chManager) {
		delete _chManager;
	}
}

unsigned int AtvPlayer::getLastChannelIndex(void) {
	FUNC_ENTRY();
	return _chIndexCur;
}

CChannel* AtvPlayer::getCurChannel(void) {
	FUNC_ENTRY();
	return getChannel(_chIndexCur);
}

CChannel* AtvPlayer::getChannel(unsigned int chIndex) {
	FUNC_ENTRY();
	if (chIndex >= getChannelCount()) {
		return NULL;
	}
	return dynamic_cast<CChannel*>(getChannelManager()->getChannel(chIndex));
}

unsigned int AtvPlayer::getChannelCount(void)
{
	FUNC_ENTRY();
	return getChannelManager()->getChannelCount();
}

bool AtvPlayer::swapChannel(unsigned int firstChannelIndex, unsigned int secondChannelIndex) {
	FUNC_ENTRY();
	if ((firstChannelIndex >= getChannelCount()) || (secondChannelIndex >= getChannelCount())) {
		return NULL;
	}
	return getChannelManager()->swap(firstChannelIndex, secondChannelIndex);
}

bool AtvPlayer::playCur(void) {
	FUNC_ENTRY();
	return play(_chIndexCur);
}

bool AtvPlayer::playPrev(void) {
	FUNC_ENTRY();
	unsigned int count = getChannelCount();
	if (0 == count) {
		return false;
	}
	unsigned int tmpIndex = _chIndexCur;
	if (0 == tmpIndex) {
		tmpIndex = count - 1;
	}
	else {
		tmpIndex--;
	}
	_chIndexCur = tmpIndex;

	return play(tmpIndex);
}

bool AtvPlayer::playNext(void) {
	FUNC_ENTRY();
	unsigned int count = getChannelCount();
	if (0 == count) {
		return false;
	}
	unsigned int tmpIndex = _chIndexCur;
	if ((count - 1) == tmpIndex) {
		tmpIndex = 0;
	}
	else {
		tmpIndex++;
	}
	_chIndexCur = tmpIndex;

	return play(tmpIndex);
}

bool AtvPlayer::playBack(void)
{
	FUNC_ENTRY();
	unsigned int count = getChannelCount();
	if (0 == count) {
		return false;
	}

	_chIndexCur = _chIndexOld;

	return play(_chIndexOld);
}

bool AtvPlayer::play(unsigned int chIndex) {
	FUNC_ENTRY();
	if (chIndex >= getChannelCount()) {
		return false;
	}

	return playChannel(chIndex);
}

bool AtvPlayer::pause(bool freeze)
{
	FUNC_ENTRY();
	return stop(freeze);
}

bool AtvPlayer::stop(bool freeze)
{
	FUNC_ENTRY();
	CChannel* tmpCh = getCurChannel();
	if (!tmpCh) {
		return false;
	}

	return stopChannel(*tmpCh, freeze);
}

bool AtvPlayer::reset(void)
{
	FUNC_ENTRY();
	stop(false);
	_chIndexCur = 0;
	_chIndexOld = 0;
	return true;
}

bool AtvPlayer::setChannelStatus(unsigned int chIndex, SKYTV_CHANNEL_OPT_TYPE opt, bool status) {
	FUNC_ENTRY();
	if (chIndex >= getChannelCount()) {
		return false;
	}

	CChannelInner* tmpCh = getChannelManager()->getChannel(chIndex);
	if (NULL == tmpCh) {
		return false;
	}

	switch (opt)
	{
	case SKYTV_CHANNEL_OPT_FAV:
		if (status) {
			tmpCh->setFav(true);
		}
		else {
			tmpCh->setFav(true);
		}
		break;
	case SKYTV_CHANNEL_OPT_LOCK:
		if (status) {
			tmpCh->setLock(false);
		}
		else {
			tmpCh->setLock(true);
		}
		break;
	case SKYTV_CHANNEL_OPT_HIDE:
		if (status) {
			tmpCh->setHide(false);
		}
		else {
			tmpCh->setHide(true);
		}
		break;
	case SKYTV_CHANNEL_OPT_DEL:
		getChannelManager()->deletChannel(chIndex);
		break;
	default:
		break;
	}
	return true;
}

bool AtvPlayer::getAllFav(std::vector<CChannel*>& favCh) {
	FUNC_ENTRY();
	if (0 == getChannelCount()) {
		return false;
	}

	std::vector<CChannelInner*> allCh;
	getChannelManager()->getAllChannel(allCh);

	CChannelInner* tmpCh = NULL;
	std::vector<CChannelInner*>::iterator it = allCh.begin();
	for (it = allCh.begin(); it != allCh.end(); ++it)
	{
		tmpCh = *it;
		if (tmpCh->isFav()) {
			favCh.push_back(dynamic_cast<CChannel*>(tmpCh));
		}
	}
	return true;
}

bool AtvPlayer::playChannel(CChannel& ch) {
	FUNC_ENTRY();

	Channel tmpCh = ch.get();

	CPlayerService::getInstance()->play(tmpCh);
	return true;
}


bool AtvPlayer::stopChannel(CChannel& ch, bool freeze) {
	FUNC_ENTRY();
	Channel tmpCh = ch.get();
	if (freeze) {
		CPlayerService::getInstance()->setFreeze(true);
	} else {
		CPlayerService::getInstance()->setFreeze(false);
	}

	return CPlayerService::getInstance()->stop(tmpCh);
}

bool AtvPlayer::playChannel(unsigned int chIndex) {
	FUNC_ENTRY();
	CChannel* tmpCh = getChannel(chIndex);
	if (!tmpCh) {
		return false;
	}
	return playChannel(*tmpCh);
}

bool AtvPlayer::stopChannel(unsigned int chIndex, bool freeze) {
	FUNC_ENTRY();
	if (freeze) {
		CPlayerService::getInstance()->setFreeze(true);
	} else {
		CPlayerService::getInstance()->setFreeze(false);
	}
	return CPlayerService::getInstance()->stop(chIndex);
}

bool AtvPlayer::printfAllChannel(void) {
	FUNC_ENTRY();
	_chManager->showChannelList();
	return true;
}

CChannelManager* AtvPlayer::getChannelManager(void) {
	FUNC_ENTRY();
	return _chManager;
}
