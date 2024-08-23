#ifndef _EASY_WIN32_PLUS_H_
#define _EASY_WIN32_PLUS_H_
// �� ���̺귯���� C++ ���� Win32 ���α׷����� ���� �Ҽ� �ֵ��� �����ֱ� ���� ��������ϴ�.
// �� ����� ����ؼ� C++ �� ���鼭 Win32 ���α׷������� �ǽ��� �ϸ� �˴ϴ�.
//
// ������ : �輺�� (tipsware@naver.com, https://blog.naver.com/tipsware, https://cafe.naver.com/easywin32)
//
// ���� ���� : 2019�� 9�� 3�� ȭ����
// �ֱ� ������Ʈ : 2024�� 1�� 4�� �����
//
// �� ���̺귯���� ���۱��� '(��)��������'�� �ֽ��ϴ�.
// �� ���̺귯���� C++ �� �����ϴ� ������� ���� ����������ϴ�.
// ���� ��ó�� ��Ȯ�ϰ� �����ָ� ��� ��Ȳ���� ����� ����� �����մϴ�.
// �� ���̺귯���� �Ŀ� �Ͻô� �е��� �������� ��� �����ϰ� �ֽ��ϴ�.
// �Ŀ��� �����Ͻ� �е��� �Ʒ��� ��ũ�� �����ϼ���.
// https://blog.naver.com/tipsware/223265814721
// �������� ���� ������ ���߿� ū ���� �˴ϴ�. �����մϴ�!!

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
	UINT8 m_attached_flag;  // ��Ʈ�� ���� ��������
	HWND mh_wnd;           // ��Ʈ���� ������ �ڵ� ��
	COLORREF m_fill_color, m_text_color; // ��Ʈ���� ������ ���ڻ�
	COLORREF m_in_border_color, m_out_border_color; // ��Ʈ���� �׵θ� ��
	UINT m_control_id;  // ��Ʈ���� ID ��

public:
	CEasyCtrl();           // ��ü ������
	virtual ~CEasyCtrl();  // ��ü �ı���

	// ��Ʈ���� �����ϴ� �Լ�
	virtual HWND Create(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0) { return 0; }
	virtual HWND CreateEx(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0, UINT32 a_style_ex = 0) { return 0; }
	// ��Ʈ���� �ڵ��� ��� �Լ�
	inline HWND GetHandle() { return mh_wnd; }
	// �ܺο��� ������� ��Ʈ���� �� Ŭ������ �����ϴ� ��쿡 ���
	void Attach(HWND ah_attach_wnd);
	// ��Ʈ���� ������ ������ �� ����ϴ� �Լ�
	void ChangeCtrlColor(COLORREF a_fill_color, COLORREF a_out_border_color, COLORREF a_in_border_color, COLORREF a_text_color);

	// ��Ʈ���� Owner Draw �Ӽ��� True�� ��쿡 ó���ϴ� �Լ�
	virtual void OnDrawItem(DRAWITEMSTRUCT *ap_dis) { }
	virtual void OnMeasureItem(MEASUREITEMSTRUCT *ap_mis) { }
	virtual INT32 OnCtrlColor(HDC ah_dc, HWND ah_wnd);
	virtual void DestroyWindow();

	int GetWindowTextLength(); // �������� �⺻ �ؽ�Ʈ ���̸� ��� �Լ�
	int GetWindowText(char *ap_str, int a_limit); // �������� �⺻ �ؽ�Ʈ�� ��� �Լ�(�ƽ�Ű)
	int GetWindowText(wchar_t *ap_str, int a_limit); // �������� �⺻ �ؽ�Ʈ�� ��� �Լ�(�����ڵ�)

	void SetWindowText(const char *ap_str); // �������� �⺻ �ؽ�Ʈ�� �����ϴ� �Լ� (�ƽ�Ű)
	void SetWindowText(const wchar_t *ap_str);  // �������� �⺻ �ؽ�Ʈ�� �����ϴ� �Լ� (�����ڵ�)
	void ShowWindow(int a_type); // �������� ��� ���¸� �����ϴ� �Լ�

	// ��Ʈ���� �ٽ� �׸� �ʿ䰡 ������ ȣ���ϴ� �Լ�
	void Invalidate(int a_bk_update = 1);
	// ��Ʈ�ѿ� �۲��� ������ �� ����ϴ� �Լ�
	void SetFont(HFONT ah_font);
	// ��Ŀ���� �����ϴ� �Լ�
	void SetFocus();
	// ��Ʈ���� ID�� ��� �Լ�
	INT32 GetID();
};

class CEasyBtn : public CEasyCtrl
{
public:
	CEasyBtn();   // ��ü ������
	virtual ~CEasyBtn();  // ��ü �ı���

	virtual HWND Create(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0);
	virtual HWND CreateEx(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0, UINT32 a_style_ex = 0);

	// ��Ʈ���� Owner Draw �Ӽ��� True�� ��쿡 ó���ϴ� �Լ� (��ư�� �׸��� ���� ������ ��)
	virtual void OnDrawItem(DRAWITEMSTRUCT *ap_dis);
};

#define EN_ENTER_KEYUP          1000

// Edit ��Ʈ�ѿ� ���Ӱ� ������ ������ ���ν���
extern LRESULT APIENTRY TW_EditProcForEnterKeyUp(HWND ah_wnd, UINT message_id, WPARAM wParam, LPARAM lParam);

class CEasyEdit : public CEasyCtrl
{
protected:
	// Edit ��Ʈ���� ���� ����ϴ� ���ν����� �ּҸ� �����ϱ� ���� �Լ��� ������
	WNDPROC m_org_edit_proc;
	HBRUSH mh_tip_brush;

public:
	CEasyEdit();  // ��ü ������
	virtual ~CEasyEdit(); // ��ü �ı���

	// �⺻ �Ӽ����� Edit ��Ʈ���� �����ϴ� �Լ�
	virtual HWND Create(HWND ah_parent_wnd, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id);
	virtual HWND CreateEx(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style, UINT32 a_style_ex);

	HWND CreateUserStyle(HWND ah_parent_wnd, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL);
	// ����Ŭ������ �ϴ� �Լ�. �⺻���� �����Ǵ� TW_EditProcForEnterKeyUp ���������� 
	// ����Ű�� üũ�ؼ� EN_ENTER_KEYUP �޽����� �����ϴ� ����� �߰��Ǿ� �ִ�.
	void SubclassWnd(WNDPROC afp_filter, WNDPROC a_new_proc = TW_EditProcForEnterKeyUp);
	// ����Ʈ ��Ʈ�� ��濡 �ؽ�Ʈ�� ����ϴ� �Լ�
	void SetBgTipText(const char *ap_text, int a_text_len, COLORREF a_color);
	// ����Ʈ ��Ʈ�� ����� �⺻ �������� �����ϴ� �Լ�
	void ResetTipText();
	virtual void DestroyWindow();
	// WM_CTRLCOLOREDIT �޽������� ����ϴ� �Լ�
	virtual INT32 OnCtrlColor(HDC ah_dc, HWND ah_wnd);
	// �ؽ�Ʈ ������ �о ����Ʈ ��Ʈ�ѿ� ǥ���ϴ� �Լ�
	int ReadTextFromFile(const char *ap_file_path);
	int SaveTextToFile(const char *ap_file_path);

	// �������� ����Ʈ ��Ʈ�ѿ� ����ϴ� �Լ�
	void SetIntData(int a_value);
	// ����Ʈ ��Ʈ�ѿ� �Էµ� ���� ���������� ��� �Լ�
	int GetIntData();
	// �Ǽ����� ����Ʈ ��Ʈ�ѿ� ����ϴ� �Լ�
	void SetDoubleData(double a_value, const char *ap_format = "%g");
	// ����Ʈ ��Ʈ�ѿ� �Էµ� ���� �Ǽ������� ��� �Լ�
	double GetDoubleData();
};

typedef void (*DRAW_LISTBOX_ITEM)(int index, char *ap_str, int a_str_len, void *ap_data, int a_is_selected, RECT *ap_rect);

class CEasyListBox : public CEasyCtrl
{
protected:
	DRAW_LISTBOX_ITEM mfp_draw_item;

public:
	CEasyListBox(DRAW_LISTBOX_ITEM afp_draw_item = NULL); // ��ü ������
	virtual ~CEasyListBox(); // ��ü �ı���

	// �⺻ �Ӽ����� ListBox�� �����ϴ� �Լ�
	virtual HWND Create(HWND ah_parent_wnd, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = LBS_STANDARD);
	// Ȯ�� �Ӽ��� ����ؼ� ListBox�� �����ϴ� �Լ�
	virtual HWND CreateEx(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0, UINT32 a_ex_style = WS_EX_STATICEDGE);

	void ChangeDrawItemFunc(DRAW_LISTBOX_ITEM afp_draw_item);
	// ���ڿ��� ListBox�� �߰��ϴ� �Լ�, LBS_SORT �ɼ��� ������ �ִٸ� ������������ �����ؼ� �߰��Ѵ�.
	INT32 AddString(const char *ap_string, UINT8 a_auto_select = 1);
	// ���ڿ��� ����ڰ� ������ ��ġ�� �߰��ϴ� �Լ�
	INT32 InsertString(INT32 a_index, const char *ap_string, UINT8 a_auto_select = 1);
	// ����ڰ� ������ �׸� �߰��� ���ڿ��� ���̸� ��´�.
	INT32 GetTextLength(INT32 a_index);
	// ����ڰ� ������ �׸񿡼� ���ڿ��� �����ؼ� �����´�.
	INT32 GetText(INT32 a_index, char *ap_string, int a_max_len);
	// ListBox�� Ư�� �׸��� �����Ѵ�.
	void SetCurSel(INT32 a_index);
	// ListBox���� � �׸��� ���õǾ� �ִ��� ��ġ ���� ��´�.
	INT32 GetCurSel();
	// ListBox�� �߰��� �׸��� ������ ��´�.
	INT32 GetCount();
	// ListBox���� ������ �׸��� �����Ѵ�.
	void DeleteString(INT32 a_index);
	// ListBox�� �߰��� ��� �׸��� �����Ѵ�.
	void ResetContent();
	// ������ �׸� �߰� 4����Ʈ ������ �����Ѵ�. (������ ����)
	void SetItemDataPtr(INT32 a_index, void *ap_data);
	// ������ ��� InsertString�� ����ϰ� SetItemDataPtr �Լ��� ����ؾ� ������
	// �� �Լ��� ����ϸ� �� �Լ��� ����� ���ÿ� �����մϴ�.  (������ ����)
	void SetItemDataPtrEx(INT32 a_index, const char *ap_string, void *ap_data, UINT8 a_auto_select = 1);
	// �׸� �߰��� 4����Ʈ �޸� ���� ��´�. (������ ����)
	void *GetItemDataPtr(INT32 a_index);
	// ������ �׸� �߰� 4����Ʈ ������ �����Ѵ�. (���� ����)
	void SetItemData(INT32 a_index, INT32 a_data);
	// ������ ��� InsertString�� ����ϰ� SetItemDataPtr �Լ��� ����ؾ� ������
	// �� �Լ��� ����ϸ� �� �Լ��� ����� ���ÿ� �����մϴ�.  (���� ����)
	void SetItemDataEx(INT32 a_index, const char *ap_string, INT32 a_data, UINT8 a_auto_select = 1);
	// �׸� �߰��� 4����Ʈ �޸� ���� ��´�. (���� ����)
	INT32 GetItemData(INT32 a_index);
	// ListBox�� �߰��� ���ڿ����� ���ϴ� ���ڿ��� �˻��Ѵ�. �� �Լ��� ����ϸ�
	// �ڽ��� ã�� ���� ���ڿ��� 'abc'�� ��쿡 'abc'�Ӹ� �ƴ϶� 'abcdef'�� ����
	// �κ������� ��ġ�ϴ� ���ڿ��� ã�� �� �ֽ��ϴ�.
	INT32 FindString(INT32 a_index, const char *ap_string);
	// ListBox�� �߰��� ���ڿ����� ���ϴ� ���ڿ��� �˻��Ѵ�. �� �Լ��� ��Ȯ�ϰ�
	// ��ġ�ϴ� ���ڿ��� �˻��մϴ�.
	INT32 FindStringExact(INT32 a_index, const char *ap_string);
	// ����ȭ�� ���ڿ��� �߰��ϴ� �Լ�
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
	CEasyComboBox(DRAW_COMBOBOX_ITEM afp_draw_item = NULL); // ��ü ������
	virtual ~CEasyComboBox(); // ��ü �ı���

	// �⺻ �Ӽ����� ComboBox�� �����ϴ� �Լ�
	virtual HWND Create(HWND ah_parent_wnd, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0);
	// Ȯ�� �Ӽ��� ����ؼ� ComboBox�� �����ϴ� �Լ�
	virtual HWND CreateEx(HWND ah_parent_wnd, const char *ap_title_name, INT32 a_sx, INT32 a_sy, INT32 a_ex, INT32 a_ey, INT32 a_ctrl_id, UINT32 a_style = 0, UINT32 a_ex_style = WS_EX_STATICEDGE);

	void ChangeDrawItemFunc(DRAW_COMBOBOX_ITEM afp_draw_item);
	// ���ڿ��� ComboBox�� �߰��ϴ� �Լ�, CBS_SORT �ɼ��� ������ �ִٸ� ������������ �����ؼ� �߰��Ѵ�.
	INT32 AddString(const char *ap_string, UINT8 a_auto_select = 1);
	// ���ڿ��� ����ڰ� ������ ��ġ�� �߰��ϴ� �Լ�
	INT32 InsertString(INT32 a_index, const char *ap_string, UINT8 a_auto_select = 1);
	// ����ڰ� ������ �׸� �߰��� ���ڿ��� ���̸� ��´�.
	INT32 GetTextLength(INT32 a_index);
	// ����ڰ� ������ �׸񿡼� ���ڿ��� �����ؼ� �����´�.
	INT32 GetText(INT32 a_index, char *ap_string, int a_max_len);
	// ComboBox�� Ư�� �׸��� �����Ѵ�.
	void SetCurSel(INT32 a_index);
	// ComboBox���� � �׸��� ���õǾ� �ִ��� ��ġ ���� ��´�.
	INT32 GetCurSel();
	// ComboBox�� �߰��� �׸��� ������ ��´�.
	INT32 GetCount();
	// ComboBox���� ������ �׸��� �����Ѵ�.
	void DeleteString(INT32 a_index);
	// ComboBox�� �߰��� ��� �׸��� �����Ѵ�.
	void ResetContent();
	// ������ �׸� �߰� 4����Ʈ ������ �����Ѵ�. (������ ����)
	void SetItemDataPtr(INT32 a_index, void *ap_data);
	// ������ ��� InsertString�� ����ϰ� SetItemDataPtr �Լ��� ����ؾ� ������
	// �� �Լ��� ����ϸ� �� �Լ��� ����� ���ÿ� �����մϴ�.  (������ ����)
	void SetItemDataPtrEx(INT32 a_index, const char *ap_string, void *ap_data, UINT8 a_auto_select = 1);
	// �׸� �߰��� 4����Ʈ �޸� ���� ��´�. (������ ����)
	void *GetItemDataPtr(INT32 a_index);
	// ������ �׸� �߰� 4����Ʈ ������ �����Ѵ�. (���� ����)
	void SetItemData(INT32 a_index, INT32 a_data);
	// ������ ��� InsertString�� ����ϰ� SetItemDataPtr �Լ��� ����ؾ� ������
	// �� �Լ��� ����ϸ� �� �Լ��� ����� ���ÿ� �����մϴ�.  (���� ����)
	void SetItemDataEx(INT32 a_index, const char *ap_string, INT32 a_data, UINT8 a_auto_select = 1);
	// �׸� �߰��� 4����Ʈ �޸� ���� ��´�. (���� ����)
	INT32 GetItemData(INT32 a_index);
	// ComboBox�� �߰��� ���ڿ����� ���ϴ� ���ڿ��� �˻��Ѵ�. �� �Լ��� ����ϸ�
	// �ڽ��� ã�� ���� ���ڿ��� 'abc'�� ��쿡 'abc'�Ӹ� �ƴ϶� 'abcdef'�� ����
	// �κ������� ��ġ�ϴ� ���ڿ��� ã�� �� �ֽ��ϴ�.
	INT32 FindString(INT32 a_index, const char *ap_string);
	// ComboBox�� �߰��� ���ڿ����� ���ϴ� ���ڿ��� �˻��Ѵ�. �� �Լ��� ��Ȯ�ϰ�
	// ��ġ�ϴ� ���ڿ��� �˻��մϴ�.
	INT32 FindStringExact(INT32 a_index, const char *ap_string);
	// ����ȭ�� ���ڿ��� �߰��ϴ� �Լ�
	int PrintFormat(const char *ap_format, ...);

	void SetItemHeight(INT32 a_height);

	virtual void OnDrawItem(DRAWITEMSTRUCT *ap_dis);
	virtual void OnMeasureItem(MEASUREITEMSTRUCT *ap_mis);
	virtual INT32 OnCtrlColor(HDC ah_dc, HWND ah_wnd);
};

class CEasyWnd
{
protected:
	// �������� Ȯ�� ��Ÿ�ϰ� �⺻ ��Ÿ��
	int m_ex_wnd_style, m_wnd_style;
	// �����찡 �⺻ ��¿� ����� GDI+ ��ü
	TW_GDIP m_gdip;

public:
	CEasyWnd();
	virtual ~CEasyWnd();

	// ����ڰ� ����� ������ ũ�⸦ �����ϴ� �Լ�
	void ChangeWorkSize(int a_cx, int a_cy);
	// ���� ������� GDI+ ��ü�� �ּҸ� ��ȯ�ϴ� �Լ�
	TW_GDIP *GetGDIP();
	// ��Ʈ���� ID�� ����ؼ� ��Ʈ���� �ּҸ� ��� �Լ�
	CEasyCtrl *FindControl(int a_id);
	// ������ ������ �����ϴ� �Լ�
	void InvalidateRect(RECT a_rect);
	// �۾� ���� ��ü�� �����ϴ� �Լ�
	void Invalidate();
	// ���콺�� ������ ������ ����� ��� �޽����� ���� �� �ֵ��� �ϴ� �Լ�
	void SetCapture();
	// SetCapture�� �����ϴ� �Լ�
	void ReleaseCapture();
	// �۲��� ��� �Լ�
	HFONT GetUserFont(const char *ap_font_name, short a_size, UINT8 a_style);

	// ��ư�� �����ϴ� �Լ�
	CEasyBtn *CreateButton(const char *ap_name, int a_x, int a_y, int a_width, int a_height, int a_id, int a_style = 0, int a_ex_syle = 0);
	// ����Ʈ ��Ʈ���� �����ϴ� �Լ�
	CEasyEdit *CreateEdit(int a_x, int a_y, int a_width, int a_height, int a_id, int a_style = 0, int a_ex_syle = 0);
	// ����Ʈ �ڽ��� �����ϴ� �Լ�
	CEasyListBox *CreateListBox(int a_x, int a_y, int a_width, int a_height, int a_id, void *afp_draw = NULL, int a_style = 0, int a_ex_syle = 0);
	// �޺� �ڽ��� �����ϴ� �Լ�
	CEasyComboBox *CreateComboBox(int a_x, int a_y, int a_width, int a_height, int a_id, void *afp_draw = NULL, int a_style = 0, int a_ex_syle = 0);

	// ������ ��Ʈ���� �����ϴ� �Լ�
	void DestroyControl(CEasyCtrl *ap_ctrl);
	void DestroyControl(int a_id);

	// ����� �����츦 �����ϴ� �Լ�
	virtual int Create(const char *ap_title, int a_x, int a_y);
	// �������� ũ�Ⱑ ����Ǿ��� �� ȣ��Ǵ� �Լ�
	virtual void OnSize(UINT32 a_type, int a_cx, int a_cy) { }
	// ȭ�鿡 ����� ������ �׸��� �Լ�
	virtual void OnDraw() { }
	// �����찡 ������ ���Ŀ� ȣ��Ǵ� �Լ�
	virtual void OnCreate(CREATESTRUCT *ap_create_info) { }
	// ���콺 ���� ��ư Ŭ�� ó���� �Լ�
	virtual void OnLButtonDown(int a_mixed_key, POINT a_pos) { }
	// ���콺 ���� ��ư Ŭ�� ���� ó���� �Լ�
	virtual void OnLButtonUp(int a_mixed_key, POINT a_pos){ }
	// ���콺 �̵� ó���� �Լ�
	virtual void OnMouseMove(int a_mixed_key, POINT a_pos) { }
	// ��� �޽��� ó���� �Լ�
	virtual void OnCommand(int a_id, int a_notify_code) { }
	// WM_DRAWITEM �޽��� ó���� �Լ�
	virtual void OnDrawItem(int a_id, LPARAM lParam);
	// WM_MEASUREITEM �޽��� ó���� �Լ�
	virtual void OnMeasureItem(int a_id, LPARAM lParam);
	// WM_CTLCOLOR �޽��� ó���� �Լ�
	virtual int OnCtrlColor(WPARAM wParam, LPARAM lParam);
	// WM_DESTROY �޽��� ó���� �Լ�
	virtual void OnDestroy();
	// �����쿡 �߻��ϴ� �Ϲ� �޽����� ó���ϴ� �Լ�
	virtual int WndProc(HWND ah_wnd, UINT a_message_id, WPARAM wParam, LPARAM lParam){ return 0; }
};

class CEasyApp
{
protected:
	// ���� ���α׷��� ����ϴ� ������ Ŭ���� �̸�
	char m_app_name[128];
	// �����쿡�� ����� �޴� ID, �ΰ� ������ ID - �Ѵ� �⺻ �� 0
	int m_menu_id, m_system_icon_id;

public:
	CEasyApp();
	virtual ~CEasyApp();

	// ���� ���α׷��� ������ Ŭ���� �̸��� ��ȯ�ϴ� �Լ�
	const char *GetAppName();
	// ���� ���α׷��� ����� Window Ŭ������ ����ϴ� �Լ�
	virtual int RegisterWndClass();
	// ���� ���α׷��� ���۵� �� ȣ��Ǵ� �Լ� - �ݵ�� �������̵��ؾ� ��
	virtual void InitInstance(){ }
	// ���� ���α׷��� ����� �� ȣ��Ǵ� �Լ�
	virtual void ExitInstance(){ };
};

#endif
