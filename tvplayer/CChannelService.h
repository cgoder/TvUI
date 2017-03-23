#ifndef __CCHANNESERVICE_H__
#define __CCHANNESERVICE_H__

// using namespace std;
#include <vector>
#include "CChannelinner.h"

class CChannelService
{
public:
	static CChannelService* getInstance(void);
	bool destoryInstance(void);

	unsigned int getAllChannelCount(void);
	unsigned int getChannelCount(ServiceType chType);
	unsigned int getChannelCount(SourceType source);
	bool getAllChannel(std::vector<Channel>& channels);
	bool getAllChannel(ServiceType chType, std::vector<Channel>& channels);
	bool getAllChannel(SourceType source, std::vector<Channel>& channels);
	bool getChannelByIndex(unsigned int index, Channel& channel);
	bool getCurrentChannel(Channel& channel);

};


#endif // __CCHANNESERVICE_H__
