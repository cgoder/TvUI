#ifndef __CCHANNEL_H__
#define __CCHANNEL_H__

#include <string>

enum SortType {
	CHANNEL_SORT_UNKNOWN = 0,
	CHANNEL_SORT_SVCID,
	CHANNEL_SORT_NAME,
	CHANNEL_SORT_NUM,
};

enum SourceType {
	SOURCE_TYPE_UNKNOWN = 0,
	SOURCE_TYPE_ATV,
	SOURCE_TYPE_DTV,
	SOURCE_TYPE_DVBC,
	SOURCE_TYPE_DVBT,
	SOURCE_TYPE_DVBS,
	SOURCE_TYPE_DTMB,
};

enum ModulationMode {
	MODULATION_MODE_UNKNOWN = 0,
	MODULATION_MODE_QPSK,
	MODULATION_MODE_BPSK,
	MODULATION_MODE_OQPSK,
	MODULATION_MODE_VSB8,
	MODULATION_MODE_VSB16,
	MODULATION_MODE_QAM16,
	MODULATION_MODE_QAM32,
	MODULATION_MODE_QAM64,
	MODULATION_MODE_QAM80,
	MODULATION_MODE_QAM96,
	MODULATION_MODE_QAM112,
	MODULATION_MODE_QAM128,
	MODULATION_MODE_QAM160,
	MODULATION_MODE_QAM192,
	MODULATION_MODE_QAM224,
	MODULATION_MODE_QAM256,
	MODULATION_MODE_QAM320,
	MODULATION_MODE_QAM384,
	MODULATION_MODE_QAM448,
	MODULATION_MODE_QAM512,
	MODULATION_MODE_QAM640,
	MODULATION_MODE_QAM768,
	MODULATION_MODE_QAM896,
	MODULATION_MODE_QAM1024,
	MODULATION_MODE_QAM_NTSC // for analog mode
};

typedef struct TransportStream {
	unsigned int frequency;
	unsigned int symbolRate;
	ModulationMode modulation;
	unsigned short networkId;
	unsigned short tsId;
} TransportStreamStruct;

typedef struct EitEvent {
	unsigned short networkId;
	unsigned short tsId;
	unsigned short serviceId;
	unsigned short eventId;
	unsigned long startTime;
	unsigned int duration;
	std::string eventName;
	std::string eventText;
} EitEventStruct;

enum ServiceType {
	SERVICE_TYPE_UNKNOWN = 0,
	SERVICE_TYPE_ATV,
	SERVICE_TYPE_DTV,
	SERVICE_TYPE_DTV_TV,
	SERVICE_TYPE_DTV_RADIO,
	SERVICE_TYPE_DTV_DATA,
};

enum VideoType {
	VIDEO_TYPE_UNKNOWN = 0,
	VIDEO_TYPE_MPEG,
	VIDEO_TYPE_MPEG2,
	VIDEO_TYPE_MPEG4,
	VIDEO_TYPE_H264,
	VIDEO_TYPE_H265,
	VIDEO_TYPE_AVS,
	VIDEO_TYPE_AVSPLUS,
};

enum AudioType {
	AUDIO_TYPE_UNKNOWN = 0,
	AUDIO_TYPE_AC3,
	AUDIO_TYPE_AAC,
	AUDIO_TYPE_MP3,
	AUDIO_TYPE_WAV,
};

enum LaunageType {
	LAUNAGE_TYPE_UNKNOWN = 0,
	LAUNAGE_TYPE_ENG,
	LAUNAGE_TYPE_CHS,
	LAUNAGE_TYPE_CHT,
	LAUNAGE_TYPE_JP,
};

enum AtvSoundSystem {
	SOUND_SYSTEM_UNKNOWN = 0,
	SOUND_SYSTEM_AUTO,
	SOUND_SYSTEM_BG,
	SOUND_SYSTEM_I,
	SOUND_SYSTEM_DK,
	SOUND_SYSTEM_L,
	SOUND_SYSTEM_LL,
	SOUND_SYSTEM_M,
};

enum AtvVideoSystem {
	VIDEO_SYSTEM_UNKNOWN = 0,
	VIDEO_SYSTEM_PAL,
	VIDEO_SYSTEM_NTSC,
};

typedef struct Audio {
	enum LaunageType audioLaunage;
	enum AudioType audioType;
	unsigned short audioPid;
} AudioStruct;

typedef struct Service {
	bool isEncrypted;
	unsigned short ecmPid;
	unsigned short videoPid;
	enum VideoType videoType;//mpeg/mpeg2/mpeg4/h264
	unsigned short pcrPid;
	unsigned short audioCount;
	Audio* audioList;
} ServiceStruct;

typedef struct ChannelPhysics {
	unsigned int number; //底层数据库存储时的频道号
	enum SourceType source;//c/s/t/atv
	enum ServiceType serviceType;

	unsigned short serviceId;
	unsigned short networkId;
	unsigned short tsId;
	unsigned short pmtPid;
	std::string serviceName;
	Service services;
	//unsigned short eitVersion;
	EitEvent* eventPf;//EIT actual(0x4E), present/following.
	EitEvent* eventAll;//EIT actual(0x50~0x5F), schedule.
} ChannelPhysicsStruct;

// typedef struct ChannelPhysicsDTV {
// 	unsigned int number; //底层数据库存储时的频道号
// 	enum SourceType source;//c/s/t
// 	enum ServiceType serviceType;
// 	unsigned short serviceId;
// 	unsigned short networkId;
// 	unsigned short tsId;
// 	unsigned short pmtPid;
// 	std::string serviceName;
// 	Service services;
// 	//unsigned short eitVersion;
// 	EitEvent* eventPf;//EIT actual(0x4E), present/following.
// 	EitEvent* eventAll;//EIT actual(0x50~0x5F), schedule.
// } ChannelPhysicsDTVStruct;

// typedef struct ChannelPhysicsATV {
// 	unsigned int number;//底层数据库存储时的频道号
// 	enum SourceType source;//c/s/t/atv
// 	AtvVideoSystem vidio;
// 	AtvSoundSystem sound;
// 	unsigned int freq; //KHZ
// } ChannelPhysicsATVStruct;

typedef struct ChannelLogic {
	bool isFavorite;
	bool isLock;
	bool isHide;
	bool isDelete;
	std::string chNo;
	std::string chName;
} ChannelLogicStruct;

//channel struct
typedef struct Channel {
	ChannelLogic logic;
	ChannelPhysics physics;
} ChannelStruct;


class IChannel
{
public:
	IChannel() {};
	virtual ~IChannel() {};

	virtual std::string getName() = 0;
	virtual std::string getNo() = 0;
	virtual bool isFav() = 0;
	virtual bool isLock() = 0;
	virtual bool isHide() = 0;
	virtual bool isDelete() = 0;
};

//channel class
class CChannel : public IChannel
{
public:
	CChannel();
	virtual ~CChannel();

	inline std::string getName() {
		return channel.logic.chName;
	}
	inline std::string getNo() {
		return channel.logic.chNo;
	}
	inline bool isFav() {
		return channel.logic.isFavorite;
	}
	inline bool isLock() {
		return channel.logic.isLock;
	}
	inline bool isHide() {
		return channel.logic.isHide;
	}
	inline bool isDelete() {
		return channel.logic.isDelete;
	}
	inline bool isAtv() {
		if (SOURCE_TYPE_ATV == channel.physics.source) {
			return true;
		} return false;
	}
	inline SourceType getSource() {
		return channel.physics.source;
	}
	inline Channel& get(void) {
		return channel;
	}

protected:
	Channel channel;
};


#endif // __CCHANNEL_H__
