#pragma once

#define SZ_MAX_SIZE 255 * 4
#define SZ_DEFAULT_SIZE 255
#define SZ_EXT_SIZE 16

#define TMP_SCALE_FACTOR

// ĸó ���� ��� ���� 
// CAPTURE_MODE 0: �Žð� ����Ű�� �ѹ��� ��ũ���� ���� / 1: ��ũ���� ���� ����
#define CAPTURE_MODE 0
#if CAPTURE_MODE == 1
#define UNLOCK_TIME_LIMIT
#else
#endif