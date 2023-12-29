#define isDown(b) input->buttons[b].isDown
#define pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define released(b) (!input->buttons[b].isDown && input->buttons[b].changed)

float playerPositionX = 0.f;
float playerPositionY = 0.f;

internalVariable void simulateGame(Input* input) {
	clearScreen(0xffff00);
	if (pressed(BUTTON_UP)) playerPositionY += 1.f;
	if (pressed(BUTTON_DOWN)) playerPositionY -= 1.f;
	if (pressed(BUTTON_LEFT)) playerPositionX -= 1.f;
	if (pressed(BUTTON_RIGHT)) playerPositionX += 1.f;

	drawRectangle(playerPositionX, playerPositionY, 1, 1, 0xc8a2c8);
	drawRectangle(playerPositionX+30, playerPositionY+30, 5, 5, 0x000000);
	drawRectangle(playerPositionX-20, playerPositionY+20, 8, 8, 0xffffff);
}