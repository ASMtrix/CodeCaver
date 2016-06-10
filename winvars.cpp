#include "winvars.h"
#include <windows.h>


int window_x = 100;
int window_y = 100;

int Width=250;
int Height=230;
HWND form1hwnd;
WNDCLASSEX wc;
HWND hwnd;
MSG Msg;


#define WindowsMain() ( WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow) )

const char ClassName[] = "myWindowClass";
const char WindowTitle[] = "Caving Code";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);