#include <windows.h>
#include <iostream>
#include <crtdbg.h>
using namespace std;

#include "EnvironmentV.h"
#include "MessageLoop.h"

int main() {
	wcout << "작성자: 김동일" << endl;
	wcout << "이메일: extremecode716@gmail.com" << endl;
	wcout << "촬영 단축키(기본): LCTRL + 1 / LCTRL + 2" << endl;
	wcout << "환경 설정 파일: ExtremeScreenCapture_env.txt " << endl;
	wcout << " ※환경 설정 파일을 수정하시고 사용하시기 바랍니다.※ " << endl;
	wcout << "-----------------------------------------------------" << endl;

	CEnvironmentV::GetInst();
	CEnvironmentV::GetInst()->SetConsolePosition( 50, 50, 50, 50 );
	CEnvironmentV::GetInst()->ReadFile();

	mainMessageLoop();

	_CrtDumpMemoryLeaks();
	return 0;
}