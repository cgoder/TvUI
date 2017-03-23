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
	/*��ʼ����*/
	virtual bool skyScanStart();
	/*��ʼƵ�η�ʽ�����������Ƶ������ endFreΪ0*/
	//virtual bool skyScanWithRangeStart(skyFreqData startFre, skyFreqData endFre);

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
	virtual void skyRegisterScanData(skyScanDataCallBack callback, void*  ptr);
	/*����Ƶ�����,PersistentNitCableInfo ��ʱ���� 0*/
	/*just for ATV*/
	/*���õ�ǰ��Ŀsound��ʵʱ��Ч*/
	virtual bool skyAtvSetCurSound(skyAudioSystemType aValue);
	/*���õ�ǰ��Ŀcolor��ʵʱ��Ч*/
	virtual bool skyAtvSetCurColor(skyColorSystemType aValue);
	/*����fine ֵ*/
	virtual  bool skySetCurrentFineFreq(int fine);
	
	/*just for DTV-S*/



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
	
	/*��ȡ��������*/
	virtual  bool skyDtvGetCurrentScanParam(skyScanParam &scanparam);

	/*������������*/
	virtual  bool skyDtvSetScanParam(skyScanParam scanparam);

	/*reserve*/

	static skyScanUi* skyGetScanInstance(skyScanSourceType sourcetype);
	static void  skyScanDestroyInstance();

private:
	static skyScanUi* pInstance;

};

#endif