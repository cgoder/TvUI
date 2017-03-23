#ifndef  _COMMON_API_H_
#define  _COMMON_API_H_
#include "cocos2d.h"
#include "tvplayer/tv_common.h"

//#include "common/slock.h"
//
//class SkyLock : public IMutex
//{
//public:
//	SkyLock(const ILock&);
//	~SkyLock();
//
//private:
//	const ILock& mLock;
//};
//
//inline SkyLock::SkyLock(const ILock & lock) : mLock(lock)
//{
//	mLock.Lock();
//}
//
//inline SkyLock::~SkyLock()
//{
//	mLock.Unlock();
//}
//
//
//
#ifdef _WIN32
#define FUNC_ENTRY() {}//printf("\n######## [%s]%d enter! #######\n", __FUNCTION__,__LINE__)
#define FUNC_EXIT() {}//printf("\n######## [%s]%d exit! #######\n", __FUNCTION__,__LINE__)
#else
#define FUNC_ENTRY() printf("\n######## [%s]%d enter! #######\n", __PRETTY_FUNCTION__,__LINE__)
#define FUNC_EXIT() printf("\n######## [%s]%d exit! #######\n", __PRETTY_FUNCTION__,__LINE__)
#endif


#define Get_TvPlayer()	(skyTvMw::getInstance()->getPlayer())

class CommonApi
{
public:
	CommonApi();
	~CommonApi();

	static CommonApi* getInstance();
	void removeKeyListener(std::string name, cocos2d::EventDispatcher* dispatcher);
	void addKeyListener(std::string name, std::function<void(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*)> keyback, cocos2d::EventDispatcher* dispatcher);

	void addKeyListener(std::string name, cocos2d::EventListener* listener, cocos2d::EventDispatcher* dispatcher);


	// implement the "static create()" method manually

protected:
	static CommonApi * sm_pCommonApi;
	cocos2d::Map<std::string, cocos2d::EventListener*>  keymap;
	bool _keydeal;
	int _keypriority;
};
#endif

