#pragma once
#include <Windows.h>
#include <string>
#include "define.h"

using namespace std;

class CFilePath
{
private:
	wchar_t m_szSaveImgFullDir[SZ_MAX_SIZE];
	wchar_t m_szCurrentEXEDir[SZ_MAX_SIZE]; // exe���� ���� ���
	wchar_t m_szEnvironmentDir[SZ_MAX_SIZE]; // ȯ�漳��.txt
	wchar_t m_szRootDir[SZ_MAX_SIZE]; // ��Ʈ ���
	wchar_t m_szRelativeDir[SZ_DEFAULT_SIZE];  // ��Ʈ���\\��� ���
	wchar_t m_szBaseFileName[SZ_DEFAULT_SIZE];	// ���� �⺻ �̸�
	wchar_t m_szNumberToAddToBaseFileName[SZ_DEFAULT_SIZE]; // �⺻ ���� �̸��� �߰��� ����
	wchar_t m_szTimeToAddToBaseFileName[SZ_DEFAULT_SIZE]; // �⺻ ���� �̸��� �߰��� �ð�
	wchar_t m_szFileExt[SZ_EXT_SIZE];		// ���� Ȯ����

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

