#ifndef _PVRRECORDDB_H_
#define _PVRRECORDDB_H_

#include <string>
#include <vector>

using namespace std;

#define USE_PVR_RECORD_DB


class PVRRecordDB;
class CppSQLite3DB;

enum {
	RECORD_STATE_FAILED,
	RECORD_STATE_COMPLETED
};



class PVRRecordInfo {    
public:
    string mRecordName;
    string mChannelName;
    string mEventName;
    string mMouth;
    string mDay;
    string mStartHour;
    string mStartMinute;
    string mEndHour;
    string mEndMinute;
    int     mState; /*recording / complete/ error*/
};

class PVRRecordDB {
private:
    static PVRRecordDB* mRecordDB;
    PVRRecordDB();
    ~PVRRecordDB();	

public:
    static PVRRecordDB* getInstance();    
    int getPvrRecords(vector<PVRRecordInfo>& list);
    int addPvrRecord(PVRRecordInfo& info);
    int updateRecordStatus(const char* recordname, int state);
    int deleteRecord(const char* recordname);
private:
    CppSQLite3DB* m_pSQLiteDB;
};


#endif

