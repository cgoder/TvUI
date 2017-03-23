#include <map>
#include <stdio.h>
#include "TvPlayer.h"
#include "dtvplayer.h"
#include "atvplayer.h"
#include "tv_common.h"
#include "CSystemService.h"

static skyTvMw* _gSkyTvMw = NULL;
static TvPlayer* _gPlayer = NULL;
static SKYTV_INPUT_SOURCE_TYPE _gInputSource = SKYTV_INPUT_SOURCE_UNKNOWN;

static TvPlayer* creatPlayerBySource(SKYTV_INPUT_SOURCE_TYPE source) {
	TvPlayer* player = NULL;
	switch (source) {
	case SKYTV_INPUT_SOURCE_ATV:
		player = dynamic_cast<TvPlayer*>(new AtvPlayer());
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
		player = dynamic_cast<TvPlayer*>(new DtvPlayer(source));
		break;
	case SKYTV_INPUT_SOURCE_HDMI1:
	case SKYTV_INPUT_SOURCE_HDMI2:
	case SKYTV_INPUT_SOURCE_HDMI3:
	case SKYTV_INPUT_SOURCE_HDMI4:
	default:
		player = NULL;//dynamic_cast<TvPlayer*>(new DtvPlayer(source));
		break;
	}
	return _gPlayer = player;
}

static bool destoryPlayerBySource(SKYTV_INPUT_SOURCE_TYPE source, TvPlayer* player) {
	if (player == NULL) {
		return false;
	}
	switch (source) {
	case SKYTV_INPUT_SOURCE_ATV:
		delete (dynamic_cast<AtvPlayer*>(player));
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
		delete (dynamic_cast<DtvPlayer*>(player));
		break;
	case SKYTV_INPUT_SOURCE_HDMI1:
	case SKYTV_INPUT_SOURCE_HDMI2:
	case SKYTV_INPUT_SOURCE_HDMI3:
	case SKYTV_INPUT_SOURCE_HDMI4:
	default:
		delete (dynamic_cast<DtvPlayer*>(player));
		break;
	}
	return true;
}

static bool releaseAll(void) {
	if (_gPlayer) {
		destoryPlayerBySource(_gInputSource, _gPlayer);
		_gPlayer = NULL;
	}
	_gInputSource = SKYTV_INPUT_SOURCE_UNKNOWN;
	return true;
}

skyTvMw* skyTvMw::getInstance(void) {
	if (NULL == _gSkyTvMw) {
		_gSkyTvMw = new skyTvMw();
		//assert(_gSkyTvMw);
		_gInputSource = _gSkyTvMw->getInputSource();
		_gPlayer = NULL;

		//for test
		_gSkyTvMw->setCountry(SKYTV_COUNTRY_CHINA);
		// _gSkyTvMw->setTimeZone(SKYTV_TIMEZONE_UTC_P8);
	}
	return _gSkyTvMw;
}

void skyTvMw::destoryInstance(void) {
	releaseAll();

	_gInputSource = SKYTV_INPUT_SOURCE_UNKNOWN;
	if (_gSkyTvMw) {
		delete _gSkyTvMw;
		_gSkyTvMw = NULL;
	}
}

SKYTV_INPUT_SOURCE_TYPE skyTvMw::getInputSource(void) {
	if (_gInputSource == SKYTV_INPUT_SOURCE_UNKNOWN) {
		return CSystemService::getCurInputSoruce();
	} else {
		return _gInputSource;
	}
}

bool skyTvMw::setInputSoruce(SKYTV_INPUT_SOURCE_TYPE input) {
	releaseAll();

	SKYTV_INPUT_SOURCE_TYPE cur = getInputSource();
	printf("\n oldInput:%d, new = %d \n", cur, input);

	_gInputSource = input;

	if (CSystemService::setInputSoruce(_gInputSource)) {
		TvPlayer* tmpPlayer = getPlayer();
		if (tmpPlayer) {
			_gPlayer = tmpPlayer;
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}

}

TvPlayer* skyTvMw::getPlayer(void) {
	if (_gPlayer) {
		return _gPlayer;
	} else {
		return creatPlayerBySource(_gInputSource);
	}
}

bool skyTvMw::destoryPlayer(void) {
	releaseAll();
	return true;
}


bool skyTvMw::setCountry(SKYTV_COUNTRY_E country) {
	return CSystemService::setCountry(country);
}

bool skyTvMw::setTimeZone(SKYTV_TIMEZONE_E tz) {
	return CSystemService::setTimeZone(tz);
}

bool skyTvMw::isDtvSource(void) {
	if ((_gInputSource >= SKYTV_INPUT_SOURCE_DTV) && (_gInputSource <= SKYTV_INPUT_SOURCE_DTV_MAX)) {
		return true;
	} else {
		return false;
	}
}

bool skyTvMw::isAtvSource(void) {
	if (_gInputSource == SKYTV_INPUT_SOURCE_ATV) {
		return true;
	} else {
		return false;
	}
}
bool skyTvMw::isTvSource(void) {
	if ((_gInputSource >= SKYTV_INPUT_SOURCE_ATV) && (_gInputSource <= SKYTV_INPUT_SOURCE_DTV_MAX)) {
		return true;
	} else {
		return false;
	}
}
