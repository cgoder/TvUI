#include "CSystemService.h" //skytvmw UAPI

CSystemService::CSystemService() {

}

CSystemService::~CSystemService() {

}

bool CSystemService::setInputSoruce(SKYTV_INPUT_SOURCE_TYPE input) {

	return true;
}

SKYTV_INPUT_SOURCE_TYPE CSystemService::getCurInputSoruce(void) {
	SKYTV_INPUT_SOURCE_TYPE source = SKYTV_INPUT_SOURCE_DTV;
	return source;
}

unsigned long CSystemService::getClock(void) {
	return 12345678;
}

bool CSystemService::getLocalTime(struct tm& time) {
	FUNC_ENTRY();

	return 12345678;
}

bool CSystemService::setCountry(SKYTV_COUNTRY_E country) {
	return true;
}

bool CSystemService::setTimeZone(SKYTV_TIMEZONE_E tz) {
	return true;
}
