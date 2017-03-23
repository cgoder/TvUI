#include <string>
#include <stdio.h>
#include "TvPlayer.h"
#include "CChannelinner.h"
#include "dtvplayer.h"
#include "atvplayer.h"
// TvPlayer::TvPlayer(SKYTV_INPUT_SOURCE_TYPE soureInput) {
// 	_chIndexCur = 0;
// 	_chIndexOld = 0;
// 	_source = soureInput;
// }

// TvPlayer::~TvPlayer() {

// 	// if (this) {
// 	// 	reset();
// 	// 	delete this;
// 	// 	this = NULL;
// 	// }
// }
//
unsigned int TvPlayer::getLastChannelIndex(void) {
	FUNC_ENTRY();
	if (_source >= SKYTV_INPUT_SOURCE_DTV_MAX ) {
		return 0;
	}
	return _chIndexCur;
}

CChannel* TvPlayer::getCurChannel(void) {
	FUNC_ENTRY();
	return getChannel(_chIndexCur);
}

CChannel* TvPlayer::getChannel(unsigned int chIndex) {
	FUNC_ENTRY();
	if (chIndex >= getChannelCount()) {
		return NULL;
	}
	DtvPlayer* dplayer = dynamic_cast<DtvPlayer*>(this);
	return dynamic_cast<CChannel*>(dplayer->getChannelManager()->getChannel(chIndex));
}

unsigned int TvPlayer::getChannelCount(void)
{
	FUNC_ENTRY();
	DtvPlayer* dplayer = dynamic_cast<DtvPlayer*>(this);
	return dplayer->getChannelManager()->getChannelCount();
}

bool TvPlayer::swapChannel(unsigned int firstChannelIndex, unsigned int secondChannelIndex) {
	FUNC_ENTRY();
	if ((firstChannelIndex >= getChannelCount()) || (secondChannelIndex >= getChannelCount())) {
		return NULL;
	}
	DtvPlayer* dplayer = dynamic_cast<DtvPlayer*>(this);
	return dplayer->getChannelManager()->swap(firstChannelIndex, secondChannelIndex);
}

bool TvPlayer::playCur(void) {
	FUNC_ENTRY();
	return play(_chIndexCur);
}

bool TvPlayer::playPrev(void) {
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

bool TvPlayer::playNext(void) {
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

bool TvPlayer::playBack(void)
{
	FUNC_ENTRY();
	unsigned int count = getChannelCount();
	if (0 == count) {
		return false;
	}

	_chIndexCur = _chIndexOld;

	return play(_chIndexOld);
}

bool TvPlayer::play(unsigned int chIndex) {
	FUNC_ENTRY();
	if (chIndex >= getChannelCount()) {
		return NULL;
	}


	DtvPlayer* dplayer = dynamic_cast<DtvPlayer*>(this);
	return dplayer->playChannel(chIndex);
}

bool TvPlayer::pause(bool freeze)
{
	FUNC_ENTRY();
	return stop(freeze);
}

bool TvPlayer::stop(bool freeze)
{
	FUNC_ENTRY();
	CChannel* tmpCh = getCurChannel();
	if (!tmpCh) {
		return false;
	}

	DtvPlayer* dplayer = dynamic_cast<DtvPlayer*>(this);
	return dplayer->stopChannel(*tmpCh, freeze);
}

bool TvPlayer::reset(void)
{
	FUNC_ENTRY();
	stop(false);
	_chIndexCur = 0;
	_chIndexOld = 0;
	return true;
}

bool TvPlayer::setChannelStatus(unsigned int chIndex, SKYTV_CHANNEL_OPT_TYPE opt, bool status) {
	FUNC_ENTRY();
	if (chIndex >= getChannelCount()) {
		return NULL;
	}


	CChannelInner* tmpCh = NULL;//_chManager->getChannel(chIndex);
	DtvPlayer* dplayer = dynamic_cast<DtvPlayer*>(this);
	tmpCh = dplayer->getChannelManager()->getChannel(chIndex);
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
		// _chManager->deletChannel(chIndex);
		dplayer->getChannelManager()->deletChannel(chIndex);
		break;
	default:
		break;
	}
	return true;
}

bool TvPlayer::getAllFav(std::vector<CChannel*>& favCh) {
	FUNC_ENTRY();
	if (0 == getChannelCount()) {
		return false;
	}

	std::vector<CChannelInner*> allCh;

	DtvPlayer* dplayer = dynamic_cast<DtvPlayer*>(this);
	dplayer->getChannelManager()->getAllChannel(allCh);

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
