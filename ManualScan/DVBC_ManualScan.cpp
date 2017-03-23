#include "ManualScan/DVBC_ManualScan.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

skyScanCallbackData *DVBC_Manual_Scan::tvdata = NULL;
DVBC_Manual_Scan::DVBC_Manual_Scan()
{
	this->setName("DVBC_Manual_Scan");
	log("DVBC_Manual_Scan");
}

DVBC_Manual_Scan::~DVBC_Manual_Scan()
{
	//skyScanCallbackData *tvdata;
	delete tvdata;
}

cocos2d::Layer* DVBC_Manual_Scan::creatLayer(Node* node)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("DVBC_Manual_Scan");
		if (tuning) {
			return tuning;
		}
		else {
			log("DVBC_Manual_Scan:ceart");
			auto ptuning = DVBC_Manual_Scan::create();
			node->addChild(ptuning);
			return ptuning;
		}
	}
	return nullptr;
}
bool DVBC_Manual_Scan::skyShow(cocos2d::Node* node)
{
	if (node) {
		auto layer = node->getChildByName("DVBC_Manual_Scan");
		if (layer) {
			layer->setVisible(true);
		}			
		else {
			auto player = DVBC_Manual_Scan::create();
			node->addChild(player);
			player->setVisible(true);
		}
		return true;
	}
	return false;
}
void DVBC_Manual_Scan::skyHide(cocos2d::Node* node)
{
	if (node) {
		auto layer = node->getChildByName("DVBC_Manual_Scan");
		if (layer)
			layer->setVisible(false);
	}
}

void DVBC_Manual_Scan::skyRefresh()
{

}
Scene* DVBC_Manual_Scan::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
   
    // 'layer' is an autorelease object
	auto layer = DVBC_Manual_Scan::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


void DVBC_Manual_Scan::dvbc_getdata(skyScanCallbackData  data, void* ptr)
{
	memcpy(tvdata, &data, sizeof(skyScanCallbackData));

}
// on "init" you need to initialize your instance
bool DVBC_Manual_Scan::init()
{
   
	// 1. super init first
	if ( !Layer::init() )
	{
	return false;
	}
    
	rootNode = CSLoader::createNode("DVBCManualScan.csb");

	addChild(rootNode);
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(DVBC_Manual_Scan::keyPressed, this);
	keyboardListener->setEnabled(1);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto basenode = (Layout*)rootNode->getChildByName("BaseNode");
	label_list = (ListView*)basenode->getChildByName("Label_List");
	arrow_list_l = (ListView*)basenode->getChildByName("Arrow_List_L");
	arrow_list_r = (ListView*)basenode->getChildByName("Arrow_List_R");
	option_list = (ListView*)basenode->getChildByName("Option_List");
	medual_text = (Text*)option_list->getChildByName("Text_Field_0");
	symbol_text = (Text*)option_list->getChildByName("Text_Field_1");
	scope_text = (Text*)option_list->getChildByName("Text_Field_2");
	focus_image = (ImageView*)basenode->getChildByName("Image_Bg_List");
	button_save = (ImageView*)basenode->getChildByName("Button_Save");
	button_cancle = (ImageView*)basenode->getChildByName("Button_Cancle");
	inputlayer = (Layout*)basenode->getChildByName("Panel_4");
	inputtext = (TextField*)inputlayer->getChildByName("TextField_4");
	freqtext = (Text*)basenode->getChildByName("Text_1");
	auto save_text = (Text*)button_save->getChildByName("Text_Save");
	int order = save_text->getLocalZOrder();
	log("order %d", order);
	button_bg_save = ImageView::create("general/general_button_focus.png", TextureResType::LOCAL);
	button_bg_save->setScale9Enabled(true);
	button_bg_save->setContentSize(Size(400, 140));
	button_bg_save->setPosition(Vec2(155,14));
	button_bg_save->setLocalZOrder(order - 1);
	order= button_bg_save->getOrderOfArrival();
	log("order %d", order);
	button_save->addChild(button_bg_save);
	button_bg_save->setVisible(false);
	button_bg_save->setName("BUTTON_BG");

	auto cancle_text = (Text*)button_cancle->getChildByName("Text_Cancle");
	order = cancle_text->getLocalZOrder();
	log("order %d", order);
	button_bg_cancle = ImageView::create("general/general_button_focus.png", TextureResType::LOCAL);
	button_bg_cancle->setScale9Enabled(true);
	button_bg_cancle->setContentSize(Size(400, 140));
	button_bg_cancle->setPosition(Vec2(155, 14));
	button_bg_cancle->setLocalZOrder(order - 1);
	order = button_bg_cancle->getOrderOfArrival();
	log("order %d", order);
	button_cancle->addChild(button_bg_cancle);
	button_bg_cancle->setVisible(false);

	item_focus = 0;
	list_focus = 0;
	m_switch = 0;
	
	tvdata = new skyScanCallbackData;
	memset(tvdata, 0, sizeof(skyScanCallbackData));
	pInstance = skyScanUi::skyGetScanInstance(SOURCE_TYPE_DVBC_S);

	pInstance->skyRegisterScanData(dvbc_getdata, this);

	medulation[S_MODULATION_MODE_QAM_AUTO] = { "auto" };
	medulation[S_MODULATION_MODE_QAM16] = { "16QAM" };
	medulation[S_MODULATION_MODE_QAM32] = { "32QAM" };
	medulation[S_MODULATION_MODE_QAM64] = { "64QAM" };
	medulation[S_MODULATION_MODE_QAM128] = { "128QAM" };
	medulation[S_MODULATION_MODE_QAM256] = { "256QAM" };

	symbol[0] = { "auto" };
	symbol[1] = { "0000" };

	scanscope[TV_FREE_ONLY] = { "all" };
	scanscope[TV_FREE_SCRAMBLE] = { "free" };
	scanscope[TV_SCRAMBLE] = { "scramble" };
	medulation_index=5;
	symbol_index = 0;
	scope_index = 1;
	
	this->schedule(schedule_selector(DVBC_Manual_Scan::updataScanStatus), 1);
	SetOptionData(medulation_index,symbol_index, scope_index, DEFAULT_FREQ);

	return true;
}

void DVBC_Manual_Scan::ChangeOptionData(REMOTE_TYPE type, int currentListFocus)//改变option数据
{


	switch (type)
	{
	
	case REMOTE_LEFT:
		switch (currentListFocus)
		{
		case 1:
			medulation_index--;
			if (medulation_index < 0)
			{
				medulation_index = 5;
			}
			medual_text->setString(medulation[medulation_index]);
			break;
		case 2:
			symbol_index--;
			if (symbol_index < 0)
			{
				symbol_index = 1;
			}
			symbol_text->setString(symbol[symbol_index]);
			break;
		case 3:
			scope_index--;
			if (scope_index < 0)
			{
				scope_index = 2;
			}
			scope_text->setString(scanscope[scope_index]);
			break;

		}
		SetOptionData(medulation_index, symbol_index, scope_index, stoi(inputtext->getString().c_str()));
		break;
	case REMOTE_RIGHT:
		switch (currentListFocus)
		{
		case 1:
			medulation_index++;
			if (medulation_index > 5)
			{
				medulation_index = 0;
			}
			medual_text->setString(medulation[medulation_index]);
			break;
		case 2:
			symbol_index++;
			if (symbol_index > 1)
			{
				symbol_index = 0;
			}
			symbol_text->setString(symbol[symbol_index]);
			break;
		case 3:
			scope_index++;
			if (scope_index > 2)
			{
				scope_index = 0;
			}
			scope_text->setString(scanscope[scope_index]);
			break;
			
		}
		SetOptionData(medulation_index, symbol_index, scope_index, stoi(inputtext->getString().c_str()));
		break;
	case REMOTE_OK:
		if (!button_bg_save->isVisible())
		{
			DVBC_Manual_Scan::onBtnCancel_C(nullptr, (cocos2d::ui::Widget::TouchEventType) 0);
		}
		else
		{
			m_switch = 1;
			SetOptionData(medulation_index, symbol_index, scope_index, stoi(inputtext->getString().c_str()));
			DVBC_Manual_Scan::onBtnScan_C(nullptr, (cocos2d::ui::Widget::TouchEventType) 0);
		}
		
		break;
	case REMOTE_NUMBER:
		
		switch (currentListFocus)
		{
		case 0:
			if (fre_result != "")
			{
				inputtext->setString(fre_result);
			}
			else
			{
				inputtext->setString("250");
			}
			break;
		case 2:
			if (symbol_result != "")
			{
				symbol_text->setString(symbol_result);
			}
			else
			{
				symbol_text->setString("0000");
			}
			break;
		}
		if((inputtext->getString().length() ==3 )||(symbol_result.length() ==4))
		{
			SetOptionData(medulation_index, symbol_index, scope_index, stoi(inputtext->getString().c_str()));
		}
		break;
	}
	

}
void DVBC_Manual_Scan::SetOptionData(int medulation, int symbol, int scope, int freq)
{
	if (symbol)
	{
		symbol = stoi(symbol_text->getString());
	}

	skyScanParam scanparam;
	
	scanparam.freqdata.freq = freq*1000;
	
	scanparam.freqdata.modulation = (S_QAM_ModulationMode)medulation;
	scanparam.freqdata.symbolRate = symbol;
	scanparam.freqdata.networkid =0;
	scanparam.freqdata.front_id =0;
	scanparam.autoscanmodel = MANUALSCAN;
	scanparam.networksearch =0;
	/*
	freqparam.freq =0;
	freqparam.networkid =0;
	pInstance->skyScanSetCountryData(50);
	pInstance->skyScanSetCableOP_Type(E_SKY_CABLEOP_OTHER);
	pInstance->skySetAutoScanModel(AUTOSCAN);*/






	log("\nfreqparam.freq %ld %d %ld\n",scanparam.freqdata.freq, scanparam.freqdata.modulation, scanparam.freqdata.symbolRate);
	pInstance->skyDtvSetScanParam(scanparam);
	if (m_switch)
	{
		//pInstance->skyScanWithRangeStart(freqparam, freqend);
		pInstance->skyScanStart();
	}
	//pInstance->skyScanWithRangeStart(freq, freqend);
}

void DVBC_Manual_Scan::drawCurrent(REMOTE_TYPE type, int currentListFocus, int currentItemFocus)
{
	int count = 0;
	switch (type)
	{
	case REMOTE_UP:
		button_bg_save->setVisible(false);
		button_bg_cancle->setVisible(false);
		focus_image->setPositionY(focus_image->getPositionY() + SPACEFOCUS);
		if (currentListFocus)
		{		
			focus_image->setVisible(true);
			count = arrow_list_l->getChildrenCount();
			log("count %d ", count);
			for (int i = 0; i < count; i++)
			{
				auto buttonl = arrow_list_l->getItem(i);
				auto buttonr = arrow_list_r->getItem(i);
				auto text = label_list->getItem(i);
				if (i == currentListFocus - 1)
				{
					text->setColor(Color3B(51, 51, 51));
				}
				else
				{
					text->setColor(Color3B(91, 91, 91));
				}
				buttonl->setHighlighted(false);
				buttonr->setHighlighted(false);
			}
		}
		else
		{
			focus_image->setVisible(false);
			inputlayer->setVisible(true);
		}
		break;
	case REMOTE_DOWN:
		focus_image->setPositionY(focus_image->getPositionY() - SPACEFOCUS);
		if (currentItemFocus)
		{
			focus_image->setVisible(false);
			button_bg_save->setVisible(true);
		}
		else
		{
			focus_image->setVisible(true);			
			inputlayer->setVisible(false);
			if (!inputtext->getString().empty())
			{
				string tmp = inputtext->getString() + "MHZ";
				freqtext->setString(tmp);
			}
			count = arrow_list_l->getChildrenCount();
			log("count %d ", count);
			for (int i = 0; i < count; i++)
			{
				auto buttonl = arrow_list_l->getItem(i);
				auto buttonr = arrow_list_r->getItem(i);
				auto text = label_list->getItem(i);
				if (i == currentListFocus - 1)
				{
					text->setColor(Color3B(51, 51, 51));
				}
				else
				{
					text->setColor(Color3B(91, 91, 91));
				}
				buttonl->setHighlighted(false);
				buttonr->setHighlighted(false);
			}
		}
		break;
	case REMOTE_LEFT:
		if (currentItemFocus)
		{
			button_bg_save->setVisible(true);
			button_bg_cancle->setVisible(false);
		}
		else
		{
			if (!currentListFocus)
			{
				return;
			}
			auto button = arrow_list_l->getItem(currentListFocus - 1);
			button->setHighlighted(true);
			ChangeOptionData(type, currentListFocus);

		}
		break;
	case REMOTE_RIGHT:
		if (currentItemFocus)
		{
			button_bg_save->setVisible(false);
			button_bg_cancle->setVisible(true);
		}
		else
		{
			if (!currentListFocus)
			{
				return;
			}
			auto button = arrow_list_r->getItem(currentListFocus - 1);
			button->setHighlighted(true);
			ChangeOptionData(type, currentListFocus );
		}

		break;
	case REMOTE_OK:
		ChangeOptionData(type, currentListFocus);
		break;
	case REMOTE_NUMBER:
		ChangeOptionData(type, currentListFocus );
		break;
	}
}
void DVBC_Manual_Scan::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, Event *event)
{
	stopPropagation(keyCode, event, false);
	int type = REMOTE_UNKNOW;

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_DOWN:

		if (list_focus < MAXITEM_C)
		{
			type = REMOTE_DOWN;
			list_focus++;
			if (list_focus == MAXITEM_C)
			{
				item_focus = 1;
			}
		}
		break;
	case  EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_UP:
		
		if (list_focus > 0)
		{
			type = REMOTE_UP;
			list_focus--;
			if (item_focus)
			{
				item_focus = 0;
			}
		}
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
		type = REMOTE_LEFT;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
		type = REMOTE_RIGHT;
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
	case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
		type = REMOTE_OK;
		break;
	case  EventKeyboard::KeyCode::KEY_0:
	case EventKeyboard::KeyCode::KEY_1:
	case EventKeyboard::KeyCode::KEY_2:
	case EventKeyboard::KeyCode::KEY_3:
	case EventKeyboard::KeyCode::KEY_4:
	case EventKeyboard::KeyCode::KEY_5:
	case EventKeyboard::KeyCode::KEY_6:
	case EventKeyboard::KeyCode::KEY_7:
	case EventKeyboard::KeyCode::KEY_8:
	case EventKeyboard::KeyCode::KEY_9:
		
		if (!list_focus || (list_focus == 2))
		{
			int tmp;
			type = REMOTE_NUMBER;
			//当触摸到控件的时候弹出软键盘
			//inputtext->attachWithIME();
			tmp = KeyCode2int(keyCode);
			if (!list_focus)
			{
				fre_result = fre_result + std::to_string(tmp);
				if (fre_result.length() > 3)
				{
					fre_result = "";
				}
			}
			else if (list_focus == 2)
			{
				symbol_result = symbol_result + std::to_string(tmp);
				if (symbol_result.length() > 4)
				{
					symbol_result = "";
				}
			}
		}
		break;
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
	case EventKeyboard::KeyCode::KEY_BACK:
	case EventKeyboard::KeyCode::KEY_TV_BACK:
	case EventKeyboard::KeyCode::KEY_TV_EXIT:
		pInstance->skyScanStop();
		this->removeAllChildren();
		if (this->getParent())
		{
			this->getParent()->removeChild(this);
		}
		break;
	default:
		break;
	}
	log("get item_focus %d list_item  %d", item_focus, list_focus);
	drawCurrent((REMOTE_TYPE)type, list_focus, item_focus);
	return;
}


int DVBC_Manual_Scan::KeyCode2int(cocos2d::EventKeyboard::KeyCode keyCode)
{
	int index = 0;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_0:
		index = 0;
		break;
	case EventKeyboard::KeyCode::KEY_1:
		index = 1;
		break;
	case EventKeyboard::KeyCode::KEY_2:
		index = 2;
		break;
	case EventKeyboard::KeyCode::KEY_3:
		index = 3;
		break;
	case EventKeyboard::KeyCode::KEY_4:
		index = 4;
		break;
	case EventKeyboard::KeyCode::KEY_5:
		index = 5;
		break;
	case EventKeyboard::KeyCode::KEY_6:
		index = 6;
		break;
	case EventKeyboard::KeyCode::KEY_7:
		index = 7;
		break;
	case EventKeyboard::KeyCode::KEY_8:
		index = 8;
		break;
	case EventKeyboard::KeyCode::KEY_9:
		index = 9;
		break;
	default:
		break;
	}
	return index;
}



void DVBC_Manual_Scan::onBtnCancel_C(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	pInstance->skyScanStop();
	this->unschedule(schedule_selector(DVBC_Manual_Scan::completeCountDown));
	this->getParent()->removeChild(this);
}

void DVBC_Manual_Scan::onBtnScan_C(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	this->removeAllChildren();
	auto rootNode = CSLoader::createNode("MTuning.csb");
	Text *title;
	addChild(rootNode);
	
	m_rootNode = rootNode;
	m_rootNode->setPosition(Vec2(355, 326));
	title = (Text*)getRootByName_Common(m_rootNode,"ID_TEXT_TITLE");
	title->setString("DVB-C Manual Tuning");

	//m_btnFocused = nullptr;
	setBtnFunc(rootNode, "ID_BUT_NO", CC_CALLBACK_2(DVBC_Manual_Scan::onBtnCancel_C, this), nullptr);
	addKeyListener(CC_CALLBACK_2(BtnFocusLayer::onKeyPressed, this), m_rootNode);
	//TODO ManualScan
//	m_scanApi->skyAutoScanStart();
	//this->schedule(schedule_selector(DVBC_Manual_Scan::updataScanStatus), 1);
}
void DVBC_Manual_Scan::updataDataCounts(const char* nodeName, int counts)
{
	char str[64] = { 0 };
	Text* text = (Text*)m_rootNode->getChildByName(nodeName)->getChildByName("ID_TEXT_VALUE");
	sprintf(str, "%d", counts);
	if (text)
		text->setText(str);
}
void DVBC_Manual_Scan::updataScanStatus(float dt)
{
	if (!m_switch)
	{
		LoadingBar* bar = (LoadingBar*)rootNode->getChildByName("LoadingBar_1");
		bar->setPercent(tvdata->signal_quality);
	}
	else
	{
		updataDataCounts("ID_TEXT_ALL", tvdata->digitaltv_count + tvdata->radio_count + tvdata->data_count);
		updataDataCounts("ID_TEXT_DTV", tvdata->digitaltv_count); //??DTV is tv_count
		updataDataCounts("ID_TEXT_RADIO", tvdata->radio_count);
		LoadingBar* bar = (LoadingBar*)m_rootNode->getChildByName("ID_PROGRESS");
		bar->setPercent(tvdata->process);
		if (tvdata->scanstatus == STATUS_SKYSCAN_TUNING_END)
		{
			this->unschedule(schedule_selector(DVBC_Manual_Scan::updataScanStatus));
			onTuningComplete();
		}
	}

	
	/*
	skyScanCallbackData scandata;
	skyScanStatus scanstatus = (skyScanStatus)0;
	if (scanstatus == skyScanStatus::FAILED || scanstatus == skyScanStatus::TIMEOUT)
	{
		this->unschedule(schedule_selector(DVBC_Manual_Scan::updataScanStatus));
		//TODO failed deal

	}
	else if (scanstatus == skyScanStatus::ALLFREQ_FINSH)
	{
		//TODO 
		this->unschedule(schedule_selector(DVBC_Manual_Scan::updataScanStatus));
		onTuningComplete();
		//skyScanCallbackData scandata = m_scanApi->getScanData();
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
	}*/
}
void DVBC_Manual_Scan::onTuningComplete()
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

	pInstance->skyScanStop();
	m_countDown = 5;
	this->schedule(schedule_selector(DVBC_Manual_Scan::completeCountDown), 1);
}
void DVBC_Manual_Scan::completeCountDown(float dt)
{
	if (m_countDown > 0)
	{
		m_countDown--;
		char str[64] = { 0 };
		sprintf(str, "Close(%ds)", m_countDown);
		setBtnTitle(m_rootNode, "ID_BUT_NO", str);
	}
	else {
		this->unschedule(schedule_selector(DVBC_Manual_Scan::completeCountDown));
		this->getParent()->removeChild(this);
		pInstance->skyScanStop();
	}
}