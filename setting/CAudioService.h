/****************************************************************************
 * Notice:      Copyright (c) Skyworth.
 *              All rights reserved.
 * Owner:      zhangyamei@skyworth.com
 ****************************************************************************/

#ifndef __CAUDIOSERVICE_H__
#define __CAUDIOSERVICE_H__

#include "AudioManagerTypeDefine.h"

class MSrv_SSAudio;

class CAudioService
{
    public:
    	CAudioService();
    	~CAudioService();
    	
    //static MSrv_SSAudio* m_MSrvSSAudio;
    void AudioServiceSetAutoVolume(bool value);
    bool AudioServiceEnableMute(int32_t enMuteType);
    bool AudioServiceGetAudioMuteFlag(void);
    bool AudioServiceDisableMute(int32_t enMuteType);
    uint8_t AudioServiceSetSurroundSound(uint32_t sound);
    void AudioServiceSetDigitalOut(int32_t mode);
    void setDigitalOut(int32_t mode);
    int32_t AudioServiceSetBasicSoundEffect(int32_t soundEffectType,DtvSoundEffect &ef);
    void AudioServiceSetADEnable(bool enable);
    void AudioServiceSetADAbsoluteVolume(int32_t value);

};


#endif // __CAUDIOSERVICE_H__
