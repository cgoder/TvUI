#ifndef __BASE_TABELVIEWCELL_H__
#define __BASE_TABELVIEWCELL_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
typedef void (cocos2d::Ref::*Click_CallFun)(cocos2d::Node* node);
class BaseTableViewCell : public cocos2d::extension::TableViewCell
{
public:
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
	void addBtnlClick(Click_CallFun callfunc,cocos2d::Ref* listener) 
	{ 
		m_cellClick = callfunc; 
		m_cellListener = listener;
	};
	void onCellClick();
protected:
	cocos2d::Ref* m_cellListener;
	Click_CallFun m_cellClick;
};

#endif /* __CUSTOMTABELVIEWCELL_H__ */

