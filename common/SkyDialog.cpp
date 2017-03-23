#include "cocos2d.h"
#include "common/SkyDialog.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
SkyDialog::SkyDialog()
{
	m_btnFocused = nullptr;
	m_rootNode = nullptr;
	m_callListener = nullptr;
}
SkyDialog::~SkyDialog()
{

}

SkyDialog* SkyDialog::create(cocos2d::Node* root, const std::string& filename, Click_CallFun callfuncl, Click_CallFun callfuncr, cocos2d::Ref* listener)
{
	if (root == nullptr)
		return nullptr;
	auto rootNode = CSLoader::createNode(filename);
	return SkyDialog::create(root,rootNode, callfuncl, callfuncr, listener);
	 
}
SkyDialog* SkyDialog::create(cocos2d::Node* root,cocos2d::Node* node, Click_CallFun callfuncl, Click_CallFun callfuncr, cocos2d::Ref* listener)
{
	if (root == nullptr)
		return nullptr;
	SkyDialog *pRet = new(std::nothrow) SkyDialog(); 
		if (pRet && pRet->init()) 
		{ 
			pRet->autorelease();
			pRet->addBtnlClick(callfuncl);
			pRet->addBtnrClick(callfuncr);
			pRet->setCallListener(listener);
			pRet->addChild(node);	
			Size size = node->getContentSize();
			pRet->setContentSize(size);
			pRet->setRootNode(node);
			pRet->setPosition(Vec2(1920/2-size.width/2,1080/2-size.height/2));
			node->setName("SKY_DIA");
			pRet->initDia();
			root->addChild(pRet);
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
}
void SkyDialog::setTextTitle(const char* nodeName, const char* textTitle)
{
	if (m_rootNode)
	{
		Text* text = (Text*)m_rootNode->getChildByName(nodeName);
		if (text) {
			text->setString(textTitle);
		}
	}
}
void SkyDialog::setBtnTitle(const char* nodeName, const char* textTitle)
{
	if (m_rootNode)
	{
		Button* btn = (Button*)m_rootNode->getChildByName(nodeName);
		if (btn) {
			btn->setTitleText(textTitle);
		}
	}
}
bool SkyDialog::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->addKeyListener(CC_CALLBACK_2(SkyDialog::onKeyPressed, this), this);
	return true;
}
void SkyDialog::initDia()
{
	auto node = this->getChildByName("SKY_DIA");
	Button* btn = (Button*)node->getChildByName("ID_BUT_YES");
	m_btnFocused = nullptr;
	if (btn) {
		btn->addTouchEventListener(CC_CALLBACK_2(SkyDialog::onBtnYes, this));
		m_btnFocused = btn;
	}
	btn = (Button*)node->getChildByName("ID_BUT_NO");
	if (btn) {
		btn->addTouchEventListener(CC_CALLBACK_2(SkyDialog::onBtnNo, this));
		if (!m_btnFocused)
			m_btnFocused = btn;
	}
	onFocusChanged(nullptr, m_btnFocused);
}
void SkyDialog::onBtnYes(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (m_callFuncl)
	{
		if (m_callListener)
			(m_callListener->*m_callFuncl)(this);
		else
		    (this->getParent()->*m_callFuncl)(this);
	}
	this->getParent()->removeChild(this);
}
void SkyDialog::onBtnNo(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (m_callFuncr)
	{
		if (m_callListener)
			(m_callListener->*m_callFuncr)(this);
		else
		    (this->getParent()->*m_callFuncr)(this);
	}
	this->getParent()->removeChild(this);
}

