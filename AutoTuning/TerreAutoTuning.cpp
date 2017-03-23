#include "AutoTuning/TerreAutoTuning.h"
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
TerreAutoTuning::TerreAutoTuning()
{
	m_rootNode = nullptr;
	this->setName("TerreAutoTuning");
	log("TerreAutoTuning::TerreAutoTuning");
#ifdef SCANTV
	m_scanApi = nullptr;
#endif
}
TerreAutoTuning::~TerreAutoTuning()
{
}
cocos2d::Layer* TerreAutoTuning::creatLayer(Node* node,int type)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("TerreAutoTuning");
		if (tuning) {
			return tuning;
		}
		else {
			log("TerreAutoTuning:ceart");
			auto ptuning =  TerreAutoTuning::create();
			ptuning->setSignalType(type);
			ptuning->initTerreAutoTuning();
			node->addChild(ptuning);
			return ptuning;
		}
	}
	return nullptr;
}

void TerreAutoTuning::initTerreAutoTuning()
{
#ifdef SCANTV
	m_scanApi = skyScanUi::skyGetScanInstance(skyScanSourceType::SOURCE_TYPE_DVBT_S);
	(m_scanApi)->skyRegisterScanData(TerreAutoTuning::tuningBack, this);
#endif
	this->removeChild(m_rootNode);
	auto rootNode = CSLoader::createNode("broadcast/ADVB_T.csb");
	rootNode->setName("ID_NODE_CHOOSETUNING");
	this->addChild(rootNode);
	m_rootNode = rootNode;

	setBtnFunc(rootNode, "ID_BUT_SCAN", CC_CALLBACK_2(TerreAutoTuning::onBtnScan, this), nullptr);
	setBtnFunc(rootNode, "ID_BUT_COUNTRY", CC_CALLBACK_2(TerreAutoTuning::onBtnCountry, this), nullptr);
	//setBtnFunc(rootNode, "ID_BUT_TYPE", CC_CALLBACK_2(TerreAutoTuning::onBtnType, this), nullptr);

	m_btnData = new button_user_data;
	m_btnData->type = BUTTON_TYPE::TYPE_NUMS;
	m_btnData->index = 0;
	m_vecScope.push_back("All");
	m_vecScope.push_back("Free");
	m_btnData->data = (void*)&m_vecScope;
	setBtnFunc(rootNode, "ID_BUT_MODE", CC_CALLBACK_2(TerreAutoTuning::onBtnScope, this), m_btnData);

	addKeyListener(CC_CALLBACK_2(TerreAutoTuning::onKeyPressed, this), m_rootNode);

    
}
bool TerreAutoTuning::init()
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



void TerreAutoTuning::onBtnScan(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	Text* text = (Text*)m_rootNode->getChildByName("ID_BUT_MODE")->getChildByName("ID_TEXT_VALUE");
	std::string scope = text->getString();
#ifdef SCANTV
	if (scope == "All")
		m_scanParam->scanscope = skyScanScope::TV_FREE_SCRAMBLE;
	  // m_scanApi->skySetScanScopeType(skyScanScope::TV_FREE_SCRAMBLE);
	else 
		m_scanParam->scanscope = skyScanScope::TV_FREE_ONLY;
	//	m_scanApi->skySetScanScopeType(skyScanScope::TV_FREE_ONLY);
#endif
	m_scanParam->country =50;
	m_scanParam->autoscanmodel = skyScanModel::AUTOSCAN;
	m_scanApi->skyDtvSetScanParam(*m_scanParam);
	initTuning();
}
void TerreAutoTuning::onBtnCountry(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	vector<string> countryparam;
	countryparam.push_back("China");
	countryparam.push_back("Canada");
	countryparam.push_back("France");
	//m_scanApi->skyDtvGetSatelliteParam(countryparam);
	int cellNums = countryparam.size();
	int rowNums = 6;
	int colNums = cellNums / 6 + 1;
	ChooseDialog* node = (ChooseDialog*)ChooseDialog::creatLayer(this, colNums, rowNums, cellNums, (Click_CallFun)(&TerreAutoTuning::onCountryChoose));
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

void TerreAutoTuning::onBtnType(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	std::string str = ((Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE"))->getString();
}
void TerreAutoTuning::onBtnScope(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
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
void TerreAutoTuning::onCountryChoose(cocos2d::Node* node)
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
void TerreAutoTuning::onTypeChoose(cocos2d::Node* node)
{
	Text* text = (Text*)node->getChildByName("ID_TEXT_TITLE");
	((Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE"))->setString(text->getString());
}
void TerreAutoTuning::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
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