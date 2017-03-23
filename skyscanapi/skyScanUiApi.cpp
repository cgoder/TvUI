#include "skyScanUiApi.h"
#include "skyScanAtv.h"
#include "skyScanDvbC.h"
#include "skyScanDvbS.h"
#include "skyScanDvbT.h"

skyScanUi*skyScanUi:: pInstance = NULL;

skyScanUi::skyScanUi()
{
	return;
}

skyScanUi::~skyScanUi()
{
	return;
}
/*开始自动搜索*/
bool skyScanUi::skyScanStart()
{
	return SKYSCAN_SUCCESS;
}

/*暂停搜索*/
bool skyScanUi::skyScanPause()
{
	return SKYSCAN_SUCCESS;
}
/*停止搜索*/
bool skyScanUi::skyScanStop()
{
	return SKYSCAN_SUCCESS;
}
/*恢复搜索*/
bool skyScanUi::skyResumeScan()
{
	return SKYSCAN_SUCCESS;
}
/*获取系统预存频点信息*/
void skyScanUi::skyGetFreTable(vector<skyFreqData> &vec)
{
	return;
}
/*获取当前信号状态*/
void skyScanUi::skyGetCurrentSignalPropety(skySignalStatus &frePropety)
{
	return;
}

/*注册回调函数，返回具体的搜索数据*/
void skyScanUi::skyRegisterScanData(skyScanDataCallBack callback, void*  ptr)
{
	return;
}


/*just for ATV*/
/*设置当前节目sound*/
bool skyScanUi::skyAtvSetCurSound(skyAudioSystemType aValue)
{
	return SKYSCAN_SUCCESS;
}
/*设置当前节目color*/
bool skyScanUi::skyAtvSetCurColor(skyColorSystemType aValue)
{
	return SKYSCAN_SUCCESS;
}
/*设置fine 值*/
bool skyScanUi::skySetCurrentFineFreq(int fine)
{
	return SKYSCAN_SUCCESS;
}

/*just for DTV-S*/
bool skyScanUi::skyDtvGetSatellitesinfo(vector<skySatellite_Info> &vec)
{
	 return SKYSCAN_SUCCESS;
}
bool skyScanUi::skyDtvGetTranspondersInfo(const int satelliteNumber, vector<skyTransponder_Info> &info)
{
	return SKYSCAN_SUCCESS;
}
bool skyScanUi::skyDtvUpdateSatelliteInfo(const int satelliteNumber, skySatellite_Info &info,int diseqc_type)
{
	return SKYSCAN_SUCCESS;
}
bool skyScanUi::skyDtvUpdateTransponderInfo(const int satelliteNumber, const int transponderNumber, skyTransponder_Info &info)
{
	return SKYSCAN_SUCCESS;
}
bool skyScanUi::skyDtvAddSatellite(skySatellite_Info &info)
{
	return SKYSCAN_SUCCESS;
}
bool skyScanUi::skyDtvDeletSatellite(unsigned int satelliteNumber)
{
	return SKYSCAN_SUCCESS;
}
bool skyScanUi::skyDtvAddTransponderInfo(const int satelliteNumber, skyTransponder_Info &info)
{
	return SKYSCAN_SUCCESS;
}
bool skyScanUi::skyDtvDeleteTransponderInfo(int satelliteNumber, int transponderNumber)
{
	return SKYSCAN_SUCCESS;
}

void skyScanUi::skyScanDestroyInstance()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = NULL;
	}
}
skyScanUi* skyScanUi::skyGetScanInstance(skyScanSourceType sourcetype)
{
	static skyScanSourceType sourcetype_tmp;
	if ((sourcetype != sourcetype_tmp) || (pInstance == NULL))
	{
		sourcetype_tmp = sourcetype;
		switch (sourcetype_tmp)
		{
			case SOURCE_TYPE_ATV_S:
				pInstance = skyScanAtv::skyGetScanInstance();
				break;
			case SOURCE_TYPE_DVBC_S:
				pInstance = skyScanDvbC::skyGetScanInstance();
				break;
			case SOURCE_TYPE_DVBT_S:
				pInstance = skyScanDvbT::skyGetScanInstance();
				break;
			case SOURCE_TYPE_DVBS_S:
				pInstance = skyScanDvbS::skyGetScanInstance();
				break;
			case SOURCE_TYPE_DTMB_S:
				pInstance = skyScanDvbT::skyGetScanInstance();
				break;
			default:
				pInstance = skyScanAtv::skyGetScanInstance();
				break;
		}
	
	}
	return pInstance;
}
bool skyScanUi::skyDtvSetScanParam(skyScanParam scanparam)
{
	return SKYSCAN_SUCCESS;
}
bool skyScanUi::skyDtvGetCurrentScanParam(skyScanParam &scanparam)
{
	return SKYSCAN_SUCCESS;
}