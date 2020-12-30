#include "fileTrans.h"
#include "cstring"
#include "iostream"
#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib,"crypt32.lib")
using namespace std;

std::string readFile(const std::string& f_path) {
	std::ifstream is(f_path.c_str(), std::ifstream::in | ios::binary);
	is.seekg(0, is.end);
	DWORD flength = is.tellg()*2;
	is.seekg(0, is.beg);
	char* buffer = (char *)malloc(flength);
	is.read(buffer, flength);
	char* buf = (char*)malloc(flength);
	CryptBinaryToStringA((BYTE *)buffer,flength, CRYPT_STRING_BASE64,buf,&flength);
	string file(buf, flength);
	return file;
}

