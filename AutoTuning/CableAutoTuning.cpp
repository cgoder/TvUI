#include "AutoTuning/CableAutoTuning.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "skyscanapi/skyScanAtv.h"
#include "base/ccUtils.h"
#include "common/KeyBoard.h"
#include "ManualScan/DVBT_ManualScan.h"
#include "sources/SignalSources.h"
#include "AutoTuning/ChooseDialog.h"
#include "AutoTuning/CableType.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;
CableAutoTuning::CableAutoTuning()
{
	m_rootNode = nullptr;
	this->setName("CableAutoTuning");
	log("CableAutoTuning::CableAutoTuning");
#ifdef SCANTV
	m_scanApi = nullptr;
#endif
}
CableAutoTuning::~CableAutoTuning()
{
	delete m_btnData;
}
cocos2d::Layer* CableAutoTuning::creatLayer(Node* node,int type)
{
	//return SignalSources::creatLayer(node);
	//return DVBT_Manual_Scan::creatLayer(node);
	
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("CableAutoTuning");
		if (tuning) {
			return tuning;
		}
		else {
			log("CableAutoTuning:ceart");
			auto ptuning =  CableAutoTuning::create();
			ptuning->setSignalType(type);
			ptuning->initCableAutoTuning();
			node->addChild(ptuning);
			return ptuning;
		}
	}
	return nullptr;
}

void CableAutoTuning::initCableAutoTuning()
{
#ifdef SCANTV
	m_scanApi = skyScanUi::skyGetScanInstance(skyScanSourceType::SOURCE_TYPE_DVBC_S);
	(m_scanApi)->skyRegisterScanData(CableAutoTuning::tuningBack, this);
#endif
	this->removeChild(m_rootNode);
	auto rootNode = CSLoader::createNode("broadcast/ADVB_C.csb");
	rootNode->setName("ID_NODE_CHOOSETUNING");
	this->addChild(rootNode);
	m_rootNode = rootNode;

	setBtnFunc(rootNode, "ID_BUT_SCAN", CC_CALLBACK_2(CableAutoTuning::onBtnScan, this), nullptr);
#ifdef SCANTV
	m_scanParam->country = 1;
	//m_scanApi->skyScanSetCountryData(1);//init scan country
#endif
	setBtnFunc(rootNode, "ID_BUT_COUNTRY", CC_CALLBACK_2(CableAutoTuning::onBtnCountry, this), nullptr);

	skyFreqData freparam;
	freparam.modulation = S_MODULATION_MODE_QAM_AUTO;
	freparam.symbolRate = 0;
	freparam.networkid = 0;
	freparam.front_id = 0;
	freparam.freq = 0;
#ifdef SCANTV
	m_scanParam->freqdata = freparam;
//	m_scanApi->skySetFreParam(freparam, false);//init scan freparam
#endif

	setBtnFunc(rootNode, "ID_BUT_TYPE", CC_CALLBACK_2(CableAutoTuning::onBtnType, this), nullptr);

	m_btnData = new button_user_data;
	m_btnData->type = BUTTON_TYPE::TYPE_NUMS;
	m_btnData->index = 0;
	m_vecScope.push_back("All");
	m_vecScope.push_back("Free");
	m_btnData->data = (void*)&m_vecScope;
	setBtnFunc(rootNode, "ID_BUT_MODE", CC_CALLBACK_2(CableAutoTuning::onBtnScope, this), m_btnData);

	addKeyListener(CC_CALLBACK_2(CableAutoTuning::onKeyPressed, this), m_rootNode);

    
}
bool CableAutoTuning::init()
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



void CableAutoTuning::onBtnScan(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	Text* text = (Text*)m_rootNode->getChildByName("ID_BUT_MODE")->getChildByName("ID_TEXT_VALUE");
	std::string scope = text->getString();
#ifdef SCANTV
	if (scope == "All")
		m_scanParam->scanscope = skyScanScope::TV_FREE_SCRAMBLE;
	 //  m_scanApi->skySetScanScopeType(skyScanScope::TV_FREE_SCRAMBLE);
	else 
		m_scanParam->scanscope = skyScanScope::TV_FREE_ONLY;
		//m_scanApi->skySetScanScopeType(skyScanScope::TV_FREE_ONLY);
#endif


	text = (Text*)m_rootNode->getChildByName("ID_BUT_TYPE")->getChildByName("ID_TEXT_VALUE");
	std::string scantype = text->getString();
#ifdef SCANTV
	if (scantype == "Full")
		m_scanParam->autoscanmodel = skyScanModel::FULLSACN;
		//m_scanApi->skySetAutoScanModel(skyAutoScanModel::FULLSACN);
	else 
		m_scanParam->autoscanmodel = skyScanModel::AUTOSCAN;
		//m_scanApi->skySetAutoScanModel(skyAutoScanModel::AUTOSCAN);
#endif
	m_scanApi->skyDtvSetScanParam(*m_scanParam);
	initTuning();
}
void CableAutoTuning::onBtnCountry(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	vector<string> countryparam;
	countryparam.push_back("China");
	countryparam.push_back("Canada");
	countryparam.push_back("France");
#ifdef SCANTV
//	m_scanApi->skyDtvGetSatelliteParam(countryparam);
#endif
	int cellNums = countryparam.size();
	int rowNums = 6;
	int colNums = cellNums / 6 + 1;
	ChooseDialog* node = (ChooseDialog*)ChooseDialog::creatLayer(this, colNums, rowNums, cellNums, (Click_CallFun)(&CableAutoTuning::onCountryChoose));
	std::string str = ((Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE"))->getString();
	node->addTitle("Satellite");
	node->addNote("Please choose a Satellite for auto tuning.");
	node->addChooseStr("All", str.c_str());
	for (int i = 0; i < cellNums; i++)
	{
		std::string sate = countryparam.at(i);
		node->addChooseStr(sate.c_str(), str.c_str());
	}
	node->initTableView();
}

void CableAutoTuning::onBtnType(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	std::string str = ((Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE"))->getString();
	CableType* node = (CableType*)CableType::creatLayer(this, str, m_scanParam,(Click_CallFun)(&CableAutoTuning::onTypeChoose));
}
void CableAutoTuning::onBtnScope(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	button_user_data* data = (button_user_data*)m_btnFocused->getUserData();
	if (m_keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT) {
		if (data->index > 0)
		{
			data->index -= 1;
			std::vector<std::string> vec = *((std::vector<std::string>*)data->data);
			Text* text = (Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE");
			text->setString(vec.at(data->index));
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(false);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(true);
		}
	}
	else if (m_keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT)
	{
		if (data->index < (m_vecScope.size() - 1))
		{
			data->index += 1;
			Text* text = (Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE");
			std::vector<std::string> vec = *((std::vector<std::string>*)data->data);
			text->setString(vec.at(data->index));
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(true);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(false);
		}
	}
}
void CableAutoTuning::onCountryChoose(cocos2d::Node* node)
{
	ChooseDialog* dialog = dynamic_cast<ChooseDialog*>(node);
	if (dialog)
	{
		Text* text = (Text*)dialog->getFocusCell()->getChildByName("ID_TEXT_NAME");
		((Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE"))->setString(text->getString());
#ifdef SCANTV
		m_scanParam->country = dialog->getFocusIdx();
		//m_scanApi->skyScanSetCountryData(dialog->getFocusIdx());
#endif
	}
}
void CableAutoTuning::onTypeChoose(cocos2d::Node* node)
{
	Text* text = (Text*)node->getChildByName("ID_TEXT_TITLE");
	((Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE"))->setString(text->getString());
}
void CableAutoTuning::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	m_keyCode = keyCode;
	button_user_data* data = (button_user_data*)m_btnFocused->getUserData();
	if (data )
	{
		Touch touch;
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
			m_btnFocused->onTouchBegan(&touch, NULL);
			m_btnFocused->onTouchEnded(&touch, NULL);
			break;
		default:
			break;
		}
	}
	BtnFocusLayer::onKeyPressed(keyCode, unused_event);
}