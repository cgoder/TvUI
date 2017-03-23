#ifndef  _SKY_SCANDVBT_H_
#define  _SKY_SCANDVBT_H_
#include "skyScanUiApi.h"
#include "skyScanType.h"
#include  <thread> 

using namespace std;

/*xxxx����ƽ̨���*/
class skyScanDvbT : public skyScanUi
{
public:

	skyScanDvbT();
	~skyScanDvbT();
	/*��ʼ����*/
	virtual bool skyScanStart();
	/*��ͣ����*/
	virtual bool skyScanPause();
	/*ֹͣ����*/
	virtual bool skyScanStop();
	/*�ָ�����*/
	virtual bool skyResumeScan();
	/*��ȡϵͳԤ��Ƶ����Ϣ*/
	virtual void skyGetFreTable(vector<skyFreqData> &vec);
	/*��ȡ��ǰ�ź�״̬*/
	virtual void skyGetCurrentSignalPropety(skySignalStatus &frePropety);
	/*ע��ص����������ؾ������������*/
	virtual void skyRegisterScanData(skyScanDataCallBack callback, void* ptr);

	/*��ȡ��������*/
	//virtual  bool skyDtvGetCurrentScanParam(skyScanParam &scanparam);

	/*������������*/
	virtual  bool skyDtvSetScanParam(skyScanParam scanparam);
#ifdef WIN32
	void thread_task();
#endif
	static skyScanDvbT* skyGetScanInstance(void);
	void *ptr_tmp;
	skyScanDataCallBack  data_callback;
private:
	/*��ȡ��ǰ�����ź�Դ*/
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
/*xxxx����ƽ̨���*/

#endif