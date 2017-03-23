#include <string>
#ifdef WIN32
#include "../tvplayer/tv_common.h"
#else
#include "tv_common.h"
#endif
#include "mapi_types.h"
#include "AudioSetting.h"
//#include "TVTypeDefine.h"


AudioSetting *AudioSetting::m_pInstance = NULL;

AudioSetting::AudioSetting()
{
    m_pstUiAudioData = NULL;
    bool ret = AudioSetting::AsSettingDataInit();
    if(ret == false)
    {
        printf("error!!![FUNC:%s]\r\n", __FUNCTION__);
    }
    _AudioService = new CAudioService();
}

AudioSetting::~AudioSetting()
{

    if (_AudioService) {
        delete _AudioService;
        _AudioService = NULL;
    }
}

AudioSetting* AudioSetting::getInstance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new AudioSetting();
    }
    return m_pInstance;
}

void AudioSetting::destroyInstance(void)
{
    if(m_pInstance != NULL)
    {
        m_pInstance->AsSaveSettingDataAll();
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

bool AudioSetting::AudioGetSoundMode(EN_UI_SOUND_MODE *penSoundMode, SoundModeSetting *pstSoundModeSetting)
{
    if(penSoundMode != NULL)
    {
        *penSoundMode = m_pstUiAudioData->soundMode;
    }
    if(pstSoundModeSetting != NULL)
    {
        memcpy(pstSoundModeSetting, 
            &(m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode]), 
            sizeof(SoundModeSetting));
    }

    return true;
}

void AudioSetting::AudioSetSoundMode(EN_UI_SOUND_MODE enSoundMode)
{
    m_pstUiAudioData->soundMode = enSoundMode;
    AsSetAudioItem(enSoundMode, UI_AS_EQ_ALL);

    AsSetAudioItem(m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].bass, 
                            UI_AS_BASS);
    AsSetAudioItem(m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].treble, 
                            UI_AS_TREBLE);    
}

bool AudioSetting::AudioGetEqBand1(int16_t *pvalue)
{
    *pvalue = m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand1;
    return true;
}

void AudioSetting::AudioSetEqBand1(int16_t value)
{
    m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand1 = value;
    AsSetAudioItem(value, UI_AS_EQ_BAND1);
}

bool AudioSetting::AudioGetEqBand2(int16_t *pvalue)
{
    *pvalue = m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand2;
    return true;
}

void AudioSetting::AudioSetEqBand2(int16_t value)
{
    m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand2 = value;
    AsSetAudioItem(value, UI_AS_EQ_BAND2);
}

bool AudioSetting::AudioGetEqBand3(int16_t *pvalue)
{
    *pvalue = m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand3;
    return true;
}

void AudioSetting::AudioSetEqBand3(int16_t value)
{
    m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand3 = value;
    AsSetAudioItem(value, UI_AS_EQ_BAND3);
}

bool AudioSetting::AudioGetEqBand4(int16_t *pvalue)
{
    *pvalue = m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand4;
    return true;
}

void AudioSetting::AudioSetEqBand4(int16_t value)
{
    m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand4 = value;
    AsSetAudioItem(value, UI_AS_EQ_BAND4);
}

bool AudioSetting::AudioGetEqBand5(int16_t *pvalue)
{
    *pvalue = m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand5;
    return true;
}

void AudioSetting::AudioSetEqBand5(int16_t value)
{
    m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand5 = value;
    AsSetAudioItem(value, UI_AS_EQ_BAND5);
}

bool AudioSetting::AudioGetBass(int16_t *pvalue)
{
    *pvalue = m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].bass;
    return true;
}

void AudioSetting::AudioSetBass(int16_t value)
{
    m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].bass = value;
    AsSetAudioItem(value, UI_AS_BASS);
}

bool AudioSetting::AudioGetTreble(int16_t *pvalue)
{
    *pvalue = m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].treble;
    return true;
}

void AudioSetting::AudioSetTreble(int16_t value)
{
    m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].treble = value;
    AsSetAudioItem(value, UI_AS_TREBLE);
}

/*balance input:-50~50*/
bool AudioSetting::AudioGetBalance(char *pvalue)
{
    *pvalue = m_pstUiAudioData->balance - 50; 
    return true;
}

void AudioSetting::AudioSetBalance(char value)
{
    m_pstUiAudioData->balance =  (unsigned char)(value + 50); 
    AsSetAudioItem(m_pstUiAudioData->balance, UI_AS_BALANCE);
}

bool AudioSetting::AudioGetEqualizerMode(EN_UI_SETTING_ON_OFF *pbValue)
{
    *pbValue = (EN_UI_SETTING_ON_OFF)m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].userMode;
    return true;
}

void AudioSetting::AudioSetEqualizerMode(EN_UI_SETTING_ON_OFF bValue)
{
    m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].userMode = bValue;
}

void AudioSetting::AudioGetAutoVolume(EN_UI_SETTING_ON_OFF *pbValue)
{
    *pbValue = (EN_UI_SETTING_ON_OFF)m_pstUiAudioData->enableAVC; 
}

void AudioSetting::AudioSetAutoVolume(EN_UI_SETTING_ON_OFF bValue)
{
    m_pstUiAudioData->enableAVC = (bool)bValue; 
    AsSetAudioItem(bValue, UI_AS_AUTO_VOLUME);
}

bool AudioSetting::AudioGetSurroundSound(EN_UI_SURROUND_MODE *penValue)
{
    *penValue = m_pstUiAudioData->surroundSoundMode; 
    return true;
}

void AudioSetting::AudioSetSurroundSound(EN_UI_SURROUND_MODE enValue)
{
    m_pstUiAudioData->surroundSoundMode = enValue; 
    AsSetAudioItem(enValue, UI_AS_SURROUND_SOUND);
}

bool AudioSetting::AudioGetAnalogOutput(EN_UI_SOUND_AD_OUTPUT *penValue)
{
    *penValue = m_pstUiAudioData->adOutput;
    return true;
}

void AudioSetting::AudioSetAnalogOutput(EN_UI_SOUND_AD_OUTPUT enValue)
{
    m_pstUiAudioData->adOutput = enValue;
}

bool AudioSetting::AudioGetDigitalOutput(EN_UI_SPDIF_MODE *penValue)
{

    if(m_pstUiAudioData->enSPDIFMODE == MSAPI_AUD_SPDIF_NONPCM_){
        *penValue = UI_SPDIF_AUTO;
    }else if(m_pstUiAudioData->enSPDIFMODE == MSAPI_AUD_SPDIF_PCM_){
        *penValue = UI_SPDIF_PCM;
    }else{
        printf("error!!![FUNC:%s],enSPDIFMODE=%d\r\n", __FUNCTION__, m_pstUiAudioData->enSPDIFMODE);
        *penValue = UI_SPDIF_AUTO;
    }
    return true;	
}

void AudioSetting::AudioSetDigitalOutput(EN_UI_SPDIF_MODE enValue)
{
    if (enValue == UI_SPDIF_AUTO)
    {
        m_pstUiAudioData->enSPDIFMODE = MSAPI_AUD_SPDIF_NONPCM_;
    }
    else if (enValue == UI_SPDIF_PCM)
    {
        m_pstUiAudioData->enSPDIFMODE = MSAPI_AUD_SPDIF_PCM_;
    }
    else
    {
        printf("error!!![FUNC:%s],enSPDIFMODE=%d\r\n", __FUNCTION__, m_pstUiAudioData->enSPDIFMODE);
        m_pstUiAudioData->enSPDIFMODE = MSAPI_AUD_SPDIF_NONPCM_;
    }
    
    AudioSetting::AsSetAudioItem(m_pstUiAudioData->enSPDIFMODE, UI_AS_SPDIF_MODE);

}

bool AudioSetting::AudioGetAudioHdmiType(HDMI_TYPE_ *penValue)
{
    *penValue = m_pstUiAudioData->AudioHdmiType;
    return true;
}

void AudioSetting::AudioSetAudioHdmiType(HDMI_TYPE_ enValue)
{
    m_pstUiAudioData->AudioHdmiType = enValue;
}

bool AudioSetting::AudioGetAudioDescription(EN_UI_SETTING_ON_OFF * pbValue)
{
    *pbValue = (EN_UI_SETTING_ON_OFF)m_pstUiAudioData->enableAd;
    return true;
}
void AudioSetting::AudioSetAudioDescription(EN_UI_SETTING_ON_OFF bValue)
{
    m_pstUiAudioData->enableAd = (bool)bValue;
    AsSetAudioItem(bValue, UI_AS_AD_ENABLE);
}
bool AudioSetting::AudioGetADVolume(uint8_t * pValue)
{
    *pValue = m_pstUiAudioData->adVolume;
    return true;
}
void AudioSetting::AudioSetADVolume(uint8_t Value)
{
    m_pstUiAudioData->adVolume = Value;
    AsSetAudioItem(Value, UI_AS_AD_VOLUME);
}

bool AudioSetting::AudioGetADBanlance(uint8_t *pValue)
{
    *pValue = m_pstUiAudioData->balance;
    return true;
}

void AudioSetting::AudioSetADBanlance(uint8_t Value)
{
    m_pstUiAudioData->balance = Value;
    AsSetAudioItem(m_pstUiAudioData->balance, UI_AS_BALANCE);
}

void AudioSetting::AudioSettingReset(void)
{
    int i = 0;
    MS_UI_USER_SOUND_SETTING stUiSoundSetting = {0};

    memset(&stUiSoundSetting, 0, sizeof(MS_UI_USER_SOUND_SETTING));    
    UI_System_Database::GetUiSystemDbInstance()->GetFactoryAudioSetting(&stUiSoundSetting);
    
    /*Sound mode data*/
    m_pstUiAudioData->soundMode = stUiSoundSetting.soundMode;
    for(i=SOUND_MODE_MIN; i<SOUND_MODE_NUM;  i++)
    {
        memcpy(&(m_pstUiAudioData->astSoundModeSetting[i]), 
                    &(stUiSoundSetting.astSoundModeSetting[i]), 
                    sizeof(SoundModeSetting));
    }
    /*balance*/
    m_pstUiAudioData->balance =  stUiSoundSetting.balance;
    /*Auto Volume*/
    m_pstUiAudioData->enableAVC = stUiSoundSetting.enableAVC;
    /*Surround Sound*/
    m_pstUiAudioData->surroundSoundMode = stUiSoundSetting.surroundSoundMode;
    /*Analog Audio Output*/
    m_pstUiAudioData->adOutput = stUiSoundSetting.adOutput;
    /*Digital Audio Output*/
    m_pstUiAudioData->enSPDIFMODE = stUiSoundSetting.enSPDIFMODE;
    /*Audio HDMI*/
    m_pstUiAudioData->AudioHdmiType = stUiSoundSetting.AudioHdmiType;
    /*Audio description*/
    m_pstUiAudioData->enableAd = stUiSoundSetting.enableAd;
    m_pstUiAudioData->adVolume = stUiSoundSetting.adVolume;
  
}

/**** private functions*****/
void AudioSetting::AsSetAudioItem(uint32_t u32Value, EN_UI_AS_ITEM enItem)
{
    switch(enItem)
    {
        case UI_AS_EQ_BAND1:
            m_DtvSoundEf.soundParameterEqs[0].eqLevel= (int32_t)u32Value;
            _AudioService->AudioServiceSetBasicSoundEffect(BSND_EQ,m_DtvSoundEf);
            break;
        case UI_AS_EQ_BAND2:
            m_DtvSoundEf.soundParameterEqs[1].eqLevel= (int32_t)u32Value;
            _AudioService->AudioServiceSetBasicSoundEffect(BSND_EQ,m_DtvSoundEf);
            break;
        case UI_AS_EQ_BAND3:
            m_DtvSoundEf.soundParameterEqs[2].eqLevel= (int32_t)u32Value;
            _AudioService->AudioServiceSetBasicSoundEffect(BSND_EQ,m_DtvSoundEf);
            break;
        case UI_AS_EQ_BAND4:
            m_DtvSoundEf.soundParameterEqs[3].eqLevel= (int32_t)u32Value;
            _AudioService->AudioServiceSetBasicSoundEffect(BSND_EQ,m_DtvSoundEf);
            break;
        case UI_AS_EQ_BAND5:
            m_DtvSoundEf.soundParameterEqs[4].eqLevel= (int32_t)u32Value;
            _AudioService->AudioServiceSetBasicSoundEffect(BSND_EQ,m_DtvSoundEf);
            break;
        case UI_AS_EQ_ALL:
            AsInitDtvSoundEffect();
            _AudioService->AudioServiceSetBasicSoundEffect(BSND_EQ,m_DtvSoundEf);
            break;            
        case UI_AS_SURROUND_SOUND:
            _AudioService->AudioServiceSetSurroundSound(u32Value);
            break;
        case UI_AS_AUTO_VOLUME:
            // For speaker "PU" when adjust AVC
            //_AudioService->AudioServiceEnableMute(MUTE_BYUSER);
            //usleep(100000);
            _AudioService->AudioServiceSetAutoVolume((bool)u32Value);
            // For speaker "PU" when adjust AVC
            //if(!VolumeControlFrame::IsMuteFlag)
            //{
            //usleep(100000);
            //_AudioService->AudioServiceDisableMute(MUTE_BYUSER);
            //}
            break;
        case UI_AS_SPDIF_MODE:
            _AudioService->AudioServiceSetDigitalOut((int32_t)u32Value);
            break;
        case UI_AS_AD_ENABLE:
            _AudioService->AudioServiceSetADEnable((bool)u32Value);
            break;
        case UI_AS_AD_VOLUME:
            _AudioService->AudioServiceSetADAbsoluteVolume((int32_t)u32Value);
            break;
        case UI_AS_BALANCE:
            m_DtvSoundEf.balance = (int32_t)u32Value;
            _AudioService->AudioServiceSetBasicSoundEffect(BSND_BALANCE,m_DtvSoundEf);
            break;
        default:
            break;
    }

}

bool AudioSetting::AsSettingDataInit(void)
{
    if(m_pstUiAudioData == NULL)
    {
        m_pstUiAudioData = new MS_UI_USER_SOUND_SETTING;
        if(m_pstUiAudioData == NULL)
            return false;
        UI_System_Database::GetUiSystemDbInstance()->GetAudioSetting(m_pstUiAudioData);
        AsInitDtvSoundEffect();
    }
    return true;
}

void AudioSetting::AsSaveSettingDataAll(void)
{
    if(m_pstUiAudioData != NULL)
    {
        UI_System_Database::GetUiSystemDbInstance()->SetAudioSetting(m_pstUiAudioData);
        delete m_pstUiAudioData;
        m_pstUiAudioData = NULL;
    }
    
}

void AudioSetting::AsInitDtvSoundEffect(void)
{

    if(m_pstUiAudioData == NULL)
        return;
    m_DtvSoundEf.eqBandNumber = MAXEQNAD;

    m_DtvSoundEf.soundParameterEqs[0].eqLevel =  
            m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand1;

    m_DtvSoundEf.soundParameterEqs[1].eqLevel =  
            m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand2;

    m_DtvSoundEf.soundParameterEqs[2].eqLevel =  
            m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand3;

    m_DtvSoundEf.soundParameterEqs[3].eqLevel =  
            m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand4;

    m_DtvSoundEf.soundParameterEqs[4].eqLevel =  
            m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].eqBand5;

    m_DtvSoundEf.bass = m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].bass;
    m_DtvSoundEf.treble = m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].treble;
    m_DtvSoundEf.balance = m_pstUiAudioData->astSoundModeSetting[m_pstUiAudioData->soundMode].balance;
    
}


