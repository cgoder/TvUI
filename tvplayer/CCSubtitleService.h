#ifndef __CCSUBTITLESERVICE_H__
#define __CCSUBTITLESERVICE_H__

#include "tv_common.h"
#include <stdio.h>
#include <stdint.h>

#define MAX_TTXINFO_NUM 12
#define MAX_SUBTITLEINFO_NUM 12
#define MAX_SERVICE_NUM (MAX_TTXINFO_NUM + MAX_SUBTITLEINFO_NUM)

/// the struct of the menu subtitle for UI reference
typedef struct
{
    /// the subtitle language
    uint32_t eLanguage;
    /// the subtitle type
    uint32_t  enSubtitleType;
    /// how many subtitle services it refers
    uint8_t  u8RefCount;
    /// the  ISO 639 subtitle string code
    uint8_t  StringCodes[4];
}CCMenuSubtitleService;


typedef struct
{
    /// subtitle services informaion
    CCMenuSubtitleService m_pSubtitle[MAX_SERVICE_NUM];
    /// subtitle current index
    int32_t currentSubtitleIndex;
    /// subtitle services number
    int32_t subtitleServiceNumber;
    /// subtitle on or off
    bool subtitleOn;    
}CCDtvSubtitleInfo;

class SubtitleManager;
class CCSubtitleService
{
private:
    static CCSubtitleService* mSubtitleService;
    CCSubtitleService();
    ~CCSubtitleService();	
		
public:
    static CCSubtitleService* getInstance();    
    static void destoryInstance(void);
    //CC
		void getSubtitleInfo(CCDtvSubtitleInfo &DSubtitleInfo);		
		bool openSubtitle(int index);
		bool closeSubtitle();
private:
		SubtitleManager* pSubtitleManager;
};


#endif //__CCSUBTITLE_H__
