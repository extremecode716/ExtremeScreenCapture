#include "LocalTime.h"
#include <iostream>

LocalTime * CLocalTime::GetLocalTime()
{
	time_t curTime = time( NULL );
	m_pLocalTime = (LocalTime*)localtime( &curTime );
	m_pLocalTime->tm_year += 1900;
	++m_pLocalTime->tm_mon;

	return m_pLocalTime;
}

wchar_t * CLocalTime::GetMonAndDay_Hour()
{
	GetLocalTime();
	swprintf( m_szMonAndDay_Hour, L"%02d%02d_%02d", m_pLocalTime->tm_mon, m_pLocalTime->tm_mday, m_pLocalTime->tm_hour);
	
	return m_szMonAndDay_Hour;
}

CLocalTime::CLocalTime()
	:
	m_pLocalTime( NULL )
	, m_szMonAndDay_Hour{}
{
}

CLocalTime::~CLocalTime()

{
}
