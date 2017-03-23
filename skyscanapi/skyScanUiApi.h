#ifndef  _SKY_SCANAPI_H_
#define  _SKY_SCANAPI_H_

#include "skyScanType.h"
#include "vector"
using namespace std;

class skyScanUi
{
	public :

	skyScanUi();
	virtual~skyScanUi();
	/*开始搜索*/
	virtual bool skyScanStart();
	/*开始频段方式搜索，如果单频点搜索 endFre为0*/
	//virtual bool skyScanWithRangeStart(skyFreqData startFre, skyFreqData endFre);

	/*暂停搜索*/
	virtual bool skyScanPause();
	/*停止搜索*/
	virtual bool skyScanStop();
	/*恢复搜索*/
	virtual bool skyResumeScan();
	/*获取系统预存频点信息*/
	virtual void skyGetFreTable(vector<skyFreqData> &vec);
	/*获取当前信号状态*/
	virtual void skyGetCurrentSignalPropety(skySignalStatus &frePropety);
	
	/*注册回调函数，返回具体的搜索数据*/
	virtual void skyRegisterScanData(skyScanDataCallBack callback, void*  ptr);
	/*设置频点参数,PersistentNitCableInfo 暂时传入 0*/
	/*just for ATV*/
	/*设置当前节目sound，实时生效*/
	virtual bool skyAtvSetCurSound(skyAudioSystemType aValue);
	/*设置当前节目color，实时生效*/
	virtual bool skyAtvSetCurColor(skyColorSystemType aValue);
	/*设置fine 值*/
	virtual  bool skySetCurrentFineFreq(int fine);
	
	/*just for DTV-S*/



	/*获取所有卫星参数*/
	virtual  bool skyDtvGetSatellitesinfo(vector<skySatellite_Info> &vec);
	/*获取指定卫星所有tp参数*/
	virtual bool  skyDtvGetTranspondersInfo(const int satelliteNumber, vector<skyTransponder_Info> &info);
	/*更新指定卫星 信息*/
	virtual bool skyDtvUpdateSatelliteInfo(const int satelliteNumber, skySatellite_Info &info,int diseqc_type);
	/*更新指定卫星指定tp 信息*/
	virtual bool skyDtvUpdateTransponderInfo(const int satelliteNumber, const int transponderNumber, skyTransponder_Info &info);
	
	/*添加卫星*/
	virtual bool skyDtvAddSatellite(skySatellite_Info &info);
	/*删除卫星*/
	virtual  bool skyDtvDeletSatellite(unsigned int satelliteNumber);

	/*添加指定卫星tp*/
	virtual bool skyDtvAddTransponderInfo(const int satelliteNumber, skyTransponder_Info &info);
	/*删除指定卫星tp*/
	virtual bool skyDtvDeleteTransponderInfo(int satelliteNumber, int transponderNumber);
//	virtual bool getSatelliteInfo(const int index, Dtv_DVBS_Satellite_Info &info);
//	virtual int32_t getCurrentSatelliteNumber();
	//virtual bool setCurrentSatelliteNumber(int32_t satelliteNumber);
	///virtual int32_t getTransponderCount(int32_t satelliteNumber);
	//virtual int32_t getCurrentTransponderNumber();
	//virtual bool setCurrentTransponderNumber(int32_t transponderNumber);
	//virtual bool getTransponderInfo(const int satelliteNumber, const int transponderNumber, Dtv_DVBS_Transponder_Info &info);
	//virtual bool updateSatelliteInfo(const int satelliteNumber, skySatellite_Info &info);
	//virtual bool updateTransponderInfo(const int satelliteNumber, const int transponderNumber, skyTransponder_Info &info);
	//virtual bool addSatelliteInfo(skySatellite_Info &info);
	//virtual bool addTransponderInfo(const int satelliteNumber, Dtv_DVBS_Transponder_Info &info);
	//virtual bool deleteSatelliteInfo(int32_t satelliteNumber);
	//virtual bool deleteTransponderInfo(int32_t satelliteNumber, int32_t transponderNumber);
	//virtual bool sendDiSEqCMotorCommand(int32_t command);
	//virtual int32_t getUserLocationCount();
	//virtual bool getUserLocationInfo(const int locationNumber, Dtv_DVBS_Location_Info &info);
	//virtual bool setProgramSortByType(int32_t sortType);

	/*
	virtual bool verifySlotFrequency();
	virtual bool skyDtvSetDishLNBPowerMode(Dtv_Dvbs_Lnbpwr_OnOff mode);
	virtual bool skyDtvSetDish22KMode(Dtv_Dvbs_Tone_22KHZ mode);
	virtual bool setDishToneburstMode(int32_t mode);
	virtual bool setDiSEqCSwitchPort(uint8_t port, uint8_t unCommited);
	*/
	
	/*获取搜索参数*/
	virtual  bool skyDtvGetCurrentScanParam(skyScanParam &scanparam);

	/*设置搜索参数*/
	virtual  bool skyDtvSetScanParam(skyScanParam scanparam);

	/*reserve*/

	static skyScanUi* skyGetScanInstance(skyScanSourceType sourcetype);
	static void  skyScanDestroyInstance();

private:
	static skyScanUi* pInstance;

};

#endif