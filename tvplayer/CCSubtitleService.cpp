#include <stdio.h>
#include "CCSubtitleService.h"

CCSubtitleService* CCSubtitleService::mSubtitleService = NULL;
CCSubtitleService* CCSubtitleService::getInstance()
{
    if (mSubtitleService == NULL) {
        mSubtitleService = new CCSubtitleService();
    }
    return mSubtitleService;
}

void CCSubtitleService::destoryInstance(void)
{
    if (mSubtitleService != NULL) {
        delete mSubtitleService;
        mSubtitleService = NULL;            
    }
}

CCSubtitleService::CCSubtitleService()
{  
}

CCSubtitleService::~CCSubtitleService()
{
  
}

void CCSubtitleService::getSubtitleInfo(CCDtvSubtitleInfo &ccSubtitleInfo)
{

}

bool CCSubtitleService::openSubtitle(int index)
{
}

bool CCSubtitleService::closeSubtitle()
{
}

