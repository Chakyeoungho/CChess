#ifndef _TIPSWARE_H_
#define _TIPSWARE_H_

/*  [ 기본 샘플 코드 ]
#include "pch.h"
#include "tipsware.h"

NOT_USE_MESSAGE

int main()
{

	ShowDisplay(); // 정보를 윈도우에 출력한다.
	return 0;
}
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
소켓에서 지켜야할 UserData 시작 형식!! - 1개의 클라이언트 정보를 저장할 구조체
struct UserData
{
	unsigned int h_socket;   // 소켓 핸들
	char ip_address[16];     // 접속한 클라이언트의 주소
};
*/

// 현재 수신한 데이터 정보를 저장할 구조체
struct CurrentServerNetworkData
{
	unsigned char m_net_msg_id;      // 메시지 ID
	unsigned short m_net_body_size;  // Body 데이터의 크기
	char *mp_net_body_data;          // Body 데이터 정보
	void *mp_net_user;               // 데이터를 전송한 클라이언트 정보
};

// 현재 수신한 데이터 정보를 저장할 구조체
struct CurrentClientNetworkData
{
	unsigned char m_net_msg_id;      // 메시지 ID
	unsigned short m_net_body_size;  // Body 데이터의 크기
	char *mp_net_body_data;          // Body 데이터 정보
};

// 응용 프로그램이 사용하는 내부 윈도우 클래스 이름입니다. (수정 가능)
const char *gp_app_name = "EasyMyWindow";
// 응용 프로그램이 사용하는 제목입니다. (수정 가능)
const char *gp_window_title = "https://blog.naver.com/tipsware";
// 응용 프로그램이 사용할 메뉴의 ID입니다. (0이면 메뉴를 사용하지 않는다는 뜻입니다.)
int g_menu_id = 0;
// 응용 프로그램이 사용할 메인 아이콘의 ID입니다. (0이면 운영체제가 제공하는 기본 아이콘을 사용한다는 뜻입니다.)
int g_system_icon_id = 0;
// 응용 프로그램이 사용할 확장 윈도우 속성과 기본 윈도우 기본 속성
int g_ex_wnd_style = 0, g_wnd_style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
// _printf 함수를 사용하는 리스트 박스 기반 출력을 사용 여부 (0:사용안함, 1:사용)
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

// 중심점과 반지름을 사용하여 정사각형과 원 좌표를 구성하는 매크로 함수
#define G_POS(pos, r) pos.x - r, pos.y - r, pos.x + r, pos.y + r
#define G_PPOS(pos, r) pos->x - r, pos->y - r, pos->x + r, pos->y + r

#endif