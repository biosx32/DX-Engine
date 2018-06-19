#include "Static.h"
#include "MouseRegion.h"

void MouseRegion::Draw ()
{
	
	Color c = (state == MouseState::pressed) ? Colors::Green : Colors::Blue;
	c = state < 1 ? Colors::Red : c;

	Vector2 pos = parent->property.GetAbs () + offset;
	Vector2 size = parent->property.GetSize ();

	PrintText (BaseElement::draw, pos, parent->property.font, 0.75, name);
	BaseElement::draw->paint->rectangleBorder (pos.x, pos.y, size.x, size.y, Colors::Red, 2);

	BaseElement::draw->paint->circleBorder (pos.x + size.x / 2,
		pos.y + size.y / 2,
		size.x, c, 1);

	BaseElement::draw->paint->circleBorder (pos.x + size.x / 2,
		pos.y + size.y / 2,
		1 * size.x / 3, c, 1);

	Vector2 lpos =
		Pos (pos.x + size.x / 2 - BaseElement::DFONT->charw * name.size () / 2,
			pos.y + size.y / 2 - BaseElement::DFONT->charh / 2);
	


}

void MouseRegion::Update ()
{
	if (isHover ()) {
		if (isPress ()) {
			if (BaseElement::io->mhelper->CanBeUsedBy (parent->property.ID)) {
				state = MouseState::pressed;
				BaseElement::io->mhelper->LockMouse (parent->property.ID);
			}
		}
		else {
			state = MouseState::hovered;
			if (BaseElement::io->mhelper->IsMouseUsedBy (parent->property.ID)) {
				click_count += 1;
				BaseElement::io->mhelper->ReleaseLock ();
			}
		}
	}
	else { state = MouseState::none; }

	if (function) {
		if (GetClick()) {
			function ();
		}
	}

}

bool MouseRegion::isHover ()
{
	Vector2 mPos = Vector2 (BaseElement::io->mouse->GetMouseX (), BaseElement::io->mouse->GetMouseY ());
	Vector2 ePos = parent->property.GetAbs () + offset;
	return mPos.x >= ePos.x && mPos.y >= ePos.y &&
		mPos.x < ePos.x + parent->property.size.x &&
		mPos.y < ePos.y + parent->property.size.y;
}

bool MouseRegion::isPress ()
{
	if (BaseElement::io->mouse->LeftIsPressed ()) {
		if (isHover ()) {
			return BaseElement::io->mhelper->CanBeUsedBy (parent->property.ID);
		}
	}
	return false;
}

