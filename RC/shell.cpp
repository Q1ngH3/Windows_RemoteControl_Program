#include<string>
#include<iostream>
using namespace std;

string getCMD(char* cmd) {
    FILE* file;
    char ptr[1024] = { 0 };
    char tmp[1024] = { 0 };
    strcat_s(ptr, cmd);
    string result = "";
    if ((file = _popen(ptr, "r")) != NULL)
    {
        while (fgets(tmp, 1024, file) != NULL) {
            result = result + tmp;
        }
        _pclose(file);
    }
    return result;
}

