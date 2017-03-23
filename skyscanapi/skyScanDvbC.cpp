
#include "skyScanDvbC.h"

#include <chrono>    // std::chrono::seconds
#include <iostream>  // std::cout
skyScanDvbC* skyScanDvbC::pInstance = NULL;

skyScanDvbC::skyScanDvbC()
{
	data_callback =NULL;
	scandata.current_freq = 0;
	scandata.data_count = 0;
	scandata.process = 0;
	scandata.radio_count = 0;
	scandata.analogtv_count = 0;
	scandata.digitaltv_count = 0;
	scandata.signal_quality = 0;
	scandata.signal_strength = 0;
	scandata.scanstatus = STATUS_SKYSCAN_UNKNOW;
	//m_automodel = FULLSACN;
#ifdef WIN32
	startenable = 0;
	ptr_tmp = NULL;
		destoryenable = 1;
	td_c = thread(&skyScanDvbC::thread_task, this);
#endif
	
	
	return;
}
skyScanDvbC::~skyScanDvbC()
{
#ifdef WIN32
	if (pInstance->td_c.joinable()){//����Ǻ��б�Ҫ�ģ���Ϊthread::joinֻ�ܵ���һ�Σ�Ҫ��ֹ�����ط�����join��
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
void skyScanDvbC::thread_task()
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
		pInstance->scandata.digitaltv_count = count;
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
skyScanDvbC* skyScanDvbC::skyGetScanInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new skyScanDvbC;
		
	}
	return pInstance;
}

bool skyScanDvbC::skyScanStart()

{
#ifdef WIN32
	startenable = 1;
#endif
	return SKYSCAN_SUCCESS;
}

/*��ͣ����*/

/*��ͣ����*/
bool skyScanDvbC::skyScanPause()
{
#ifdef WIN32
	startenable = 0;
#endif
	return SKYSCAN_SUCCESS;
}
/*ֹͣ����*/
bool skyScanDvbC::skyScanStop()
{
#ifdef WIN32
	startenable = 0;
#endif
	return SKYSCAN_SUCCESS;
}
/*�ָ�����*/
bool skyScanDvbC::skyResumeScan()
{
#ifdef WIN32
	startenable = 1;
#endif
	return SKYSCAN_SUCCESS;
}

/*��ȡ��ǰ�ź�״̬*/
void skyScanDvbC::skyGetCurrentSignalPropety(skySignalStatus &frePropety)
{
	return;
}

/*ע��ص����������ؾ������������*/
void skyScanDvbC::skyRegisterScanData(skyScanDataCallBack callback, void* ptr)
{
	ptr_tmp = ptr;
	data_callback = callback;
	return;
}
skyScanSourceType skyScanDvbC::skyGetScanSourceType()
{
	return SOURCE_TYPE_DVBC_S;
}


bool skyScanDvbC::skyDtvGetCurrentScanParam(skyScanParam &scanparam)
{
	return SKYSCAN_SUCCESS;
}
bool skyScanDvbC::skyDtvSetScanParam(skyScanParam scanparam)
{
	return SKYSCAN_SUCCESS;
}
