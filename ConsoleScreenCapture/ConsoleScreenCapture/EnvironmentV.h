#pragma once
#include <iostream>
#include "define.h"
#include "FilePath.h"
#include "Monitor.h"

/* 환경 설정 class */
class CEnvironmentV
{
private:
	CFilePath* m_pFilePath;
	CMonitor* m_pMonitor;
	int m_iCaptureMonitorIndex; // 캡쳐할 모니터 index!

public:
	// 매크로 키 설정
	DWORD m_ulMacroKey1[2];
	DWORD m_ulMacroKey2[2];
public:
	void SetConsolePosition( int _x, int _y, int _cx, int _cy );
	CFilePath* GetFilePath() { return m_pFilePath; }
	CMonitor* GetMonitor() { return m_pMonitor; }
	int GetCaptureMonitorIndex() { return m_iCaptureMonitorIndex; }
	bool SetMacroKey( wchar_t* _szMacroKey1, wchar_t* _szMacroKey2 );
	DWORD GetWCHARConvertToASCII( const wchar_t* _szValue );

	bool ReadFile();
	bool SaveFile();

public:
	static CEnvironmentV* GetInst() {
		static CEnvironmentV g_environment;
		return &g_environment;
	}
private:
	CEnvironmentV();
	~CEnvironmentV();
};

