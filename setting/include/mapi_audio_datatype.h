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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAPI_AUDIO_DATATYPE_H_
#define _MAPI_AUDIO_DATATYPE_H_

#include "mapi_types.h"

#define TV_NTSC                             0
#define TV_PAL                              1
#define TV_CHINA                            2

//------------------------------- AUDIO_SYSTEM_SEL -----------------------------------
#define AUDIO_SYSTEM_BTSC                   0
#define AUDIO_SYSTEM_A2                     1
#define AUDIO_SYSTEM_EIAJ                   2

#ifndef IS_SYSTEM_L_ENABLED
#define IS_SYSTEM_L_ENABLED                 0
#endif

#define AU_DELAY_FOR_ENTERING_MUTE          150
#define AU_DELAY_FOR_LEAVING_MUTE           10
#define AU_SIF_A2_STABLE_CNT                0x30

#define EU_SIF_OUT_FM_OFFSET                21
#define EU_SIF_OUT_NICAM_OFFSET             27

#define EA_SIF_OUT_FM_OFFSET                0
#define EA_SIF_OUT_NICAM_OFFSET             0

/*MENU_KEY definition */
#define KEY_BUF_SIZE 0x8000//32K
#define WRITE_LINE_SIZE 128 //128*16=2048 bytes
#define WRITE_BYTES WRITE_LINE_SIZE*16
#define MENU_KEY_DDR_BASE 0x11400  //Line Address , It must be the same definition with in audio_comm2.h

//==============================================
/// HDMI RX Mode Type
/// AUDIO_HDMI_RX_TYPE_
typedef enum
{
    ///< HDMI RX PCM Mode
    HDMI_RX_PCM_                            = 0x0,
    ///< HDMI RX Dolby Mode
    HDMI_RX_DD_                             = 0x1,
    ///< HDMI RX DTS Mode
    HDMI_RX_DTS_                            = 0x2,
    ///< HDMI RX DDP Mode
    HDMI_RX_DDP_                            = 0x3,
    ///< HDMI RX Other Mode
    HDMI_RX_Other_                          = 0x4,
} AUDIO_HDMI_RX_TYPE_;

/// HDMI_TYPE_
#if 0
typedef enum
{
    MSAPI_HDMI_MODE_PCM,    //Analog
    MSAPI_HDMI_MODE_RAW,    //Digital
    MSAPI_HDMI_MODE_UNKNOWN,    //Auto
} HDMI_TYPE_;
#endif
//==============================================
/// SPDIF Tx Mode Type
typedef enum
{
    /// SPDIF output type is PCM
    MSAPI_AUD_SPDIF_PCM_                    =  0,
    /// SPDIF output software OFF, don't use
    MSAPI_AUD_SPDIF_OFF_                    =  1,
    /// SPDIF output type is nonPCM
    MSAPI_AUD_SPDIF_NONPCM_                 =  2,
    /// SPDIF output type is bypass
    MSAPI_AUD_SPDIF_BYPASS_                 =  3,
    /// SPDIF output type is transcode
    MSAPI_AUD_SPDIF_TRANSCODE_              =  4,
} SPDIF_TYPE_;

#endif
