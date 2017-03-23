#include "AutoTuning/AutoTuning.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "skyscanapi/skyScanAtv.h"
#include "base/ccUtils.h"
#include "AutoTuning/TerreAutoTuning.h"
#include "AutoTuning/CableAutoTuning.h"
#include "AutoTuning/SateAutoTuning.h"
#include "AutoTuning/ATVAutoTuning.h"
#include "ManualScan/DVBT_ManualScan.h"
#include "tvplayer/tv_common.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;
AutoTuning::AutoTuning()
{
	m_rootNode = nullptr;
#ifdef SCANTV
	m_scanApi = nullptr;
#endif
	m_scanData.process = 0;
	m_scanData.data_count = 0;
	m_scanData.digitaltv_count = 0;
	m_scanData.analogtv_count = 0;
	m_scanData.scanstatus = skyScanStatus::STATUS_SKYSCAN_UNKNOW;
	m_scanParam = new skyScanParam;
	//memset(&m_scanData,0,sizeof(skyScanCallbackData));
}
AutoTuning::~AutoTuning()
{
#ifdef SCANTV
	m_scanApi->skyScanStop();
	skyScanUi::skyScanDestroyInstance();
	delete m_scanParam;
#endif
}
cocos2d::Layer* AutoTuning::creatLayer(cocos2d::Node* node,int signaltype)
{
#ifndef _WIN32
	SKYTV_INPUT_SOURCE_TYPE type = skyTvMw::getInstance()->getInputSource();
	switch (type)
	{
	case SKYTV_INPUT_SOURCE_DVBT:
		return TerreAutoTuning::creatLayer(node, 2);
		break;
	case SKYTV_INPUT_SOURCE_ATV:
		return ATVAutoTuning::creatLayer(node, 0);
		break;
	case SKYTV_INPUT_SOURCE_DVBC:
		return CableAutoTuning::creatLayer(node, 1);
		break;;
	case SKYTV_INPUT_SOURCE_DVBS:
		return SateAutoTuning::creatLayer(node, 3);
		break;
	default:
		return nullptr;
	}
#else
	SKYTV_INPUT_SOURCE_TYPE type = skyTvMw::getInstance()->getInputSource();
	//return DVBT_Manual_Scan::creatLayer(node);
	return CableAutoTuning::creatLayer(node,1);
	//return SateAutoTuning::creatLayer(node,3);
	return TerreAutoTuning::creatLayer(node,2);
	//return ATVAutoTuning::creatLayer(node,0);
#endif
}
void AutoTuning::initTuning()
{
	log("\n++init autotuing++\n");
//	this->removeChild(m_rootNode);
	m_rootNode->setUserData(m_btnFocused);

	auto rootNode = CSLoader::createNode("Tuning.csb");
	this->addChild(rootNode);
	m_rootNode = rootNode;
	if (m_signalType == 0)
	{
		setTextTitle(m_rootNode->getChildByName("ID_TEXT_FRE"), "ID_TEXT_VALUE", "ATV");
		setTextTitle(m_rootNode->getChildByName("ID_TEXT_DIG"), "ID_TEXT_TITLE", "TV");
		m_rootNode->getChildByName("ID_TEXT_TV")->setVisible(false);
		m_rootNode->getChildByName("ID_TEXT_OTHER")->setVisible(false);
		m_rootNode->getChildByName("ID_TEXT_RADIO")->setVisible(false);
	}
	else if (m_signalType == 1)
		setTextTitle(m_rootNode->getChildByName("ID_TEXT_FRE"), "ID_TEXT_VALUE", "DVB_C");
	else if (m_signalType == 2)
		setTextTitle(m_rootNode->getChildByName("ID_TEXT_FRE"), "ID_TEXT_VALUE", "DVB_T");
	else if (m_signalType == 3)
		setTextTitle(m_rootNode->getChildByName("ID_TEXT_FRE"), "ID_TEXT_VALUE", "DVB_S");

	m_btnFocused = nullptr;
	setBtnFunc(rootNode, "ID_BUT_STOP", CC_CALLBACK_2(AutoTuning::onBtnStop_Tuning, this), nullptr);

	addKeyListener(CC_CALLBACK_2(BtnFocusLayer::onKeyPressed, this), m_rootNode);
	
	log("\n++start schedule +\n");
	this->schedule(schedule_selector(AutoTuning::updataScanStatus), 1);
	//TODO register tuning progress back
#ifdef SCANTV
	m_scanApi->skyScanStart();
	//m_scanApi->skyAutoScanStart();
#endif

	
//TEST TODO
	/*
	if (m_signalType != 0)
		initTuning_Completed();
	else
        this->schedule(schedule_selector(AutoTuning::updataScanStatus), 1);
*/
}
void AutoTuning::updataDataCounts(const char* nodeName,int counts)
{
	char str[64] = { 0 };
	Text* text = (Text*)m_rootNode->getChildByName(nodeName)->getChildByName("ID_TEXT_VALUE");
	sprintf(str, "%d", counts);
	if (text)
	    text->setText(str);
}
void AutoTuning::updataScanStatus(float dt)
{
	//log("\n haha \n");
	skyScanCallbackData scandata = m_scanData;// m_scanApi->getScanData();
//	log("\n++m_scanData %d %d %d++\n",scandata.scanstatus,scandata.process,scandata.digitaltv_count);
		skyScanStatus scanstatus = scandata.scanstatus;
		if (scanstatus == skyScanStatus::STATUS_SKYSCAN_FAILED || scanstatus == skyScanStatus::STATUS_SKYSCAN_TIMEOUT)
		{
			this->unschedule(schedule_selector(AutoTuning::updataScanStatus));

		}
		else if (scanstatus == skyScanStatus::STATUS_SKYSCAN_TUNING_END)
		{
			//TODO 
			this->unschedule(schedule_selector(AutoTuning::updataScanStatus));
			initTuning_Completed();
			skyScanCallbackData scandata = m_scanData;// m_scanApi->getScanData();
			if (m_signalType == 0) {
				updataDataCounts("ID_TEXT_DIG", scandata.analogtv_count);
			}
			else {
				updataDataCounts("ID_TEXT_DIG", scandata.digitaltv_count + scandata.radio_count + scandata.data_count);
				updataDataCounts("ID_TEXT_TV", scandata.digitaltv_count);
				updataDataCounts("ID_TEXT_RADIO", scandata.radio_count);
				updataDataCounts("ID_TEXT_OTHER", scandata.data_count);
			}

		}
		else {
			LoadingBar* bar = (LoadingBar*)m_rootNode->getChildByName("ID_PROGRESS_TUNING");
			bar->setPercent(scandata.process);
			char str[64] = { 0 };
			sprintf(str, "%uKHz", scandata.current_freq);
			setTextTitle(m_rootNode->getChildByName("ID_TEXT_FRE"),"ID_TEXT_TITLE", str);
			if (m_signalType == 0) {
				updataDataCounts("ID_TEXT_DIG", scandata.analogtv_count);
			}
			else {
				updataDataCounts("ID_TEXT_DIG", scandata.digitaltv_count + scandata.radio_count + scandata.data_count);
				updataDataCounts("ID_TEXT_TV", scandata.digitaltv_count);
				updataDataCounts("ID_TEXT_RADIO", scandata.radio_count);
				updataDataCounts("ID_TEXT_OTHER", scandata.data_count);
			}
			sprintf(str, "Stop(%d%%)", scandata.process);
			setBtnTitle(m_rootNode,"ID_BUT_STOP", str);
		}
		
}

void AutoTuning::StopTuning()
{
	auto node = CSLoader::createNode("Dia_Stop_Tuning.csb");
	node->setPosition(Vec2(430,300));
	m_rootNode->addChild(node,1,"ID_LAYER_DIA_STOP");

	auto btnnode = node->getChildByName("ID_PAN_STOP");
	Button* btn = (Button*)node->getChildByName("ID_PAN_STOP")->getChildByName("ID_BUT_YES");
	m_btnFocusedStore = m_btnFocused;
	m_btnFocused = nullptr;
	setBtnFunc(btnnode, "ID_BUT_YES", CC_CALLBACK_2(AutoTuning::onBtnStop_Tuning_Confirm, this), nullptr);

	setBtnFunc(btnnode, "ID_BUT_NO", CC_CALLBACK_2(AutoTuning::onBtnStop_Tuning_Cancel, this), nullptr);

}

void AutoTuning::onBtnStop_Tuning(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	StopTuning();
}

void AutoTuning::onBtnStop_Tuning_Confirm(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	initTuning_Stoped();
	//TODO stop tuning interface
	log("###########################onBtnStop_Tuning_Confirm m_scanApi->skyScanStop###############");
#ifdef SCANTV
	m_scanApi->skyScanStop();
#endif
	this->unschedule(schedule_selector(AutoTuning::updataScanStatus));
}
void AutoTuning::onBtnStop_Tuning_Cancel(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	m_btnFocused = m_btnFocusedStore;
	m_btnTempFocused = m_btnFocused;
	m_rootNode->removeChildByName("ID_LAYER_DIA_STOP",true);
}
void AutoTuning::initTuning_Stoped()
{
	this->removeChild(m_rootNode);

	auto rootNode = CSLoader::createNode("Tuning_Stop.csb");
	this->addChild(rootNode);
	m_rootNode = rootNode;

	skyScanCallbackData scandata = m_scanData;// m_scanApi->getScanData();
	updataDataCounts("ID_TEXT_DIG", scandata.digitaltv_count + scandata.radio_count + scandata.data_count);
	updataDataCounts("ID_TEXT_TV", scandata.digitaltv_count);
	updataDataCounts("ID_TEXT_RADIO", scandata.radio_count);
	updataDataCounts("ID_TEXT_OTHER", scandata.data_count);

	m_btnFocused = nullptr;
	setBtnFunc(rootNode, "ID_BUT_STOP", CC_CALLBACK_2(AutoTuning::onBtnTuning_Close, this), nullptr);
	setBtnFunc(rootNode, "ID_BUT_SCAN", CC_CALLBACK_2(AutoTuning::onBtnTuning_Again, this), nullptr);
	
	addKeyListener(CC_CALLBACK_2(BtnFocusLayer::onKeyPressed, this), m_rootNode);
	//TODO init tuning data
}
void AutoTuning::onBtnTuning_Again(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	this->removeChild(m_rootNode);
	m_rootNode = this->getChildByName("ID_NODE_CHOOSETUNING");
	m_btnFocused = (Button*)m_rootNode->getUserData();
	m_btnTempFocused = m_btnFocused;

}
void AutoTuning::onBtnTuning_Close(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	this->removeChild(m_rootNode);
	this->getParent()->removeChild(this);
	
	//TODO close tuning
}
void AutoTuning::completeCountDown(float dt)
{
	if (m_countDown > 0)
	{
		m_countDown--;
		char str[64] = { 0 };
		sprintf(str,"Close(%ds)", m_countDown);
		setBtnTitle(m_rootNode,"ID_BUT_STOP",str);
	}
	else {
		this->unschedule(schedule_selector(AutoTuning::completeCountDown));
		this->getParent()->removeChild(this);
	}
}
//TODO 底层扫描结束回调，绘制完成UI
void AutoTuning::initTuning_Completed()
{
	this->removeChild(m_rootNode);
	auto rootNode = CSLoader::createNode("Tuning_Complete.csb");
	this->addChild(rootNode);
	m_rootNode = rootNode;
	if (m_signalType == 0)
	{
		setTextTitle(m_rootNode->getChildByName("ID_TEXT_FRE"), "ID_TEXT_VALUE", "ATV");
		setTextTitle(m_rootNode->getChildByName("ID_TEXT_DIG"), "ID_TEXT_TITLE", "TV");
		m_rootNode->getChildByName("ID_TEXT_TV")->setVisible(false);
		m_rootNode->getChildByName("ID_TEXT_OTHER")->setVisible(false);
		m_rootNode->getChildByName("ID_TEXT_RADIO")->setVisible(false);
	}
	else if (m_signalType == 1)
		setTextTitle(m_rootNode->getChildByName("ID_TEXT_FRE"), "ID_TEXT_VALUE", "DVB_C");
	else if (m_signalType == 2)
		setTextTitle(m_rootNode->getChildByName("ID_TEXT_FRE"), "ID_TEXT_VALUE", "DVB_T");
	else if (m_signalType == 3)
		setTextTitle(m_rootNode->getChildByName("ID_TEXT_FRE"), "ID_TEXT_VALUE", "DVB_S");
	Button* btn = (Button*)rootNode->getChildByName("ID_BUT_STOP");
	m_btnFocused = nullptr;
	setBtnFunc(rootNode, "ID_BUT_STOP", CC_CALLBACK_2(AutoTuning::onBtnTuning_Completed, this), nullptr);
	addKeyListener(CC_CALLBACK_2(BtnFocusLayer::onKeyPressed, this), m_rootNode);
	m_countDown = 5;
	this->schedule(schedule_selector(AutoTuning::completeCountDown), 1);
}

void AutoTuning::onBtnTuning_Completed(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	this->unschedule(schedule_selector(AutoTuning::completeCountDown));
	this->removeChild(m_rootNode);
	this->getParent()->removeChild(this);
	//TODO completed
}


void AutoTuning::tuningBack(skyScanCallbackData data, void* ptr)
{
	AutoTuning* tuning = (AutoTuning*)ptr;
	tuning->m_scanData.current_freq = data.current_freq;
	tuning->m_scanData.process = data.process;
	tuning->m_scanData.data_count = data.data_count;
	tuning->m_scanData.digitaltv_count = data.digitaltv_count;
	tuning->m_scanData.analogtv_count = data.analogtv_count;
	tuning->m_scanData.scanstatus = data.scanstatus;
		log("\n tuning->m_scanData.current_freq %d %d\n", tuning->m_scanData.current_freq, tuning->m_scanData.process);

}