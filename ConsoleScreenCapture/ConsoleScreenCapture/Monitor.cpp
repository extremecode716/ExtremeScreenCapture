#include "Monitor.h"

MonitorData CMonitor::GetMonitorData()
{
	return m_MonitorData;
}

int CMonitor::GetMonitorCount()
{
	return m_iMonitors;
}

bool CMonitor::Close()
{
	if ( m_MonitorData.pInfo == nullptr )
		return true;
	free( m_MonitorData.pInfo );
	m_MonitorData.pInfo = nullptr;
	return true;
}

bool CMonitor::Run()
{
	m_iMonitors = GetSystemMetrics( SM_CMONITORS );
	m_MonitorData.iCurrent = 0;
	m_MonitorData.pInfo = (MONITORINFOEXW*)calloc( m_iMonitors, sizeof( MONITORINFOEXW ) );

	if ( !GetAllMonitorInfo( &m_MonitorData ) ) return false;

	return true;
}

CMonitor::CMonitor()
	:m_iMonitors(0)
{
}

CMonitor::~CMonitor()
{
	if ( m_MonitorData.pInfo != nullptr )
	{
		free( m_MonitorData.pInfo );
	}
}
