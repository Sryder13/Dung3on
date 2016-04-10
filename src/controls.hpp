#ifndef CONTROLS_H
#define CONTROLS_H

#include<iostream>

enum buttons
{
	BUTTON_UP = 0x01,
	BUTTON_RIGHT = 0x02,
	BUTTON_DOWN = 0x04,
	BUTTON_LEFT = 0x08,
	BUTTON_EXIT = 0x10,
};

class controls
{
	public:
		controls();
		void pressButton(buttons button);
		void updateheldButtons();
		void unpressButton(buttons button);

		int getPressedButtons() {return this->pressedButtons;}
		int getHeldButtons() {return this->heldButtons;}
	protected:
	private:
		int pressedButtons; // These buttons are currently being pressed
		int heldButtons; // These buttons are currently being held (pressed for more than 1 frame)
};

#endif // CONTROLS_H
