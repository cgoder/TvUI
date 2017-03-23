#ifndef __CHANNELEDIT_SCENE_H__
#define __CHANNELEDIT_SCENE_H__

#include "cocos2d.h"
#include "ChannelList/ChannelListPage.h"

#include "common/SkyLayer.h"

#define CHEDIT_FOCUS_IMG_POS 728
#define CHEDIT_ITEM_NUM 7
#define CHEDIT_FOCUS_IMG_TAG 0x202
#define CHEDIT_ATTR_TAG 0x100

#define CHNUM_X_POS 730

enum
{
	CHEDIT_NULL,
	CHEDIT_CHANNEL_NUMBER,
	CHEDIT_LOCK,
	CHEDIT_FAVOURITE,
	CHEDIT_DELETE,
};


class ChannelEdit : public SkyLayer
{
public:
	ChannelEdit();
	~ChannelEdit();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
   	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	virtual bool skyShow(cocos2d::Node* node);
	virtual void skyHide(cocos2d::Node* node);
	virtual void skyRefresh();
    // implement the "static create()" method manually
    CREATE_FUNC(ChannelEdit);
    
protected:  
	void initChannelEdit();  
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    	
	void addChannelList(ui::Layout* layout, ssize_t index);
	void addChannelPin();
	void onKeyPressed_ChannelPin(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	
	void updateChannelAttr(ui::Layout* layout,bool is_locked);	
	void modifyChannelAttr(ui::Layout* layout,int type_index,int table_index);	
	
	void moveChannel(TableView* table,ssize_t idx);
	void setLock(TableView* table,ssize_t idx);
	void setFavourite(TableView* table,ssize_t idx);
	void deleteChannel(TableView* table,ssize_t idx);	
		
	bool changing_number;		
};

#endif // __CHANNELEDIT_SCENE_H__
