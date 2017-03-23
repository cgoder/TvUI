#include "AutoTuning/ATVAutoTuning.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "skyscanapi/skyScanAtv.h"
#include "base/ccUtils.h"
#include "common/KeyBoard.h"
#include "ManualScan/DVBT_ManualScan.h"
#include "sources/SignalSources.h"
#include "AutoTuning/ChooseDialog.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;
ATVAutoTuning::ATVAutoTuning()
{
	m_rootNode = nullptr;
	this->setName("ATVAutoTuning");
	log("ATVAutoTuning::ATVAutoTuning");
#ifdef SCANTV
	m_scanApi = nullptr;
#endif
}
ATVAutoTuning::~ATVAutoTuning()
{
}
cocos2d::Layer* ATVAutoTuning::creatLayer(Node* node,int type)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("ATVAutoTuning");
		if (tuning) {
			return tuning;
		}
		else {
			log("ATVAutoTuning:ceart");
			auto ptuning =  ATVAutoTuning::create();
			ptuning->setSignalType(type);
			ptuning->initATVAutoTuning();
			node->addChild(ptuning);
			return ptuning;
		}
	}
	return nullptr;
}

void ATVAutoTuning::initATVAutoTuning()
{
#ifdef SCANTV
	m_scanApi = skyScanUi::skyGetScanInstance(skyScanSourceType::SOURCE_TYPE_ATV_S);
	(m_scanApi)->skyRegisterScanData(ATVAutoTuning::tuningBack, this);
#endif
	this->removeChild(m_rootNode);
	auto rootNode = CSLoader::createNode("ATV.csb");
	rootNode->setName("ID_NODE_CHOOSETUNING");
	this->addChild(rootNode);
	m_rootNode = rootNode;

	setBtnFunc(rootNode, "ID_BUT_SCAN", CC_CALLBACK_2(ATVAutoTuning::onBtnScan, this), nullptr);
	addKeyListener(CC_CALLBACK_2(ATVAutoTuning::onKeyPressed, this), m_rootNode);    
}
bool ATVAutoTuning::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	GLubyte op = this->getOpacity();
	m_btnFocusedStore = nullptr;
	
	return true;
}

void ATVAutoTuning::onBtnScan(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	m_scanParam->autoscanmodel = skyScanModel::AUTOSCAN;
	m_scanApi->skyDtvSetScanParam(*m_scanParam);
	initTuning();
}
