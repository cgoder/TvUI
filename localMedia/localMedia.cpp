#include "cocos2d.h"
#include "localMedia/localMedia.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
#include "menu/channelMenu.h"
#include "localMedia/pictureList.h"
#include "localMedia/audioList.h"
#include "localMedia/videoList.h"
#include "localMedia/deviceDetect.h"
#include "common/SkyDialog.h"
#ifndef _WIN32
#include <dirent.h>
#endif
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;


localMedia::localMedia()
{
	this->setName("localMedia");
	m_btnFocused = nullptr;
	m_readUsb = false;

}
localMedia::~localMedia()
{

}

Layer* localMedia::creatLayer(cocos2d::Node* node)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("localMedia");
		if (tuning) {
			return tuning;
		}
		else
		{
			localMedia* pRet = (localMedia*)localMedia::create();
			node->addChild(pRet);
			return pRet;
		}
	}
	return nullptr;
}


bool localMedia::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		bRet = true;
	} while (0);
	auto rootNode = CSLoader::createNode("localMeida.csb");
	this->addChild(rootNode);
	m_rootNode = rootNode;
	setBtnFunc(rootNode, "ID_BUT_DEVICE", CC_CALLBACK_2(localMedia::onBtnDevice, this), nullptr);
	setBtnFunc(rootNode, "ID_BUT_VIDEO", CC_CALLBACK_2(localMedia::onBtnVideo, this), nullptr);
	setBtnFunc(rootNode, "ID_BUT_AUDIO", CC_CALLBACK_2(localMedia::onBtnAudio, this), nullptr);
	setBtnFunc(rootNode, "ID_BUT_PIC", CC_CALLBACK_2(localMedia::onBtnPicture, this), nullptr);
	setBtnFunc(rootNode, "ID_BUT_NETSHARE", CC_CALLBACK_2(localMedia::onBtnShared, this), nullptr);

	this->scheduleOnce(schedule_selector(localMedia::readUsbData), 1);

	
	return bRet;
}

void localMedia::addTitle(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 60);
	text->setAnchorPoint(Vec2(0, 0));
	text->setColor(Color3B(153, 153, 153));
	text->setPosition(Vec2(87, 947));
	this->addChild(text);
}
void localMedia::addNote(const char* str)
{
	Text* text = Text::create(str, "general/SourceHanSansTWHK-Light.ttf", 32);
	text->setColor(Color3B(153, 153, 153));
	text->setAnchorPoint(Vec2(0, 0));
	text->setPosition(Vec2(387, 964));
	this->addChild(text);
}
void localMedia::readUsbData(float dt)
{
	std::map<std::string, std::string>  usbPathMap;
	usbPathMap = deviceDetect::getInstance()->getUsbPath();
	std::map<std::string, std::string>::iterator it;
	for (it = usbPathMap.begin(); it != usbPathMap.end(); ++it)
	{
		std::string path = it->second;
		getDirList(path.c_str(), GET_TYPE_ALL, m_pictureVec, m_audioVec, m_videoVec, m_fileVec);
	}
#ifdef _WIN32
	getDirList("", GET_TYPE_ALL, m_pictureVec, m_audioVec, m_videoVec, m_fileVec);
#endif
	this->addKeyListener(CC_CALLBACK_2(localMedia::onKeyPressed, this), this);
}
int localMedia::getDirList(const char *path, int type, std::vector<std::string> &piclist, std::vector<std::string> &audiolist, std::vector<std::string> &videolist, std::vector<std::string> &filelist)
{
#ifndef _WIN32
	struct dirent* ent = NULL;
	DIR *pDir;
	pDir = opendir(path);
	if (pDir == NULL) {
		return 0;
	}
	while (NULL != (ent = readdir(pDir))) {
		if (ent->d_type == 8) {
			//file  
			/*for (int i = 0; i < level; i++) {
			printf("-");
			}*/
			
			std::string _path(path);
			std::string _fileName(ent->d_name);
			std::string fullName = _path + "/" + _fileName;
			log("file:%s/n", ent->d_name);
			if (type & GET_TYPE_PIC)
			{
				int pos = _fileName.find_last_of('.');
				std::string filetype(_fileName.substr(pos + 1));
				if (filetype == "jpg" || filetype == "png" || filetype == "gif" || filetype == "bmp" )
				{
					piclist.push_back(fullName);
				}
			}
			if (type & GET_TYPE_AUDIO)
			{
				int pos = _fileName.find_last_of('.');
				std::string filetype(_fileName.substr(pos + 1));
				if (filetype == "mp3" || filetype == "aac" || filetype == "wav" )
				{
					audiolist.push_back(fullName);
				}
			}
			if (type & GET_TYPE_VIDEO)
			{
				int pos = _fileName.find_last_of('.');
				std::string filetype(_fileName.substr(pos + 1));
				if (filetype == "mp4" || filetype == "flv" || filetype == "m3u8" || filetype == "ts" || filetype == "mkv" || filetype == "rmvb")
				{
					videolist.push_back(fullName);
				}
			}
			if (type & GET_TYPE_FILES)
			{
				filelist.push_back(fullName);
			}
			
		}
		else {
			if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
				continue;
			}
			//directory  
			std::string _path(path);
			std::string _dirName(ent->d_name);
			std::string fullDirPath = _path + "/" + _dirName;
			log("dir:%s//n", ent->d_name);
			if (type & GET_TYPE_FILES)
			    filelist.push_back(fullDirPath);
			if (type & GET_TYPE_MEDIA)
			    getDirList(fullDirPath.c_str(),GET_TYPE_MEDIA, piclist, audiolist, videolist, filelist);

		}
	}
#else
	if (type & GET_TYPE_PIC)
	{
		piclist.push_back("general/general_arrow_focus.png");
		piclist.push_back("general/general_bg.png");
		piclist.push_back("general/general_button_focus.png");
		piclist.push_back("general/general_popup_bg.png");
		piclist.push_back("general/general_favicon.png");
		piclist.push_back("general/general_unlockicon.png");
		piclist.push_back("general/general_lockicon.png");
		piclist.push_back("general/general_recordicon.png");
	}
	if (type & GET_TYPE_AUDIO)
	{
		audiolist.push_back("general/南京新闻广播.png");
		audiolist.push_back("general/general_bg.png");
		audiolist.push_back("general/general_button_focus.png");
		audiolist.push_back("general/general_popup_bg.png");
		audiolist.push_back("general/general_favicon.png");
		audiolist.push_back("general/general_unlockicon.png");
		audiolist.push_back("general/general_lockicon.png");
		audiolist.push_back("general/general_recordicon.png");
	}
	if (type & GET_TYPE_VIDEO)
	{
		/*videolist.push_back("general/general_arrow_focus.png");
		videolist.push_back("general/general_bg.png");
		videolist.push_back("general/general_button_focus.png");
		videolist.push_back("general/general_popup_bg.png");
		videolist.push_back("general/general_favicon.png");
		videolist.push_back("general/general_unlockicon.png");
		videolist.push_back("general/general_lockicon.png");
		videolist.push_back("general/general_recordicon.png");
		videolist.push_back("general/general_arrow_focus.png");
		videolist.push_back("general/general_bg.png");
		videolist.push_back("general/general_button_focus.png");
		videolist.push_back("general/general_popup_bg.png");
		videolist.push_back("general/general_favicon.png");
		videolist.push_back("general/general_unlockicon.png");
		videolist.push_back("general/general_lockicon.png");
		videolist.push_back("general/general_recordicon.png");*/
	}
	if (type & GET_TYPE_FILES)
	{
		filelist.push_back("general/general_arrow_focus.png");
		filelist.push_back("general/general_bg.png");
		filelist.push_back("general/general_button_focus.png");
		filelist.push_back("general/general_popup_bg.png");
		filelist.push_back("general/general_favicon.png");
		filelist.push_back("general/general_unlockicon.png");
		filelist.push_back("general/general_lockicon.png");
		filelist.push_back("general/general_recordicon.png");
	}
	return 8;
#endif
}
#if 0
int localMedia::getDirList(const char *path, int type, std::vector<std::string> &list)
{
#ifndef _WIN32
	struct dirent* ent = NULL;
	DIR *pDir;
	pDir = opendir(path);
	if (pDir == NULL) {
		return 0;
	}
	while (NULL != (ent = readdir(pDir))) {
		if (ent->d_type == 8) {
			//file  
			/*for (int i = 0; i < level; i++) {
			printf("-");
			}*/
			std::string _path(path);
			std::string _dirName(ent->d_name);
			std::string fullName= _path + "/" + _dirName;
			log("file:%s/n", ent->d_name);
			list.push_back(fullName);
		}
		else {
			if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
				continue;
			}
			//directory  
			std::string _path(path);
			std::string _dirName(ent->d_name);
			std::string fullDirPath = _path + "/" + _dirName;
			log("dir:%s//n", ent->d_name);
			list.push_back(fullDirPath);

		}
	}
#else
	list.push_back("general/general_arrow_focus.png");
	list.push_back("general/general_bg.png");
	list.push_back("general/general_button_focus.png");
	list.push_back("general/general_popup_bg.png");
	list.push_back("general/general_favicon.png");
	list.push_back("general/general_unlockicon.png");
	list.push_back("general/general_lockicon.png");
	list.push_back("general/general_recordicon.png");
	return 8;
#endif
}
#endif

void localMedia::onFocusChanged(cocos2d::Node *nodeLostFocus, cocos2d::Node *nodeGetFocus)
{
	if (nodeLostFocus)
	{
		if (dynamic_cast<Button*>(nodeLostFocus))
		{
			((Button*)nodeLostFocus)->setTitleColor(Color3B(51, 51, 51));
		}

		nodeLostFocus->removeChildByName("ID_PIC_FOCUS");
		Vector<cocos2d::Node*> pChildren = nodeLostFocus->getChildren();
		for (Node *node : pChildren)
		{
			if (dynamic_cast<Text*>(node))
			{
				((Text*)node)->setColor(Color3B(153, 153, 153));
			}
			if (dynamic_cast<Button*>(node))
			{
				((Button*)node)->setHighlighted(false);
			}
		}
	}
	if (nodeGetFocus)
	{
		ImageView  * focus = ImageView::create("general/general_button_focus.png");
		focus->setScale9Enabled(true);
		focus->setCapInsets(Rect(40, 16, 135, 73));
		Size size = nodeGetFocus->getContentSize();
		int w = size.width;
		int h = size.height;
		if (h < 500) {
			focus->setContentSize(Size(w + 60, h + 60));
			focus->setPosition(Vec2(w / 2, h / 2 - 26));
		}
		else {
			focus->setContentSize(Size(w + 60, h + 74));
			focus->setPosition(Vec2(w / 2, h / 2 - 30));
		}
		focus->setZOrder(-1);
		focus->setName("ID_PIC_FOCUS");
		nodeGetFocus->addChild(focus);
		if (dynamic_cast<Button*>(nodeGetFocus))
		{
			((Button*)nodeGetFocus)->setTitleColor(Color3B(0, 0, 0));
		}
		Vector<cocos2d::Node*> pChildrenFocus = nodeGetFocus->getChildren();
		for (Node *node : pChildrenFocus)
		{
			if (dynamic_cast<Text*>(node))
			{
				((Text*)node)->setColor(Color3B(0, 0, 0));
			}
			else if (dynamic_cast<Button*>(node))
			{
				((Button*)node)->setHighlighted(true);
			}
		}
	}
}

void localMedia::onBtnDevice(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{

}
void localMedia::onBtnVideo(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{	
	int rows = (m_videoVec.size() % 4) == 0 ? (m_videoVec.size() / 4) : (m_videoVec.size() / 4 + 1);
	videoList* pRet = (videoList*)videoList::creatLayer(this, 4, rows, m_videoVec.size());
	pRet->setPicVec(m_videoVec);
	pRet->initTableView();

}
void localMedia::onBtnAudio(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	audioList* pRet = (audioList*)audioList::creatLayer(this, 1, m_audioVec.size(), m_audioVec.size());
	pRet->setPicVec(m_audioVec);
	pRet->initTableView();
}
void localMedia::onBtnPicture(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	int rows = (m_pictureVec.size() % 5) == 0 ? (m_pictureVec.size() / 5) : (m_pictureVec.size() / 5 + 1);
	pictureList* pRet = (pictureList*)pictureList::creatLayer(this, 5, rows, m_pictureVec.size());
	pRet->setPicVec(m_pictureVec);
	pRet->initTableView();
}
void localMedia::onBtnShared(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{

}