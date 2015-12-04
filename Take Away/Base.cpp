// Base.cpp: 实现CBase类。
// Base.cpp: implementation of the CBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Settings.h"
#include <WinConsole.h>
#include "Base.h"

// 在WinMain.cpp定义了唯一的指向CBase对象的全局指针
// global pointer to the one and only CBase object
// defined in WinMain.cpp
extern CBase *g_pBase;

extern "C" {
typedef struct 
{
	const char *name;
	int (*func)(lua_State *);
}luaDef;
}


extern luaDef MyGlue[];

// 
// static function just to keep the DX timekeeping and other message handling 
// functions hidden in the DX9 library. 
static void	RenderStub(float fTime)
{
	if(g_pBase)
		g_pBase->Render(fTime);
}


// testing stuff

Sprite *g_pSprite = NULL;
Font   *g_pd3dxFont  = NULL;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBase::CBase()
{
	m_lpDX = NULL;
	m_hConsole = NULL;
}

void LuaErrorHandler(const char *pError)
{
	HWND hConsole = g_pBase->GetConsole();
	if(hConsole && IsWindow(hConsole))
	{
		CWinConsole::Write(pError);
		BringWindowToTop(hConsole);
	}

}

bool CBase::Init(HINSTANCE hInstance, const char *szClass, const char *szCaption, WNDPROC WindowProc)
{
	// 鍒涘缓搴旂敤绋嬪簭鍙ユ焺鍜岄摼鎺ュ埌绐楀彛杩囩▼
    // create application handler and link to our WindowProc

    m_lpDX=new DXBase(hInstance,szClass,szCaption,WindowProc);
    if (!m_lpDX)
        return false;;

	// 妫