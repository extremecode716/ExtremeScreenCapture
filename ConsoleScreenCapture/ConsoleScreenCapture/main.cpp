#include <windows.h>
#include <iostream>
#include <crtdbg.h>
using namespace std;

#include "EnvironmentV.h"
#include "MessageLoop.h"

int main() {
	wcout << "�ۼ���: �赿��" << endl;
	wcout << "�̸���: extremecode716@gmail.com" << endl;
	wcout << "�Կ� ����Ű: ctrl + 1 / ctrl + 2" << endl;
	wcout << "ȯ�� ���� ����: ExtremeScreenCapture_env.txt " << endl;
	wcout << "-------------------------------------" << endl;

	CEnvironmentV::GetInst();
	CEnvironmentV::GetInst()->SetConsolePosition( 50, 50, 50, 50 );
	CEnvironmentV::GetInst()->ReadFile();

	mainMessageLoop();

	_CrtDumpMemoryLeaks();
	return 0;
}