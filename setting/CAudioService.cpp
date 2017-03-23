/****************************************************************************
 * Notice:      Copyright (c) Skyworth.
 *              All rights reserved.
 * Owner:      zhangyamei@skyworth.com
 ****************************************************************************/
#include "../tvplayer/tv_common.h"
#include "mapi_types.h"
#include "CAudioService.h" //skytvmw UAPI

CAudioService::CAudioService() {

}

CAudioService::~CAudioService() {

}
void CAudioService::AudioServiceSetAutoVolume(bool value)
{
	
}
bool CAudioService::AudioServiceEnableMute(int32_t enMuteType)
{
	 return true;
}
bool CAudioService::AudioServiceGetAudioMuteFlag(void)
{
	return true;
}
bool CAudioService::AudioServiceDisableMute(int32_t enMuteType)
{
	return true;
}
uint8_t CAudioService::AudioServiceSetSurroundSound(uint32_t sound)
{
	return true;
}

void CAudioService::AudioServiceSetDigitalOut(int32_t mode)
{
	
}
int32_t CAudioService::AudioServiceSetBasicSoundEffect(int32_t soundEffectType,DtvSoundEffect &ef)
{
	return 0;
}

void CAudioService::AudioServiceSetADEnable(bool enable)
{

}

void CAudioService::AudioServiceSetADAbsoluteVolume(int32_t value)
{
}

#if 0
int32_t CAudioService::AudioServiceEnableAdvancedSoundEffect(int32_t soundType,int32_t subProcessType)
{
	return CMstarService::getAudioManager()->enableAdvancedSoundEffect(soundType,subProcessType);
}
#endif


