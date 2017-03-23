#ifndef  _SKY_SCANATV_H_
#define  _SKY_SCANATV_H_
#include "skyScanUiApi.h"
#include "skyScanType.h"
#include  <thread> 

using namespace std;
class skyScanAtv : public skyScanUi
{
public:
	skyScanAtv();
	~skyScanAtv();
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

	/*注册回调函数，返回具体的搜索数据*/
	virtual void skyRegisterScanData(skyScanDataCallBack callback, void* ptr);
	/*atv 获取*/
	virtual  bool skyDtvGetCurrentScanParam(skyScanParam &scanparam);

	/*设置过滤节目color*/
	virtual  bool skyDtvSetScanParam(skyScanParam scanparam);
	
		/*just for ATV，实时生效*/
	/*设置当前sound*/
	virtual bool skyAtvSetCurSound(skyAudioSystemType aValue);
	/*设置当前color ，实时生效*/
	virtual bool skyAtvSetCurColor(skyColorSystemType aValue);

	/*设置当前fine*/
	virtual  bool skySetCurrentFineFreq(int fine);
	
#ifdef WIN32
	void thread_task();
#endif
	static skyScanAtv* skyGetScanInstance(void);

	void *ptr_tmp;
	skyScanDataCallBack  data_callback;
private:
	/*获取当前搜索信号源*/
	skyScanSourceType skyGetScanSourceType();

	/*获取当前sound*/
	virtual skyAudioSystemType skyAtvGetCurSoundSystem(void);
	/*获取当前color*/
	virtual skyColorSystemType skyAtvGetCurColorSystem(void);
	/*获取当前fine*/
	virtual unsigned int skyGetCurrentFineFreq();

	virtual int getCurrentProgrameIndex();
private:
	static skyScanAtv* pInstance;

	skyScanCallbackData scandata;
	skyScanParam scanparam_tmp;
#ifdef WIN32
	bool startenable;
	thread td_c;
	bool destoryenable;
	
#endif
};


#endif