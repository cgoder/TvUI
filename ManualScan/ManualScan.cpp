#include "ManualScan/ManualScan.h"
#include "tvplayer/tv_common.h"
cocos2d::Layer* Manual_Scan::creatLayer(Node* node)
{
	//skyScanSourceType sourcetype_tmp =get_source();
	skyTvMw* sourceInstance = skyTvMw::getInstance();
	SKYTV_INPUT_SOURCE_TYPE source = sourceInstance->getInputSource();
	//skyScanSourceType sourcetype_tmp = SOURCE_TYPE_DVBC_S;
	Layer* tuning = nullptr;
	switch (source)
	{
		

		case SKYTV_INPUT_SOURCE_ATV:
			tuning =ATV_Manual_Scan::creatLayer(node);
			break;
		case SKYTV_INPUT_SOURCE_DVBC:
		case SKYTV_INPUT_SOURCE_DVBC2:
			tuning=DVBC_Manual_Scan::creatLayer(node);
			break;
		case SKYTV_INPUT_SOURCE_DVBT:
		case SKYTV_INPUT_SOURCE_DVBT2:
			tuning = DVBT_Manual_Scan::creatLayer(node);
			break;

	}

	return tuning;

	

}