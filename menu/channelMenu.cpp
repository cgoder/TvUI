#include "cocos2d.h"
#include "menu/channelMenu.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "common/BaseTableViewCell.h"
#include "epg/GridView/GridView.h"
#include "AutoTuning/AutoTuning.h"
#include "ManualScan/DVBT_ManualScan.h"
#include "ChannelEdit/ChannelEdit.h"
#include "ManualScan/ManualScan.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
channelMenu::channelMenu()
{
	this->setName("channelMenu");
	m_btnFocused = nullptr;
	m_focusIdx = 0;
	m_focusCol = 0;
	m_focusRow = 0;
	m_gridView = nullptr;
	m_callFunc = nullptr;
	m_menuIdx = 0;
}
channelMenu::~channelMenu()
{
	
}


Layer* channelMenu::creatLayer(cocos2d::Node* node, int cols,int rows,int cells,Click_CallFun callFunc)
{
	if (node) {
		Layer* tuning = (Layer*)node->getChildByName("channelMenu");
		if (tuning) {
			return tuning;
		}
		else {
			channelMenu* pRet =(channelMenu*) channelMenu::create();
			pRet->addCallBack(callFunc);
			pRet->setColNum(cols);
			pRet->setRowNum(rows);
			pRet->setCellNum(cells);
			
			pRet->addMenuStr("Auto Tuning");
			pRet->addMenuStr("Manual Tuning");
			pRet->addMenuStr("Channel edit");
			pRet->addMenuStr("Signal Info");
			pRet->addMenuStr("text5");
			pRet->initTableView();
			node->addChild(pRet);
			return pRet;
		}
	}
	return nullptr;
}

bool channelMenu::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		bRet = true;
	} while (0);
	this->addKeyListener(CC_CALLBACK_2(ListFocusLayer::onKeyPressed, this), this);
	return bRet;
}
void channelMenu::onCellClick(cocos2d::Node* node)
{
	auto scene = Director::getInstance()->getRunningScene();
	switch (m_focusIdx)
	{
	case 0:
		AutoTuning::creatLayer(scene,3);
		break;
	case 1:
		Manual_Scan::creatLayer(scene);
		break;
	case 2:
		ChannelEdit::creatLayer(scene);
		break;
	}
	this->getParent()->getParent()->removeChild(this->getParent());
}