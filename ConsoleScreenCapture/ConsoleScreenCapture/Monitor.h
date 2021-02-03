#pragma once
#include <windows.h>

typedef struct tagMonitorData {
	int iCurrent;
	MONITORINFOEXW* pInfo;
}MonitorData;

class CMonitor
{
private:
	int	m_iMonitors;
	MonitorData m_MonitorData;

public:
	bool Run();
	bool Close();

	MonitorData GetMonitorData();
	int GetMonitorCount();

public:
	static CMonitor* GetInst() {
		static CMonitor g_monitor;
		return &g_monitor;
	}
private:
	CMonitor();
	~CMonitor();
};

static BOOL EnumProc_CMonitor( HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData ) {
	MonitorData* data = (MonitorData*)dwData;
	data->pInfo[data->iCurrent].cbSize = sizeof( MONITORINFOEXW );
	return GetMonitorInfoW( hMonitor, &(data->pInfo[data->iCurrent++]) );
}

static BOOL GetAllMonitorInfo( MonitorData* data )
{
	return EnumDisplayMonitors( NULL, NULL, (MONITORENUMPROC)&EnumProc_CMonitor, (LPARAM)(data) );
}