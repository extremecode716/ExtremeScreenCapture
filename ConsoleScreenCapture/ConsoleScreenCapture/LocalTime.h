#pragma once
#include <time.h>
#include "define.h"

typedef struct tLocalTime
{
	int tm_sec;   // seconds after the minute - [0, 60] including leap second
	int tm_min;   // minutes after the hour - [0, 59]
	int tm_hour;  // hours since midnight - [0, 23]
	int tm_mday;  // day of the month - [1, 31]
	int tm_mon;   // months since January - [0, 11]
	int tm_year;  // years since 1900
	int tm_wday;  // days since Sunday - [0, 6]
	int tm_yday;  // days since January 1 - [0, 365]
	int tm_isdst; // daylight savings time flag
}LocalTime;

class CLocalTime
{
private:
	LocalTime *m_pLocalTime;
	wchar_t m_szMonAndDay_Hour[SZ_DEFAULT_SIZE];

public:
	LocalTime* GetLocalTime();
	wchar_t* GetMonAndDay_Hour();

	static CLocalTime* GetInst() {
		static CLocalTime g_localTime;
		return &g_localTime;
	}
private:
	CLocalTime();
	~CLocalTime();
};

