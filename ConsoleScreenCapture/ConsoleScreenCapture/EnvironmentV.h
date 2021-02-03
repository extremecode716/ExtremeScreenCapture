#pragma once
#include <iostream>
#include "define.h"
#include "FilePath.h"
#include "Monitor.h"

/* ȯ�� ���� class */
class CEnvironmentV
{
private:
	CFilePath* m_pFilePath;
	CMonitor* m_pMonitor;
	int m_iCaptureMonitorIndex; // ĸ���� ����� index!

public:
	// ��ũ�� Ű ����
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

