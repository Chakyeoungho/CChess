#ifndef _TW_GDIP_H_
#define _TW_GDIP_H_

// 이 클래스는 GDI+ 함수들을 편하게 사용할 수 있도록 만들었습니다.
// 이 클래스를 처음 만든 사람의 노력을 존중하는 마음으로 저작권 표시를 유지해 주세요.
// 클래스 초기 모델 제작 : 김성엽(tipsware@naver.com)
// 클래스 배포 : https://cafe.naver.com/mythread
// 처음 만든 날짜 : 2020년 3월 24일 (화요일)
// TW_DCP에서 TW_GDIP로 변경된 날짜 : 2023년 6월 28일 (수요일)
// 마지막 업데이트 날짜 : 2023년 8월 16일 (수요일) - Ver 0.18

#include <Gdiplus.h>        // GDI+를 사용하기 위한 헤더 파일
using namespace Gdiplus;    // Gdiplus:: 표현을 줄이기 위해
using namespace DllExports; // GDI+용 함수 앞에 DllExports:: 표현을 줄이기 위해

#define RGB24(r,g,b) (0xFF000000 | ((r) << 16) | ((g) << 8) | (b))   // 0xFFRRGGBB
#define RGB32(a,r,g,b) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))  // 0xAARRGGBB

// GDI+ 기술을 좀더 편하게 사용할 수 있도록 제공하는 클래스
class TW_GDIP
{
protected:
	GpBitmap *mp_bitmap; // GDI+ 출력을 저장할 비트맵 객체
	GpGraphics *mp_graphics; // 비트맵에 연결된 GDI+ 출력 객체
	GpPen *mp_stock_pen = NULL; // 출력시 사용할 펜 객체
	GpSolidFill *mp_stock_brush, *mp_stock_font_brush; // 출력시 사용할 브러시 객체
	GpFontFamily *mp_stock_font_family;  // 문자 집합 객체
	GpFont *mp_stock_font; // 글꼴 객체
	GpStringFormat *mp_stock_str_format;
	ARGB m_def_clear_color = RGB24(255, 255, 255);

	int m_cx, m_cy;  // 출력 영역의 크기 (폭과 높이)
	static ULONG_PTR m_token;  // GDI+ 라이브러리 사용정보
	static int m_object_count;  // DCP 객체의 개수를 계산
	wchar_t m_temp_str[2048]; // 내부적으로 사용할 임시 버퍼

public:
	TW_GDIP();
	TW_GDIP(int a_cx, int a_cy);
	virtual ~TW_GDIP();

	void Init();  // 객체를 초기화할 때 사용하는 기본 함수
	int CreateGDIP(int a_cx, int a_cy); // GDI+ 출력 정보를 구성하는 함수
	void Clear(ARGB a_color); // a_color로 전체 영역을 채운다.
	void Clear(); // 마지막에 사용된 Clear 색상으로 전체 영역을 채운다.

	// 새로운 색상을 지정하지 않고 기존 브러시로 사각형을 그리는 함수 (채우기만 수행)
	void FillRect(int a_x, int a_y, int a_cx, int a_cy);
	void FillRect(float a_x, float a_y, float a_cx, float a_cy);
	// 지정된 색상으로 사각형을 그리는 함수 (채우기만 수행)
	void FillRect(int a_x, int a_y, int a_cx, int a_c, ARGB a_color);
	void FillRect(float a_x, float a_y, float a_cx, float a_cy, ARGB a_color);
	// 지정된 Brush으로 사각형을 그리는 함수 (채우기만 수행)
	void FillRect(int a_x, int a_y, int a_cx, int a_cy, GpBrush *ap_brush);
	void FillRect(float a_x, float a_y, float a_cx, float a_cy, GpBrush *ap_brush);

	// 새로운 색상을 지정하지 않고 기존 펜으로 사각형을 그리는 함수 (테두리만 그림)
	void DrawRect(int a_x, int a_y, int a_cx, int a_cy);
	void DrawRect(float a_x, float a_y, float a_cx, float a_cy);
	// 지정된 색상으로 사각형을 그리는 함수 (테두리만 그림)
	void DrawRect(int a_x, int a_y, int a_cx, int a_cy, ARGB a_color);
	void DrawRect(float a_x, float a_y, float a_cx, float a_cy, ARGB a_color);
	// 지정된 펜으로 사각형을 그리는 함수 (테두리만 그림)
	void DrawRect(int a_x, int a_y, int a_cx, int a_cy, GpPen *ap_pen);
	void DrawRect(float a_x, float a_y, float a_cx, float a_cy, GpPen *ap_pen);

	// 기존에 사용하던 펜과 브러시로 사각형을 그리는 함수 (채우기, 테두리 모두 수행)
	void Rectangle(int a_x, int a_y, int a_cx, int a_cy);
	void Rectangle(float a_x, float a_y, float a_cx, float a_cy);
	void Rectangle(RectF *ap_rect);

	// 새로운 색상을 지정하지 않고 기존 브러시로 타원을 그리는 함수 (채우기만 수행)
	void FillEllipse(int a_x, int a_y, int a_cx, int a_cy);
	void FillEllipse(float a_x, float a_y, float a_cx, float a_cy);
	// 지정된 색상으로 타원을 그리는 함수 (채우기만 수행)
	void FillEllipse(int a_x, int a_y, int a_cx, int a_cy, ARGB a_color);
	void FillEllipse(float a_x, float a_y, float a_cx, float a_cy, ARGB a_color);
	// 지정된 Brush으로 타원을 그리는 함수 (채우기만 수행)
	void FillEllipse(int a_x, int a_y, int a_cx, int a_cy, GpBrush *ap_brush);
	void FillEllipse(float a_x, float a_y, float a_cx, float a_cy, GpBrush *ap_brush);

	// 새로운 색상을 지정하지 않고 기존 펜으로 타원을 그리는 함수 (테두리만 그림)
	void DrawEllipse(int a_x, int a_y, int a_cx, int a_cy);
	void DrawEllipse(float a_x, float a_y, float a_cx, float a_cy);
	// 지정된 색상으로 타원을 그리는 함수 (테두리만 그림)
	void DrawEllipse(int a_x, int a_y, int a_cx, int a_cy, ARGB a_color);
	void DrawEllipse(float a_x, float a_y, float a_cx, float a_cy, ARGB a_color);
	// 지정된 펜으로 타원을 그리는 함수 (테두리만 그림)
	void DrawEllipse(int a_x, int a_y, int a_cx, int a_cy, GpPen *ap_pen);
	void DrawEllipse(float a_x, float a_y, float a_cx, float a_cy, GpPen *ap_pen);

	// 기존에 사용하던 펜과 브러시로 타원을 그리는 함수 (채우기, 테두리 모두 수행)
	void Ellipse(int a_x, int a_y, int a_cx, int a_cy);
	void Ellipse(float a_x, float a_y, float a_cx, float a_cy);
	void Ellipse(RectF *ap_rect);

	// 기존 펜으로 선을 그리는 함수 (시작 점과 끝 점 사용)
	void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey);
	void DrawLine(float a_sx, float a_sy, float a_ex, float a_ey);
	// 지정한 색상으로 선을 그리는 함수 (시작 점과 끝 점 사용)
	void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);
	void DrawLine(float a_sx, float a_sy, float a_ex, float a_ey, ARGB a_color);
	// 지정한 펜으로 선을 그리는 함수 (시작 점과 끝 점 사용)
	void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, GpPen *ap_pen);
	void DrawLine(float a_sx, float a_sy, float a_ex, float a_ey, GpPen *ap_pen);

	// 기존 펜으로 연속선을 그리는 함수
	void DrawLines(GpPoint *ap_pos_list, INT a_count);
	void DrawLines(GpPointF *ap_pos_list, INT a_count);
	// 지정한 색상으로 연속선을 그리는 함수
	void DrawLines(GpPoint *ap_pos_list, INT a_count, ARGB a_color);
	void DrawLines(GpPointF *ap_pos_list, INT a_count, ARGB a_color);
	// 지정한 펜으로 연속선을 그리는 함수
	void DrawLines(GpPoint *ap_pos_list, INT a_count, GpPen *ap_pen);
	void DrawLines(GpPointF *ap_pos_list, INT a_count, GpPen *ap_pen);

	// 지정한 색상으로 호를 그리는 함수
	void DrawArc(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle, ARGB a_color);
	void DrawArc(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle, ARGB a_color);
	// 기존 펜으로 호를 그리는 함수
	void DrawArc(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle);
	void DrawArc(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle);
	// 지정한 펜으로 호를 그리는 함수
	void DrawArc(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle, GpPen *ap_pen);
	void DrawArc(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle, GpPen *ap_pen);

	// 지정한 색상으로 파이를 그리는 함수
	void DrawPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle, ARGB a_color);
	void DrawPie(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle, ARGB a_color);
	// 기존 펜으로 파이를 그리는 함수 (테두리만 그림)
	void DrawPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle);
	void DrawPie(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle);
	// 지정한 펜으로 파이를 그리는 함수 (테두리만 그림)
	void DrawPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle, GpPen *ap_pen);
	void DrawPie(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle, GpPen *ap_pen);

	// 지정한 색상으로 파이를 그리는 함수 (내부 채우기)
	void FillPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle, ARGB a_color);
	void FillPie(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle, ARGB a_color);
	// 기존 펜으로 파이를 그리는 함수 (내부 채우기)
	void FillPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle);
	void FillPie(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle);
	// 지정한 펜으로 파이를 그리는 함수 (내부 채우기)
	void FillPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle, GpBrush *ap_brush);
	void FillPie(float a_x, float a_y, float a_cx, float a_cy, REAL a_start_angle, REAL a_sweep_angle, GpBrush *ap_brush);

	// 파이를 그리는 함수
	void Pie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle);
	void Pie(float  a_x, float  a_y, float  a_cx, float  a_cy, REAL a_start_angle, REAL a_sweep_angle);

	// 문자열을 지정한 위치에 출력하는 함수 (색상 지정 가능)
	void TextOut(int a_x, int a_y, const wchar_t *ap_str, int a_str_len = -1);
	void TextOut(float a_x, float a_y, const wchar_t *ap_str, int a_str_len = -1);
	void TextOut(GpFont *ap_font, int a_x, int a_y, const wchar_t *ap_str, int a_str_len = -1);
	void TextOut(GpFont *ap_font, float a_x, float a_y, const wchar_t *ap_str, int a_str_len = -1);
	int TextOutEx(int a_x, int a_y, const wchar_t *ap_format, ...); // 형식화된 출력 지원
	int TextOutEx(float a_x, float a_y, const wchar_t *ap_format, ...);

	// 문자열을 지정한 영역에 정렬해서 출력하는 함수
	void DrawText(RectF *ap_rect, const wchar_t *ap_str, int a_str_len = -1,
		StringAlignment a_x_align = StringAlignmentCenter, StringAlignment a_y_align = StringAlignmentCenter);
	void DrawText(GpFont *ap_font, RectF *ap_rect, const wchar_t *ap_str, int a_str_len = -1,
		StringAlignment a_x_align = StringAlignmentCenter, StringAlignment a_y_align = StringAlignmentCenter);
	int DrawTextEx(RectF *ap_rect, StringAlignment a_x_align, StringAlignment a_y_align, const wchar_t *ap_format, ...); // 형식화된 출력지원

	// 지정한 문자열이 출력되었을 때 폭과 높이를 계산하는 함수
	SIZE GetTextExtent(const wchar_t *ap_str, int a_len);
	SizeF GetTextExtentF(const wchar_t *ap_str, int a_len);


	// 전달된 이미지 객체를 출력하는 함수 (다른 이미지 객체를 현 이미지 객체에 출력하는 함수)
	void Draw(GpImage *ap_image, int a_x, int a_y);
	void Draw(GpImage *ap_image, float a_x, float a_y);
	// 전달된 이미지 객체를 출력하는 함수 (다른 이미지 객체를 현 이미지 객체에 출력하는 함수)
	void Draw(GpImage *ap_image, int a_x, int a_y, int a_cx, int a_cy);
	void Draw(GpImage *ap_image, float a_x, float a_y, float a_cx, float a_cy);
	// 전달된 이미지 객체를 출력하는 함수 (이미지 속성을 적용하는 함수)
	void Draw(GpImage *ap_image, int a_x, int a_y, GpImageAttributes *ap_attr);
	void Draw(GpImage *ap_image, float a_x, float a_y, GpImageAttributes *ap_attr);
	// 전달된 이미지 객체의 시작 좌표와 크기를 지정해서 출력하는 함수 (이미지 속성을 적용하는 함수)
	void Draw(GpImage *ap_image, int a_x, int a_y, int a_cx, int a_cy, GpImageAttributes *ap_attr);
	void Draw(GpImage *ap_image, float a_x, float a_y, float a_cx, float a_cy, GpImageAttributes *ap_attr);
	// 전달된 이미지 객체의 전체 내용을 출력하는 함수 (이미지 속성을 적용하는 함수)
	void DrawFullImage(GpImage *ap_image, int a_x, int a_y, GpImageAttributes *ap_attr);
	void DrawFullImage(GpImage *ap_image, float a_x, float a_y, GpImageAttributes *ap_attr);
	// 전달된 이미지 객체 크기로 내용을 출력하는 함수 (이미지 속성을 적용하는 함수)
	void DrawRealImage(GpImage *ap_image, int a_x, int a_y, GpImageAttributes *ap_attr);
	void DrawRealImage(GpImage *ap_image, float a_x, float a_y, GpImageAttributes *ap_attr);

	// 전달된 DC에 현재 이미지를 출력하는 함수
	void Draw(HDC ah_dc, int a_x = 0, int a_y = 0);
	void DrawF(HDC ah_dc, float a_x = 0.0f, float a_y = 0.0f);
	// 전달된 DC에 현재 이미지를 출력하는 함수
	void Draw(HDC ah_dc, int a_x, int a_y, int a_cx, int a_cy);
	void DrawF(HDC ah_dc, float a_x, float a_y, float a_cx, float a_cy);


	// 새로운 색상을 지정하지 않고 기존 펜으로 지정한 Path를 출력하는 함수 (테두리만 그림)
	void DrawUserPath(GpPath *ap_path);
	// 지정한 펜 색상으로 Path를 출력하는 함수 (테두리만 그림)
	void DrawUserPath(GpPath *ap_path, ARGB a_color);
	// 지정한 펜으로 Path를 출력하는 함수 (테두리만 그림)
	void DrawUserPath(GpPath *ap_path, GpPen *ap_pen);

	// 새로운 색상을 지정하지 않고 기존 브러시로 지정한 Path를 출력하는 함수 (내부 채우기)
	void FillUserPath(GpPath *ap_path);
	// 지정한 브러시 색상으로 Path를 출력하는 함수 (테두리만 그림)
	void FillUserPath(GpPath *ap_path, ARGB a_color);
	// 지정한 브러시로 Path를 출력하는 함수 (테두리만 그림)
	void FillUserPath(GpPath *ap_path, GpBrush *ap_brush);

	// 지정된 점을 연결하는 곡선을 그리는 함수
	void DrawCurve(GpPoint *ap_pos_list, int a_count, float a_tension);
	void DrawCurve(GpPointF *ap_pos_list, int a_count, float a_tension);
	// 지정된 점을 연결하는 베지어 선을 그리는 함수
	void DrawBezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
	void DrawBezier(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

	// 다각형을 그리는 함수
	void Polygon(GpPoint *ap_pos_list, int a_count);
	void Polygon(GpPointF *ap_pos_list, int a_count);

	// 새로운 색상을 지정하지 않고 기존 펜으로 다각형을 그리는 함수 (테두리만 그림)
	void DrawPolygon(GpPoint *ap_pos_list, int a_count);
	void DrawPolygon(GpPointF *ap_pos_list, int a_count);
	// 지정된 색상으로 다각형을 그리는 함수 (테두리만 그림)
	void DrawPolygon(GpPoint *ap_pos_list, int a_count, ARGB a_color);
	void DrawPolygon(GpPointF *ap_pos_list, int a_count, ARGB a_color);
	// 지정된 펜으로 다각형을 그리는 함수 (테두리만 그림)
	void DrawPolygon(GpPoint *ap_pos_list, int a_count, GpPen *ap_pen);
	void DrawPolygon(GpPointF *ap_pos_list, int a_count, GpPen *ap_pen);

	// 새로운 색상을 지정하지 않고 기존 브러시로 다각형을 그리는 함수 (채우기만 수행)
	void FillPolygon(GpPoint *ap_pos_list, int a_count);
	void FillPolygon(GpPointF *ap_pos_list, int a_count);
	// 지정된 색상으로 다각형을 그리는 함수 (채우기만 수행)
	void FillPolygon(GpPoint *ap_pos_list, int a_count, ARGB a_color);
	void FillPolygon(GpPointF *ap_pos_list, int a_count, ARGB a_color);
	// 지정된 Brush으로 다각형을 그리는 함수 (채우기만 수행)
	void FillPolygon(GpPoint *ap_pos_list, int a_count, GpBrush *ap_brush);
	void FillPolygon(GpPointF *ap_pos_list, int a_count, GpBrush *ap_brush);

	GpPath *MakeRoundRectPath(int a_x, int a_y, int a_cx, int a_cy, int a_rcx, int a_rcy); // RoundRect를 Path로 구성해주는 함수
	GpPath *MakeRoundRectPath(float a_x, float a_y, float a_cx, float a_cy, float a_rcx, float a_rcy);
	GpPath *MakeUpStyleRoundRectPath(int a_x, int a_y, int a_cx, int a_cy, int a_rcx, int a_rcy); // RoundRect를 Path로 구성해주는 함수
	GpPath *MakeUpStyleRoundRectPath(float a_x, float a_y, float a_cx, float a_cy, float a_rcx, float a_rcy);
	void DeletePathData(GpPath *ap_path); // Path 데이터를 제거하는 함수
	GpPath *OpenPath(); // Path구성을 시작하는 함수
	void ClosePath(GpPath *ap_path); // Path구성을 마무리하는 함수

	void SetBrushColor(ARGB a_color); // 브러시 객체의 색상을 변경하는 함수
	void SetPenColor(ARGB a_color); // 펜 객체의 색상을 변경하는 함수
	void SetPenColor(DashStyle a_style, REAL a_width, ARGB a_color); // 펜 객체의 속성을 변경하는 함수 (스타일, 굵기, 색상)
	void SetTextColor(ARGB a_color); // 글꼴의 색상을 변경하는 함수

	void ChangeFont(const wchar_t *ap_font_name, REAL a_size = 15, INT a_style = FontStyleRegular); // 글꼴 정보를 변경하는 함수
	GpFontFamily *CreateFontFamily(const wchar_t *ap_font_name); // 글꼴 집합을 생성하는 함수	
	GpFont *CreateFont(GpFontFamily *ap_family, REAL a_size, INT a_style); // 글꼴을 생성하는 함수
	void DeleteFontFamily(GpFontFamily *ap_family); // 지정한 글꼴 집합을 제거하는 함수
	void DeleteFont(GpFont *ap_font); // 지정한 글꼴을 제거하는 함수
	void DeleteFontInfo(GpFontFamily *ap_family, GpFont *ap_font); // 지정한 글꼴 정보를 제거하는 함수

	void SetSmoothingMode(UINT8 a_smooth = 1); // 안티엘리어스 모드로 설정할 것인지 여부를 지정하는 함수

	GpPen *GetStockPen(); // 내부적으로 생성되어 있는 펜 객체의 주소를 얻는 함수
	GpBrush *GetStockBrush(); // 내부적으로 생성되어 있는 브러시 객체의 주소를 얻는 함수
	void ChangePenDashCap(DashCap a_cap_type, GpPen *ap_pen = NULL); // Dash 형식의 펜인 경우 Dash의 양쪽 끝모양을 변경하는 함수 (ap_pen이 NULL이면 기본 펜에 적용 됨)	
	void ChangePenCap(LineCap a_cap_type, GpPen *ap_pen = NULL); // 펜의 양쪽 끝모양을 변경하는 함수 (ap_pen이 NULL이면 기본 펜에 적용 됨)
	void ChangePenLineJoin(LineJoin a_join_type, GpPen *ap_pen = NULL); // 선과 선이 만났을 때의 모양을 변경하는 함수 (ap_pen이 NULL이면 기본 펜에 적용 됨)

	GpImage *LoadImage(const wchar_t *ap_path); // 지정된 이미지 파일을 읽어서 이미지 객체를 만드는 함수
	void DestroyImage(GpImage *ap_image); // 지정된 이미지 객체를 제거하는 함수

	// 지정한 이미지를 사용해서 a_width * a_height 크기의 섬네일 이미지를 생성하는 함수
	GpImage *MakeImageForThumbnail(GpImage *ap_src_image, int a_width, int a_height);

	// (a_x, a_y)위치를 논리적 기준점(0, 0)으로 지정하는 함수
	void SetViewportOrg(REAL a_x, REAL a_y, MatrixOrder a_order_type = MatrixOrderAppend);
	// 이후 사용된 출력 좌표를 지정한 메트릭스 연산을 반영하도록 하는 함수
	void ApplyMatrix(GpMatrix *ap_matrix);

	GpMatrix *CreateMatrix(); // 새로운 메트릭스를 생성하는 함수
	void DeleteMatrix(GpMatrix *ap_matrix);  // 메트릭스를 제거하는 함수

	GpGraphics *GetGraphics(); // GDI+ 출력용 객체의 주소를 얻는 함수
	GpImage *GetStockImage(); // GDI+ 출력에 사용하는 이미지 객체의 주소를 얻는 함수

	// 이미지 Encoder의 CLSID 값을 얻는 함수
	UINT GetEncoderClsid(const wchar_t *ap_format, CLSID *ap_clsid);

	int GetWidth();
	int GetHeight();
};

#endif