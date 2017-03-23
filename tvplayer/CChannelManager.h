#ifndef __CCHANNEL_MANAGER_H__
#define __CCHANNEL_MANAGER_H__
// #include <map>
#include <vector>
#include "CChannelinner.h"
#include "CChannelService.h"
#include "tv_types.h"

#define DEFAULT_CH_NUM_MAX (65535)


class CChannelManager
{
public:
	//CChannelManager();
	CChannelManager(SKYTV_INPUT_SOURCE_TYPE inputSource);
	~CChannelManager();

	inline unsigned int getChannelCount(void) {
		return channels.size();
	}
	inline unsigned int getChannelMax(void) {
		return DEFAULT_CH_NUM_MAX;
	}
	inline unsigned int getLastChannel(void) {
		return u32LastChIndex;
	}

	Channel& getChannelInfo(unsigned int chIndex);
	CChannelInner* getChannel(unsigned int chIndex);
	bool getAllChannel(std::vector<CChannelInner*>& allCh);
	bool swap(unsigned int firstChannelIndex, unsigned int secondChannelIndex);
	bool sort(enum SortType sortType);
	bool deletChannel(unsigned int chIndex);
	void showChannelList(void);
	bool findChannel(Channel ch, unsigned int& chIndex);

protected:
	bool addChannel(CChannelInner* ch);
	bool deletChannel(CChannelInner* ch);
	bool init(SKYTV_INPUT_SOURCE_TYPE input);

private:
	std::vector<CChannelInner*> channels;
	SKYTV_INPUT_SOURCE_TYPE curSource;
	unsigned int u32LastChIndex;
};
#endif //__CCHANNEL_MANAGER_H__
