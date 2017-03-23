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
	/*��ʼ�Զ�����*/
	virtual bool skyScanStart();
	/*��ͣ����*/
	virtual bool skyScanPause();
	/*ֹͣ����*/
	virtual bool skyScanStop();
	/*�ָ�����*/
	virtual bool skyResumeScan();
	/*��ȡ��ǰ�ź�״̬*/
	virtual void skyGetCurrentSignalPropety(skySignalStatus &frePropety);

	/*ע��ص����������ؾ������������*/
	virtual void skyRegisterScanData(skyScanDataCallBack callback, void* ptr);
	/*atv ��ȡ*/
	virtual  bool skyDtvGetCurrentScanParam(skyScanParam &scanparam);

	/*���ù��˽�Ŀcolor*/
	virtual  bool skyDtvSetScanParam(skyScanParam scanparam);
	
		/*just for ATV��ʵʱ��Ч*/
	/*���õ�ǰsound*/
	virtual bool skyAtvSetCurSound(skyAudioSystemType aValue);
	/*���õ�ǰcolor ��ʵʱ��Ч*/
	virtual bool skyAtvSetCurColor(skyColorSystemType aValue);

	/*���õ�ǰfine*/
	virtual  bool skySetCurrentFineFreq(int fine);
	
#ifdef WIN32
	void thread_task();
#endif
	static skyScanAtv* skyGetScanInstance(void);

	void *ptr_tmp;
	skyScanDataCallBack  data_callback;
private:
	/*��ȡ��ǰ�����ź�Դ*/
	skyScanSourceType skyGetScanSourceType();

	/*��ȡ��ǰsound*/
	virtual skyAudioSystemType skyAtvGetCurSoundSystem(void);
	/*��ȡ��ǰcolor*/
	virtual skyColorSystemType skyAtvGetCurColorSystem(void);
	/*��ȡ��ǰfine*/
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