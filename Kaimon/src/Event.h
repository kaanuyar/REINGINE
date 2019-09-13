#pragma once


class Event
{
public:
	enum State : int
	{
		MOUSE_BUTTON_MIDDLE_PRESSED = 0,
		MOUSE_BUTTON_MIDDLE_RELEASED,
		MOUSE_BUTTON_MIDDLE_DRAGGED,
		MOUSE_BUTTON_RIGHT_PRESSED,
		MOUSE_BUTTON_RIGHT_RELEASED,
		MOUSE_BUTTON_RIGHT_HELD,
		MOUSE_SCROLL,

		KEY_W, KEY_S, KEY_A, KEY_D,
		KEY_R, 
		KEY_UP, KEY_DOWN,
		WINDOW_RESIZE
	};

	Event(State state, bool isAlive, float x = 0.0f, float y = 0.0f, float z = 0.0f) 
		: state(state), isAlive(isAlive), x(x), y(y), z(z), isProcessed(false)  { }

	State state;
	bool isAlive;
	bool isProcessed;
	float x, y, z;

};
