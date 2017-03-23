//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
#ifndef __AudioManager_TYPEDEFINE_H__
#define __AudioManager_TYPEDEFINE_H__


#define MAXEQNAD 5
#define MAXPEQNAD 5

/// Define Audio Baisc Effect Type For Android. 
/// It shall be the same with BSOUND_EFFECT_TYPE of TVOS Msrv_SSound.h
typedef enum
{
    ///PreScale
    E_BSND_PRESCALE=0,
    ///Treble
    E_BSND_TREBLE,
    ///Bass
    E_BSND_BASS,
    ///Balance
    E_BSND_BALANCE,
    ///EQ
    E_BSND_EQ,
    ///PEQ
    E_BSND_PEQ,
    ///AVC(AVL)
    E_BSND_AVC,
    ///MStar Surround
    E_BSND_Surround,
    ///Sound DRC
    E_BSND_DRC,
    /// Noise Reduction
    E_BSND_NR,
    /// ECHO
    E_BSND_ECHO,
} EN_BSOUND_EFFECT_TYPE;

/// Define MessageBox return value.
typedef enum
{
    /// MessageBox return value is OK.
    E_MSGBOX_OK = 0,
    E_MSGBOX_CANCEL,
    E_MSGBOX_ABORT,
    E_MSGBOX_RETRY,
    E_MSGBOX_IGNORE,
    E_MSGBOX_YES,
    E_MSGBOX_NO,
    E_MSGBOX_TRYAGAIN,
    E_MSGBOX_CONTINUE,

    E_MSGBOX_RESULTNUM,
} EN_MSGBOX_RESULT;

typedef enum
{
    E_MBTYPE_ABORTRETRYIGNORE,
    E_MBTYPE_CANCELTRYCONTINUE,
    E_MBTYPE_OK,
    E_MBTYPE_OKCANCEL,
    E_MBTYPE_RETRYCANCEL,
    E_MBTYPE_YESNO,
    E_MBTYPE_YESNOCANCEL,

    E_MBTYPE_TYPENUM,
} EN_MSGBOX_TYPES;

typedef struct
{
     int spdifDelayTime;
     int speakerDelayTime;
     int spdifOutmodInUi;
     int spdifOutmodActive;
}AudioOutParameter;

typedef struct
{
 int32_t eqLevel ;

}SoundParameterEq;

typedef struct
{
 int32_t peqGain ;
 int32_t peqGc ;
 int32_t peqQvalue;

}SoundParameterPeq;

typedef struct
{
 int32_t avcAttachTime;
 int32_t avcReleaseTime;
 int32_t avcThreshold ;
 int32_t balance ;
 int32_t bass  ;
 int32_t echoTime  ;
 int32_t eqBandNumber;
 int32_t noiseReductionThreshold;
 int32_t peqBandNumber ;
 int32_t preScale ;
 int32_t soundDrcThreshold  ;
 SoundParameterEq soundParameterEqs[MAXEQNAD]  ;
 SoundParameterPeq soundParameterPeqs[MAXPEQNAD] ;
 int32_t surroundXaValue    ;
 int32_t surroundXbValue  ;
 int32_t surroundXkValue ;
 int32_t treble;

}DtvSoundEffect;

/// Audio output port source setting
typedef struct
{
    int32_t SpeakerOut; ///<  for Speaker
    int32_t HpOut;          ///<  for HP
    int32_t MonitorOut; ///<  for Monitor out
    int32_t ScartOut;     ///<  for Scart out
    int32_t SpdifOut;     ///<  for SPDIF out
} AUDIO_OUTPORT_SOURCE_INFO;

typedef struct
{
    ///DOLBY PL2 + VSPK SMOD Setting
    int32_t  paramDolbyPl2vdpkSmod;
    ///DOLBY PL2 + VSPK WMOD Setting
    int32_t  paramDolbyPl2vdpkWmod;
    ///SRS TSXT PARAM:INPUTGain Setting
    int32_t  paramSrsTsxtSetInputGain;
    ///SRS TSXT PARAM:DCGain Setting
    int32_t  paramSrsTsxtSetDcGain;
    ///SRS TSXT PARAM:TRUBASSGain Setting
    int32_t  paramSrsTsxtSetTrubassGain;
    ///SRS TSXT PARAM:SPEAKERSIZE Setting
    int32_t  paramSrsTsxtSetSpeakerSize;
    ///SRS TSXT PARAM:INPUTMode Setting
    int32_t  paramSrsTsxtSetInputMode;
    ///SRS TSXT PARAM:OUTPUTGain Setting
    int32_t  paramSrsTsxtSetOutputGain;

    ///SRS TSHD Sub-Process Setting Parameter
    ///SRS TSHD PARAM:INPUTMode Setting
    int32_t  paramSrsTshdSetInputMode;
    ///SRS TSHD PARAM:OUTPUTMode Setting
    int32_t  paramSrsTshdSetOutputMode;
    ///SRS TSHD PARAM:SPEAKERSIZE Setting
    int32_t  paramSrsTshdSetSpeakerSize;
    ///SRS TSHD PARAM:TRUBASSControl Setting
    int32_t  paramSrsTshdSetTrubassControl;
    ///SRS TSHD PARAM:DEFINITIONControl Setting
    int32_t  paramSrsTshdSetDefinitionControl;
    ///SRS TSHD PARAM:DCControl Setting
    int32_t  paramSrsTshdSetDcControl;
    ///SRS TSHD PARAM:SURROUNDLevel Setting
    int32_t  paramSrsTshdSetSurroundLevel;
    ///SRS TSHD PARAM:INPUTGain Setting
    int32_t  paramSrsTshdSetInputGain;
    ///SRS TSHD PARAM:WOWSPACEControl Setting
    int32_t  paramSrsTshdSetWowSpaceControl;
    ///SRS TSHD PARAM:WOWCENTERControl Setting
    int32_t  paramSrsTshdSetWowCenterControl;
    ///SRS TSHD PARAM:WOWHDSRS3DMODE Setting
    int32_t  paramSrsTshdSetWowHdSrs3dMode;
    ///SRS TSHD PARAM:LIMITERControl Setting
    int32_t  paramSrsTshdSetLimiterControl;
    ///SRS TSHD PARAM:OUTPUTGain Setting
    int32_t  paramSrsTshdSetOutputGain;

    ///SRS_THEATERSOUND Sub-Process Setting Parameter
    ///SRS THEATERSOUND PARAM:INPUTGain Setting
    int32_t  paramSrsTheaterSoundInputGain;
    ///SRS THEATERSOUND PARAM:DEFINITIONControl Setting
    int32_t  paramSrsTheaterSoundDefinitionControl;
    ///SRS THEATERSOUND PARAM:DCControl Setting
    int32_t  paramSrsTheaterSoundDcControl;
    ///SRS THEATERSOUND PARAM:TRUBASSControl Setting
    int32_t  paramSrsTheaterSoundTrubassControl;
    ///SRS THEATERSOUND PARAM:SPEAKERSIZE Setting
    int32_t  paramSrsTheaterSoundSpeakerSize;
    ///SRS THEATERSOUND PARAM:HARDLIMITERLevel Setting
    int32_t  paramSrsTheaterSoundHardLimiterLevel;
    ///SRS THEATERSOUND PARAM:HARDLIMITERBoostGain Setting
    int32_t  paramSrsTheaterSoundHardLimiterBoostGain;
    ///SRS THEATERSOUND PARAM:HEADROOMGain Setting
    int32_t  paramSrsTheaterSoundHeadRoomGain;
    ///SRS THEATERSOUND PARAM:TRUVOLUMEMode Setting
    int32_t  paramSrsTheaterSoundTruVolumeMode;
    ///SRS THEATERSOUND PARAM:TRUVOLUMERefLevel Setting
    int32_t  paramSrsTheaterSoundTruVolumeRefLevel;
    ///SRS THEATERSOUND PARAM:TRUVOLUME_MAXGain Setting
    int32_t  paramSrsTheaterSoundTruVolumeMaxGain;
    ///SRS THEATERSOUND PARAM:TRUVOLUMENoiseMngrThld Setting
    int32_t  paramSrsTheaterSoundTruVolumeNoiseMngrThld;
    ///SRS THEATERSOUND PARAM:TRUVOLUMECalibrate Setting
    int32_t  paramSrsTheaterSoundTruVolumeCalibrate;
    ///SRS THEATERSOUND PARAM:TRUVOLUMEInputGain Setting
    int32_t  paramSrsTheaterSoundTruVolumeInputGain;
    ///SRS THEATERSOUND PARAM:TRUVOLUMEOutputGain Setting
    int32_t  paramSrsTheaterSoundTruVolumeOutputGain;
    ///SRS THEATERSOUND PARAM:HPF_FC Setting
    int32_t  paramSrsTheaterSoundHpfFc;

    ///DTS_ULTRATV Sub-Process Setting Parameter
    ///DTS_ULTRATV PARAM:EVOMonoInput Setting
    int32_t  paramDtsUltraTvEvoMonoInput;
    ///DTS_ULTRATV PARAM:EVOWideningon Setting
    int32_t  paramDtsUltraTvEvoWideningon;
    ///DTS_ULTRATV PARAM:EVOAdd3dBon Setting
    int32_t  paramDtsUltraTvEvoAdd3dBon;
    ///DTS_ULTRATV PARAM:EVOPceLevel Setting
    int32_t  paramDtsUltraTvEvoPceLevel;
    ///DTS_ULTRATV PARAM:EVOVlfeLevel Setting
    int32_t  paramDtsUltraTvEvoVlfeLevel;
    ///DTS_ULTRATV PARAM:SYMDefault Setting
    int32_t  paramDtsUltraTvSymDefault;
    ///DTS_ULTRATV PARAM:SYMMode Setting
    int32_t  paramDtsUltraTvSymMode;
    ///DTS_ULTRATV PARAM:SYMLevel Setting
    int32_t  paramDtsUltraTvSymLevel;
    ///DTS_ULTRATV PARAM:SYMReset Setting
    int32_t  paramDtsUltraTvSymReset;

    ///AUDYSSEY Sub-Process Setting Parameter
    ///AUDYSSEY PARAM:DYNAMICVOLCompressMode Setting
    int32_t  paramAudysseyDynamicVolCompressMode;
    ///AUDYSSEY PARAM:DYNAMICVOLGc Setting
    int32_t  paramAudysseyDynamicVolGc;
    ///AUDYSSEY PARAM:DYNAMICVOLVolSetting Setting
    int32_t  paramAudysseyDynamicVolVolSetting;
    ///AUDYSSEY PARAM:DYNAMICEQ_EQOFFSET Setting
    int32_t  paramAudysseyDynamicEqEqOffset;
    ///AUDYSSEY PARAM:ABX_GWET Setting
    int32_t  paramAudysseyAbxGwet;
    ///AUDYSSEY PARAM:ABX_GDRY Setting
    int32_t  paramAudysseyAbxGdry;
    ///AUDYSSEY PARAM:ABX_FILSET Setting
    int32_t  paramAudysseyAbxFilset;

    ///SRS_THEATERSOUND Sub-Process Setting Parameter
    ///SRS THEATERSOUND PARAM:TSHD_INPUT_GAIN Setting
    int32_t    paramSrsTheaterSoundTshdInputGain;
    ///SRS THEATERSOUND PARAM:TSHD_OUTPUT_GAIN Setting
    int32_t    paramSrsTheaterSoundTshdutputGain;
    ///SRS THEATERSOUND PARAM:SURR_LEVEL_CONTROL Setting
    int32_t    paramSrsTheaterSoundSurrLevelControl;
    ///SRS THEATERSOUND PARAM:TRUBASS_COMPRESSOR_CONTROL Setting
    int32_t    paramSrsTheaterSoundTrubassCompressorControl;
    ///SRS THEATERSOUND PARAM:TRUBASS_PROCESS_MODE Setting
    int32_t    paramSrsTheaterSoundTrubassProcessMode;
    ///SRS THEATERSOUND PARAM:TRUBASS_SPEAKER_AUDIO Setting
    int32_t    paramSrsTheaterSoundTrubassSpeakerAudio;
    ///SRS THEATERSOUND PARAM:TRUBASS_SPEAKER_ANALYSIS Setting
    int32_t    paramSrsTheaterSoundTrubassSpeakerAnalysis;

    ///SRS THEATERSOUND PARAM:TSHD_BYPASS_GAIN Setting
    int32_t  paramSrsTheaterSoundTshdBypassGain;
    ///SRS THEATERSOUND PARAM:OUTPUT_GAIN Setting
    int32_t  paramSrsTheaterSoundOutputGain;
    ///SRS THEATERSOUND PARAM:BYPASS_GAIN Setting
    int32_t  paramSrsTheaterSoundBypassGain;
    ///SRS THEATERSOUND PARAM:INPUT_MODE Setting
    int32_t  paramSrsTheaterSoundInputMode;
    ///SRS THEATERSOUND PARAM:TRUVOLUME_BYPASS_GAIN Setting
    int32_t  paramSrsTheaterSoundTruvolumeBypassGain;
    ///SRS THEATERSOUND PARAM:CS_INPUT_GAIN Setting
    int32_t  paramSrsTheaterSoundCsInputGain;

    //SRS PURESOUND PARAM:HL_INPUT_GAIN Setting
    int32_t  paramSrsPuresoundHlInputGain;
    ///SRS PURESOUND PARAM:HL_OUTPUT_GAIN Setting
    int32_t  paramSrsPuresoundHlOutputGain;
    ///SRS PURESOUND PARAM:HL_BYPASS_GAIN Setting
    int32_t  paramSrsPuresoundHlBypassGain;
    ///SRS PURESOUND PARAM:HL_LIMITERBOOST Setting
    int32_t  paramSrsPuresoundHlLimiterboost;
    ///SRS PURESOUND PARAM:HL_HARDLIMIT Setting
    int32_t  paramSrsPuresoundHlHardlimit;
    ///SRS PURESOUND PARAM:HL_DELAYLEN Setting
    int32_t  paramSrsPuresoundHlDelaylen;
    ///SRS PURESOUND PARAM:AEQ_INPUT_GAIN Setting
    int32_t  paramSrsPuresoundAeqInputGain;
    ///SRS PURESOUND PARAM:AEQ_OUTPUT_GAIN Setting
    int32_t  paramSrsPuresoundAeqOutputGain;
    ///SRS PURESOUND PARAM:AEQ_BYPASS_GAIN Setting
    int32_t  paramSrsPuresoundAeqBypassGain;
    ///SRS PURESOUND PARAM:FILTER_CONFIG Setting
    int32_t  paramSrsPuresoundFilterConfig;
    ///SRS PURESOUND PARAM:HPF_FREQUENCY Setting
    int32_t  paramSrsPuresoundHpfFrequency;
    ///SRS PURESOUND PARAM:TBHD_TRUBASS_LEVEL Setting
    int32_t  paramSrsPuresoundTbhdTrubassLevel;
    ///SRS PURESOUND PARAM:TBHD_SPEAKER_SIZE Setting
    int32_t  paramSrsPuresoundTbhdSpeakerSize;
    ///SRS PURESOUND PARAM:TBHD_LEVEL_INDEPENDENT_EN Setting
    int32_t  paramSrsPuresoundTbhdLevelIndependentEn;
    ///SRS PURESOUND PARAM:TBHD_COMPRESSOR_LEVEL Setting
    int32_t  paramSrsPuresoundTbhdCompressorLevel;
    ///SRS PURESOUND PARAM:TBHD_MODE Setting
    int32_t  paramSrsPuresoundTbhdMode;
    ///SRS PURESOUND PARAM:TBHD_SPEAKER_AUDIO Setting
    int32_t  paramSrsPuresoundTbhdSpeakerAudio;
    ///SRS PURESOUND PARAM:TBHD_SPEAKER_ANALYSIS Setting
    int32_t  paramSrsPuresoundTbhdSpeakerAnalysis;
    ///SRS PURESOUND PARAM:INPUT_GAIN Setting
    int32_t  paramSrsPuresoundInputGain;
    ///SRS PURESOUND PARAM:OUTPUT_GAIN Setting
    int32_t  paramSrsPuresoundOutputGain;

    ///SRS THEATERSOUND PARAM:CC3D_INPUT_GAIN Setting
    int32_t  paramSrsPuresoundCc3dInputGain;
    ///SRS THEATERSOUND PARAM:CC3D_OUTPUT_GAIN Setting
    int32_t  paramSrsPuresoundCc3dOutputGain;
    ///SRS THEATERSOUND PARAM:CC3D_BYPASS_GAIN Setting
    int32_t  paramSrsPuresoundCc3dBypassGain;
    ///SRS THEATERSOUND PARAM:CC3D_APERTURE Setting
    int32_t  paramSrsPuresoundCc3dAperture;
    ///SRS THEATERSOUND PARAM:CC3D_GAINLIMIT Setting
    int32_t  paramSrsPuresoundCc3dGainlimit;
    ///SRS THEATERSOUND PARAM:CC3D_FF_DEPTH Setting
    int32_t  paramSrsPuresoundCc3dFfDepth;
    ///SRS THEATERSOUND PARAM:CC3D_NF_DEPTH Setting
    int32_t  paramSrsPuresoundCc3dNfDepth;
    ///SRS THEATERSOUND PARAM:CC3D_TSHD_SURR_MODE Setting
    int32_t  paramSrsPuresoundCc3dTshdSurrMode;
    ///SRS THEATERSOUND PARAM:TSHD_MIX_FADE_CTRL Setting
    int32_t  paramSrsPuresoundCc3dTshdMixFadeCtrl;
    ///SRS THEATERSOUND PARAM:CC3D_TBHDX_INPUT_GAIN Setting
    int32_t  paramSrsPuresoundCc3dTbhdxInputGain;
    ///SRS THEATERSOUND PARAM:CC3D_TBHDX_BASSLEVEL Setting
    int32_t  paramSrsPuresoundCc3dTbhdxBasslevel;
    ///SRS THEATERSOUND PARAM:CC3D_TBHDX_SPEAKERSIZE Setting
    int32_t  paramSrsPuresoundCc3dTbhdxSpeakersize;
    ///SRS THEATERSOUND PARAM:CC3D_TBHDX_MODE Setting
    int32_t  paramSrsPuresoundCc3dTbhdxMode;
    ///SRS THEATERSOUND PARAM:CC3D_TBHDX_DYNAMICS Setting
    int32_t  paramSrsPuresoundCc3dTbhdxDynamics;
    ///SRS THEATERSOUND PARAM:CC3D_TBHDX_HP_ORDER Setting
    int32_t  paramSrsPuresoundCc3dTbhdxHpOrder;
    ///SRS THEATERSOUND PARAM:CC3D_TBHDX_CUSTOM_FILTER Setting
    int32_t  paramSrsPuresoundCc3dTbhdxCustomFilter;
    ///SRS THEATERSOUND PARAM:GEQ_INPUT_GAIN Setting
    int32_t  paramSrsPuresoundCc3dGeqInputGain;
    ///SRS THEATERSOUND PARAM:GEQ_BAND0_GAIN Setting
    int32_t  paramSrsPuresoundCc3dGeqBand0Gain;
    ///SRS THEATERSOUND PARAM:GEQ_BAND1_GAIN Setting
    int32_t  paramSrsPuresoundCc3dGeqBand1Gain;
    ///SRS THEATERSOUND PARAM:GEQ_BAND2_GAIN Setting
    int32_t  paramSrsPuresoundCc3dGeqBand2Gain;
    ///SRS THEATERSOUND PARAM:GEQ_BAND3_GAIN Setting
    int32_t  paramSrsPuresoundCc3dGeqBand3Gain;
    ///SRS THEATERSOUND PARAM:GEQ_BAND4_GAIN Setting
    int32_t  paramSrsPuresoundCc3dGeqBand4Gain;
    ///SRS THEATERSOUND PARAM:CC3D_PROCESS_PATH Setting
    int32_t  paramSrsPuresoundCc3dCc3D_processPath;

    ///DBX PARAM:TOTAL_SONIC_MODE Setting
    int32_t  paramDbxTotalSonicMode;
    ///DBX PARAM:TOTAL_VOLUME_MODE Setting
    int32_t  paramDbxTotalVolumeMode;
    ///DBX PARAM:TOTAL_SURROUND_MODE Setting
    int32_t  paramDbxTotalSurroundMode;
} AdvancedSoundParam;

#endif //__AudioManager_TYPEDEFINE_H__
