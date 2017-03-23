
#include "skyScanDvbT.h"

#include <chrono>    // std::chrono::seconds
#include <iostream>  // std::cout
skyScanDvbT* skyScanDvbT::pInstance = NULL;
skyScanDvbT::skyScanDvbT()
{
	data_callback = NULL;
	scandata.current_freq = 0;
	scandata.data_count = 0;
	scandata.process = 0;
	scandata.radio_count = 0;
	scandata.analogtv_count = 0;
	scandata.digitaltv_count = 0;
	scandata.signal_quality = 0;
	scandata.signal_strength = 0;
	scandata.scanstatus = STATUS_SKYSCAN_UNKNOW;
	ptr_tmp = NULL;
#ifdef WIN32
	startenable = 0;
	destoryenable = 1;
	
	td_c = thread(&skyScanDvbT::thread_task, this);
#endif
	return;
}
skyScanDvbT::~skyScanDvbT()
{
#ifdef WIN32

		if (pInstance->td_c.joinable()){//检测是很有必要的，因为thread::join只能调用一次，要防止其它地方意外join了
		{			
			destoryenable = 0;

			pInstance->td_c.join();
			pInstance = NULL;			
		}	
	}
		#else
		pInstance = NULL;	
		#endif
	return;
}
#ifdef WIN32
void skyScanDvbT::thread_task()
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

		pInstance->scandata.radio_count = count;
		pInstance->scandata.data_count = count;
		pInstance->scandata.digitaltv_count = count;
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
skyScanDvbT* skyScanDvbT::skyGetScanInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new skyScanDvbT;
	}
	return pInstance;
}

bool skyScanDvbT::skyScanStart()
{
#ifdef WIN32
	startenable = 1;
#endif
	return SKYSCAN_SUCCESS;
}
/*暂停搜索*/
bool skyScanDvbT::skyScanPause()
{
#ifdef WIN32
	startenable = 0;
#endif
	return SKYSCAN_SUCCESS;
}
/*停止搜索*/
bool skyScanDvbT::skyScanStop()
{
#ifdef WIN32
	startenable = 0;
#endif
	return SKYSCAN_SUCCESS;
}
/*恢复搜索*/
bool skyScanDvbT::skyResumeScan()
{
#ifdef WIN32
	startenable = 1;
#endif
	return SKYSCAN_SUCCESS;
}


/*获取当前信号状态*/
void skyScanDvbT::skyGetCurrentSignalPropety(skySignalStatus &frePropety)
{
	return;
}

/*注册回调函数，返回具体的搜索数据*/
void skyScanDvbT::skyRegisterScanData(skyScanDataCallBack callback, void* ptr)
{
	ptr_tmp = ptr;
	data_callback = callback;
	return;
}

skyScanSourceType skyScanDvbT::skyGetScanSourceType()
{
	return SOURCE_TYPE_DVBT_S;
}

void skyScanDvbT::skyGetFreTable(vector<skyFreqData> &vec)
{
	
#ifdef WIN32
	skyFreqData freqdata;
	for (int i = 0; i < 10; i++)
	{
		freqdata.freq = 44300 + i * 100;
		freqdata.modulation = S_MODULATION_MODE_QAM16;
		freqdata.symbolRate = 6875;
		vec.push_back(freqdata);
	}
	
#endif

	return;
}
bool skyScanDvbT::skyDtvSetScanParam(skyScanParam scanparam)
{
	return SKYSCAN_SUCCESS ;
}