#include "EnvironmentV.h"

void CEnvironmentV::SetConsolePosition( int _x, int _y, int _cx, int _cy )
{
	HWND hConsoleWindow = GetConsoleWindow();
	SetWindowPos( hConsoleWindow, 0, _x, _y, _cx, _cy, SWP_NOSIZE | SWP_NOZORDER );
	ShowWindow( hConsoleWindow, SW_SHOWMINIMIZED );
}

bool CEnvironmentV::SetMacroKey( wchar_t * _szMacroKey1, wchar_t * _szMacroKey2 )
{
	if ( wcsstr( _szMacroKey1, L"+" ) == NULL || wcsstr( _szMacroKey2, L"+" ) == NULL ) {
		wcout << "Error : ExtremeScreenCapture_env.txt 의 Macro2Key 설정에서 오류가 났습니다.";
		wcout << "Macro2Key의 값은 2개의 키를 설정해야 하며, \",\"로 분리되어야 하며, 키 조합은 + 조합으로 이루어져야 합니다.(+:1번만 사용)" << endl;
	}
	else
	{
		// _szMacroKey1
		wchar_t* pValue = NULL;
		pValue = wcstok( _szMacroKey1, L"+" );
		m_ulMacroKey1[0] = GetWCHARConvertToASCII( pValue );
		pValue = wcstok( NULL, L"\0" );
		m_ulMacroKey1[1] = GetWCHARConvertToASCII( pValue );

		// _szMacroKey2
		pValue = NULL;
		pValue = wcstok( _szMacroKey2, L"+" );
		m_ulMacroKey2[0] = GetWCHARConvertToASCII( pValue );
		pValue = wcstok( NULL, L"\0" );
		m_ulMacroKey2[1] = GetWCHARConvertToASCII( pValue );
	}

	return true;
}

DWORD CEnvironmentV::GetWCHARConvertToASCII( const wchar_t * _szValue )
{
	int iLen = wcslen( _szValue );

	if ( iLen == 1 )
	{
		return (DWORD)_szValue[0];
	}
	else {

		if ( 0 == _wcsicmp( _szValue, L"CTRL" )  ) {
			return VK_LCONTROL;
		}
		else if ( 0 == _wcsicmp( _szValue, L"LCTRL" ) ) {
			return VK_LCONTROL;
		}
		else if ( 0 == _wcsicmp( _szValue, L"RCTRL" ) ) {
			return VK_RCONTROL;
		}
		else if ( 0 == _wcsicmp( _szValue, L"SHIFT" ) ) {
			return VK_LSHIFT;
		}
		else if ( 0 == wcsicmp( _szValue, L"LSHIFT" ) ) {
			return VK_LSHIFT;
		}
		else if ( 0 == wcsicmp( _szValue, L"RSHIFT" ) ) {
			return VK_RSHIFT;
		}
		else if ( 0 == wcsicmp( _szValue, L"ALT" ) ) {
			return VK_LMENU;
		}
		else if ( 0 == wcsicmp( _szValue, L"LALT" ) ) {
			return VK_LMENU;
		}
		else if ( 0 == wcsicmp( _szValue, L"RALT" ) ) {
			return VK_RMENU;
		}
		else if ( 0 == wcsicmp( _szValue, L"CAPITAL" ) ) {
			return VK_CAPITAL;
		}
		else if ( 0 == wcsicmp( _szValue, L"TAB" ) ) {
			return VK_TAB;
		}
		else if ( 0 == wcsicmp( _szValue, L"OEM_3" ) ) {
			return VK_OEM_3;
		}
		else if ( 0 == wcsicmp( _szValue, L"OEM_5" ) ) {
			return VK_OEM_5;
		}
		else if ( 0 == wcsicmp( _szValue, L"F1" ) ) {
			return VK_F1;
		}
		else if ( 0 == wcsicmp( _szValue, L"F2" ) ) {
			return VK_F2;
		}
		else if ( 0 == wcsicmp( _szValue, L"F3" ) ) {
			return VK_F3;
		}
		else if ( 0 == wcsicmp( _szValue, L"F4" ) ) {
			return VK_F4;
		}
		else if ( 0 == wcsicmp( _szValue, L"F5" ) ) {
			return VK_F5;
		}
		else if ( 0 == wcsicmp( _szValue, L"F6" ) ) {
			return VK_F6;
		}
		else if ( 0 == wcsicmp( _szValue, L"F7" ) ) {
			return VK_F7;
		}
		else if ( 0 == wcsicmp( _szValue, L"F8" ) ) {
			return VK_F8;
		}
		else if ( 0 == wcsicmp( _szValue, L"F9" ) ) {
			return VK_F9;
		}
		else if ( 0 == wcsicmp( _szValue, L"F10" ) ) {
			return VK_F10;
		}
		else if ( 0 == wcsicmp( _szValue, L"F11" ) ) {
			return VK_F11;
		}
		else if ( 0 == wcsicmp( _szValue, L"F12" ) ) {
			return VK_F12;
		}
		else if ( 0 == wcsicmp( _szValue, L"ESC" ) ) {
			return VK_ESCAPE;
		}
		else if ( 0 == wcsicmp( _szValue, L"PAGEUP" ) ) {
			return VK_PRIOR;
		}
		else if ( 0 == wcsicmp( _szValue, L"PAGEDOWN" ) ) {
			return VK_NEXT;
		}
		else if ( 0 == wcsicmp( _szValue, L"END" ) ) {
			return VK_END;
		}
		else if ( 0 == wcsicmp( _szValue, L"HOME" ) ) {
			return VK_HOME;
		}
		else if ( 0 == wcsicmp( _szValue, L"NUMPAD0" ) ) {
			return VK_NUMPAD0;
		}
		else if ( 0 == wcsicmp( _szValue, L"NUMPAD1" ) ) {
			return VK_NUMPAD1;
		}
		else if ( 0 == wcsicmp( _szValue, L"NUMPAD2" ) ) {
			return VK_NUMPAD2;
		}
		else if ( 0 == wcsicmp( _szValue, L"NUMPAD3" ) ) {
			return VK_NUMPAD3;
		}
		else if ( 0 == wcsicmp( _szValue, L"NUMPAD4" ) ) {
			return VK_NUMPAD4;
		}
		else if ( 0 == wcsicmp( _szValue, L"NUMPAD5" ) ) {
			return VK_NUMPAD5;
		}
		else if ( 0 == wcsicmp( _szValue, L"NUMPAD6" ) ) {
			return VK_NUMPAD6;
		}
		else if ( 0 == wcsicmp( _szValue, L"NUMPAD7" ) ) {
			return VK_NUMPAD7;
		}
		else if ( 0 == wcsicmp( _szValue, L"NUMPAD8" ) ) {
			return VK_NUMPAD8;
		}
		else if ( 0 == wcsicmp( _szValue, L"NUMPAD9" ) ) {
			return VK_NUMPAD9;
		}
		else if ( 0 == wcsicmp( _szValue, L"MULTIPY" ) ) {
			return VK_MULTIPLY;
		}
		else if ( 0 == wcsicmp( _szValue, L"ADD" ) ) {
			return VK_ADD;
		}
		else if ( 0 == wcsicmp( _szValue, L"SUBTRACT" ) ) {
			return VK_SUBTRACT;
		}
		else if ( 0 == wcsicmp( _szValue, L"DECIMAL" ) ) {
			return VK_DECIMAL;
		}
		else if ( 0 == wcsicmp( _szValue, L"DIVIDE" ) ) {
			return VK_DIVIDE;
		}
	}

	return VK_LCONTROL;
}

bool CEnvironmentV::ReadFile()
{
	FILE* pFile = NULL;
	// 환경 설정 파일 read
	_wfopen_s( &pFile, m_pFilePath->GetEnvironmentDir(), L"r,ccs=UTF-8" );

	if ( NULL == pFile ) {
		_wfopen_s( &pFile, m_pFilePath->GetEnvironmentDir(), L"a,ccs=UTF-8" );
		fputws( L"MultiMonitorIndex=0", pFile );
		fputws( L"\nSaveFolderDir=C:\\Zoom302\\", pFile );
		fputws( L"\nBaseFileName=302room", pFile );
		fputws( L"\nFileExt=jpg", pFile ); // GetDefaultFileExt()
		fputws( L"\nMacro2Key=LCTRL+1,LCTRL+2", pFile );
		fclose( pFile );

		m_iCaptureMonitorIndex = 0;
		m_pFilePath->SetRootDir( L"C:\\Zoom302\\" );
		m_pFilePath->SetBaseFileName( L"302room" );

		return true;
	}

	wchar_t szBuffer[SZ_DEFAULT_SIZE];
	fgetws( szBuffer, sizeof( szBuffer ), pFile );
	wchar_t* pValue = wcstok( szBuffer, L"=" );
	pValue = wcstok( NULL, L"\n" );
	m_iCaptureMonitorIndex = _wtoi( pValue );
	if ( m_iCaptureMonitorIndex >= m_pMonitor->GetMonitorCount() ) {
		wcout << "monitor index over error -> reset index: 0" << endl;
		m_iCaptureMonitorIndex = 0;
	}

	fgetws( szBuffer, sizeof( szBuffer ), pFile );
	pValue = wcstok( szBuffer, L"=" );
	pValue = wcstok( NULL, L"\n" );
	m_pFilePath->SetRootDir( pValue );

	fgetws( szBuffer, sizeof( szBuffer ), pFile );
	pValue = wcstok( szBuffer, L"=" );
	pValue = wcstok( NULL, L"\n" );
	m_pFilePath->SetBaseFileName( pValue );

	fgetws( szBuffer, sizeof( szBuffer ), pFile );
	pValue = wcstok( szBuffer, L"=" );
	pValue = wcstok( NULL, L"\n" );
	m_pFilePath->SetFileExt( pValue );

	fgetws( szBuffer, sizeof( szBuffer ), pFile );
	pValue = wcstok( szBuffer, L"=" );
	pValue = wcstok( NULL, L"," );
	wchar_t* pKey1Value = pValue;
	pValue = wcstok( NULL, L"\n" );
	wchar_t* pKey2Value = pValue;
	SetMacroKey( pKey1Value, pKey2Value );

	fclose( pFile );

	return true;
}

bool CEnvironmentV::SaveFile()
{
	return true;
}

CEnvironmentV::CEnvironmentV()
	:
	m_pFilePath( CFilePath::GetInst() ),
	m_pMonitor( CMonitor::GetInst() ),
	m_iCaptureMonitorIndex( 0 ),
	m_ulMacroKey1{ 162, 49 }, // Ctrl + 1
	m_ulMacroKey2{ 162, 50 }  // Ctrl + 2
{
	m_pMonitor->Run();
}

CEnvironmentV::~CEnvironmentV()
{
	CMonitor::GetInst()->Close();

}
