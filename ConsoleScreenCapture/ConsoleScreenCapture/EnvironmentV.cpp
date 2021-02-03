#include "EnvironmentV.h"

void CEnvironmentV::SetConsolePosition( int _x, int _y, int _cx, int _cy )
{
	HWND hConsoleWindow = GetConsoleWindow();
	SetWindowPos( hConsoleWindow, 0, _x, _y, _cx, _cy, SWP_NOSIZE | SWP_NOZORDER );
	ShowWindow( hConsoleWindow, SW_SHOWMINIMIZED );
}

bool CEnvironmentV::ReadFile()
{
	FILE* pFile = NULL;
	// 환경 설정 파일 read
	_wfopen_s( &pFile, m_pFilePath->GetEnvironmentDir(), L"r" );

	if ( NULL == pFile ) {
		_wfopen_s( &pFile, m_pFilePath->GetEnvironmentDir(), L"a" );
		fputws( L"MultiMonitorIndex=0", pFile );
		fputws( L"\nSaveFolderDir=C:\\Zoom302\\", pFile );
		fputws( L"\nBaseFileName=302room", pFile );
		fputws( L"\nFileExt=jpg", pFile );
		//fputws( L"\nHookKey:Ctrl+1,Ctrl+2", pFile );
		fclose( pFile );

		m_iCaptureMonitorIndex = 0;
		m_pFilePath->SetRootDir(L"C:\\Zoom302\\");
		m_pFilePath->SetBaseFileName( L"302room" );

		return true;
	}

	wchar_t szBuffer[SZ_DEFAULT_SIZE];
	fgetws( szBuffer, sizeof( szBuffer ), pFile );
	wchar_t* pValue = wcstok( szBuffer, L"=" );
	pValue = wcstok( NULL, L"\n" );
	m_iCaptureMonitorIndex = _wtoi( pValue );

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
	m_pMonitor(CMonitor::GetInst()),
	m_iCaptureMonitorIndex(0),
	m_ulMecroKey1{162, 49}, // Ctrl + 1
	m_ulMecroKey2{162, 50}  // Ctrl + 2
{
	m_pMonitor->Run();
}

CEnvironmentV::~CEnvironmentV()
{
	CMonitor::GetInst()->Close();

}
