#include "AutoTuning/CableType.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "skyscanapi/skyScanAtv.h"
#include "base/ccUtils.h"
#include "common/KeyBoard.h"
#include "ManualScan/DVBT_ManualScan.h"
#include "sources/SignalSources.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;
CableType::CableType()
{
	m_selectNode = nullptr;
	m_rootNode = nullptr;
	this->setName("CableType");
	log("CableType::CableType");
	m_scanApi = nullptr;
}
CableType::~CableType()
{
	delete m_btnData[0];
	delete m_btnData[1];
	delete m_btnData[2];
}
cocos2d::Layer* CableType::creatLayer(Node* node, std::string &select, skyScanParam* params, Click_CallFun callFunc,int type)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("CableType");
		if (tuning) {
			return tuning;
		}
		else {
			log("CableType:ceart");
			auto ptuning =  CableType::create();			
			ptuning->initCableType();
			ptuning->setParams(select, params, callFunc, type);
			node->addChild(ptuning);
			return ptuning;
		}
	}
	return nullptr;
}

void CableType::setParams(std::string &select, skyScanParam* params, Click_CallFun callFunc, int type )
{
	m_scanParam = params;
	if (select == "Full")
	{
		Button* btn = (Button*)m_rootNode->getChildByName("ID_BUT_FULL")->getChildByName("ID_BUT_SEL");
		btn->setEnabled(false);
		m_selectNode = btn->getParent();
		setBtnEnable(m_rootNode, "ID_BUT_FRE", false);
		setBtnEnable(m_rootNode, "ID_BUT_NETID", false);
		setBtnEnable(m_rootNode, "ID_BUT_SYM", false);
	}
	else
	{
	    Button* btn = (Button*)m_rootNode->getChildByName("ID_BUT_NET")->getChildByName("ID_BUT_SEL");
		btn->setEnabled(false);
		m_selectNode = btn->getParent();
		btn = (Button*)m_rootNode->getChildByName("ID_BUT_NET");
		setBtnEnable(m_rootNode, "ID_BUT_FRE", true);
		setBtnEnable(m_rootNode, "ID_BUT_NETID", true);
		setBtnEnable(m_rootNode, "ID_BUT_SYM", true);
	}

	m_callFunc = callFunc;
	m_signalType = type;
}
void CableType::setBtnEnable(cocos2d::Node* rootNode, const char* nodeName, bool enable)
{
	Button*  btn = (Button*)rootNode->getChildByName(nodeName);
	if (btn) {
		if (enable)
		{
			btn->setEnabled(true);
			Vector<cocos2d::Node*> pChildren = btn->getChildren();
			for (Node *node : pChildren)
			{
				if (dynamic_cast<Text*>(node))
				{
					((Text*)node)->setColor(Color3B(91, 91, 91));
				}
				if (dynamic_cast<Button*>(node))
				{
					((Button*)node)->setHighlighted(false);
				}
			}
		}
		else
		{
			btn->setEnabled(false);
			Vector<cocos2d::Node*> pChildren = btn->getChildren();
			for (Node *node : pChildren)
			{
				if (dynamic_cast<Text*>(node))
				{
					((Text*)node)->setColor(Color3B(153, 153, 153));
				}
				if (dynamic_cast<Button*>(node))
				{
					((Button*)node)->setHighlighted(false);
				}
			}
		}
	}
}
void CableType::initCableType()
{
	m_scanApi = skyScanUi::skyGetScanInstance(skyScanSourceType::SOURCE_TYPE_DVBC_S);
	this->removeChild(m_rootNode);
	auto rootNode = CSLoader::createNode("broadcast/ADVB_C_Type.csb");
	this->addChild(rootNode);
	m_rootNode = rootNode;
	
	setBtnFunc(rootNode, "ID_BUT_OK", CC_CALLBACK_2(CableType::onBtnOK, this), nullptr);
	setBtnFunc(rootNode, "ID_BUT_NET", CC_CALLBACK_2(CableType::onBtnNet, this), nullptr);
	setBtnFunc(rootNode, "ID_BUT_FULL", CC_CALLBACK_2(CableType::onBtnFull, this), nullptr);

	m_btnData[0] = new button_user_data;
	m_btnData[0]->type = BUTTON_TYPE::TYPE_TEXT;
	m_btnData[0]->index = 0;
	m_btnData[0]->data = nullptr;
	setBtnFunc(rootNode, "ID_BUT_FRE", CC_CALLBACK_2(CableType::onBtnFre, this), m_btnData[0]);

	m_btnData[1] = new button_user_data;
	m_btnData[1]->type = BUTTON_TYPE::TYPE_TEXTNUMS;
	m_btnData[1]->index = 1;
	m_vecScope.push_back("0000");
	m_vecScope.push_back("Auto");
	m_btnData[1]->data = (void*)&m_vecScope;
	setBtnFunc(rootNode, "ID_BUT_NETID", CC_CALLBACK_2(CableType::onBtnNetId, this), m_btnData[1]); 

	m_btnData[2] = new button_user_data;
	m_btnData[2]->type = BUTTON_TYPE::TYPE_TEXTNUMS;
	m_btnData[2]->index = 1;
	m_btnData[2]->data = (void*)&m_vecScope;
	setBtnFunc(rootNode, "ID_BUT_SYM", CC_CALLBACK_2(CableType::onBtnSym, this), m_btnData[2]);

	addKeyListener(CC_CALLBACK_2(CableType::onKeyPressed, this), m_rootNode);

    
}
bool CableType::init()
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

void CableType::onBtnOK(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	Button* network = (Button*)m_rootNode->getChildByName("ID_BUT_NET")->getChildByName("ID_BUT_SEL");
	if (!network->isEnabled())
	{
		//skyFreqData freData;
		Text* text = (Text*)m_rootNode->getChildByName("ID_BUT_FRE")->getChildByName("ID_TEXT_VALUE");
		std::string fre = text->getString();
		m_scanParam->freqdata.freq = std::stoi(fre);

		text = (Text*)m_rootNode->getChildByName("ID_BUT_NETID")->getChildByName("ID_TEXT_VALUE");
		std::string netid = text->getString();
		if (netid == "Auto")
			netid = "0";
		m_scanParam->freqdata.networkid = std::stoi(netid);

		text = (Text*)m_rootNode->getChildByName("ID_BUT_SYM")->getChildByName("ID_TEXT_VALUE");
		std::string symbol = text->getString();
		if (symbol == "Auto")
			symbol = "0";
		m_scanParam->freqdata.symbolRate = std::stoi(symbol);
		//m_scanApi->skySetFreParam(freData,false);
		
	}


	if (m_callFunc)
		(this->getParent()->*m_callFunc)(m_selectNode);
	this->getParent()->removeChild(this);
}
void CableType::onBtnFull(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{	
	Button* btn = (Button*)m_rootNode->getChildByName("ID_BUT_FULL")->getChildByName("ID_BUT_SEL");
	btn->setEnabled(false);
	m_selectNode = btn->getParent();
	btn = (Button*)m_rootNode->getChildByName("ID_BUT_NET")->getChildByName("ID_BUT_SEL");
	btn->setEnabled(true);
	setBtnEnable(m_rootNode, "ID_BUT_FRE", false);
	setBtnEnable(m_rootNode, "ID_BUT_NETID", false);
	setBtnEnable(m_rootNode, "ID_BUT_SYM", false);
}
void CableType::onBtnNet(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	Button* btn = (Button*)m_rootNode->getChildByName("ID_BUT_NET")->getChildByName("ID_BUT_SEL");
	btn->setEnabled(false);
	m_selectNode = btn->getParent();
	btn = (Button*)m_rootNode->getChildByName("ID_BUT_FULL")->getChildByName("ID_BUT_SEL");
	btn->setEnabled(true);
	setBtnEnable(m_rootNode, "ID_BUT_FRE", true);
	setBtnEnable(m_rootNode, "ID_BUT_NETID", true);
	setBtnEnable(m_rootNode, "ID_BUT_SYM", true);
}
void CableType::onBtnFre(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	button_user_data* data = (button_user_data*)m_btnFocused->getUserData();
	data->text = "";
}
void CableType::onBtnNetId(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
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
			if (data->index == 0)
				data->text = "";
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
void CableType::onBtnSym(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
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
			if (data->index == 0)
				data->text = "";
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
void CableType::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	m_keyCode = keyCode;
	button_user_data* data = (button_user_data*)m_btnFocused->getUserData();
	if (data)
	{
		Touch touch;
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
			if (data->type == BUTTON_TYPE::TYPE_TEXT || data->type == BUTTON_TYPE::TYPE_TEXTNUMS)
			{
				if (data->index == 0)
				{
					if (data->text.size() > 0)
					{
						data->text.pop_back();
						this->setTextTitle(m_btnFocused, "ID_TEXT_VALUE", data->text.c_str());
					}					
				}
			}
			if (data->type != BUTTON_TYPE::TYPE_TEXT)
			{
				m_btnFocused->onTouchBegan(&touch, NULL);
				m_btnFocused->onTouchEnded(&touch, NULL);
			}
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
			if (data->type != BUTTON_TYPE::TYPE_TEXT)
			{
				m_btnFocused->onTouchBegan(&touch, NULL);
				m_btnFocused->onTouchEnded(&touch, NULL);
			}
			break;
		default:
			break;
		}

		if (keyCode <= cocos2d::EventKeyboard::KeyCode::KEY_9 && keyCode >= cocos2d::EventKeyboard::KeyCode::KEY_0)
		{
			unused_event->stopPropagation();
			if (data->type == BUTTON_TYPE::TYPE_TEXT || data->type == BUTTON_TYPE::TYPE_TEXTNUMS)
			{
				if (data->index == 0)
				{
					data->text += std::to_string((int)keyCode - 76);
					this->setTextTitle(m_btnFocused,"ID_TEXT_VALUE", data->text.c_str());
				}
			}
		}

	}
	
	BtnFocusLayer::onKeyPressed(keyCode, unused_event);
}
