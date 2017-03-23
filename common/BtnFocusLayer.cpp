#include "cocos2d.h"
#include "common/BtnFocusLayer.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
BtnFocusLayer::BtnFocusLayer()
{
	m_btnTempFocused = nullptr;
	m_btnFocused = nullptr;
}
BtnFocusLayer::~BtnFocusLayer()
{
}
void BtnFocusLayer::checkBtnText(cocos2d::ui::Button* node, Touch touch)
{
	button_user_data* data = (button_user_data*)node->getUserData();
	if (data && data->type == BUTTON_TYPE::TYPE_TEXT)
	{
		node->onTouchBegan(&touch, NULL);
		node->onTouchEnded(&touch, NULL);
	}
}
void BtnFocusLayer::findNextFocus(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event, char* direction)
{
	auto pnode = m_btnTempFocused->getParent();
	Button* next;
	Touch touch;
	char nextFocuname[128] = { 0 };
	auto userdate = ((cocostudio::ComExtensionData*)(m_btnTempFocused->getComponent("ComExtensionData")))->getCustomProperty();
	const char* cuserdata = userdate.c_str();
	if (parseUserData((char*)cuserdata, direction, nextFocuname)) {
		next = (Button*)(pnode->getChildByName(nextFocuname));
		if (next) {
			if (!next->isEnabled())
			{
				m_btnTempFocused = next;
				findNextFocus(keyCode, unused_event, direction);
			}
			else
			{
				onFocusChanged(m_btnFocused, next);
				m_btnFocused = next;
				m_btnTempFocused = m_btnFocused;
				checkBtnText(m_btnFocused, touch);
			}
		}
		else
			m_btnTempFocused = m_btnFocused;
	}
	else
		m_btnTempFocused = m_btnFocused;
}

void BtnFocusLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
//	if (!m_btnTempFocused)
		m_btnTempFocused = m_btnFocused;
	this->stopPropagation(keyCode, unused_event);
	if (m_btnFocused != nullptr)
	{
		int current = m_btnTempFocused->getTag();
		auto pnode = m_btnTempFocused->getParent();
		Touch touch;
		Button* next;
		char nextFocuname[128] = { 0 };
		auto userdate = ((cocostudio::ComExtensionData*)(m_btnTempFocused->getComponent("ComExtensionData")))->getCustomProperty();
		const char* cuserdata = userdate.c_str();
		log("keyCode:%d,userdata:%s,", keyCode, cuserdata);
		//(char*)m_btnFocused->getUserData();
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
			findNextFocus(keyCode, unused_event,"left=");			
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
			findNextFocus(keyCode, unused_event, "right=");
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_UP:
			findNextFocus(keyCode, unused_event, "up=");
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_DPAD_DOWN:
			findNextFocus(keyCode, unused_event, "down=");
			break;
		case EventKeyboard::KeyCode::KEY_ENTER:
		case EventKeyboard::KeyCode::KEY_DPAD_CENTER:
			m_btnFocused->onTouchBegan(&touch, NULL);
			m_btnFocused->onTouchEnded(&touch, NULL);
			break;
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:
			//TODO for back
			this->getParent()->removeChild(this);
			break;
		default:
			break;
		}
	}
	else {
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_BACKSPACE:
		case EventKeyboard::KeyCode::KEY_BACK:
		case EventKeyboard::KeyCode::KEY_TV_BACK:
		case EventKeyboard::KeyCode::KEY_TV_EXIT:
			//TODO for back
			this->getParent()->removeChild(this);
			break;
		default:
			break;
		}
	}
}
void BtnFocusLayer::onFocusChanged(cocos2d::Node *nodeLostFocus, cocos2d::Node *nodeGetFocus)
{
	if (nodeLostFocus)
	{
		if (dynamic_cast<Button*>(nodeLostFocus))
		{
			((Button*)nodeLostFocus)->setTitleColor(Color3B(51, 51, 51));
		}

		nodeLostFocus->removeChildByName("ID_PIC_FOCUS");
		Vector<cocos2d::Node*> pChildren = nodeLostFocus->getChildren();
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
	if (nodeGetFocus)
	{
		ImageView  * focus = ImageView::create("general/general_button_focus.png");
		focus->setScale9Enabled(true);
		focus->setCapInsets(Rect(40, 16, 135, 73));
		Size size = nodeGetFocus->getContentSize();
		int w = size.width;
		int h = size.height;
		focus->setContentSize(Size(w + 60, h + 60));
		focus->setPosition(Vec2(w / 2, h / 2 - 26));
		focus->setZOrder(-1);
		focus->setName("ID_PIC_FOCUS");
		nodeGetFocus->addChild(focus);
		if (dynamic_cast<Button*>(nodeGetFocus))
		{
			((Button*)nodeGetFocus)->setTitleColor(Color3B(0, 0, 0));
		}
		Vector<cocos2d::Node*> pChildrenFocus = nodeGetFocus->getChildren();
		for (Node *node : pChildrenFocus)
		{
			if (dynamic_cast<Text*>(node))
			{
				((Text*)node)->setColor(Color3B(0, 0, 0));
			}
			if (dynamic_cast<Button*>(node))
			{
				((Button*)node)->setHighlighted(true);
			}
		}
	}
}
bool BtnFocusLayer::parseUserData(char *in, char * matching, char* out) {
	if (!in)
		return false;
	char *find = NULL;
	if (NULL != (find = strstr(in, matching))) {
		find += strlen(matching);//strlen("key=")
		sscanf(find, "%[^&]", out);
		return true;
	}
	return false;
}
Button* BtnFocusLayer::setBtnFunc(cocos2d::Node* rootNode, const char* nodeName, std::function<void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType)> func, void* userdata)
{
	Button*  btn = (Button*)rootNode->getChildByName(nodeName);
	if (btn) {
		btn->addTouchEventListener(func);
		btn->setUserData(userdata);
		if (!m_btnFocused)
		{
			m_btnFocused = btn;
			m_btnTempFocused = m_btnFocused;
			onFocusChanged(nullptr, m_btnFocused);
		}
	}
	return btn;
}
void BtnFocusLayer::setTextTitle(Node* rootNode,const char* nodeName, const char* textTitle)
{
	if (rootNode)
	{
		Text* text = (Text*)rootNode->getChildByName(nodeName);
		if (text) {
			text->setString(textTitle);
		}
	}
}
void BtnFocusLayer::setBtnTitle(Node* rootNode, const char* nodeName, const char* textTitle)
{
	if (rootNode)
	{
		Button* btn = (Button*)rootNode->getChildByName(nodeName);
		if (btn) {
			btn->setTitleText(textTitle);
		}
	}
}
