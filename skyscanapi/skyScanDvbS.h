#ifndef  _SKY_SCANDVBS_H_
#define  _SKY_SCANDVBS_H_
#include "skyScanUiApi.h"
#include "skyScanType.h"
#include  <thread> 

using namespace std;

/*xxxx具体平台相关*/
class skyScanDvbS : public skyScanUi
{
public:
	
	skyScanDvbS();
	~skyScanDvbS();
	/*开始自动搜索*/
	virtual bool skyScanStart();
	/*暂停搜索*/
	virtual bool skyScanPause();
	/*停止搜索*/
	virtual bool skyScanStop();
	/*恢复搜索*/
	virtual bool skyResumeScan();
	/*获取当前信号状态*/
	virtual void skyGetCurrentSignalPropety(skySignalStatus &frePropety);
	/*设置搜索相关参数*/
	virtual  bool skyDtvSetScanParam(skyScanParam scanparam);
	/*注册回调函数，返回具体的搜索数据*/
	virtual void skyRegisterScanData(skyScanDataCallBack callback, void* ptr);

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
#ifdef WIN32
	void thread_task();
#endif
	static skyScanDvbS* skyGetScanInstance(void);
private:
	/*获取当前搜索信号源*/
	skyScanSourceType skyGetScanSourceType();

private:
	static skyScanDvbS* pInstance;
	void*  ptr_tmp;
	skyScanParam scanparam_tmp;
	skyScanDataCallBack  data_callback;
	skyScanCallbackData scandata;	
#ifdef WIN32
	bool startenable;
	thread td_c;
	volatile bool destoryenable;	
#endif
};
/*xxxx具体平台相关*/

#endif