#ifndef __CHANNELLIST_SCENE_H__
#define __CHANNELLIST_SCENE_H__

#include "cocos2d.h"
#include "ChannelListPage.h"
#include "ChannelListPageFavorite.h"
#include "ChannelListPageRecorded.h"
#include "ChannelListPageSchRecording.h"
#include "ChannelListPageSchViewing.h"


#include "common/SkyLayer.h"



#define CHLIST_PAGECOUNT 5
#define FOCUS_IMG_POS 703
#define CHLIST_ITEM_NUM 6


enum
{
	CHLIST_PAGEVIEW_RECORDED,
	CHLIST_PAGEVIEW_SCH_RECORDING,
	CHLIST_PAGEVIEW_ALL,
	CHLIST_PAGEVIEW_SCH_VIEWING,
	CHLIST_PAGEVIEW_FAVOURITE
	
};


enum
{
	CHLIST_PAGEVIEW_TAG = 0x200,
	CHLIST_FOCUS_IMG_TAG = 0x201
	
};

enum
{
	CHLIST_RECORDED_PLAY,
	CHLIST_RECORDED_DEL,
	CHLIST_SCH_REC_CANCEL,
	CHLIST_SCH_VIEWING_CANCEL,
	CHLIST_ENTER_PIN
};


class ChannelList : public SkyLayer
{
public:
	ChannelList();
	~ChannelList();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
   	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	virtual bool skyShow(cocos2d::Node* node);
	virtual void skyHide(cocos2d::Node* node);
	virtual void skyRefresh();
    // implement the "static create()" method manually
    CREATE_FUNC(ChannelList);
    
protected:  
	void initChannelList();  
    void onKeyPressed_PageView(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void addChannelList(ui::Layout* layout, ssize_t index);
//M by frank for channel favorite.
	void addChannelList(ui::Layout* layout, ChannelListPageView* ChannelListPageViewScene ,ssize_t index);
	void addInfoPanel(int type_index,int cur_page_index,int tableindex);
	
	
	void onKeyPressed_ChannelInfo(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);	
	
};

#endif // __CHANNELLIST_SCENE_H__
