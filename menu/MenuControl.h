#ifndef  _MenuControl_H_
#define  _MenuControl_H_
#include "cocos2d.h"

class MenuControl
{
public:
	MenuControl();
	~MenuControl();	

	void addXmlFile(const std::string& xml) { m_xmlName = xml; };
	std::string getXmlFile() { return m_xmlName; };
	///// for left/right radio and on/off
	virtual void addItem(const std::string& str) { ; };
	virtual bool getItemNext(std::string& str) { return false; };
	virtual bool getItemLast(std::string& str) { return false; };
	virtual bool getItemCur(std::string& str) { return false; };
	virtual bool setItemCur(const std::string& str) { return false; };
	virtual std::vector<std::string> getItemVec() { std::vector<std::string> vec; return vec; };

	/////

	///// for adjust
	virtual void setMinValue(int value) { ; };
	virtual void setMaxValue(int value) { ; };
	virtual int getCurValue() { return 0; };
	virtual void setCurValue(int value,cocos2d::Node* rootNode = nullptr) { ; };
	/////


	///// for up/down radio
	virtual void setItemHeight(float height) { ; };
	virtual void setItemWidth(float width) { ; };
	virtual void setTableHeight(float height) { ; };

	virtual float getItemHeight() { return 0; };
	virtual float getItemWidth() { return 0; };
	virtual float getTableHeight() { return 0; };
	/////

	virtual void initNode(float cellWidth,float cellHeight) { ; };
	virtual bool onKeyLeft(cocos2d::Node* rootNode) { return false; };
	virtual bool onKeyRight(cocos2d::Node* rootNode) { return false; };

	void setType(int type) { m_type = type; };
	void setName(const std::string &name) { m_name = name; };
	void setCellWidth(float width) { m_cellWidth = width; };
	void setCellHeight(float height) { m_cellHeight = height; };
	void setEnable(bool enable) { m_enable = enable; };
	void addNode(cocos2d::Node* node) { m_nodes.push_back(node); };
	void addAssocNums(int num) { m_assocVec.push_back(num); };
	void addAssocName(const std::string name) { m_assocNameVec.push_back(name); };
	void assocAction(std::vector<MenuControl*> menuvec);
	int getType() { return m_type; };
	std::string getName() { return m_name; };
	float getCellWidth() { return m_cellWidth; };
	float getCellHeight() { return m_cellHeight; };
	bool getEnable() { return m_enable; };

	std::vector<cocos2d::Node*> getNodes() { return m_nodes;};

protected:
	int m_type;
	std::string m_name;
	float m_cellHeight;
	float m_cellWidth;
	bool m_enable;
	std::vector<cocos2d::Node*> m_nodes;
	std::vector<int> m_assocVec;
//	std::string m_assocName;
	std::vector<std::string> m_assocNameVec;
	std::string m_xmlName;
};


class LFRaidoControl :public MenuControl
{
public:
	LFRaidoControl() {
		m_index = 0;
	};
	void setIndex(int index) { m_index = index; };
	int getIndex() { return m_index; };
	virtual void initNode(float cellWidth, float cellHeight);
	virtual std::vector<std::string> getItemVec() { return m_itemName; };
	virtual void addItem(const std::string& str) { m_itemName.push_back(str); };
	virtual bool getItemNext(std::string& str) {
		if (m_index < m_itemName.size() - 1) {
			m_index++;
		}
		else
			m_index = 0;
		str = m_itemName.at(m_index);
		return true;
	};
	virtual bool getItemLast(std::string& str) {
		if (m_index > 0) {
			m_index--;
		}
		else
			m_index = m_itemName.size() - 1;
		str = m_itemName.at(m_index);
		return true;
	};
	virtual bool getItemCur(std::string& str) { 
		if (m_itemName.size() > 0)
		{
			str = m_itemName.at(m_index);
			return true;
		}
		return false;
	};
	virtual bool setItemCur(const std::string& str);
	virtual bool onKeyLeft(cocos2d::Node* rootNode);
	virtual bool onKeyRight(cocos2d::Node* rootNode);
protected:
	int m_index;
	std::vector<std::string> m_itemName;
};

class SwitchControl :public LFRaidoControl
{
public:
	SwitchControl()
	{
		addItem("On");
		addItem("Off");
	}
};

class UDRadioControl :public LFRaidoControl
{
public:
	UDRadioControl()
	{
		m_cellWidth = 0;
		m_cellHeight = 0;
		m_tableHeight = 0;
	}
	virtual bool onKeyLeft(cocos2d::Node* rootNode) { return false; };
	virtual bool onKeyRight(cocos2d::Node* rootNode) { return false; };
	virtual void initNode(float cellWidth, float cellHeight) ;
	virtual void setItemHeight(float height) { m_itemHeight = height; };
	virtual void setItemWidth(float width) { m_itemWidth = width; };
	virtual void setTableHeight(float height) { m_tableHeight = height; };

	virtual float getItemHeight() { return m_itemHeight; };
	virtual float getItemWidth() { return m_itemWidth; };
	virtual float getTableHeight() { return m_tableHeight; };
protected:
	float m_itemWidth;
	float m_itemHeight;
	float m_tableHeight;
};

class AdjustControl : public MenuControl
{
public:
	AdjustControl() { 
		m_minValue = 0;
		m_maxValue = 100;
		m_curValue = 50;
	};

	virtual void setMinValue(int value) { m_minValue = value; };
	virtual void setMaxValue(int value) { m_maxValue = value; };
	virtual bool onKeyLeft(cocos2d::Node* rootNode);
	virtual bool onKeyRight(cocos2d::Node* rootNode);
	virtual void initNode(float cellWidth, float cellHeight);
	virtual bool setItemCur(const std::string& str) ;
	virtual bool getItemCur(std::string& str);
	void setCurValue(int value,cocos2d::Node* rootNode = nullptr);
	virtual int getCurValue() { return m_curValue; };

protected:
	float m_minValue;
	float m_maxValue;
	int m_curValue;
	float m_startPosition;
};

class NumsRadioControl :public AdjustControl
{
public:
	virtual bool onKeyLeft(cocos2d::Node* rootNode);
	virtual bool onKeyRight(cocos2d::Node* rootNode);
	void setCurValue(int value, cocos2d::Node* rootNode = nullptr);
	virtual void initNode(float cellWidth, float cellHeight);
};

#endif

