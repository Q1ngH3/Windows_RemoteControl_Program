//
// Created by Dengzhanhong on 2020/9/5.
//

#ifndef AUTO_STARTUP_AUTOSTARTUPDIR_H
#define AUTO_STARTUP_AUTOSTARTUPDIR_H
#include <iostream>
#include <Windows.h>
#include <Shlobj.h>
#include <tchar.h>

/**
 *
 * @param lpszSrcFilePath ��Ҫ��������Դ�ļ�·��
 * @param lpszDestFileName ���Ƶ��������ļ��к���ļ���
 * @return �ɹ�����true ʧ�ܷ���false
 */
BOOL autoStartupDir(char* lpszSrcFilePath, char* lpszDestFileName);

#endif //AUTO_STARTUP_AUTOSTARTUPDIR_H
