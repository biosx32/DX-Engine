#include "MouseRegion.h"

int MouseRegion::_IDC = 0;
void MouseRegion::Draw ()
{
	Color clr = (!isHover()) ? Colors::Blue : Colors::Green;
	clr = (isLockedOn()) ? Colors::Red : clr;


	if (!const_size) {
		size = parent->property.GetSize ();
	}

	Vector2 pos = this->GetStartPos ();



	//PrintTextAlign (BaseElement::draw, GetCenterOf(pos,size), parent->property.font, 1, ALIGN_VH, name);
	BaseElement::draw->paint->rectangleBorder (pos.x, pos.y, size.x, size.y, clr, 2);

	/*BaseElement::draw->paint->circleBorder (pos.x + size.x / 2,
	pos.y + size.y / 2,
	size.x, clr, 1);

	BaseElement::draw->paint->circleBorder (pos.x + size.x / 2,
	pos.y + size.y / 2,
	1 * size.x / 3, clr, 1);*/

}

void MouseRegion::Update ()
{
	MouseHelper* mhelper = BaseElement::io->mhelper;

	if (mhelper->IsMouseUsedBy (ID)) {
		if (!mhelper->mouse->LeftIsPressed ()) {
			mhelper->ReleaseLock ();
			click_count += 1;
		}
	}

	if (isHover ()) {
		if (mhelper->CanBeUsedBy (ID)) {
			if (isPress ()) {
				mhelper->LockMouse (this->ID);
			}
		}

	}


	if (function) {
		if (GetClick ()) {
			function ();
		}
	}
}

bool MouseRegion::isHover ()
{
	Vector2 ePos = this->GetStartPos ();
	Vector2 mPos = BaseElement::io->mhelper->position;
	return mPos.x >= ePos.x && mPos.y >= ePos.y &&
		mPos.x < ePos.x + size.x &&
		mPos.y < ePos.y + size.y;
}

bool MouseRegion::isPress ()
{
	if (BaseElement::io->mouse->LeftIsPressed ()) {
		if (isHover ()) {
			return true;
		}
	}
	return false;
}


