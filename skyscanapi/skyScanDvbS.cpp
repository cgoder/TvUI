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

		if (pInstance->td_c.joinable()){//����Ǻ��б�Ҫ�ģ���Ϊthread::joinֻ�ܵ���һ�Σ�Ҫ��ֹ�����ط�����join��
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
/*��ͣ����*/
bool skyScanDvbS::skyScanPause()
{
#ifdef WIN32
	startenable = 0;
#endif
	return SKYSCAN_SUCCESS;
}
/*ֹͣ����*/
bool skyScanDvbS::skyScanStop()
{
#ifdef WIN32
	startenable = 0;
#endif
	return SKYSCAN_SUCCESS;
}
/*�ָ�����*/
bool skyScanDvbS::skyResumeScan()
{
#ifdef WIN32
	startenable = 1;
#endif
	return SKYSCAN_SUCCESS;
}

/*��ȡ��ǰ�ź�״̬*/
void skyScanDvbS::skyGetCurrentSignalPropety(skySignalStatus &frePropety)
{
	return;
}

/*ע��ص����������ؾ������������*/
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

/*��ȡ�������ǲ���*/
bool skyScanDvbS::skyDtvGetSatellitesinfo(vector<skySatellite_Info> &vec)
{
	return SKYSCAN_SUCCESS;
}
/*��ȡָ����������tp����*/
bool skyScanDvbS::skyDtvGetTranspondersInfo(const int satelliteNumber, vector<skyTransponder_Info> &vec)
{
	return SKYSCAN_SUCCESS;
}
/*����ָ������ ��Ϣ*/
bool skyScanDvbS::skyDtvUpdateSatelliteInfo(const int satelliteNumber, skySatellite_Info &info,int diseqc_type)
{
	return SKYSCAN_SUCCESS;
}
/*����ָ������ָ��tp ��Ϣ*/
bool skyScanDvbS::skyDtvUpdateTransponderInfo(const int satelliteNumber, const int transponderNumber, skyTransponder_Info &info)
{
	return SKYSCAN_SUCCESS;
}
/*�������*/
bool skyScanDvbS::skyDtvAddSatellite(skySatellite_Info &info)
{
	return SKYSCAN_SUCCESS;
}
/*ɾ������*/
bool skyScanDvbS::skyDtvDeletSatellite(unsigned int satelliteNumber)
{
	return SKYSCAN_SUCCESS;
}

/*���ָ������tp*/
bool skyScanDvbS::skyDtvAddTransponderInfo(const int satelliteNumber, skyTransponder_Info &info)
{
	return SKYSCAN_SUCCESS;
}
/*ɾ��ָ������tp*/
bool skyScanDvbS::skyDtvDeleteTransponderInfo(int satelliteNumber, int transponderNumber)
{
	return SKYSCAN_SUCCESS;
}
