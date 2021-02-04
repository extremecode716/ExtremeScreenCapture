#pragma once
#include <windows.h>
#include <ShellScalingApi.h>
#pragma comment(lib, "Shcore.lib")

typedef struct tagDpiAndScale {
	UINT iXDpi;
	UINT iYDpi;
	double dXScale;
	double dYScale;

	tagDpiAndScale() :
		iXDpi( 0 ), iYDpi( 0 ), dXScale( 0.0 ), dYScale( 0.0 ) 
	{}
}DpiAndScale;

typedef struct tagMonitorData {
	int iCurrent;
	MONITORINFOEXW* pInfo;
	DpiAndScale* pDpiAndScale;
	DEVICE_SCALE_FACTOR* pDSF;
	HMONITOR* pHMonitor;

	tagMonitorData():
	iCurrent(0), pInfo(nullptr), pDpiAndScale(nullptr), pDSF(nullptr), pHMonitor(nullptr)
	{}
}MonitorData;

class CMonitor
{
private:
	int	m_iMonitors;
	MonitorData m_MonitorData;

public:
	bool Setting();
	bool Close();

	MonitorData GetMonitorData();
	int GetMonitorCount();
	void DeleteMonitorData();

	static void SetDPIAndScale( UINT _iXDpi, UINT _iYDpi, DpiAndScale* _pDpiAndScale);

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
	BOOL iResult = -1;
	MonitorData* data = (MonitorData*)dwData;
	data->pInfo[data->iCurrent].cbSize = sizeof( MONITORINFOEXW );
	iResult = GetMonitorInfoW( hMonitor, &(data->pInfo[data->iCurrent]) );
	data->pHMonitor[data->iCurrent] = hMonitor;
	++data->iCurrent;
	return iResult;
}

static BOOL GetAllMonitorInfo( MonitorData* data )
{
	return EnumDisplayMonitors( NULL, NULL, (MONITORENUMPROC)&EnumProc_CMonitor, (LPARAM)(data) );
}
