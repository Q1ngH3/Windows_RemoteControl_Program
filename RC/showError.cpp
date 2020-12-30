//
// Created by Dengzhanhong on 2020/9/5.
//

#include "showError.h"
void ShowError(char* lpszText)
{
    char szErr[MAX_PATH] = { 0 };
    ::wsprintf(szErr, "%s Error!\nError Code Is:%d\n", lpszText, ::GetLastError());
#ifdef _DEBUG
    ::MessageBox(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
#endif
}