#include <windows.h>
bool running = true;
void* buffer_memory;
int buffer_height;
int buffer_width;

LRESULT CALLBACK Wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT res = 0;
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			running = false;
		} break;

		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);
			buffer_height = rect.bottom - rect.top;
			buffer_width = rect.right - rect.left;

			int buffer_size = buffer_width * buffer_height * sizeof(unsigned int);

			if (buffer_memory) VirtualFree(buffer_memory, 0, MEM_RELEASE);
			buffer_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		}

		default:
			res = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return res;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// Create Window Class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = Wndproc;
	
	// Register It
	RegisterClass(&window_class);

	// Create Window
	HWND window = CreateWindow(window_class.lpszClassName, L"Test Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);

	while (running) {
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}









	}

}