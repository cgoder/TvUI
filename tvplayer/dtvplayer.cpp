#include <string>
#include <stdio.h>
#include "dtvplayer.h"
#include "CChannelinner.h"
#include "CChannelManager.h"
#include "CPlayerService.h" //skytvmw UAPI
#include "CEpgManager.h"


DtvPlayer::DtvPlayer(SKYTV_INPUT_SOURCE_TYPE signalType)
{
	FUNC_ENTRY();
	_source = signalType;
	if ((signalType >= SKYTV_INPUT_SOURCE_DTV_MAX) || (signalType < SKYTV_INPUT_SOURCE_ATV)) {
		_source = SKYTV_INPUT_SOURCE_DTV;
	}
	_chIndexCur = 0;
	_chIndexOld = 0;
	_chManager = NULL;

	_chManager = new CChannelManager(_source);
	//assert(_chManager);
	_chIndexCur = _chIndexOld = _chManager->getLastChannel();

	// _chManager->showChannelList();

	FUNC_EXIT();
}

DtvPlayer::~DtvPlayer()
{
	FUNC_ENTRY();
	_chIndexCur = 0;
	_chIndexOld = 0;
	_chManager = NULL;
	_source = SKYTV_INPUT_SOURCE_DTV;

	if (_chManager) {
		delete _chManager;
	}
}

unsigned int DtvPlayer::getLastChannelIndex(void) {
	FUNC_ENTRY();
	return _chIndexCur;
}

CChannel* DtvPlayer::getCurChannel(void) {
	FUNC_ENTRY();
	return getChannel(_chIndexCur);
}

CChannel* DtvPlayer::getChannel(unsigned int chIndex) {
	FUNC_ENTRY();
	if (chIndex >= getChannelCount()) {
		return NULL;
	}
	return dynamic_cast<CChannel*>(getChannelManager()->getChannel(chIndex));
}

unsigned int DtvPlayer::getChannelCount(void)
{
	FUNC_ENTRY();
	return getChannelManager()->getChannelCount();
}

bool DtvPlayer::swapChannel(unsigned int firstChannelIndex, unsigned int secondChannelIndex) {
	FUNC_ENTRY();
	if ((firstChannelIndex >= getChannelCount()) || (secondChannelIndex >= getChannelCount())) {
		return NULL;
	}
	return getChannelManager()->swap(firstChannelIndex, secondChannelIndex);
}

bool DtvPlayer::playCur(void) {
	FUNC_ENTRY();
	return play(_chIndexCur);
}

bool DtvPlayer::playPrev(void) {
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

bool DtvPlayer::playNext(void) {
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

bool DtvPlayer::playBack(void)
{
	FUNC_ENTRY();
	unsigned int count = getChannelCount();
	if (0 == count) {
		return false;
	}

	_chIndexCur = _chIndexOld;

	return play(_chIndexOld);
}

bool DtvPlayer::play(unsigned int chIndex) {
	FUNC_ENTRY();
	if (chIndex >= getChannelCount()) {
		return false;
	}

	return playChannel(chIndex);
}

bool DtvPlayer::pause(bool freeze)
{
	FUNC_ENTRY();
	return stop(freeze);
}

bool DtvPlayer::stop(bool freeze)
{
	FUNC_ENTRY();
	CChannel* tmpCh = getCurChannel();
	if (!tmpCh) {
		return false;
	}

	return stopChannel(*tmpCh, freeze);
}

bool DtvPlayer::reset(void)
{
	FUNC_ENTRY();
	stop(false);
	_chIndexCur = 0;
	_chIndexOld = 0;
	return true;
}

bool DtvPlayer::setChannelStatus(unsigned int chIndex, SKYTV_CHANNEL_OPT_TYPE opt, bool status) {
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
			tmpCh->setFav(false);
		}
		break;
	case SKYTV_CHANNEL_OPT_LOCK:
		if (status) {
			tmpCh->setLock(true);
		}
		else {
			tmpCh->setLock(false);
		}
		break;
	case SKYTV_CHANNEL_OPT_HIDE:
		if (status) {
			tmpCh->setHide(true);
		}
		else {
			tmpCh->setHide(false);
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

bool DtvPlayer::getAllFav(std::vector<CChannel*>& favCh) {
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

bool DtvPlayer::playChannel(CChannel& ch) {
	FUNC_ENTRY();

	Channel tmpCh = ch.get();

	CPlayerService::getInstance()->play(tmpCh);
	CEpgManager::getInstance()->start(ch.get());
	return true;
}


bool DtvPlayer::stopChannel(CChannel& ch, bool freeze) {
	FUNC_ENTRY();
	Channel tmpCh = ch.get();
	if (freeze) {
		CPlayerService::getInstance()->setFreeze(true);
	} else {
		CPlayerService::getInstance()->setFreeze(false);
	}
	CEpgManager::getInstance()->stop(ch.get());

	return CPlayerService::getInstance()->stop(tmpCh);
}

bool DtvPlayer::playChannel(unsigned int chIndex) {
	FUNC_ENTRY();
	CChannel* tmpCh = getChannel(chIndex);
	if (!tmpCh) {
		return false;
	}
	return playChannel(*tmpCh);
}

bool DtvPlayer::stopChannel(unsigned int chIndex, bool freeze) {
	FUNC_ENTRY();
	if (freeze) {
		CPlayerService::getInstance()->setFreeze(true);
	} else {
		CPlayerService::getInstance()->setFreeze(false);
	}
	return CPlayerService::getInstance()->stop(chIndex);
}

bool DtvPlayer::printfAllChannel(void) {
	FUNC_ENTRY();
	_chManager->showChannelList();
	return true;
}

CChannelManager* DtvPlayer::getChannelManager(void) {
	FUNC_ENTRY();
	return _chManager;
}
