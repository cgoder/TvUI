
#include "skyScanAtv.h"

#include <chrono>    // std::chrono::seconds
#include <iostream>  // std::cout
skyScanAtv* skyScanAtv::pInstance = NULL;

skyScanAtv::skyScanAtv()
{
	data_callback = NULL;

	scandata.current_freq = 0;
	scandata.data_count = 0;
	scandata.process = 0;
	scandata.radio_count = 0;
	scandata.analogtv_count = 0;
	scandata.current_channelnum = 0;
	scandata.digitaltv_count = 0;
	scandata.signal_quality = 0;
	scandata.signal_strength = 0;
	scandata.scanstatus = STATUS_SKYSCAN_UNKNOW;
	
#ifdef WIN32
	ptr_tmp = NULL;
	startenable = 0;
	destoryenable = 1;
	td_c = thread(&skyScanAtv::thread_task, this);
#endif
	return;
}
skyScanAtv::~skyScanAtv()
{
#ifdef WIN32
	if (pInstance->td_c.joinable()){//检测是很有必要的，因为thread::join只能调用一次，要防止其它地方意外join了
		destoryenable = 0;
		pInstance->td_c.join();
		pInstance = NULL;
	}
	#else
	pInstance = NULL;
	#endif
	return;
}
#ifdef WIN32
void skyScanAtv::thread_task()
{
	static int count = 0;
	while (destoryenable)
	{
		if (!pInstance)
		{
			continue;
		}
		if (!pInstance->startenable)
		{
			continue;
		}

		count++;
		if (count >= 20)
		{
			if (count == 20)
			{
				pInstance->scandata.scanstatus = STATUS_SKYSCAN_TUNING_END;
			}
			else
			{
				pInstance->startenable = 0;
				count = 0;
				continue;
			}

		}

		pInstance->scandata.current_freq = 44300 + count * 100;
		pInstance->scandata.analogtv_count = count;
		pInstance->scandata.process = count * 5;
		if (data_callback)
		{
			pInstance->data_callback(scandata, ptr_tmp);
		}
		this_thread::sleep_for(chrono::microseconds(SKYSCAN_INTERVAL));
	}
	return;

}
#endif
skyScanAtv* skyScanAtv::skyGetScanInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new skyScanAtv;
	}
	return pInstance;
}


/*开始自动搜索*/
bool skyScanAtv::skyScanStart()
{
#ifdef WIN32
	startenable = 1;
#endif
	return SKYSCAN_SUCCESS;
}
/*暂停搜索*/
bool skyScanAtv::skyScanPause()
{
#ifdef WIN32
	startenable = 0;
#endif
	return SKYSCAN_SUCCESS;
}
/*停止搜索*/
bool skyScanAtv::skyScanStop()
{
#ifdef WIN32
	startenable = 0;
#endif
	return SKYSCAN_SUCCESS;
}
/*恢复搜索*/
bool skyScanAtv::skyResumeScan()
{
#ifdef WIN32
	startenable = 1;
#endif
	return SKYSCAN_SUCCESS;
}

/*获取当前信号状态*/
void skyScanAtv::skyGetCurrentSignalPropety(skySignalStatus &frePropety)
{
	return;
}

/*注册回调函数，返回具体的搜索数据*/
void skyScanAtv::skyRegisterScanData(skyScanDataCallBack callback, void* ptr)
{
	ptr_tmp = ptr;
	data_callback = callback;
	return;
}

skyScanSourceType skyScanAtv::skyGetScanSourceType()
{
	return SOURCE_TYPE_ATV_S;
}

/*设置当前节目sound*/
bool skyScanAtv::skyAtvSetCurSound(skyAudioSystemType aValue)
{
	return SKYSCAN_SUCCESS;
}
/*设置当前节目color*/
bool skyScanAtv::skyAtvSetCurColor(skyColorSystemType aValue)
{
	return SKYSCAN_SUCCESS;
}
/*获取当前节目sound*/
skyAudioSystemType skyScanAtv::skyAtvGetCurSoundSystem(void)
{
	return ATV_MODE_BG;
}
/*获取当前节目color*/
skyColorSystemType skyScanAtv::skyAtvGetCurColorSystem(void)
{
	return ATV_COLOR_AUTO;
}

/*获取当前节目index ，just for atv*/
int skyScanAtv::getCurrentProgrameIndex()
{
	return SKYSCAN_SUCCESS;
}
/*获取fine 值*/
unsigned int skyScanAtv::skyGetCurrentFineFreq()
{
	return SKYSCAN_SUCCESS;
}
/*设置fine 值*/
bool skyScanAtv::skySetCurrentFineFreq(int fine)
{
	return SKYSCAN_SUCCESS;
}
bool skyScanAtv::skyDtvGetCurrentScanParam(skyScanParam &scanparam)
{
	return SKYSCAN_SUCCESS;
}
bool skyScanAtv::skyDtvSetScanParam(skyScanParam scanparam)
{
	return SKYSCAN_SUCCESS;
	
}
