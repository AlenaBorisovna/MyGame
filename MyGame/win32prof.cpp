#include "utils.cpp"
#include <windows.h>
#include <iostream>
/*

wnd - window
proc - process
h - handler

UINT - unsigned integer
param - parameter
l - long
rect - rectangle >> прямоугольник
alloc - allocate - размечать память

default - по умолчанию
use - использовать
destroy - разрушить
close - закрыть

	 top
left      right
	bottom
*/

globalVariable bool running = true;

struct RenderState {
	void* memory;
	int width;
	int height;
	BITMAPINFO bitmapInfo;
};
globalVariable RenderState renderState;
#include "platforme_com.cpp"
#include "rendere.cpp"

LRESULT CALLBACK windowClick(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
	} break;

	case WM_SIZE: {
		RECT rect;
		GetClientRect(hWnd, &rect); // функция размера прямоугольника

		renderState.width = rect.right - rect.left; // ширина окна
		renderState.height = rect.bottom - rect.top; // высота окна

		int bufferSize = renderState.width * renderState.height * sizeof(unsigned int); // высчитываем размер буфера

		if (renderState.memory) // выяснем есть память 
			VirtualFree(renderState.memory, 0, MEM_RELEASE); // освождаем память
		renderState.memory = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); // записываем новую память

		renderState.bitmapInfo.bmiHeader.biSize = sizeof(renderState.bitmapInfo.bmiHeader);
		renderState.bitmapInfo.bmiHeader.biWidth = renderState.width;
		renderState.bitmapInfo.bmiHeader.biHeight = renderState.height;
		renderState.bitmapInfo.bmiHeader.biPlanes = 1;
		renderState.bitmapInfo.bmiHeader.biBitCount = 32;
		renderState.bitmapInfo.bmiHeader.biCompression = BI_RGB;

	} break;

	default: {
		result = DefWindowProc(hWnd, uMsg, wParam, lParam);
	} break;
	}
	return result;
};

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// создать класс window
	WNDCLASS WindowClass = {};
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpszClassName = TEXT("Game Window Class");
	WindowClass.lpfnWndProc = windowClick;

	// зарегистрировать этот класс
	RegisterClass(&WindowClass);

	// создать окно по шаблону
	HWND window = CreateWindow(WindowClass.lpszClassName, TEXT("Pong - Tutorial"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	Input input = {};

	while (running)
	{
		// ввод
		MSG message;

		for (size_t i = 0; i < BUTTON_COUNT; i++)
		{
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				u32 vkCode = (u32)message.wParam;
				bool isDown = ((message.lParam & (1 << 31)) == 0);

				switch (vkCode) {
				case VK_UP: {
					input.buttons[BUTTON_UP].isDown = true;
					input.buttons[BUTTON_UP].changed = true;
				} break;
				}

			} break;
			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}
		}
		// симуляция - процесс игры
		clearScreen(0xff5500);
		if (input.buttons[BUTTON_UP].isDown)
			drawRectangle(0, 0, 1, 1, 0x00ff22);
		drawRectangle(30, 30, 5, 5, 0xffff22);
		drawRectangle(-20, 20, 8, 3, 0xffff22);
		// симуляция - процесс игры
		//renderBackground();
		clearScreen(0xff5500);
		drawRectangle(0, 0, 10, 10, 0x00ff22);
		drawRectangle(30, 30, 5, 5, 0xffff22);
		drawRectangle(-25, 20, 8, 3, 0x00ff22);

		// перерисовка
		StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0, renderState.width, renderState.height, renderState.memory, &renderState.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}
};
