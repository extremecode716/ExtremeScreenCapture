#pragma once
#include <Windows.h>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

#include "define.h"
#include "EnvironmentV.h"
#include "ScreenCapture.h"
#include "LocalTime.h"
#include "DeltaTime.h"

#define MACRO_MAGIC_NUM1 256
#define MACRO_MAGIC_NUM2 257

float fResetAccTime = 0.f;
float fResetMaxAccTime = 1.f;

float fPressTermAccTime = 0.f;
float fPressTermMaxAccTime = 0.3f;
bool bPressTermTime = false;

bool bMecroPressed1 = false;
bool bMecroPressed2 = false;
HHOOK hHook;
// 키 처리도 클래스로 전체적으로 관리해야하는데 귀찮으니~pass
DWORD pressMacroKey[2] = { MACRO_MAGIC_NUM1, MACRO_MAGIC_NUM2 }; //magic num
void resetPressMacroKey() {
	pressMacroKey[0] = MACRO_MAGIC_NUM1;
	pressMacroKey[1] = MACRO_MAGIC_NUM2;
}

bool IsPressMacroKey() {
	if ( pressMacroKey[0] != MACRO_MAGIC_NUM1 ) {
		return true;
	}
	if ( pressMacroKey[1] != MACRO_MAGIC_NUM2 ) {
		return true;
	}
	return false;
}

LRESULT CALLBACK KeyboardProc( int nCode, WPARAM wParam, LPARAM lParam ) {
	PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT)lParam;
	if ( wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN ) {
		if ( nCode >= 0 ) {
			/*cout << pKey->vkCode << " ";*/
			bool bMecroPressed1 = false;
			bool bMecroPressed2 = false;

			if ( pKey->vkCode == CEnvironmentV::GetInst()->m_ulMacroKey1[0] ) {
				pressMacroKey[0] = CEnvironmentV::GetInst()->m_ulMacroKey1[0];
			}
			else if ( pKey->vkCode == CEnvironmentV::GetInst()->m_ulMacroKey1[1] ) {
				pressMacroKey[1] = CEnvironmentV::GetInst()->m_ulMacroKey1[1];
			}
			else if ( pKey->vkCode == CEnvironmentV::GetInst()->m_ulMacroKey2[0] )
			{
				pressMacroKey[0] = CEnvironmentV::GetInst()->m_ulMacroKey2[0];
			}
			else if ( pKey->vkCode == CEnvironmentV::GetInst()->m_ulMacroKey2[1] )
			{
				pressMacroKey[1] = CEnvironmentV::GetInst()->m_ulMacroKey2[1];
			}

			if ( pressMacroKey[0] == CEnvironmentV::GetInst()->m_ulMacroKey1[0] && pressMacroKey[1] == CEnvironmentV::GetInst()->m_ulMacroKey1[1] ) {
				bMecroPressed1 = true;
			}
			else if ( pressMacroKey[0] == CEnvironmentV::GetInst()->m_ulMacroKey2[0] && pressMacroKey[1] == CEnvironmentV::GetInst()->m_ulMacroKey2[1] )
			{
				bMecroPressed2 = true;
			}

			if ( bMecroPressed1 && !bPressTermTime )
			{
#ifdef UNLOCK_TIME_LIMIT
				CEnvironmentV::GetInst()->GetFilePath()->SetSaveImgFullDir( 1, CLocalTime::GetInst()->GetDate() );
#else
				CEnvironmentV::GetInst()->GetFilePath()->SetSaveImgFullDir( 1, CLocalTime::GetInst()->GetMonAndDay_Hour() );
#endif
				
#ifdef TMP_SCALE_FACTOR
				CScreenCapture::GetInst()->screenshot( &CEnvironmentV::GetInst()->GetMonitor()->GetMonitorData().pInfo[CEnvironmentV::GetInst()->GetCaptureMonitorIndex()],
					CEnvironmentV::GetInst()->GetTmpScaleFactor(),
					CEnvironmentV::GetInst()->GetTmpScaleFactor(),
					CEnvironmentV::GetInst()->GetFilePath()->GetSaveImgFullDir() );
#else		
				CScreenCapture::GetInst()->screenshot( &CEnvironmentV::GetInst()->GetMonitor()->GetMonitorData().pInfo[CEnvironmentV::GetInst()->GetCaptureMonitorIndex()],
					CEnvironmentV::GetInst()->GetMonitor()->GetMonitorData().pDpiAndScale[CEnvironmentV::GetInst()->GetCaptureMonitorIndex()].dXScale,
					CEnvironmentV::GetInst()->GetMonitor()->GetMonitorData().pDpiAndScale[CEnvironmentV::GetInst()->GetCaptureMonitorIndex()].dYScale,
					CEnvironmentV::GetInst()->GetFilePath()->GetSaveImgFullDir() );
#endif
				wcout << L"사진 촬영1-경로: " << CEnvironmentV::GetInst()->GetFilePath()->GetSaveImgFullDir() << endl;
				bPressTermTime = true;

				PlaySound( CEnvironmentV::GetInst()->GetFilePath()->GetSound1Dir(), 0, SND_FILENAME | SND_ASYNC ); //일반 재생
			}
			else if ( bMecroPressed2 && !bPressTermTime ) {

#ifdef UNLOCK_TIME_LIMIT
				CEnvironmentV::GetInst()->GetFilePath()->SetSaveImgFullDir( 2, CLocalTime::GetInst()->GetDate() );
#else
				CEnvironmentV::GetInst()->GetFilePath()->SetSaveImgFullDir( 2, CLocalTime::GetInst()->GetMonAndDay_Hour() );
#endif
#ifdef TMP_SCALE_FACTOR
				CScreenCapture::GetInst()->screenshot( &CEnvironmentV::GetInst()->GetMonitor()->GetMonitorData().pInfo[CEnvironmentV::GetInst()->GetCaptureMonitorIndex()],
					CEnvironmentV::GetInst()->GetTmpScaleFactor(),
					CEnvironmentV::GetInst()->GetTmpScaleFactor(),
					CEnvironmentV::GetInst()->GetFilePath()->GetSaveImgFullDir() );
#else		
				CScreenCapture::GetInst()->screenshot( &CEnvironmentV::GetInst()->GetMonitor()->GetMonitorData().pInfo[CEnvironmentV::GetInst()->GetCaptureMonitorIndex()],
					CEnvironmentV::GetInst()->GetMonitor()->GetMonitorData().pDpiAndScale[CEnvironmentV::GetInst()->GetCaptureMonitorIndex()].dXScale,
					CEnvironmentV::GetInst()->GetMonitor()->GetMonitorData().pDpiAndScale[CEnvironmentV::GetInst()->GetCaptureMonitorIndex()].dYScale,
					CEnvironmentV::GetInst()->GetFilePath()->GetSaveImgFullDir() );
#endif
				wcout << L"사진 촬영2-경로: " << CEnvironmentV::GetInst()->GetFilePath()->GetSaveImgFullDir() << endl;
				bPressTermTime = true;

				PlaySound( CEnvironmentV::GetInst()->GetFilePath()->GetSound2Dir(), 0, SND_FILENAME | SND_ASYNC ); //일반 재생
			}
		}
	}
	else if ( wParam == WM_KEYUP || wParam == WM_SYSKEYUP )
	{
		if ( nCode >= 0 ) {
			if ( pKey->vkCode == CEnvironmentV::GetInst()->m_ulMacroKey1[0] ) {
				pressMacroKey[0] = MACRO_MAGIC_NUM1;
			}
			else if ( pKey->vkCode == CEnvironmentV::GetInst()->m_ulMacroKey1[1] ) {
				pressMacroKey[1] = MACRO_MAGIC_NUM2;
			}
			else if ( pKey->vkCode == CEnvironmentV::GetInst()->m_ulMacroKey2[0] )
			{
				pressMacroKey[0] = MACRO_MAGIC_NUM1;
			}
			else if ( pKey->vkCode == CEnvironmentV::GetInst()->m_ulMacroKey2[1] )
			{
				pressMacroKey[1] = MACRO_MAGIC_NUM2;
			}
		}
	}

	CallNextHookEx( hHook, nCode, wParam, lParam );
	return 0;
}

void SetHook() {
	HMODULE hInstance = GetModuleHandle( NULL );
	hHook = SetWindowsHookEx( WH_KEYBOARD_LL, KeyboardProc, hInstance, NULL );
}

void UnHook() {
	UnhookWindowsHookEx( hHook );
}

BOOL ConsoleCtrlHandler( DWORD fdwCtrlType )
{
	switch ( fdwCtrlType )
	{
	case CTRL_CLOSE_EVENT:
	case CTRL_SHUTDOWN_EVENT:
	default:
		CMonitor::GetInst()->DeleteMonitorData();
		UnHook();
		return FALSE;
	}
}

int mainMessageLoop() {
	SetConsoleCtrlHandler( (PHANDLER_ROUTINE)ConsoleCtrlHandler, TRUE );
	SetHook();
	MSG msg;
	CDeltaTime::GetInst()->Init();
	while ( true ) {
		if ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT )
				break;
		}
		else
		{
			CDeltaTime::GetInst()->Update();

			/*	if ( IsPressMacroKey() ) {
				fResetAccTime += CDeltaTime::GetInst()->DeltaTime();
				if ( fResetAccTime > fResetMaxAccTime ) {
					resetPressMacroKey();
					fResetAccTime = 0.f;
				}
			}*/

			if ( bPressTermTime ) {
				fPressTermAccTime += CDeltaTime::GetInst()->DeltaTime();
				if ( fPressTermAccTime > fPressTermMaxAccTime )
				{
					bPressTermTime = false;
					fPressTermAccTime = 0.f;
				}
			}
			Sleep( 20 );
		}
	}
	UnHook();
	return true;
}
