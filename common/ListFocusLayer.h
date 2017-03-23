#ifndef  _LISTFOCUS_LAYER_H_
#define  _LISTFOCUS_LAYER_H_
#include "cocos2d.h"
#include "common/common.h"
#include "common/SkyLayer.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "ui/UILayout.h" 
#include "ui/UIWidget.h" 
#include "epg/GridView/GridView.h"
typedef void (cocos2d::Ref::*Click_CallFun)(cocos2d::Node* node);
class ListFocusLayer :
	public SkyLayer
{
public:
	ListFocusLayer();
	~ListFocusLayer();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);
	virtual bool onFocusChanged(int next, cocos2d::ui::Widget::FocusDirection direction,bool isscroll = true);
	bool parseUserData(char *in, char * matching, char* out);
	void addCellClick(Click_CallFun callfunc) { m_callFunclick = callfunc; };
	cocos2d::ui::Button* getFocused() { return m_btnFocused; };
	bool findNextFocus(int &next,cocos2d::ui::Widget::FocusDirection direction);
	bool findHorNextFocus(int &next, cocos2d::ui::Widget::FocusDirection direction);
	void setRowNum(int rowNums) {	m_rowNums = rowNums; };
	int getRowNum() {	return m_rowNums;	};
	void setColNum(int colNums) { m_colNums = colNums; };
	int getColNum() { return m_colNums; };
	void setCellNum(int cellNums) { m_cellNums = cellNums; };
	int getCellNum() { return m_cellNums; };
	cocos2d::extension::TableViewCell* getFocusCell() { return m_focusCell; };
	int getFocusIdx() { return m_focusIdx; };
protected:
	cocos2d::ui::Button* m_btnFocused;
	Click_CallFun m_callFunclick;
	GridView* m_gridView;
	int m_rowNums;
	int m_colNums;
	int m_cellNums;
	int m_focusIdx;
	int m_focusCol;
	int m_focusRow;
protected:
	Click_CallFun m_callFunc;
	cocos2d::extension::TableViewCell* m_focusCell;
	bool m_bFocus;
};
#endif

