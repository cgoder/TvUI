#ifndef __CCHANNELINNER_H__
#define __CCHANNELINNER_H__
#include "CChannel.h"

class CChannelInner : public CChannel
{
public:
	CChannelInner() {};
	~CChannelInner() {};

	inline void setName(std::string name) {
		channel.logic.chName = name;
	}
	inline void setNo(std::string chNo) {
		channel.logic.chNo = chNo;
	}
	inline void setFav(bool bFav) {
		channel.logic.isFavorite = bFav;
	}
	inline void setLock(bool bLock) {
		channel.logic.isLock = bLock;
	}
	inline void setHide(bool bHide) {
		channel.logic.isHide = bHide;
	}
	inline void setDelete(bool bDelete) {
		channel.logic.isDelete = bDelete;
	}
	bool set(Channel& ch) {
		channel = ch;
		return true;
	}
};


#endif // __CCHANNELINNER_H__
