#ifndef  _SKY_SCANDVBS_H_
#define  _SKY_SCANDVBS_H_
#include "skyScanUiApi.h"
#include "skyScanType.h"
#include  <thread> 

using namespace std;

/*xxxx����ƽ̨���*/
class skyScanDvbS : public skyScanUi
{
public:
	
	skyScanDvbS();
	~skyScanDvbS();
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
	/*����������ز���*/
	virtual  bool skyDtvSetScanParam(skyScanParam scanparam);
	/*ע��ص����������ؾ������������*/
	virtual void skyRegisterScanData(skyScanDataCallBack callback, void* ptr);

	/*��ȡ�������ǲ���*/
	virtual  bool skyDtvGetSatellitesinfo(vector<skySatellite_Info> &vec);
	/*��ȡָ����������tp����*/
	virtual bool  skyDtvGetTranspondersInfo(const int satelliteNumber, vector<skyTransponder_Info> &info);
	/*����ָ������ ��Ϣ*/
	virtual bool skyDtvUpdateSatelliteInfo(const int satelliteNumber, skySatellite_Info &info,int diseqc_type);
	/*����ָ������ָ��tp ��Ϣ*/
	virtual bool skyDtvUpdateTransponderInfo(const int satelliteNumber, const int transponderNumber, skyTransponder_Info &info);

	/*�������*/
	virtual bool skyDtvAddSatellite(skySatellite_Info &info);
	/*ɾ������*/
	virtual  bool skyDtvDeletSatellite(unsigned int satelliteNumber);

	/*���ָ������tp*/
	virtual bool skyDtvAddTransponderInfo(const int satelliteNumber, skyTransponder_Info &info);
	/*ɾ��ָ������tp*/
	virtual bool skyDtvDeleteTransponderInfo(int satelliteNumber, int transponderNumber);
#ifdef WIN32
	void thread_task();
#endif
	static skyScanDvbS* skyGetScanInstance(void);
private:
	/*��ȡ��ǰ�����ź�Դ*/
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
/*xxxx����ƽ̨���*/

#endif