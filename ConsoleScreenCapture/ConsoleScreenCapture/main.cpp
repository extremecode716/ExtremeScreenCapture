#include <windows.h>
#include <iostream>
#include <crtdbg.h>
using namespace std;

#include "EnvironmentV.h"
#include "MessageLoop.h"

int main() {
	std::wcout.imbue( std::locale( "korean" ) );
	wcout << L"�ۼ���: ExtremeCode" << endl;
	wcout << L"�̸���: extremecode716@gmail.com" << endl;
	wcout << L"�Կ� ����Ű(�⺻): LCTRL + 1 / LCTRL + 2" << endl;
	wcout << L"ȯ�� ���� ����: ExtremeScreenCapture_env.txt " << endl;
	wcout << L" ��ȯ�� ���� ������ �����Ͻð� ����Ͻñ� �ٶ��ϴ�.�� " << endl;
	wcout << L"-----------------------------------------------------" << endl;

	CEnvironmentV::GetInst();
	CEnvironmentV::GetInst()->SetConsolePosition( 50, 50, 50, 50 );
	CEnvironmentV::GetInst()->ReadFile();

	mainMessageLoop();

	_CrtDumpMemoryLeaks();
	return 0;
}