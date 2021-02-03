#include "ScreenCapture.h"
#include <iostream>
#include <fstream>

#define BIT_COUNT 24;
using namespace std;

CScreenCapture::CScreenCapture()
{
}

CScreenCapture::~CScreenCapture()
{
}

BOOL CScreenCapture::SaveHBITMAPToFile( HBITMAP hBitmap, LPCWSTR lpszFileName )
{
	ofstream stream;
	stream.open( lpszFileName, ios::binary );
	if ( !stream.is_open() )
	{
		cout << "File open error!" << endl;
		return FALSE;
	}
	BITMAP bitmap;
	GetObject( hBitmap, sizeof( bitmap ), (LPSTR)&bitmap );
	BITMAPINFOHEADER bi;
	bi.biSize = sizeof( BITMAPINFOHEADER );
	bi.biWidth = bitmap.bmWidth;
	bi.biHeight = bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = BIT_COUNT;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;
	int PalSize = (bi.biBitCount == 24 ? 0 : 1 << bi.biBitCount) * sizeof( RGBQUAD );
	int Size = bi.biSize + PalSize + bi.biSizeImage;
	BITMAPFILEHEADER fh;
	fh.bfOffBits = sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + PalSize;
	fh.bfReserved1 = 0;
	fh.bfReserved2 = 0;
	fh.bfSize = Size + sizeof( BITMAPFILEHEADER );
	fh.bfType = 0x4d42;
	stream.write( (LPSTR)&fh, sizeof( BITMAPFILEHEADER ) );
	HDC hDC = GetDC( NULL );
	BITMAPINFO* header = (BITMAPINFO*)malloc( bi.biSize + PalSize );
	header->bmiHeader = bi;
	GetDIBits( hDC, hBitmap, 0, bitmap.bmHeight, NULL, header, DIB_RGB_COLORS );
	bi = header->bmiHeader;
	if ( bi.biSizeImage == 0 )
	{
		bi.biSizeImage = ((bitmap.bmWidth * bi.biBitCount + 31) & ~31) / 8 * bitmap.bmHeight;
	}
	Size = bi.biSize + PalSize + bi.biSizeImage;
	void* body = malloc( header->bmiHeader.biSizeImage );
	GetDIBits( hDC, hBitmap, 0, header->bmiHeader.biHeight, body, header, DIB_RGB_COLORS );
	stream.write( (LPSTR)&header->bmiHeader, sizeof( BITMAPINFOHEADER ) );
	stream.write( (LPSTR)body, Size );
	ReleaseDC( NULL, hDC );
	stream.close();
	delete header;
	delete body;

	return 0;
}

void CScreenCapture::screenshot( MONITORINFOEXW* _pMonitorInfo, LPCWSTR filepath )
{
	int width = (labs( _pMonitorInfo->rcMonitor.right ) > labs( _pMonitorInfo->rcMonitor.left )) ? (labs( _pMonitorInfo->rcMonitor.right ) - labs( _pMonitorInfo->rcMonitor.left )) : (labs( _pMonitorInfo->rcMonitor.left) - labs( _pMonitorInfo->rcMonitor.right) );
	int height = (labs( _pMonitorInfo->rcMonitor.bottom ) > labs( _pMonitorInfo->rcMonitor.top )) ? (labs( _pMonitorInfo->rcMonitor.bottom ) - labs( _pMonitorInfo->rcMonitor.top )) : (labs( _pMonitorInfo->rcMonitor.top ) - labs( _pMonitorInfo->rcMonitor.bottom ));
	HDC hScreen = CreateDC( NULL, _pMonitorInfo->szDevice, NULL, NULL );
	HDC hDC = CreateCompatibleDC( hScreen );
	HBITMAP hBitmap = CreateCompatibleBitmap( hScreen, width, height );
	HGDIOBJ old_obj = SelectObject( hDC, hBitmap );
	BOOL bRet = BitBlt( hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY );
	SaveHBITMAPToFile( hBitmap, filepath );
	SelectObject( hDC, old_obj );
	DeleteDC( hDC );
	ReleaseDC( NULL, hScreen );
	DeleteObject( hBitmap );
}
