#ifndef  _SKY_SCANTYPE_H_
#define  _SKY_SCANTYPE_H_
#include <string>
#include "vector"
using  std::string;
//#define SCAN_TEST
using namespace std;
#define SKYSCAN_SUCCESS       (0)
#define SKYSCAN_FAILURE       (-1)
#define SKYSCAN_INTERVAL       10  //扫描间隔时间
#define SKY_SI_MAX_REGION_NAME  32

typedef enum //信号源   //for test
{
	SOURCE_TYPE_ATV_S = 0,
	SOURCE_TYPE_DVBC_S,
	SOURCE_TYPE_DVBT_S,
	SOURCE_TYPE_DVBS_S,
	SOURCE_TYPE_DTMB_S,
}skyScanSourceType;


typedef enum
{
	S_MODULATION_MODE_QAM16,
	S_MODULATION_MODE_QAM32,
	S_MODULATION_MODE_QAM64,
	S_MODULATION_MODE_QAM128,
	S_MODULATION_MODE_QAM256,
	S_MODULATION_MODE_QAM_AUTO,
}S_QAM_ModulationMode;

typedef enum //自动搜索方式
{
	AUTOSCAN,
	QUICKSCAN,
	FULLSACN,
	MANUALSCAN,
}skyScanModel;


typedef enum //搜索方式
{
	DIGITAL_ONLY,
	ATV_ONLY,
	DIGITAL_ATV

}skyScanTvType;


/*频点数据*/
typedef struct {
	unsigned int freq;
	unsigned int symbolRate;
	//just for c
	S_QAM_ModulationMode modulation;  
	unsigned int networkid;
	// just for t 
	unsigned int front_id; 

}skyFreqData;
/*signal 状态*/
typedef struct
{
	unsigned int 	strength;
	unsigned int 	quality;
	unsigned int		ber[3]; /*误码率*/
}skySignalStatus;

typedef enum //搜索状态返回
{

	STATUS_SKYSCAN_FAILED,
	STATUS_SKYSCAN_TIMEOUT,
	STATUS_SKYSCAN_TUNING_PROGRESS,
	STATUS_SKYSCAN_TUNING_END,
	STATUS_SKYSCAN_UNKNOW
}skyScanStatus;

/*搜索过程中ui需要显示的数据*/
typedef struct
{
	unsigned int 	radio_count;
	unsigned int 	data_count;
	unsigned int 	digitaltv_count;
	unsigned int 	analogtv_count;
	unsigned int	current_channelnum;
	unsigned int	current_freq;
	unsigned int	process;
	unsigned int	signal_quality;
	unsigned int	signal_strength;
	skyScanStatus	scanstatus;
}skyScanCallbackData;

typedef enum
{
  /// BG
  ATV_MODE_BG = 0,
  /// I
  ATV_MODE_I ,
  /// DK
  ATV_MODE_DK ,
  /// L
  ATV_MODE_L ,
  /// M
  ATV_MODE_M ,
  /// the total counts of this enum
  ATV_MODE_COUNT ,
} skyAudioSystemType;
typedef enum
{
	ATV_COLOR_PAL,
	ATV_COLOR_NTSC,
	ATV_COLOR_SECAM,
	ATV_COLOR_AUTO,
}skyColorSystemType;
typedef enum
{
	DTV_BINDWITH_5M = 5,
	DTV_BINDWITH_6M,
	DTV_BINDWITH_7M,
	DTV_BINDWITH_8M
}skyFreBindWith;

typedef enum 
{
    E_SKY_CABLEOP_OTHER,
    E_SKY_CABLEOP_CDSMATV,
    E_SKY_CABLEOP_CDCABLE,
    E_SKY_CABLEOP_COMHEM,
    E_SKY_CABLEOP_UPC,
    E_SKY_CABLEOP_YOUSEE,
    E_SKY_CABLEOP_CABLEREADY,
    E_SKY_CABLEOP_ZIGGO,
    E_SKY_CABLEOP_STOFA,
    E_SKY_CABLEOP_UNITYMEDIA,
    E_SKY_CABLEOP_COUNT
}skyCableOp;
/// define the ATV manual tuning mode
typedef enum
{
	/// search one channel, direction = up
	ATV_MANUAL_TUNE_MODE_SEARCH_ONE_TO_UP,
	/// search one channel, direction = down
	ATV_MANUAL_TUNE_MODE_SEARCH_ONE_TO_DOWN,
	/// fine tune to a given frequency
	ATV_MANUAL_TUNE_MODE_FINE_TUNE_ONE_FREQUENCY,
	/// fine tune, direction = up
	ATV_MANUAL_TUNE_MODE_FINE_TUNE_UP,
	/// fine tune, direction = down
	ATV_MANUAL_TUNE_MODE_FINE_TUNE_DOWN,
	/// undefine
	ATV_MANUAL_TUNE_MODE_UNDEFINE,
} skyAtvManualTuneMode;

/*channel 状态*/
typedef enum
{
	TV_FREE_ONLY,
	/// Free and scramble
	TV_FREE_SCRAMBLE,
	/// scramble only
	TV_SCRAMBLE,
}skyScanScope;
/*channel type*/
typedef enum
{
	/// TV only
	TV_ONLY,
	/// TV and radio
	TV_RADIO,
	/// Radio only
	RADIO_ONLY,
	// TV, radio and data
	TV_RADIO_DATA,
} skyScanServicetype;


typedef struct
{
    /// the Satellite name
	string  dvbs_sSatName;
	/// Band Type : 0 is C band / 1 is Ku band
	int dvbs_eLNBType;

    /// the low LOF value (unit: MHz)
    int dvbs_u16LoLOF;
    /// the high LOF value (unit: MHz)
    int dvbs_u16HiLOF;
	/// the Angle value
	//if(m_u16LongitudeAngle > 1800)
	//{
	//	m_u16LongitudeAngle = 3600 - m_u16LongitudeAngle;
	//	u32Direction = OPTION_WEST;
	//}
	int dvbs_u16Angle;
	/// the Direction value
	int dvbs_Direction;


    /// LNB Type : Universal / 9750 / 5150 ... (Ref: MS_EN_LNB_FREQ_TYPE enum)
    int  dvbs_eLNBTypeReal;
    /// DiSEqC Type : Off/1.0/1.1/1.2/1.3 (Ref: MS_EN_DISEQC_LEVEL enum)
    int  dvbs_eDiseqcLevel;
    /// the ToneBurstType : none/0/1 (Ref: MS_EN_TONEBURST_TYPE enum)
    int  dvbs_eToneburstType;
    /// the type of DiSEqC 1.0 : type1/2/3/4 (Ref: DISEQC_1_0_LNB_TYPE enum)
    int  dvbs_eSwt10Port;
    /// the type of DiSEqC 1.1 : type1/2/3/4..16 (Ref: DISEQC_1_1_LNB_TYPE enum)
    int  dvbs_eSwt11Port;
    /// the 22K type: Auto/On/Off (Ref: MS_EN_22K_ONOFF enum)
    int  dvbs_e22KOnOff;
    /// the 13/18V type : Off/auto/13V/18V (Ref: MS_EN_LNBPWR_ONOFF)
    int  dvbs_eLNBPwrOnOff;
    /// No Used.
    int  dvbs_e0V12VOnOff;
    /// Motor position bit8 1:USALS 0:DISEQC1.2
    int  dvbs_u8Position;

    /// the number of TP in this Satellite
    int dvbs_u16NumberOfTP;
    /// the Satellite ID
    int  dvbs_u8SatID;
    /// unicable channel Id
    int dvbs_u8ChannelId;
    /// unicable frequency
    int dvbs_u16IFreq;
    /// unicable MDU
    bool dvbs_bMDU;
    /// unicable password pin
    int dvbs_u8PasswordPIN;
    /// the single cable LNB index, 0: LNB A, 1: LNB B
    int  dvbs_u8SingleCableLNBIdx;
} skySatellite_Info;

typedef struct
{
    /// the tp frequence
    int  u32Frequency;
    /// the tp symbol rate
    int  u16SymbolRate;
    /// the polarity : 0 is vertical, 1 is horizontal
	int   bPolarity;
    /// the Satellite ID
	int   u8SatID;
    /// the TP index in Satellite.
	int   u8RF;
    /// the TP ID
	int  u16TpID;
} skyTransponder_Info;

/* DISEQC LNB TYPE */
/*
typedef enum
{
    DISEQC_1_0_LNB_TYPE_NONE,
    DISEQC_1_0_LNB_TYPE_1,
    DISEQC_1_0_LNB_TYPE_2,
    DISEQC_1_0_LNB_TYPE_3,
    DISEQC_1_0_LNB_TYPE_4,
    DISEQC_1_0_LNB_TYPE_COUNT
} dtv_Dvbs_DISEQC_1_0_LNB_TYPE;

// DISEQC 1.1 LNB TYPE /
typedef enum
{
    DISEQC_1_1_LNB_TYPE_NONE,
    DISEQC_1_1_LNB_TYPE_1,
    DISEQC_1_1_LNB_TYPE_2,
    DISEQC_1_1_LNB_TYPE_3,
    DISEQC_1_1_LNB_TYPE_4,
    DISEQC_1_1_LNB_TYPE_5,
    DISEQC_1_1_LNB_TYPE_6,
    DISEQC_1_1_LNB_TYPE_7,
    DISEQC_1_1_LNB_TYPE_8,
    DISEQC_1_1_LNB_TYPE_9,
    DISEQC_1_1_LNB_TYPE_10,
    DISEQC_1_1_LNB_TYPE_11,
    DISEQC_1_1_LNB_TYPE_12,
    DISEQC_1_1_LNB_TYPE_13,
    DISEQC_1_1_LNB_TYPE_14,
    DISEQC_1_1_LNB_TYPE_15,
    DISEQC_1_1_LNB_TYPE_16,
    DISEQC_1_1_LNB_TYPE_COUNT
} Dtv_DVBS_DISEQC_1_1_LNB_TYPE;

typedef enum
{
    DISEQC_MOTOR_CMD_HALTMOTOR,
    DISEQC_MOTOR_CMD_CONTINUE_WEST,
    DISEQC_MOTOR_CMD_CONTINUE_EAST,
    DISEQC_MOTOR_CMD_STEP_WEST,
    DISEQC_MOTOR_CMD_STEP_EAST,
    DISEQC_MOTOR_CMD_GOTO_REF_POINT,
    DISEQC_MOTOR_CMD_SAVE_SAT_POSITION,
    DISEQC_MOTOR_CMD_GOTO_SAT_POSITION,
    DISEQC_MOTOR_CMD_GOTO_X,
    DISEQC_MOTOR_CMD_SET_WEST_LIMIT,
    DISEQC_MOTOR_CMD_SET_EAST_LIMIT,
    DISEQC_MOTOR_CMD_DISABLE_LIMIT,
} Dtv_DVBS_DISEQC_MOTOR_CMD;*/



typedef enum
{
	/// off
	DVBS_LNBPWR_OFF,
	/// 13 or 18
	DVBS_LNBPWR_13OR18V,
	/// 13v
	DVBS_LNBPWR_13V,
	/// 18v
	DVBS_LNBPWR_18V,
	
	DVBS_LNBPWR_ONOFF_NUM
}Dtv_Dvbs_Lnbpwr_OnOff;

/* 22KHZ_TONE */
typedef enum
{
	TONE_22KHZ_AUTO,
	TONE_22KHZ_ON,
	TONE_22KHZ_OFF,
	TONE_22KHZ_COUNT
} Dtv_Dvbs_Tone_22KHZ;
/*搜索过程中具体数据回调*/





typedef struct
{
	int satnum;
	vector<int> tplist;
}skySatelliteSelected;

typedef struct {
	skyFreqData freqdata;
	skyScanModel autoscanmodel; 
	skyScanTvType scantvtype;
	skyFreBindWith frebindwith;
	skyScanServicetype servicetype;
	skyScanScope scanscope;
	skyAtvManualTuneMode atvtunemode;   /*just for atv*/
	skyAudioSystemType audiosystem;		/*just for atv*/
	skyColorSystemType colorsystemtype;/*just for atv*/
	int turnfine;/*just for atv*/
	int channelindex; /* just for atv,we should get this number from channelmanager*/
	skyCableOp cableop;
	int country;
	bool networksearch;
	vector<skySatelliteSelected > selectsats;/*just for dvbs*/
}skyScanParam;
typedef void(*skyScanDataCallBack)(skyScanCallbackData  callbackdata, void* ptr);
#endif