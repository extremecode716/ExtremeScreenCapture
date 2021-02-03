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
	DWORD m_ulMecroKey1[2];
	DWORD m_ulMecroKey2[2];
public:
	void SetConsolePosition( int _x, int _y, int _cx, int _cy );
	CFilePath* GetFilePath() { return m_pFilePath; }
	CMonitor* GetMonitor() { return m_pMonitor; }
	int GetCaptureMonitorIndex() { return m_iCaptureMonitorIndex; }

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

