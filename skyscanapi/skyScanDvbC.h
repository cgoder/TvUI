#ifndef  _SKY_SCANDVBC_H_
#define  _SKY_SCANDVBC_H_
#include "skyScanUiApi.h"
#include "skyScanType.h"
#include  <thread> 

using namespace std;
/*xxxx����ƽ̨���*/
class skyScanDvbC : public skyScanUi
{
public:

	skyScanDvbC();
	~skyScanDvbC();
	/*��ʼ����*/
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
	/*��ȡ��������*/
	virtual  bool skyDtvGetCurrentScanParam(skyScanParam &scanparam);

	/*������������*/
	virtual  bool skyDtvSetScanParam(skyScanParam scanparam);


#ifdef WIN32
	void thread_task();
#endif
	static skyScanDvbC* skyGetScanInstance(void);
	skyScanDataCallBack  data_callback;
	void*ptr_tmp;
private :
	
	/*��ȡ��ǰ�����ź�Դ*/
	skyScanSourceType skyGetScanSourceType();	
private:
	static skyScanDvbC* pInstance;
	skyScanParam scanparam_tmp;
	skyScanCallbackData scandata;
#ifdef WIN32
	bool startenable;
	thread td_c;
	bool destoryenable;
#endif

};

#endif