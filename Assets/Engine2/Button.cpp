#include "Button.h"

void Button::RefreshFunction()
{
	if (state == ButtonState::release) {
		if (function) {
			function();
		}
	}
}

void Button::RefreshClickState(MouseClient mouse)
{

	if (!isHover(mouse)) {
		state = ButtonState::normal;
	}

	else { //!isHover(mouse)
		if (isPress(mouse)) {
			state = ButtonState::press;
		}

		else { // !isPress(mouse)
			if (state == ButtonState::press) {
				state = ButtonState::release;
			}
			else { //state != ButtonState::press
				state = ButtonState::hover;
			}
		}

	}


}