#ifndef _TW_GDIP_H_
#define _TW_GDIP_H_

// �� Ŭ������ GDI+ �Լ����� ���ϰ� ����� �� �ֵ��� ��������ϴ�.
// �� Ŭ������ ó�� ���� ����� ����� �����ϴ� �������� ���۱� ǥ�ø� ������ �ּ���.
// Ŭ���� �ʱ� �� ���� : �輺��(tipsware@naver.com)
// Ŭ���� ���� : https://cafe.naver.com/mythread
// ó�� ���� ��¥ : 2020�� 3�� 24�� (ȭ����)
// TW_DCP���� TW_GDIP�� ����� ��¥ : 2023�� 6�� 28�� (������)
// ������ ������Ʈ ��¥ : 2023�� 8�� 16�� (������) - Ver 0.18

#include <Gdiplus.h>        // GDI+�� ����ϱ� ���� ��� ����
using namespace Gdiplus;    // Gdiplus:: ǥ���� ���̱� ����
using namespace DllExports; // GDI+�� �Լ� �տ� DllExports:: ǥ���� ���̱� ����

#define RGB24(r,g,b) (0xFF000000 | ((r) << 16) | ((g) << 8) | (b))   // 0xFFRRGGBB
#define RGB32(a,r,g,b) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))  // 0xAARRGGBB

// GDI+ ����� ���� ���ϰ� ����� �� �ֵ��� �����ϴ� Ŭ����
class TW_GDIP
{
protected:
	GpBitmap *mp_bitmap; // GDI+ ����� ������ ��Ʈ�� ��ü
	GpGraphics *mp_graphics; // ��Ʈ�ʿ� ����� GDI+ ��� ��ü
	GpPen *mp_stock_pen = NULL; // ��½� ����� �� ��ü
	GpSolidFill *mp_stock_brush, *mp_stock_font_brush; // ��½� ����� �귯�� ��ü
	GpFontFamily *mp_stock_font_family;  // ���� ���� ��ü
	GpFont *mp_stock_font; // �۲� ��ü
	GpStringFormat *mp_stock_str_format;
	ARGB m_def_clear_color = RGB24(255, 255, 255);

	int m_cx, m_cy;  // ��� ������ ũ�� (���� ����)
	static ULONG_PTR m_token;  // GDI+ ���̺귯�� �������
	static int m_object_count;  // DCP ��ü�� ������ ���
	wchar_t m_temp_str[2048]; // ���������� ����� �ӽ� ����

public:
	TW_GDIP();
	TW_GDIP(int a_cx, int a_cy);
	virtual ~TW_GDIP();

	void Init();  // ��ü�� �ʱ�ȭ�� �� ����ϴ� �⺻ �Լ�
	int CreateGDIP(int a_cx, int a_cy); // GDI+ ��� ������ �����ϴ� �Լ�
	void Clear(ARGB a_color); // a_color�� ��ü ������ ä���.
	void Clear(); // �������� ���� Clear �������� ��ü ������ ä���.

	// ���ο� ������ �������� �ʰ� ���� �귯�÷� �簢���� �׸��� �Լ� (ä��⸸ ����)
	void FillRect(int a_x, int a_y, int a_cx, int a_cy);
	void FillRect(float a_x, float a_y, float a_cx, float a_cy);
	// ������ �������� �簢���� �׸��� �Լ� (ä��⸸ ����)
	void FillRect(int a_x, int a_y, int a_cx, int a_c, ARGB a_color);
	void FillRect(float a_x, float a_y, float a_cx, float a_cy, ARGB a_color);
	// ������ Brush���� �簢���� �׸��� �Լ� (ä��⸸ ����)
	void FillRect(int a_x, int a_y, int a_cx, int a_cy, GpBrush *ap_brush);
	void FillRect(float a_x, float a_y, float a_cx, float a_cy, GpBrush *ap_brush);

	// ���ο� ������ �������� �ʰ� ���� ������ �簢���� �׸��� �Լ� (�׵θ��� �׸�)
	void DrawRect(int a_x, int a_y, int a_cx, int a_cy);
	void DrawRect(float a_x, float a_y, float a_cx, float a_cy);
	// ������ �������� �簢���� �׸��� �Լ� (�׵θ��� �׸�)
	void DrawRect(int a_x, int a_y, int a_cx, int a_cy, ARGB a_color);
	void DrawRect(float a_x, float a_y, float a_cx, float a_cy, ARGB a_color);
	// ������ ������ �簢���� �׸��� �Լ� (�׵θ��� �׸�)
	void DrawRect(int a_x, int a_y, int a_cx, int a_cy, GpPen *ap_pen);
	void DrawRect(float a_x, float a_y, float a_cx, float a_cy, GpPen *ap_pen);

	// ������ ����ϴ� ��� �귯�÷� �簢���� �׸��� �Լ� (ä���, �׵θ� ��� ����)
	void Rectangle(int a_x, int a_y, int a_cx, int a_cy);
	void Rectangle(float a_x, float a_y, float a_cx, float a_cy);
	void Rectangle(RectF *ap_rect);

	// ���ο� ������ �������� �ʰ� ���� �귯�÷� Ÿ���� �׸��� �Լ� (ä��⸸ ����)
	void FillEllipse(int a_x, int a_y, int a_cx, int a_cy);
	void FillEllipse(float a_x, float a_y, float a_cx, float a_cy);
	// ������ �������� Ÿ���� �׸��� �Լ� (ä��⸸ ����)
	void FillEllipse(int a_x, int a_y, int a_cx, int a_cy, ARGB a_color);
	void FillEllipse(float a_x, float a_y, float a_cx, float a_cy, ARGB a_color);
	// ������ Brush���� Ÿ���� �׸��� �Լ� (ä��⸸ ����)
	void FillEllipse(int a_x, int a_y, int a_cx, int a_cy, GpBrush *ap_brush);
	void FillEllipse(float a_x, float a_y, float a_cx, float a_cy, GpBrush *ap_brush);

	// ���ο� ������ �������� �ʰ� ���� ������ Ÿ���� �׸��� �Լ� (�׵θ��� �׸�)
	void DrawEllipse(int a_x, int a_y, int a_cx, int a_cy);
	void DrawEllipse(float a_x, float a_y, float a_cx, float a_cy);
	// ������ �������� Ÿ���� �׸��� �Լ� (�׵θ��� �׸�)
	void DrawEllipse(int a_x, int a_y, int a_cx, int a_cy, ARGB a_color);
	void DrawEllipse(float a_x, float a_y, float a_cx, float a_cy, ARGB a_color);
	// ������ ������ Ÿ���� �׸��� �Լ� (�׵θ��� �׸�)
	void DrawEllipse(int a_x, int a_y, int a_cx, int a_cy, GpPen *ap_pen);
	void DrawEllipse(float a_x, float a_y, float a_cx, float a_cy, GpPen *ap_pen);

	// ������ ����ϴ� ��� �귯�÷� Ÿ���� �׸��� �Լ� (ä���, �׵θ� ��� ����)
	void Ellipse(int a_x, int a_y, int a_cx, int a_cy);
	void Ellipse(float a_x, float a_y, float a_cx, float a_cy);
	void Ellipse(RectF *ap_rect);

	// ���� ������ ���� �׸��� �Լ� (���� ���� �� �� ���)
	void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey);
	void DrawLine(float a_sx, float a_sy, float a_ex, float a_ey);
	// ������ �������� ���� �׸��� �Լ� (���� ���� �� �� ���)
	void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);
	void DrawLine(float a_sx, float a_sy, float a_ex, float a_ey, ARGB a_color);
	// ������ ������ ���� �׸��� �Լ� (���� ���� �� �� ���)
	void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, GpPen *ap_pen);
	void DrawLine(float a_sx, float a_sy, float a_ex, float a_ey, GpPen *ap_pen);

	// ���� ������ ���Ӽ��� �׸��� �Լ�
	void DrawLines(GpPoint *ap_pos_list, INT a_count);
	void DrawLines(GpPointF *ap_pos_list, INT a_count);
	// ������ �������� ���Ӽ��� �׸��� �Լ�
	void DrawLines(GpPoint *ap_pos_list, INT a_count, ARGB a_color);
	void DrawLines(GpPointF *ap_pos_list, INT a_count, ARGB a_color);
	// ������ ������ ���Ӽ��� �׸��� �Լ�
	void DrawLines(GpPoint *ap_pos_list, INT a_count, GpPen *ap_pen);
	void DrawLines(GpPointF *ap_pos_list, INT a_count, GpPen *ap_pen);

	// ������ �������� ȣ�� �׸��� �Լ�
	void DrawArc(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle, ARGB a_color);
	void DrawArc(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle, ARGB a_color);
	// ���� ������ ȣ�� �׸��� �Լ�
	void DrawArc(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle);
	void DrawArc(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle);
	// ������ ������ ȣ�� �׸��� �Լ�
	void DrawArc(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle, GpPen *ap_pen);
	void DrawArc(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle, GpPen *ap_pen);

	// ������ �������� ���̸� �׸��� �Լ�
	void DrawPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle, ARGB a_color);
	void DrawPie(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle, ARGB a_color);
	// ���� ������ ���̸� �׸��� �Լ� (�׵θ��� �׸�)
	void DrawPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle);
	void DrawPie(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle);
	// ������ ������ ���̸� �׸��� �Լ� (�׵θ��� �׸�)
	void DrawPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle, GpPen *ap_pen);
	void DrawPie(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle, GpPen *ap_pen);

	// ������ �������� ���̸� �׸��� �Լ� (���� ä���)
	void FillPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle, ARGB a_color);
	void FillPie(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle, ARGB a_color);
	// ���� ������ ���̸� �׸��� �Լ� (���� ä���)
	void FillPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle);
	void FillPie(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle);
	// ������ ������ ���̸� �׸��� �Լ� (���� ä���)
	void FillPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle, GpBrush *ap_brush);
	void FillPie(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle, GpBrush *ap_brush);

	// ���̸� �׸��� �Լ�
	void Pie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle);
	void Pie(float  a_x, float  a_y, float  a_cx, float  a_cy, REAL a_start_angle, REAL a_sweep_angle);

	// ���ڿ��� ������ ��ġ�� ����ϴ� �Լ� (���� ���� ����)
	void TextOut(int a_x, int a_y, const wchar_t *ap_str, int a_str_len = -1);
	void TextOut(float a_x, float a_y, const wchar_t *ap_str, int a_str_len = -1);
	void TextOut(GpFont *ap_font, int a_x, int a_y, const wchar_t *ap_str, int a_str_len = -1);
	void TextOut(GpFont *ap_font, float a_x, float a_y, const wchar_t *ap_str, int a_str_len = -1);
	int TextOutEx(int a_x, int a_y, const wchar_t *ap_format, ...); // ����ȭ�� ��� ����
	int TextOutEx(float a_x, float a_y, const wchar_t *ap_format, ...);

	// ���ڿ��� ������ ������ �����ؼ� ����ϴ� �Լ�
	void DrawText(RectF *ap_rect, const wchar_t *ap_str, int a_str_len = -1,
		StringAlignment a_x_align = StringAlignmentCenter, StringAlignment a_y_align = StringAlignmentCenter);
	void DrawText(GpFont *ap_font, RectF *ap_rect, const wchar_t *ap_str, int a_str_len = -1,
		StringAlignment a_x_align = StringAlignmentCenter, StringAlignment a_y_align = StringAlignmentCenter);
	int DrawTextEx(RectF *ap_rect, StringAlignment a_x_align, StringAlignment a_y_align, const wchar_t *ap_format, ...); // ����ȭ�� �������

	// ������ ���ڿ��� ��µǾ��� �� ���� ���̸� ����ϴ� �Լ�
	SIZE GetTextExtent(const wchar_t *ap_str, int a_len);
	SizeF GetTextExtentF(const wchar_t *ap_str, int a_len);


	// ���޵� �̹��� ��ü�� ����ϴ� �Լ� (�ٸ� �̹��� ��ü�� �� �̹��� ��ü�� ����ϴ� �Լ�)
	void Draw(GpImage *ap_image, int a_x, int a_y);
	void Draw(GpImage *ap_image, float a_x, float a_y);
	// ���޵� �̹��� ��ü�� ����ϴ� �Լ� (�ٸ� �̹��� ��ü�� �� �̹��� ��ü�� ����ϴ� �Լ�)
	void Draw(GpImage *ap_image, int a_x, int a_y, int a_cx, int a_cy);
	void Draw(GpImage *ap_image, float a_x, float a_y, float a_cx, float a_cy);
	// ���޵� �̹��� ��ü�� ����ϴ� �Լ� (�̹��� �Ӽ��� �����ϴ� �Լ�)
	void Draw(GpImage *ap_image, int a_x, int a_y, GpImageAttributes *ap_attr);
	void Draw(GpImage *ap_image, float a_x, float a_y, GpImageAttributes *ap_attr);
	// ���޵� �̹��� ��ü�� ���� ��ǥ�� ũ�⸦ �����ؼ� ����ϴ� �Լ� (�̹��� �Ӽ��� �����ϴ� �Լ�)
	void Draw(GpImage *ap_image, int a_x, int a_y, int a_cx, int a_cy, GpImageAttributes *ap_attr);
	void Draw(GpImage *ap_image, float a_x, float a_y, float a_cx, float a_cy, GpImageAttributes *ap_attr);
	// ���޵� �̹��� ��ü�� ��ü ������ ����ϴ� �Լ� (�̹��� �Ӽ��� �����ϴ� �Լ�)
	void DrawFullImage(GpImage *ap_image, int a_x, int a_y, GpImageAttributes *ap_attr);
	void DrawFullImage(GpImage *ap_image, float a_x, float a_y, GpImageAttributes *ap_attr);
	// ���޵� �̹��� ��ü ũ��� ������ ����ϴ� �Լ� (�̹��� �Ӽ��� �����ϴ� �Լ�)
	void DrawRealImage(GpImage *ap_image, int a_x, int a_y, GpImageAttributes *ap_attr);
	void DrawRealImage(GpImage *ap_image, float a_x, float a_y, GpImageAttributes *ap_attr);

	// ���޵� DC�� ���� �̹����� ����ϴ� �Լ�
	void Draw(HDC ah_dc, int a_x = 0, int a_y = 0);
	void DrawF(HDC ah_dc, float a_x = 0.0f, float a_y = 0.0f);
	// ���޵� DC�� ���� �̹����� ����ϴ� �Լ�
	void Draw(HDC ah_dc, int a_x, int a_y, int a_cx, int a_cy);
	void DrawF(HDC ah_dc, float a_x, float a_y, float a_cx, float a_cy);


	// ���ο� ������ �������� �ʰ� ���� ������ ������ Path�� ����ϴ� �Լ� (�׵θ��� �׸�)
	void DrawUserPath(GpPath *ap_path);
	// ������ �� �������� Path�� ����ϴ� �Լ� (�׵θ��� �׸�)
	void DrawUserPath(GpPath *ap_path, ARGB a_color);
	// ������ ������ Path�� ����ϴ� �Լ� (�׵θ��� �׸�)
	void DrawUserPath(GpPath *ap_path, GpPen *ap_pen);

	// ���ο� ������ �������� �ʰ� ���� �귯�÷� ������ Path�� ����ϴ� �Լ� (���� ä���)
	void FillUserPath(GpPath *ap_path);
	// ������ �귯�� �������� Path�� ����ϴ� �Լ� (�׵θ��� �׸�)
	void FillUserPath(GpPath *ap_path, ARGB a_color);
	// ������ �귯�÷� Path�� ����ϴ� �Լ� (�׵θ��� �׸�)
	void FillUserPath(GpPath *ap_path, GpBrush *ap_brush);

	// ������ ���� �����ϴ� ��� �׸��� �Լ�
	void DrawCurve(GpPoint *ap_pos_list, int a_count, float a_tension);
	void DrawCurve(GpPointF *ap_pos_list, int a_count, float a_tension);
	// ������ ���� �����ϴ� ������ ���� �׸��� �Լ�
	void DrawBezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
	void DrawBezier(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

	// �ٰ����� �׸��� �Լ�
	void Polygon(GpPoint *ap_pos_list, int a_count);
	void Polygon(GpPointF *ap_pos_list, int a_count);

	// ���ο� ������ �������� �ʰ� ���� ������ �ٰ����� �׸��� �Լ� (�׵θ��� �׸�)
	void DrawPolygon(GpPoint *ap_pos_list, int a_count);
	void DrawPolygon(GpPointF *ap_pos_list, int a_count);
	// ������ �������� �ٰ����� �׸��� �Լ� (�׵θ��� �׸�)
	void DrawPolygon(GpPoint *ap_pos_list, int a_count, ARGB a_color);
	void DrawPolygon(GpPointF *ap_pos_list, int a_count, ARGB a_color);
	// ������ ������ �ٰ����� �׸��� �Լ� (�׵θ��� �׸�)
	void DrawPolygon(GpPoint *ap_pos_list, int a_count, GpPen *ap_pen);
	void DrawPolygon(GpPointF *ap_pos_list, int a_count, GpPen *ap_pen);

	// ���ο� ������ �������� �ʰ� ���� �귯�÷� �ٰ����� �׸��� �Լ� (ä��⸸ ����)
	void FillPolygon(GpPoint *ap_pos_list, int a_count);
	void FillPolygon(GpPointF *ap_pos_list, int a_count);
	// ������ �������� �ٰ����� �׸��� �Լ� (ä��⸸ ����)
	void FillPolygon(GpPoint *ap_pos_list, int a_count, ARGB a_color);
	void FillPolygon(GpPointF *ap_pos_list, int a_count, ARGB a_color);
	// ������ Brush���� �ٰ����� �׸��� �Լ� (ä��⸸ ����)
	void FillPolygon(GpPoint *ap_pos_list, int a_count, GpBrush *ap_brush);
	void FillPolygon(GpPointF *ap_pos_list, int a_count, GpBrush *ap_brush);

	GpPath *MakeRoundRectPath(int a_x, int a_y, int a_cx, int a_cy, int a_rcx, int a_rcy); // RoundRect�� Path�� �������ִ� �Լ�
	GpPath *MakeRoundRectPath(float a_x, float a_y, float a_cx, float a_cy, float a_rcx, float a_rcy);
	GpPath *MakeUpStyleRoundRectPath(int a_x, int a_y, int a_cx, int a_cy, int a_rcx, int a_rcy); // RoundRect�� Path�� �������ִ� �Լ�
	GpPath *MakeUpStyleRoundRectPath(float a_x, float a_y, float a_cx, float a_cy, float a_rcx, float a_rcy);
	void DeletePathData(GpPath *ap_path); // Path �����͸� �����ϴ� �Լ�
	GpPath *OpenPath(); // Path������ �����ϴ� �Լ�
	void ClosePath(GpPath *ap_path); // Path������ �������ϴ� �Լ�

	void SetBrushColor(ARGB a_color); // �귯�� ��ü�� ������ �����ϴ� �Լ�
	void SetPenColor(ARGB a_color); // �� ��ü�� ������ �����ϴ� �Լ�
	void SetPenColor(DashStyle a_style, REAL a_width, ARGB a_color); // �� ��ü�� �Ӽ��� �����ϴ� �Լ� (��Ÿ��, ����, ����)
	void SetTextColor(ARGB a_color); // �۲��� ������ �����ϴ� �Լ�

	void ChangeFont(const wchar_t *ap_font_name, REAL a_size = 15, INT a_style = FontStyleRegular); // �۲� ������ �����ϴ� �Լ�
	GpFontFamily *CreateFontFamily(const wchar_t *ap_font_name); // �۲� ������ �����ϴ� �Լ�	
	GpFont *CreateFont(GpFontFamily *ap_family, REAL a_size, INT a_style); // �۲��� �����ϴ� �Լ�
	void DeleteFontFamily(GpFontFamily *ap_family); // ������ �۲� ������ �����ϴ� �Լ�
	void DeleteFont(GpFont *ap_font); // ������ �۲��� �����ϴ� �Լ�
	void DeleteFontInfo(GpFontFamily *ap_family, GpFont *ap_font); // ������ �۲� ������ �����ϴ� �Լ�

	void SetSmoothingMode(UINT8 a_smooth = 1); // ��Ƽ����� ���� ������ ������ ���θ� �����ϴ� �Լ�

	GpPen *GetStockPen(); // ���������� �����Ǿ� �ִ� �� ��ü�� �ּҸ� ��� �Լ�
	GpBrush *GetStockBrush(); // ���������� �����Ǿ� �ִ� �귯�� ��ü�� �ּҸ� ��� �Լ�
	void ChangePenDashCap(DashCap a_cap_type, GpPen *ap_pen = NULL); // Dash ������ ���� ��� Dash�� ���� ������� �����ϴ� �Լ� (ap_pen�� NULL�̸� �⺻ �濡 ���� ��)	
	void ChangePenCap(LineCap a_cap_type, GpPen *ap_pen = NULL); // ���� ���� ������� �����ϴ� �Լ� (ap_pen�� NULL�̸� �⺻ �濡 ���� ��)
	void ChangePenLineJoin(LineJoin a_join_type, GpPen *ap_pen = NULL); // ���� ���� ������ ���� ����� �����ϴ� �Լ� (ap_pen�� NULL�̸� �⺻ �濡 ���� ��)

	GpImage *LoadImage(const wchar_t *ap_path); // ������ �̹��� ������ �о �̹��� ��ü�� ����� �Լ�
	void DestroyImage(GpImage *ap_image); // ������ �̹��� ��ü�� �����ϴ� �Լ�

	// ������ �̹����� ����ؼ� a_width * a_height ũ���� ������ �̹����� �����ϴ� �Լ�
	GpImage *MakeImageForThumbnail(GpImage *ap_src_image, int a_width, int a_height);

	// (a_x, a_y)��ġ�� ���� ������(0, 0)���� �����ϴ� �Լ�
	void SetViewportOrg(REAL a_x, REAL a_y, MatrixOrder a_order_type = MatrixOrderAppend);
	// ���� ���� ��� ��ǥ�� ������ ��Ʈ���� ������ �ݿ��ϵ��� �ϴ� �Լ�
	void ApplyMatrix(GpMatrix *ap_matrix);

	GpMatrix *CreateMatrix(); // ���ο� ��Ʈ������ �����ϴ� �Լ�
	void DeleteMatrix(GpMatrix *ap_matrix);  // ��Ʈ������ �����ϴ� �Լ�

	GpGraphics *GetGraphics(); // GDI+ ��¿� ��ü�� �ּҸ� ��� �Լ�
	GpImage *GetStockImage(); // GDI+ ��¿� ����ϴ� �̹��� ��ü�� �ּҸ� ��� �Լ�

	// �̹��� Encoder�� CLSID ���� ��� �Լ�
	UINT GetEncoderClsid(const wchar_t *ap_format, CLSID *ap_clsid);

	int GetWidth();
	int GetHeight();
};

#endif