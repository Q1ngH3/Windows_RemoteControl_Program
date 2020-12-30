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
 * ��Ҫ��ǰ�û�Ȩ��
 *
 * @param lpszFileName ��Ҫд��ע������������ļ�·��
 * @param lpszValueName ע�������е�ֵ
 * @return ������define������intֵ
 */
int Reg_CurrentUser(char* lpszFileName, char* lpszValueName);

/**
 * ��Ҫ����ԱȨ��
 *
 * @param lpszFileName ��Ҫд��ע������������ļ�·��
 * @param lpszValueName ע�������е�ֵ
 * @return ������define������intֵ
 */
int Reg_LocalMachine(char* lpszFileName, char* lpszValueName);

#endif //AUTO_STARTUP_REG_H
