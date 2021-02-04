#pragma once
#include <windows.h>

class CScreenCapture
{
public:
	BOOL SaveHBITMAPToFile( HBITMAP hBitmap, LPCWSTR lpszFileName );
	void screenshot( MONITORINFOEXW* _pMonitorInfo, double _dScaleX, double _dScaleY, LPCWSTR filepath );

public:
	static CScreenCapture* GetInst() {
		static CScreenCapture g_screenCapture;
		return &g_screenCapture;
	}

private:
	CScreenCapture();
	~CScreenCapture();
};

