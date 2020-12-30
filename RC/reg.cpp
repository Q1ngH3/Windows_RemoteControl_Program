//
// Created by Dengzhanhong on 2020/9/5.
//
#include "reg.h"
#include "showError.h"

int Reg_CurrentUser(char* lpszFileName, char* lpszValueName)
{
    HKEY hKey;
    // ��ע����
    if (ERROR_SUCCESS != ::RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey))
    {
        ShowError("RegOpenKeyEx");
        return REG_OPEN_KEY_ERROR;
    }
    // �޸�ע���ֵ��ʵ�ֿ�������
    if (ERROR_SUCCESS != ::RegSetValueEx(hKey, lpszValueName, 0, REG_SZ, (BYTE*)lpszFileName, (1 + ::lstrlen(lpszFileName))))
    {
        ::RegCloseKey(hKey);
        ShowError("RegSetValueEx");
        return REG_SET_KEY_VALUE_ERROR;
    }
    // �ر�ע����
    ::RegCloseKey(hKey);

    return SUCCESS;
}


int Reg_LocalMachine(char* lpszFileName, char* lpszValueName)
{
    HKEY hKey;
    // ��ע����
    if (ERROR_SUCCESS != ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey))
    {
        ShowError("RegOpenKeyEx");
        return REG_OPEN_KEY_ERROR;
    }
    // �޸�ע���ֵ��ʵ�ֿ�������
    if (ERROR_SUCCESS != ::RegSetValueEx(hKey, lpszValueName, 0, REG_SZ, (BYTE*)lpszFileName, (1 + ::lstrlen(lpszFileName))))
    {
        ::RegCloseKey(hKey);
        ShowError("RegSetValueEx");
        return REG_SET_KEY_VALUE_ERROR;
    }
    // �ر�ע����
    ::RegCloseKey(hKey);

    return SUCCESS;
}
