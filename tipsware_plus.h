#ifndef _TIPSWARE_PLUS_H_
#define _TIPSWARE_PLUS_H_

/*  [ �⺻ ���� �ڵ� ]
#include "pch.h"                // ������ �ӵ� ����� ����
#include "tipsware_plus.h"      // EasyWin32�� C++ ��Ÿ�Ϸ� ����ϱ� ����

class MyWnd : public CEasyWnd
{
public:
	virtual void OnDraw() // ȭ�鿡 ����� ������ �׸��� �Լ�
	{
		m_gdip.Clear(RGB24(82, 97, 124)); // ȭ���� RGB24(82, 97, 124) �������� ä���.
		m_gdip.FillRect(50, 50, 300, 100, RGB24(168, 220, 238)); // �簢���� �׸���.
	}
};

class MyApp : public CEasyApp
{
private:
	MyWnd m_main_wnd;

public:
	virtual void InitInstance() // ���� ���α׷��� ���۵� �� ȣ��Ǵ� �Լ�
	{
		m_main_wnd.Create("EasyWin32 Plus", 10, 10); // â�� �����Ѵ�.
		m_main_wnd.ChangeWorkSize(500, 300); // ���� ����� ������ �����Ѵ�.
	}
};

MyApp g_app; // ���α׷��� �����Ѵ�.
*/

#include "resource.h"

// ExpParserEx���� ����ϴ� ����ü
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

// �߽����� �������� ����Ͽ� ���簢���� �� ��ǥ�� �����ϴ� ��ũ�� �Լ�
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

// C���� ȣȯ���� �����ϱ� ���� ���ܵ� - ��� �Ұ� ���� ����
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
// ��� �Ұ� ���� ����

#endif