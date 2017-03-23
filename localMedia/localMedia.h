#ifndef  _LOCAL_MEIDA_H_
#define  _LOCAL_MEIDA_H_
#include "cocos2d.h"
#include "common/common.h"
#include "common/SkyLayer.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
#include "epg/GridView/GridView.h"
#include "common/BtnFocusLayer.h"
#define GET_TYPE_PIC 0x01
#define GET_TYPE_AUDIO 0x02
#define GET_TYPE_VIDEO 0x04
#define GET_TYPE_FILES 0x08
#define GET_TYPE_ALL (GET_TYPE_PIC | GET_TYPE_AUDIO | GET_TYPE_VIDEO | GET_TYPE_FILES)
#define GET_TYPE_MEDIA (GET_TYPE_PIC | GET_TYPE_AUDIO | GET_TYPE_VIDEO)

typedef void (cocos2d::Ref::*Click_CallFun)(cocos2d::Node* node);
class localMedia :
	public BtnFocusLayer
{
public:
	localMedia();
	~localMedia();
	virtual bool init();
	static cocos2d::Layer* creatLayer(cocos2d::Node* node);
	void addTitle(const char* str);
	void addNote(const char* str);
	CREATE_FUNC(localMedia);
	virtual void onFocusChanged(cocos2d::Node *nodeLostFocus, cocos2d::Node *nodeGetFocus);
	void onBtnDevice(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnVideo(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnAudio(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnPicture(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onBtnShared(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	int getDirList(const char *path, int type, std::vector<std::string> &piclist, std::vector<std::string> &audiolist, std::vector<std::string> &videolist, std::vector<std::string> &filelist);
protected:
	void readUsbData(float dt);
	cocos2d::Node* m_rootNode;
	std::vector<std::string> m_pictureVec;
	std::vector<std::string> m_audioVec;
	std::vector<std::string> m_videoVec;
	std::vector<std::string> m_fileVec;
	bool m_readUsb;
};

#endif

