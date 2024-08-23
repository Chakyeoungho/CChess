#ifndef _EASY_WIN32_PLUS_H_
#define _EASY_WIN32_PLUS_H_
// 이 라이브러리는 C++ 언어로 Win32 프로그래밍을 쉽게 할수 있도록 도와주기 위해 만들었습니다.
// 이 방법을 사용해서 C++ 언어를 배우면서 Win32 프로그래밍으로 실습을 하면 됩니다.
//
// 제작자 : 김성엽 (tipsware@naver.com, https://blog.naver.com/tipsware, https://cafe.naver.com/easywin32)
//
// 개발 시작 : 2019년 9월 3일 화요일
// 최근 업데이트 : 2024년 1월 4일 목요일
//
// 이 라이브러리의 저작권은 '(주)팁스웨어'에 있습니다.
// 이 라이브러리는 C++ 언어를 공부하는 사람들을 위해 만들어졌습니다.
// 따라서 출처만 정확하게 밝혀주면 모든 상황에서 무료로 사용이 가능합니다.
// 이 라이브러리는 후원 하시는 분들의 도움으로 계속 발전하고 있습니다.
// 후원에 참여하실 분들은 아래의 링크를 참고하세요.
// https://blog.naver.com/tipsware/223265814721
// 여러분의 작은 관심이 개발에 큰 힘이 됩니다. 감사합니다!!

#include "TW_GDIP.h"

#define WS_NORMAL_WINDOW          WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN
#define WS_SIMPLE_WINDOW          WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN
#define WS_SIMPLE_MIN_BOX_WINDOW  WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN


#define MAX_STOCK_FONT          50

#define FONT_BOLD       0x01
#define FONT_ITALIC     0x02
#define FONT_UNDERLINE  0x04
#define FONT_STRIKEOUT  0x08

class EasyFontManager
{
private:
	HFONT mh_stock_font[MAX_STOCK_FONT];
	char *mp_name[MAX_STOCK_FONT];
	UINT16 m_name_len[MAX_STOCK_FONT];
	short m_size[MAX_STOCK_FONT];
	UINT8 m_style[MAX_STOCK_FONT];
	int m_stock_font_count;

public:
	EasyFontManager();
	~EasyFontManager();

	HFONT GetMyFont(const char *ap_name, short a_size, UINT8 a_style);
	HFONT GetMyFont(int a_index);
	void DeleteAllFont();
	int GetCount();
};

class CEasyCtrl
{
protected:
	UINT8 m_attached_flag;  // 컨트롤 직접 생성여부
	HWND mh_wnd;           // 컨트롤의 윈도우 핸들 값
	COLORREF m_fill_color, m_text_color; // 컨트롤의 배경색과 글자색
	COLORREF m_in_border_color, m_out_border_color; // 컨트롤의 테두리 색
	UINT m_control_id;  // 컨트롤의 ID 값

public:
	CEasyCtrl();           // 객체 생성자
	virtual ~CEasyCtrl();  // 객체 파괴자

	// 컨트롤을 생성하는 함수
	virtual HWND Create(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0) { return 0; }
	virtual HWND CreateEx(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0, UINT32 a_style_ex = 0) { return 0; }
	// 컨트롤의 핸들을 얻는 함수
	inline HWND GetHandle() { return mh_wnd; }
	// 외부에서 만들어진 컨트롤을 이 클래스가 관리하는 경우에 사용
	void Attach(HWND ah_attach_wnd);
	// 컨트롤의 색상을 변경할 때 사용하는 함수
	void ChangeCtrlColor(COLORREF a_fill_color, COLORREF a_out_border_color, COLORREF a_in_border_color, COLORREF a_text_color);

	// 컨트롤의 Owner Draw 속성이 True인 경우에 처리하는 함수
	virtual void OnDrawItem(DRAWITEMSTRUCT *ap_dis) { }
	virtual void OnMeasureItem(MEASUREITEMSTRUCT *ap_mis) { }
	virtual INT32 OnCtrlColor(HDC ah_dc, HWND ah_wnd);
	virtual void DestroyWindow();

	int GetWindowTextLength(); // 윈도우의 기본 텍스트 길이를 얻는 함수
	int GetWindowText(char *ap_str, int a_limit); // 윈도우의 기본 텍스트를 얻는 함수(아스키)
	int GetWindowText(wchar_t *ap_str, int a_limit); // 윈도우의 기본 텍스트를 얻는 함수(유니코드)

	void SetWindowText(const char *ap_str); // 윈도우의 기본 텍스트를 설정하는 함수 (아스키)
	void SetWindowText(const wchar_t *ap_str);  // 윈도우의 기본 텍스트를 설정하는 함수 (유니코드)
	void ShowWindow(int a_type); // 윈도우의 출력 상태를 변경하는 함수

	// 컨트롤을 다시 그릴 필요가 있을때 호출하는 함수
	void Invalidate(int a_bk_update = 1);
	// 컨트롤에 글꼴을 설정할 때 사용하는 함수
	void SetFont(HFONT ah_font);
	// 포커스를 설정하는 함수
	void SetFocus();
	// 컨트롤의 ID를 얻는 함수
	INT32 GetID();
};

class CEasyBtn : public CEasyCtrl
{
public:
	CEasyBtn();   // 객체 생성자
	virtual ~CEasyBtn();  // 객체 파괴자

	virtual HWND Create(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0);
	virtual HWND CreateEx(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0, UINT32 a_style_ex = 0);

	// 컨트롤의 Owner Draw 속성이 True인 경우에 처리하는 함수 (버튼을 그리기 위해 재정의 함)
	virtual void OnDrawItem(DRAWITEMSTRUCT *ap_dis);
};

#define EN_ENTER_KEYUP          1000

// Edit 컨트롤에 새롭게 설정할 윈도우 프로시저
extern LRESULT APIENTRY TW_EditProcForEnterKeyUp(HWND ah_wnd, UINT message_id, WPARAM wParam, LPARAM lParam);

class CEasyEdit : public CEasyCtrl
{
protected:
	// Edit 컨트롤이 본래 사용하던 프로시저의 주소를 저장하기 위한 함수의 포인터
	WNDPROC m_org_edit_proc;
	HBRUSH mh_tip_brush;

public:
	CEasyEdit();  // 객체 생성자
	virtual ~CEasyEdit(); // 객체 파괴자

	// 기본 속성으로 Edit 컨트롤을 생성하는 함수
	virtual HWND Create(HWND ah_parent_wnd, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id);
	virtual HWND CreateEx(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style, UINT32 a_style_ex);

	HWND CreateUserStyle(HWND ah_parent_wnd, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL);
	// 서브클래싱을 하는 함수. 기본으로 제공되는 TW_EditProcForEnterKeyUp 프러시저는 
	// 엔터키를 체크해서 EN_ENTER_KEYUP 메시지를 전달하는 기능이 추가되어 있다.
	void SubclassWnd(WNDPROC afp_filter, WNDPROC a_new_proc = TW_EditProcForEnterKeyUp);
	// 에디트 컨트롤 배경에 텍스트를 출력하는 함수
	void SetBgTipText(const char *ap_text, int a_text_len, COLORREF a_color);
	// 에디트 컨트롤 배경을 기본 형식으로 복구하는 함수
	void ResetTipText();
	virtual void DestroyWindow();
	// WM_CTRLCOLOREDIT 메시지에서 사용하는 함수
	virtual INT32 OnCtrlColor(HDC ah_dc, HWND ah_wnd);
	// 텍스트 파일을 읽어서 에디트 컨트롤에 표시하는 함수
	int ReadTextFromFile(const char *ap_file_path);
	int SaveTextToFile(const char *ap_file_path);

	// 정숫값을 에디트 컨트롤에 출력하는 함수
	void SetIntData(int a_value);
	// 에디트 컨트롤에 입력된 값을 정숫값으로 얻는 함수
	int GetIntData();
	// 실수값을 에디트 컨트롤에 출력하는 함수
	void SetDoubleData(double a_value, const char *ap_format = "%g");
	// 에디트 컨트롤에 입력된 값을 실숫값으로 얻는 함수
	double GetDoubleData();
};

typedef void (*DRAW_LISTBOX_ITEM)(int index, char *ap_str, int a_str_len, void *ap_data, int a_is_selected, RECT *ap_rect);

class CEasyListBox : public CEasyCtrl
{
protected:
	DRAW_LISTBOX_ITEM mfp_draw_item;

public:
	CEasyListBox(DRAW_LISTBOX_ITEM afp_draw_item = NULL); // 객체 생성자
	virtual ~CEasyListBox(); // 객체 파괴자

	// 기본 속성으로 ListBox를 생성하는 함수
	virtual HWND Create(HWND ah_parent_wnd, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = LBS_STANDARD);
	// 확장 속성을 사용해서 ListBox를 생성하는 함수
	virtual HWND CreateEx(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0, UINT32 a_ex_style = WS_EX_STATICEDGE);

	void ChangeDrawItemFunc(DRAW_LISTBOX_ITEM afp_draw_item);
	// 문자열을 ListBox에 추가하는 함수, LBS_SORT 옵션을 가지고 있다면 오름차순으로 정렬해서 추가한다.
	INT32 AddString(const char *ap_string, UINT8 a_auto_select = 1);
	// 문자열을 사용자가 지정한 위치에 추가하는 함수
	INT32 InsertString(INT32 a_index, const char *ap_string, UINT8 a_auto_select = 1);
	// 사용자가 지정한 항목에 추가된 문자열의 길이를 얻는다.
	INT32 GetTextLength(INT32 a_index);
	// 사용자가 지정한 항목에서 문자열을 복사해서 가져온다.
	INT32 GetText(INT32 a_index, char *ap_string, int a_max_len);
	// ListBox의 특정 항목을 선택한다.
	void SetCurSel(INT32 a_index);
	// ListBox에서 어떤 항목이 선택되어 있는지 위치 값을 얻는다.
	INT32 GetCurSel();
	// ListBox에 추가된 항목의 개수를 얻는다.
	INT32 GetCount();
	// ListBox에서 지정된 항목을 제거한다.
	void DeleteString(INT32 a_index);
	// ListBox에 추가된 모든 항목을 제거한다.
	void ResetContent();
	// 지정한 항목에 추가 4바이트 정보를 설정한다. (포인터 형식)
	void SetItemDataPtr(INT32 a_index, void *ap_data);
	// 보통의 경우 InsertString을 사용하고 SetItemDataPtr 함수를 사용해야 하지만
	// 이 함수를 사용하면 두 함수의 기능을 동시에 수행합니다.  (포인터 형식)
	void SetItemDataPtrEx(INT32 a_index, const char *ap_string, void *ap_data, UINT8 a_auto_select = 1);
	// 항목에 추가된 4바이트 메모리 값을 얻는다. (포인터 형식)
	void *GetItemDataPtr(INT32 a_index);
	// 지정한 항목에 추가 4바이트 정보를 설정한다. (정수 형식)
	void SetItemData(INT32 a_index, INT32 a_data);
	// 보통의 경우 InsertString을 사용하고 SetItemDataPtr 함수를 사용해야 하지만
	// 이 함수를 사용하면 두 함수의 기능을 동시에 수행합니다.  (정수 형식)
	void SetItemDataEx(INT32 a_index, const char *ap_string, INT32 a_data, UINT8 a_auto_select = 1);
	// 항목에 추가된 4바이트 메모리 값을 얻는다. (정수 형식)
	INT32 GetItemData(INT32 a_index);
	// ListBox에 추가된 문자열에서 원하는 문자열을 검색한다. 이 함수를 사용하면
	// 자신이 찾고 싶은 문자열이 'abc'인 경우에 'abc'뿐만 아니라 'abcdef'와 같이
	// 부분적으로 일치하는 문자열도 찾을 수 있습니다.
	INT32 FindString(INT32 a_index, const char *ap_string);
	// ListBox에 추가된 문자열에서 원하는 문자열을 검색한다. 이 함수는 정확하게
	// 일치하는 문자열만 검색합니다.
	INT32 FindStringExact(INT32 a_index, const char *ap_string);
	// 형식화된 문자열을 추가하는 함수
	int PrintFormat(const char *ap_format, ...);

	void SetItemWidth(INT32 a_width);
	void SetItemHeight(INT32 a_height);

	virtual void OnDrawItem(DRAWITEMSTRUCT *ap_dis);
	virtual void OnMeasureItem(MEASUREITEMSTRUCT *ap_mis);
	virtual INT32 OnCtrlColor(HDC ah_dc, HWND ah_wnd);
};

typedef DRAW_LISTBOX_ITEM DRAW_COMBOBOX_ITEM;

class CEasyComboBox : public CEasyCtrl
{
protected:
	DRAW_COMBOBOX_ITEM mfp_draw_item;
	int m_item_height = 19;

public:
	CEasyComboBox(DRAW_COMBOBOX_ITEM afp_draw_item = NULL); // 객체 생성자
	virtual ~CEasyComboBox(); // 객체 파괴자

	// 기본 속성으로 ComboBox를 생성하는 함수
	virtual HWND Create(HWND ah_parent_wnd, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0);
	// 확장 속성을 사용해서 ComboBox를 생성하는 함수
	virtual HWND CreateEx(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0, UINT32 a_ex_style = WS_EX_STATICEDGE);

	void ChangeDrawItemFunc(DRAW_COMBOBOX_ITEM afp_draw_item);
	// 문자열을 ComboBox에 추가하는 함수, CBS_SORT 옵션을 가지고 있다면 오름차순으로 정렬해서 추가한다.
	INT32 AddString(const char *ap_string, UINT8 a_auto_select = 1);
	// 문자열을 사용자가 지정한 위치에 추가하는 함수
	INT32 InsertString(INT32 a_index, const char *ap_string, UINT8 a_auto_select = 1);
	// 사용자가 지정한 항목에 추가된 문자열의 길이를 얻는다.
	INT32 GetTextLength(INT32 a_index);
	// 사용자가 지정한 항목에서 문자열을 복사해서 가져온다.
	INT32 GetText(INT32 a_index, char *ap_string, int a_max_len);
	// ComboBox의 특정 항목을 선택한다.
	void SetCurSel(INT32 a_index);
	// ComboBox에서 어떤 항목이 선택되어 있는지 위치 값을 얻는다.
	INT32 GetCurSel();
	// ComboBox에 추가된 항목의 개수를 얻는다.
	INT32 GetCount();
	// ComboBox에서 지정된 항목을 제거한다.
	void DeleteString(INT32 a_index);
	// ComboBox에 추가된 모든 항목을 제거한다.
	void ResetContent();
	// 지정한 항목에 추가 4바이트 정보를 설정한다. (포인터 형식)
	void SetItemDataPtr(INT32 a_index, void *ap_data);
	// 보통의 경우 InsertString을 사용하고 SetItemDataPtr 함수를 사용해야 하지만
	// 이 함수를 사용하면 두 함수의 기능을 동시에 수행합니다.  (포인터 형식)
	void SetItemDataPtrEx(INT32 a_index, const char *ap_string, void *ap_data, UINT8 a_auto_select = 1);
	// 항목에 추가된 4바이트 메모리 값을 얻는다. (포인터 형식)
	void *GetItemDataPtr(INT32 a_index);
	// 지정한 항목에 추가 4바이트 정보를 설정한다. (정수 형식)
	void SetItemData(INT32 a_index, INT32 a_data);
	// 보통의 경우 InsertString을 사용하고 SetItemDataPtr 함수를 사용해야 하지만
	// 이 함수를 사용하면 두 함수의 기능을 동시에 수행합니다.  (정수 형식)
	void SetItemDataEx(INT32 a_index, const char *ap_string, INT32 a_data, UINT8 a_auto_select = 1);
	// 항목에 추가된 4바이트 메모리 값을 얻는다. (정수 형식)
	INT32 GetItemData(INT32 a_index);
	// ComboBox에 추가된 문자열에서 원하는 문자열을 검색한다. 이 함수를 사용하면
	// 자신이 찾고 싶은 문자열이 'abc'인 경우에 'abc'뿐만 아니라 'abcdef'와 같이
	// 부분적으로 일치하는 문자열도 찾을 수 있습니다.
	INT32 FindString(INT32 a_index, const char *ap_string);
	// ComboBox에 추가된 문자열에서 원하는 문자열을 검색한다. 이 함수는 정확하게
	// 일치하는 문자열만 검색합니다.
	INT32 FindStringExact(INT32 a_index, const char *ap_string);
	// 형식화된 문자열을 추가하는 함수
	int PrintFormat(const char *ap_format, ...);

	void SetItemHeight(INT32 a_height);

	virtual void OnDrawItem(DRAWITEMSTRUCT *ap_dis);
	virtual void OnMeasureItem(MEASUREITEMSTRUCT *ap_mis);
	virtual INT32 OnCtrlColor(HDC ah_dc, HWND ah_wnd);
};

class CEasyWnd
{
protected:
	// 윈도우의 확장 스타일과 기본 스타일
	int m_ex_wnd_style, m_wnd_style;
	// 윈도우가 기본 출력에 사용할 GDI+ 객체
	TW_GDIP m_gdip;

public:
	CEasyWnd();
	virtual ~CEasyWnd();

	// 사용자가 출력할 영역의 크기를 변경하는 함수
	void ChangeWorkSize(int a_cx, int a_cy);
	// 현재 사용중인 GDI+ 객체의 주소를 반환하는 함수
	TW_GDIP *GetGDIP();
	// 컨트롤의 ID를 사용해서 컨트롤의 주소를 얻는 함수
	CEasyCtrl *FindControl(int a_id);
	// 지정된 영역을 갱신하는 함수
	void InvalidateRect(RECT a_rect);
	// 작업 영역 전체를 갱신하는 함수
	void Invalidate();
	// 마우스가 윈도우 영역을 벗어나도 계속 메시지를 받을 수 있도록 하는 함수
	void SetCapture();
	// SetCapture를 해제하는 함수
	void ReleaseCapture();
	// 글꼴을 얻는 함수
	HFONT GetUserFont(const char *ap_font_name, short a_size, UINT8 a_style);

	// 버튼을 생성하는 함수
	CEasyBtn *CreateButton(const char *ap_name, int a_x, int a_y, int a_width, int a_height, int a_id, int a_style = 0, int a_ex_syle = 0);
	// 에디트 컨트롤을 생성하는 함수
	CEasyEdit *CreateEdit(int a_x, int a_y, int a_width, int a_height, int a_id, int a_style = 0, int a_ex_syle = 0);
	// 리스트 박스를 생성하는 함수
	CEasyListBox *CreateListBox(int a_x, int a_y, int a_width, int a_height, int a_id, void *afp_draw = NULL, int a_style = 0, int a_ex_syle = 0);
	// 콤보 박스를 생성하는 함수
	CEasyComboBox *CreateComboBox(int a_x, int a_y, int a_width, int a_height, int a_id, void *afp_draw = NULL, int a_style = 0, int a_ex_syle = 0);

	// 지정한 컨트롤을 제거하는 함수
	void DestroyControl(CEasyCtrl *ap_ctrl);
	void DestroyControl(int a_id);

	// 사용할 윈도우를 생성하는 함수
	virtual int Create(const char *ap_title, int a_x, int a_y);
	// 윈도우의 크기가 변경되었을 때 호출되는 함수
	virtual void OnSize(UINT32 a_type, int a_cx, int a_cy) { }
	// 화면에 출력할 내용을 그리는 함수
	virtual void OnDraw() { }
	// 윈도우가 생성된 직후에 호출되는 함수
	virtual void OnCreate(CREATESTRUCT *ap_create_info) { }
	// 마우스 왼쪽 버튼 클릭 처리용 함수
	virtual void OnLButtonDown(int a_mixed_key, POINT a_pos) { }
	// 마우스 왼쪽 버튼 클릭 해제 처리용 함수
	virtual void OnLButtonUp(int a_mixed_key, POINT a_pos){ }
	// 마우스 이동 처리용 함수
	virtual void OnMouseMove(int a_mixed_key, POINT a_pos) { }
	// 명령 메시지 처리용 함수
	virtual void OnCommand(int a_id, int a_notify_code) { }
	// WM_DRAWITEM 메시지 처리용 함수
	virtual void OnDrawItem(int a_id, LPARAM lParam);
	// WM_MEASUREITEM 메시지 처리용 함수
	virtual void OnMeasureItem(int a_id, LPARAM lParam);
	// WM_CTLCOLOR 메시지 처리용 함수
	virtual int OnCtrlColor(WPARAM wParam, LPARAM lParam);
	// WM_DESTROY 메시지 처리용 함수
	virtual void OnDestroy();
	// 윈도우에 발생하는 일반 메시지를 처리하는 함수
	virtual int WndProc(HWND ah_wnd, UINT a_message_id, WPARAM wParam, LPARAM lParam){ return 0; }
};

class CEasyApp
{
protected:
	// 응용 프로그램이 사용하는 윈도우 클래스 이름
	char m_app_name[128];
	// 윈도우에서 사용할 메뉴 ID, 로고 아이콘 ID - 둘다 기본 값 0
	int m_menu_id, m_system_icon_id;

public:
	CEasyApp();
	virtual ~CEasyApp();

	// 응용 프로그램의 윈도우 클래스 이름을 반환하는 함수
	const char *GetAppName();
	// 응용 프로그램이 사용할 Window 클래스를 등록하는 함수
	virtual int RegisterWndClass();
	// 응용 프로그램이 시작될 때 호출되는 함수 - 반드시 오버라이딩해야 함
	virtual void InitInstance(){ }
	// 응용 프로그램이 종료될 때 호출되는 함수
	virtual void ExitInstance(){ };
};

#endif
