//<MStar Software>
//******************************************************************************
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


#ifndef _MAPI_VIDEO_DATATYPE_H_
#define _MAPI_VIDEO_DATATYPE_H_

#include "mapi_types.h"


/// dynamic scalering height
#define DYNAMIC_SCALING_VB_H        1920
/// dynamic scalering width
#define DYNAMIC_SCALING_VB_V        1080

/// dynamic scalering 4k2k width
#define DYNAMIC_SCALING_VB_4k_H        3840
/// dynamic scalering 4k2k height
#define DYNAMIC_SCALING_VB_4k_V        2160

///////////////////////////
// HDR metadata type define
/// HDR metadata none type.
#define HDR_METATYPE_NONE 0x0000
/// HDR metadata MPEG VUI type. Document : JCTVC-P1005_v1_Annex_E_changes_for_Q0084_r1
#define HDR_METATYPE_MPEG_VUI 0x0001
/// HDR metadata MPEG SEI Tone mapping type. Document : w14700 SEI - D.2.15 : Tone mapping information SEI message syntax
#define HDR_METADATA_MPEG_SEI_TONE_MAPPING 0x0002
/// HDR metadata MPEG SEI mastering color volume type. Document : w14700 SEI - D.2.27 : Mastering display colour volume SEI message syntax
#define HDR_METADATA_MPEG_SEI_MASTERING_COLOR_VOLUME 0x0004
/// HDR metadata MPEG SEI Knee function type. Document : w14700 SEI - D.2.31 : Knee function information SEI message syntax
#define HDR_METADATA_MPEG_SEI_KNEE_FUNCTION 0x0008
/// HDR metadata HDMI infoframe type. Document : CEA-861.3_V16BallotDraft
#define HDR_METADATA_HDMI_INFOFRAME 0x0010

///////////////////////////
// Define VDEC FW_DS capacity
///////////////////////////
#define DS_ENHANCE_MODE_3D                            (1 << 0)  // on: mvc       off: non-mvc
#define DS_ENHANCE_MODE_RESET_DISP_WIN                (1 << 1)  // on: new ds    off: old ds
#define DS_ENHANCE_MODE_EXTERNAL_DS_BUF               (1 << 2)  // on: external DS buffer.
#define DS_ENHANCE_MODE_MHP                           (1 << 3)  // on: MHP mode, off: non-MHP mode.
#define DS_ENHANCE_MODE_RESET_CAP_WIM                 (1 << 4)  // on: AR change DS, off: not change AR change DS
#define DS_ENHANCE_MODE_RESET_DISP_WIN_WO_SEQ_CHANGE  (1 << 5)
#define DS_ENHANCE_MODE_ENABLE_DNR_SETTINGS           (1 << 6)

///Mute Engine define
typedef enum _MuteEngine
{
    MUTE_ENGINE_XC = 0,
    MUTE_ENGINE_SOC,
    MUTE_ENGINE_BACKEND,
    MUTE_ENGINE_BACKEND_VIDEO_ONLY,
    MUTE_ENGINE_MAX,
    MUTE_ENGINE_NONE = MUTE_ENGINE_MAX,
} E_MUTE_ENGINE;
///Mute Engine define
typedef enum _MuteLock
{
    MUTE_LOCK_AP = 0,
    MUTE_LOCK_RESERVE_1,
    MUTE_LOCK_RESERVE_2,
    MUTE_LOCK_RESERVE_3,
} E_MUTE_LOCK;

/// ADC setting index
typedef enum _AdcSetIndexType
{
    /// ADC seting VGA
    ADC_SET_VGA,
    /// ADC seting YPBPR_SD
    ADC_SET_YPBPR_SD,
    /// ADC seting YPBPR_HD
    ADC_SET_YPBPR_HD,

    ADC_SET_SCART_RGB,
    /// ADC seting YPBPR2_SD
    ADC_SET_YPBPR2_SD,
    /// ADC seting YPBPR2_HD
    ADC_SET_YPBPR2_HD,
    /// ADC seting YPBPR3_SD
    ADC_SET_YPBPR3_SD,
    /// ADC seting YPBPR3_HD
    ADC_SET_YPBPR3_HD,
    /// ADC seting ADC_SET_SCART_RGB

    /// ADC seting number
    ADC_SET_NUMS
} E_ADC_SET_INDEX;

/// NLA setting index
typedef enum _NlaSetIndexType
{
    /// NLA seting VOLUME
    NLA_SET_VOLUME,
    /// NLA seting BRIGHTNESS
    NLA_SET_BRIGHTNESS,
    /// NLA seting CONTRAST
    NLA_SET_CONTRAST,
    /// NLA seting SATURATION
    NLA_SET_SATURATION,
    /// NLA seting HUE
    NLA_SET_HUE,
    /// NLA seting SHARPNESS
    NLA_SET_SHARPNESS,
    /// NLA seting BACKLIGHT
    NLA_SET_BACKLIGHT,
} E_NLA_SET_INDEX;

/// Define calibration mode
typedef enum
{
    E_MAPI_CALIBRATION_MODE_HW,  ///< hardware calibration mode
    E_MAPI_CALIBRATION_MODE_SW,  ///< software calibration mode
    E_MAPI_CALIBRATION_MODE_NUMS,  ///< number of calibration mode
}EN_MAPI_CALIBRATION_MODE;

namespace mapi_video_datatype
{
    /// Define aspect ratio type
    typedef enum
    {
        /// Default
        E_AR_DEFAULT = 0,
        /// 16x9
        E_AR_16x9,
        /// 4x3
        E_AR_4x3,
        /// Auto
        E_AR_AUTO,
        /// Panorama
        E_AR_Panorama,
        /// Just Scan
        E_AR_JustScan,
        /// Zoom 1
        E_AR_Zoom1,
        /// Zoom 2
        E_AR_Zoom2,
        E_AR_14x9,
        /// point to point
        E_AR_DotByDot,
         /// Subtitle
        E_AR_Subtitle,
        /// movie
        E_AR_Movie,
        /// Personal
        E_AR_Personal,
        /// 4x3 Panorama
        E_AR_4x3_PanScan,
        /// 4x3 Letter Box
        E_AR_4x3_LetterBox,
        /// 16x9 PillarBox
        E_AR_16x9_PillarBox,
        /// 16x9 PanScan
        E_AR_16x9_PanScan,
        /// 4x3 Combind
        E_AR_4x3_Combind,
        /// 16x9  Combind
        E_AR_16x9_Combind,
        /// Zoom 2X
        E_AR_Zoom_2x,
        /// Zoom 3X
        E_AR_Zoom_3x,
        /// Zoom 4X
        E_AR_Zoom_4x,
        /// In front of E_AR_CUS is Supernova area and the customization area at the back of E_AR_CUS.
        E_AR_CUS =0x20,
        /// Maximum value of this enum
        E_AR_MAX=0x40,
    } MAPI_VIDEO_ARC_Type;

    ///Define HDMI resolution type
    typedef enum
    {
        ///480i_60
        E_HDMI480i_60,
        ///480p_60
        E_HDMI480p_60,
        ///576i_50
        E_HDMI576i_50,
        ///576p_50
        E_HDMI576p_50,
        ///720p_60
        E_HDMI720p_60,
        ///720p_50
        E_HDMI720p_50,
        ///1080i_60
        E_HDMI1080i_60,
        ///1080i_50
        E_HDMI1080i_50,
        ///1080p_60
        E_HDMI1080p_60,
        ///1080p_50
        E_HDMI1080p_50,
        ///1080p_30
        E_HDMI1080p_30,
        ///1080p_24
        E_HDMI1080p_24,
        ///1440x480i_60
        E_HDMI1440x480i_60,
        ///1440x480p_60
        E_HDMI1440x480p_60,
        ///1440x576i_50
        E_HDMI1440x576i_50,
        ///1440x576p_50
        E_HDMI1440x576p_50,
        ///PC timing 640x480_60
        E_HDMI_PC_640_480_60,
        ///PC timing 640x480_72
        E_HDMI_PC_640_480_72,
        ///PC timing 640x480_75
        E_HDMI_PC_640_480_75,
        ///PC timing 640x480_85
        E_HDMI_PC_640_480_85,
        ///PC timing 720x400_60
        E_HDMI_PC_720_400_60,
        ///PC timing 800x600_56
        E_HDMI_PC_800_600_56,
        ///PC timing 800x600_60
        E_HDMI_PC_800_600_60,
        ///PC timing 800x600_72
        E_HDMI_PC_800_600_72,
        ///PC timing 800x600_75
        E_HDMI_PC_800_600_75,
        ///PC timing 800x600_85
        E_HDMI_PC_800_600_85,
        ///PC timing 1024x768_50
        E_HDMI_PC_1024_768_50,
        ///PC timing 1024x768_60
        E_HDMI_PC_1024_768_60,
        ///PC timing 1024x768_70
        E_HDMI_PC_1024_768_70,
        ///PC timing 1024x768_75
        E_HDMI_PC_1024_768_75,
        ///PC timing 1024x768_85
        E_HDMI_PC_1024_768_85,
        ///PC timing 1152x864_70
        E_HDMI_PC_1152_864_70,
        ///PC timing 1152x864_75
        E_HDMI_PC_1152_864_75,
        ///PC timing 1152x864_85
        E_HDMI_PC_1152_864_85,
        ///PC timing 1280x960_60
        E_HDMI_PC_1280_960_60,
        ///PC timing 1280x960_75
        E_HDMI_PC_1280_960_75,
        ///PC timing 1280x960_85
        E_HDMI_PC_1280_960_85,
        ///PC timing 1280x800_60
        E_HDMI_PC_1280_800_60,
        ///PC timing 1280x768_60
        E_HDMI_PC_1280_768_60,
        ///PC timing 1280x1024_60
        E_HDMI_PC_1280_1024_60,
        ///PC timing 1280x1024_75
        E_HDMI_PC_1280_1024_75,
        ///PC timing 1280x1024_85
        E_HDMI_PC_1280_1024_85,
        ///PC timing 1360x768_60
        E_HDMI_PC_1360_768_60,
        ///PC timing 1360x768_60
        E_HDMI_PC_1366_768_60,
        //2160p_24
        E_HDMI2160p_24,
        //2160p_25
        E_HDMI2160p_25,
        //2160p_30
        E_HDMI2160p_30,
        // 2160p_50
        E_HDMI2160p_50,
        // 2160p_60
        E_HDMI2160P_60,
        ///MAX
        E_HDMI_MAX,
    } MAX_HDMI_Resolution_Info;

    ///Define component resolution type
    typedef enum
    {
        ///480i_60
        E_YPbPr480i_60,
        ///480p_60
        E_YPbPr480p_60,
        ///576i_50
        E_YPbPr576i_50,
        ///576p_50
        E_YPbPr576p_50,
        ///720p_60
        E_YPbPr720p_60,
        ///720p_50
        E_YPbPr720p_50,
        ///1080i_60
        E_YPbPr1080i_60,
        ///1080i_50
        E_YPbPr1080i_50,
        ///1080p_60
        E_YPbPr1080p_60,
        ///1080p_50
        E_YPbPr1080p_50,
        ///1080p_30
        E_YPbPr1080p_30,
        ///1080p_24
        E_YPbPr1080p_24,
        ///1080p_25
        E_YPbPr1080p_25,
        ///Max
        E_YPbPr_MAX,
    } MAX_YPbPr_Resolution_Info;

    ///Define video zoom level
    typedef enum
    {
        /// zoom1_4
        E_VIDEO_ZOOM1_4 = 0,
        /// zoom1_2
        E_VIDEO_ZOOM1_2,
        /// no zoom
        E_VIDEO_NO_ZOOM,
        /// zoom1
        E_VIDEO_ZOOM1,
        /// zoom2
        E_VIDEO_ZOOM2,
        /// zoom3
        E_VIDEO_ZOOM3,
        /// current zoom
        E_VIDEO_CURRENT_ZOOMLEVEL,
    } EN_MAPI_VIDEO_ZOOM_LEVEL;

    /// the display color when screen mute
    typedef enum
    {
        E_COLOR_SPACE_RGB332 = 0,
        E_COLOR_SPACE_RGB233,
        E_COLOR_SPACE_ARGB8888,
        E_COLOR_SPACE_UYV888,
        E_COLOR_SPACE_YUV332,
        E_COLOR_SPACE_YUV422,
        E_COLOR_SPACE_R10,
        E_COLOR_SPACE_G10,
        E_COLOR_SPACE_B10,
        E_COLOR_SPACE_U10,
        E_COLOR_SPACE_Y10,
        E_COLOR_SPACE_V10,
        /// counts of this enum
        E_COLOR_SPACE_NUMBER,
    } MAPI_VIDEO_COLOR_SPACE;
    /// the display color when screen mute
    typedef enum
    {
        /// black
        E_SCREEN_MUTE_BLACK = 0,
        /// white
        E_SCREEN_MUTE_WHITE,
        /// red
        E_SCREEN_MUTE_RED,
        /// blue
        E_SCREEN_MUTE_BLUE,
        /// green
        E_SCREEN_MUTE_GREEN,
        /// counts of this enum
        E_SCREEN_MUTE_NUMBER,
    } MAPI_VIDEO_Screen_Mute_Color;

    /// 3D aspect ratio type
    typedef enum
    {
        E_3D_AR_FULL = 0,   // full screen
        E_3D_AR_AUTO,       // auto adapt
        E_3D_AR_CENTER,     // centering
    } MAPI_VIDEO_3D_ARC_Type;

    /// to define the structure for the video ARC info
    typedef struct
    {
        MAPI_VIDEO_ARC_Type enARCType;///< ARC index
        MAPI_VIDEO_3D_ARC_Type en3DARCType;///< 3D ARC type
        MAPI_S16 s16Adj_ARC_Left;     ///< adjust ARC Left
        MAPI_S16 s16Adj_ARC_Right;    ///< adjust ARC Right
        MAPI_S16 s16Adj_ARC_Up;       ///< adjust ARC Up
        MAPI_S16 s16Adj_ARC_Down;     ///< adjust ARC Down

        MAPI_BOOL bSetCusWin;      ///< Set customize win
        EN_MAPI_VIDEO_ZOOM_LEVEL enZoomLevel;   ///  zoom level
    } ST_MAPI_VIDEO_ARC_INFO;

    /// to define the structure for the video window type
    typedef struct
    {
        MAPI_U16 x;         ///<start x of the window
        MAPI_U16 y;         ///<start y of the window
        MAPI_U16 width;     ///<width of the window
        MAPI_U16 height;    ///<height of the window
    } ST_MAPI_VIDEO_WINDOW_TYPE;

    /// to define the scaler information for dynamic scaling (DS)
    typedef struct
    {
        // 0x000
        MAPI_U8 u8DSVersion;                  /// Versin
        MAPI_U8 bHKIsUpdating;                /// House keeping is writing
        MAPI_U8 bFWIsUpdating;                /// firmware is reading
        MAPI_U8 bFWGotXCInfo;                 /// for firmware internal use, indicate that firmware received XC current setting
        MAPI_U8 u8XCInfoUpdateIdx;            /// XC info
        MAPI_U8 bFWGotNewSetting;             /// for firmware internal use, indicate that firmware received XC current setting
        MAPI_U8 u8Dummy_3;                    /// u8Dummy_3
        MAPI_U8 u8Dummy_2;                    /// u8Dummy_2

        // 0x008
        ST_MAPI_VIDEO_WINDOW_TYPE stCapWin;   ///capture window
        ST_MAPI_VIDEO_WINDOW_TYPE stCropWin;  ///croping window

        // 0x018
        ST_MAPI_VIDEO_WINDOW_TYPE stDispWin;  ///display window
        MAPI_U16 u16H_SizeAfterPreScaling;    //horizontal size
        MAPI_U16 u16V_SizeAfterPreScaling;    //vertical size
        MAPI_U32 u32PNL_WIDTH;                /// Panel width

        // 0x028
        MAPI_U32 u32IPMBase0;                  ///<IPM base 0
        MAPI_U32 u32IPMBase1;                  ///<IPM base 1
        MAPI_U32 u32IPMBase2;                  ///<IPM base 2

        // 0x034
        ST_MAPI_VIDEO_WINDOW_TYPE stNewCropWin;                ///< Zoom in/out new crop win
        ST_MAPI_VIDEO_WINDOW_TYPE stNewDispWin;                ///< Zoom in/out new disp win

        // 0x044
        MAPI_U8 bLinearMode;                  ///<Is current memory format LinearMode?
        MAPI_U8 u8BitPerPixel;                ///<Bits number Per Pixel
        MAPI_U8 bInterlace;                   ///<Interlaced or Progressive
        MAPI_U8 u8StoreFrameNum;              ///<Store frame number

        // 0x048
        MAPI_U16 u16IPMOffset;                ///<IPM offset
        MAPI_U8 u8GetCapacity;                /// dummy0 for Get
        MAPI_U8 u8SetCapacity;                /// dummy0 for Set

        // 0x04C
        MAPI_U8 bMirrorMode;                  ///<mirror mode
        MAPI_U8 bResolutionChanging;          ///<indicate the resolution will be changed.
        MAPI_U8 u8MVOPMirror;                 ///<MVOP Mirror
        MAPI_U8 u8Dummy2;                     ///dummy2

        // internal use only
        // 0x050
        ST_MAPI_VIDEO_WINDOW_TYPE stDSScaledCropWin;  ///dynamic scalering croping window

        // 0x058
        MAPI_U16 u16SizeAfterPreScaling;      ///size after pre sacling
        MAPI_U16 u16Fetch;                    ///fetch
        MAPI_U16 u16Offset;                   ///offset
        MAPI_U16 u16PixelOffset;              ///Pixel offset
        MAPI_U16 u16LineBufOffset;            ///Line Buffer Offset
        MAPI_U16 u16Dummy1;                   ///Dummy1

        // 0x064
        MAPI_U32 u32CropOffset;               ///crop offset

        // for debugging, 0x68
        MAPI_U8 OPRegMaxDepth;                /// point to record max OP reg depth
        MAPI_U8 IPRegMaxDepth;                /// point to record max IP reg depth
        MAPI_U8 ErrorCode;                    /// point to record error code
        MAPI_U8 u8Dummy3;                     /// dummy

        // 0x6C
        //MAPI_U16 u16CodedWidth;                  /// codec width
        //MAPI_U16 u16CodedHeight;                 /// codec height
        //MAPI_U16 u16DSBufIdx;                    /// dynamic scalering Buffer index
        ST_MAPI_VIDEO_WINDOW_TYPE stDSCropWin;   /// dynamic scaalering crop window

        // 0x74
        MAPI_U16 u16HCusScalingSrc;        ///< horizontal scaling down/up source size
        MAPI_U16 u16VCusScalingSrc;        ///< vertical scaling down/up source size
        MAPI_U16 u16HCusScalingDst;        ///< horizontal prescaling down/up destination size
        MAPI_U16 u16VCusScalingDst;        ///< vertical prescaling down/up destination size

        // 0x7C
        //////E_XC_3D_INPUT_MODE  e3DInputType;        ///< input 3D type decided by APP layer
        //////E_XC_3D_OUTPUT_MODE e3DOutputType;       ///< output 3D type decided by APP layer
        MAPI_U32 e3DInputType;              ///< input 3D type decided by APP layer
        MAPI_U32 e3DOutputType;             ///< output 3D type decided by APP layer

        // 0x84
        MAPI_U16 u16MVOPHStart;              ///<MVOP HStart
        MAPI_U16 u16MVOPVStart;              ///<MVOP VStart

        // 0x88
        MAPI_U16 u16CurrentFrameHSize;        ///<Current frame horizontal active size.
        MAPI_U16 u16CurrentFrameVSize;        ///<Current frame vertical active size.
        MAPI_U16 u16NextFrameHSize;           ///<Next frame horizontal active size.
        MAPI_U16 u16NextFrameVSize;           ///<Next frame vertical active size.
        MAPI_U16 u16VsyncCNT;                 ///<vsync count

        // 0x92
        //MAPI_U8 u8Dummy4;
        MAPI_U8 u8FRCMStoreFrameNum;
        MAPI_U8 bUseVBoxOfHK;

        // 0x94
        MAPI_U16 u16VirtualBoxWidth;
        MAPI_U16 u16VirtualBoxHeight;

        //0x98
        MAPI_U16 u16InputVFreq;

        //0x9A
        MAPI_U32 u32FRCMBase0;                  ///<FRCM base 0
        MAPI_U32 u32FRCMBase1;                  ///<FRCM base 1
        MAPI_U32 u32FRCMBase2;                  ///<FRCM base 2
        
        //0xA6
        MAPI_U8 bFBL;                  ///<bFBL
        MAPI_U8 bR_FBL;                ///<bR_FBL

        //0xA8
        MAPI_U8 bFRC;                  ///<bFRC        
    } ST_MM_DS_XC_STATUS;




    /// to define the information for dynamic scaling (DS)
    typedef struct
    {
        MAPI_U32  u32DS_Info_BaseAddr;        ///< The memory base address to update IP/OP dynamic scaling registers. Absolute without any alignment.
        MAPI_U8   u8MIU_Select;               ///< 0: MIU0, 1: MIU1, etc.
        MAPI_U8   u8DS_Index_Depth;           ///< The index depth (how many entries to fire per MVOP Vsync falling) of DS
        MAPI_BOOL bOP_DS_On;                  ///< OP dynamic scaling on/off
        MAPI_BOOL bIPS_DS_On;                 ///< IPS dynamic scaling on/off
        MAPI_BOOL bIPM_DS_On;                 ///< IPM dynamic scaling on/off
    } ST_MAPI_DYNAMICSCALING_INFO;

    /// to define the video status
    typedef struct
    {
        // Capture_Memory
        MAPI_U32 u32IPMBase0;             ///<IPM base 0
        MAPI_U32 u32IPMBase1;             ///<IPM base 1
        MAPI_U32 u32IPMBase2;             ///<IPM base 2
        MAPI_U16 u16IPMOffset;            ///<IPM offset
        MAPI_U32 u16IPMFetch;             ///<IPM fetch

        //----------------------
        // Window
        //----------------------
        ST_MAPI_VIDEO_WINDOW_TYPE stCapWin;       ///<Capture window
        ST_MAPI_VIDEO_WINDOW_TYPE stDispWin;      ///<Display window
        ST_MAPI_VIDEO_WINDOW_TYPE stCropWin;      ///<Crop window

        //----------------------
        // Timing
        //----------------------
        MAPI_BOOL bInterlace;             ///<Interlaced or Progressive

        //----------------------
        // XC internal setting
        //----------------------

        /* scaling ratio */
        MAPI_U16 u16H_SizeAfterPreScaling;         ///<Horizontal size after prescaling
        MAPI_U16 u16V_SizeAfterPreScaling;         ///<Vertical size after prescaling
        MAPI_BOOL bPreV_ScalingDown;         ///<define whether it's pre-Vertical scaling down

        /* real crop win in memory */
        ST_MAPI_VIDEO_WINDOW_TYPE ScaledCropWin;  ///<scaler crop window

        /* Video screen status */
        MAPI_BOOL bBlackscreenEnabled;      ///<Black screen status
        MAPI_BOOL bBluescreenEnabled;       ///<Blue screen status
        MAPI_U16 u16VideoDark;            ///<Video dark

        MAPI_U16 u16BytePerWord;          ///<BytePerWord in Scaler
        MAPI_U8 u8BitPerPixel;            ///<Bits number Per Pixel
        MAPI_BOOL bLinearMode;            ///<Is current memory format LinearMode?
        MAPI_BOOL bFBL;                   ///<Is framebufferless case
        MAPI_U16 u16InputVFreq;           ///<input vfreq
    }ST_MAPI_VIDEO_STATUS;

    /// Define 3D input type
    typedef enum
    {
        //range [0000 ~ 1111] reserved for hdmi 3D spec
        /// 3D input type is Frame Packing
        E_3D_INPUT_FRAME_PACKING                     = 0x00, //0000
        /// 3D input type is Field Alternative
        E_3D_INPUT_FIELD_ALTERNATIVE                 = 0x01, //0001
        /// 3D input type is Line Alternativ
        E_3D_INPUT_LINE_ALTERNATIVE                  = 0x02, //0010
        /// 3D input type is Side Full
        E_3D_INPUT_SIDE_BY_SIDE_FULL                 = 0x03, //0011
        /// 3D input type is L Depth
        E_3D_INPUT_L_DEPTH                           = 0x04, //0100
        /// 3D input type is LDepth Graphics Graphics Depth
        E_3D_INPUT_L_DEPTH_GRAPHICS_GRAPHICS_DEPTH   = 0x05, //0101
        /// 3D input type is Top and Bottom
        E_3D_INPUT_TOP_BOTTOM                        = 0x06, //0110
        /// 3D input type is Side by Side Half
        E_3D_INPUT_SIDE_BY_SIDE_HALF                 = 0x08, //1000

        /// 3D input type is Check board
        E_3D_INPUT_CHECK_BORAD                       = 0x09,

        /// 3D input type is User
        E_3D_INPUT_MODE_USER                         = 0x10,
        /// 3D input type is None
        E_3D_INPUT_MODE_NONE                         = E_3D_INPUT_MODE_USER,
        /// 3D input type is Frame Alternative
        E_3D_INPUT_FRAME_ALTERNATIVE,
        /// 3D input type is Side by Side Half Interlace
        E_3D_INPUT_SIDE_BY_SIDE_HALF_INTERLACE,
        /// 3D input type is Frame Packing Opt
        E_3D_INPUT_FRAME_PACKING_OPT,
        /// 3D input type is Top and Bottom Opt
        E_3D_INPUT_TOP_BOTTOM_OPT,
        /// 3D input type is Normal 2d
        E_3D_INPUT_NORMAL_2D,
        /// 3D input type is Normal 2d interlace
        E_3D_INPUT_NORMAL_2D_INTERLACE,
        /// 3D input type is normal 2d interlace point to point
        E_3D_INPUT_NORMAL_2D_INTERLACE_PTP,
        /// 3D input type is HW Normal 2d
        E_3D_INPUT_NORMAL_2D_HW,
        /// 3D input type is Pixel Alternative
        E_3D_INPUT_PIXEL_ALTERNATIVE,
        /// Maximum number of 3D input type
        E_3D_INPUT_TYPE_NUM,
    }EN_3D_INPUT_TYPE;

    /// Define 3D output type
    typedef enum
    {
        /// 3D output type is None
        E_3D_OUTPUT_MODE_NONE,
        /// 3D output type is Line Alternativ
        E_3D_OUTPUT_LINE_ALTERNATIVE ,
        /// 3D output type is Top and Bottom
        E_3D_OUTPUT_TOP_BOTTOM,
        /// 3D output type is Side by Side Half
        E_3D_OUTPUT_SIDE_BY_SIDE_HALF,
        /// 3D output type is Frame Alternativ
        E_3D_OUTPUT_FRAME_ALTERNATIVE,       //25-->50,30-->60,24-->48,50-->100,60-->120----FRC 1:2
        /// 3D output type is Frame L
        E_3D_OUTPUT_FRAME_L,
        /// 3D output type is Frame R
        E_3D_OUTPUT_FRAME_R,
        /// 3D output type is Frame Alternative NoRFC
        E_3D_OUTPUT_FRAME_ALTERNATIVE_NOFRC,  //50->50, 60->60-------------------------------FRC 1:1
        /// 3D output type is Frame packing
        E_3D_OUTPUT_FRAME_PACKING,
        /// 3D output type is HW Line Alternativ
        E_3D_OUTPUT_LINE_ALTERNATIVE_HW ,
        /// 3D output type is HW Frame Alternativ
        E_3D_OUTPUT_FRAME_ALTERNATIVE_HW ,
        /// 3D output type is HW Check Board
        E_3D_OUTPUT_CHECKBOARD_HW,
        /// 3D output type is HW Pixel Alternativ
        E_3D_OUTPUT_PIXEL_ALTERNATIVE_HW,
        /// 3D output type is HW Frame L
        E_3D_OUTPUT_FRAME_L_HW,
        /// 3D output type is HW Frame R
        E_3D_OUTPUT_FRAME_R_HW,
        /// 3D output type is HW Top and Bottom
        E_3D_OUTPUT_TOP_BOTTOM_HW,
        /// 3D output type is HW Side by Side Half
        E_3D_OUTPUT_SIDE_BY_SIDE_HALF_HW,
        /// 3D output type is HW Frame packing
        E_3D_OUTPUT_FRAME_PACKING_HW,
        /// Maximum number of 3D output type
        E_3D_OUTPUT_TYPE_NUM,
    }EN_3D_OUTPUT_TYPE;

    /// Define auto detect 3d method
    typedef enum
    {
        EN_3D_AUTODETECT_SW,
        EN_3D_AUTODETECT_HW,
        EN_3D_AUTODETECT_HW_COMPATIBLE,
        EN_3D_AUTODETECT_MAX
    }EN_3D_AUTODETECT_METHOD;

    /// Define 3D info
    typedef struct
    {
        /// Enable / Disable 3D feature
        MAPI_BOOL           bEnable3D;
        /// 3D input type
        EN_3D_INPUT_TYPE    enInput3DMode;
        /// 3D output type
        EN_3D_OUTPUT_TYPE   enOutput3DMode;
    }ST_MAPI_3D_INFO;

    /// the scaler IPM info
    typedef enum
    {
        ///Scaler IPM base 0 addr
        SC_INFO_IPMBase0,
        ///Scaler IPM base 1 addr
        SC_INFO_IPMBase1,
        ///Scaler IPM base 2 addr
        SC_INFO_IPMBase2,
    } MAPI_VIDEO_SC_INFO;

    /// Define hw 2d to 3d para
    typedef struct
    {
        MAPI_U32  u32Hw2dTo3dPara_Version;
        MAPI_U16  u16Concave;
        MAPI_U16  u16Gain;
        MAPI_U16  u16Offset;
        MAPI_U16  u16ArtificialGain;
        MAPI_U16  u16EleSel;
        MAPI_U16  u16ModSel;
        MAPI_U16  u16EdgeBlackWidth;
    }ST_MAPI_3D_HW2DTO3DPARA;

    /// Define detect 3d format para
    typedef struct
    {
        MAPI_U32  u32Detect3DFormatPara_Version;  //version control, back compatible
        MAPI_U16  u16HorSearchRange;              //the horizontal range for find the similar pixel at R image
        MAPI_U16  u16VerSearchRange;              //the vertical range for find the similar pixel at R image
        MAPI_U16  u16GYPixelThreshold;            //g/y pixel threshold for define the similar pixel
        MAPI_U16  u16RCrPixelThreshold;           //r/cr pixel threshold for define the similar pixel
        MAPI_U16  u16BCbPixelThreshold;           //b/cb pixel threshold for define the similar pixel
        MAPI_U16  u16HorSampleCount;              //the horizontal sample count, the total checked pixel will be u16HorSampleCount*u16VerSampleCount
        MAPI_U16  u16VerSampleCount;              //the vertical sample count, the total checked pixel will be u16HorSampleCount*u16VerSampleCount
        MAPI_U16  u16MaxCheckingFrameCount;       //the max checking frame count
        MAPI_U16  u16HitPixelPercentage;          //the percentage about hit pixel in one frame total checked pixel, for example: 70%, need set as 70
        MAPI_BOOL bEnableOverscan;                //detect 3d format for considering overscan shift

        //the area without MVOP black area
        MAPI_U16 u16NonBlockAreaX;
        MAPI_U16 u16NonBlockAreaY;
        MAPI_U16 u16NonBlockAreaWidth;
        MAPI_U16 u16NonBlockAreaHeight;
    }ST_MAPI_3D_DETECT3DFORMATPARA;

    /// Define DWIN format
    typedef enum
    {
        /// CrYCb domain.
        DWIN_FMT_UV7Y8 = 0,
        /// CrYCb domain.
        DWIN_FMT_UV8Y8,
        /// RGB domain (CSC bypass).
        DWIN_FMT_ARGB8888,
        /// RGB domain (CSC bypass).
        DWIN_FMT_RGB565,
    } EN_MAPI_GOP_DWIN_DATA_FMT;

    /// Define for format of pixel 24 bit
    typedef struct
    {
        MAPI_U8 R_Cr;
        MAPI_U8 G_Y;
        MAPI_U8 B_Cb;
    } EN_MAPI_PIXEL_24BIT;

    /// Define for format of pixel 32 bit
    typedef struct
    {
        MAPI_U32 B_Cb   :10;
        MAPI_U32 G_Y    :10;
        MAPI_U32 R_Cr   :10;
        MAPI_U32 u8Dummy:2;
    }EN_MAPI_PIXEL_32BIT;

    /// Define for format of pixel 16 bit
    typedef struct
    {
        MAPI_U8 u8G_Y;
        MAPI_U8 u8BR_CbCr;
    } EN_MAPI_PIXEL_422_8BIT;

    /// Define output data format
    typedef enum
    {
        E_MAPI_XC_OUTPUTDATA_RGB10BITS = 0x00,  ///< Dummy[31:30]  R[29:20]  G[19:10] B[9:0]
        E_MAPI_XC_OUTPUTDATA_RGB8BITS  = 0x01,  ///< R[23:16]  G[15:8] B[7:0]
        E_MAPI_XC_OUTPUTDATA_4228BITS  = 0x03,  ///<   CbCr[15:8] Y[7:0]
    }EN_MAPI_XC_OUTPUTDATA_TYPE;

    /// Define input data format
    typedef enum
    {
        E_MAPI_XC_INPUTDATA_RGB10BITS = 0x00,  ///< Dummy[31:30]  R[29:20]  G[19:10] B[9:0]
        E_MAPI_XC_INPUTDATA_RGB8BITS  = 0x01,  ///< R[23:16]  G[15:8] B[7:0]
        E_MAPI_XC_INPUTDATA_4228BITS  = 0x03,  ///<   CbCr[15:8] Y[7:0]
    }EN_MAPI_XC_INPUTDATA_TYPE;

    /// Define Panel LVDS Channel Type
    typedef enum
    {
        E_MAPI_PNL_LVDS_CHANNEL_A    = 0x0001,
        E_MAPI_PNL_LVDS_CHANNEL_B    = 0x0002,
        E_MAPI_PNL_LVDS_CHANNEL_C    = 0x0004,
        E_MAPI_PNL_LVDS_CHANNEL_D    = 0x0008,
    }EN_MAPI_PNL_LVDS_CHANNEL_TYPE;

    /// Define Panel LVDS Pair Type
    typedef enum
    {
        E_MAPI_PNL_LVDS_PAIR_0    = 0x0001,
        E_MAPI_PNL_LVDS_PAIR_1    = 0x0002,
        E_MAPI_PNL_LVDS_PAIR_2    = 0x0004,
        E_MAPI_PNL_LVDS_PAIR_3    = 0x0008,
        E_MAPI_PNL_LVDS_PAIR_4    = 0x0010,
        E_MAPI_PNL_LVDS_PAIR_5    = 0x0020,
    }EN_MAPI_PNL_LVDS_PAIR_TYPE;

    /// OP2 Video/GOP layer switch
    typedef enum
    {
        E_MAPI_VIDEO_ON_OSD_LAYER_DEAFULT = 0, ///< video -> osd layer 0 -> osd layer 1 -> osd layer 2 -> osd layer 3
        E_MAPI_VIDEO_ON_OSD_LAYER_0 = 1,       ///< osd layer 0 -> video -> osd layer 1 -> osd layer 2 -> osd layer 3
        E_MAPI_VIDEO_ON_OSD_LAYER_1 = 2,       ///< osd layer 0 -> osd layer 1 -> video -> osd layer 2 -> osd layer 3
        E_MAPI_VIDEO_ON_OSD_LAYER_2 = 3,       ///< osd layer 0 -> osd layer 1 -> osd layer 2 -> video -> osd layer 3
        E_MAPI_VIDEO_ON_OSD_LAYER_3 = 4,       ///< osd layer 0 -> osd layer 1 -> osd layer 2 -> osd layer 3 -> video
        E_MAPI_VIDEO_ON_OSD_LAYER_NUM,
    } EN_MAPI_VIDEO_ON_OSD_LAYER;

    /// Define Window position and size attribute
    typedef struct
    {
        MAPI_U16 x;           ///<start x of the window
        MAPI_U16 y;           ///<start y of the window
        MAPI_U16 width;       ///<width of the window
        MAPI_U16 height;      ///<height of the window
    } ST_MAPI_WINDOW_TYPE;

    /// Define DeInterlace mode
    typedef enum
    {

        E_DEINT_OFF=0,         ///<deinterlace mode off
        E_DEINT_2DDI_BOB,      ///<deinterlace mode: BOB
        E_DEINT_2DDI_AVG,      ///<deinterlace mode: AVG
        E_DEINT_3DDI_HISTORY,  ///<deinterlace mode: HISTORY // 24 bit
        E_DEINT_3DDI,          ///<deinterlace mode:3DDI// 16 bit
    } EN_MAPI_DEINTERLACE_MODE;

    /// Image store format in XC
    typedef enum
    {
        E_IMAGE_STORE_444_24BIT,    ///< (8+8+8)   Y Cb Cr   / B G R
        E_IMAGE_STORE_422_16BIT,    ///< (8+8)     Y Cb Y Cr / G B G R
        E_IMAGE_STORE_422_24BIT,    ///< (10+10+4) Y Cb Y Cr / G B G R -- Y7 Y6 Y5 Y4 Y3 Y2 Y1 Y0 - C5 C4 C3 C2 C1 C0 Y9 Y8 - xx xx xx xx C9 C8 C7 C6
    } EN_MAPI_IMAGE_STORE_FMT;

    /// XC API status
    typedef struct
    {
        MAPI_U32 u32ApiStatusEx_Version;   ///<Version of current structure. Please always set to "PANEL_INFO_EX_VERSION" as input
        MAPI_U16 u16ApiStatusEX_Length;    ///<Length of this structure, u16PanelInfoEX_Length=sizeof(XC_PANEL_INFO_EX)

        //----------------------
        // Customer setting
        //----------------------
        MAPI_INPUT_SOURCE_TYPE enInputSourceType;      ///< Input source type

        //----------------------
        // Window
        //----------------------
        ST_MAPI_WINDOW_TYPE stCapWin;       ///<Capture window
        ST_MAPI_WINDOW_TYPE stDispWin;      ///<Display window
        ST_MAPI_WINDOW_TYPE stCropWin;      ///<Crop window

        //----------------------
        // Timing
        //----------------------
        MAPI_BOOL bInterlace;             ///<Interlaced or Progressive
        MAPI_BOOL bHDuplicate;            ///<flag for vop horizontal duplicate, for MVD, YPbPr, indicate input double sampled or not
        MAPI_U16  u16InputVFreq;          ///<Input V Frequency, VFreqx10, for calculate output panel timing
        MAPI_U16  u16InputVTotal;         ///<Input Vertical total, for calculate output panel timing
        MAPI_U16  u16DefaultHtotal;       ///<Default Htotal for VGA/YPbPr input
        MAPI_U8   u8DefaultPhase;         ///<Obsolete, use u16DefaultPhase instead

        //----------------------
        // Post customized scaling
        //----------------------
        MAPI_BOOL bHCusScaling;           ///<assign H customized scaling instead of using XC scaling
        MAPI_U16  u16HCusScalingSrc;      ///<H customized scaling src width
        MAPI_U16  u16HCusScalingDst;      ///<H customized scaling dst width
        MAPI_BOOL bVCusScaling;           ///<assign V manuel scaling instead of using XC scaling
        MAPI_U16  u16VCusScalingSrc;      ///<V customized scaling src height
        MAPI_U16  u16VCusScalingDst;      ///<V customized scaling dst height

        //--------------
        // 9 lattice
        //--------------
        MAPI_BOOL bDisplayNineLattice;    ///<used to indicate where to display in panel and where to put in frame buffer

        //----------------------
        // XC internal setting
        //----------------------

        /* scaling ratio */
        MAPI_U16 u16H_SizeAfterPreScaling;         ///<Horizontal size after prescaling
        MAPI_U16 u16V_SizeAfterPreScaling;         ///<Vertical size after prescaling
        MAPI_BOOL bPreV_ScalingDown;      ///<define whether it's pre-Vertical scaling down

        /* real crop win in memory */
        ST_MAPI_WINDOW_TYPE ScaledCropWin;

        /* others */
        MAPI_U32 u32Op2DclkSet;           ///<OP to Dot clock set

        /* Video screen status */
        MAPI_BOOL bBlackscreenEnabled;      ///<Black screen status
        MAPI_BOOL bBluescreenEnabled;       ///<Blue screen status
        MAPI_U16 u16VideoDark;            ///<Video dark

        MAPI_U16 u16V_Length;             ///<for MDrv_Scaler_SetFetchNumberLimit
        MAPI_U16 u16BytePerWord;          ///<BytePerWord in Scaler
        MAPI_U16 u16OffsetPixelAlignment; ///<Pixel alignment of Offset (including IPM/OPM)
        MAPI_U8 u8BitPerPixel;            ///<Bits number Per Pixel
        EN_MAPI_DEINTERLACE_MODE eDeInterlaceMode;       ///<De-interlace mode
        MAPI_U8 u8DelayLines;             ///<delay lines
        MAPI_BOOL bMemFmt422;             ///<whether memory format is 422, for easy usage
        EN_MAPI_IMAGE_STORE_FMT eMemory_FMT; ///<memory format
        MAPI_BOOL bForceNRoff;            ///<Force NR off
        MAPI_BOOL bEn3DNR;                ///<whether it's 3DNR enabled
        MAPI_BOOL bUseYUVSpace;           ///< color format before 3x3 matrix
        MAPI_BOOL bMemYUVFmt;             ///< memroy color format
        MAPI_BOOL bForceRGBin;            ///<Force set format in memory as RGB (only for RGB input source)
        MAPI_BOOL bLinearMode;            ///<Is current memory format LinearMode?

        // frame lock related
        // only main can select FB/FBL because panel output timing depends on main window, sub will always use FB
        MAPI_BOOL bFBL;                   ///<whether it's framebufferless case
        MAPI_BOOL bFastFrameLock;         ///<whether framelock is enabled or not
        MAPI_BOOL bDoneFPLL;              ///<whether the FPLL is done
        MAPI_BOOL bEnableFPLL;            ///<enable FPLL or not
        MAPI_BOOL bFPLL_LOCK;             ///<whether FPLL is locked (in specific threshold.)

        // Capture_Memory
        MAPI_U32 u32IPMBase0;             ///<IPM base 0
        MAPI_U32 u32IPMBase1;             ///<IPM base 1
        MAPI_U32 u32IPMBase2;             ///<IPM base 2
        MAPI_U16 u16IPMOffset;            ///<IPM offset
        MAPI_U32 u16IPMFetch;             ///<IPM fetch

        //----------------------
        // Pre customized scaling
        //----------------------
        MAPI_BOOL bPreHCusScaling;           ///<assign H customized scaling instead of using XC scaling
        MAPI_U16  u16PreHCusScalingSrc;      ///<H customized scaling src width
        MAPI_U16  u16PreHCusScalingDst;      ///<H customized scaling dst width
        MAPI_BOOL bPreVCusScaling;           ///<assign V manuel scaling instead of using XC scaling
        MAPI_U16  u16PreVCusScalingSrc;      ///<V customized scaling src height
        MAPI_U16  u16PreVCusScalingDst;      ///<V customized scaling dst height

        MAPI_BOOL bPQSetHSD;///<H_SizeAfterPreScaling is changed manually, which will skip PQ HSD sampling and filter

        MAPI_U16  u16DefaultPhase;           ///<Default Phase for VGA/YPbPr input
        MAPI_BOOL bIsHWDepthAdjSupported;    ///<Is hw depth adjustment for real 3d supported or not
        MAPI_BOOL bIs2LineMode;              ///<Is 2 line mode or not
        MAPI_BOOL bIsPNLYUVOutput;         ///<Is Scaler YUV output

        MAPI_U8  u8HDMIPixelRepetition;   ///<the HDMI pixel repetition info

        MAPI_U32 u32FRCMBase0;             ///<FRCM base 0
        MAPI_U32 u32FRCMBase1;             ///<FRCM base 1
        MAPI_U32 u32FRCMBase2;             ///<FRCM base 2
    }ST_MAPI_XC_API_STATUS;

    typedef enum
    {
        E_MAPI_VIDEO_FEATURE_INVALID = 0,
        E_MAPI_VIDEO_FEATURE_4K2K_PIP,
        E_MAPI_VIDEO_FEATURE_MAX,
    }EN_MAPI_VIDEO_SUPPORTED_FEATURES;


    typedef enum{
        E_MAPI_VIDEO_INIT_EDID,
        E_MAPI_VIDEO_INIT_HDMI,
    }EN_MAPI_VIDEO_INIT_TYPE;
};

///////////////////////////////
// HDR metadata structure
/// Document : JCTVC-P1005_v1_Annex_E_changes_for_Q0084_r1
typedef struct
{
    MAPI_U8 u8ColorPrimaries;
    MAPI_U8 u8TransferCharacteristics;
    MAPI_U8 u8MatrixCoefficients;
} ST_MAPI_HDR_METADATA_MPEG_VUI;

/// enum of test pattern mode
typedef enum
{
    E_MVOP_PATTERN_MODE,         // mvop tset Pattern
    E_ADC_PATTERN_MODE,          // adc tset Pattern
    E_IPMUX_PATTERN_MODE,        // ipmux tset Pattern
    E_IP1_PATTERN_MODE,           // ip tset Pattern
    E_OP_PATTERN_MODE,           // op tset Pattern
    E_VOP_PATTERN_MODE,          // vop tset Pattern
    E_VOP2_PATTERN_MODE,         // vop2 tset Pattern
    E_MOD_PATTERN_MODE,          // mod tset Pattern
}EN_TEST_PATTERN_MODE;

/// HDR error code.
typedef enum{
    /// Success.
    E_MAPI_HDR_ERROR_SUCCESS,
    /// Undefined fail.
    E_MAPI_HDR_ERROR_UNDEFINED_FAIL,
    /// Driver doesn't support.
    E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT,
    /// Driver still work.
    E_MAPI_HDR_ERROR_STILL_WORK,
    /// Input source doesn't support.
    E_MAPI_HDR_ERROR_INPUT_SOUCE_NOT_SUPPORT,
    /// HDR conflict.
    E_MAPI_HDR_CONFLICT,
} EN_MAPI_HDR_ERROR_CODE;

/// HDR level attributes.
typedef struct
{
    /// Is auto detect HDR level.
    MAPI_BOOL bAuto;
    /// Manual HDR level setting. Reference to E_MAPI_XC_HDR_LEVEL in mapi_syscfg_table.h
    MAPI_U8 u8Level;
} ST_MAPI_HDR_LEVEL_ATTRIBUTES;

/// Dolby HDR mode.
typedef struct
{
    /// Dolby mode.
    MAPI_U8 u8Mode;
    /// Get or set attribute error code. (Read only)
    EN_MAPI_HDR_ERROR_CODE eResult;
} ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES;

/// HDR setting attributes.
typedef struct
{
    /// Is Open / Dolby HDR video. If metadata is VUI/SEI/Dolby, this value set MAPI_TRUE, otherwise this value set MAPI_FALSE. (Read only)
    MAPI_BOOL bHdrVideo;
    /// Open / Dolby HDR on or off. This value means user set HDR on / off. (Read / Write)
    MAPI_BOOL bHdrOn;
    /// Is HDR HW working. (Read only)
    MAPI_BOOL bHdrHwWorking;
    union
    {
        /// Open HDR level. (Read / Write)
        ST_MAPI_HDR_LEVEL_ATTRIBUTES stHdrLevel;
        /// Dolby HDR mode. (Read / Write)
        ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES stMode;
    };
    /// Get or set attribute error code. (Read only)
    EN_MAPI_HDR_ERROR_CODE eResult;
} ST_MAPI_HDR_SETTING_ATTRIBUTES;

/// enum for HDR attributes.
typedef enum{
    /// Open HDR on / off attributes. Attribute data type is MAPI_BOOL. (Get / Set)
    EN_MAPI_HDR_ONOFF_ATTRIBUTES,
    /// Open HDR init auto detect attributes. Attribute data type is ST_MAPI_HDR_LEVEL_ATTRIBUTES. (Set only)
    EN_MAPI_HDR_INIT_AUTO_DETECT_ATTRIBUTES,
    /// Open HDR level attributes. Attribute data type is ST_MAPI_HDR_LEVEL_ATTRIBUTES. (Get / Set)
    EN_MAPI_HDR_LEVEL_ATTRIBUTES,
    /// HDR video metadata type attributes. Attribute data type is MAPI_U16. (Get only)
    EN_MAPI_HDR_TYPE_ATTRIBUTES,
    /// Dolby HDR mode attributes. Attribute data type is ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES. (Get / Set)
    EN_MAPI_HDR_DOLBY_MODE_ATTRIBUTES,
    /// Open HDR setting attributes. Attribute data type is ST_MAPI_HDR_SETTING_ATTRIBUTES. (Get / Set)
    EN_MAPI_HDR_OPEN_SETTING_ATTRIBUTES,
    /// Dolby HDR setting attributes. Attribute data type is ST_MAPI_HDR_SETTING_ATTRIBUTES. (Get / Set)
    EN_MAPI_HDR_DOLBY_SETTING_ATTRIBUTES,
    /// HDR internal attribute that is used in Supernova.
    EN_MAPI_HDR_INTERNAL_ATTRIBUTES = 500,
    /// HDR video timing attributes. Attribute data type is EN_MAPI_TIMING. (Set only)
    EN_MAPI_HDR_VIDEO_TIMING_ATTRIBUTES = EN_MAPI_HDR_INTERNAL_ATTRIBUTES,
} EN_MAPI_HDR_ATTRIBUTES;


/// Document : w14700 SEI - D.2.15 : Tone mapping information SEI message syntax
typedef struct
{
    MAPI_U8      u8ToneMapId;
    MAPI_BOOL   bToneMapCancelFlag;
    MAPI_BOOL   bToneMapPersistenceFlag;
    MAPI_U8      u8CodedDataBitDepth;
    MAPI_U8      u8TargetBitDepth;
    MAPI_U8      u8ToneMapModelId;
    MAPI_U32    u32MinValue;
    MAPI_U32    u32MaxValue;
    MAPI_U32    u32SigmoidMidpoint;
    MAPI_U32    u32SigmoidWidth;
    MAPI_U16*   pu16StartOfCodedInterval; /// array size = (1 << target_bit_depth)
    MAPI_U16     u16NumPivots;
    MAPI_U16*   pu16CodedPivotValue;  /// array size = num_pivots
    MAPI_U16*   pu16TargetPivotValue; /// array size = num_pivots
    MAPI_U8       u8CameraIsoSpeedIdc;
    MAPI_U32     u32CameraIsoSpeedValue;
    MAPI_U8       u8ExposureIndexIdc;
    MAPI_U32     u32ExposureIndexValue;
    MAPI_BOOL   bExposureCompensationValueSignFlag;
    MAPI_U16     u16ExposureCompensationValueNumerator;
    MAPI_U16     u16ExposureCompensationValueDenomIdc;
    MAPI_U32     u32RefScreenLuminanceWhite;
    MAPI_U32     u32ExtendedRangeWhiteLevel;
    MAPI_U16     u16NominalBlackLevelCodeValue;
    MAPI_U16     u16NominalWhiteLevelCodeValue;
    MAPI_U16     u16ExtendedWhiteLevelCodeValue;
} ST_MAPI_HDR_METADATA_MPEG_SEI_TONE_MAPPING;

/// Document : w14700 SEI - D.2.27 : Mastering display colour volume SEI message syntax
typedef struct
{
    MAPI_U16     u16DisplayPrimariesX[3];
    MAPI_U16     u16DisplayPrimariesY[3];
    MAPI_U16     u16WhitePointX;
    MAPI_U16     u16WhitePointY;
    MAPI_U32     u32MaxDisplayMasteringLuminance;
    MAPI_U32     u32MinDisplayMasteringLuminance;
} ST_MAPI_HDR_METADATA_MPEG_SEI_MASTERING_COLOR_VOLUME;

/// Document : w14700 SEI - D.2.31 : Knee function information SEI message syntax
typedef struct
{
    MAPI_U8      u8KneeFunctionId;
    MAPI_BOOL   bKneeFunctionCancelFlag;
    MAPI_BOOL   bKneeFunctionPersistenceFlag;
    MAPI_U32     u32InputDRange;
    MAPI_U32     u32InputDispLuminance;
    MAPI_U32     u32OutputDRange;
    MAPI_U32     u32OutputDispLuminance;
    MAPI_U16     u16NumKneePointsMinus1; /// num_knee_points_minus1 shall be in the range of 0 to 998, inclusive.
    MAPI_U16*    pu16InputKneePoint; /// array size = num_knee_points_minus1+1
    MAPI_U16*    pu16OutputKneePoint; /// array size = num_knee_points_minus1+1
} ST_MAPI_HDR_METADATA_MPEG_SEI_KNEE_FUNCTION;

/// Document : CEA-861.3_V16BallotDraft
typedef struct
{
    MAPI_U8      u8EOTF; /// 0:SDR gamma, 1:HDR gamma, 2:SMPTE ST2084, 3:Future EOTF, 4-7:Reserved
    MAPI_U16     u16Rx; /// display primaries Rx
    MAPI_U16     u16Ry; /// display primaries Ry
    MAPI_U16     u16Gx; /// display primaries Gx
    MAPI_U16     u16Gy; /// display primaries Gy
    MAPI_U16     u16Bx; /// display primaries Bx
    MAPI_U16     u16By; /// display primaries By
    MAPI_U16     u16Wx; /// display primaries Wx
    MAPI_U16     u16Wy; /// display primaries Wy
    MAPI_U16     u16Lmax; /// max display mastering luminance
    MAPI_U16     u16Lmin; /// min display mastering luminance
    MAPI_U16     u16MaxCLL; /// maximum content light level
    MAPI_U16     u16MaxFALL; /// maximum frame-average light level
} ST_MAPI_HDR_METADATA_HDMI_INFOFRAME;

/// HDR Metadata.
typedef struct
{
    /// HDR Metadata type
    MAPI_U16 u16HDRMetadataType;
    /// HDR Metadata Mpeg VUI
    ST_MAPI_HDR_METADATA_MPEG_VUI stHdrMetadataMpegVUI;
    ST_MAPI_HDR_METADATA_MPEG_SEI_TONE_MAPPING stHdrMetadataMpegSEIToneMapping;
    ST_MAPI_HDR_METADATA_MPEG_SEI_MASTERING_COLOR_VOLUME stHdrMetadataMpegSEIMasteringColorVolume;
    ST_MAPI_HDR_METADATA_MPEG_SEI_KNEE_FUNCTION stHdrMetadataMpegSEIKneeFunction;
    ST_MAPI_HDR_METADATA_HDMI_INFOFRAME stHdrMetadataHdmiInfoframe;
} ST_MAPI_HDR_METADATA;


#endif
