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

bool running = true;

struct RenderState {
	void* memory;
	int width;
	int height;
	BITMAPINFO bitmapInfo;
};
RenderState renderState;

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

		bufferBitmapInfo.bmiHeader.biSize = sizeof(bufferBitmapInfo.bmiHeader);
		bufferBitmapInfo.bmiHeader.biWidth = renderState.width;
		bufferBitmapInfo.bmiHeader.biHeight = renderState.height;
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

	// создать окно по шаблону
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
		unsigned int* pixel = (unsigned int*) renderState.memory;
		for (size_t y = 0; y < renderState.height; y++) {
			for (size_t x = 0; x < renderState.width; x++) {
				*pixel++ = 0x1c3578;
			}
		}
		/*for (size_t y = 0; y < renderState.height; y++)
		{
			for (size_t x = 0; x < renderState.width; x++)
			{
				if (y * 3 < renderState.height)
					*pixel++ = 0xe4181c;
				else if (y * 3 < 2 * renderState.height)
					*pixel++ = 0x1c3578;
				else
					*pixel++ = 0xffffff;
			}
		}*/

		// перерисовка
		StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0, renderState.width, renderState.height, renderState.memory, &bufferBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}
};