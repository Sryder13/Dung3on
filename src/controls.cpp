#include "controls.hpp"

controls::controls()
{
	pressedButtons = 0;
	heldButtons = 0;
}

void controls::pressButton(buttons button)
{
	pressedButtons |= button;
}

void controls::updateheldButtons()
{
    heldButtons = pressedButtons;
}

void controls::unpressButton(buttons button)
{
	pressedButtons &= ~button;
}
