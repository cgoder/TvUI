#include "CustomTableViewCell.h"

USING_NS_CC;

void CustomTableViewCell::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	TableViewCell::draw(renderer, transform, flags);
	// draw bounding box
// 		Vec2(pos.x+size.width-1, pos.y+1),
// 		Vec2(pos.x+size.width-1, pos.y+size.height-1),
// 		Vec2(pos.x+1, pos.y+size.height-1),
// 	};
 	//DrawPrimitives::setDrawColor4B(128, 0, 0, 128);
	//DrawPrimitives::drawLine(Vec2(0,0),Vec2(700,0));
}
