//
// Created by Dengzhanhong on 2020/9/6.
//
#include "screenShot.h"





void screenshot(string file) {
	ULONG_PTR gdiplustoken;
	GdiplusStartupInput gdistartupinput;
	GdiplusStartupOutput gdistartupoutput;
	gdistartupinput.SuppressBackgroundThread = true;
	GdiplusStartup(&gdiplustoken, &gdistartupinput, &gdistartupoutput);
	HDC dc = GetDC(GetDesktopWindow());
	HDC dc2 = CreateCompatibleDC(dc);
	RECT rc0kno;
	GetWindowRect(GetDesktopWindow(), &rc0kno);
	HWND hWnd = GetDesktopWindow();
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFOEX miex;
	miex.cbSize = sizeof(miex);
	GetMonitorInfo(hMonitor, &miex);
	int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;
	EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
	int cxPhysical = dm.dmPelsWidth;
	double dpi = ((double)cxPhysical / (double)cxLogical);
	int w = GetSystemMetrics(SM_CXSCREEN) * dpi;
	int h = GetSystemMetrics(SM_CYSCREEN) * dpi;
	HBITMAP hbitmap = CreateCompatibleBitmap(dc, w, h);
	HBITMAP holdbitmap = (HBITMAP)SelectObject(dc2, hbitmap);
	BitBlt(dc2, 0, 0, w, h, dc, 0, 0, SRCCOPY);
	Bitmap* bm = new Bitmap(hbitmap, NULL);

	UINT num;
	UINT size;

	ImageCodecInfo* imagecodecinfo;
	GetImageEncodersSize(&num, &size);

	imagecodecinfo = (ImageCodecInfo*)(malloc(size));
	GetImageEncoders(num, size, imagecodecinfo);

	CLSID clsidEncoder;

	for (int i = 0; i < num; i++)
	{
		if (wcscmp(imagecodecinfo[i].MimeType, L"image/jpeg") == 0)
			clsidEncoder = imagecodecinfo[i].Clsid;//get jpeg codec id
	}
	free(imagecodecinfo);
	wstring ws;
	ws.assign(file.begin(), file.end());
	bm->Save(ws.c_str(), &clsidEncoder);
	SelectObject(dc2, holdbitmap);
	DeleteObject(dc2);
	DeleteObject(hbitmap);
	ReleaseDC(GetDesktopWindow(), dc);
	GdiplusShutdown(gdiplustoken);
}