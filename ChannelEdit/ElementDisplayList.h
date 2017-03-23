#ifndef __ELEMENT_DISPLAY_LIST_H__
#define __ELEMENT_DISPLAY_LIST_H__

#include <map>

#include "cocos2d.h"
#include "tvplayer/TvPlayer.h"

typedef std::map<unsigned int, unsigned int> SortedDisplayList;

class ElementDisplayListSystem:public cocos2d::Scene//from CChannel list
{
public:
	ElementDisplayListSystem();
	~ElementDisplayListSystem();
	
	virtual bool init();
	
	int validChannelCount();
	CChannel* getChannel(unsigned int chIndex);
	bool play(unsigned int chIndex);
			
	void insertElement(SortedDisplayList& list,int tableindex,int channelindex);
	void eraseElement(SortedDisplayList& list,int tableindex,bool delete_flag);
	void exchangeElement(SortedDisplayList& list,int tableindex,bool is_up);
	void updateElement();
	
	bool getFavAttr(int tableindex);
	bool getLockAttr(int tableindex);
	void updateFavAttr(int tableindex,bool enable);
	void updateLockAttr(int tableindex,bool enable);				

	SortedDisplayList allChannels;
	SortedDisplayList favouriteChannels;
	
	int tableindex_all;
	int tableindex_fav;
};


class ElementDisplayListUser:public cocos2d::Scene//user defined list
{
public:
	ElementDisplayListUser();
	~ElementDisplayListUser();
	
	virtual bool init();
	
	void insertElement(SortedDisplayList& list,int tableindex,int channelindex);
	void eraseElement(SortedDisplayList& list,int tableindex);
	
	void updateFinishedAttr(int tableindex,bool finished);
		
	SortedDisplayList scheduleViewing;
	SortedDisplayList scheduleEncoding;
	SortedDisplayList encodedProgram;

};

#endif //__ELEMENT_DISPLAY_LIST_H__