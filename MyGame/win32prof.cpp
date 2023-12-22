#include <windows.h>

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

bool running = true;

void* bufferMemory;
int bufferWidth;
int bufferHeight;
BITMAPINFO bufferBitmapInfo;

LRESULT CALLBACK windowClick(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
	} break;

	case WM_SIZE: {
		RECT rect;
		GetClientRect(hWnd, &rect);

		bufferWidth = rect.right - rect.left;
		bufferHeight = rect.bottom - rect.top;

		int bufferSize = bufferWidth * bufferHeight * sizeof(unsigned int);

		if (bufferMemory)
			VirtualFree(bufferMemory, 0, MEM_RELEASE);
		bufferMemory = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		bufferBitmapInfo.bmiHeader.biSize = sizeof(bufferBitmapInfo.bmiHeader);
		bufferBitmapInfo.bmiHeader.biWidth = bufferWidth;
		bufferBitmapInfo.bmiHeader.biHeight = bufferHeight;
		bufferBitmapInfo.bmiHeader.biPlanes = 1;
		bufferBitmapInfo.bmiHeader.biBitCount = 32;
		bufferBitmapInfo.bmiHeader.biCompression = BI_RGB;

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

	// создать окно
	HWND window = CreateWindow(WindowClass.lpszClassName, TEXT("Pong - Tutorial"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	while (running)
	{
		// ввод
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		// симуляция - процесс игры

		// перерисовка
		StretchDIBits(hdc, 0, 0, bufferWidth, bufferHeight, 0, 0, bufferWidth, bufferHeight, bufferMemory, &bufferBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}
};