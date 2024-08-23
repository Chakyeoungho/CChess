#ifndef _TIPSWARE_H_
#define _TIPSWARE_H_

/*  [ �⺻ ���� �ڵ� ]
#include "pch.h"
#include "tipsware.h"

NOT_USE_MESSAGE

int main()
{

	ShowDisplay(); // ������ �����쿡 ����Ѵ�.
	return 0;
}
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
#include "EasyWin32.h"

#pragma comment(lib, "gdiplus")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "WS2_32.lib")

#ifdef _DEBUG
	#pragma comment(lib, "DSH_EasyWin32.lib")
#else
	#pragma comment(lib, "RST_EasyWin32.lib")
#endif

/*
���Ͽ��� ���Ѿ��� UserData ���� ����!! - 1���� Ŭ���̾�Ʈ ������ ������ ����ü
struct UserData
{
	unsigned int h_socket;   // ���� �ڵ�
	char ip_address[16];     // ������ Ŭ���̾�Ʈ�� �ּ�
};
*/

// ���� ������ ������ ������ ������ ����ü
struct CurrentServerNetworkData
{
	unsigned char m_net_msg_id;      // �޽��� ID
	unsigned short m_net_body_size;  // Body �������� ũ��
	char *mp_net_body_data;          // Body ������ ����
	void *mp_net_user;               // �����͸� ������ Ŭ���̾�Ʈ ����
};

// ���� ������ ������ ������ ������ ����ü
struct CurrentClientNetworkData
{
	unsigned char m_net_msg_id;      // �޽��� ID
	unsigned short m_net_body_size;  // Body �������� ũ��
	char *mp_net_body_data;          // Body ������ ����
};

// ���� ���α׷��� ����ϴ� ���� ������ Ŭ���� �̸��Դϴ�. (���� ����)
const char *gp_app_name = "EasyMyWindow";
// ���� ���α׷��� ����ϴ� �����Դϴ�. (���� ����)
const char *gp_window_title = "https://blog.naver.com/tipsware";
// ���� ���α׷��� ����� �޴��� ID�Դϴ�. (0�̸� �޴��� ������� �ʴ´ٴ� ���Դϴ�.)
int g_menu_id = 0;
// ���� ���α׷��� ����� ���� �������� ID�Դϴ�. (0�̸� �ü���� �����ϴ� �⺻ �������� ����Ѵٴ� ���Դϴ�.)
int g_system_icon_id = 0;
// ���� ���α׷��� ����� Ȯ�� ������ �Ӽ��� �⺻ ������ �⺻ �Ӽ�
int g_ex_wnd_style = 0, g_wnd_style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
// _printf �Լ��� ����ϴ� ����Ʈ �ڽ� ��� ����� ��� ���� (0:������, 1:���)
extern int g_console_type_output;

using namespace EasyAPI_Tipsware;
using namespace TW_NeoServerSocket;
using namespace TW_NeoClientSocket;

#ifndef _USE_INIT_WINDOW_
void InitWindow() { }
#endif

#ifndef _USE_REG_WND_CLASS_
ATOM UserRegisterWndClass() { return (ATOM)0; }
#endif

#define printf TextOut
#define TIMER void CALLBACK

#define NOT_USE_TIMER_DATA HWND ah_wnd, UINT a_msg_id, UINT_PTR a_timer_id, DWORD a_time
#define NOT_USE_MESSAGE SystemMessageMap g_system_map;
#define MOUSE_MESSAGE(left_down, left_up, move) SystemMessageMap g_system_map(left_down, left_up, move, NULL, NULL, NULL);
#define MOUSE_MESSAGE_EX(left_down, left_up, move, destroy) SystemMessageMap g_system_map(left_down, left_up, move, NULL, destroy, NULL);
#define MOUSE_CMD_MESSAGE(left_down, left_up, move, command) SystemMessageMap g_system_map(left_down, left_up, move, command, NULL, NULL);
#define MOUSE_CMD_MESSAGE_EX(left_down, left_up, move, command, destroy) SystemMessageMap g_system_map(left_down, left_up, move, command, destroy, NULL);
#define CMD_MESSAGE(command) SystemMessageMap g_system_map(NULL, NULL, NULL, command, NULL, NULL);
#define CMD_USER_MESSAGE(command, destroy, user_msg) SystemMessageMap g_system_map(NULL, NULL, NULL, command, destroy, user_msg);
#define ON_MESSAGE(left_down, left_up, move, command, destroy, user_msg) SystemMessageMap g_system_map(left_down, left_up, move, command, destroy, user_msg);
#define USE_EASYWIN32 NOT_USE_MESSAGE

// �߽����� �������� ����Ͽ� ���簢���� �� ��ǥ�� �����ϴ� ��ũ�� �Լ�
#define G_POS(pos, r) pos.x - r, pos.y - r, pos.x + r, pos.y + r
#define G_PPOS(pos, r) pos->x - r, pos->y - r, pos->x + r, pos->y + r

#endif