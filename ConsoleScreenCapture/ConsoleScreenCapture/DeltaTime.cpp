#include "DeltaTime.h"

void CDeltaTime::Init()
{
	QueryPerformanceFrequency( &m_llFrequency );
	QueryPerformanceCounter( &m_llCurCnt );
	m_llOldCnt = m_llCurCnt;
}

bool CDeltaTime::Update()
{
	QueryPerformanceCounter( &m_llCurCnt );
	m_fDeltaTime = (m_llCurCnt.QuadPart - m_llOldCnt.QuadPart) / (float)m_llFrequency.QuadPart;
	m_llOldCnt = m_llCurCnt;

	return true;
}

CDeltaTime::CDeltaTime()
	: 
	m_llFrequency{ 0 }
	, m_llCurCnt{ 0 }
	, m_llOldCnt{ 0 }
	, m_fDeltaTime( 0.f )
{
}

CDeltaTime::~CDeltaTime()
{
}
