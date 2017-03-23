#ifndef  _SKY_SCANDVBT_H_
#define  _SKY_SCANDVBT_H_
#include "skyScanUiApi.h"
#include "skyScanType.h"
#include  <thread> 

using namespace std;

/*xxxx具体平台相关*/
class skyScanDvbT : public skyScanUi
{
public:

	skyScanDvbT();
	~skyScanDvbT();
	/*开始搜索*/
	virtual bool skyScanStart();
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
	virtual void skyRegisterScanData(skyScanDataCallBack callback, void* ptr);

	/*获取搜索参数*/
	//virtual  bool skyDtvGetCurrentScanParam(skyScanParam &scanparam);

	/*设置搜索参数*/
	virtual  bool skyDtvSetScanParam(skyScanParam scanparam);
#ifdef WIN32
	void thread_task();
#endif
	static skyScanDvbT* skyGetScanInstance(void);
	void *ptr_tmp;
	skyScanDataCallBack  data_callback;
private:
	/*获取当前搜索信号源*/
	skyScanSourceType skyGetScanSourceType();
	
private:
	static skyScanDvbT* pInstance;

	skyScanCallbackData scandata;
	skyScanParam scanparam_tmp;

#ifdef WIN32
	bool startenable;
	thread td_c;
	bool destoryenable;
#endif

};
/*xxxx具体平台相关*/

#endif