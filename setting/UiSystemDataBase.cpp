/****************************************************************************
 * Notice:      Copyright (c) Skyworth.
 *              All rights reserved.
 * Owner:      miaolibin@skyworth.com
 ****************************************************************************/
#include <iostream>
#include <cstdio>
#ifdef WIN32
#include <Windows.h>
#include <stdio.h>
#else
#include <unistd.h>
#endif
#include <string.h>
#include <cstdlib>

#include "DatabaseManagerType.h"
#include "mapi_types.h"
#include "mapi_video_datatype.h"
#include "UiSystemDataBase.h"
//#include "UIATVDataTypes.h"

#ifdef WIN32
#define snprintf _snprintf
#define usleep(x) Sleep(x/1000)
#endif

using namespace std;

UI_System_Database* UI_System_Database::m_UipInstance = NULL;


UI_System_Database* UI_System_Database::GetUiSystemDbInstance(void)
{
    if(m_UipInstance == NULL)
    {
        m_UipInstance = new (std::nothrow) UI_System_Database;
    }

    return m_UipInstance;
}

UI_System_Database::UI_System_Database(void)
{
    pUiSqldb = NULL;
    pUiSqlfactorydb = NULL;

    memset(&m_stUiSysSetting, 0, sizeof(MS_UI_UserSystemSetting));
    memset(&m_stUiSoundSetting, 0, sizeof(MS_UI_USER_SOUND_SETTING));
    memset(&m_stUiFactoryExt, 0, sizeof(MS_FACTORY_UI_EXTERN_SETTING));
    memset(&m_stUiMediumSetting, 0, sizeof(ST_TV_MEDIUM_SETTING));
    memset(&m_stUiCISet, 0, sizeof(ST_UI_FACTORY_CI_SETTING));
    memset(&m_stFactoryColorTempEx, 0, sizeof(T_MS_UI_COLOR_TEMPEX));
    m_pastUiVideo = new (std::nothrow) MS_UI_VIDEO[MAPI_INPUT_SOURCE_NUM];
    LoadFactoryColorTempEx();
    m_pastUiNLASet = new (std::nothrow) MS_UI_NLA_SETTING[MAPI_INPUT_SOURCE_NUM];
}

UI_System_Database::~UI_System_Database(void)
{
    SQL_UI_Connect uiSqlConn;

    if(NULL != pUiSqldb)
    {
        uiSqlConn.SQL_UI_Close(&pUiSqldb);
    }

    if(NULL != pUiSqlfactorydb)
    {
        uiSqlConn.SQL_UI_Close(&pUiSqlfactorydb);
    }
}

int UI_System_Database::SQL_UI_GetColumnIndex(sqlite3_stmt * stmt,const char *ColName)
{
     int Index = 0;
     int ColNum = sqlite3_column_count(stmt);

     for(Index = 0; Index < ColNum; Index ++)
     {
         if(strcmp(ColName, sqlite3_column_name(stmt, Index)) == 0)
         {
             break;
         }
     }

     if(Index >= ColNum)
     {
         Index = -1;
     }

     return Index;
}

unsigned int UI_System_Database::SQL_UI_GetU32(sqlite3_stmt *stmt, const char *Title)
{
    unsigned int  RetVal = 0;
    int ColIndex = SQL_UI_GetColumnIndex(stmt, (const char *)Title);

    if(ColIndex == -1)
    {
        MSG_SQL_UI_ERROR(printf("SQL_UI_GetU32 error!No such Column %s\n",Title));
        //ASSERT(0);
        return 0;
    }

    RetVal = sqlite3_column_int64(stmt, ColIndex);
    return RetVal;
}

int UI_System_Database::SQL_UI_Step(sqlite3_stmt * pstmt)
{
    unsigned char u8TimeOut = SQL_UI_AFRESHCNT;
    int rc = SQLITE_ERROR;

    do{
        rc = sqlite3_step(pstmt);
        if(rc == SQLITE_DONE)
        {
            MSG_SQL_UI_DBG(printf("\nSQL_UI_Step End\n"));
        }
        else if(rc == SQLITE_ROW)
        {
            MSG_SQL_UI_DBG(printf("\nSQL_UI_Step Row\n"));
        }
        else
        {
            MSG_SQL_UI_ERROR(printf("\n SQL_UI_Step Row error:%d\n",rc));
            usleep(SQL_UI_AFRESHSLP * 1000);
            u8TimeOut--;
            sqlite3_reset(pstmt);
            MSG_SQL_UI_ERROR(printf("\nSQL_UI_Step Retry cnt:%d\n",u8TimeOut));
        }
    } while (rc != SQLITE_DONE && rc != SQLITE_ROW && u8TimeOut);

    if(rc != SQLITE_DONE && rc != SQLITE_ROW)
    {
            printf("error!!![FUNC:%s,%d]\r\n",__FUNCTION__, __LINE__);
    }

    return rc;
}

const unsigned char* UI_System_Database::SQL_UI_GetText(sqlite3_stmt *stmt, const char *Title)
{
    int ColIndex = SQL_UI_GetColumnIndex(stmt, (const char *)Title);

    if(ColIndex == -1)
    {
        MSG_SQL_UI_ERROR(printf("SQL_GetText error!No such Column %s\n",Title));
        //ASSERT(0);
        return 0;
    }
    return (sqlite3_column_text(stmt, ColIndex));
}

MEMBER_LANGUAGE UI_System_Database::GetOsdLanguage()
{
    int ColNum = 0;

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stUiSysSetting---------------------
    {
        SQL_UI_LookupPre prepare(pUiSqldb, T_SystemSetting, ColNum, NULL);
        while(SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt))
        {
            m_stUiSysSetting.Language = (MEMBER_LANGUAGE)SQL_UI_GetU32(prepare.pSqlstmt,"Language");
        }
    }

    return (MEMBER_LANGUAGE)m_stUiSysSetting.Language;
}

void UI_System_Database::SetOsdLanguage(MEMBER_LANGUAGE *pValue)
{
    string strCondition = string("_id=0");
    MEMBER_LANGUAGE nlanguage = *(MEMBER_LANGUAGE *) pValue;

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stUiSysSetting---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
    if((pValue != NULL ) && (nlanguage != m_stUiSysSetting.Language))
    {
           m_stUiSysSetting.Language = nlanguage;
        SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "Language", strCondition.c_str(), m_stUiSysSetting.Language);
    }
    }
}

MEMBER_COUNTRY UI_System_Database::GetSystemCountry()
{
    int ColNum = 0;

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stUiSysSetting---------------------
    {
       SQL_UI_LookupPre prepare(pUiSqldb, T_SystemSetting, ColNum, NULL);
       while(SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt))
       {
           m_stUiSysSetting.Country = (MEMBER_COUNTRY)SQL_UI_GetU32(prepare.pSqlstmt,"Country");
        }
    }

    return (MEMBER_COUNTRY)m_stUiSysSetting.Country;
}

#if (STEREO_3D_ENABLE == 1)
void UI_System_Database::SetV3DAspectRatio(const int u8Value)
{
    string strCondition = string("_id=0");
    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stUiSysSetting---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
    if(u8Value != (int)m_stUiSysSetting.en3DARC)
    {
            m_stUiSysSetting.en3DARC = u8Value;
        SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "en3DARC", strCondition.c_str(), m_stUiSysSetting.en3DARC);
     }
     }
}
#endif
void UI_System_Database::SetSoundMode(const int u8Value)
{
    string strCondition = string("_id=0");
    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stUiSoundSetting---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
    if(u8Value !=  m_stUiSoundSetting.soundMode)
    {
         m_stUiSoundSetting.soundMode = (EN_UI_SOUND_MODE)u8Value;
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "SoundMode", strCondition.c_str(), m_stUiSoundSetting.soundMode);
     }
     }
}

void UI_System_Database::GetFactoryExtSetting_Power_Mode(unsigned char* u8PowerMode)
{
    int ColNum = 0;

    SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqlfactorydb);
    //-------------------m_stFactoryExt---------------------
    {
        SQL_UI_LookupPre prepare(pUiSqlfactorydb, T_FactoryExtern, ColNum, NULL);
        while(SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt))
        {
            m_stUiFactoryExt.stPowerMode = (MS_UI_FACTORY_POWER_MODE)SQL_UI_GetU32(prepare.pSqlstmt, "stPowerMode");
         }
     }

    memcpy((unsigned char*)u8PowerMode, (unsigned char*)&(m_stUiFactoryExt.stPowerMode), sizeof(MS_UI_FACTORY_POWER_MODE));
}

void UI_System_Database::SetFactoryExtSetting_Power_Mode(unsigned char* u8PowerMode)
{
    string strCondition = string("_id=0");

    m_stUiFactoryExt.stPowerMode = (MS_UI_FACTORY_POWER_MODE)*u8PowerMode;

    SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqlfactorydb);
    SQL_UI_Transaction sql_trans(pUiSqlfactorydb);
    //-------------------m_stFactoryExt---------------------
    {
        SQL_UI_SetU32(pUiSqlfactorydb, T_FactoryExtern, "stPowerMode",strCondition.c_str(), m_stUiFactoryExt.stPowerMode);
    }
}

void UI_System_Database::GetVideoSetting(MS_UI_VIDEO *pValue, MAPI_INPUT_SOURCE_TYPE *pParam)
{
    MAPI_INPUT_SOURCE_TYPE enInputSrc = MAPI_INPUT_SOURCE_NUM;
    enInputSrc = *pParam;

    if(enInputSrc >= MAPI_INPUT_SOURCE_NUM)
    {
        return;
    }

    unsigned char u8Index = (unsigned char)enInputSrc;
    LoadUiVideoSetting(u8Index);
    memcpy((unsigned char*)pValue, (unsigned char*)&(m_pastUiVideo[u8Index]), sizeof(MS_UI_VIDEO));
}

void UI_System_Database::LoadUiVideoSetting(unsigned char u8Index)
{
    int ColNum = 0;
    int ColIndex = 0;
    int PicNumIdx = 0;
    int ColorTempNumIdx = 0;
    char con[16] = {0};


    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);

    //-------------------m_pastUiVideo---------------------
    {
        snprintf(con, 16, "InputSrcType=%d", u8Index);//change Inputsource index to InputSrcType
        SQL_UI_LookupPre prepare(pUiSqldb, T_VideoSetting, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt)) && (ColIndex < ColNum))
        {
            m_pastUiVideo[u8Index].picture = (EN_UI_PICTURE_MODE)SQL_UI_GetU32(prepare.pSqlstmt, "ePicture");
            m_pastUiVideo[u8Index].subColor.u8SubBrightness = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8SubBrightness");
            m_pastUiVideo[u8Index].subColor.u8SubContrast = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8SubContrast");
            m_pastUiVideo[u8Index].arcType = (EN_UI_VIDEO_AR_Type)SQL_UI_GetU32(prepare.pSqlstmt, "enARCType");
            m_pastUiVideo[u8Index].outputResolution = (EN_UI_DISPLAY_RES_TYPE)SQL_UI_GetU32(prepare.pSqlstmt, "fOutput_RES");
            m_pastUiVideo[u8Index].tvSystemSetting = (EN_UI_VIDEO_OUT_VE_SYS)SQL_UI_GetU32(prepare.pSqlstmt, "tvsys");
            m_pastUiVideo[u8Index].lastVideoStandardMode = (EN_UI_AVD_VideoStandardType)SQL_UI_GetU32(prepare.pSqlstmt, "LastVideoStandardMode");
            m_pastUiVideo[u8Index].lastAudioStandardMode = (EN_UI_AUDIOMODE_TYPE_)SQL_UI_GetU32(prepare.pSqlstmt, "LastAudioStandardMode");
            m_pastUiVideo[u8Index].dynamicContrast = (EN_UI_MS_Dynamic_Contrast)SQL_UI_GetU32(prepare.pSqlstmt, "eDynamic_Contrast");
            m_pastUiVideo[u8Index].filmMode = (EN_UI_MS_FILM)SQL_UI_GetU32(prepare.pSqlstmt, "eFilm");
            m_pastUiVideo[u8Index].tvFormat = (EN_UI_DISPLAY_TVFORMAT)SQL_UI_GetU32(prepare.pSqlstmt, "eTvFormat");

            m_pastUiVideo[u8Index].enGameModeARCType = (mapi_video_datatype::MAPI_VIDEO_ARC_Type)SQL_UI_GetU32(prepare.pSqlstmt, "enGameModeARCType");
            m_pastUiVideo[u8Index].enAutoModeARCType = (mapi_video_datatype::MAPI_VIDEO_ARC_Type)SQL_UI_GetU32(prepare.pSqlstmt, "enAutoModeARCType");
            m_pastUiVideo[u8Index].enPcModeARCType = (mapi_video_datatype::MAPI_VIDEO_ARC_Type)SQL_UI_GetU32(prepare.pSqlstmt, "enPcModeARCType");
            m_pastUiVideo[u8Index].bIsPcMode = (bool) SQL_UI_GetU32(prepare.pSqlstmt, "bIsPcMode");
        }
    }

    //-------------------m_pastVideo.astPicture---------------------
    {
        snprintf(con, 16, "InputSrcType=%d", u8Index);//change Inputsource index to InputSrcType
        SQL_UI_LookupPre prepare(pUiSqldb, T_PicMode_Setting, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        PicNumIdx = 0;
        while((SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt)) && (ColIndex < ColNum) && (PicNumIdx < PICTURE_NUMS))
        {
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].backlight = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8Backlight");
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].contrast = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8Contrast");
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].brightness = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8Brightness");
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].saturation = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8Saturation");
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].sharpness = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8Sharpness");
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].hue = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8Hue");
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].colorTemp = (EN_UI_COLOR_TEMP)SQL_UI_GetU32(prepare.pSqlstmt, "eColorTemp");
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].vibrantColour = (EN_UI_MS_PIC_ADV)SQL_UI_GetU32(prepare.pSqlstmt, "eVibrantColour");
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].perfectClear = (EN_UI_MS_PIC_ADV)SQL_UI_GetU32(prepare.pSqlstmt, "ePerfectClear");
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].dynamicContrast = (EN_UI_MS_PIC_ADV)SQL_UI_GetU32(prepare.pSqlstmt, "eDynamicContrast");
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].dynamicBacklight = (EN_UI_MS_PIC_ADV)SQL_UI_GetU32(prepare.pSqlstmt, "eDynamicBacklight");
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].eActiveBackLight = (EN_UI_MS_ACTIVE_BACKLIGHT)SQL_UI_GetU32(prepare.pSqlstmt, "eActiveBackLight");
            m_pastUiVideo[u8Index].astPicture[PicNumIdx].eAutoBrightnessSensor = (EN_UI_MS_AUTO_BRIGHTNESS)SQL_UI_GetU32(prepare.pSqlstmt, "eAutoBrightnessSensor");
            PicNumIdx++;
        }
    }

    //-------------------m_pastVideo.stUserOverScanMode---------------------
    {
        snprintf(con, 16, "InputSrcType=%d", u8Index);//change Inputsource index to InputSrcType
        SQL_UI_LookupPre prepare(pUiSqldb, T_UserOverScanMode, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt)) && (ColIndex < ColNum))
        {
            m_pastUiVideo[u8Index].userOverScanMode.OverScanHposition = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "OverScanHposition");
            m_pastUiVideo[u8Index].userOverScanMode.OverScanVposition = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "OverScanVposition");
            m_pastUiVideo[u8Index].userOverScanMode.OverScanHRatio = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "OverScanHRatio");
            m_pastUiVideo[u8Index].userOverScanMode.OverScanVRatio = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "OverScanVRatio");
        }
    }

    //-------------------m_pastVideo.eNRMode---------------------
    {
        snprintf(con, 16, "InputSrcType=%d", u8Index);//change Inputsource index to InputSrcType
        SQL_UI_LookupPre prepare(pUiSqldb, T_NRMode, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        ColorTempNumIdx = 0;
        while((SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt)) && (ColIndex<ColNum) && (ColorTempNumIdx < COLOR_TEMP_NUM))
        {
            m_pastUiVideo[u8Index].noiseReductionMode[ColorTempNumIdx].eNR= (EN_UI_MS_NR)SQL_UI_GetU32(prepare.pSqlstmt, "eNR");
            m_pastUiVideo[u8Index].noiseReductionMode[ColorTempNumIdx].eMPEG_NR= (EN_UI_MS_MPEG_NR)SQL_UI_GetU32(prepare.pSqlstmt, "eMPEG_NR");
            ColorTempNumIdx ++;
        }
    }
}

void UI_System_Database::SetVideoSetting(MS_UI_VIDEO *pValue, MAPI_INPUT_SOURCE_TYPE  *pParam)
{
    MAPI_INPUT_SOURCE_TYPE enInputSrc = MAPI_INPUT_SOURCE_NUM;
    enInputSrc = *pParam;
    if(enInputSrc >= MAPI_INPUT_SOURCE_NUM)
    {
        return;
    }

    unsigned char u8Index = (unsigned char)*pParam;
    memcpy((unsigned char*)&(m_pastUiVideo[u8Index]), (unsigned char*)pValue, sizeof(MS_UI_VIDEO));
    SaveUiVideoSetting(u8Index);
}

void UI_System_Database::SaveUiVideoSetting(unsigned char u8Index)
{
    char con[64]={0};

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    snprintf(con, 64, "InputSrcType=%d", u8Index);//change Inputsource index to InputSrcType
    SQL_UI_Transaction sql_trans(pUiSqldb);
    //-------------------m_pastUiVideo---------------------
    {
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "ePicture",con,m_pastUiVideo[u8Index].picture);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "u8SubBrightness",con,m_pastUiVideo[u8Index].subColor.u8SubBrightness);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "u8SubContrast",con,m_pastUiVideo[u8Index].subColor.u8SubContrast);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "enARCType",con,m_pastUiVideo[u8Index].arcType);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "fOutput_RES",con,m_pastUiVideo[u8Index].outputResolution);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "tvsys",con,m_pastUiVideo[u8Index].tvSystemSetting);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "LastVideoStandardMode",con,m_pastUiVideo[u8Index].lastVideoStandardMode);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "LastAudioStandardMode",con,m_pastUiVideo[u8Index].lastAudioStandardMode);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "eDynamic_Contrast",con,m_pastUiVideo[u8Index].dynamicContrast);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "eFilm",con,m_pastUiVideo[u8Index].filmMode);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "eTvFormat",con,m_pastUiVideo[u8Index].tvFormat);

      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "enGameModeARCType",con,m_pastUiVideo[u8Index].enGameModeARCType);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "enAutoModeARCType",con,m_pastUiVideo[u8Index].enAutoModeARCType);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "enPcModeARCType",con,m_pastUiVideo[u8Index].enPcModeARCType);
      SQL_UI_SetU32(pUiSqldb, T_VideoSetting, "bIsPcMode",con,m_pastUiVideo[u8Index].bIsPcMode);
    }
    //-------------------m_pastUiVideo.astPicture---------------------
    {
        for(int PicNumIdx = 0; PicNumIdx < PICTURE_NUMS; PicNumIdx++)
        {
            snprintf(con, 64, "InputSrcType=%d and PictureModeType=%d", u8Index, PicNumIdx);//change Inputsource index to InputSrcType
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "u8Backlight",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].backlight);
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "u8Contrast",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].contrast);
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "u8Brightness",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].brightness);
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "u8Saturation",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].saturation);
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "u8Sharpness",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].sharpness);
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "u8Hue",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].hue);
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "eColorTemp",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].colorTemp);
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "eVibrantColour",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].vibrantColour);
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "ePerfectClear",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].perfectClear);
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "eDynamicContrast",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].dynamicContrast);
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "eDynamicBacklight",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].dynamicBacklight);
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "eActiveBackLight",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].eActiveBackLight);
            SQL_UI_SetU32(pUiSqldb, T_PicMode_Setting, "eAutoBrightnessSensor",con,m_pastUiVideo[u8Index].astPicture[PicNumIdx].eAutoBrightnessSensor);
        }
    }
    //-------------------m_pastUiVideo.stUserOverScanMode---------------------
    snprintf(con, 64, "InputSrcType=%d", u8Index);
    {
        SQL_UI_SetU32(pUiSqldb, T_UserOverScanMode, "OverScanHposition",con,m_pastUiVideo[u8Index].userOverScanMode.OverScanHposition);
        SQL_UI_SetU32(pUiSqldb, T_UserOverScanMode, "OverScanVposition",con,m_pastUiVideo[u8Index].userOverScanMode.OverScanVposition);
        SQL_UI_SetU32(pUiSqldb, T_UserOverScanMode, "OverScanHRatio",con,m_pastUiVideo[u8Index].userOverScanMode.OverScanHRatio);
        SQL_UI_SetU32(pUiSqldb, T_UserOverScanMode, "OverScanVRatio",con,m_pastUiVideo[u8Index].userOverScanMode.OverScanVRatio);
    }

    //-------------------m_pastVideo.eNRMode---------------------
    {
        for(int ColorTempNumIdx=0; ColorTempNumIdx < COLOR_TEMP_NUM; ColorTempNumIdx++)
        {
            snprintf(con, 64, "InputSrcType=%d and NRMode=%d", u8Index, ColorTempNumIdx);//change Inputsource index to InputSrcType
            SQL_UI_SetU32(pUiSqldb, T_NRMode, "eNR",con,m_pastUiVideo[u8Index].noiseReductionMode[ColorTempNumIdx].eNR);
            SQL_UI_SetU32(pUiSqldb, T_NRMode, "eMPEG_NR",con,m_pastUiVideo[u8Index].noiseReductionMode[ColorTempNumIdx].eMPEG_NR);
        }
        
    }
    
}

UI_System_Database::SQL_UI_Connect::SQL_UI_Connect(void)
{
    if (m_ppdb != NULL)
    {
        SQL_UI_Close(m_ppdb);
    }

    m_ppdb = NULL;
}

UI_System_Database::SQL_UI_Connect::SQL_UI_Connect(const char *dbpath, sqlite3 **ppdb)
{
    m_ppdb = NULL;

    // open
    if ((dbpath != NULL) && (ppdb != NULL))
    {
        m_ppdb = ppdb;
        SQL_UI_Open(dbpath, m_ppdb);
    }
}

UI_System_Database::SQL_UI_Connect::~SQL_UI_Connect(void)
{
    if(m_ppdb != NULL)
    {
        SQL_UI_Close(m_ppdb);
    }
}

int UI_System_Database::SQL_UI_Connect::SQL_UI_Open(const char *dbpath, sqlite3** ppdb)
{
    int rc = 0, rc2 = 0;
    char *zErrMsg = NULL;
    unsigned char u8ReTryCnt = 0;

    rc = sqlite3_open_v2(dbpath, ppdb, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE|SQLITE_OPEN_FULLMUTEX|SQLITE_OPEN_SHAREDCACHE, NULL);
    rc2 = sqlite3_exec(*ppdb, "PRAGMA journal_mode = TRUNCATE;", NULL, NULL, &zErrMsg);

    while(u8ReTryCnt < SQL_UI_AFRESHCNT && rc2 != SQLITE_OK)
    {
        printf("Retry...,sqlite3_exec PRAGMA journal_mode = TRUNCATE error:%s\n", zErrMsg);
        rc2 = sqlite3_exec(*ppdb, "PRAGMA journal_mode = TRUNCATE;", NULL, NULL, &zErrMsg);
        u8ReTryCnt ++;
        usleep(SQL_UI_AFRESHSLP * 1000);
    }

    if((rc != SQLITE_OK) || (rc2 != SQLITE_OK))
    {
        if(rc != SQLITE_OK)
        {
            printf("Can't open database:%s\n", sqlite3_errmsg(*ppdb));
        }

        if(rc2 != SQLITE_OK)
        {
            printf("sqlite3_exec PRAGMA journal_mode = TRUNCATE error:%s\n", zErrMsg);
        }

        SQL_UI_Close(ppdb);
        //ASSERT(0);
    }

    return SQLITE_OK;
}

int UI_System_Database::SQL_UI_Connect::SQL_UI_Close(sqlite3** ppdb)
{
    int ret = sqlite3_close(*ppdb);
    if(ret != SQLITE_OK)
    {
        printf("Can't close database, error code:%d\n", ret);
    }

    *ppdb = NULL;

     return ret;
}

int UI_System_Database::SQL_UI_SetU32(sqlite3* db, const char *Table, const char * Title, const char * Condition, unsigned int Value)
{
    int rc = SQLITE_ERROR;
    unsigned char u8TimeOut = SQL_UI_AFRESHCNT;
    char *zErrMsg = NULL;
    char str_SQL[QUERY_UI_STRING_LENGTH] = {0};
    snprintf(str_SQL, QUERY_UI_STRING_LENGTH, "UPDATE %s SET %s=%d WHERE %s;", Table, Title, Value, Condition);

    do
    {
        rc = sqlite3_exec(db, str_SQL, NULL, 0, &zErrMsg);
        if( rc == SQLITE_OK)
        {
            break;
        }
        else
        {
            printf("SQL_SetU32 error:%s\n", zErrMsg);
            printf("str_SQL:%s\n", str_SQL);

            if( strstr(zErrMsg, "database is locked") )
            {
                usleep(SQL_UI_AFRESHSLP * 1000);
            }
            else if( strstr(zErrMsg, "unable to open") )
            {
                usleep(SQL_UI_AFRESHSLP * 1000);
            }

            u8TimeOut --;

            if(zErrMsg != NULL)
            {
                sqlite3_free(zErrMsg);
                zErrMsg = NULL;
            }
        }
    }while(u8TimeOut);

    if(zErrMsg != NULL)
    {
        sqlite3_free(zErrMsg);
    }

    if(u8TimeOut == 0)
    {
        sqlite3_exec(db, "IGNORE;", NULL, 0, NULL);
        return SQLITE_ERROR;
    }
    else
    {
       return SQLITE_OK;
    }
}

UI_System_Database::SQL_UI_Transaction::SQL_UI_Transaction(sqlite3 *db)
{
    unsigned char u8Redetect = 0;

    if(db == NULL)
        return;
    pdb = db;
    rc = sqlite3_exec(pdb,"BEGIN EXCLUSIVE TRANSACTION;",0,0,&zErrMsg);

    while(u8Redetect < SQL_UI_AFRESHCNT && rc != SQLITE_OK)
    {
        rc = sqlite3_exec(pdb,"BEGIN EXCLUSIVE TRANSACTION;",0,0,&zErrMsg);
        u8Redetect ++;
        usleep(SQL_UI_AFRESHSLP * 1000);
    }

    if( rc != SQLITE_OK)
    {
        printf("SQL Transaction error:%s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

UI_System_Database::SQL_UI_Transaction::~SQL_UI_Transaction(void)
{
    if(pdb == NULL)
    {
        return;
    }

    rc = sqlite3_exec(pdb,"COMMIT TRANSACTION;",0,0,&zErrMsg);

    if(rc != SQLITE_OK)
    {
        printf("SQL Transaction end error:%s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

UI_System_Database::SQL_UI_LookupPre::SQL_UI_LookupPre(sqlite3 *db, const char *table, int &ColNum, char *Condition)
{
    char sql[QUERY_UI_STRING_LENGTH];
    unsigned char u8Redetect = 0;

    if(Condition == NULL)
    {
        snprintf(sql, QUERY_UI_STRING_LENGTH, "select * from %s;", table);
    }
    else
    {
        snprintf(sql, QUERY_UI_STRING_LENGTH, "select * from %s where %s;", table, Condition);
    }

    sqlite3_prepare_v2(db, sql, strlen(sql), &pSqlstmt, NULL);
    ColNum = sqlite3_column_count(pSqlstmt);

    while(u8Redetect < SQL_UI_AFRESHCNT && ColNum == 0)
    {
        printf("select table error!! sleep and prepare again!!!\n");
        u8Redetect ++;
        usleep(SQL_UI_AFRESHSLP * 1000);
        sqlite3_prepare_v2(db, sql, strlen(sql), &pSqlstmt, NULL);
        ColNum = sqlite3_column_count(pSqlstmt);
    }

    if(ColNum == 0)
    {
        printf("select table error!!\n");
    }
}

UI_System_Database::SQL_UI_LookupPre::~SQL_UI_LookupPre(void)
{
    sqlite3_finalize(pSqlstmt);
}


void UI_System_Database::SetAudioSetting(MS_UI_USER_SOUND_SETTING *pstSoundSetting)
{
    LoadUiSoundSetting();
    MS_UI_USER_SOUND_SETTING stAudioSetting;
    memcpy(&stAudioSetting, &m_stUiSoundSetting, sizeof(MS_UI_USER_SOUND_SETTING));

    m_stUiSoundSetting.u16CheckSum = pstSoundSetting->u16CheckSum;
    m_stUiSoundSetting.soundMode= (EN_UI_SOUND_MODE)pstSoundSetting->soundMode;

    for (unsigned char i = 0; i < E_TVOS_SOUND_MODE_NUM; i++)
    {
        m_stUiSoundSetting.astSoundModeSetting[i].balance = pstSoundSetting->astSoundModeSetting[i].balance;
        m_stUiSoundSetting.astSoundModeSetting[i].bass = pstSoundSetting->astSoundModeSetting[i].bass;
        m_stUiSoundSetting.astSoundModeSetting[i].enSoundAudioChannel = (EN_UI_AUD_MODE)pstSoundSetting->astSoundModeSetting[i].enSoundAudioChannel;
        m_stUiSoundSetting.astSoundModeSetting[i].eqBand1 = pstSoundSetting->astSoundModeSetting[i].eqBand1;
        m_stUiSoundSetting.astSoundModeSetting[i].eqBand2 = pstSoundSetting->astSoundModeSetting[i].eqBand2;
        m_stUiSoundSetting.astSoundModeSetting[i].eqBand3 = pstSoundSetting->astSoundModeSetting[i].eqBand3;
        m_stUiSoundSetting.astSoundModeSetting[i].eqBand4 = pstSoundSetting->astSoundModeSetting[i].eqBand4;
        m_stUiSoundSetting.astSoundModeSetting[i].eqBand5 = pstSoundSetting->astSoundModeSetting[i].eqBand5;
        m_stUiSoundSetting.astSoundModeSetting[i].eqBand6 = pstSoundSetting->astSoundModeSetting[i].eqBand6;
        m_stUiSoundSetting.astSoundModeSetting[i].eqBand7 = pstSoundSetting->astSoundModeSetting[i].eqBand7;
        m_stUiSoundSetting.astSoundModeSetting[i].treble = pstSoundSetting->astSoundModeSetting[i].treble;
        m_stUiSoundSetting.astSoundModeSetting[i].userMode = pstSoundSetting->astSoundModeSetting[i].userMode;
    }

    m_stUiSoundSetting.audysseyDynamicVolume = (EN_UI_AUDYSSEY_DYNAMIC_VOLUME_MODE)pstSoundSetting->audysseyDynamicVolume;
    m_stUiSoundSetting.audysseyEq = (EN_UI_AUDYSSEY_EQ_MODE)pstSoundSetting->audysseyEq;
    m_stUiSoundSetting.surroundSoundMode = (EN_UI_SURROUND_MODE)pstSoundSetting->surroundSoundMode;
    m_stUiSoundSetting.surround = (EN_UI_SURROUND_TYPE)pstSoundSetting->surround;
    m_stUiSoundSetting.enableAVC = pstSoundSetting->enableAVC;
    m_stUiSoundSetting.volume = pstSoundSetting->volume;
    m_stUiSoundSetting.HPVolume = pstSoundSetting->HPVolume;
    m_stUiSoundSetting.balance = pstSoundSetting->balance;
    m_stUiSoundSetting.primaryFlag = pstSoundSetting->primaryFlag;
    m_stUiSoundSetting.soundAudioLanguage1 = (MEMBER_LANGUAGE)pstSoundSetting->soundAudioLanguage1;
    m_stUiSoundSetting.soundAudioLanguage2 = (MEMBER_LANGUAGE)pstSoundSetting->soundAudioLanguage2;
    m_stUiSoundSetting.muteFlag = pstSoundSetting->muteFlag;
    m_stUiSoundSetting.soundAudioChannel = (EN_UI_AUD_MODE)pstSoundSetting->soundAudioChannel;
    m_stUiSoundSetting.enableAd = pstSoundSetting->enableAd;
    m_stUiSoundSetting.adVolume = pstSoundSetting->adVolume;
    m_stUiSoundSetting.adOutput = (EN_UI_SOUND_AD_OUTPUT)pstSoundSetting->adOutput;
    m_stUiSoundSetting.enSPDIFMODE= (SPDIF_TYPE_)pstSoundSetting->enSPDIFMODE;
    m_stUiSoundSetting.spdifDelay = pstSoundSetting->spdifDelay;
    m_stUiSoundSetting.speakerdelay = pstSoundSetting->speakerdelay;
    m_stUiSoundSetting.enAudioType = (EN_AUDIO_TRACK_TYPE)pstSoundSetting->enAudioType;
    m_stUiSoundSetting.bEnableDRC = pstSoundSetting->bEnableDRC;
    m_stUiSoundSetting.AudioHdmiType = pstSoundSetting->AudioHdmiType;

    SaveUiSoundSetting(&stAudioSetting);
    //pDatabaseManager->setDatabaseDirtyByApplication(T_SoundSetting_IDX);
    return;
}

void UI_System_Database::SaveUiSoundSetting(MS_UI_USER_SOUND_SETTING *pOrgValue)
{
    string strCondition = string("_id=0");

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    SQL_UI_Transaction sql_trans(pUiSqldb);
    //-------------------m_stUiSoundSetting---------------------
    {
        if((pOrgValue == NULL ) || (pOrgValue->soundMode != m_stUiSoundSetting.soundMode))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "SoundMode",strCondition.c_str(),m_stUiSoundSetting.soundMode);
        }
        if((pOrgValue == NULL ) || (pOrgValue->audysseyDynamicVolume != m_stUiSoundSetting.audysseyDynamicVolume))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "AudysseyDynamicVolume",strCondition.c_str(),m_stUiSoundSetting.audysseyDynamicVolume);
        }
        if((pOrgValue == NULL ) || (pOrgValue->audysseyEq != m_stUiSoundSetting.audysseyEq))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "AudysseyEQ",strCondition.c_str(),m_stUiSoundSetting.audysseyEq);
        }
        if((pOrgValue == NULL ) || (pOrgValue->surroundSoundMode != m_stUiSoundSetting.surroundSoundMode))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "SurroundSoundMode",strCondition.c_str(),m_stUiSoundSetting.surroundSoundMode);
        }
        if((pOrgValue == NULL ) || (pOrgValue->surround != m_stUiSoundSetting.surround))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "Surround",strCondition.c_str(),m_stUiSoundSetting.surround);
        }
        if((pOrgValue == NULL ) || (pOrgValue->enableAVC != m_stUiSoundSetting.enableAVC))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "bEnableAVC",strCondition.c_str(),m_stUiSoundSetting.enableAVC);
        }
        if((pOrgValue == NULL ) || (pOrgValue->volume != m_stUiSoundSetting.volume))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "Volume",strCondition.c_str(),m_stUiSoundSetting.volume);
        }
        if((pOrgValue == NULL ) || (pOrgValue->HPVolume != m_stUiSoundSetting.HPVolume))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "HPVolume",strCondition.c_str(),m_stUiSoundSetting.HPVolume);
        }
        if((pOrgValue == NULL ) || (pOrgValue->balance != m_stUiSoundSetting.balance))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "Balance",strCondition.c_str(),m_stUiSoundSetting.balance);
        }
        if((pOrgValue == NULL ) || (pOrgValue->primaryFlag != m_stUiSoundSetting.primaryFlag))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "Primary_Flag",strCondition.c_str(),m_stUiSoundSetting.primaryFlag);
        }
        if((pOrgValue == NULL ) || (pOrgValue->soundAudioLanguage1 != m_stUiSoundSetting.soundAudioLanguage1))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "enSoundAudioLan1",strCondition.c_str(),m_stUiSoundSetting.soundAudioLanguage1);
        }
        if((pOrgValue == NULL ) || (pOrgValue->soundAudioLanguage2 != m_stUiSoundSetting.soundAudioLanguage2))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "enSoundAudioLan2",strCondition.c_str(),m_stUiSoundSetting.soundAudioLanguage2);
        }
        if((pOrgValue == NULL ) || (pOrgValue->muteFlag != m_stUiSoundSetting.muteFlag))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "MUTE_Flag",strCondition.c_str(),m_stUiSoundSetting.muteFlag);
        }
        if((pOrgValue == NULL ) || (pOrgValue->soundAudioChannel != m_stUiSoundSetting.soundAudioChannel))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "enSoundAudioChannel",strCondition.c_str(),m_stUiSoundSetting.soundAudioChannel);
        }
        if((pOrgValue == NULL ) || (pOrgValue->enableAd != m_stUiSoundSetting.enableAd))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "bEnableAD",strCondition.c_str(),m_stUiSoundSetting.enableAd);
        }
        if((pOrgValue == NULL ) || (pOrgValue->adVolume != m_stUiSoundSetting.adVolume))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "ADVolume",strCondition.c_str(),m_stUiSoundSetting.adVolume);
        }
        if((pOrgValue == NULL ) || (pOrgValue->adOutput != m_stUiSoundSetting.adOutput))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "ADOutput",strCondition.c_str(),m_stUiSoundSetting.adOutput);
        }
        if((pOrgValue == NULL ) || (pOrgValue->enSPDIFMODE != m_stUiSoundSetting.enSPDIFMODE))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "enSPDIFMODE",strCondition.c_str(),m_stUiSoundSetting.enSPDIFMODE);
        }
        if((pOrgValue == NULL ) || (pOrgValue->spdifDelay != m_stUiSoundSetting.spdifDelay))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "SPDIF_Delay",strCondition.c_str(),m_stUiSoundSetting.spdifDelay);
        }
        if((pOrgValue == NULL ) || (pOrgValue->speakerdelay != m_stUiSoundSetting.speakerdelay))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "Speaker_Delay",strCondition.c_str(),m_stUiSoundSetting.speakerdelay);
        }
        if((pOrgValue == NULL ) || (pOrgValue->AudioHdmiType != m_stUiSoundSetting.AudioHdmiType))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "AudioHdmiType",strCondition.c_str(),m_stUiSoundSetting.AudioHdmiType);
        }
        
        if((pOrgValue == NULL ) || (pOrgValue->SpeakerPreScale != m_stUiSoundSetting.SpeakerPreScale))
        {
            bool bRtn = false;
            bRtn = SQL_UI_SetArray(pUiSqldb,T_SoundSetting , "SpeakerPreScale",NULL, &m_stUiSoundSetting.SpeakerPreScale, (sizeof(m_stUiSoundSetting.SpeakerPreScale) / sizeof(m_stUiSoundSetting.SpeakerPreScale[0])), U8_UI_ARRAY_TYPE);
            if(bRtn == false)
                printf("ERROR Set T_SoundSetting SpeakerPreScale FAIL!!!");
        }
        if((pOrgValue == NULL ) || (pOrgValue->HeadPhonePreScale != m_stUiSoundSetting.HeadPhonePreScale))
        {
            bool bRtn = false;
            bRtn = SQL_UI_SetArray(pUiSqldb,T_SoundSetting , "HeadPhonePreScale",NULL, &m_stUiSoundSetting.HeadPhonePreScale, (sizeof(m_stUiSoundSetting.HeadPhonePreScale) / sizeof(m_stUiSoundSetting.HeadPhonePreScale[0])), U8_UI_ARRAY_TYPE);
            if(bRtn == false)
                printf("ERROR Set T_SoundSetting HeadPhonePreScale FAIL!!!");
        }

        if((pOrgValue == NULL ) || (pOrgValue->LineOutPreScale != m_stUiSoundSetting.LineOutPreScale))
        {
            bool bRtn = false;
            bRtn = SQL_UI_SetArray(pUiSqldb,T_SoundSetting ,"LineOutPreScale",NULL, &m_stUiSoundSetting.LineOutPreScale, (sizeof(m_stUiSoundSetting.LineOutPreScale) / sizeof(m_stUiSoundSetting.LineOutPreScale[0])), U8_UI_ARRAY_TYPE);
            if(bRtn == false)
                printf("ERROR Set T_SoundSetting LineOutPreScale FAIL!!!");

        }
        if((pOrgValue == NULL ) || (pOrgValue->SCART1PreScale != m_stUiSoundSetting.SCART1PreScale))
        {
            bool bRtn = false;
            bRtn = SQL_UI_SetArray(pUiSqldb,T_SoundSetting , "SCART1PreScale",NULL, &m_stUiSoundSetting.SCART1PreScale, (sizeof(m_stUiSoundSetting.SCART1PreScale) / sizeof(m_stUiSoundSetting.SCART1PreScale[0])), U8_UI_ARRAY_TYPE);
            if(bRtn == false)
                printf("ERROR Set T_SoundSetting SCART1PreScale FAIL!!!");

        }
        if((pOrgValue == NULL ) || (pOrgValue->SCART2PreScale != m_stUiSoundSetting.SCART2PreScale))
        {
            bool bRtn = false;
            bRtn = SQL_UI_SetArray(pUiSqldb,T_SoundSetting , "SCART2PreScale",NULL, &m_stUiSoundSetting.SCART2PreScale, (sizeof(m_stUiSoundSetting.SCART2PreScale) / sizeof(m_stUiSoundSetting.SCART2PreScale[0])), U8_UI_ARRAY_TYPE);
            if(bRtn == false)
                printf("ERROR Set T_SoundSetting SCART2PreScale FAIL!!!");

        }
        if((pOrgValue == NULL ) || (pOrgValue->bEnableDRC != m_stUiSoundSetting.bEnableDRC))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundSetting, "bEnableDRC",strCondition.c_str(),m_stUiSoundSetting.bEnableDRC);
        }

    }

    //-------------------m_stUiSoundSetting---------------------
    char con[16]={0};
    for(int RowIndex=0; RowIndex < SOUND_MODE_NUM; RowIndex++)
    {
        snprintf(con, 16, "_id=%d", RowIndex);
        if((pOrgValue == NULL ) || (pOrgValue->astSoundModeSetting[RowIndex].bass != m_stUiSoundSetting.astSoundModeSetting[RowIndex].bass))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundMode_Setting, "Bass", con, m_stUiSoundSetting.astSoundModeSetting[RowIndex].bass);
        }
        if((pOrgValue == NULL ) || (pOrgValue->astSoundModeSetting[RowIndex].treble != m_stUiSoundSetting.astSoundModeSetting[RowIndex].treble))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundMode_Setting, "Treble", con, m_stUiSoundSetting.astSoundModeSetting[RowIndex].treble);
        }
        if((pOrgValue == NULL ) || (pOrgValue->astSoundModeSetting[RowIndex].eqBand1 != m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand1))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundMode_Setting, "EqBand1", con, m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand1);
        }
        if((pOrgValue == NULL ) || (pOrgValue->astSoundModeSetting[RowIndex].eqBand2 != m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand2))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundMode_Setting, "EqBand2", con, m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand2);
        }
        if((pOrgValue == NULL ) || (pOrgValue->astSoundModeSetting[RowIndex].eqBand3 != m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand3))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundMode_Setting, "EqBand3", con, m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand3);
        }
        if((pOrgValue == NULL ) || (pOrgValue->astSoundModeSetting[RowIndex].eqBand4 != m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand4))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundMode_Setting, "EqBand4", con, m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand4);
        }
        if((pOrgValue == NULL ) || (pOrgValue->astSoundModeSetting[RowIndex].eqBand5 != m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand5))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundMode_Setting, "EqBand5", con, m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand5);
        }
        if((pOrgValue == NULL ) || (pOrgValue->astSoundModeSetting[RowIndex].eqBand6 != m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand6))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundMode_Setting, "EqBand6", con, m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand6);
        }
        if((pOrgValue == NULL ) || (pOrgValue->astSoundModeSetting[RowIndex].eqBand7 != m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand7))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundMode_Setting, "EqBand7", con, m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand7);
        }
        if((pOrgValue == NULL ) || (pOrgValue->astSoundModeSetting[RowIndex].userMode != m_stUiSoundSetting.astSoundModeSetting[RowIndex].userMode))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundMode_Setting, "UserMode", con, m_stUiSoundSetting.astSoundModeSetting[RowIndex].userMode);
        }
        if((pOrgValue == NULL ) || (pOrgValue->astSoundModeSetting[RowIndex].balance != m_stUiSoundSetting.astSoundModeSetting[RowIndex].balance))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundMode_Setting, "Balance", con, m_stUiSoundSetting.astSoundModeSetting[RowIndex].balance);
        }
        if((pOrgValue == NULL ) || (pOrgValue->astSoundModeSetting[RowIndex].enSoundAudioChannel != m_stUiSoundSetting.astSoundModeSetting[RowIndex].enSoundAudioChannel))
        {
            SQL_UI_SetU32(pUiSqldb, T_SoundMode_Setting, "enSoundAudioChannel", con, m_stUiSoundSetting.astSoundModeSetting[RowIndex].enSoundAudioChannel);
        }
    }

    m_stUiSoundSetting.u16CheckSum = UiCalCheckSum((unsigned char *)&(m_stUiSoundSetting), sizeof(MS_UI_USER_SOUND_SETTING));
}

unsigned int UI_System_Database::UiCalCheckSum(unsigned char *pBuf, unsigned int u16BufLen)
{
    unsigned int u16CheckSum, u16Idx;

    u16CheckSum = 0;

    u16Idx = sizeof(u16CheckSum);   // skip checksum field
    while(u16Idx < u16BufLen)
    {
        u16CheckSum += pBuf[u16Idx];
        u16Idx++;
    }

    //ask to mstar
    return (u16CheckSum + 0x55);
}

bool UI_System_Database::SQL_UI_SetArray(sqlite3* db, const char *Table, const char * Title, const char * Condition, void * pArray, unsigned int u16Size, unsigned char ArrayType)
{
    int rc = SQLITE_ERROR;
    unsigned char u8TimeOut = SQL_UI_AFRESHCNT;
    char *zErrMsg=NULL;
    char str_SQL[QUERY_UI_STRING_LENGTH*2]={0};
    char str_Val[64]={0};
    char str_Tail[QUERY_UI_STRING_LENGTH]={0};

    if(pArray == NULL)
        return false;

    snprintf(str_SQL, QUERY_UI_STRING_LENGTH*2, "UPDATE %s SET %s=\"", Table, Title);
    snprintf(str_Tail, QUERY_UI_STRING_LENGTH, "\" WHERE %s;", Condition);

    unsigned int index = 0;
    switch(ArrayType)
    {
        case U8_UI_ARRAY_TYPE:
        {
            unsigned char * pdata = (unsigned char *)pArray;
            do
            {
                snprintf(str_Val, 64, "0x%x,", *((unsigned char *)pdata));
                strcat(str_SQL, str_Val);
                pdata += 1;
                index ++;
            }while(( index < u16Size )&& (strlen(str_SQL) + strlen(str_Tail) < QUERY_UI_STRING_LENGTH*2));
        }
        break;
        case U16_UI_ARRAY_TYPE:
        {
            unsigned int * pdata = (unsigned int *)pArray;
            do
            {
                snprintf(str_Val, 64, "0x%x,", *((unsigned int *)pdata));
                strcat(str_SQL, str_Val);
                pdata += 1;
                index ++;
            }while(( index < u16Size )&& (strlen(str_SQL) + strlen(str_Tail) < QUERY_UI_STRING_LENGTH*2));
        }
        break;
        case U32_UI_ARRAY_TYPE:
        {
            unsigned long int * pdata = (unsigned long int *)pArray;
            do
            {
                snprintf(str_Val, 64, "0x%lx,", *((unsigned long int  *)pdata));
                strcat(str_SQL, str_Val);
                pdata += 1;
                index ++;
            }while(( index < u16Size )&& (strlen(str_SQL) + strlen(str_Tail) < QUERY_UI_STRING_LENGTH*2));
        }
        break;
        default:
        {
            MSG_SQL_UI_ERROR(printf("SQL_UI_SetArray error!Not supported type !\n"));
            //ASSERT(0);
            return false;
            break;
        }
    }

    if(strlen(str_SQL) < QUERY_UI_STRING_LENGTH*2)
    {
        str_SQL[strlen(str_SQL)] = '"';
    }
    else
    {
        MSG_SQL_UI_ERROR(printf("SQL_SetArray error! reach the end of array!\n"));
        //ASSERT(0);
    }

    MSG_SQL_UI_DBG(printf("%s\n",str_SQL));
    do
    {
        rc = sqlite3_exec(db, str_SQL, NULL, 0, &zErrMsg);
        if( rc == SQLITE_OK)
        {
            break;
        }
        else
        {
            MSG_SQL_UI_ERROR(printf("SQL_UI_SetText error:%s\n", zErrMsg));
            if( strstr(zErrMsg, "database is locked") )
            {
                usleep(SQL_UI_AFRESHSLP * 1000);
            }
            else if( strstr(zErrMsg, "unable to open") )
            {
                usleep(SQL_UI_AFRESHSLP * 1000);
            }
            u8TimeOut --;
        }
    }while(u8TimeOut);

    if(zErrMsg != NULL)
    {
        sqlite3_free(zErrMsg);
        zErrMsg = NULL;
    }

    if(u8TimeOut == 0)
    {
        sqlite3_exec(db, "IGNORE;", NULL, 0, NULL);
        return false;
    }
    else
    {
       return true;
    }
}

void UI_System_Database::GetAudioSetting(MS_UI_USER_SOUND_SETTING *pstSoundSetting)
{
    LoadUiSoundSetting();

    pstSoundSetting->u16CheckSum = m_stUiSoundSetting.u16CheckSum;
    pstSoundSetting->soundMode = m_stUiSoundSetting.soundMode;

    for (unsigned char i = 0; i < E_TVOS_SOUND_MODE_NUM; i++)
    {
        pstSoundSetting->astSoundModeSetting[i].balance = m_stUiSoundSetting.astSoundModeSetting[i].balance;
        pstSoundSetting->astSoundModeSetting[i].bass = m_stUiSoundSetting.astSoundModeSetting[i].bass;
        pstSoundSetting->astSoundModeSetting[i].enSoundAudioChannel = m_stUiSoundSetting.astSoundModeSetting[i].enSoundAudioChannel;
        pstSoundSetting->astSoundModeSetting[i].eqBand1 = m_stUiSoundSetting.astSoundModeSetting[i].eqBand1;
        pstSoundSetting->astSoundModeSetting[i].eqBand2 = m_stUiSoundSetting.astSoundModeSetting[i].eqBand2;
        pstSoundSetting->astSoundModeSetting[i].eqBand3 = m_stUiSoundSetting.astSoundModeSetting[i].eqBand3;
        pstSoundSetting->astSoundModeSetting[i].eqBand4 = m_stUiSoundSetting.astSoundModeSetting[i].eqBand4;
        pstSoundSetting->astSoundModeSetting[i].eqBand5 = m_stUiSoundSetting.astSoundModeSetting[i].eqBand5;
        pstSoundSetting->astSoundModeSetting[i].eqBand6 = m_stUiSoundSetting.astSoundModeSetting[i].eqBand6;
        pstSoundSetting->astSoundModeSetting[i].eqBand7 = m_stUiSoundSetting.astSoundModeSetting[i].eqBand7;
        pstSoundSetting->astSoundModeSetting[i].treble = m_stUiSoundSetting.astSoundModeSetting[i].treble;
        pstSoundSetting->astSoundModeSetting[i].userMode = m_stUiSoundSetting.astSoundModeSetting[i].userMode;
    }

    pstSoundSetting->audysseyDynamicVolume = m_stUiSoundSetting.audysseyDynamicVolume;
    pstSoundSetting->audysseyEq = m_stUiSoundSetting.audysseyEq;
    pstSoundSetting->surroundSoundMode = m_stUiSoundSetting.surroundSoundMode;
    pstSoundSetting->surround = m_stUiSoundSetting.surround;
    pstSoundSetting->enableAVC = m_stUiSoundSetting.enableAVC;
    pstSoundSetting->volume = m_stUiSoundSetting.volume;
    pstSoundSetting->HPVolume = m_stUiSoundSetting.HPVolume;
    pstSoundSetting->balance = m_stUiSoundSetting.balance;
    pstSoundSetting->primaryFlag = m_stUiSoundSetting.primaryFlag;
    pstSoundSetting->soundAudioLanguage1 = m_stUiSoundSetting.soundAudioLanguage1;
    pstSoundSetting->soundAudioLanguage1 = m_stUiSoundSetting.soundAudioLanguage1;
    pstSoundSetting->muteFlag = m_stUiSoundSetting.muteFlag;
    pstSoundSetting->soundAudioChannel = m_stUiSoundSetting.soundAudioChannel;
    pstSoundSetting->enableAd = m_stUiSoundSetting.enableAd;
    pstSoundSetting->adVolume = m_stUiSoundSetting.adVolume;
    pstSoundSetting->adOutput = m_stUiSoundSetting.adOutput;
    pstSoundSetting->enSPDIFMODE = m_stUiSoundSetting.enSPDIFMODE;
    pstSoundSetting->spdifDelay = m_stUiSoundSetting.spdifDelay;
    pstSoundSetting->speakerdelay = m_stUiSoundSetting.speakerdelay;
    pstSoundSetting->enAudioType = m_stUiSoundSetting.enAudioType;
    pstSoundSetting->bEnableDRC = m_stUiSoundSetting.bEnableDRC;
    pstSoundSetting->AudioHdmiType = m_stUiSoundSetting.AudioHdmiType;

   return ;
}

void UI_System_Database::LoadUiSoundSetting(void)
{
    int ColNum = 0;
    int ColIndex = 0;
    int RowIndex =0;

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stSoundSetting---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_SoundSetting, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            ColIndex = 1;
            m_stUiSoundSetting.soundMode = (EN_UI_SOUND_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"SoundMode");
            m_stUiSoundSetting.audysseyDynamicVolume = (EN_UI_AUDYSSEY_DYNAMIC_VOLUME_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"AudysseyDynamicVolume");
            m_stUiSoundSetting.audysseyEq = (EN_UI_AUDYSSEY_EQ_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"AudysseyEQ");
            m_stUiSoundSetting.surroundSoundMode = (EN_UI_SURROUND_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"SurroundSoundMode");
            m_stUiSoundSetting.surround = (EN_UI_SURROUND_TYPE)SQL_UI_GetU32(prepear.pSqlstmt,"Surround");
            m_stUiSoundSetting.enableAVC = (bool)SQL_UI_GetU32(prepear.pSqlstmt,"bEnableAVC");
            m_stUiSoundSetting.volume = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Volume");
            m_stUiSoundSetting.HPVolume = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"HPVolume");
            m_stUiSoundSetting.balance = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Balance");
            m_stUiSoundSetting.primaryFlag = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Primary_Flag");
            m_stUiSoundSetting.soundAudioLanguage1 = (MEMBER_LANGUAGE)SQL_UI_GetU32(prepear.pSqlstmt,"enSoundAudioLan1");
            m_stUiSoundSetting.soundAudioLanguage2 = (MEMBER_LANGUAGE)SQL_UI_GetU32(prepear.pSqlstmt,"enSoundAudioLan2");
            m_stUiSoundSetting.muteFlag = (bool)SQL_UI_GetU32(prepear.pSqlstmt,"MUTE_Flag");
            m_stUiSoundSetting.soundAudioChannel = (EN_UI_AUD_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"enSoundAudioChannel");
            m_stUiSoundSetting.enableAd = (bool)SQL_UI_GetU32(prepear.pSqlstmt,"bEnableAD");
            m_stUiSoundSetting.adVolume = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"ADVolume");
            m_stUiSoundSetting.adOutput = (EN_UI_SOUND_AD_OUTPUT)SQL_UI_GetU32(prepear.pSqlstmt,"ADOutput");
            m_stUiSoundSetting.enSPDIFMODE = (SPDIF_TYPE_)SQL_UI_GetU32(prepear.pSqlstmt,"enSPDIFMODE");           
            m_stUiSoundSetting.spdifDelay = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"SPDIF_Delay");
            m_stUiSoundSetting.speakerdelay = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Speaker_Delay");
            m_stUiSoundSetting.AudioHdmiType = (HDMI_TYPE_)SQL_UI_GetU32(prepear.pSqlstmt,"AudioHdmiType");

            bool bRtn = false;
        bRtn = SQL_UI_GetArray(prepear.pSqlstmt, "SpeakerPreScale", m_stUiSoundSetting.SpeakerPreScale, (sizeof(m_stUiSoundSetting.SpeakerPreScale) / sizeof(m_stUiSoundSetting.SpeakerPreScale[0])), U8_UI_ARRAY_TYPE);

        if(bRtn == false)
        {
          printf("ERROR Get T_SoundSetting SpeakerPreScale FAIL!!!");
        }
        bRtn = SQL_UI_GetArray(prepear.pSqlstmt, "HeadPhonePreScale", m_stUiSoundSetting.HeadPhonePreScale, (sizeof(m_stUiSoundSetting.HeadPhonePreScale) / sizeof(m_stUiSoundSetting.HeadPhonePreScale[0])), U8_UI_ARRAY_TYPE);
        if(bRtn == false)
        {
          printf("ERROR Get T_SoundSetting HeadPhonePreScale FAIL!!!");
        }
        bRtn = SQL_UI_GetArray(prepear.pSqlstmt, "LineOutPreScale", m_stUiSoundSetting.LineOutPreScale, (sizeof(m_stUiSoundSetting.LineOutPreScale) / sizeof(m_stUiSoundSetting.LineOutPreScale[0])), U8_UI_ARRAY_TYPE);
        if(bRtn == false)
        {
          printf("ERROR Get T_SoundSetting LineOutPreScale FAIL!!!");
        }
        bRtn = SQL_UI_GetArray(prepear.pSqlstmt, "SCART1PreScale", m_stUiSoundSetting.SCART1PreScale, (sizeof(m_stUiSoundSetting.SCART1PreScale) / sizeof(m_stUiSoundSetting.SCART1PreScale[0])), U8_UI_ARRAY_TYPE);
        if(bRtn == false)
        {
          printf("ERROR Get T_SoundSetting SCART1PreScale FAIL!!!");
        }
        bRtn = SQL_UI_GetArray(prepear.pSqlstmt, "SCART2PreScale", m_stUiSoundSetting.SCART2PreScale, (sizeof(m_stUiSoundSetting.SCART2PreScale) / sizeof(m_stUiSoundSetting.SCART2PreScale[0])), U8_UI_ARRAY_TYPE);
        if(bRtn == false)
        {
          printf("ERROR Get T_SoundSetting SCART2PreScale FAIL!!!");
        }
    }
    }
    //-------------------m_stUiSoundSetting.astSoundModeSetting[]---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_SoundMode_Setting, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        RowIndex = 0;
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            ColIndex = 1;
            m_stUiSoundSetting.astSoundModeSetting[RowIndex].bass = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Bass");
            m_stUiSoundSetting.astSoundModeSetting[RowIndex].treble = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Treble");
            m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand1 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand1");
            m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand2 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand2");
            m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand3 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand3");
            m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand4 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand4");
            m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand5 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand5");
            m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand6 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand6");
            m_stUiSoundSetting.astSoundModeSetting[RowIndex].eqBand7 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand7");
            m_stUiSoundSetting.astSoundModeSetting[RowIndex].userMode = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"UserMode");
            m_stUiSoundSetting.astSoundModeSetting[RowIndex].balance = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Balance");
            m_stUiSoundSetting.astSoundModeSetting[RowIndex].enSoundAudioChannel = (EN_UI_AUD_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"enSoundAudioChannel");
            RowIndex ++;
        }
        MSG_SQL_UI_DBG(printf("Row =%d\n",RowIndex));
    }
}

bool UI_System_Database::SQL_UI_GetArray(sqlite3_stmt * stmt, const char * Title, void * pArray, unsigned int u16Size, unsigned char ArrayType)
{
    char str_Text[QUERY_UI_STRING_LENGTH*2+1] = {0};
    int ColIndex = SQL_UI_GetColumnIndex(stmt, (const char *)Title);
    if(ColIndex == -1)
    {
        MSG_SQL_UI_ERROR(printf("SQL_UI_GetArray error!No such Column %s\n",Title));
        //ASSERT(0);
        return false;
    }

    if(pArray == NULL)
        return false;

    strncpy(str_Text, (char *)sqlite3_column_text(stmt, ColIndex), QUERY_UI_STRING_LENGTH*2);
    unsigned long int temp_value = 0;
    unsigned int temp_Idx = 0;
    unsigned int index = 0;
    switch(ArrayType)
    {
        case U8_UI_ARRAY_TYPE:
        {
            unsigned char* aU8Data = new unsigned char[u16Size];
            bool bHEX = false;
            if(aU8Data == NULL)
            {
                printf("ERROR!!!! [%s,%d]\r\n",__FILE__, __LINE__);
                break;
            }
            memset(aU8Data, 0, sizeof(aU8Data));
            for(index = 0; (index  < strlen(str_Text)) && (temp_Idx < u16Size); index ++)
            {
                if((str_Text[index]==',') ||(str_Text[index+1] == '\0'))
                {
                    aU8Data[temp_Idx] = (unsigned char)temp_value;
                    temp_value = 0;
                    temp_Idx ++;
                    bHEX = false;
                    continue;
                }
                else if(str_Text[index]=='0' && (str_Text[index+1]=='x' ||str_Text[index+1]=='X'))
                {
                    temp_value = 0;
                    index ++;
                    bHEX = true;
                    continue;
                }
                if(bHEX)
                {
                    if((str_Text[index] >= '0') && (str_Text[index] <= '9'))
                    {
                        temp_value = (temp_value << 4) + (str_Text[index] - '0' );
                    }
                    else if((str_Text[index]>='A') && (str_Text[index]<='F'))
                    {
                        temp_value = (temp_value << 4) + (str_Text[index] - 'A' + 10);
                    }
                    else if((str_Text[index]>='a') && (str_Text[index]<='f'))
                    {
                        temp_value = (temp_value << 4) + (str_Text[index] - 'a' + 10);
                    }
                    else
                        index = strlen(str_Text);
                }
                else
                {
                    temp_value = temp_value * 10 + (str_Text[index] - '0');
                }
            }
            memcpy((unsigned char *)pArray, aU8Data, sizeof(aU8Data));
            delete aU8Data;
        }
        break;
        case U16_UI_ARRAY_TYPE:
        {
            unsigned int *aU16Data = new unsigned int[u16Size];//[u16Size];
            bool bHEX = false;
            if(aU16Data == NULL)
            {
                printf("ERROR!!!! [%s,%d]\r\n",__FILE__, __LINE__);
                break;
            }
            memset(aU16Data, 0, sizeof(aU16Data));
            for(index = 0; (index< strlen(str_Text)) && (temp_Idx < u16Size); index ++)
            {
                if((str_Text[index]==',') ||(str_Text[index+1] == '\0'))
                {
                    aU16Data[temp_Idx] = (unsigned int)temp_value;
                    temp_value = 0;
                    temp_Idx ++;
                    bHEX = false;
                    continue;
                }
                else if(str_Text[index]=='0' && (str_Text[index+1]=='x' ||str_Text[index+1]=='X'))
                {
                    temp_value = 0;
                    index ++;
                    bHEX = true;
                    continue;
                }
                if(bHEX)
                {
                    if((str_Text[index] >= '0') && (str_Text[index] <= '9'))
                    {
                        temp_value = (temp_value << 4) + (str_Text[index] - '0' );
                    }
                    else if((str_Text[index]>='A') && (str_Text[index]<='F'))
                    {
                        temp_value = (temp_value << 4) + (str_Text[index] - 'A' + 10);
                    }
                    else if((str_Text[index]>='a') && (str_Text[index]<='f'))
                    {
                        temp_value = (temp_value << 4) + (str_Text[index] - 'a' + 10);
                    }
                    else
                        index = strlen(str_Text);
                }
                else
                {
                    temp_value = temp_value * 10 + (str_Text[index] - '0');
                }
            }
            memcpy((unsigned int *)pArray, aU16Data, sizeof(aU16Data));
            delete aU16Data;
        }
        break;
        case U32_UI_ARRAY_TYPE:
        {
            unsigned long int *aU32Data = new unsigned long int[u16Size];//[u16Size];
            bool bHEX = false;
            if(aU32Data == NULL)
            {
                printf("ERROR!!!! [%s,%d]\r\n",__FILE__, __LINE__);
                break;
            }            
            memset(aU32Data, 0, sizeof(aU32Data));
            for(index = 0; (index  < strlen(str_Text)) && (temp_Idx < u16Size); index ++)
            {
                if((str_Text[index]==',') ||(str_Text[index+1] == '\0'))
                {

                    aU32Data[temp_Idx] = (unsigned long int)temp_value;
                    temp_value = 0;
                    temp_Idx ++;
                    bHEX = false;
                    continue;
                }
                else if(str_Text[index]=='0' && (str_Text[index+1]=='x' ||str_Text[index+1]=='X'))
                {
                    temp_value = 0;
                    index ++;
                    bHEX = true;
                    continue;
                }
                if(bHEX)
                {
                    if((str_Text[index] >= '0') && (str_Text[index] <= '9'))
                    {
                        temp_value = (temp_value << 4) + (str_Text[index] - '0' );
                    }
                    else if((str_Text[index]>='A') && (str_Text[index]<='F'))
                    {
                        temp_value = (temp_value << 4) + (str_Text[index] - 'A' + 10);
                    }
                    else if((str_Text[index]>='a') && (str_Text[index]<='f'))
                    {
                        temp_value = (temp_value << 4) + (str_Text[index] - 'a' + 10);
                    }
                    else
                        index = strlen(str_Text);
                }
                else
                {
                    temp_value = temp_value * 10 + (str_Text[index] - '0');
                }
            }
            memcpy((unsigned long int *)pArray, aU32Data, sizeof(aU32Data));
            delete aU32Data;
        }
        break;
        default:
        {
            MSG_SQL_UI_ERROR(printf("SQL_UI_GetArray error!Not supported type !\n"));
            //ASSERT(0);
            return false;
            break;
        }
    }
    return true;
}

void UI_System_Database::GetUserSystemSetting(MS_UI_UserSystemSetting *pValue)
{
    LoadUiSysSetting();
    memcpy(pValue, &(m_stUiSysSetting), sizeof(MS_UI_UserSystemSetting));
}

void UI_System_Database::LoadUiSysSetting(void)
{
    int ColNum = 0;
    int ColIndex = 0;
    int RowIndex =0;

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stUiSysSetting---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_SystemSetting, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            ColIndex = 1;
            m_stUiSysSetting.fRunInstallationGuide = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"fRunInstallationGuide");
            m_stUiSysSetting.fNoChannel = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"fNoChannel");
            m_stUiSysSetting.bDisableSiAutoUpdate = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bDisableSiAutoUpdate");
            m_stUiSysSetting.enInputSourceType = (MAPI_INPUT_SOURCE_TYPE)SQL_UI_GetU32(prepear.pSqlstmt,"enInputSourceType");
            m_stUiSysSetting.Country = (MEMBER_COUNTRY)SQL_UI_GetU32(prepear.pSqlstmt,"Country");
            m_stUiSysSetting.enCableOperators = (EN_CABLE_OPERATORS)SQL_UI_GetU32(prepear.pSqlstmt,"enCableOperators");
            m_stUiSysSetting.enSatellitePlatform = (EN_SATELLITE_PLATFORM)SQL_UI_GetU32(prepear.pSqlstmt,"enSatellitePlatform");
            m_stUiSysSetting.u16NetworkId = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16NetworkId");
            m_stUiSysSetting.Language = (MEMBER_LANGUAGE)SQL_UI_GetU32(prepear.pSqlstmt,"Language");
        #if (STEREO_3D_ENABLE == 1)
            m_stUiSysSetting.en3DARC = (EN_UI_VIDEO_3D_ARC_Type)SQL_UI_GetU32(prepear.pSqlstmt,"en3DARC");
        #endif
            m_stUiSysSetting.fSoftwareUpdate = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"fSoftwareUpdate");
            m_stUiSysSetting.U8OADTime = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"U8OADTime");
            m_stUiSysSetting.fOADScanAfterWakeup = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"fOADScanAfterWakeup");
            m_stUiSysSetting.fAutoVolume = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"fAutoVolume");
            m_stUiSysSetting.fDcPowerOFFMode = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"fDcPowerOFFMode");
            m_stUiSysSetting.DtvRoute = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"DtvRoute");
            m_stUiSysSetting.ScartOutRGB = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"ScartOutRGB");
            m_stUiSysSetting.U8Transparency = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"U8Transparency");
            m_stUiSysSetting.u32MenuTimeOut = (unsigned long int)SQL_UI_GetU32(prepear.pSqlstmt,"u32MenuTimeOut");
            m_stUiSysSetting.AudioOnly = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"AudioOnly");
            m_stUiSysSetting.bEnableWDT = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bEnableWDT");
            m_stUiSysSetting.u8FavoriteRegion = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8FavoriteRegion");
            m_stUiSysSetting.u8Bandwidth = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8Bandwidth");
//m_stUiSysSetting.bEnableUHF7M = (bool)SQL_UI_GetU32(prepear.pSqlstmt,"bEnableUHF7M");
            m_stUiSysSetting.u8TimeShiftSizeType = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8TimeShiftSizeType");
            m_stUiSysSetting.fOadScan = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"fOadScan");
            m_stUiSysSetting.u8ColorRangeMode = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8ColorRangeMode");
            m_stUiSysSetting.u8HDMIAudioSource = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8HDMIAudioSource");
            m_stUiSysSetting.bEnableAlwaysTimeshift = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bEnableAlwaysTimeshift");
            m_stUiSysSetting.eSUPER = (EN_UI_MS_SUPER)SQL_UI_GetU32(prepear.pSqlstmt,"eSUPER");
            m_stUiSysSetting.bUartBus = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bUartBus");
        #if AUTOZOOM_ENABLE
            m_stUiSysSetting.m_AutoZoom = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"m_AutoZoom");
        #endif
        #if ENABLE_OVERSCAN_FOR_ALL_SOURCE
            m_stUiSysSetting.bOverScan = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bOverScan");
        #endif
        #if (ISDB_SYSTEM_ENABLE == 1)
            m_stUiSysSetting.m_u8BrazilVideoStandardType = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"m_u8BrazilVideoStandardType");
        #endif
            m_stUiSysSetting.m_u8SoftwareUpdateMode = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"m_u8SoftwareUpdateMode");
            m_stUiSysSetting.OSD_Active_Time = (unsigned long int)SQL_UI_GetU32(prepear.pSqlstmt,"OSD_Active_Time");
            m_stUiSysSetting.m_MessageBoxExist = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"m_MessageBoxExist");
        #if (FREEVIEW_AU_ENABLE == 1)
            m_stUiSysSetting.u16LastOADVersion = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16LastOADVersion");
        #endif
            m_stUiSysSetting.bEnableAutoChannelUpdate = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bEnableAutoChannelUpdate");
            m_stUiSysSetting.enLocalDimm = (EN_UI_LOCAL_DIMM_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"enLocalDimm");
            m_stUiSysSetting.bATVChSwitchFreeze = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bATVChSwitchFreeze");

        #if (OFL_DET == 1)
            m_stUiSysSetting.bSourceDetectEnable = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bSourceDetectEnable");
            m_stUiSysSetting.bAutoSourceSwitch = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bAutoSourceSwitch");
        #endif
            m_stUiSysSetting.u32MsrvTimerCounter = (unsigned long int)SQL_UI_GetU32(prepear.pSqlstmt,"u32MsrvTimerCounter");
            m_stUiSysSetting.bAutoMHLSwitch = (unsigned long int)SQL_UI_GetU32(prepear.pSqlstmt,"bAutoMHLSwitch");
        #if (FREEVIEW_AU_ENABLE == 1)
            m_stUiSysSetting.bViewerPrompt = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bViewerPrompt");
        #endif
        #if(CI_PLUS_ENABLE == 1)
            m_stUiSysSetting.u8OpMode = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8OpMode");
            m_stUiSysSetting.u32CicamIdentifier = (unsigned long int)SQL_UI_GetU32(prepear.pSqlstmt,"u32CicamIdentifier");
        #endif
        #if (XVYCC_ENABLE == 1)
            m_stUiSysSetting.bxvYCCOnOff = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bxvYCCOnOff");
        #endif
        #if (HBBTV_ENABLE == 1)
            m_stUiSysSetting.bEnableHbbtv = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bEnableHbbtv");
            m_stUiSysSetting.bEnableStoreCookies = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bEnableStoreCookies");
        #endif
        #if (WOL_ENABLE == 1)
            m_stUiSysSetting.bWOLEnable = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bWOLEnable");
        #endif
        #if (STR_ENABLE == 1)
            m_stUiSysSetting.u32StrPowerMode = (unsigned long int)SQL_UI_GetU32(prepear.pSqlstmt,"u32StrPowerMode");
        #endif

            m_stUiSysSetting.bEnableACR= (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bEnableACR");
            m_stUiSysSetting.bMonitorITC = (bool)SQL_UI_GetU32(prepear.pSqlstmt,"bMonitorITC");
            m_stUiSysSetting.bServiceListNeedRearrange = (bool)SQL_UI_GetU32(prepear.pSqlstmt, "bServiceListNeedRearrange");
        #if (ISDB_SYSTEM_ENABLE == 1)
            m_stUiSysSetting.u8MonitorDebugMode = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8MonitorDebugMode");
        #endif
        #if (CI_PLUS_ENABLE == 1)
            m_stUiSysSetting.bCiOccupiedTuner = (bool)SQL_UI_GetU32(prepear.pSqlstmt, "bCiOccupiedTuner");
            m_stUiSysSetting.u16CiPinCode = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "u16CiPinCode");
        #endif
        }
    }
    //-------------------m_stUiSysSetting.stSubtitleSetting---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_SubtitleSetting, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            ColIndex = 1;
            m_stUiSysSetting.stSubtitleSetting.SubtitleDefaultLanguage = (MEMBER_LANGUAGE)SQL_UI_GetU32(prepear.pSqlstmt,"SubtitleDefaultLanguage");
            m_stUiSysSetting.stSubtitleSetting.SubtitleDefaultLanguage_2 = (MEMBER_LANGUAGE)SQL_UI_GetU32(prepear.pSqlstmt,"SubtitleDefaultLanguage_2");
            m_stUiSysSetting.stSubtitleSetting.fHardOfHearing = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"fHardOfHearing");
            m_stUiSysSetting.stSubtitleSetting.fEnableSubTitle = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"fEnableSubTitle");
        }
    }
    //-------------------m_stUiSysSetting.stUserColorTemp---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_USER_COLORTEMP, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            ColIndex = 1;
            m_stUiSysSetting.stUserColorTemp.u8RedGain = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8RedGain");
            m_stUiSysSetting.stUserColorTemp.u8GreenGain = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8GreenGain");
            m_stUiSysSetting.stUserColorTemp.u8BlueGain = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8BlueGain");
            m_stUiSysSetting.stUserColorTemp.u8RedOffset = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8RedOffset");
            m_stUiSysSetting.stUserColorTemp.u8GreenOffset = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8GreenOffset");
            m_stUiSysSetting.stUserColorTemp.u8BlueOffset = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8BlueOffset");
        }
    }

    //-------------------m_stUiSysSetting.stUserColorTempEx[]---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_USER_COLORTEMP_EX, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        RowIndex = 0;
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum) && (RowIndex < MS_INPUT_SOURCE_TYPE_NUM))
        {
            ColIndex = 1;
            m_stUiSysSetting.stUserColorTempEx[RowIndex].u16RedGain = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16RedGain");
            m_stUiSysSetting.stUserColorTempEx[RowIndex].u16GreenGain = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16GreenGain");
            m_stUiSysSetting.stUserColorTempEx[RowIndex].u16BlueGain = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16BlueGain");
            m_stUiSysSetting.stUserColorTempEx[RowIndex].u16RedOffset = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16RedOffset");
            m_stUiSysSetting.stUserColorTempEx[RowIndex].u16GreenOffset = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16GreenOffset");
            m_stUiSysSetting.stUserColorTempEx[RowIndex].u16BlueOffset = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16BlueOffset");
            RowIndex++;
        }
        MSG_SQL_UI_DBG(printf("Row =%d\n",RowIndex));
    }

    //-------------------m_stUiSysSetting.st3DInfo---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_3DInfo, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            ColIndex = 1;
            m_stUiSysSetting.st3DInfo.bEnable3D = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"bEnable3D");
            m_stUiSysSetting.st3DInfo.enInput3DMode= (mapi_video_datatype::EN_3D_INPUT_TYPE)SQL_UI_GetU32(prepear.pSqlstmt,"enInput3DMode");
            m_stUiSysSetting.st3DInfo.enOutput3DMode = (mapi_video_datatype::EN_3D_OUTPUT_TYPE)SQL_UI_GetU32(prepear.pSqlstmt,"enOutput3DMode");
        }
    }
    //-------------------m_stSysSetting.stUserMMSetting---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_UserMMSetting, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            ColIndex = 1;
            m_stUiSysSetting.stUserMMSetting.u8SubtitleSpecific = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8SubtitleSpecific");
            m_stUiSysSetting.stUserMMSetting.u8SubtitleBGColor= (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8SubtitleBGColor");
            m_stUiSysSetting.stUserMMSetting.u8SubtitleFontColor = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8SubtitleFontColor");
            m_stUiSysSetting.stUserMMSetting.u8SlideShowTime = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8SlideShowTime");
            m_stUiSysSetting.stUserMMSetting.u8SlideShowMode= (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"u8SlideShowMode");
            m_stUiSysSetting.stUserMMSetting.fPreviewOn = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"fPreviewOn");
            m_stUiSysSetting.stUserMMSetting.fResumePlay= (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"fResumePlay");
        }
    }
    //-------------------m_stUiSysSetting.stUserLocationSetting---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_UserLocationSetting, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum))
        {
            ColIndex = 1;
            m_stUiSysSetting.stUserLocationSetting.u16LocationNo = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16LocationNo");
            m_stUiSysSetting.stUserLocationSetting.s16ManualLongitude= (int)SQL_UI_GetU32(prepear.pSqlstmt,"s16ManualLongitude");
            m_stUiSysSetting.stUserLocationSetting.s16ManualLatitude = (int)SQL_UI_GetU32(prepear.pSqlstmt,"s16ManualLatitude");
        }
    }

    //-------------------m_stUiSysSetting.MfcMode---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_MfcMode, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            ColIndex = 1;
            m_stUiSysSetting.MfcMode.eMFC = (EN_UI_MFC)SQL_UI_GetU32(prepear.pSqlstmt,"eMFC");
        }
    }

    //-------------------m_stUiSysSetting.FavTypeName---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_FavTypeName, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        RowIndex = 0;
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum) && (RowIndex < MAX_FAVLIST_NUM))
        {
            ColIndex = 1;
               strncpy((char *)&m_stUiSysSetting.FavTypeName[RowIndex][0], (const char *)SQL_UI_GetText(prepear.pSqlstmt,"TypeName"), MAX_FAVTYPE_NAME_SIZE);
            RowIndex ++;
        }
    }
    #if (STEREO_3D_ENABLE == 1)
    //-------------------m_stUiSysSetting.st3DSetting---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_3DSetting, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            ColIndex = 1;
            m_stUiSysSetting.st3DSetting.enDisplayMode = (EN_UI_DISPLAY_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"enDisplayMode");
            m_stUiSysSetting.st3DSetting.en3DFormat= (EN_UI_3D_DISPLAY_FORMAT)SQL_UI_GetU32(prepear.pSqlstmt,"en3DFormat");
            m_stUiSysSetting.st3DSetting.en2DFormat = (EN_UI_2D_DISPLAY_FORMAT)SQL_UI_GetU32(prepear.pSqlstmt,"en2DFormat");
            m_stUiSysSetting.st3DSetting.enAutoStart= (EN_UI_AUTO_START)SQL_UI_GetU32(prepear.pSqlstmt,"enAutoStart");
            m_stUiSysSetting.st3DSetting.en3DTimerPeriod = (EN_UI_3D_TIMER_PERIOD)SQL_UI_GetU32(prepear.pSqlstmt,"en3DTimerPeriod");
        }
    }
    #endif
    //-------------------m_stUiSysSetting rename inputSource---------------------
    {
        char con[16]={0};
        snprintf(con, 16, "_id=%d",MAPI_INPUT_SOURCE_ATV);
        SQL_UI_LookupPre  prepear(pUiSqldb, T_InputSource_Type, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum))
        {
            ColIndex = 1;
            strncpy((char *)&m_stUiSysSetting.InputSourceName_TV[0], (const char *)SQL_UI_GetText(prepear.pSqlstmt,"_Name"), INPUTSOURCE_NAME_MAX_SIZE);
        }
    }
    {
        char con[16]={0};
        snprintf(con, 16, "_id=%d",MAPI_INPUT_SOURCE_YPBPR);
        SQL_UI_LookupPre  prepear(pUiSqldb,T_InputSource_Type, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            ColIndex = 1;
            strncpy((char *)&m_stUiSysSetting.InputSourceName_Componant1[0], (const char *)SQL_UI_GetText(prepear.pSqlstmt,"_Name"), INPUTSOURCE_NAME_MAX_SIZE);
        }
    }
    {
        char con[16]={0};
        snprintf(con, 16, "_id=%d",MAPI_INPUT_SOURCE_VGA);
        SQL_UI_LookupPre  prepear(pUiSqldb, T_InputSource_Type, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum))
        {
            ColIndex = 1;
            strncpy((char *)&m_stUiSysSetting.InputSourceName_PC_RGB[0], (const char *)SQL_UI_GetText(prepear.pSqlstmt,"_Name"), INPUTSOURCE_NAME_MAX_SIZE);
        }
    }
    {
        char con[16]={0};
        snprintf(con, 16, "_id=%d",MAPI_INPUT_SOURCE_VGA2);
        SQL_UI_LookupPre  prepear(pUiSqldb, T_InputSource_Type, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum))
        {
            ColIndex = 1;
            strncpy((char *)&m_stUiSysSetting.InputSourceName_PC_RGB2[0], (const char *)SQL_UI_GetText(prepear.pSqlstmt,"_Name"), INPUTSOURCE_NAME_MAX_SIZE);
        }
    }
    {
        char con[16] = {0};
        snprintf(con, 16, "_id=%d",MAPI_INPUT_SOURCE_VGA3);
        SQL_UI_LookupPre  prepear(pUiSqldb, T_InputSource_Type, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum))
        {
            ColIndex = 1;
            strncpy((char *)&m_stUiSysSetting.InputSourceName_PC_RGB3[0], (const char *)SQL_UI_GetText(prepear.pSqlstmt,"_Name"), INPUTSOURCE_NAME_MAX_SIZE);
        }
    }
    {
        char con[16]={0};
        snprintf(con, 16, "_id=%d",MAPI_INPUT_SOURCE_HDMI);
        SQL_UI_LookupPre  prepear(pUiSqldb,T_InputSource_Type,ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum))
        {
            ColIndex = 1;
            strncpy((char *)&m_stUiSysSetting.InputSourceName_HDMI1[0], (const char *)SQL_UI_GetText(prepear.pSqlstmt,"_Name"), INPUTSOURCE_NAME_MAX_SIZE);
        }
    }
    {
        char con[16] = {0};
        snprintf(con, 16, "_id=%d",MAPI_INPUT_SOURCE_HDMI2);
        SQL_UI_LookupPre  prepear(pUiSqldb, T_InputSource_Type, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum))
        {
            ColIndex = 1;
            strncpy((char *)&m_stUiSysSetting.InputSourceName_HDMI2[0], (const char *)SQL_UI_GetText(prepear.pSqlstmt,"_Name"), INPUTSOURCE_NAME_MAX_SIZE);
        }
    }
    {
        char con[16]={0};
        snprintf(con, 16, "_id=%d",MAPI_INPUT_SOURCE_HDMI3);
        SQL_UI_LookupPre  prepear(pUiSqldb,T_InputSource_Type, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum))
        {
            ColIndex = 1;
            strncpy((char *)&m_stUiSysSetting.InputSourceName_HDMI3[0], (const char *)SQL_UI_GetText(prepear.pSqlstmt,"_Name"), INPUTSOURCE_NAME_MAX_SIZE);
        }
    }
    {
        char con[16]={0};
        snprintf(con, 16, "_id=%d",MAPI_INPUT_SOURCE_HDMI4);
        SQL_UI_LookupPre  prepear(pUiSqldb, T_InputSource_Type, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum))
        {
            ColIndex = 1;
            strncpy((char *)&m_stUiSysSetting.InputSourceName_HDMI4[0], (const char *)SQL_UI_GetText(prepear.pSqlstmt,"_Name"), INPUTSOURCE_NAME_MAX_SIZE);
        }
    }

    {
        char con[16] = {0};
        snprintf(con, 16, "_id=%d",MAPI_INPUT_SOURCE_CVBS);
        SQL_UI_LookupPre  prepear(pUiSqldb, T_InputSource_Type, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum))
        {
            ColIndex = 1;
            strncpy((char *)&m_stUiSysSetting.InputSourceName_AV1[0], (const char *)SQL_UI_GetText(prepear.pSqlstmt,"_Name"), INPUTSOURCE_NAME_MAX_SIZE);
        }
    }
}

void UI_System_Database::GetSubtitleSetting(UserSubtitleSetting* pUserSubtitleSetting)
{
    LoadUiSysSetting();

    pUserSubtitleSetting->SubtitleDefaultLanguage = m_stUiSysSetting.stSubtitleSetting.SubtitleDefaultLanguage;
    pUserSubtitleSetting->SubtitleDefaultLanguage_2 = m_stUiSysSetting.stSubtitleSetting.SubtitleDefaultLanguage_2;
    pUserSubtitleSetting->fHardOfHearing = m_stUiSysSetting.stSubtitleSetting.fHardOfHearing;
    pUserSubtitleSetting->fEnableSubTitle = m_stUiSysSetting.stSubtitleSetting.fEnableSubTitle;
    pUserSubtitleSetting->Reserved = m_stUiSysSetting.stSubtitleSetting.Reserved;

    return;
}

void UI_System_Database::SetSubtitleSetting(UserSubtitleSetting* pUserSubtitleSetting)
{
    string strCondition = string("_id=0");

    memcpy((unsigned char*)&m_stUiSysSetting.stSubtitleSetting, (unsigned char*)pUserSubtitleSetting, sizeof(UserSubtitleSetting));

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stUiSysSetting.stSubtitleSetting---------------------
    SQL_UI_Transaction sql_trans(pUiSqldb);
    {
        SQL_UI_SetU32(pUiSqldb, T_SubtitleSetting, "SubtitleDefaultLanguage",strCondition.c_str(),m_stUiSysSetting.stSubtitleSetting.SubtitleDefaultLanguage);
        SQL_UI_SetU32(pUiSqldb, T_SubtitleSetting, "SubtitleDefaultLanguage_2",strCondition.c_str(),m_stUiSysSetting.stSubtitleSetting.SubtitleDefaultLanguage_2);
        SQL_UI_SetU32(pUiSqldb, T_SubtitleSetting, "fHardOfHearing",strCondition.c_str(),m_stUiSysSetting.stSubtitleSetting.fHardOfHearing);
        SQL_UI_SetU32(pUiSqldb, T_SubtitleSetting, "fEnableSubTitle",strCondition.c_str(),m_stUiSysSetting.stSubtitleSetting.fEnableSubTitle);
    }
    //pDatabaseManager->setDatabaseDirtyByApplication(T_SubtitleSetting_IDX);

}
void UI_System_Database::SetUserSystemSetting(MS_UI_UserSystemSetting *pstUserSystemSetting)
{
    MS_UI_UserSystemSetting pOrgValue;
    LoadUiSysSetting();
    memcpy(&pOrgValue, &m_stUiSysSetting, sizeof(MS_UI_UserSystemSetting));
    memcpy(&m_stUiSysSetting, pstUserSystemSetting, sizeof(MS_UI_UserSystemSetting));
    SaveUiSysSetting(&pOrgValue);
}

void UI_System_Database::SaveUiSysSetting(MS_UI_UserSystemSetting *pOrgValue)
{
    string strCondition = string("_id=0");
    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);

    //-------------------m_stUiSysSetting---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
        if((pOrgValue == NULL ) || (pOrgValue->fRunInstallationGuide != m_stUiSysSetting.fRunInstallationGuide))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "fRunInstallationGuide",strCondition.c_str(),m_stUiSysSetting.fRunInstallationGuide);
        }
        if((pOrgValue == NULL ) || (pOrgValue->fNoChannel != m_stUiSysSetting.fNoChannel))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "fNoChannel",strCondition.c_str(),m_stUiSysSetting.fNoChannel);
        }
        if((pOrgValue == NULL ) || (pOrgValue->bDisableSiAutoUpdate != m_stUiSysSetting.bDisableSiAutoUpdate))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bDisableSiAutoUpdate",strCondition.c_str(),m_stUiSysSetting.bDisableSiAutoUpdate);
        }
        if((pOrgValue == NULL ) || (pOrgValue->enInputSourceType != m_stUiSysSetting.enInputSourceType))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "enInputSourceType",strCondition.c_str(),m_stUiSysSetting.enInputSourceType);
        }
        if((pOrgValue == NULL ) || (pOrgValue->Country != m_stUiSysSetting.Country))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "Country",strCondition.c_str(),m_stUiSysSetting.Country);
        }
        if((pOrgValue == NULL ) || (pOrgValue->enCableOperators != m_stUiSysSetting.enCableOperators))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "enCableOperators",strCondition.c_str(),m_stUiSysSetting.enCableOperators);
        }
        if((pOrgValue == NULL ) || (pOrgValue->enSatellitePlatform != m_stUiSysSetting.enSatellitePlatform))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "enSatellitePlatform",strCondition.c_str(),m_stUiSysSetting.enSatellitePlatform);
        }
        if((pOrgValue == NULL ) || (pOrgValue->u16NetworkId != m_stUiSysSetting.u16NetworkId))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u16NetworkId",strCondition.c_str(),m_stUiSysSetting.u16NetworkId);
        }
        if((pOrgValue == NULL ) || (pOrgValue->Language != m_stUiSysSetting.Language))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "Language",strCondition.c_str(),m_stUiSysSetting.Language);
        }
#if (STEREO_3D_ENABLE == 1)
        if((pOrgValue == NULL ) || (pOrgValue->en3DARC != m_stUiSysSetting.en3DARC))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "en3DARC",strCondition.c_str(),m_stUiSysSetting.en3DARC);
        }
#endif
        if((pOrgValue == NULL ) || (pOrgValue->fSoftwareUpdate != m_stUiSysSetting.fSoftwareUpdate))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "fSoftwareUpdate",strCondition.c_str(),m_stUiSysSetting.fSoftwareUpdate);
        }
        if((pOrgValue == NULL ) || (pOrgValue->U8OADTime != m_stUiSysSetting.U8OADTime))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "U8OADTime",strCondition.c_str(),m_stUiSysSetting.U8OADTime);
        }
        if((pOrgValue == NULL ) || (pOrgValue->fOADScanAfterWakeup != m_stUiSysSetting.fOADScanAfterWakeup))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "fOADScanAfterWakeup",strCondition.c_str(),m_stUiSysSetting.fOADScanAfterWakeup);
        }
        if((pOrgValue == NULL ) || (pOrgValue->fAutoVolume != m_stUiSysSetting.fAutoVolume))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "fAutoVolume",strCondition.c_str(),m_stUiSysSetting.fAutoVolume);
        }
        if((pOrgValue == NULL ) || (pOrgValue->fDcPowerOFFMode != m_stUiSysSetting.fDcPowerOFFMode))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "fDcPowerOFFMode",strCondition.c_str(),m_stUiSysSetting.fDcPowerOFFMode);
        }
        if((pOrgValue == NULL ) || (pOrgValue->DtvRoute != m_stUiSysSetting.DtvRoute))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "DtvRoute",strCondition.c_str(),m_stUiSysSetting.DtvRoute);
        }
        if((pOrgValue == NULL ) || (pOrgValue->ScartOutRGB != m_stUiSysSetting.ScartOutRGB))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "ScartOutRGB",strCondition.c_str(),m_stUiSysSetting.ScartOutRGB);
        }
        if((pOrgValue == NULL ) || (pOrgValue->U8Transparency != m_stUiSysSetting.U8Transparency))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "U8Transparency",strCondition.c_str(),m_stUiSysSetting.U8Transparency);
        }
        if((pOrgValue == NULL ) || (pOrgValue->u32MenuTimeOut != m_stUiSysSetting.u32MenuTimeOut))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u32MenuTimeOut",strCondition.c_str(),m_stUiSysSetting.u32MenuTimeOut);
        }
        if((pOrgValue == NULL ) || (pOrgValue->AudioOnly != m_stUiSysSetting.AudioOnly))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "AudioOnly",strCondition.c_str(),m_stUiSysSetting.AudioOnly);
        }
        if((pOrgValue == NULL ) || (pOrgValue->bEnableWDT != m_stUiSysSetting.bEnableWDT))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bEnableWDT",strCondition.c_str(),m_stUiSysSetting.bEnableWDT);
        }
        if((pOrgValue == NULL ) || (pOrgValue->u8FavoriteRegion != m_stUiSysSetting.u8FavoriteRegion))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u8FavoriteRegion",strCondition.c_str(),m_stUiSysSetting.u8FavoriteRegion);
        }
        if((pOrgValue == NULL ) || (pOrgValue->u8Bandwidth != m_stUiSysSetting.u8Bandwidth))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u8Bandwidth",strCondition.c_str(),m_stUiSysSetting.u8Bandwidth);
        }
       if((pOrgValue == NULL ) || (pOrgValue->bEnableUHF7M != m_stUiSysSetting.bEnableUHF7M))
        {
           SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bEnableUHF7M",strCondition.c_str(),m_stUiSysSetting.bEnableUHF7M);
        }
        if((pOrgValue == NULL ) || (pOrgValue->u8TimeShiftSizeType != m_stUiSysSetting.u8TimeShiftSizeType))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u8TimeShiftSizeType",strCondition.c_str(),m_stUiSysSetting.u8TimeShiftSizeType);
        }
        if((pOrgValue == NULL ) || (pOrgValue->fOadScan != m_stUiSysSetting.fOadScan))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "fOadScan",strCondition.c_str(),m_stUiSysSetting.fOadScan);
        }
        if((pOrgValue == NULL ) || (pOrgValue->u8ColorRangeMode != m_stUiSysSetting.u8ColorRangeMode))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u8ColorRangeMode",strCondition.c_str(),m_stUiSysSetting.u8ColorRangeMode);
        }
        if((pOrgValue == NULL ) || (pOrgValue->u8HDMIAudioSource != m_stUiSysSetting.u8HDMIAudioSource))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u8HDMIAudioSource",strCondition.c_str(),m_stUiSysSetting.u8HDMIAudioSource);
        }
        if((pOrgValue == NULL ) || (pOrgValue->bEnableAlwaysTimeshift != m_stUiSysSetting.bEnableAlwaysTimeshift))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bEnableAlwaysTimeshift",strCondition.c_str(),m_stUiSysSetting.bEnableAlwaysTimeshift);
        }
        if((pOrgValue == NULL ) || (pOrgValue->eSUPER != m_stUiSysSetting.eSUPER))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "eSUPER",strCondition.c_str(),m_stUiSysSetting.eSUPER);
        }
        if((pOrgValue == NULL ) || (pOrgValue->bUartBus != m_stUiSysSetting.bUartBus))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bUartBus",strCondition.c_str(),m_stUiSysSetting.bUartBus);
        }
    #if AUTOZOOM_ENABLE
        if((pOrgValue == NULL ) || (pOrgValue->m_AutoZoom != m_stUiSysSetting.m_AutoZoom))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "m_AutoZoom",strCondition.c_str(),m_stUiSysSetting.m_AutoZoom);
        }
    #endif
    #if ENABLE_OVERSCAN_FOR_ALL_SOURCE
        if((pOrgValue == NULL ) || (pOrgValue->bOverScan != m_stUiSysSetting.bOverScan))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bOverScan",strCondition.c_str(),m_stUiSysSetting.bOverScan);
        }
    #endif
    #if (ISDB_SYSTEM_ENABLE == 1)
        if((pOrgValue == NULL ) || (pOrgValue->m_u8BrazilVideoStandardType != m_stUiSysSetting.m_u8BrazilVideoStandardType))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "m_u8BrazilVideoStandardType",strCondition.c_str(),m_stUiSysSetting.m_u8BrazilVideoStandardType);
        }
    #endif
        if((pOrgValue == NULL ) || (pOrgValue->m_u8SoftwareUpdateMode != m_stUiSysSetting.m_u8SoftwareUpdateMode))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "m_u8SoftwareUpdateMode",strCondition.c_str(),m_stUiSysSetting.m_u8SoftwareUpdateMode);
        }
        if((pOrgValue == NULL ) || (pOrgValue->OSD_Active_Time != m_stUiSysSetting.OSD_Active_Time))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "OSD_Active_Time",strCondition.c_str(),m_stUiSysSetting.OSD_Active_Time);
        }
        if((pOrgValue == NULL ) || (pOrgValue->m_MessageBoxExist != m_stUiSysSetting.m_MessageBoxExist))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "m_MessageBoxExist",strCondition.c_str(),m_stUiSysSetting.m_MessageBoxExist);
        }
    #if (FREEVIEW_AU_ENABLE == 1)
        if((pOrgValue == NULL ) || (pOrgValue->u16LastOADVersion != m_stUiSysSetting.u16LastOADVersion))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u16LastOADVersion",strCondition.c_str(),m_stUiSysSetting.u16LastOADVersion);
        }
    #endif
        if((pOrgValue == NULL ) || (pOrgValue->bEnableAutoChannelUpdate != m_stUiSysSetting.bEnableAutoChannelUpdate))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bEnableAutoChannelUpdate",strCondition.c_str(),m_stUiSysSetting.bEnableAutoChannelUpdate);
        }
#if(1)
        if((pOrgValue == NULL ) || (pOrgValue->bDisableDynamicRescan!= m_stUiSysSetting.bDisableDynamicRescan))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bDisableDynamicRescan",strCondition.c_str(),m_stUiSysSetting.bDisableDynamicRescan);
        }

        if((pOrgValue == NULL ) || (pOrgValue->enLocalDimm != m_stUiSysSetting.enLocalDimm))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "enLocalDimm",strCondition.c_str(),m_stUiSysSetting.enLocalDimm);
        }
        if((pOrgValue == NULL ) || (pOrgValue->bATVChSwitchFreeze!= m_stUiSysSetting.bATVChSwitchFreeze))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bATVChSwitchFreeze",strCondition.c_str(),m_stUiSysSetting.bATVChSwitchFreeze);
        }
#endif
    #if(OFL_DET == 1)
        if((pOrgValue == NULL ) || (pOrgValue->bSourceDetectEnable != m_stUiSysSetting.bSourceDetectEnable))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bSourceDetectEnable",strCondition.c_str(),m_stUiSysSetting.bSourceDetectEnable);
        }
        if((pOrgValue == NULL ) || (pOrgValue->bAutoSourceSwitch != m_stUiSysSetting.bAutoSourceSwitch))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bAutoSourceSwitch",strCondition.c_str(),m_stUiSysSetting.bAutoSourceSwitch);
        }
    #endif

        if((pOrgValue == NULL ) || (pOrgValue->u32MsrvTimerCounter != m_stUiSysSetting.u32MsrvTimerCounter))
       {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u32MsrvTimerCounter",strCondition.c_str(),m_stUiSysSetting.u32MsrvTimerCounter);
        }
        if((pOrgValue == NULL ) || (pOrgValue->bAutoMHLSwitch != m_stUiSysSetting.bAutoMHLSwitch))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bAutoMHLSwitch",strCondition.c_str(),m_stUiSysSetting.bAutoMHLSwitch);
        }
    #if(FREEVIEW_AU_ENABLE == 1)
        if((pOrgValue == NULL ) || (pOrgValue->bViewerPrompt != m_stUiSysSetting.bViewerPrompt))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bViewerPrompt",strCondition.c_str(),m_stUiSysSetting.bViewerPrompt);
        }
    #endif
    #if(CI_PLUS_ENABLE == 1)
        if((pOrgValue == NULL ) || (pOrgValue->u8OpMode != m_stUiSysSetting.u8OpMode))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u8OpMode",strCondition.c_str(),m_stUiSysSetting.u8OpMode);
        }
        if((pOrgValue == NULL ) || (pOrgValue->u32CicamIdentifier != m_stUiSysSetting.u32CicamIdentifier))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u32CicamIdentifier",strCondition.c_str(),m_stUiSysSetting.u32CicamIdentifier);
        }
    #endif
#if (HBBTV_ENABLE == 1)
        if((pOrgValue == NULL ) || (pOrgValue->bEnableHbbtv != m_stUiSysSetting.bEnableHbbtv))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bEnableHbbtv", strCondition.c_str(), m_stUiSysSetting.bEnableHbbtv);
        }
        if((pOrgValue == NULL ) || (pOrgValue->bEnableStoreCookies != m_stUiSysSetting.bEnableStoreCookies))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bEnableStoreCookies", strCondition.c_str(), m_stUiSysSetting.bEnableStoreCookies);
        }
#endif
    #if(XVYCC_ENABLE == 1)
        if((pOrgValue == NULL ) || (pOrgValue->bxvYCCOnOff != m_stUiSysSetting.bxvYCCOnOff))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bxvYCCOnOff",strCondition.c_str(),m_stUiSysSetting.bxvYCCOnOff);
        }
    #endif
    #if (WOL_ENABLE == 1)
        if((pOrgValue == NULL ) || (pOrgValue->bWOLEnable != m_stUiSysSetting.bWOLEnable))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bWOLEnable",strCondition.c_str(),m_stUiSysSetting.bWOLEnable);
        }
    #endif
    #if(STR_ENABLE == 1)
        if((pOrgValue == NULL ) || (pOrgValue->u32StrPowerMode != m_stUiSysSetting.u32StrPowerMode))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u32StrPowerMode",strCondition.c_str(),m_stUiSysSetting.u32StrPowerMode);
        }
    #endif
         if((pOrgValue == NULL ) || (pOrgValue->bEnableACR != m_stUiSysSetting.bEnableACR))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bEnableACR", strCondition.c_str(), m_stUiSysSetting.bEnableACR);
        }
        if((pOrgValue == NULL ) || (pOrgValue->bMonitorITC != m_stUiSysSetting.bMonitorITC))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bMonitorITC",strCondition.c_str(),m_stUiSysSetting.bMonitorITC);
        }
        if((pOrgValue == NULL ) || (pOrgValue->bServiceListNeedRearrange != m_stUiSysSetting.bServiceListNeedRearrange))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bServiceListNeedRearrange", strCondition.c_str(), m_stUiSysSetting.bServiceListNeedRearrange);
        }

#if (CI_PLUS_ENABLE == 1)
        if((pOrgValue == NULL ) || (pOrgValue->bCiOccupiedTuner != m_stUiSysSetting.bCiOccupiedTuner))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "bCiOccupiedTuner", strCondition.c_str(), m_stUiSysSetting.bCiOccupiedTuner);
        }
        if((pOrgValue == NULL ) || (pOrgValue->u16CiPinCode != m_stUiSysSetting.u16CiPinCode))
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u16CiPinCode", strCondition.c_str(), m_stUiSysSetting.u16CiPinCode);
        }
#endif
    }

    //-------------------m_stUiSysSetting.stSubtitleSetting---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
        if((pOrgValue == NULL ) || (pOrgValue->stSubtitleSetting.SubtitleDefaultLanguage != m_stUiSysSetting.stSubtitleSetting.SubtitleDefaultLanguage))
        {
            SQL_UI_SetU32(pUiSqldb, T_SubtitleSetting, "SubtitleDefaultLanguage", strCondition.c_str(), m_stUiSysSetting.stSubtitleSetting.SubtitleDefaultLanguage);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stSubtitleSetting.SubtitleDefaultLanguage != m_stUiSysSetting.stSubtitleSetting.SubtitleDefaultLanguage))
        {
            SQL_UI_SetU32(pUiSqldb, T_SubtitleSetting, "SubtitleDefaultLanguage_2", strCondition.c_str(),m_stUiSysSetting.stSubtitleSetting.SubtitleDefaultLanguage_2);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stSubtitleSetting.fHardOfHearing != m_stUiSysSetting.stSubtitleSetting.fHardOfHearing))
        {
            SQL_UI_SetU32(pUiSqldb, T_SubtitleSetting, "fHardOfHearing", strCondition.c_str(),m_stUiSysSetting.stSubtitleSetting.fHardOfHearing);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stSubtitleSetting.fEnableSubTitle != m_stUiSysSetting.stSubtitleSetting.fEnableSubTitle))
        {
            SQL_UI_SetU32(pUiSqldb, T_SubtitleSetting, "fEnableSubTitle", strCondition.c_str(),m_stUiSysSetting.stSubtitleSetting.fEnableSubTitle);
        }
    }

    //-------------------m_stSysSetting.stUserColorTemp---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
        if((pOrgValue == NULL ) || (pOrgValue->stUserColorTemp.u8RedGain != m_stUiSysSetting.stUserColorTemp.u8RedGain))
        {
            SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP, "u8RedGain",strCondition.c_str(),m_stUiSysSetting.stUserColorTemp.u8RedGain);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserColorTemp.u8GreenGain != m_stUiSysSetting.stUserColorTemp.u8GreenGain))
        {
            SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP, "u8GreenGain",strCondition.c_str(),m_stUiSysSetting.stUserColorTemp.u8GreenGain);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserColorTemp.u8BlueGain != m_stUiSysSetting.stUserColorTemp.u8BlueGain))
        {
            SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP, "u8BlueGain",strCondition.c_str(),m_stUiSysSetting.stUserColorTemp.u8BlueGain);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserColorTemp.u8RedOffset != m_stUiSysSetting.stUserColorTemp.u8RedOffset))
        {
            SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP, "u8RedOffset",strCondition.c_str(),m_stUiSysSetting.stUserColorTemp.u8RedOffset);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserColorTemp.u8GreenOffset != m_stUiSysSetting.stUserColorTemp.u8GreenOffset))
        {
            SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP, "u8GreenOffset",strCondition.c_str(),m_stUiSysSetting.stUserColorTemp.u8GreenOffset);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserColorTemp.u8BlueOffset != m_stUiSysSetting.stUserColorTemp.u8BlueOffset))
        {
            SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP, "u8BlueOffset",strCondition.c_str(),m_stUiSysSetting.stUserColorTemp.u8BlueOffset);
        }
    }

    //-------------------m_stSysSetting.stUserColorTempEx[]---------------------
    {
        char con[16]={0};
        SQL_UI_Transaction sql_trans(pUiSqldb);
        for(int RowIndex=0; RowIndex < MS_INPUT_SOURCE_TYPE_NUM; RowIndex++)
        {
            snprintf(con, 16, "_id=%d", RowIndex);
            if((pOrgValue == NULL ) || (pOrgValue->stUserColorTempEx[RowIndex].u16RedGain != m_stUiSysSetting.stUserColorTempEx[RowIndex].u16RedGain))
            {
                SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP_EX, "u16RedGain",con, m_stUiSysSetting.stUserColorTempEx[RowIndex].u16RedGain);
            }
            if((pOrgValue == NULL ) || (pOrgValue->stUserColorTempEx[RowIndex].u16GreenGain != m_stUiSysSetting.stUserColorTempEx[RowIndex].u16GreenGain))
            {
                SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP_EX, "u16GreenGain",con, m_stUiSysSetting.stUserColorTempEx[RowIndex].u16GreenGain);
            }
            if((pOrgValue == NULL ) || (pOrgValue->stUserColorTempEx[RowIndex].u16BlueGain != m_stUiSysSetting.stUserColorTempEx[RowIndex].u16BlueGain))
            {
                SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP_EX, "u16BlueGain",con, m_stUiSysSetting.stUserColorTempEx[RowIndex].u16BlueGain);
            }
            if((pOrgValue == NULL ) || (pOrgValue->stUserColorTempEx[RowIndex].u16RedOffset != m_stUiSysSetting.stUserColorTempEx[RowIndex].u16RedOffset))
            {
                SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP_EX, "u16RedOffset",con, m_stUiSysSetting.stUserColorTempEx[RowIndex].u16RedOffset);
            }
            if((pOrgValue == NULL ) || (pOrgValue->stUserColorTempEx[RowIndex].u16GreenOffset != m_stUiSysSetting.stUserColorTempEx[RowIndex].u16GreenOffset))
            {
                SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP_EX, "u16GreenOffset",con, m_stUiSysSetting.stUserColorTempEx[RowIndex].u16GreenOffset);
            }
            if((pOrgValue == NULL ) || (pOrgValue->stUserColorTempEx[RowIndex].u16BlueOffset != m_stUiSysSetting.stUserColorTempEx[RowIndex].u16BlueOffset))
            {
                SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP_EX, "u16BlueOffset",con, m_stUiSysSetting.stUserColorTempEx[RowIndex].u16BlueOffset);
            }
        }
    }


    //-------------------m_stSysSetting.st3DInfo---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
        if((pOrgValue == NULL ) || (pOrgValue->st3DInfo.bEnable3D != m_stUiSysSetting.st3DInfo.bEnable3D))
        {
            SQL_UI_SetU32(pUiSqldb, T_3DInfo, "bEnable3D",strCondition.c_str(),m_stUiSysSetting.st3DInfo.bEnable3D);
        }
        if((pOrgValue == NULL ) || (pOrgValue->st3DInfo.enInput3DMode != m_stUiSysSetting.st3DInfo.enInput3DMode))
        {
            SQL_UI_SetU32(pUiSqldb, T_3DInfo, "enInput3DMode",strCondition.c_str(),m_stUiSysSetting.st3DInfo.enInput3DMode);
        }
        if((pOrgValue == NULL ) || (pOrgValue->st3DInfo.enOutput3DMode != m_stUiSysSetting.st3DInfo.enOutput3DMode))
        {
            SQL_UI_SetU32(pUiSqldb, T_3DInfo, "enOutput3DMode",strCondition.c_str(),m_stUiSysSetting.st3DInfo.enOutput3DMode);
        }
    }
    //-------------------m_stUiSysSetting.stUserMMSetting---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
        if((pOrgValue == NULL ) || (pOrgValue->stUserMMSetting.u8SubtitleSpecific != m_stUiSysSetting.stUserMMSetting.u8SubtitleSpecific))
        {
            SQL_UI_SetU32(pUiSqldb, T_UserMMSetting, "u8SubtitleSpecific",strCondition.c_str(),m_stUiSysSetting.stUserMMSetting.u8SubtitleSpecific);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserMMSetting.u8SubtitleBGColor != m_stUiSysSetting.stUserMMSetting.u8SubtitleBGColor))
        {
            SQL_UI_SetU32(pUiSqldb, T_UserMMSetting, "u8SubtitleBGColor",strCondition.c_str(),m_stUiSysSetting.stUserMMSetting.u8SubtitleBGColor);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserMMSetting.u8SubtitleBGColor != m_stUiSysSetting.stUserMMSetting.u8SubtitleBGColor))
        {
            SQL_UI_SetU32(pUiSqldb, T_UserMMSetting, "u8SubtitleFontColor",strCondition.c_str(),m_stUiSysSetting.stUserMMSetting.u8SlideShowTime);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserMMSetting.u8SlideShowTime != m_stUiSysSetting.stUserMMSetting.u8SlideShowTime))
        {
            SQL_UI_SetU32(pUiSqldb, T_UserMMSetting, "u8SlideShowTime",strCondition.c_str(),m_stUiSysSetting.stUserMMSetting.u8SlideShowTime);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserMMSetting.u8SlideShowMode != m_stUiSysSetting.stUserMMSetting.u8SlideShowMode))
        {
            SQL_UI_SetU32(pUiSqldb, T_UserMMSetting, "u8SlideShowMode",strCondition.c_str(),m_stUiSysSetting.stUserMMSetting.u8SlideShowMode);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserMMSetting.fPreviewOn != m_stUiSysSetting.stUserMMSetting.fPreviewOn))
        {
            SQL_UI_SetU32(pUiSqldb, T_UserMMSetting, "fPreviewOn",strCondition.c_str(),m_stUiSysSetting.stUserMMSetting.fPreviewOn);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserMMSetting.fResumePlay != m_stUiSysSetting.stUserMMSetting.fResumePlay))
        {
            SQL_UI_SetU32(pUiSqldb, T_UserMMSetting, "fResumePlay",strCondition.c_str(),m_stUiSysSetting.stUserMMSetting.fResumePlay);
        }
    }
    //-------------------m_stSysSetting.stUserLocationSetting---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
        if((pOrgValue == NULL ) || (pOrgValue->stUserLocationSetting.u16LocationNo != m_stUiSysSetting.stUserLocationSetting.u16LocationNo))
        {
            SQL_UI_SetU32(pUiSqldb, T_UserLocationSetting, "u16LocationNo",strCondition.c_str(),m_stUiSysSetting.stUserLocationSetting.u16LocationNo);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserLocationSetting.s16ManualLongitude != m_stUiSysSetting.stUserLocationSetting.s16ManualLongitude))
        {
            SQL_UI_SetU32(pUiSqldb, T_UserLocationSetting, "s16ManualLongitude",strCondition.c_str(),m_stUiSysSetting.stUserLocationSetting.s16ManualLongitude);
        }
        if((pOrgValue == NULL ) || (pOrgValue->stUserLocationSetting.s16ManualLatitude != m_stUiSysSetting.stUserLocationSetting.s16ManualLatitude))
        {
            SQL_UI_SetU32(pUiSqldb, T_UserLocationSetting, "s16ManualLatitude",strCondition.c_str(),m_stUiSysSetting.stUserLocationSetting.s16ManualLatitude);
        }
    }

    //-------------------m_stUiSysSetting.MfcMode---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
        if((pOrgValue == NULL ) || (pOrgValue->MfcMode.eMFC != m_stUiSysSetting.MfcMode.eMFC))
        {
            SQL_UI_SetU32(pUiSqldb, T_MfcMode, "eMFC",strCondition.c_str(),m_stUiSysSetting.MfcMode.eMFC);
        }
    }

    //-------------------m_stSysSetting.FavTypeName---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
        char con[16]={0};
        for(int RowIndex=0; RowIndex < MAX_FAVLIST_NUM; RowIndex++)
        {
            snprintf(con, 16, "TypeId=%d", RowIndex);
            if((pOrgValue == NULL ) || (pOrgValue->FavTypeName[RowIndex] != m_stUiSysSetting.FavTypeName[RowIndex]))
            {
                SQL_UI_SetText(pUiSqldb, T_FavTypeName, "TypeName",(const char *)con, (char *)&m_stUiSysSetting.FavTypeName[RowIndex]);
            }
        }
    }
    #if (STEREO_3D_ENABLE == 1)
    //-------------------m_stUiSysSetting.st3DSetting---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
        if((pOrgValue == NULL ) || (pOrgValue->st3DSetting.enDisplayMode != m_stUiSysSetting.st3DSetting.enDisplayMode))
        {
            SQL_UI_SetU32(pUiSqldb, T_3DSetting, "enDisplayMode",strCondition.c_str(),m_stUiSysSetting.st3DSetting.enDisplayMode);
        }
        if((pOrgValue == NULL ) || (pOrgValue->st3DSetting.en3DFormat != m_stUiSysSetting.st3DSetting.en3DFormat))
        {
            SQL_UI_SetU32(pUiSqldb, T_3DSetting, "en3DFormat",strCondition.c_str(),m_stUiSysSetting.st3DSetting.en3DFormat);
        }
        if((pOrgValue == NULL ) || (pOrgValue->st3DSetting.en2DFormat != m_stUiSysSetting.st3DSetting.en2DFormat))
        {
            SQL_UI_SetU32(pUiSqldb, T_3DSetting, "en2DFormat",strCondition.c_str(),m_stUiSysSetting.st3DSetting.en2DFormat);
        }
        if((pOrgValue == NULL ) || (pOrgValue->st3DSetting.enAutoStart != m_stUiSysSetting.st3DSetting.enAutoStart))
        {
            SQL_UI_SetU32(pUiSqldb, T_3DSetting, "enAutoStart",strCondition.c_str(),m_stUiSysSetting.st3DSetting.enAutoStart);
        }
        if((pOrgValue == NULL ) || (pOrgValue->st3DSetting.en3DTimerPeriod != m_stUiSysSetting.st3DSetting.en3DTimerPeriod))
        {
            SQL_UI_SetU32(pUiSqldb, T_3DSetting, "en3DTimerPeriod",strCondition.c_str(),m_stUiSysSetting.st3DSetting.en3DTimerPeriod);
        }
    }
    #endif

    //-------------------m_stSysSetting rename inputSource---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
        char con[16]={0};
        if((pOrgValue == NULL ) || (strcmp(pOrgValue->InputSourceName_TV, m_stUiSysSetting.InputSourceName_TV) == 1))
        {
            snprintf(con, 16, "_id=%d", MAPI_INPUT_SOURCE_ATV);
            SQL_UI_SetText(pUiSqldb, T_InputSource_Type, "_Name",(const char *)con, m_stUiSysSetting.InputSourceName_TV);
        }
        if((pOrgValue == NULL ) || (strcmp(pOrgValue->InputSourceName_Componant1, m_stUiSysSetting.InputSourceName_Componant1) == 1))
        {
            snprintf(con, 16, "_id=%d", MAPI_INPUT_SOURCE_YPBPR);
            SQL_UI_SetText(pUiSqldb, T_InputSource_Type, "_Name",(const char *)con, m_stUiSysSetting.InputSourceName_Componant1);
        }
        if((pOrgValue == NULL ) || (strcmp(pOrgValue->InputSourceName_PC_RGB, m_stUiSysSetting.InputSourceName_PC_RGB) == 1))
        {
            snprintf(con, 16, "_id=%d", MAPI_INPUT_SOURCE_VGA);
            SQL_UI_SetText(pUiSqldb, T_InputSource_Type, "_Name",(const char *)con, m_stUiSysSetting.InputSourceName_PC_RGB);
        }
        if((pOrgValue == NULL ) || (strcmp(pOrgValue->InputSourceName_PC_RGB2, m_stUiSysSetting.InputSourceName_PC_RGB2) == 1))
        {
            snprintf(con, 16, "_id=%d", MAPI_INPUT_SOURCE_VGA2);
            SQL_UI_SetText(pUiSqldb, T_InputSource_Type, "_Name",(const char *)con, m_stUiSysSetting.InputSourceName_PC_RGB2);
        }
        if((pOrgValue == NULL ) || (strcmp(pOrgValue->InputSourceName_PC_RGB3, m_stUiSysSetting.InputSourceName_PC_RGB3) == 1))
        {
            snprintf(con, 16, "_id=%d", MAPI_INPUT_SOURCE_VGA3);
            SQL_UI_SetText(pUiSqldb, T_InputSource_Type, "_Name",(const char *)con, m_stUiSysSetting.InputSourceName_PC_RGB3);
        }
        if((pOrgValue == NULL ) || (strcmp(pOrgValue->InputSourceName_HDMI1, m_stUiSysSetting.InputSourceName_HDMI1) == 1))
        {
            snprintf(con, 16, "_id=%d", MAPI_INPUT_SOURCE_HDMI);
            SQL_UI_SetText(pUiSqldb, T_InputSource_Type, "_Name",(const char *)con, m_stUiSysSetting.InputSourceName_HDMI1);
        }
        if((pOrgValue == NULL ) || (strcmp(pOrgValue->InputSourceName_HDMI2, m_stUiSysSetting.InputSourceName_HDMI2) == 1))
        {
            snprintf(con, 16, "_id=%d", MAPI_INPUT_SOURCE_HDMI2);
            SQL_UI_SetText(pUiSqldb, T_InputSource_Type, "_Name",(const char *)con, m_stUiSysSetting.InputSourceName_HDMI2);
        }
        if((pOrgValue == NULL ) || (strcmp(pOrgValue->InputSourceName_HDMI3, m_stUiSysSetting.InputSourceName_HDMI3) == 1))
        {
            snprintf(con, 16, "_id=%d", MAPI_INPUT_SOURCE_HDMI3);
            SQL_UI_SetText(pUiSqldb, T_InputSource_Type, "_Name",(const char *)con, m_stUiSysSetting.InputSourceName_HDMI3);
        }
        if((pOrgValue == NULL ) || (strcmp(pOrgValue->InputSourceName_HDMI4, m_stUiSysSetting.InputSourceName_HDMI4) == 1))
        {
            snprintf(con, 16, "_id=%d", MAPI_INPUT_SOURCE_HDMI4);
            SQL_UI_SetText(pUiSqldb, T_InputSource_Type, "_Name",(const char *)con, m_stUiSysSetting.InputSourceName_HDMI4);
        }
        if((pOrgValue == NULL ) || (strcmp(pOrgValue->InputSourceName_AV1, m_stUiSysSetting.InputSourceName_AV1) == 1))
        {
            snprintf(con, 16, "_id=%d", MAPI_INPUT_SOURCE_CVBS);
            SQL_UI_SetText(pUiSqldb, T_InputSource_Type, "_Name",(const char *)con, m_stUiSysSetting.InputSourceName_AV1);
        }
    }

 //   m_stUiSysSetting.u16CheckSum = CalCheckSum((U8 *)&(m_stUiSysSetting), sizeof(MS_USER_SYSTEM_SETTING));
}


bool UI_System_Database::SQL_UI_SetText(sqlite3* db, const char *Table, const char * Title, const char * Condition, char * Text)
{
    int rc = SQLITE_ERROR;
    unsigned char u8TimeOut = 3;
    char *zErrMsg = NULL;
    char str_SQL[QUERY_UI_STRING_LENGTH] = {0};

    if(Text == NULL)
        return false;

    snprintf(str_SQL, QUERY_UI_STRING_LENGTH, "UPDATE %s SET %s=\"%s\" WHERE %s;", Table, Title, Text, Condition);
    MSG_SQL_UI_DBG(printf("%s\n",str_SQL));
    do
    {
        rc = sqlite3_exec(db, str_SQL, NULL, 0, &zErrMsg);
        if( rc == SQLITE_OK)
        {
            break;
        }
        else
        {
            MSG_SQL_UI_ERROR(printf("SQL_SetText error:%s\n", zErrMsg));
            if( strstr(zErrMsg, "database is locked") )
            {
                usleep(50 * 1000);
            }
            else if( strstr(zErrMsg, "unable to open") )
            {
                usleep(50 * 1000);
            }
            u8TimeOut --;

            if(zErrMsg != NULL)
            {
                sqlite3_free(zErrMsg);
                zErrMsg = NULL;
            }
        }
    }while(u8TimeOut);

    if(zErrMsg != NULL)
    {
        sqlite3_free(zErrMsg);
    }

    if(u8TimeOut == 0)
    {
        sqlite3_exec(db, "IGNORE;", NULL, 0, NULL);
        return false;
    }
    else
    {
       return true;
    }
}

void UI_System_Database::GetMediumSetting(ST_TV_MEDIUM_SETTING *pValue)
{
    int ColNum = 0;
    int ColIndex = 0;
    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);

    //-------------------m_stMediumSetting---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb,T_MediumSetting, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum))
        {
            ColIndex = 1;
            m_stUiMediumSetting.n32AntennaType = (EN_UI_ANTENNA_TYPE)SQL_UI_GetU32(prepear.pSqlstmt,"AntennaType");
            m_stUiMediumSetting.n32CableSystem = (EN_UI_CABLE_SYSTEM)SQL_UI_GetU32(prepear.pSqlstmt,"CableSystem");
            m_stUiMediumSetting.cAntennaPower = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"fAntennaPower");
        }
    }

    memcpy((unsigned char*)pValue, (unsigned char*)&(m_stUiMediumSetting), sizeof(m_stUiMediumSetting));
}

void UI_System_Database::SetMediumSetting(ST_TV_MEDIUM_SETTING *pValue)
{
    memcpy((unsigned char *)&(m_stUiMediumSetting), (unsigned char*)pValue, sizeof(m_stUiMediumSetting));

    string strCondition = string("_id=0");
    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stMediumSetting---------------------
    SQL_UI_Transaction sql_trans(pUiSqldb);
    {
        SQL_UI_SetU32(pUiSqldb, T_MediumSetting, "AntennaType",strCondition.c_str(),m_stUiMediumSetting.n32AntennaType);
        SQL_UI_SetU32(pUiSqldb, T_MediumSetting, "CableSystem",strCondition.c_str(),m_stUiMediumSetting.n32CableSystem);
        SQL_UI_SetU32(pUiSqldb, T_MediumSetting, "fAntennaPower",strCondition.c_str(),m_stUiMediumSetting.cAntennaPower);
    }
}

unsigned int UI_System_Database::GetSystemNetworkId(void)
{
    int ColNum = 0;
    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stSysSetting---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_SystemSetting, ColNum, NULL);
        while(SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt))
        {
            m_stUiSysSetting.u16NetworkId = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16NetworkId");
        }
    }
    return m_stUiSysSetting.u16NetworkId;
}

void UI_System_Database::SetSystemNetworkId(unsigned int u16NetworkIdValue)
{
    string strCondition = string("_id=0");
    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);

    //-------------------m_stUiSysSetting---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
        if(u16NetworkIdValue != m_stUiSysSetting.u16NetworkId)
        {
            m_stUiSysSetting.u16NetworkId= u16NetworkIdValue;
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "u16NetworkId",strCondition.c_str(),m_stUiSysSetting.u16NetworkId);
        }
    }
}

unsigned char UI_System_Database::GetPerformanceMonitor(void)
{
    int ColNum = 0;

    SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqlfactorydb);
     //-------------------m_stUiCISet---------------------
     {
         SQL_UI_LookupPre prepare(pUiSqlfactorydb, T_CIAdjust, ColNum, NULL);
         while(SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt))
         {
         m_stUiCISet.bPerformanceMonitor = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "Performance_Monitor");
     }
     }

     return m_stUiCISet.bPerformanceMonitor;
}

void UI_System_Database::SetPerformanceMonitor(unsigned char pstPerformanceMonitor)
{
    m_stUiCISet.bPerformanceMonitor  = pstPerformanceMonitor;

    string strCondition = string("_id=0");
    SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqlfactorydb);

    //-------------------m_stUiCISet---------------------
    SQL_UI_Transaction sql_trans(pUiSqlfactorydb);
    {
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "Performance_Monitor",strCondition.c_str(),m_stUiCISet.bPerformanceMonitor);
    }
}

bool UI_System_Database::IsInstallationGuideEnabled(void)
{
    int ColNum = 0;
    int ColIndex = 1;

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stUiSysSetting---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_SystemSetting, ColNum, NULL);
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            m_stUiSysSetting.fRunInstallationGuide = (bool)SQL_UI_GetU32(prepear.pSqlstmt,"fRunInstallationGuide");
        }
    }

    return m_stUiSysSetting.fRunInstallationGuide;
}

bool UI_System_Database::IsAutoChannelUpdateEnabled(void)
{
    int ColNum = 0;
    int ColIndex = 1;

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stUiSysSetting---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_SystemSetting, ColNum, NULL);
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            m_stUiSysSetting.bEnableAutoChannelUpdate = (bool)SQL_UI_GetU32(prepear.pSqlstmt,"bEnableAutoChannelUpdate");
        }
    }

    if( m_stUiSysSetting.bEnableAutoChannelUpdate == true )
    {
        return true;
    }
    else
    {
        return false;
    }
}

#if (CI_PLUS_ENABLE == 1)
unsigned char UI_System_Database::GetCredentialMode(void)
{
    int ColNum = 0;

    SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqlfactorydb);
     //-------------------m_stUiCISet---------------------
     {
         SQL_UI_LookupPre prepare(pUiSqlfactorydb, T_CIAdjust, ColNum, NULL);
         while(SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt))
         {
             m_stUiCISet.enCredentialMode = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "Credential_Mode");
         }
     }

    return m_stUiCISet.enCredentialMode;
}
#endif
void UI_System_Database::SetInstallationguideEnabled(bool *pValue)
{
    string strCondition = string("_id=0");
    m_stUiSysSetting.fRunInstallationGuide = *(bool *)pValue;

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stUiSysSetting---------------------
    {
        SQL_UI_Transaction sql_trans(pUiSqldb);
        {
            SQL_UI_SetU32(pUiSqldb, T_SystemSetting, "fRunInstallationGuide",strCondition.c_str(),m_stUiSysSetting.fRunInstallationGuide);
        }
     }
}

void UI_System_Database::GetColorTempEx(PQL_COLOR_TEMPEX_DATA *pValue, void *pParam, MAPI_INPUT_SOURCE_TYPE enSrcType)
{
    EN_UI_MS_INPUT_SOURCE_TYPE enMsInputSourceType = UITransMapiInputSourceToMsInputSoutrceType(enSrcType);

    int u32Idx;


    u32Idx = *(int *)pParam;

    if(u32Idx == COLOR_TEMP_USER)
    {
        int ColNum;
        int ColIndex;
    int RowIndex = (int)enMsInputSourceType;

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stUiSysSetting.stUserColorTempEx[]---------------------
    {
        char con[16] = {0};
        snprintf(con, 16, "_id=%d", RowIndex);
        SQL_UI_LookupPre  prepear(pUiSqldb, T_USER_COLORTEMP_EX, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex<ColNum) && (RowIndex < MS_INPUT_SOURCE_TYPE_NUM))
        {
            ColIndex = 1;
            m_stUiSysSetting.stUserColorTempEx[RowIndex].u16RedGain = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16RedGain");
            m_stUiSysSetting.stUserColorTempEx[RowIndex].u16GreenGain = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16GreenGain");
            m_stUiSysSetting.stUserColorTempEx[RowIndex].u16BlueGain = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16BlueGain");
            m_stUiSysSetting.stUserColorTempEx[RowIndex].u16RedOffset = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16RedOffset");
            m_stUiSysSetting.stUserColorTempEx[RowIndex].u16GreenOffset = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16GreenOffset");
            m_stUiSysSetting.stUserColorTempEx[RowIndex].u16BlueOffset = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16BlueOffset");
        }
    }
        memcpy(pValue, &(m_stUiSysSetting.stUserColorTempEx[enMsInputSourceType]), sizeof(PqlColorTempexData));
    }
    else
    {
        //if(IsFactoryColorTempDirty)
        {
            //MSG_SQL_TRACE(printf("\n@@@MSrv_System_Database::GetColorTempEx"));
            //LoadFactoryColorTempEx();

            //ClearFactoryColorTempDirtyFlag
        }
        memcpy(pValue, &(m_stFactoryColorTempEx.astColorTempEx[u32Idx][enMsInputSourceType]), sizeof(PqlColorTempexData));
    }
}

void UI_System_Database::LoadFactoryColorTempEx(void)
{
    int ColNum;
    char con[64]={0};
    int ColorTmpIdx;
    sqlite3 *pSqldbTmp = NULL;


    //SQL_Connect Connect(SQL_DB_FactoryColorTempExPath, &pSqldbTmp, &m_DBmutex);
    SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pSqldbTmp);
    //-------------------m_stFactoryColorTempEx.astColorTemp[ColorTmpIdx]---------------------
    {
        for(int InputSourceID = 0; InputSourceID < MS_INPUT_SOURCE_TYPE_NUM; InputSourceID++ )
        {
            snprintf(con, 16, "InputSourceID=%d", InputSourceID);
            //SQL_LookupPre prepare(pSqldbTmp, SQL_DB_FactoryColorTempExTableName, ColNum, con);
            SQL_UI_LookupPre  prepear(pSqldbTmp, T_FacrotyColorTempEx, ColNum, con);
            ColorTmpIdx = 0;
            while(SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt) && ColorTmpIdx < COLOR_TEMP_NUM)
            {
                m_stFactoryColorTempEx.astColorTempEx[ColorTmpIdx][InputSourceID].u16RedGain = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16RedGain");
                m_stFactoryColorTempEx.astColorTempEx[ColorTmpIdx][InputSourceID].u16GreenGain = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16GreenGain");
                m_stFactoryColorTempEx.astColorTempEx[ColorTmpIdx][InputSourceID].u16BlueGain = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16BlueGain");
                m_stFactoryColorTempEx.astColorTempEx[ColorTmpIdx][InputSourceID].u16RedOffset = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16RedOffset");
                m_stFactoryColorTempEx.astColorTempEx[ColorTmpIdx][InputSourceID].u16GreenOffset = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16GreenOffset");
                m_stFactoryColorTempEx.astColorTempEx[ColorTmpIdx][InputSourceID].u16BlueOffset = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt,"u16BlueOffset");
                ColorTmpIdx++;
            }
        }
    }
}

EN_UI_MS_INPUT_SOURCE_TYPE UI_System_Database::UITransMapiInputSourceToMsInputSoutrceType(MAPI_INPUT_SOURCE_TYPE enInputSrc)
{
    switch(enInputSrc)
    {
        case MAPI_INPUT_SOURCE_DTV:
        case MAPI_INPUT_SOURCE_DTV2:
        case MAPI_INPUT_SOURCE_DTV3:
            return MS_INPUT_SOURCE_TYPE_DTV;
            break;
        case MAPI_INPUT_SOURCE_ATV:
            return MS_INPUT_SOURCE_TYPE_ATV;
            break;
        case MAPI_INPUT_SOURCE_SCART:
        case MAPI_INPUT_SOURCE_SCART2:
            return MS_INPUT_SOURCE_TYPE_SCART;
            break;
        case MAPI_INPUT_SOURCE_CVBS:
        case MAPI_INPUT_SOURCE_CVBS2:
        case MAPI_INPUT_SOURCE_CVBS3:
        case MAPI_INPUT_SOURCE_CVBS4:
        case MAPI_INPUT_SOURCE_CVBS5:
        case MAPI_INPUT_SOURCE_CVBS6:
        case MAPI_INPUT_SOURCE_CVBS7:
        case MAPI_INPUT_SOURCE_CVBS8:
            return MS_INPUT_SOURCE_TYPE_CVBS;
            break;
        case MAPI_INPUT_SOURCE_SVIDEO:
        case MAPI_INPUT_SOURCE_SVIDEO2:
        case MAPI_INPUT_SOURCE_SVIDEO3:
        case MAPI_INPUT_SOURCE_SVIDEO4:
            return MS_INPUT_SOURCE_TYPE_SVIDEO;
            break;
        case MAPI_INPUT_SOURCE_YPBPR:
        case MAPI_INPUT_SOURCE_YPBPR2:
        case MAPI_INPUT_SOURCE_YPBPR3:
            return MS_INPUT_SOURCE_TYPE_YPBPR;
            break;
        case MAPI_INPUT_SOURCE_HDMI:
        case MAPI_INPUT_SOURCE_HDMI2:
        case MAPI_INPUT_SOURCE_HDMI3:
        case MAPI_INPUT_SOURCE_HDMI4:
            return MS_INPUT_SOURCE_TYPE_HDMI;
            break;
        case MAPI_INPUT_SOURCE_VGA:
        case MAPI_INPUT_SOURCE_VGA2:
        case MAPI_INPUT_SOURCE_VGA3:
            return MS_INPUT_SOURCE_TYPE_VGA;
            break;
        case MAPI_INPUT_SOURCE_DVI:
        case MAPI_INPUT_SOURCE_DVI2:
        case MAPI_INPUT_SOURCE_DVI3:
        case MAPI_INPUT_SOURCE_DVI4:

        case MAPI_INPUT_SOURCE_STORAGE:
        case MAPI_INPUT_SOURCE_KTV:
        case MAPI_INPUT_SOURCE_JPEG:
        case MAPI_INPUT_SOURCE_STORAGE2:
        case MAPI_INPUT_SOURCE_SCALER_OP:
            return MS_INPUT_SOURCE_TYPE_OTHERS;
            break;
        case MAPI_INPUT_SOURCE_RVU:
            return MS_INPUT_SOURCE_TYPE_RVU;
            break;
        default:
            // error here
            printf("Incorrect Input Source Type, Fix this\n");
            //ASSERT(0);
            return MS_INPUT_SOURCE_TYPE_NONE;
            break;
    }

    printf("Incorrect Input Source Type, Fix this\n");
    //ASSERT(0);
    return MS_INPUT_SOURCE_TYPE_NONE;
}

void UI_System_Database::SetColorTempEx(PQL_COLOR_TEMPEX_DATA *pOrgValue, void *pParam, MAPI_INPUT_SOURCE_TYPE  eCurrentInputType)
{
    EN_UI_MS_INPUT_SOURCE_TYPE enMsInputSourceType = UITransMapiInputSourceToMsInputSoutrceType(eCurrentInputType);

     int RowIndex =(int)enMsInputSourceType;
     SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
     //-------------------m_stUiSysSetting.stUserColorTempEx[]---------------------
     {
        char con[16]={0};
        SQL_UI_Transaction sql_trans(pUiSqldb);
        {
            snprintf(con, 16, "_id=%d", RowIndex);
            if((pOrgValue == NULL ) || (pOrgValue->u16RedGain != m_stUiSysSetting.stUserColorTempEx[RowIndex].u16RedGain))
            {
                SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP_EX, "u16RedGain",con, pOrgValue->u16RedGain);
            }
            if((pOrgValue == NULL ) || (pOrgValue->u16GreenGain != m_stUiSysSetting.stUserColorTempEx[RowIndex].u16GreenGain))
            {
                SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP_EX, "u16GreenGain",con, pOrgValue->u16GreenGain);
            }
            if((pOrgValue == NULL ) || (pOrgValue->u16BlueGain != m_stUiSysSetting.stUserColorTempEx[RowIndex].u16BlueGain))
            {
                SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP_EX, "u16BlueGain",con, pOrgValue->u16BlueGain);
            }
            if((pOrgValue == NULL ) || (pOrgValue->u16RedOffset != m_stUiSysSetting.stUserColorTempEx[RowIndex].u16RedOffset))
            {
                SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP_EX, "u16RedOffset",con, pOrgValue->u16RedOffset);
            }
            if((pOrgValue == NULL ) || (pOrgValue->u16GreenOffset != m_stUiSysSetting.stUserColorTempEx[RowIndex].u16GreenOffset))
            {
                SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP_EX, "u16GreenOffset",con, pOrgValue->u16GreenOffset);
            }
            if((pOrgValue == NULL ) || (pOrgValue->u16BlueOffset != m_stUiSysSetting.stUserColorTempEx[RowIndex].u16BlueOffset))
            {
                SQL_UI_SetU32(pUiSqldb, T_USER_COLORTEMP_EX, "u16BlueOffset",con, pOrgValue->u16BlueOffset);
            }
        }
    }

    memcpy(&(m_stUiSysSetting.stUserColorTempEx[enMsInputSourceType]), pOrgValue, sizeof(PqlColorTempexData));
}

void UI_System_Database::GetPEQSetting(void *pValue, unsigned char u8BandIndex)
{
   if((pValue == NULL) ||(u8BandIndex == 0))
   {
       MSG_SQL_UI_DBG(printf("Row =%d\n",u8BandIndex));
   }
}

void UI_System_Database::SetPEQSetting(void *pValue, unsigned char u8BandIndex)
{
   if((pValue == NULL) ||(u8BandIndex == 0))
   {
       MSG_SQL_UI_DBG(printf("Row =%d\n",u8BandIndex));
   }
}
void UI_System_Database::GetFactoryExtSetting_NSVD(MS_UI_Factory_NS_VD_SET *pValue)
{
    int ColNum = 0;
       SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqlfactorydb);
      //-------------------m_stUiFactoryExt.stNSVDsetting---------------------
      {
          SQL_UI_LookupPre  prepear(pUiSqlfactorydb, T_NonStarndardAdjust, ColNum, NULL);
          while(SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt))
          {
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_D4 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_D4");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_D8_Bit3210 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_D8_Bit3210");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_D5_Bit2 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_D5_Bit2");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_D7_LOW_BOUND = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_D7_LOW_BOUND");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_D7_HIGH_BOUND = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_D7_HIGH_BOUND");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_D9_Bit0 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_D9_Bit0");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_A0 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_A0");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_A1 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_A1");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_66_Bit76 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_66_Bit76");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_6E_Bit7654 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_6E_Bit7654");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_6E_Bit3210 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_6E_Bit3210");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_43 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_43");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_44 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_44");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_CB =(unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_CB");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_CF_Bit2_ATV = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_CF_Bit2_ATV");
              m_stUiFactoryExt.stNSVDsetting.u8AFEC_CF_Bit2_AV = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "u8AFEC_CF_Bit2_AV");
          }
      }

     memcpy((unsigned char*)pValue,&(m_stUiFactoryExt.stNSVDsetting), sizeof(MS_UI_Factory_NS_VD_SET));
}

void UI_System_Database::SetFactoryExtSetting_NSVD(MS_UI_Factory_NS_VD_SET *pValue)
{
    string strCondition = string("_id=0");
    memcpy((unsigned char*)(&(m_stUiFactoryExt.stNSVDsetting)), (unsigned char*)pValue, sizeof(MS_UI_Factory_NS_VD_SET));

    SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqlfactorydb);
    SQL_UI_Transaction sql_trans(pUiSqlfactorydb);
    //-------------------m_stFactoryExt.stNSVDsetting---------------------
    {
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_D4",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_D4);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_D8_Bit3210",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_D8_Bit3210);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_D5_Bit2",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_D5_Bit2);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_D7_LOW_BOUND",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_D7_LOW_BOUND);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_D7_HIGH_BOUND",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_D7_HIGH_BOUND);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_D9_Bit0",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_D9_Bit0);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_A0",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_A0);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_A1",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_A1);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_66_Bit76",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_66_Bit76);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_6E_Bit7654",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_6E_Bit7654);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_6E_Bit3210",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_6E_Bit3210);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_43",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_43);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_44",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_44);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_CB",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_CB);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_CF_Bit2_ATV",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_CF_Bit2_ATV);
        SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "u8AFEC_CF_Bit2_AV",strCondition.c_str(),m_stUiFactoryExt.stNSVDsetting.u8AFEC_CF_Bit2_AV);
     }
}

void UI_System_Database::GetFactoryExtSetting_VIF(MS_UI_Factory_NS_VIF_SET *pValue)
{
    int ColNum = 0;
       SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqlfactorydb);
      //-------------------m_stUiFactoryExt.stNSVIFsetting---------------------
      {
          SQL_UI_LookupPre  prepear(pUiSqlfactorydb, T_NonStarndardAdjust, ColNum, NULL);

          while(SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt))
          {
              //-------------------m_stUiFactoryExt.stNSVIFsetting---------------------
              m_stUiFactoryExt.stNSVIFsetting.VifTop = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifTop");
              m_stUiFactoryExt.stNSVIFsetting.VifVgaMaximum = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "VifVgaMaximum");
              m_stUiFactoryExt.stNSVIFsetting.GainDistributionThr = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "GainDistributionThr");
              m_stUiFactoryExt.stNSVIFsetting.VifAgcVgaBase = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifAgcVgaBase");
              m_stUiFactoryExt.stNSVIFsetting.ChinaDescramblerBox = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "ChinaDescramblerBox");
              m_stUiFactoryExt.stNSVIFsetting.VifCrKp1 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifCrKp1");
              m_stUiFactoryExt.stNSVIFsetting.VifCrKi1 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifCrKi1");
              m_stUiFactoryExt.stNSVIFsetting.VifCrKp2 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifCrKp2");
              m_stUiFactoryExt.stNSVIFsetting.VifCrKi2 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifCrKi2");
              m_stUiFactoryExt.stNSVIFsetting.VifCrKp = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifCrKp");
              m_stUiFactoryExt.stNSVIFsetting.VifCrKi = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifCrKi");
              m_stUiFactoryExt.stNSVIFsetting.VifCrLockThr = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "VifCrLockThr");
              m_stUiFactoryExt.stNSVIFsetting.VifCrThr = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "VifCrThr");
              m_stUiFactoryExt.stNSVIFsetting.VifCrKpKiAdjust = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifCrKpKiAdjust");
              m_stUiFactoryExt.stNSVIFsetting.VifDelayReduce = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifDelayReduce");
              m_stUiFactoryExt.stNSVIFsetting.VifOverModulation = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifOverModulation");
              m_stUiFactoryExt.stNSVIFsetting.VifClampgainClampOvNegative = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "VifClampgainClampOvNegative");
              m_stUiFactoryExt.stNSVIFsetting.VifClampgainGainOvNegative = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "VifClampgainGainOvNegative");
              m_stUiFactoryExt.stNSVIFsetting.VifACIAGCREF = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifACIAGCREF");
              m_stUiFactoryExt.stNSVIFsetting.VifAgcRefNegative = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifAgcRefNegative");
              m_stUiFactoryExt.stNSVIFsetting.VifAsiaSignalOption = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "VifAsiaSignalOption");
              m_stUiFactoryExt.stNSVIFsetting.ChinaDescramblerBoxDelay= (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "ChinaDescramblerBoxDelay");
          }
      }

     memcpy(pValue,&(m_stUiFactoryExt.stNSVIFsetting), sizeof(MS_UI_Factory_NS_VIF_SET));
}

void UI_System_Database::SetFactoryExtSetting_VIF(MS_UI_Factory_NS_VIF_SET *pValue)
{
    string strCondition = string("_id=0");

    memcpy((unsigned char*)(&(m_stUiFactoryExt.stNSVIFsetting)),(unsigned char*) pValue, sizeof(MS_UI_Factory_NS_VIF_SET));
    SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqlfactorydb);
    SQL_UI_Transaction sql_trans(pUiSqlfactorydb);

  //-------------------m_stUiFactoryExt.stNSVIFsetting---------------------
  {
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifTop",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifTop);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifVgaMaximum",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifVgaMaximum);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "GainDistributionThr",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.GainDistributionThr);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifAgcVgaBase",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifAgcVgaBase);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "ChinaDescramblerBox",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.ChinaDescramblerBox);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifCrKp1",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifCrKp1);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifCrKi1",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifCrKi1);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifCrKp2",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifCrKp2);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifCrKi2",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifCrKi2);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifCrKp",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifCrKp);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifCrKi",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifCrKi);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifCrLockThr",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifCrLockThr);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifCrThr",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifCrThr);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifCrKpKiAdjust",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifCrKpKiAdjust);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifDelayReduce",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifDelayReduce);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifOverModulation",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifOverModulation);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifClampgainClampOvNegative",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifClampgainClampOvNegative);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifClampgainGainOvNegative",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifClampgainGainOvNegative);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifACIAGCREF",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifACIAGCREF);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifAgcRefNegative",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifAgcRefNegative);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "VifAsiaSignalOption",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.VifAsiaSignalOption);
      SQL_UI_SetU32(pUiSqlfactorydb, T_NonStarndardAdjust, "ChinaDescramblerBoxDelay",strCondition.c_str(),m_stUiFactoryExt.stNSVIFsetting.ChinaDescramblerBoxDelay);
   }
}

void UI_System_Database::GetFactoryExtSetting_SSC(MS_UI_FACTORY_SSC_SET *pValue)
{
    int ColNum = 0;
       SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqlfactorydb);
       {
            //-------------------m_stUIFactoryExt.stSSCsetting---------------------
            SQL_UI_LookupPre  prepear(pUiSqlfactorydb, T_SSCAdjust,ColNum, NULL);

            while(SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt))
            {
                m_stUiFactoryExt.stSSCsetting.Lvds_SscEnable = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "Lvds_SscEnable");
                m_stUiFactoryExt.stSSCsetting.Miu_SscEnable = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt, "Miu_SscEnable");
                m_stUiFactoryExt.stSSCsetting.Lvds_SscSpan = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "Lvds_SscSpan");
                m_stUiFactoryExt.stSSCsetting.Lvds_SscStep = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "Lvds_SscStep");
                m_stUiFactoryExt.stSSCsetting.Miu_SscSpan[0] =  (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "Miu_SscSpan");
                m_stUiFactoryExt.stSSCsetting.Miu_SscStep[0] = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "Miu_SscStep");
                m_stUiFactoryExt.stSSCsetting.Miu_SscSpan[1] =  (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "Miu1_SscSpan");
                m_stUiFactoryExt.stSSCsetting.Miu_SscStep[1] = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "Miu1_SscStep");
                m_stUiFactoryExt.stSSCsetting.Miu_SscSpan[2] =  (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "Miu2_SscSpan");
                m_stUiFactoryExt.stSSCsetting.Miu_SscStep[2] = (unsigned int)SQL_UI_GetU32(prepear.pSqlstmt, "Miu2_SscStep");
            }
     }

     memcpy((unsigned char*)pValue, (unsigned char*)&(m_stUiFactoryExt.stSSCsetting), sizeof(MS_UI_FACTORY_SSC_SET));
}

void UI_System_Database::SetFactoryExtSetting_SSC(MS_UI_FACTORY_SSC_SET *pValue)
{
    string strCondition = string("_id=0");

    memcpy((unsigned char*)(&(m_stUiFactoryExt.stSSCsetting)), (unsigned char*)pValue, sizeof(MS_UI_FACTORY_SSC_SET));
    SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqlfactorydb);
    SQL_UI_Transaction sql_trans(pUiSqlfactorydb);

     //-------------------m_stFactoryExt.stSSCsetting---------------------
    {
        SQL_UI_SetU32(pUiSqlfactorydb, T_SSCAdjust, "Lvds_SscEnable",strCondition.c_str(),m_stUiFactoryExt.stSSCsetting.Lvds_SscEnable);
        SQL_UI_SetU32(pUiSqlfactorydb, T_SSCAdjust, "Miu_SscEnable",strCondition.c_str(),m_stUiFactoryExt.stSSCsetting.Miu_SscEnable);
        SQL_UI_SetU32(pUiSqlfactorydb, T_SSCAdjust, "Lvds_SscSpan",strCondition.c_str(),m_stUiFactoryExt.stSSCsetting.Lvds_SscSpan);
        SQL_UI_SetU32(pUiSqlfactorydb, T_SSCAdjust, "Lvds_SscStep",strCondition.c_str(),m_stUiFactoryExt.stSSCsetting.Lvds_SscStep);
        SQL_UI_SetU32(pUiSqlfactorydb, T_SSCAdjust, "Miu_SscSpan",strCondition.c_str(),m_stUiFactoryExt.stSSCsetting.Miu_SscSpan[0]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_SSCAdjust, "Miu_SscStep",strCondition.c_str(),m_stUiFactoryExt.stSSCsetting.Miu_SscStep[0]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_SSCAdjust, "Miu1_SscSpan",strCondition.c_str(),m_stUiFactoryExt.stSSCsetting.Miu_SscSpan[1]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_SSCAdjust, "Miu1_SscStep",strCondition.c_str(),m_stUiFactoryExt.stSSCsetting.Miu_SscStep[1]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_SSCAdjust, "Miu2_SscSpan",strCondition.c_str(),m_stUiFactoryExt.stSSCsetting.Miu_SscSpan[2]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_SSCAdjust, "Miu2_SscStep",strCondition.c_str(),m_stUiFactoryExt.stSSCsetting.Miu_SscStep[2]);
     }
}
//void MS_UI_System_Database::GetFactoryExtSetting_SSC2(void *pValue)

void UI_System_Database::GetFactoryExtSetting_6M30SSC(MS_UI_FACTORY_6M30SSC_SET *pValue)
{
    memcpy((unsigned char*)pValue, (unsigned char*)&(m_stUiFactoryExt.st6M30SSCsetting), sizeof(MS_UI_FACTORY_6M30SSC_SET));
}

void UI_System_Database::SetFactoryExtSetting_6M30SSC(MS_UI_FACTORY_6M30SSC_SET *pValue)
{
    memcpy((unsigned char*)(&(m_stUiFactoryExt.st6M30SSCsetting)), (unsigned char*)pValue, sizeof(MS_UI_FACTORY_6M30SSC_SET));
}

void UI_System_Database::GetFactoryVideoSetting(MS_UI_VIDEO *pstUiVideo, MAPI_INPUT_SOURCE_TYPE *penSrcType)
{
    int ColNum = 0;
    int ColIndex = 0;
    int PicNumIdx = 0;
    int ColorTempNumIdx = 0;
    char con[16] = {0};
    unsigned char u8Index = 0;

    if((pstUiVideo == NULL)||(penSrcType == NULL))
    {
        return;
    }
    u8Index = (unsigned char)*penSrcType;

    SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqldb);

    //-------------------m_pastUiVideo---------------------
    {
        snprintf(con, 16, "InputSrcType=%d", u8Index);//change Inputsource index to InputSrcType
        SQL_UI_LookupPre prepare(pUiSqldb, T_VideoSetting, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt)) && (ColIndex < ColNum))
        {
            pstUiVideo->picture = (EN_UI_PICTURE_MODE)SQL_UI_GetU32(prepare.pSqlstmt, "ePicture");
            pstUiVideo->subColor.u8SubBrightness = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8SubBrightness");
            pstUiVideo->subColor.u8SubContrast = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8SubContrast");
            pstUiVideo->arcType = (EN_UI_VIDEO_AR_Type)SQL_UI_GetU32(prepare.pSqlstmt, "enARCType");
            pstUiVideo->outputResolution = (EN_UI_DISPLAY_RES_TYPE)SQL_UI_GetU32(prepare.pSqlstmt, "fOutput_RES");
            pstUiVideo->tvSystemSetting = (EN_UI_VIDEO_OUT_VE_SYS)SQL_UI_GetU32(prepare.pSqlstmt, "tvsys");
            pstUiVideo->lastVideoStandardMode = (EN_UI_AVD_VideoStandardType)SQL_UI_GetU32(prepare.pSqlstmt, "LastVideoStandardMode");
            pstUiVideo->lastAudioStandardMode = (EN_UI_AUDIOMODE_TYPE_)SQL_UI_GetU32(prepare.pSqlstmt, "LastAudioStandardMode");
            pstUiVideo->dynamicContrast = (EN_UI_MS_Dynamic_Contrast)SQL_UI_GetU32(prepare.pSqlstmt, "eDynamic_Contrast");
            pstUiVideo->filmMode = (EN_UI_MS_FILM)SQL_UI_GetU32(prepare.pSqlstmt, "eFilm");
            pstUiVideo->tvFormat = (EN_UI_DISPLAY_TVFORMAT)SQL_UI_GetU32(prepare.pSqlstmt, "eTvFormat");

            pstUiVideo->enGameModeARCType = (mapi_video_datatype::MAPI_VIDEO_ARC_Type)SQL_UI_GetU32(prepare.pSqlstmt, "enGameModeARCType");
            pstUiVideo->enAutoModeARCType = (mapi_video_datatype::MAPI_VIDEO_ARC_Type)SQL_UI_GetU32(prepare.pSqlstmt, "enAutoModeARCType");
            pstUiVideo->enPcModeARCType = (mapi_video_datatype::MAPI_VIDEO_ARC_Type)SQL_UI_GetU32(prepare.pSqlstmt, "enPcModeARCType");
            pstUiVideo->bIsPcMode = (bool) SQL_UI_GetU32(prepare.pSqlstmt, "bIsPcMode");
        }
    }

    //-------------------m_pastVideo.astPicture---------------------
    {
        snprintf(con, 16, "InputSrcType=%d", u8Index);//change Inputsource index to InputSrcType
        SQL_UI_LookupPre prepare(pUiSqldb, T_PicMode_Setting, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        PicNumIdx = 0;
        while((SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt)) && (ColIndex < ColNum) && (PicNumIdx < PICTURE_NUMS))
        {
            pstUiVideo->astPicture[PicNumIdx].backlight = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8Backlight");
            pstUiVideo->astPicture[PicNumIdx].contrast = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8Contrast");
            pstUiVideo->astPicture[PicNumIdx].brightness = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8Brightness");
            pstUiVideo->astPicture[PicNumIdx].saturation = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8Saturation");
            pstUiVideo->astPicture[PicNumIdx].sharpness = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8Sharpness");
            pstUiVideo->astPicture[PicNumIdx].hue = (unsigned char)SQL_UI_GetU32(prepare.pSqlstmt, "u8Hue");
            pstUiVideo->astPicture[PicNumIdx].colorTemp = (EN_UI_COLOR_TEMP)SQL_UI_GetU32(prepare.pSqlstmt, "eColorTemp");
            pstUiVideo->astPicture[PicNumIdx].vibrantColour = (EN_UI_MS_PIC_ADV)SQL_UI_GetU32(prepare.pSqlstmt, "eVibrantColour");
            pstUiVideo->astPicture[PicNumIdx].perfectClear = (EN_UI_MS_PIC_ADV)SQL_UI_GetU32(prepare.pSqlstmt, "ePerfectClear");
            pstUiVideo->astPicture[PicNumIdx].dynamicContrast = (EN_UI_MS_PIC_ADV)SQL_UI_GetU32(prepare.pSqlstmt, "eDynamicContrast");
            pstUiVideo->astPicture[PicNumIdx].dynamicBacklight = (EN_UI_MS_PIC_ADV)SQL_UI_GetU32(prepare.pSqlstmt, "eDynamicBacklight");
            pstUiVideo->astPicture[PicNumIdx].eActiveBackLight = (EN_UI_MS_ACTIVE_BACKLIGHT)SQL_UI_GetU32(prepare.pSqlstmt, "eActiveBackLight");
            pstUiVideo->astPicture[PicNumIdx].eAutoBrightnessSensor = (EN_UI_MS_AUTO_BRIGHTNESS)SQL_UI_GetU32(prepare.pSqlstmt, "eAutoBrightnessSensor");
            PicNumIdx++;
        }
    }

    //-------------------m_pastVideo.eNRMode---------------------
    {
        snprintf(con, 16, "InputSrcType=%d", u8Index);//change Inputsource index to InputSrcType
        SQL_UI_LookupPre prepare(pUiSqldb, T_NRMode, ColNum, con);
        ColIndex = 1;//ColIndex 0 is _id
        ColorTempNumIdx = 0;
        while((SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt)) && (ColIndex<ColNum) && (ColorTempNumIdx < COLOR_TEMP_NUM))
        {
            pstUiVideo->noiseReductionMode[ColorTempNumIdx].eNR= (EN_UI_MS_NR)SQL_UI_GetU32(prepare.pSqlstmt, "eNR");
            pstUiVideo->noiseReductionMode[ColorTempNumIdx].eMPEG_NR= (EN_UI_MS_MPEG_NR)SQL_UI_GetU32(prepare.pSqlstmt, "eMPEG_NR");
            ColorTempNumIdx ++;
        }
    }
}

void UI_System_Database::GetFactoryAudioSetting(MS_UI_USER_SOUND_SETTING *pstSoundSetting)
{
    int ColNum = 0;
    int ColIndex = 0;
    int RowIndex =0;

    SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqldb);
    //-------------------m_stSoundSetting---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_SoundSetting, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            ColIndex = 1;
            pstSoundSetting->soundMode = (EN_UI_SOUND_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"SoundMode");
            pstSoundSetting->audysseyDynamicVolume = (EN_UI_AUDYSSEY_DYNAMIC_VOLUME_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"AudysseyDynamicVolume");
            pstSoundSetting->audysseyEq = (EN_UI_AUDYSSEY_EQ_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"AudysseyEQ");
            pstSoundSetting->surroundSoundMode = (EN_UI_SURROUND_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"SurroundSoundMode");
            pstSoundSetting->surround = (EN_UI_SURROUND_TYPE)SQL_UI_GetU32(prepear.pSqlstmt,"Surround");
            pstSoundSetting->enableAVC = (bool)SQL_UI_GetU32(prepear.pSqlstmt,"bEnableAVC");
            pstSoundSetting->volume = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Volume");
            pstSoundSetting->HPVolume = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"HPVolume");
            pstSoundSetting->balance = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Balance");
            pstSoundSetting->primaryFlag = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Primary_Flag");
            pstSoundSetting->soundAudioLanguage1 = (MEMBER_LANGUAGE)SQL_UI_GetU32(prepear.pSqlstmt,"enSoundAudioLan1");
            pstSoundSetting->soundAudioLanguage2 = (MEMBER_LANGUAGE)SQL_UI_GetU32(prepear.pSqlstmt,"enSoundAudioLan2");
            pstSoundSetting->muteFlag = (bool)SQL_UI_GetU32(prepear.pSqlstmt,"MUTE_Flag");
            pstSoundSetting->soundAudioChannel = (EN_UI_AUD_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"enSoundAudioChannel");
            pstSoundSetting->enableAd = (bool)SQL_UI_GetU32(prepear.pSqlstmt,"bEnableAD");
            pstSoundSetting->adVolume = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"ADVolume");
            pstSoundSetting->adOutput = (EN_UI_SOUND_AD_OUTPUT)SQL_UI_GetU32(prepear.pSqlstmt,"ADOutput");
            pstSoundSetting->enSPDIFMODE = (SPDIF_TYPE_)SQL_UI_GetU32(prepear.pSqlstmt,"enSPDIFMODE");
            pstSoundSetting->spdifDelay = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"SPDIF_Delay");
            pstSoundSetting->speakerdelay = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Speaker_Delay");
            pstSoundSetting->AudioHdmiType = (HDMI_TYPE_)SQL_UI_GetU32(prepear.pSqlstmt,"AudioHdmiType");
    
        }
    }
    //-------------------m_stUiSoundSetting.astSoundModeSetting[]---------------------
    {
        SQL_UI_LookupPre  prepear(pUiSqldb, T_SoundMode_Setting, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        RowIndex = 0;
        while((SQLITE_ROW == SQL_UI_Step(prepear.pSqlstmt)) && (ColIndex < ColNum))
        {
            ColIndex = 1;
            pstSoundSetting->astSoundModeSetting[RowIndex].bass = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Bass");
            pstSoundSetting->astSoundModeSetting[RowIndex].treble = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Treble");
            pstSoundSetting->astSoundModeSetting[RowIndex].eqBand1 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand1");
            pstSoundSetting->astSoundModeSetting[RowIndex].eqBand2 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand2");
            pstSoundSetting->astSoundModeSetting[RowIndex].eqBand3 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand3");
            pstSoundSetting->astSoundModeSetting[RowIndex].eqBand4 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand4");
            pstSoundSetting->astSoundModeSetting[RowIndex].eqBand5 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand5");
            pstSoundSetting->astSoundModeSetting[RowIndex].eqBand6 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand6");
            pstSoundSetting->astSoundModeSetting[RowIndex].eqBand7 = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"EqBand7");
            pstSoundSetting->astSoundModeSetting[RowIndex].userMode = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"UserMode");
            pstSoundSetting->astSoundModeSetting[RowIndex].balance = (unsigned char)SQL_UI_GetU32(prepear.pSqlstmt,"Balance");
            pstSoundSetting->astSoundModeSetting[RowIndex].enSoundAudioChannel = (EN_UI_AUD_MODE)SQL_UI_GetU32(prepear.pSqlstmt,"enSoundAudioChannel");
            RowIndex ++;
        }
        MSG_SQL_UI_DBG(printf("Row =%d\n",RowIndex));
    }
}

void UI_System_Database::GetLocationSetting(MS_UI_UserLocationSetting *pValue)
{
    int ColNum = 0;
    int ColIndex = 0;

    SQL_UI_Connect Connect(SQL_UI_DB_PATH, &pUiSqldb);
    //-------------------m_stUiSysSetting.stUserLocationSetting---------------------
    {
        SQL_UI_LookupPre prepare(pUiSqldb, T_UserLocationSetting, ColNum, NULL);
        ColIndex = 1;//ColIndex 0 is _id
        while((SQLITE_ROW == SQL_UI_Step(prepare.pSqlstmt)) && (ColIndex<ColNum))
        {
            m_stUiSysSetting.stUserLocationSetting.u16LocationNo = (unsigned int)SQL_UI_GetU32(prepare.pSqlstmt,"u16LocationNo");
            m_stUiSysSetting.stUserLocationSetting.s16ManualLongitude= (int)SQL_UI_GetU32(prepare.pSqlstmt,"s16ManualLongitude");
            m_stUiSysSetting.stUserLocationSetting.s16ManualLatitude = (int)SQL_UI_GetU32(prepare.pSqlstmt,"s16ManualLatitude");
        }
    }

    memcpy(pValue, (MS_UI_UserLocationSetting *)&(m_stUiSysSetting.stUserLocationSetting), sizeof(MS_UI_UserLocationSetting));
}

void UI_System_Database::SetLocationSetting(MS_UI_UserLocationSetting *pOrgValue)
{
    MS_UI_UserSystemSetting stOrgSysSetting;
    stOrgSysSetting = m_stUiSysSetting;

    memcpy(&m_stUiSysSetting.stUserLocationSetting, pOrgValue, sizeof(MS_UI_UserLocationSetting));

    SaveUiSysSetting(&stOrgSysSetting);
}

void UI_System_Database::SetCIDebugLevel(EN_UI_CI_FUNCTION enDebugIndex, unsigned char u8DebugLevel)
{
    m_stUiCISet.u8CIFunctionDebugLevel[enDebugIndex] = u8DebugLevel;
    SaveUiCISet();
}

unsigned char UI_System_Database::GetCIDebugLevel(EN_UI_CI_FUNCTION enDebugIndex)
{
    return m_stUiCISet.u8CIFunctionDebugLevel[enDebugIndex];
}

void UI_System_Database::SaveUiCISet(void)
{
    m_stUiCISet.u16CheckSum = UiCalCheckSum((unsigned char*) &m_stUiCISet, (unsigned int)sizeof(ST_UI_FACTORY_CI_SETTING));
    string strCondition = string("_id=0");
    SQL_UI_Connect Connect(SQL_UI_DB_FACTORY_PATH, &pUiSqlfactorydb);
    SQL_UI_Transaction sql_trans(pUiSqlfactorydb);
    {
#if (CI_PLUS_ENABLE == 1)
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "Credential_Mode",strCondition.c_str(),m_stUiCISet.enCredentialMode);
#endif
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "Performance_Monitor",strCondition.c_str(),m_stUiCISet.bPerformanceMonitor);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "RM_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_RM]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "APPINFO_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_APPINFO]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "CAS_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_CAS]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "HC_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_HC]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "DT_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_DT]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "MMI_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_MMI]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "LSC_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_LSC]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "CC_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_CC]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "HLC_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_HLC]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "CU_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_CU]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "OP_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_OP]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "SAS_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_SAS]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "APPMMI_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_APPMMI]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "PMT_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_PMT]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "HSS_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_HSS]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "AUTH_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_AUTH]);
        SQL_UI_SetU32(pUiSqlfactorydb, T_CIAdjust, "DEFAULT_Debug_Level",strCondition.c_str(),m_stUiCISet.u8CIFunctionDebugLevel[EN_UI_CI_FUNCTION_DEFAULT]);
     }
}

