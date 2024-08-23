#ifndef _TIPSWARE_PLUS_H_
#define _TIPSWARE_PLUS_H_

/*  [ 기본 샘플 코드 ]
#include "pch.h"                // 컴파일 속도 향상을 위해
#include "tipsware_plus.h"      // EasyWin32를 C++ 스타일로 사용하기 위해

class MyWnd : public CEasyWnd
{
public:
	virtual void OnDraw() // 화면에 출력할 내용을 그리는 함수
	{
		m_gdip.Clear(RGB24(82, 97, 124)); // 화면을 RGB24(82, 97, 124) 색상으로 채운다.
		m_gdip.FillRect(50, 50, 300, 100, RGB24(168, 220, 238)); // 사각형을 그린다.
	}
};

class MyApp : public CEasyApp
{
private:
	MyWnd m_main_wnd;

public:
	virtual void InitInstance() // 응용 프로그램이 시작될 때 호출되는 함수
	{
		m_main_wnd.Create("EasyWin32 Plus", 10, 10); // 창을 생성한다.
		m_main_wnd.ChangeWorkSize(500, 300); // 실제 사용할 영역을 지정한다.
	}
};

MyApp g_app; // 프로그램을 시작한다.
*/

#include "resource.h"

// ExpParserEx에서 사용하는 구조체
struct ExpDataType {
	unsigned char d_type;
	union {
		__int8 i8;
		__int16 i16;
		__int32 i32;
		__int64 i64;
		float f;
		double d;
	};
};

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <objidl.h>
#include "EasyWin32.h"
#include "EasyWin32Plus.h"

// 중심점과 반지름을 사용하여 정사각형과 원 좌표를 구성하는 매크로 함수
#define G_POS(pos, r) pos.x - r, pos.y - r, pos.x + r, pos.y + r
#define G_PPOS(pos, r) pos->x - r, pos->y - r, pos->x + r, pos->y + r

#pragma comment(lib, "gdiplus")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "WS2_32.lib")

#ifdef _DEBUG
#pragma comment(lib, "DSH_EasyWin32.lib")
#else
#pragma comment(lib, "RST_EasyWin32.lib")
#endif

// C언어와 호환성을 유지하기 위해 남겨둠 - 사용 불가 영역 시작
const char *gp_app_name = "EasyWin32Plus";
const char *gp_window_title = "https://blog.naver.com/tipsware";
int g_menu_id = 0;
int g_system_icon_id = 0;
int g_ex_wnd_style = 0, g_wnd_style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;

#ifndef _USE_INIT_WINDOW_
void InitWindow() { }
#endif
#ifndef _USE_REG_WND_CLASS_
ATOM UserRegisterWndClass() { return (ATOM)0; }
#endif
int main() { };
SystemMessageMap g_system_map;
// 사용 불가 영역 종료

#endif