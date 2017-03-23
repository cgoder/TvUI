#ifndef _CCPVRMANAGER_H
#define _CCPVRMANAGER_H

#include <stdint.h>

using std::string;

typedef struct {
    string filename;
    bool isRecording;
    int32_t key;
    uint32_t recordStartTime;
}CCPvrFileInfo;

class PvrManager;
class CCPvrManager {
private:
    static CCPvrManager* mPvrManager;
    CCPvrManager();
    ~CCPvrManager();		
public:
    static CCPvrManager* getInstance(); 
    static void destoryInstance();
    
    int32_t startPlayback(string filename);
    void pausePlayback();
    void resumePlayback();
    void stopPlayback();

    void stopTimeShiftPlayback();
    int32_t startTimeShiftPlayback();
    void setTimeShiftFileSize(int64_t timeShiftFileSizeInKB);

    int32_t seektoPlaybackTime(uint32_t Seconds);
    int32_t isPlaybacking();
    int32_t isPlaybackParentalLock();
    int32_t isPlaybackPaused();
    void    getCurPlaybackFileName(string &filename);
    int32_t    getCurPlaybackTime(); //Seconds
    int32_t getRecordedFileDurationTime(string fileName);//Seconds

    int32_t startRecord();
    void stopRecord();

    int32_t startTimeShift();
    void stopTimeShift();

    void pauseRecord();
    void resumeRecord();

    void        getCurRecordingFileName(string &filename);
    int32_t    getCurRecordTime();
    int32_t     getEstimateRecordRemainingTime();
    int32_t     isRecording();
    int32_t     isRecordPaused();
    int32_t     isTimeShift();    
    int32_t     getPvrFileNumber();
    void        getPvrFileInfo(int32_t index, CCPvrFileInfo &info);
    void        getFileServiceName(string fileName, string &serviceName);
    void        getFileEventName(string fileName, string &EventName);
    void        getFileEventDesc(string fileName, string &strDesc);
    int32_t     setPvrParams(string mountpath, int16_t fsType);
    void        getPvrMountPath(string &mountpath);
private:
    PvrManager* mInterface;     
};

#endif
