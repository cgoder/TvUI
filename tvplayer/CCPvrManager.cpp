#include <stdio.h>
#include <string>
#include "CCPvrManager.h"

CCPvrManager* CCPvrManager::mPvrManager = NULL;
CCPvrManager* CCPvrManager::getInstance()
{
    if (mPvrManager == NULL) {
        mPvrManager = new CCPvrManager();
    }
    return mPvrManager;
}

void CCPvrManager::destoryInstance()
{
    if (mPvrManager) {
        delete mPvrManager;
        mPvrManager = NULL;
    }
    //if (mPvrManager == NULL) {
    //    mPvrManager = new CCPvrManager();
    //}    
}


CCPvrManager::CCPvrManager()
{  
}

CCPvrManager::~CCPvrManager()
{    
}

int32_t CCPvrManager::startPlayback(string filename)
{

    return 0;
}

void CCPvrManager::pausePlayback()
{
}

void  CCPvrManager::resumePlayback()
{

}

void CCPvrManager::stopPlayback()
{

}

int32_t CCPvrManager::seektoPlaybackTime(uint32_t Seconds)
{
    return 0;
}

int32_t CCPvrManager::isPlaybacking()
{
    return 0;
}

int32_t CCPvrManager::isPlaybackPaused()
{
    return 0;
}

int32_t CCPvrManager::isPlaybackParentalLock()
{
    return 0;
}

void  CCPvrManager::getCurPlaybackFileName(string &filename)
{

}

int32_t CCPvrManager::getCurPlaybackTime()
{
    return 0;
}

int32_t CCPvrManager::getRecordedFileDurationTime(string fileName)
{
    return 1920;//s
}

int32_t CCPvrManager::startRecord()
{
    return 0;
}

void CCPvrManager::stopRecord()
{
}

int32_t CCPvrManager::startTimeShift()
{
    return 0;
}

void CCPvrManager::stopTimeShift()
{
}

void CCPvrManager::pauseRecord()
{
}

void CCPvrManager::resumeRecord()
{

}

void CCPvrManager::getCurRecordingFileName(string &filename)
{
}

int32_t CCPvrManager::getCurRecordTime()
{
    return 0;
}

int32_t CCPvrManager::getEstimateRecordRemainingTime()
{
    return 0;
}

int32_t CCPvrManager::isRecording()
{

    return 0;
}

int32_t CCPvrManager::isRecordPaused()
{
    return 0;
}

int32_t CCPvrManager::isTimeShift()
{

    return 0;
}

int32_t CCPvrManager::getPvrFileNumber()
{
    return 8;
}

void CCPvrManager::getPvrFileInfo(int32_t index, CCPvrFileInfo &info)
{
	info.filename = "Recoded file";
    info.isRecording = false;
    info.key = 0;
    info.recordStartTime = 168;//s?    
	
}

void CCPvrManager::getFileServiceName(string fileName, string &serviceName)
{
	serviceName = "Recoded channel";
}

void CCPvrManager::getFileEventName(string fileName, string &EventName)
{
	EventName = "Recoded programe";
}

void CCPvrManager::getFileEventDesc(string fileName, string &strDesc)
{

}


int32_t CCPvrManager::setPvrParams(string mountpath, int16_t fsType)
{

    return 0;
}

void CCPvrManager::getPvrMountPath(string &mountpath)
{
 
}

void CCPvrManager::setTimeShiftFileSize(int64_t timeShiftFileSizeInKB)
{
}

void CCPvrManager::stopTimeShiftPlayback()
{
}

int32_t CCPvrManager::startTimeShiftPlayback()
{
	return 0;    
}

