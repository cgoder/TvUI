#include "ManualScan/ATV_ManualScan.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "common/KeyBoard.h"
#include "common/common.h"
#include "tvplayer/TvPlayer.h"

ATV_Manual_Scan::ATV_Manual_Scan()
{
	m_searchStatus = ManualScanStatus::STATUS_SEARCH_IDLE;
	this->setName("ATV_Manual_Scan");
	log("ATV_Manual_Scan");
	memset(&m_scanData, 0, sizeof(skyScanCallbackData));
#ifdef SCANTV
	m_scanApi = skyScanUi::skyGetScanInstance(skyScanSourceType::SOURCE_TYPE_ATV_S /*SOURCE_TYPE_DVBT_S*/);
	(m_scanApi)->skyRegisterScanData(ATV_Manual_Scan::tuningBack, this);
	m_scanParam = new skyScanParam;
	m_scanParam->autoscanmodel = skyScanModel::MANUALSCAN;
#endif
}

ATV_Manual_Scan::~ATV_Manual_Scan()
{
	delete m_btnData[0];
	delete m_btnData[1];
	delete m_btnData[2];
	delete m_btnData[3];
	delete m_btnData[4];
#ifdef SCANTV
	m_scanApi->skyScanStop();
	skyScanUi::skyScanDestroyInstance();
	delete m_scanParam;
#endif
}

cocos2d::Layer* ATV_Manual_Scan::creatLayer(Node* node)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("ATV_Manual_Scan");
		if (tuning) {
			return tuning;
		}
		else {
			log("ATV_Manual_Scan:create");
			auto pRet = ATV_Manual_Scan::create();
			node->addChild(pRet);
			return pRet;
		}
	}
	return nullptr;
}

void ATV_Manual_Scan::initScanData()
{
#ifdef SCANTV
	char textValue[128] = { 0 };
	skyScanParam params;
	m_scanApi->skyDtvGetCurrentScanParam(params);
	skyAudioSystemType audiotype = params.audiosystem;
	switch (audiotype)
	{
	case skyAudioSystemType::ATV_MODE_BG:
		m_btnData[1]->index = 0;
		sprintf(textValue, "%s", "BG");
		break;
	case skyAudioSystemType::ATV_MODE_I:
		m_btnData[1]->index = 1;
		sprintf(textValue, "%s", "I");
		break;
	case skyAudioSystemType::ATV_MODE_DK:
		m_btnData[1]->index = 2;
		sprintf(textValue, "%s", "DK");
		break;
	case skyAudioSystemType::ATV_MODE_L:
		m_btnData[1]->index = 3;
		sprintf(textValue, "%s", "L");
		break;
	case skyAudioSystemType::ATV_MODE_M:
		m_btnData[1]->index = 4;
		sprintf(textValue, "%s", "M");
		break;
	default:
		m_btnData[1]->index = 0;
		sprintf(textValue, "%s", "BG");
		break;
	}
	Button* btn = (Button*)m_rootNode->getChildByName("ID_BUT_SOUND");
	if (btn)
		setTextTitle(btn, "ID_TEXT_VALUE", textValue);

	skyColorSystemType colorType = params.colorsystemtype;
	switch (colorType)
	{
	case skyColorSystemType::ATV_COLOR_PAL:
		m_btnData[2]->index = 0;
		sprintf(textValue, "%s", "PAL");
		break;
	case skyColorSystemType::ATV_COLOR_NTSC:
		m_btnData[2]->index = 1;
		sprintf(textValue, "%s", "NTSC");
		break;
	case skyColorSystemType::ATV_COLOR_SECAM:
		m_btnData[2]->index = 2;
		sprintf(textValue, "%s", "SECAM");
		break;
	case skyColorSystemType::ATV_COLOR_AUTO:
		m_btnData[2]->index = 3;
		sprintf(textValue, "%s", "AUTO");
		break;
	default:
		m_btnData[2]->index = 3;
		sprintf(textValue, "%s", "AUTO");
		break;
	}
	btn = (Button*)m_rootNode->getChildByName("ID_BUT_COLOR");
	if (btn)
		setTextTitle(btn, "ID_TEXT_VALUE", textValue);

	int currentFre = params.freqdata.freq;
	sprintf(textValue, "%dKHz", currentFre);
	btn = (Button*)m_rootNode->getChildByName("ID_BUT_SEARCH");
	if (btn)
		setTextTitle(btn, "ID_TEXT_VALUE", textValue);

	unsigned int finrFre = params.freqdata.freq; //TODO init tune freq
	sprintf(textValue, "%dKHz", finrFre);
	btn = (Button*)m_rootNode->getChildByName("ID_BUT_TUNE");
	if (btn)
		setTextTitle(btn, "ID_TEXT_VALUE", textValue);
#endif
}
// on "init" you need to initialize your instance
bool ATV_Manual_Scan::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("MATV.csb");
	rootNode->setName("ID_LAYER_DVBT_SET");
	addChild(rootNode);
	m_rootNode = rootNode;
	Size size = rootNode->getContentSize();
	this->setContentSize(size);
	this->setPosition(Vec2(1920 / 2 - size.width / 2, 1080 / 2 - size.height / 2));

	m_btnFocused = nullptr;
/*
	setBtnFunc(rootNode, "ID_BUT_YES", CC_CALLBACK_2(ATV_Manual_Scan::onBtnScan, this), nullptr);
	setBtnFunc(rootNode, "ID_BUT_NO", CC_CALLBACK_2(ATV_Manual_Scan::onBtnCancel, this), nullptr);
	*/

	m_btnData[0] = new button_user_data;
	m_btnData[1] = new button_user_data;
	m_btnData[2] = new button_user_data;
	m_btnData[3] = new button_user_data;
	m_btnData[4] = new button_user_data;

	m_channelNums = Get_TvPlayer()->getChannelCount();
	char textValue[128] = { 0 };
#ifdef SCANTV
	m_scanApi->skyDtvSetScanParam(*m_scanParam);
	int currentChannel = m_scanParam->channelindex;// m_scanApi->getCurrentProgrameIndex();
#else
	int currentChannel = 0;
#endif
	m_btnData[0]->type = BUTTON_TYPE::TYPE_NUMS;
	m_btnData[0]->index = currentChannel;
	m_btnData[0]->data = nullptr;
	Button* btn = setBtnFunc(rootNode, "ID_BUT_CHAN", CC_CALLBACK_2(ATV_Manual_Scan::onBtnChan, this), m_btnData[0]);
	sprintf(textValue,"%d", currentChannel);
	if (btn)
	    setTextTitle(btn,"ID_TEXT_VALUE",textValue);

	m_btnData[1]->type = BUTTON_TYPE::TYPE_NUMS;
	m_btnData[1]->index = 0;
	m_vecAudio.push_back("BG");
	m_vecAudio.push_back("I");
	m_vecAudio.push_back("DK");
	m_vecAudio.push_back("L");
	m_vecAudio.push_back("M");
	m_btnData[1]->data = (void*)&m_vecAudio;
	btn = setBtnFunc(rootNode, "ID_BUT_SOUND", CC_CALLBACK_2(ATV_Manual_Scan::onBtnSound, this), m_btnData[1]);
		
	m_btnData[2]->type = BUTTON_TYPE::TYPE_NUMS;
	m_btnData[2]->index = 0;
	m_vecColor.push_back("PAL");
	m_vecColor.push_back("NTSC");
	m_vecColor.push_back("SECAM");
	m_vecColor.push_back("AUTO");
	m_btnData[2]->data = (void*)&m_vecColor;
	btn = setBtnFunc(rootNode, "ID_BUT_COLOR", CC_CALLBACK_2(ATV_Manual_Scan::onBtnColor, this), m_btnData[2]);
	
	m_btnData[3]->type = BUTTON_TYPE::TYPE_NUMS;
	m_btnData[3]->data = nullptr;
	btn = setBtnFunc(rootNode, "ID_BUT_SEARCH", CC_CALLBACK_2(ATV_Manual_Scan::onBtnSearch, this), m_btnData[3]);
	
	m_btnData[4]->type = BUTTON_TYPE::TYPE_NUMS;
	m_btnData[4]->data = nullptr;
	btn = setBtnFunc(rootNode, "ID_BUT_TUNE", CC_CALLBACK_2(ATV_Manual_Scan::onBtnTune, this), m_btnData[4]);
	initScanData();

	addKeyListener(CC_CALLBACK_2(ATV_Manual_Scan::onKeyPressed, this), rootNode);
	return true;
}
void ATV_Manual_Scan::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
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

void ATV_Manual_Scan::onBtnChan(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	button_user_data* data = (button_user_data*)m_btnFocused->getUserData();
	if (m_keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT) {
		if (data->index > 0)
		{
			data->index -= 1;
			Text* text = (Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE");
			text->setString(std::to_string(data->index));
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(false);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(true);
			//TODO change channel
			Get_TvPlayer()->play(data->index);
			initScanData();
		}
	}
	else if (m_keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT)
	{
		if (data->index < (m_channelNums - 1))
		{
			data->index += 1;
			Text* text = (Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE");
			text->setString(std::to_string(data->index));
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(true);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(false);
			//TODO change channel set
			Get_TvPlayer()->play(data->index);
			initScanData();
		}
	}
}
void ATV_Manual_Scan::setScanColor()
{
	Text* text = (Text*) m_rootNode->getChildByName("ID_BUT_COLOR")->getChildByName("ID_TEXT_VALUE");
	std::string textValue = text->getString();
	skyColorSystemType colorType = skyColorSystemType::ATV_COLOR_PAL;
	if (textValue == "PAL")
		colorType = skyColorSystemType::ATV_COLOR_PAL;
	else if (textValue == "NTSC")
		colorType = skyColorSystemType::ATV_COLOR_NTSC;
	else if (textValue == "SECAM")
		colorType = skyColorSystemType::ATV_COLOR_SECAM;
	else if (textValue == "AUTO")
		colorType = skyColorSystemType::ATV_COLOR_AUTO;
#ifdef SCANTV
	m_scanApi->skyAtvSetCurColor(colorType);
#endif
}
void ATV_Manual_Scan::setScanSound()
{
	Text* text = (Text*)m_rootNode->getChildByName("ID_BUT_SOUND")->getChildByName("ID_TEXT_VALUE");
	std::string textValue = text->getString();
	skyAudioSystemType audioType = skyAudioSystemType::ATV_MODE_BG;
	if (textValue == "BG")
		audioType = skyAudioSystemType::ATV_MODE_BG;
	else if (textValue == "DK")
		audioType = skyAudioSystemType::ATV_MODE_DK;
	else if (textValue == "I")
		audioType = skyAudioSystemType::ATV_MODE_I;
	else if (textValue == "L")
		audioType = skyAudioSystemType::ATV_MODE_L;
	else if (textValue == "M")
		audioType = skyAudioSystemType::ATV_MODE_M;
#ifdef SCANTV
	m_scanApi->skyAtvSetCurSound(audioType);
#endif
}
void ATV_Manual_Scan::onBtnSound(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	button_user_data* data = (button_user_data*)m_btnFocused->getUserData();
	std::vector<std::string> vec = *((std::vector<std::string>*)data->data);
	if (m_keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT) {
		if (data->index > 0)
		{
			data->index -= 1;			
			Text* text = (Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE");
			text->setString(vec.at(data->index));
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(false);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(true);
			setScanSound();
		}
	}
	else if (m_keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT)
	{
		if (data->index < (vec.size() - 1))
		{
			data->index += 1;
			Text* text = (Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE");
			std::vector<std::string> vec = *((std::vector<std::string>*)data->data);
			text->setString(vec.at(data->index));
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(true);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(false);
			setScanSound();
		}
	}
}
void ATV_Manual_Scan::onBtnColor(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	button_user_data* data = (button_user_data*)m_btnFocused->getUserData();
	std::vector<std::string> vec = *((std::vector<std::string>*)data->data);
	if (m_keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT) {
		if (data->index > 0)
		{
			data->index -= 1;
			Text* text = (Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE");
			text->setString(vec.at(data->index));
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(false);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(true);
			setScanColor();
		}
	}
	else if (m_keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT)
	{
		if (data->index < (vec.size() - 1))
		{
			data->index += 1;
			Text* text = (Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE");
			std::vector<std::string> vec = *((std::vector<std::string>*)data->data);
			text->setString(vec.at(data->index));
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(true);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(false);
			setScanColor();
		}
	}
}
void ATV_Manual_Scan::onBtnSearch(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	std::string freStr = ((Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE"))->getString();
	unsigned int fre;
	fre = std::stoi(freStr.substr(0, freStr.size() - 3));
	skyFreqData freData;
	freData.freq = fre;
	if (m_keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT) {
		Button* btnr = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
		Button* btnl = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
		switch (m_searchStatus)
		{
		case ManualScanStatus::STATUS_SEARCH_IDLE:
			btnr->setHighlighted(false);
			btnl->setHighlighted(true);
			setSearchStatus(ManualScanStatus::STATUS_SEARCH_LEFT);
#ifdef SCANTV
			m_scanParam->atvtunemode = ATV_MANUAL_TUNE_MODE_SEARCH_ONE_TO_DOWN;
			m_scanParam->freqdata = freData;
			m_scanApi->skyDtvSetScanParam(*m_scanParam);
			m_scanApi->skyScanStart();
			//m_scanApi->skyAtvManualScanStart(ATV_MANUAL_TUNE_MODE_SEARCH_ONE_TO_UP, freData);
#endif
			break;
		case ManualScanStatus::STATUS_SEARCH_LEFT:
			break;
		case ManualScanStatus::STATUS_SEARCH_RIGHT:
			btnr->setHighlighted(false);
			btnl->setHighlighted(false);
			setSearchStatus(ManualScanStatus::STATUS_SEARCH_IDLE);
#ifdef SCANTV
			m_scanApi->skyScanStop();
#endif
			break;
		}		
	}
	else if (m_keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT) {
		Button* btnr = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
		Button* btnl = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
		switch (m_searchStatus)
		{
		case ManualScanStatus::STATUS_SEARCH_IDLE:
			btnr->setHighlighted(true);
			btnl->setHighlighted(false);
			setSearchStatus(ManualScanStatus::STATUS_SEARCH_RIGHT);
#ifdef SCANTV
			//m_scanApi->skyAtvManualScanStart(ATV_MANUAL_TUNE_MODE_SEARCH_ONE_TO_UP, freData);
			m_scanParam->atvtunemode = ATV_MANUAL_TUNE_MODE_SEARCH_ONE_TO_UP;
			m_scanParam->freqdata = freData;
			m_scanApi->skyDtvSetScanParam(*m_scanParam);
			m_scanApi->skyScanStart();
#endif
			break;
		case ManualScanStatus::STATUS_SEARCH_LEFT:
			btnr->setHighlighted(false);
			btnl->setHighlighted(false);
			setSearchStatus(ManualScanStatus::STATUS_SEARCH_IDLE);
#ifdef SCANTV
			m_scanApi->skyScanStop();
#endif
			break;
		case ManualScanStatus::STATUS_SEARCH_RIGHT:			
			break;
		}
	}
}
void ATV_Manual_Scan::onBtnTune(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	std::string freStr = ((Text*)m_btnFocused->getChildByName("ID_TEXT_VALUE"))->getString();
	unsigned int fre;
	fre = std::stoi(freStr.substr(0, freStr.size() - 3));
	skyFreqData freData;
	freData.freq = fre;
	if (m_keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT) {
		if (m_searchStatus == ManualScanStatus::STATUS_SEARCH_IDLE)
		{
#ifdef SCANTV

			m_scanParam->atvtunemode = ATV_MANUAL_TUNE_MODE_FINE_TUNE_DOWN;
			m_scanParam->freqdata = freData;
			m_scanApi->skyDtvSetScanParam(*m_scanParam);
			m_scanApi->skyScanStart();

			//m_scanApi->skyAtvManualScanStart(ATV_MANUAL_TUNE_MODE_FINE_TUNE_UP, freData);
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(false);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(true);

			skyScanParam params;
			m_scanApi->skyDtvGetCurrentScanParam(params);

			m_scanData.current_freq = params.freqdata.freq; //m_scanApi->getCurrentFrequency();
			updateSignalQuality();
#endif
		}
	}
	else if (m_keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || m_keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT) {
		if (m_searchStatus == ManualScanStatus::STATUS_SEARCH_IDLE)
		{
#ifdef SCANTV
			m_scanParam->atvtunemode = ATV_MANUAL_TUNE_MODE_FINE_TUNE_UP;
			m_scanParam->freqdata = freData;
			m_scanApi->skyDtvSetScanParam(*m_scanParam);
			m_scanApi->skyScanStart();

			//m_scanApi->skyAtvManualScanStart(ATV_MANUAL_TUNE_MODE_FINE_TUNE_DOWN, freData);
			Button* btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_R");
			btn->setHighlighted(true);
			btn = (Button*)m_btnFocused->getChildByName("ID_BUT_ARROW_L");
			btn->setHighlighted(false);

			skyScanParam params;
			m_scanApi->skyDtvGetCurrentScanParam(params);
			m_scanData.current_freq = params.freqdata.freq; //m_scanApi->getCurrentFrequency();
			updateSignalQuality();
#endif
		}
	}
}
/*
void ATV_Manual_Scan::onBtnCancel(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	this->unschedule(schedule_selector(ATV_Manual_Scan::completeCountDown));
	this->getParent()->removeChild(this);
}
void ATV_Manual_Scan::onBtnScan(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	this->removeAllChildren();
	auto rootNode = CSLoader::createNode("MTuning.csb");
	addChild(rootNode);
	m_rootNode = rootNode;
	m_btnFocused = nullptr;
	setBtnFunc(rootNode, "ID_BUT_NO", CC_CALLBACK_2(ATV_Manual_Scan::onBtnCancel, this), nullptr);
	addKeyListener(CC_CALLBACK_2(BtnFocusLayer::onKeyPressed, this), m_rootNode);
	//TODO ManualScan
	m_scanApi->skyAutoScanStart();
	this->schedule(schedule_selector(ATV_Manual_Scan::updataScanStatus), 1);
}
void ATV_Manual_Scan::updataDataCounts(const char* nodeName, int counts)
{
	char str[64] = { 0 };
	Text* text = (Text*)m_rootNode->getChildByName(nodeName)->getChildByName("ID_TEXT_VALUE");
	sprintf(str, "%d", counts);
	if (text)
		text->setText(str);
}
void ATV_Manual_Scan::updataScanStatus(float dt)
{
	//skyScanCallbackData scandata = m_scanApi->getScanData();
	skyScanCallbackData scandata = m_scanData;
	skyScanStatus scanstatus = scandata.scanstatus;
	if (scanstatus == skyScanStatus::STATUS_SKYSCAN_FAILED || scanstatus == skyScanStatus::STATUS_SKYSCAN_TIMEOUT)
	{
		this->unschedule(schedule_selector(ATV_Manual_Scan::updataScanStatus));
		//TODO failed deal

	}
	else if (scanstatus == skyScanStatus::STATUS_SKYSCAN_TUNING_END)
	{
		//TODO 
		this->unschedule(schedule_selector(ATV_Manual_Scan::updataScanStatus));
		onTuningComplete();
		skyScanCallbackData scandata = m_scanData;
		updataDataCounts("ID_TEXT_ALL", scandata.tv_count + scandata.radio_count + scandata.data_count);
		updataDataCounts("ID_TEXT_DTV", scandata.tv_count); //??DTV is tv_count
		updataDataCounts("ID_TEXT_RADIO", scandata.radio_count);

	}
	else {
		LoadingBar* bar = (LoadingBar*)m_rootNode->getChildByName("ID_PROGRESS");
		bar->setPercent(scandata.process);

		updataDataCounts("ID_TEXT_ALL", scandata.tv_count + scandata.radio_count + scandata.data_count);
		updataDataCounts("ID_TEXT_DTV", scandata.tv_count);
		updataDataCounts("ID_TEXT_RADIO", scandata.radio_count);
	}
}
void ATV_Manual_Scan::onTuningComplete()
{
	ImageView* img = ImageView::create("broadcast/broadcast_completed.png");
	img->setPosition(Vec2(215, 335));
	m_rootNode->addChild(img);

	Text* text = Text::create("Completed", "general/SourceHanSansTWHK-Light.ttf", 42);
	text->setColor(Color3B(90, 201, 17));
	text->setPosition(Vec2(355, 326));
	m_rootNode->addChild(text);

	LoadingBar* bar = (LoadingBar*)m_rootNode->getChildByName("ID_PROGRESS");
	bar->setPercent(100);

	m_countDown = 5;
	this->schedule(schedule_selector(ATV_Manual_Scan::completeCountDown), 1);
}
void ATV_Manual_Scan::completeCountDown(float dt)
{
	if (m_countDown > 0)
	{
		m_countDown--;
		char str[64] = { 0 };
		sprintf(str, "Close(%ds)", m_countDown);
		setBtnTitle(m_rootNode, "ID_BUT_NO", str);
	}
	else {
		this->unschedule(schedule_selector(ATV_Manual_Scan::completeCountDown));
		this->getParent()->removeChild(this);
	}
}
*/
void ATV_Manual_Scan::updateSignalQuality()
{	
	//TODO update freq
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]
	{
		Node* node = this->getChildByName("ID_LAYER_DVBT_SET");
		if (node) {
			Text* freqText = (Text*)node->getChildByName("ID_BUT_SEARCH")->getChildByName("ID_TEXT_VALUE");
			Text* tuneText = (Text*)node->getChildByName("ID_BUT_TUNE")->getChildByName("ID_TEXT_VALUE");
			char textValue[128] = { 0 };
			sprintf(textValue,"%dKHz", m_scanData.current_freq);
			freqText->setString(textValue);
			tuneText->setString(textValue);
		}
	});
}
void ATV_Manual_Scan::tuningBack(skyScanCallbackData data, void* ptr)
{
	ATV_Manual_Scan* tuning = (ATV_Manual_Scan*)ptr;
	memcpy(&tuning->m_scanData, &data, sizeof(skyScanCallbackData));
	if (data.process == 100)
    	tuning->setSearchStatus(ManualScanStatus::STATUS_SEARCH_IDLE); //TODO
	tuning->updateSignalQuality();
}