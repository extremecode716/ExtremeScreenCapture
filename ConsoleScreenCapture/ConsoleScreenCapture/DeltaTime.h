#pragma once
#include <Windows.h>
class CDeltaTime
{
private:
	LARGE_INTEGER	m_llFrequency;
	LARGE_INTEGER	m_llCurCnt;
	LARGE_INTEGER	m_llOldCnt;
	float			m_fDeltaTime;

public:
	void Init();
	bool Update();
	float DeltaTime() { return m_fDeltaTime; }

	static CDeltaTime* GetInst() {
		static CDeltaTime g_deltaTime;
		return &g_deltaTime;
	}
private:
	CDeltaTime();
	~CDeltaTime();
};

