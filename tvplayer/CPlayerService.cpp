#include "CPlayerService.h" //skytvmw UAPI

static CPlayerService* _gPlayerService = NULL;

// CPlayerService::CPlayerService() {

// }

// CPlayerService::~CPlayerService() {

// }
CPlayerService* CPlayerService::getInstance(void) {
	if (NULL == _gPlayerService) {
		_gPlayerService = new CPlayerService();
	}
	return _gPlayerService;
}

bool CPlayerService::destoryInstance(void) {
	if (_gPlayerService) {
		delete _gPlayerService;
		_gPlayerService = NULL;
	}
	return true;
}

bool CPlayerService::play(unsigned int chNo) {

	return true;
}

bool CPlayerService::stop(unsigned int chNo) {

	return true;
}

bool CPlayerService::pause(unsigned int chNo) {

	return stop(chNo);
}

bool CPlayerService::resume(unsigned int chNo) {

	return play(chNo);
}

bool CPlayerService::play(Channel& ch) {

	return true;
}

bool CPlayerService::stop(Channel& ch) {

	return stop(ch.physics.number);
}

bool CPlayerService::pause(Channel& ch) {

	return stop(ch.physics.number);
}

bool CPlayerService::resume(Channel& ch) {

	return play(ch);
}

bool CPlayerService::setFreeze(bool freeze) {

	return true;
}

bool CPlayerService::playFirst(void) {
	return true;
}
