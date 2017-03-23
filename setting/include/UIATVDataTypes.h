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
#ifndef __UIATVTYPES_H__
#define __UIATVTYPES_H__

/// Get Program Ctrl;
typedef enum
{
    ///Get current program number
    GET_CURRENT_PROGRAM_NUMBER = 0,
    ///Get first program number
    GET_FIRST_PROGRAM_NUMBER,
    ///Get next program number
    GET_NEXT_PROGRAM_NUMBER,
    ///Get prev program number
    GET_PREV_PROGRAM_NUMBER,
    ///Get past program number
    GET_PAST_PROGRAM_NUMBER,
    ///Is program number active
    IS_PROGRAM_NUMBER_ACTIVE,
    ///Is program empty
    IS_PROGRAM_EMPTY,
    ///Get active program count
    GET_ACTIVE_PROGRAM_COUNT,
    ///Get non skip program count
    GET_NON_SKIP_PROGRAM_COUNT,
    ///Get channel max
    GET_CHANNEL_MAX,
    ///Get channel min
    GET_CHANNEL_MIN

} EN_GET_RPOGRAM_CTRL;
/// Define the Channel Search type
    typedef enum
    {
        /// Search Left
        E_CHANNEL_SEARCH_LEFT,
        /// Search Right
        E_CHANNEL_SEARCH_RIGHT,
        ///No Search Type
        E_CHANNEL_SEARCH_NONE,
    } EN_CHANNEL_SEARCH_TYPE;
///GET PROGRAM INFO;
typedef enum
{
    /// Get fine tune frequency
    GET_FINE_TUNE = 0,
    /// Get Program PLL number
    GET_PROGRAM_PLL_DATA,
    /// Get Program Audio Standard
    GET_AUDIO_STANDARD,
    /// Get Program Video Standard
    GET_VIDEO_STANDARD_OF_PROGRAM,
    /// Get Program DUAL AUDIO Selection
    GET_DUAL_AUDIO_SELECTED,
    /// Is Program need to skip
    IS_PROGRAM_SKIPPED,
    /// Is Program lock
    IS_PROGRAM_LOCKED,
    /// Is Program need to hide
    IS_PROGRAM_HIDE,
    /// Is Program need to AFT
    IS_AFT_NEED,
    /// Is Direct Tuned
    IS_DIRECT_TUNED,
    /// Get AFT Offset
    GET_AFT_OFFSET,
    /// Is realtime audio detection enable
    IS_REALTIME_AUDIO_DETECTION_ENABLE,
    /// Get station name
    GET_STATION_NAME,
    /// Get Sorting priority
    GET_SORTING_PRIORITY,
    /// Get Channel Index
    GET_CHANNEL_INDEX,
#if (ISDB_SYSTEM_ENABLE == 1)
    ///Get ATV auto color
    GET_ATV_AUTOCOLOR,
#endif
    /// Get MISC Information
    GET_MISC

} EN_GET_PROGRAM_INFO;
/// define the sound system
    typedef enum
    {
        /// BG
        E_SYSTEM_MODE_BG = 0,
        /// I
        E_SYSTEM_MODE_I ,
        /// DK
        E_SYSTEM_MODE_DK ,
        /// L
        E_SYSTEM_MODE_L ,
        /// M
        E_SYSTEM_MODE_M ,
        /// the total counts of this enum
        E_SYSTEM_MODE_MAX_COUNT ,

    } EN_MSRV_UI_SOUND_SYSTEM;
/// AUDIO STANDARD
typedef enum
{
    /// Audio Standard BG
    E_AUDIOSTANDARD_BG          = 0x00,
    /// Audio Standard BG A2
    E_AUDIOSTANDARD_BG_A2       = 0x01,
    /// Audio Standard BG Nicam
    E_AUDIOSTANDARD_BG_NICAM    = 0x02,
    /// Audio Standard I
    E_AUDIOSTANDARD_I           = 0x03,
    /// Audio Standard DK
    E_AUDIOSTANDARD_DK          = 0x04,
    /// Audio Standard DK1
    E_AUDIOSTANDARD_DK1_A2      = 0x05,
    /// Audio Standard DK2
    E_AUDIOSTANDARD_DK2_A2      = 0x06,
    /// Audio Standard DK3
    E_AUDIOSTANDARD_DK3_A2      = 0x07,
    /// Audio Standard DK NICAM
    E_AUDIOSTANDARD_DK_NICAM    = 0x08,
    /// Audio Standard L
    E_AUDIOSTANDARD_L           = 0x09,
    /// Audio Standard M
    E_AUDIOSTANDARD_M           = 0x0A,
    /// Audio Standard M BTSC
    E_AUDIOSTANDARD_M_BTSC      = 0x0B,
    /// Audio Standard M A2
    E_AUDIOSTANDARD_M_A2        = 0x0C,
    /// Audio Standard M EIAJ
    E_AUDIOSTANDARD_M_EIA_J     = 0x0D,
    /// Audio Standard Nonstandard
    E_AUDIOSTANDARD_NOTSTANDARD = 0x0F
} EN_MSRV_AUDIOSTANDARD_TYPE;
/// define the ATV manual tuning mode
    typedef enum
    {
        /// search one channel, direction = up
        E_MANUAL_TUNE_MODE_SEARCH_ONE_TO_UP,
        /// search one channel, direction = down
        E_MANUAL_TUNE_MODE_SEARCH_ONE_TO_DOWN,
        /// fine tune to a given frequency
        E_MANUAL_TUNE_MODE_FINE_TUNE_ONE_FREQUENCY,
        /// fine tune, direction = up
        E_MANUAL_TUNE_MODE_FINE_TUNE_UP,
        /// fine tune, direction = down
        E_MANUAL_TUNE_MODE_FINE_TUNE_DOWN,
        /// undefine
        E_MANUAL_TUNE_MODE_UNDEFINE,
    } eAtvManualTuneMode;
///Set Program Info
typedef enum
{
    ///Set program pll data
    SET_PROGRAM_PLL_DATA = 0,
    ///Set audio standard
    SET_AUDIO_STANDARD,
    ///Set video standard of program
    SET_VIDEO_STANDARD_OF_PROGRAM,
    ///Skip program
    SKIP_PROGRAM,
    ///Hide program
    HIDE_PROGRAM,
    ///Lock program
    LOCK_PROGRAM,
    ///Need aft
    NEED_AFT,
    ///Set direct tuned
    SET_DIRECT_TUNED,
    ///Set AFT offset
    SET_AFT_OFFSET,
    ///Enable realtime audio detection
    ENABLE_REALTIME_AUDIO_DETECTION,
    ///Set station name
    SET_STATION_NAME,
    ///Set sorting priority
    SET_SORTING_PRIORITY,
    ///Set channel index
    SET_CHANNEL_INDEX,
#if (ISDB_SYSTEM_ENABLE == 1)
    ///Get ATV auto color
    SET_ATV_AUTOCOLOR,
#endif
    ///Set misc
    SET_MISC

} EN_SET_PROGRAM_INFO;
typedef enum
{
    /// NONE
    E_ANTENNA_TYPE_NONE,
    /// Air
    E_ANTENNA_TYPE_AIR,
    /// Cable
    E_ANTENNA_TYPE_CABLE,
} EN_ANTENNA_TYPE;

/// Database Type
    typedef enum
    {
        /// ATV Database invalid
        DB_INVALID=-1,
        /// ATV Database for dvbt
        DVBT_DB=0,
        /// ATV Database for dvbc
        DVBC_DB
    } DB_TYPE;
/// Set Rpogram Ctrl
typedef enum
{
    /// Reset channel data
    RESET_CHANNEL_DATA = 0,
    /// Init all channel data
    INIT_ALL_CHANNEL_DATA,
    /// Set current program number
    SET_CURRENT_PROGRAM_NUMBER,
    /// Inc current program number
    INC_CURRENT_PROGRAM_NUMBER,
    /// Dec current program number
    DEC_CURRENT_PROGRAM_NUMBER,
    /// Delete program
    DELETE_PROGRAM,
    /// Move program
    MOVE_PROGRAM,
    /// Swap program
    SWAP_PROGRAM,
    /// Copy program
    COPY_PROGRAM,
    /// Move program By Channel List Index Number
    MOVE_PROGRAM_BY_CH_LIST

} EN_SET_RPOGRAM_CTRL;
/// the first program number
#if (ATSC_SYSTEM_ENABLE == 1)
#define ATV_FIRST_PR_NUM                            1
#else
#define ATV_FIRST_PR_NUM                            0
#endif
/// Medium type
    typedef enum
    {
        ///< Medium type Cable
        MEDIUM_CABLE,
        ///< Medium type Air
        MEDIUM_AIR
    } MEDIUM;
/// COMMON COMMAND;
typedef enum
{
    /// Initial atv data manager
    INITIAL_ATV_DATA_MANAGER = 0,
    /// Reset atv data manager
    RESET_ATV_DATA_MANAGER,
    /// Sort program
    SORT_PROGRAM,
    /// Convert program number to ordinal number
    CONVERT_PROGRAM_NUMBER_TO_ORDINAL_NUMBER,
    /// Convert ordinal number to program number
    CONVERT_ORDINAL_NUMBER_TO_PROGRAM_NUMBER,
    /// Get audio mode
    GET_AUDIO_MODE,
    /// Set audio mode
    SET_AUDIO_MODE

} EN_COMMON_COMMAND;


#endif