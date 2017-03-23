#ifndef  _DEVICE_DETECT_H_
#define  _DEVICE_DETECT_H_
#include "cocos2d.h"
#include  <thread> 

class deviceDetect:public cocos2d::Ref
{
public:
	deviceDetect();
	~deviceDetect();
	static deviceDetect* getInstance(void);
	void showUsbNotifyUi(const char* usbPath);
	void onBtnYes(cocos2d::Node* node);
	void onBtnNo(cocos2d::Node* node);
	void startDeviceDetect();
	void detectThread();
	bool GetMountPath(std::string &mountPath , const char *devPath);
	bool removeUsbPath(const char* devPath);
	bool isExistUsbPath(const char* pMountPath);
	bool saveUsbPath(const char* devPath);
	std::map<std::string, std::string>  getUsbPath() {
		return m_usbPathMap;
	};
	static deviceDetect* pInstance;
protected:
	std::thread td_c;
	std::map<std::string, std::string>  m_usbPathMap;

};
#endif

