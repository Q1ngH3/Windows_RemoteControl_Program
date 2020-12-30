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
 * @param lpszSrcFilePath 需要自启动的源文件路径
 * @param lpszDestFileName 复制到自启动文件夹后的文件名
 * @return 成功返回true 失败返回false
 */
BOOL autoStartupDir(char* lpszSrcFilePath, char* lpszDestFileName);

#endif //AUTO_STARTUP_AUTOSTARTUPDIR_H
