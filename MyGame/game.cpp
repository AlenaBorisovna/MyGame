internalVariable void simulateGame(Input* input) {
	clearScreen(0xff5500);
	if (isDown(BUTTON_UP))
		drawRectangle(0, 0, 10, 10, 0x00ff22);
	drawRectangle(30, 30, 5, 5, 0xffff22);
	drawRectangle(-25, 20, 8, 3, 0x00ff22);
}