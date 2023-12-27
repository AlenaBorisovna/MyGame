struct  ButtonState {
	bool isDown;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_Down,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	BUTTON_COUNT
};

struct  Input {
	ButtonState buttons[BUTTON_COUNT];
};