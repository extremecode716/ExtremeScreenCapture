#pragma once
#include <Windows.h>
#include <string>
#include "define.h"

using namespace std;

class CFilePath
{
private:
	wchar_t m_szSaveImgFullDir[SZ_MAX_SIZE];
	wchar_t m_szCurrentEXEDir[SZ_MAX_SIZE]; // exe파일 현재 경로
	wchar_t m_szEnvironmentDir[SZ_MAX_SIZE]; // 환경설정.txt
	wchar_t m_szRootDir[SZ_MAX_SIZE]; // 루트 경로
	wchar_t m_szRelativeDir[SZ_DEFAULT_SIZE];  // 루트경로\\상대 경로
	wchar_t m_szBaseFileName[SZ_DEFAULT_SIZE];	// 파일 기본 이름
	wchar_t m_szNumberToAddToBaseFileName[SZ_DEFAULT_SIZE]; // 기본 파일 이름에 추가할 숫자
	wchar_t m_szTimeToAddToBaseFileName[SZ_DEFAULT_SIZE]; // 기본 파일 이름에 추가할 시간
	wchar_t m_szFileExt[SZ_EXT_SIZE];		// 파일 확장자

	wchar_t m_szSound1Dir[SZ_MAX_SIZE];
	wchar_t m_szSound2Dir[SZ_MAX_SIZE];

private:
	bool SetCurrentEXEDir();
	bool SetEnvironmentDir();
	bool SetSoundDir();

public:
	bool init();
	
	bool SetSaveImgFullDir( int _iCaptureNum, const wchar_t* _szTime );
	bool SetRootDir( const wchar_t* _szRootDir );
	bool SetRelativeDir( const wchar_t* _szRelativeDir );
	bool SetBaseFileName( const wchar_t* _szFileName );
	bool SetNumberToAddToBaseFileName( const wchar_t* _szNumberToAddToBaseFileName );
	bool SetTimeToAddToBaseFileName( const wchar_t* _szTimeToAddToBaseFileName );
	bool SetFileExt( const wchar_t* _szFileExt );

	wchar_t* GetSaveImgFullDir() { return m_szSaveImgFullDir; }
	wchar_t* GetRootDir() { return m_szRootDir; }
	wchar_t* GetCurrentEXEDir() { return m_szCurrentEXEDir; }
	wchar_t* GetEnvironmentDir() { return m_szEnvironmentDir; }
	wchar_t* GetBaseFileName() { return m_szBaseFileName; }
	wchar_t* GetFileExt() { return m_szFileExt; }

	wchar_t* GetSound1Dir() { return m_szSound1Dir; }
	wchar_t* GetSound2Dir() { return m_szSound2Dir; }

public:
	static CFilePath* GetInst() {
		static CFilePath g_filePath;
		return &g_filePath;
	}

private:
	CFilePath();
	~CFilePath();
};

