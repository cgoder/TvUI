#ifndef __CPLAYERSERVICE_H__
#define __CPLAYERSERVICE_H__

#include "CChannelinner.h"

class CPlayerService
{
public:
	// CPlayerService();
	// ~CPlayerService();
	static CPlayerService* getInstance(void);
	bool destoryInstance(void);

	bool play(unsigned int chNo);
	bool stop(unsigned int chNo);
	bool pause(unsigned int chNo);
	bool resume(unsigned int chNo);

	bool play(Channel& ch);
	bool stop(Channel& ch);
	bool pause(Channel& ch);
	bool resume(Channel& ch);

	bool setFreeze(bool freeze);
	bool playFirst(void);
};


#endif // __CPLAYERSERVICE_H__
