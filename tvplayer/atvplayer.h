#ifndef __ATVPLAYER_H__
#define __ATVPLAYER_H__

#include <vector>
#include "CChannel.h"
#include "TvPlayer.h"
#include "CChannelManager.h"
#include "CPlayerService.h" //skytvmw UAPI

class AtvPlayer : public TvPlayer
{
public:
	AtvPlayer();
	~AtvPlayer();

	bool playCur(void);
	bool playPrev(void);
	bool playNext(void);
	bool playBack(void);
	bool play(unsigned int chIndex);
	bool pause(bool freeze = true);
	bool stop(bool freeze = true);
	bool reset(void);

	unsigned int getChannelCount(void);
	CChannel* getCurChannel(void);
	CChannel* getChannel(unsigned int chIndex);

public:
	unsigned int getLastChannelIndex(void);
	bool swapChannel(unsigned int firstChannelIndex, unsigned int secondChannelIndex);
	bool setChannelStatus(unsigned int chIndex, SKYTV_CHANNEL_OPT_TYPE opt, bool status);

	bool getAllFav(std::vector<CChannel*>& favCh);

public:
	CChannelManager* getChannelManager(void);
	bool playChannel(CChannel& ch);
	bool stopChannel(CChannel& ch, bool freeze);
	bool playChannel(unsigned int chIndex);
	bool stopChannel(unsigned int chIndex, bool freeze);
	bool printfAllChannel(void);

private:
	CChannelManager* _chManager;
};

#endif // __ATVPLAYER_H__

