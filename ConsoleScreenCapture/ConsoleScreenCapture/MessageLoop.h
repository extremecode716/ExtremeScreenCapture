#pragma once
#include <Windows.h>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

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

			if ( bMecroPressed1 && !bPressTermTime)
			{
				CEnvironmentV::GetInst()->GetFilePath()->SetSaveImgFullDir( 1, CLocalTime::GetInst()->GetMonAndDay_Hour() );
				CScreenCapture::GetInst()->screenshot( &CEnvironmentV::GetInst()->GetMonitor()->GetMonitorData().pInfo[CEnvironmentV::GetInst()->GetCaptureMonitorIndex()], CEnvironmentV::GetInst()->GetFilePath()->GetSaveImgFullDir() );
				wcout << L"사진 촬영1-경로: "<< CEnvironmentV::GetInst()->GetFilePath()->GetSaveImgFullDir() << endl;
				bPressTermTime = true; 

				PlaySound( CEnvironmentV::GetInst()->GetFilePath()->GetSound1Dir(), 0, SND_FILENAME | SND_ASYNC ); //일반 재생
			}
			else if ( bMecroPressed2 && !bPressTermTime ) {
				CEnvironmentV::GetInst()->GetFilePath()->SetSaveImgFullDir( 2, CLocalTime::GetInst()->GetMonAndDay_Hour() );
				CScreenCapture::GetInst()->screenshot( &CEnvironmentV::GetInst()->GetMonitor()->GetMonitorData().pInfo[CEnvironmentV::GetInst()->GetCaptureMonitorIndex()], CEnvironmentV::GetInst()->GetFilePath()->GetSaveImgFullDir() );
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

int mainMessageLoop() {
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

			Sleep( 10 );
		}
	}
	UnHook();
	return true;
}
