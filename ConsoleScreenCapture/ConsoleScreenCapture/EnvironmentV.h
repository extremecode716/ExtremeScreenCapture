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

#ifdef TMP_SCALE_FACTOR
public:
	double m_dTmpScaleFactor;	// ���� ����� ScaleFactor�� ����� �������� ���ؼ�, �ӽ÷� File Read ������� ����...(dpi,scalefactor...)
	void SetTmpScaleFactor( double _dScale ) { m_dTmpScaleFactor = _dScale; } // Tmp
	double GetTmpScaleFactor() { return m_dTmpScaleFactor; } // Tmp
#else
#endif

public:
	// ��ũ�� Ű ����
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

