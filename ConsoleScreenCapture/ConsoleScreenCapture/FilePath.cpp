#include "FilePath.h"
#include <iostream>
using namespace std;

bool CFilePath::SetCurrentEXEDir()
{
	GetCurrentDirectory( SZ_MAX_SIZE, m_szCurrentEXEDir );
	int iLen = wcslen( m_szCurrentEXEDir );
	if ( m_szCurrentEXEDir[iLen - 1] != L'\\' )
	{
		wcscat_s( m_szCurrentEXEDir, SZ_MAX_SIZE, L"\\" );
	}

	return true;
}

bool CFilePath::SetEnvironmentDir()
{
	wcscpy_s( m_szEnvironmentDir, SZ_MAX_SIZE, m_szCurrentEXEDir );
	wcscat_s( m_szEnvironmentDir, SZ_MAX_SIZE, L"ExtremeScreenCapture_env.txt" );

	return true;
}

bool CFilePath::SetSoundDir()
{
	wcscpy_s( m_szSound1Dir, SZ_MAX_SIZE, m_szCurrentEXEDir );
	wcscat_s( m_szSound1Dir, SZ_MAX_SIZE, L"Capture1.wav" );

	wcscpy_s( m_szSound2Dir, SZ_MAX_SIZE, m_szCurrentEXEDir );
	wcscat_s( m_szSound2Dir, SZ_MAX_SIZE, L"Capture2.wav" );

	return true;
}

bool CFilePath::init()
{
	SetCurrentEXEDir();
	SetEnvironmentDir();
	SetBaseFileName( L"ExtremeScreenCapture_" );
	SetDefaultFileExt( L"jpg" );
	SetFileExt( GetDefaultFileExt());
	SetSoundDir();

	return true;
}

bool CFilePath::SetSaveImgFullDir( int _iMecroNum, const wchar_t * _szTime )
{
	swprintf( m_szSaveImgFullDir, L"%s%s_%s_%d.%s", GetRootDir(), GetBaseFileName(), _szTime, _iMecroNum, GetFileExt());

	return true;
}

bool CFilePath::SetRootDir( const wchar_t* _szRootDir )
{
	int iErr = 0;
	int iLen = wcslen( _szRootDir );
	wmemcpy( m_szRootDir, _szRootDir, iLen );
	m_szRootDir[iLen] = L'\0';
	if ( m_szRootDir[iLen - 1] != L'\\' )
	{
		wcscat_s( m_szRootDir, SZ_MAX_SIZE, L"\\" );
	}

	iErr = _waccess_s( m_szRootDir, 0 );
	if ( iErr == 0 ) {
		return true;
	}
	else {
		if ( ::CreateDirectoryW( m_szRootDir, NULL ) ) {
			return true;
		}

		wcout << "폴더에 접근 할 수 없습니다. ExtremeScreenCapture_env.txt의 SaveFolderDir 경로를 다시 설정해 주세요." << endl;
		return false;
	}
	return true;
}

bool CFilePath::SetRelativeDir( const wchar_t* _szRelativeDir )
{
	int iErr = 0;
	int iLen = wcslen( _szRelativeDir );
	wmemcpy( m_szRelativeDir, _szRelativeDir, iLen );
	m_szRelativeDir[iLen] = L'\0';
	if ( m_szRelativeDir[iLen - 1] != L'\\' )
	{
		wcscat_s( m_szRelativeDir, SZ_DEFAULT_SIZE, L"\\" );
	}

	wcscat_s( m_szRootDir, SZ_MAX_SIZE, m_szRelativeDir );

	iErr = _waccess_s( m_szRootDir, 0 );
	if ( iErr == 0 ) {
		return true;
	}
	else {
		if ( ::CreateDirectoryW( m_szRootDir, NULL ) ) {
			return true;
		}

		wcout << "폴더에 접근 할 수 없습니다. ExtremeScreenCapture_env.txt의 SaveFolderDir 경로를 다시 설정해 주세요." << endl;
		return false;
	}
	return true;
}

bool CFilePath::SetBaseFileName( const wchar_t* _szFileName )
{
	int iLen = wcslen( _szFileName );
	wmemcpy( m_szBaseFileName, _szFileName, iLen );
	m_szBaseFileName[iLen] = L'\0';
	return true;
}

bool CFilePath::SetNumberToAddToBaseFileName( const wchar_t * _szNumberToAddToBaseFileName )
{
	int iLen = wcslen( m_szNumberToAddToBaseFileName );
	wmemcpy( m_szNumberToAddToBaseFileName, _szNumberToAddToBaseFileName, iLen );
	m_szNumberToAddToBaseFileName[iLen] = L'\0';
	return true;
}

bool CFilePath::SetTimeToAddToBaseFileName( const wchar_t * _szTimeToAddToBaseFileName )
{
	int iLen = wcslen( _szTimeToAddToBaseFileName );
	wmemcpy( m_szTimeToAddToBaseFileName, _szTimeToAddToBaseFileName, iLen );
	m_szTimeToAddToBaseFileName[iLen] = L'\0';
	return true;
}

bool CFilePath::SetFileExt( const wchar_t* _szFileExt )
{
	int iLen = wcslen( _szFileExt );
	wmemcpy( m_szFileExt, _szFileExt, iLen );
	m_szFileExt[iLen] = L'\0';
	return true;
}

bool CFilePath::SetDefaultFileExt( const wchar_t * _szFileExt )
{
	int iLen = wcslen( _szFileExt );
	wmemcpy( m_szDefaultFileExt, _szFileExt, iLen );
	m_szDefaultFileExt[iLen] = L'\0';
	return true;
}

CFilePath::CFilePath()
	:
	m_szSaveImgFullDir{},
	m_szCurrentEXEDir{},
	m_szEnvironmentDir{},
	m_szRootDir{},
	m_szRelativeDir{},
	m_szBaseFileName{},
	m_szNumberToAddToBaseFileName{},
	m_szTimeToAddToBaseFileName{},
	m_szFileExt{},
	m_szDefaultFileExt{},
	m_szSound1Dir{},
	m_szSound2Dir{}
{
	init();
}

CFilePath::~CFilePath()
{
}
