#include "skyScanDvbS.h"
#include <sstream> 
#include <chrono>    // std::chrono::second

skyScanDvbS* skyScanDvbS::pInstance = NULL;
skyScanDvbS::skyScanDvbS()
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
	
	
#ifdef WIN32
	destoryenable = 1;
	startenable = 0;
	ptr_tmp = NULL;
	td_c = thread(&skyScanDvbS::thread_task, this);
#endif
	return;
}
skyScanDvbS::~skyScanDvbS()
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
void skyScanDvbS::thread_task()
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
skyScanDvbS* skyScanDvbS::skyGetScanInstance()
{
	if (pInstance == NULL)
	{
		pInstance=new skyScanDvbS;
	}
	return pInstance;
}




bool skyScanDvbS::skyScanStart()
{
#ifdef WIN32
	startenable = 1;
#endif
	return SKYSCAN_SUCCESS;
}
/*暂停搜索*/
bool skyScanDvbS::skyScanPause()
{
#ifdef WIN32
	startenable = 0;
#endif
	return SKYSCAN_SUCCESS;
}
/*停止搜索*/
bool skyScanDvbS::skyScanStop()
{
#ifdef WIN32
	startenable = 0;
#endif
	return SKYSCAN_SUCCESS;
}
/*恢复搜索*/
bool skyScanDvbS::skyResumeScan()
{
#ifdef WIN32
	startenable = 1;
#endif
	return SKYSCAN_SUCCESS;
}

/*获取当前信号状态*/
void skyScanDvbS::skyGetCurrentSignalPropety(skySignalStatus &frePropety)
{
	return;
}

/*注册回调函数，返回具体的搜索数据*/
void skyScanDvbS::skyRegisterScanData(skyScanDataCallBack callback, void* ptr)
{
	ptr_tmp =  ptr;
	data_callback = callback;
	return;
}

skyScanSourceType skyScanDvbS::skyGetScanSourceType()
{
	return SOURCE_TYPE_DVBS_S;
}
bool skyScanDvbS::skyDtvSetScanParam(skyScanParam scanparam)
{
	return SKYSCAN_SUCCESS;
}

/*获取所有卫星参数*/
bool skyScanDvbS::skyDtvGetSatellitesinfo(vector<skySatellite_Info> &vec)
{
	return SKYSCAN_SUCCESS;
}
/*获取指定卫星所有tp参数*/
bool skyScanDvbS::skyDtvGetTranspondersInfo(const int satelliteNumber, vector<skyTransponder_Info> &vec)
{
	return SKYSCAN_SUCCESS;
}
/*更新指定卫星 信息*/
bool skyScanDvbS::skyDtvUpdateSatelliteInfo(const int satelliteNumber, skySatellite_Info &info,int diseqc_type)
{
	return SKYSCAN_SUCCESS;
}
/*更新指定卫星指定tp 信息*/
bool skyScanDvbS::skyDtvUpdateTransponderInfo(const int satelliteNumber, const int transponderNumber, skyTransponder_Info &info)
{
	return SKYSCAN_SUCCESS;
}
/*添加卫星*/
bool skyScanDvbS::skyDtvAddSatellite(skySatellite_Info &info)
{
	return SKYSCAN_SUCCESS;
}
/*删除卫星*/
bool skyScanDvbS::skyDtvDeletSatellite(unsigned int satelliteNumber)
{
	return SKYSCAN_SUCCESS;
}

/*添加指定卫星tp*/
bool skyScanDvbS::skyDtvAddTransponderInfo(const int satelliteNumber, skyTransponder_Info &info)
{
	return SKYSCAN_SUCCESS;
}
/*删除指定卫星tp*/
bool skyScanDvbS::skyDtvDeleteTransponderInfo(int satelliteNumber, int transponderNumber)
{
	return SKYSCAN_SUCCESS;
}
