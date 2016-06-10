#include "callback.h"
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
		case WM_CREATE:
		{
				
		}
		case WM_PAINT:
		{
			BITMAP bm;
			PAINTSTRUCT ps;
		    HDC hdc;
		    hdc = BeginPaint(hwnd,&ps);
			EndPaint(hwnd, &ps);
		}
		break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
