#include "stdafx.h"
#include "Base.h"

static char szClass[] = "TestClass";
static char szCaption[] = "Test Program";

CBase *g_pBase = NULL;

int g_mouseButtons = 0;
POINT g_mousePoint;

LRESULT CALLBACK 
WindowProc(HWND hWnd, unsigned uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:

            if(g_pBase)
				SAFE_DELETE(g_pBase);

            PostQuitMessage(0);
            break;

        case WM_SIZE:
			if(g_pBase)
				g_pBase->HandleSize(wParam);
            break;

        case WM_KEYUP: 

            switch (wParam) { 

                case VK_INSERT:
					
					// 插入键退出应用程序
                    // exit the program on insert

                    DestroyWindow(hWnd);
                    break;
				default:
					if(g_pBase)
					{
						//g_pBase->KeyHit(wParam);
					}
					break;
            } 
            break;

		case WM_CHAR:
			if(g_pBase)
			{
				g_pBase->KeyHit(wParam);
			}
			break;


		case WM_LBUTTONDOWN:
			g_mouseButtons |= MOUSE_LBUTTON_DOWN;
			break;
		case WM_LBUTTONUP:
			g_mouseButtons &= ~MOUSE_LBUTTON_DOWN;
			break;
		case WM_RBUTTONDOWN:
			g_mouseButtons |= MOUSE_RBUTTON_DOWN;
			break;
		case WM_RBUTTONUP:
			g_mouseButtons &= ~MOUSE_RBUTTON_DOWN;
			break;
		case WM_MOUSEMOVE:
			g_mousePoint.x = 0xFFFF & (lParam);
			g_mousePoint.y = 0xFFFF0000 & (lParam);
			break;

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0L;
}

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{

	g_pBase = new CBase();
	if(g_pBase->Init(hInstance, szClass, szCaption, WindowProc))
	{
		g_pBase->MainLoop();
		SAFE_DELETE(g_pBase);
	}

    return TRUE;
} 

