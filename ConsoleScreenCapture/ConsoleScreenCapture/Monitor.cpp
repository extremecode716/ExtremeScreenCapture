#include "Monitor.h"
#include "define.h"

MonitorData CMonitor::GetMonitorData()
{
	return m_MonitorData;
}

int CMonitor::GetMonitorCount()
{
	return m_iMonitors;
}

void CMonitor::DeleteMonitorData()
{
	if ( m_MonitorData.pInfo != nullptr )
	{
		free( m_MonitorData.pInfo );
		m_MonitorData.pInfo = nullptr;
	}
	if ( m_MonitorData.pDpiAndScale != nullptr )
	{
		free( m_MonitorData.pDpiAndScale );
		m_MonitorData.pDpiAndScale = nullptr;
	}
	if ( m_MonitorData.pDSF != nullptr )
	{
		free( m_MonitorData.pDSF );
		m_MonitorData.pDSF = nullptr;
	}
	if ( m_MonitorData.pHMonitor != nullptr )
	{
		free( m_MonitorData.pHMonitor );
		m_MonitorData.pHMonitor = nullptr;
	}
}

void CMonitor::SetDPIAndScale( UINT _iXDpi, UINT _iYDpi, DpiAndScale * _pDpiAndScale )
{
	_pDpiAndScale->iXDpi = _iXDpi;
	_pDpiAndScale->iYDpi = _iYDpi;

	_pDpiAndScale->dXScale = 100 / 96.0 * _iXDpi;
	_pDpiAndScale->dYScale = 100 / 96.0 * _iYDpi;
	switch ( _iXDpi )
	{
	case 96:
		_pDpiAndScale->dXScale = 1.0;
		break;
	case 120:
		_pDpiAndScale->dXScale = 1.25;
		break;
	case 144:
		_pDpiAndScale->dXScale = 1.5;
		break;
	case 168:
		_pDpiAndScale->dXScale = 1.75;
		break;
	case 192:
		_pDpiAndScale->dXScale = 2;
		break;
	default:
		break;
	}

	switch ( _iYDpi )
	{
	case 96:
		_pDpiAndScale->dYScale = 1.0;
		break;
	case 120:
		_pDpiAndScale->dYScale = 1.25;
		break;
	case 144:
		_pDpiAndScale->dYScale = 1.5;
		break;
	case 168:
		_pDpiAndScale->dYScale = 1.75;
		break;
	case 192:
		_pDpiAndScale->dYScale = 2;
		break;
	default:
		break;
	}
}

bool CMonitor::Close()
{
	DeleteMonitorData();
	return true;
}

bool CMonitor::Setting()
{
	m_iMonitors = GetSystemMetrics( SM_CMONITORS );
	m_MonitorData.iCurrent = 0;
	m_MonitorData.pInfo = (MONITORINFOEXW*)calloc( m_iMonitors, sizeof( MONITORINFOEXW ) );
	m_MonitorData.pDpiAndScale = (DpiAndScale*)calloc( m_iMonitors, sizeof( DpiAndScale ) );
	m_MonitorData.pDSF = (DEVICE_SCALE_FACTOR*)calloc( m_iMonitors, sizeof( DEVICE_SCALE_FACTOR ) );
	m_MonitorData.pHMonitor = (HMONITOR*)calloc( m_iMonitors, sizeof( HMONITOR ) );
	
	if ( !GetAllMonitorInfo( &m_MonitorData ) ) return false;

#ifdef TMP_SCALE_FACTOR

#else
	for ( int i = 0; i < m_iMonitors; ++i )
	{
		UINT _iXDpi = 0;
		UINT _iYDpi = 0;
		GetDpiForMonitor( m_MonitorData.pHMonitor[i], MDT_EFFECTIVE_DPI, (UINT*)&(_iXDpi), (UINT*)&(_iYDpi) );
		CMonitor::SetDPIAndScale( _iXDpi, _iYDpi, &m_MonitorData.pDpiAndScale[m_MonitorData.iCurrent] );
		GetScaleFactorForMonitor( m_MonitorData.pHMonitor[i], &m_MonitorData.pDSF[i] );
	}
#endif
	return true;
}

CMonitor::CMonitor()
	:m_iMonitors( 0 )
{
}

CMonitor::~CMonitor()
{
	DeleteMonitorData();
}
