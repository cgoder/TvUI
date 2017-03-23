#include "common/BaseTableViewCell.h"

USING_NS_CC;

void BaseTableViewCell::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	TableViewCell::draw(renderer, transform, flags);
}
void BaseTableViewCell::onCellClick()
{
	if (m_cellClick)
	    (m_cellListener->*m_cellClick)(this);
}
