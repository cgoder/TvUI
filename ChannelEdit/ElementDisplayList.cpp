#include "ElementDisplayList.h"
#include "common/common.h"
#include "tvplayer/TvPlayer.h"
USING_NS_CC;
//#define UPPER_UI_SORT

ElementDisplayListSystem::ElementDisplayListSystem()
{
	
}

ElementDisplayListSystem::~ElementDisplayListSystem()
{
#ifdef UPPER_UI_SORT
	allChannels.clear();
	favouriteChannels.clear();
#else
#endif	
}


bool ElementDisplayListSystem::init()
{
	log("ElementDisplayListSystem,getChannelCount() in");
	int numberofchannels = Get_TvPlayer()->getChannelCount();
	log("ElementDisplayListSystem,getChannelCount() out");
#ifdef UPPER_UI_SORT	
	tableindex_all = 0;
	tableindex_fav = 0;
	for (int i = 0; i < numberofchannels; i++)
	{
		CChannel* tmpCh = Get_TvPlayer()->getChannel(i);
		if(!tmpCh->isDelete())
		{
			allChannels.insert(std::make_pair(tableindex_all, i));
			tableindex_all++;
		}
		if(tmpCh->isFav())
		{
			favouriteChannels.insert(std::make_pair(tableindex_fav, i));
			tableindex_fav++;
		}		
	}
#else	
	tableindex_all = numberofchannels;
		
#endif	
	return true;
}
int ElementDisplayListSystem::validChannelCount()
{
	return tableindex_all;

}

CChannel* ElementDisplayListSystem::getChannel(unsigned int chIndex)
{
#ifdef UPPER_UI_SORT
	SortedDisplayList::iterator it = allChannels.find(chIndex);	
	if(it != allChannels.end())
	{
		CChannel* tmpCh = Get_TvPlayer()->getChannel(it->second);
		return tmpCh;
	}
	else
		return NULL;
#else
log("ElementDisplayListSystem,getChannel in");
	CChannel* tmpCh = Get_TvPlayer()->getChannel(chIndex);
log("ElementDisplayListSystem,getChannel out");	
	return tmpCh;
#endif
		
}

bool ElementDisplayListSystem::play(unsigned int chIndex)
{	
#ifdef UPPER_UI_SORT
	SortedDisplayList::iterator it = allChannels.find(chIndex);	
	if(it != allChannels.end())
	{
		return Get_TvPlayer()->play(it->second);		
	}
	else
		return false;
#else
log("ElementDisplayListSystem,play in");
	return Get_TvPlayer()->play(chIndex);
log("ElementDisplayListSystem,play out");
#endif		
}

void ElementDisplayListSystem::insertElement(SortedDisplayList& list,int tableindex,int channelindex)
{
	
}
void ElementDisplayListSystem::eraseElement(SortedDisplayList& list,int tableindex,bool delete_flag)
{
#ifdef UPPER_UI_SORT	
	SortedDisplayList::iterator it = list.find(tableindex);	
	SortedDisplayList::iterator it_end = list.end();	
	CChannel* tmpCh = Get_TvPlayer()->getChannel(it->second);
		
	if(delete_flag)
	{
		it_end--;
		list.erase(it,it_end);
		
		
		if(!tmpCh->isDelete())
			tmpCh->setDelete(true); 
	}
#else
	if(delete_flag)
	{
log("ElementDisplayListSystem,setChannelStatus SKYTV_CHANNEL_OPT_DEL in");		
		Get_TvPlayer()->setChannelStatus(tableindex, SKYTV_CHANNEL_OPT_DEL, true);
log("ElementDisplayListSystem,setChannelStatus SKYTV_CHANNEL_OPT_DEL out");				
	}
	
#endif	
		
}
void ElementDisplayListSystem::exchangeElement(SortedDisplayList& list,int tableindex,bool is_up)
{
#ifdef UPPER_UI_SORT	
	int idx1,idx2,tableidx;

	tableidx = tableindex;
	SortedDisplayList::iterator it = list.find(tableindex);	
	SortedDisplayList::iterator it_bk = it;	
	SortedDisplayList::iterator it_end = list.end();
	it_end--;
	if(it != list.begin() && it != it_end&& it != list.end())
	{
		idx1 = it->second;		
		if(is_up)
		{		
			it_bk--;
			tableidx--;
		}
		else
		{
			it_bk++;
			tableidx++;
		}
		idx2 = it_bk->second;
		list.erase(it);
		list.erase(it_bk);		
		
		
		list.insert(std::make_pair(tableindex, idx2));
		list.insert(std::make_pair(tableidx, idx1));
	}
#else
	
log("ElementDisplayListSystem,swapChannel in");			
	if(is_up)
	{
		Get_TvPlayer()->swapChannel(tableindex,tableindex-1);
	}
	else
	{
		Get_TvPlayer()->swapChannel(tableindex,tableindex+1);
	}
log("ElementDisplayListSystem,swapChannel out");			
	
#endif	
	
}

void ElementDisplayListSystem::updateElement()
{
	
	int numberofchannels = Get_TvPlayer()->getChannelCount();
#ifdef UPPER_UI_SORT	
	tableindex_all = 0;
	tableindex_fav = 0;
	for (int i = 0; i < numberofchannels; i++)
	{
		CChannel* tmpCh = Get_TvPlayer()->getChannel(i);
		if(!tmpCh->isDelete())
		{
			allChannels.insert(std::make_pair(tableindex_all, i));
			tableindex_all++;
		}
		if(tmpCh->isFav())
		{
			favouriteChannels.insert(std::make_pair(tableindex_fav, i));
			tableindex_fav++;
		}		
	}
#else	
	tableindex_all = numberofchannels;
#endif		
}

bool ElementDisplayListSystem::getFavAttr(int tableindex)
{
#ifdef UPPER_UI_SORT	
	SortedDisplayList::iterator it = allChannels.find(tableindex);
	CChannel* tmpCh = Get_TvPlayer()->getChannel(it->second);
	
#else
log("ElementDisplayListSystem,getChannel in");				
	CChannel* tmpCh = Get_TvPlayer()->getChannel(tableindex);
	
#endif	
log("ElementDisplayListSystem,getChannel out");			
	bool is_fav = tmpCh->isFav();
log("ElementDisplayListSystem,tmpCh->isFav() out");			
return is_fav;
}
bool ElementDisplayListSystem::getLockAttr(int tableindex)
{
#ifdef UPPER_UI_SORT
	SortedDisplayList::iterator it = allChannels.find(tableindex);
	CChannel* tmpCh = Get_TvPlayer()->getChannel(it->second);	
#else
log("ElementDisplayListSystem,getChannel in");				
	CChannel* tmpCh = Get_TvPlayer()->getChannel(tableindex);
log("ElementDisplayListSystem,getChannel out");					
#endif	
	bool is_lock = tmpCh->isLock();
log("ElementDisplayListSystem,tmpCh->isLock() out");				
	return is_lock;
}
	
void ElementDisplayListSystem::updateFavAttr(int tableindex,bool enable)
{
#ifdef UPPER_UI_SORT		
	/* find by key */
	SortedDisplayList::iterator it = allChannels.find(tableindex);
	CChannel* tmpCh = Get_TvPlayer()->getChannel(it->second);	
#else
log("ElementDisplayListSystem,getChannel in");				
	CChannel* tmpCh = Get_TvPlayer()->getChannel(tableindex);
log("ElementDisplayListSystem,getChannel out");						
#endif
	if(tmpCh->isFav()!= enable)
	{
log("ElementDisplayListSystem,setChannelStatus SKYTV_CHANNEL_OPT_FAV in");					
		Get_TvPlayer()->setChannelStatus(tableindex, SKYTV_CHANNEL_OPT_FAV, enable);
log("ElementDisplayListSystem,setChannelStatus SKYTV_CHANNEL_OPT_FAV out");	
	}
}

void ElementDisplayListSystem::updateLockAttr(int tableindex,bool enable)
{
#ifdef UPPER_UI_SORT	
	SortedDisplayList::iterator it = allChannels.find(tableindex);
	CChannel* tmpCh = Get_TvPlayer()->getChannel(it->second);
#else
log("ElementDisplayListSystem,getChannel in");	
	CChannel* tmpCh = Get_TvPlayer()->getChannel(tableindex);
log("ElementDisplayListSystem,getChannel out");			
#endif	
	if(tmpCh->isLock()!= enable)
	{
		log("ElementDisplayListSystem,setChannelStatus SKYTV_CHANNEL_OPT_LOCK in");			
		Get_TvPlayer()->setChannelStatus(tableindex, SKYTV_CHANNEL_OPT_LOCK, enable);
		log("ElementDisplayListSystem,setChannelStatus SKYTV_CHANNEL_OPT_LOCK out");			
	}
}




ElementDisplayListUser::ElementDisplayListUser()
{
	
}

ElementDisplayListUser::~ElementDisplayListUser()
{
	
}

bool ElementDisplayListUser::init()
{
	return true;
}


void ElementDisplayListUser::insertElement(SortedDisplayList& list,int tableindex,int channelindex)
{
	//list.insert(std::make_pair(tableindex, channelindex));
}
void ElementDisplayListUser::eraseElement(SortedDisplayList& list,int tableindex)
{
	//list.erase(tableindex);
}

void ElementDisplayListUser::updateFinishedAttr(int tableindex,bool finished)
{
	
}