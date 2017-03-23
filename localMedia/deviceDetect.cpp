#include "cocos2d.h"
#include "localMedia/deviceDetect.h"
#include "localMedia/localMedia.h"
#include "common/SkyDialog.h"
#include  <thread> 
#ifndef _WIN32
#include <sys/socket.h>
#include <linux/netlink.h>
#include <unistd.h>
#include <mntent.h>
#include <sys/mount.h>
#include <sys/poll.h>
#include <dirent.h>
#endif
USING_NS_CC;
using namespace cocos2d::ui;

deviceDetect* deviceDetect::pInstance = NULL;
deviceDetect::deviceDetect()
{

}
deviceDetect::~deviceDetect()
{
	pInstance = nullptr;
}
deviceDetect* deviceDetect::getInstance(void)
{
	if (!pInstance)
		pInstance = new deviceDetect();
	return pInstance;
}
void deviceDetect::showUsbNotifyUi(const char* usbPath)
{
	auto scene = Director::getInstance()->getRunningScene();
	SkyDialog* dia = SkyDialog::create(scene, "Dialog.csb", (Click_CallFun)(&deviceDetect::onBtnYes), (Click_CallFun)(&deviceDetect::onBtnNo),this);
	char title[512];
	sprintf(title, "detected usb device %s", usbPath);
	dia->setTextTitle("ID_TEXT_TITLE", title);
}
void deviceDetect::onBtnYes(cocos2d::Node* node)
{
	auto scene = Director::getInstance()->getRunningScene();
	localMedia::creatLayer(scene);

}
void deviceDetect::onBtnNo(cocos2d::Node* node)
{
}
void deviceDetect::startDeviceDetect()
{
	td_c = std::thread(&deviceDetect::detectThread, this);
}
bool deviceDetect::isExistUsbPath(const char* pMountPath)
{
	bool retval = false;
	FILE* fp = fopen("/proc/mounts", "rb");
	if (fp == NULL) {
		log("detectThread /proc/mounts open failed!");
		return false;
	}
	char buffer[1025];
	while (fgets(buffer, 1024, fp)) {
		int index = 0;
		int path_len = 0;
		char ppath[512] = { 0 };
		char* ptr = strstr(buffer, pMountPath);
		memset(ppath, 0x0, 512);
		if (ptr == nullptr)
			continue;
		retval = true;
		break;
	}
	fclose(fp);
	return retval;
}
bool deviceDetect::removeUsbPath(const char* devPath)
{
	bool ret = true;

	std::map<std::string, std::string>::iterator it;
	for (it = m_usbPathMap.begin(); it != m_usbPathMap.end(); ++it)
	{
		std::string path = it->first;
		std::string mountPath = it->second;
		log("detectThread:devpath:%s, first:%s,sencond:%s", devPath,path.c_str(), mountPath.c_str());
		if (path == devPath) {
			if (isExistUsbPath(mountPath.c_str()))
			{
				ret = true;
				m_usbPathMap.erase(it);
				log("detectThread is eraseed");
			}
			else
				ret = false;
			break;
		}
	}

	log("detectThread remove m_usbPathVec:%d,%d", m_usbPathMap.size(), ret);
	return ret;
}
bool deviceDetect::saveUsbPath(const char* devPath)
{
	std::string mountPath;
	int ret = GetMountPath(mountPath, devPath);
	log("detectThread m_usbPathVec:%d", m_usbPathMap.size());
	return ret;
}
bool deviceDetect::GetMountPath(std::string &mountPath, const char *devPath)
{
	log("detectThread getmount :%s", devPath);
	bool retval = false;
	FILE* fp = fopen("/proc/mounts", "rb");
	if (fp == NULL) {
		log("detectThread /proc/mounts open failed!");
		return false;
	}
	char buffer[1025];
	while (fgets(buffer, 1024, fp)) {
		int index = 0;
		int path_len = 0;
		char ppath[512] = { 0 };
		char* ptr = strstr(buffer, devPath);
		memset(ppath, 0x0, 512);

		char devtemp[64] = { 0 };
		if (ptr == nullptr)
			continue;
		for (index = 0; index < 511; index++) {
			sscanf(ptr, "%s %s", devtemp, ppath);

		}
		mountPath = ppath;
		log("detectThread,ppath %s,%d\n", ppath, mountPath.find("usb"));
		if (mountPath.find("usb") != -1)
		{
			bool isexist = false;
			std::map<std::string, std::string>::iterator it;
			for (it = m_usbPathMap.begin(); it != m_usbPathMap.end(); ++it)
			{
				std::string path = it->second;
				if (path == mountPath.c_str())
				{
					isexist = true;
				}
			}
			if (!isexist)
			{
				m_usbPathMap.insert(std::make_pair(devtemp, mountPath));
			}
			retval = true;
		}
	}
	fclose(fp);
	return retval;

}
void deviceDetect::detectThread()
{
	std::string usbPath;
	saveUsbPath("/dev");
	log("detectThread");
#ifdef _WIN32
	std::this_thread::sleep_for(std::chrono::microseconds(1000 * 1000 * 2));
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]
	{
		showUsbNotifyUi("usb");
	});
#endif
#ifndef _WIN32
	const int  buffSize = 1024;
	struct sockaddr_nl   socknl = { 0 };
	int hotplugsocket = -1;
	struct      pollfd pfd;
	socknl.nl_family = AF_NETLINK;
	socknl.nl_pid = getpid();
	socknl.nl_groups = -1;
	pfd.events = POLLIN;
	pfd.fd = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
	bind(pfd.fd, (struct sockaddr *)&socknl, sizeof(struct sockaddr_nl));
	int time_out;
	while (1)
	{
		int   i = 0;
		int len;
		char  buf[1024] = { 0 };
		time_out = poll(&pfd, 1, 1000);
		if (time_out == -1)
			continue;
		if (time_out == 0)
			continue;
		len = recv(pfd.fd, buf, sizeof(buf), 1000);

		//log("detectThread:%d", __LINE__);
		//recv(hotplugsocket, buf, 4095, 0);
		if (len < 0)
			continue;
		char devicePath[64] = { 0 };
		sprintf(devicePath, "%s", "/dev/");
		if (!strncmp(buf, "change@", 7) == 0) {
			//log("detectThread:%d", __LINE__);
			//log("detectThread===>%s \n", buf);
			printf("#####################detectThread===>%s \n", buf);
		}

		if (strncmp(buf, "add@", 4) == 0) {
			char* temp = buf;
			if (strstr(temp, "usb"))
			{
				char* blockstr = strstr(buf, "block/");
				if (blockstr) {
					log("detectThread:%s   ,buf:%s", blockstr, buf);
					int ret = sscanf(blockstr, "%*[^/]/%*[^/]/%s", devicePath + 5);
					if (ret > 0)
					{
						log("detectThread:add,ret:%d, %s", ret, devicePath);
#ifdef ANDROID
						sprintf(devicePath, "%s", "/dev/block/vold/8:1");
#endif
						int trytimes = 0;
						int ret = saveUsbPath((const char*)devicePath);
						while (!ret)
						{
							if (trytimes++ > 10)
								break;
							std::this_thread::sleep_for(std::chrono::microseconds(1000 * 1000 * 2));
							ret = saveUsbPath((const char*)devicePath);
						}
						if (ret) {
							Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]
							{
								showUsbNotifyUi("usb");
							});
						}
					}
				}
			}
		}
		else if (strncmp(buf, "remove@", 7) == 0) {
			char* temp = buf;
			if (strstr(temp, "usb"))
			{
				char* blockstr = strstr(buf, "block/");
				if (blockstr) {
					log("detectThread:%s   ,buf:%s", blockstr, buf);
					int ret = sscanf(blockstr, "%*[^/]/%*[^/]/%s", devicePath + 5);
					if (ret > 0)
					{
#ifdef ANDROID
						sprintf(devicePath, "%s", "/dev/block/vold/8:1");
#endif
						log("detectThread:remove,ret:%d, %s", ret, devicePath);
						int trytimes = 0;
						while (!removeUsbPath((const char*)devicePath))
						{
							if (trytimes++ > 10)
								break;
							std::this_thread::sleep_for(std::chrono::microseconds(1000 * 1000 * 2));
						}
					}
				}
			}
		}
	}
#else
	_sleep(10000000);
#endif

}