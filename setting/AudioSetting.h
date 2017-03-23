#ifndef __AUDIOSetting_H__
#define __AUDIOSetting_H__

#include <vector>
#include "CAudioService.h"
#include "DatabaseManagerType.h"
#include "mapi_audio_datatype.h"
#include "UiSystemDataBase.h"

#define BIT0                0x00000001
#define BIT1                0x00000002
#define BIT2                0x00000004
#define BIT3                0x00000008
#define BIT4                0x00000010
#define BIT5                0x00000020
#define BIT6                0x00000040
/// Define Sound mute type.
typedef enum
{
    ///Set sound mute type for permanent
    MUTE_PERMANENT          = BIT0,
    ///Set sound mute type for moment
    MUTE_MOMENT             = BIT1,
    ///Set sound mute type for by user
    MUTE_BYUSER             = BIT2,
    ///Set sound mute type for by sync
    MUTE_BYSYNC             = BIT3,
    ///Set sound mute type for by chip
    MUTE_BYVCHIP            = BIT4,
    ///Set sound mute type for by block
    MUTE_BYBLOCK            = BIT5,
    ///Set sound mute type for interanl1
    MUTE_INTERNAL1          = BIT6,
    ///Set sound mute type for interanl2
    #if 0
    MUTE_INTERNAL2          = BIT7,
    ///Set sound mute type for interanl3
    MUTE_INTERNAL3          = BIT8,
    ///Set sound mute type for during limited time
    MUTE_DURING_LIMITED_TIME = BIT9,
    ///Set sound mute type for mhegap
    MUTE_MHEGAP             = BIT10,
    ///Set sound mute type for CI
    MUTE_CI                 = BIT11,
    ///Set sound mute type for Scan
    MUTE_SCAN               = BIT12,
    ///Set sound mute type for source switch
    MUTE_SOURCESWITCH       = BIT13,
    ///Set sound mute type for user speaker
    MUTE_USER_SPEAKER       = BIT14,
    ///Set sound mute type for user hp
    MUTE_USER_HP            = BIT15,
    ///Set sound mute type for user spdif
    MUTE_USER_SPDIF         = BIT16,
    ///Set sound mute type for user scart1
    MUTE_USER_SCART1        = BIT17,
    ///Set sound mute type for user scart2
    MUTE_USER_SCART2        = BIT18,
    ///Set all sound mute type
    MUTE_ALL                = BIT19,
    ///Set sound mute type for data input (From Alsa)
    MUTE_USER_DATA_IN       = BIT20,
    ///Set sound mute type for capture1
    MUTE_USER_PCM_CAPTURE1  = BIT21,
    ///Set sound mute type for capture2
    MUTE_USER_PCM_CAPTURE2  = BIT22,
    ///Set sound mute by APP
    MUTE_BY_APP             = BIT23,
    #endif
}  SSSOUND_MUTE_TYPE;
typedef enum
{
    UI_AS_BASS,
    UI_AS_TREBLE,
    UI_AS_EQ_ALL,
    UI_AS_EQ_BAND1, //120Hz
    UI_AS_EQ_BAND2, //500Hz
    UI_AS_EQ_BAND3, ///1.5KHz
    UI_AS_EQ_BAND4, //5KHz
    UI_AS_EQ_BAND5, ///10KHz
    UI_AS_EQ_BAND6, 
    UI_AS_EQ_BAND7, 
    UI_AS_BALANCE, 
    UI_AS_SURROUND_SOUND,
    UI_AS_AUTO_VOLUME,
    UI_AS_SPDIF_MODE,
    UI_AS_AD_ENABLE, //Audio description
    UI_AS_AD_VOLUME,
}EN_UI_AS_ITEM;

//Digital Audio Output
#if 1
typedef enum
{
    UI_SPDIF_PCM = 0,
    UI_SPDIF_AUTO,
    UI_SPDIF_COUNT
}EN_UI_SPDIF_MODE;
#endif

/// Define Audio Baisc Effect Type.
typedef enum
{
    ///PreScale
    BSND_PRESCALE,
    ///Treble
    BSND_TREBLE,
    ///Bass
    BSND_BASS,
    ///Balance
    BSND_BALANCE,
    ///EQ
    BSND_EQ,
    ///PEQ
    BSND_PEQ,
    ///AVC(AVL)
    BSND_AVC,
    ///MStar Surround
    BSND_Surround,
    ///Sound DRC
    BSND_DRC,
    /// Noise Reduction
    BSND_NR,
    /// ECHO
    BSND_ECHO,
} UI_BSOUND_EFFECT_TYPE;

/// Advance Sound Main Function Type
typedef enum
{
    /// Dolby Prologic2 + Virtual Dolby Surr
    ADVSND_DOLBY_PL2VDS,
    /// Dolby Prologic2 + Dolby Virtual Speaker
    ADVSND_DOLBY_PL2VDPK,
    /// BBE
    ADVSND_BBE,
    /// SRS TrueSurr XT
    ADVSND_SRS_TSXT,
    /// SRS TrueSurr HD
    ADVSND_SRS_TSHD,
    /// SRS Theater Sound
    ADVSND_SRS_THEATERSOUND,
    /// DTS Ultra-TV
    ADVSND_DTS_ULTRATV,
    /// Audyssey
    ADVSND_AUDYSSEY,
    /// MStar Super Voice
    ADVSND_SUPER_VOICE,
    /// DBX
    ADVSND_DBX,
    /// SRS_PURESOUND
    ADVSND_SRS_PURESOUND,
    /// SRS SS3D
    ADVSND_SRS_THEATERSOUND3D,
    /// Reserve
    ADVSND_RESERVE4,
    /// Reserve
    ADVSND_RESERVE5,
    /// Reserve
    ADVSND_RESERVE6,
    /// NONE
    ADVSND_NONE,
}ADVANCESND_UI_TYPE;
class AudioSetting 
{
public:
    AudioSetting();
    ~AudioSetting();
    static AudioSetting* getInstance(void);
    static void destroyInstance(void);        
    bool AudioGetSoundMode(EN_UI_SOUND_MODE *penSoundMode, SoundModeSetting *pstSoundModeSetting);
    void AudioSetSoundMode(EN_UI_SOUND_MODE enSoundMode);
    bool AudioGetEqBand1(int16_t *pvalue);
    void AudioSetEqBand1(int16_t value);
    bool AudioGetEqBand2(int16_t *pvalue);
    void AudioSetEqBand2(int16_t value);
    bool AudioGetEqBand3(int16_t *pvalue);
    void AudioSetEqBand3(int16_t value);
    bool AudioGetEqBand4(int16_t *pvalue);
    void AudioSetEqBand4(int16_t value);
    bool AudioGetEqBand5(int16_t *pvalue);
    void AudioSetEqBand5(int16_t value);
    bool AudioGetBass(int16_t *pvalue);
    void AudioSetBass(int16_t value);
    bool AudioGetTreble(int16_t *pvalue);
    void AudioSetTreble(int16_t value);
    bool AudioGetBalance(char *pvalue);
    void AudioSetBalance(char value);
    bool AudioGetEqualizerMode(EN_UI_SETTING_ON_OFF *pbValue);
    void AudioSetEqualizerMode(EN_UI_SETTING_ON_OFF bValue);    
    void AudioGetAutoVolume(EN_UI_SETTING_ON_OFF *pbValue);
    void AudioSetAutoVolume(EN_UI_SETTING_ON_OFF bValue);
    bool AudioGetSurroundSound(EN_UI_SURROUND_MODE *penValue);
    void AudioSetSurroundSound(EN_UI_SURROUND_MODE enValue);
    bool AudioGetAnalogOutput(EN_UI_SOUND_AD_OUTPUT *penValue);
    void AudioSetAnalogOutput(EN_UI_SOUND_AD_OUTPUT enValue);
    bool AudioGetDigitalOutput(EN_UI_SPDIF_MODE *penValue);
    void AudioSetDigitalOutput(EN_UI_SPDIF_MODE enValue);
    bool AudioGetAudioHdmiType(HDMI_TYPE_ *penValue);
    void AudioSetAudioHdmiType(HDMI_TYPE_ enValue);
    bool AudioGetAudioDescription(EN_UI_SETTING_ON_OFF *pbValue);
    void AudioSetAudioDescription(EN_UI_SETTING_ON_OFF bValue);
    bool AudioGetADVolume(uint8_t *pValue);   //audio description volume
    void AudioSetADVolume(uint8_t Value);    //audio description volume
    bool AudioGetADBanlance(uint8_t *pValue);   //audio description banlance
    void AudioSetADBanlance(uint8_t Value);    //audio description banlance
    void AudioSettingReset(void);
private:
    void AsSetAudioItem(uint32_t u32Value, EN_UI_AS_ITEM enItem);
    bool AsSettingDataInit(void);
    void AsSaveSettingDataAll(void);
    void AsInitDtvSoundEffect(void);
    CAudioService* _AudioService;
    static AudioSetting *m_pInstance;
    MS_UI_USER_SOUND_SETTING *m_pstUiAudioData;
    DtvSoundEffect m_DtvSoundEf;
};

#endif // __AUDIOSetting_H__

