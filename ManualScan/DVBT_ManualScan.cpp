#include "ManualScan/DVBT_ManualScan.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "common/KeyBoard.h"

DVBT_Manual_Scan::DVBT_Manual_Scan()
{
	this->setName("DVBT_Manual_Scan");
	log("DVBT_Manual_Scan");
	memset(&m_scanData, 0, sizeof(skyScanCallbackData));
	m_scanApi = skyScanUi::skyGetScanInstance(skyScanSourceType::SOURCE_TYPE_DVBT_S /*SOURCE_TYPE_DVBT_S*/);
	(m_scanApi)->skyRegisterScanData(DVBT_Manual_Scan::tuningBack, this);
	m_scanParam.autoscanmodel = skyScanModel::MANUALSCAN;
}

DVBT_Manual_Scan::~DVBT_Manual_Scan()
{
	delete m_btnData[0];
	delete m_btnData[1];
	delete m_btnData[2];
	skyScanUi::skyScanDestroyInstance();
}

cocos2d::Layer* DVBT_Manual_Scan::creatLayer(Node* node)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("DVBT_Manual_Scan");
		if (tuning) {
			return tuning;
		}
		else {
			log("DVBT_Manual_Scan:create");
			auto pRet = DVBT_Manual_Scan::create();
			node->addChild(pRet);
			return pRet;
		}
	}
	return nullptr;
}


// on "init" you need to initialize your instance
bool DVBT_Manual_Scan::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MDVB_T.csb");
	rootNode->setName("ID_LAYER_DVBT_SET");
    addChild(rootNode);	
	m_rootNode = rootNode;
	Size size = rootNode->getContentSize();
	this->setContentSize(size);
	this->setPosition(Vec2(1920 / 2 - size.width / 2, 1080 / 2 - size.height / 2));

	m_btnFocused = nullptr;

	setBtnFunc(rootNode,"ID_BUT_YES", CC_CALLBACK_2(DVBT_Manual_Scan::onBtnScan, this), nullptr);

	setBtnFunc(rootNode, "ID_BUT_NO", CC_CALLBACK_2(DVBT_Manual_Scan::onBtnCancel, this), nullptr);
	m_btnData[0] = new button_user_data;
	m_btnData[1] = new button_user_data;
	m_btnData[2] = new button_user_data;

	m_btnData[0]->type = BUTTON_TYPE::TYPE_NUMS;
	m_btnData[0]->index = 0;
	m_vecScope.push_back("All");
	m_vecScope.push_back("Free");
	m_btnData[0]->data = (void*)&m_vecScope;
	setBtnFunc(rootNode, "ID_BUT_SCOPE", CC_CALLBACK_2(DVBT_Manual_Scan::onBtnScope, this) , m_btnData[0]);

	m_btnData[1]->type = BUTTON_TYPE::TYPE_CLICK;
	m_btnData[1]->index = 0;
	m_scanApi->skyGetFreTable(vec_Freq);
	m_btnData[1]->data = (void*)&vec_Freq;
	//chushihua TODO
	skyFreqData fredata = vec_Freq.at(0);
	char strtitle[64] = { 0 };
	Text* text = (Text*)m_rootNode->getChildByName("ID_BUT_FREID")->getChildByName("ID_TEXT_VALUE");
	sprintf(strtitle, "%d", fredata.front_id);
	text->setString(strtitle);
	text = (Text*)m_rootNode->getChildByName("ID_BUT_FRE")->getChildByName("ID_TEXT_VALUE");
	sprintf(strtitle, "%d", fredata.freq);
	text->setString(strtitle);
	setScanFreParams();

	setBtnFunc(rootNode, "ID_BUT_FREID", CC_CALLBACK_2(DVBT_Manual_Scan::onBtnFreid, this) , m_btnData[1]);

	m_btnData[2]->type = BUTTON_TYPE::TYPE_CLICK;
	m_btnData[2]->index = 0;
	m_vecBand.push_back("5M");
	m_vecBand.push_back("6M");
	m_vecBand.push_back("7M");
	m_vecBand.push_back("8M");
	m_btnData[2]->data =(void*) &m_vecBand;
	setBtnFunc(rootNode, "ID_BUT_BAND", CC_CALLBACK_2(DVBT_Manual_Scan::onBtnBand, this) , m_btnData[2]);	
	addKeyListener(CC_CALLBACK_2(DVBT_Manual_Scan::onKeyPressed, this), rootNode);
    return true;
}
void DVBT_Manual_Scan::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	m_keyCode = keyCode;	
	void* data = m_btnFocused->getUserData();
	if (data)
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

void DVBT_Manual_Scan::onBtnScope(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	button_user_data* data = (button_user_data*)m_btnFocused->getUserData();
	if (m_keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT) {
		if (data->index > 0)
		{
			data->index -= 1;
			Text* text =(Text*) m_btnFocused->getChildByName("ID_TEXT_VALUE");
			text->setString(m_vecScope.at(data->index));
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(false);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(true);
			setScanScope();
		}
	}
	else if (m_keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT)
	{
		if (data->index < (m_vecScope.size() - 1))
		{
			data->index += 1;
			Text* text = (Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE");
			text->setString(m_vecScope.at(data->index));
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(true);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(false);
			setScanScope();
		}
	}
}
void DVBT_Manual_Scan::onBtnBand(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	button_user_data* data = (button_user_data*)m_btnFocused->getUserData();
	if (m_keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT) {
		if (data->index > 0)
		{
			data->index -= 1;
			Text* text = (Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE");
			text->setString(m_vecBand.at(data->index));
			Button* btn =(Button*) m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(false);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(true);
			setScanBand();
		}
	}
	else if (m_keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT)
	{
		if (data->index < (m_vecBand.size() - 1))
		{
			data->index += 1;
			Text* text = (Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE");
			text->setString(m_vecBand.at(data->index));
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(true);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(false);
			setScanBand();
		}
	}
}
void DVBT_Manual_Scan::setScanFreParams()
{
	Text* text = (Text*)m_rootNode->getChildByName("ID_BUT_FREID")->getChildByName("ID_TEXT_VALUE");
	std::string freid = text->getString();

	text = (Text*)m_rootNode->getChildByName("ID_BUT_FRE")->getChildByName("ID_TEXT_VALUE");
	std::string fre = text->getString();

	skyFreqData freData;
	freData.front_id = std::stoi(freid);
	freData.freq = std::stoi(fre);
	m_scanParam.freqdata = freData;
	//m_scanApi->skySetFreParam(freData, false);
}
void DVBT_Manual_Scan::onBtnFreid(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
		bool deal = false;
		button_user_data* data = (button_user_data*)m_btnFocused->getUserData();
		char strtitle[64] = { 0 };
		if (m_keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT) {
			if (data->index > 0)
			{
				data->index -= 1;
				deal = true;
				Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
				btn->setHighlighted(false);
				btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
				btn->setHighlighted(true);
			}
		}
		else if (m_keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT)
		{
			int max = vec_Freq.size() - 1;
			if (data->index < max)
			{
				data->index += 1;
				deal = true;
				Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
				btn->setHighlighted(true);
				btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
				btn->setHighlighted(false);
			}
		}
		if (deal) {
			skyFreqData fredata = vec_Freq.at(data->index);
			sprintf(strtitle, "%d", fredata.front_id);
			Text* text = (Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE");
			text->setString(strtitle);
			text = (Text*)m_btnFocused->getParent()->getChildByName("ID_BUT_FRE")->getChildByName("ID_TEXT_VALUE");
			sprintf(strtitle, "%d", fredata.freq);
			text->setString(strtitle);
			setScanFreParams();
		}
}
void DVBT_Manual_Scan::setScanBand()
{
	Text* text = (Text*)m_rootNode->getChildByName("ID_BUT_BAND")->getChildByName("ID_TEXT_VALUE");
	std::string band = text->getString();
	if (band == "5M")
		m_scanParam.frebindwith = skyFreBindWith::DTV_BINDWITH_5M;
	    //m_scanApi->skySetScanBandWidth(skyFreBindWith::DTV_BINDWITH_5M);
	else if (band == "6M")
		m_scanParam.frebindwith = skyFreBindWith::DTV_BINDWITH_6M;
		//m_scanApi->skySetScanBandWidth(skyFreBindWith::DTV_BINDWITH_6M);
	else if (band == "7M")
		m_scanParam.frebindwith = skyFreBindWith::DTV_BINDWITH_7M;
		//m_scanApi->skySetScanBandWidth(skyFreBindWith::DTV_BINDWITH_7M);
	else 
		m_scanParam.frebindwith = skyFreBindWith::DTV_BINDWITH_8M;
		//m_scanApi->skySetScanBandWidth(skyFreBindWith::DTV_BINDWITH_8M);
}
void DVBT_Manual_Scan::setScanScope()
{
	Text* text = (Text*)m_rootNode->getChildByName("ID_BUT_SCOPE")->getChildByName("ID_TEXT_VALUE");
	std::string scope = text->getString();
	if (scope == "All")
		m_scanParam.scanscope = skyScanScope::TV_FREE_SCRAMBLE;
		//m_scanApi->skySetScanScopeType(skyScanScope::TV_FREE_SCRAMBLE);
	else
		m_scanParam.scanscope = skyScanScope::TV_FREE_ONLY;
		//m_scanApi->skySetScanScopeType(skyScanScope::TV_FREE_ONLY);
}
void DVBT_Manual_Scan::onBtnCancel(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	this->unschedule(schedule_selector(DVBT_Manual_Scan::completeCountDown));
	this->getParent()->removeChild(this);
}
void DVBT_Manual_Scan::onBtnScan(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	this->removeAllChildren();
	auto rootNode = CSLoader::createNode("MTuning.csb");
	addChild(rootNode);
	m_rootNode = rootNode;
	m_btnFocused = nullptr;
	setBtnFunc(rootNode, "ID_BUT_NO", CC_CALLBACK_2(DVBT_Manual_Scan::onBtnCancel, this), nullptr);
	addKeyListener(CC_CALLBACK_2(BtnFocusLayer::onKeyPressed, this), m_rootNode);
	//TODO ManualScan
	m_scanApi->skyDtvSetScanParam(m_scanParam);
	m_scanApi->skyScanStart();
	//m_scanApi->skyAutoScanStart();
	this->schedule(schedule_selector(DVBT_Manual_Scan::updataScanStatus), 1);
}
void DVBT_Manual_Scan::updataDataCounts(const char* nodeName, int counts)
{
	char str[64] = { 0 };
	Text* text = (Text*)m_rootNode->getChildByName(nodeName)->getChildByName("ID_TEXT_VALUE");
	sprintf(str, "%d", counts);
	if (text)
		text->setText(str);
}
void DVBT_Manual_Scan::updataScanStatus(float dt)
{
	//skyScanCallbackData scandata = m_scanApi->getScanData();
	skyScanCallbackData scandata = m_scanData;
	skyScanStatus scanstatus = scandata.scanstatus;
	if (scanstatus == skyScanStatus::STATUS_SKYSCAN_FAILED || scanstatus == skyScanStatus::STATUS_SKYSCAN_TIMEOUT)
	{
		this->unschedule(schedule_selector(DVBT_Manual_Scan::updataScanStatus)); 
		//TODO failed deal

	}
	else if (scanstatus == skyScanStatus::STATUS_SKYSCAN_TUNING_END)
	{
		//TODO 
		this->unschedule(schedule_selector(DVBT_Manual_Scan::updataScanStatus));
		onTuningComplete();
		skyScanCallbackData scandata = m_scanData;
		updataDataCounts("ID_TEXT_ALL", scandata.digitaltv_count + scandata.radio_count + scandata.data_count);
		updataDataCounts("ID_TEXT_DTV", scandata.digitaltv_count); //??DTV is tv_count
		updataDataCounts("ID_TEXT_RADIO", scandata.radio_count);

	}
	else {
		LoadingBar* bar = (LoadingBar*)m_rootNode->getChildByName("ID_PROGRESS");
		bar->setPercent(scandata.process);
	
		updataDataCounts("ID_TEXT_ALL", scandata.digitaltv_count + scandata.radio_count + scandata.data_count);
		updataDataCounts("ID_TEXT_DTV", scandata.digitaltv_count);
		updataDataCounts("ID_TEXT_RADIO", scandata.radio_count);
	}
}
void DVBT_Manual_Scan::onTuningComplete()
{	
	ImageView* img = ImageView::create("broadcast/broadcast_completed.png");
	img->setPosition(Vec2(215,335));
	m_rootNode->addChild(img);

	Text* text = Text::create("Completed", "general/SourceHanSansTWHK-Light.ttf", 42);
	text->setColor(Color3B(90, 201, 17));
	text->setPosition(Vec2(355,326));
	m_rootNode->addChild(text);

	LoadingBar* bar = (LoadingBar*)m_rootNode->getChildByName("ID_PROGRESS");
	bar->setPercent(100);

	m_countDown = 5;
	this->schedule(schedule_selector(DVBT_Manual_Scan::completeCountDown), 1);
}
void DVBT_Manual_Scan::completeCountDown(float dt)
{
	if (m_countDown > 0)
	{
		m_countDown--;
		char str[64] = { 0 };
		sprintf(str, "Close(%ds)", m_countDown);
		setBtnTitle(m_rootNode, "ID_BUT_NO", str);
	}
	else {
		this->unschedule(schedule_selector(DVBT_Manual_Scan::completeCountDown));
		this->getParent()->removeChild(this);
	}
}
void DVBT_Manual_Scan::updateSignalQuality()
{
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]
	{
		Node* node = this->getChildByName("ID_LAYER_DVBT_SET");
		if (node) {
			LoadingBar* signalBar = (LoadingBar*) node->getChildByName("ID_BUT_QUA")->getChildByName("ID_PROGRESS");
			signalBar->setPercent(m_scanData.signal_quality);
		}
	});
}
void DVBT_Manual_Scan::tuningBack(skyScanCallbackData data, void* ptr)
{
	DVBT_Manual_Scan* tuning = (DVBT_Manual_Scan*)ptr;
	memcpy(&tuning->m_scanData, &data, sizeof(skyScanCallbackData));
	tuning->updateSignalQuality();
}