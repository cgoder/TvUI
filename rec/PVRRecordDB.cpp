#include "PVRRecordDB.h"
#include "CppSQLite3.h"
#include <string.h>
#include <stdio.h>

#define PVRRECORD_DB "pvr_record.db"

PVRRecordDB* PVRRecordDB::mRecordDB = NULL;

static const char *base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int base64Decode(const char * base64, unsigned char * bindata)
{
	int i, j;
	unsigned char k;
	unsigned char temp[4];
	for ( i = 0, j = 0; base64[i] != '\0' ; i += 4 )
	{
		memset( temp, 0xFF, sizeof(temp) );
		for ( k = 0 ; k < 64 ; k ++ )
		{
			if ( base64char[k] == base64[i] )
				temp[0]= k;
		}
		for ( k = 0 ; k < 64 ; k ++ )
		{
			if ( base64char[k] == base64[i+1] )
				temp[1]= k;
		}
		for ( k = 0 ; k < 64 ; k ++ )
		{
			if ( base64char[k] == base64[i+2] )
				temp[2]= k;
		}
		for ( k = 0 ; k < 64 ; k ++ )
		{
			if ( base64char[k] == base64[i+3] )
				temp[3]= k;
		}

		bindata[j++] = ((unsigned char)(((unsigned char)(temp[0] << 2))&0xFC)) |
			((unsigned char)((unsigned char)(temp[1]>>4)&0x03));
		if ( base64[i+2] == '=' )
			break;

		bindata[j++] = ((unsigned char)(((unsigned char)(temp[1] << 4))&0xF0)) |
			((unsigned char)((unsigned char)(temp[2]>>2)&0x0F));
		if ( base64[i+3] == '=' )
			break;

		bindata[j++] = ((unsigned char)(((unsigned char)(temp[2] << 6))&0xF0)) |
			((unsigned char)(temp[3]&0x3F));
	}
	return j;
}

char * base64Encode( const unsigned char * bindata, char * base64, int binlength )
{
	int i, j;
	unsigned char current;

	for ( i = 0, j = 0 ; i < binlength ; i += 3 )
	{
		current = (bindata[i] >> 2) ;
		current &= (unsigned char)0x3F;
		base64[j++] = base64char[(int)current];

		current = ( (unsigned char)(bindata[i] << 4 ) ) & ( (unsigned char)0x30 ) ;
		if ( i + 1 >= binlength )
		{
			base64[j++] = base64char[(int)current];
			base64[j++] = '=';
			base64[j++] = '=';
			break;
		}
		current |= ( (unsigned char)(bindata[i+1] >> 4) ) & ( (unsigned char) 0x0F );
		base64[j++] = base64char[(int)current];

		current = ( (unsigned char)(bindata[i+1] << 2) ) & ( (unsigned char)0x3C ) ;
		if ( i + 2 >= binlength )
		{
			base64[j++] = base64char[(int)current];
			base64[j++] = '=';
			break;
		}
		current |= ( (unsigned char)(bindata[i+2] >> 6) ) & ( (unsigned char) 0x03 );
		base64[j++] = base64char[(int)current];

		current = ( (unsigned char)bindata[i+2] ) & ( (unsigned char)0x3F ) ;
		base64[j++] = base64char[(int)current];
	}
	base64[j] = '\0';
	return base64;
}

PVRRecordDB* PVRRecordDB::getInstance()
{
    if (mRecordDB == NULL) {
        mRecordDB = new PVRRecordDB();    
    }
    return mRecordDB;
}

PVRRecordDB::PVRRecordDB()
{
    m_pSQLiteDB = new CppSQLite3DB();
    try
    {        
        m_pSQLiteDB->open(PVRRECORD_DB);
        
        m_pSQLiteDB->execDML("create table if not exists records(recordname varchar(255) primary key,channelname varchar(255),eventname varchar(255)," \
            "mouth char(64),day char(64),starthour char(64),startminute char(64),endhour char(64),endminute char(64),state int);");
    }    
    catch (CppSQLite3Exception& e)
    {
        printf("error: %s",e.errorMessage()); 
    }
}

PVRRecordDB::~PVRRecordDB()
{
    try
    {        
        m_pSQLiteDB->close();
    }    
    catch (CppSQLite3Exception& e)
    {
        printf("error: %s",e.errorMessage()); 
    }
    delete m_pSQLiteDB;
}

int PVRRecordDB::getPvrRecords(vector<PVRRecordInfo>& list)
{
    int ret = 0;
    try {
        PVRRecordInfo record;        
        CppSQLite3Query q = m_pSQLiteDB->execQuery("select * from records order by 1;");

        while (!q.eof()){
            char decode[4096];            

            const char* recordname = q.fieldValue(0);
            if (recordname) {
                memset(decode, 0x0, 4096);
                base64Decode(recordname, (unsigned char*)decode);
                record.mRecordName = string(decode);
            }

            const char* channelname = q.fieldValue(1);
            if (channelname) {
                memset(decode, 0x0, 4096);
                base64Decode(channelname, (unsigned char*)decode);
                record.mChannelName = string(decode);
            }
            
            const char* eventname = q.fieldValue(2);
            if (eventname) {
                memset(decode, 0x0, 4096);
                base64Decode(eventname, (unsigned char*)decode);
                record.mEventName = string(decode);
            }
            record.mMouth = q.fieldValue(3);
            record.mDay = q.fieldValue(4);
            record.mStartHour = q.fieldValue(5);
            record.mStartMinute = q.fieldValue(6);
            record.mEndHour = q.fieldValue(7);
            record.mEndMinute= q.fieldValue(8);            
            record.mState = q.getIntField(9, -1);
            list.push_back(record);
            q.nextRow();
        }
    }
    catch (CppSQLite3Exception& e)
    {
        printf("error: %s",e.errorMessage()); 
        ret = -1;  
    }
    return ret;
}

int PVRRecordDB::addPvrRecord(PVRRecordInfo& info)
{
    int ret = 0;
    char* recordname = (char*)malloc(4096);
    if (!recordname) {
        return -1;
    }
    base64Encode((unsigned char*)info.mRecordName.c_str(), recordname, strlen(info.mRecordName.c_str()));

    char* channelname = (char*) malloc(4096);
    if (!channelname) {
        free(recordname);
        return -1;
    }
    base64Encode((unsigned char*)info.mChannelName.c_str(), channelname, strlen(info.mChannelName.c_str()));

    char* eventname = (char*) malloc(4096);
    if (!eventname) {
        free(channelname);
        free(recordname);
        return -1;
    }
    base64Encode((unsigned char*)info.mEventName.c_str(), eventname, strlen(info.mEventName.c_str()));
        
    try {
        char sql[4096];
        sprintf(sql,"insert into records values ('%s','%s','%s','%s','%s','%s','%s','%s','%s',%d);",
                    recordname, channelname, eventname, info.mMouth.c_str(),info.mDay.c_str(),
                    info.mStartHour.c_str(),info.mStartMinute.c_str(),info.mEndHour.c_str(),info.mEndMinute.c_str(),info.mState);        
        m_pSQLiteDB->execDML(sql);
    }
    catch (CppSQLite3Exception& e)
    {
        printf("error: %s",e.errorMessage()); 
        ret = -1;  
    }
    
    free(recordname);
    free(channelname);
    free(eventname);
    return ret;
}

int PVRRecordDB::updateRecordStatus(const char* record, int state)
{
    int ret = 0;
    char* recordname = (char*)malloc(4096);
    if (!recordname) {
        return -1;
    }
    base64Encode((unsigned char*)record, recordname, strlen(record));
    
    try {
        char sql[4096];
        sprintf(sql,"update records set state=%d where recordname='%s'",state,recordname); 
        
        m_pSQLiteDB->execDML(sql);
    }
    catch (CppSQLite3Exception& e)
    {
        printf("error: %s",e.errorMessage()); 
        ret = -1;  
    }

    free(recordname);
    return ret;
}

int PVRRecordDB::deleteRecord(const char* record)
{
    int ret = 0;
    char* recordname = (char*)malloc(4096);
    if (!recordname) {
        return -1;
    }
    base64Encode((unsigned char*)record, recordname, strlen(record));

    try {
        char sql[4096];
        sprintf(sql,"delete from records where recordname='%s'",recordname); 
        
        m_pSQLiteDB->execDML(sql);
    }
    catch (CppSQLite3Exception& e)
    {
        printf("error: %s",e.errorMessage()); 
        ret = -1;  
    }

    free(recordname);
    return ret;
}

