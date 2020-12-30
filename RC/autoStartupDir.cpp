//
// Created by Dengzhanhong on 2020/9/5.
//

#include "autoStartupDir.h"
#pragma comment(lib, "shell32.lib")

BOOL autoStartupDir(char* lpszSrcFilePath, char* lpszDestFileName)
{
    BOOL bRet = FALSE;
    char szStartupPath[MAX_PATH] = { 0 };
    char szDestFilePath[MAX_PATH] = { 0 };
    // ��ȡ ��������Ŀ¼ ·��
    bRet = ::SHGetSpecialFolderPath(NULL, szStartupPath, CSIDL_STARTUP, TRUE);
    printf("szStartupPath=%s\n", szStartupPath);
    if (FALSE == bRet)
    {
        return FALSE;
    }
    // ���쿽���� Ŀ���ļ�·��
    ::wsprintf(szDestFilePath, "%s\\%s", szStartupPath, lpszDestFileName);
    // �����ļ�����������Ŀ¼��
    bRet = ::CopyFile(lpszSrcFilePath, szDestFilePath, FALSE);
    if (FALSE == bRet)
    {
        return FALSE;
    }
    return TRUE;
}