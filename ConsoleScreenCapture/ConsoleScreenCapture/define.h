#pragma once

#define SZ_MAX_SIZE 255 * 4
#define SZ_DEFAULT_SIZE 255
#define SZ_EXT_SIZE 16

#define TMP_SCALE_FACTOR

// 캡처 제한 모드 설정 
// CAPTURE_MODE 0: 매시간 단축키별 한번만 스크린샷 가능 / 1: 스크린샷 제한 해제
#define CAPTURE_MODE 0
#if CAPTURE_MODE == 1
#define UNLOCK_TIME_LIMIT
#else
#endif