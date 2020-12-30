//
// Created by Dengzhanhong on 2020/9/5.
//

#ifndef AUTO_STARTUP_REG_H
#define AUTO_STARTUP_REG_H

#include <Windows.h>
#define REG_OPEN_KEY_ERROR -1
#define REG_SET_KEY_VALUE_ERROR -2
#define SUCCESS 0

/**
 * 需要当前用户权限
 *
 * @param lpszFileName 需要写入注册表自启动的文件路径
 * @param lpszValueName 注册表表项中的值
 * @return 返回上define的三种int值
 */
int Reg_CurrentUser(char* lpszFileName, char* lpszValueName);

/**
 * 需要管理员权限
 *
 * @param lpszFileName 需要写入注册表自启动的文件路径
 * @param lpszValueName 注册表表项中的值
 * @return 返回上define的三种int值
 */
int Reg_LocalMachine(char* lpszFileName, char* lpszValueName);

#endif //AUTO_STARTUP_REG_H
