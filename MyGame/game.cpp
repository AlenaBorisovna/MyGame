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
	// 3
	drawRectangle(playerPositionX+3, playerPositionY+3, 2, 5, 0x);
	drawRectangle(playerPositionX+3, playerPositionY+6, 2, 4, 0xdc143c);
	drawRectangle(playerPositionX+0, playerPositionY-1, 4, 2, 0xdc143c);
	drawRectangle(playerPositionX+0, playerPositionY+4, 4, 1, 0xdc143c);
	drawRectangle(playerPositionX+0, playerPositionY+9, 4, 2, 0xdc143c);
	// 0
	drawRectangle(playerPositionX+14, playerPositionY+3, 2, 6, 0xdc143c);
	drawRectangle(playerPositionX+17, playerPositionY+9, 4, 1, 0xdc143c);
	drawRectangle(playerPositionX+20, playerPositionY+3, 2, 6, 0xdc143c);
	drawRectangle(playerPositionX+17, playerPositionY-3, 4, 1, 0xdc143c);
}