//
// Created by Dengzhanhong on 2020/9/7.
//

#ifndef DOCUMENTLOOKUP_DOCUMENTLOOKUP_H
#define DOCUMENTLOOKUP_DOCUMENTLOOKUP_H

#include <windows.h>
#include <stdlib.h>
#include <list>
#include <iostream>
#include <io.h>



using namespace std;

typedef list<_finddata64i32_t> DOC_LIST;

/**
 *
 * @param base ��Ҫ������Ŀ¼
 * @param docList ���ڽ���Ŀ¼���ļ���Ϣ��list
 */
void travelDoc(char* base, DOC_LIST* docList);

/**
 *  ��ȡ�û����д���·��
 * @param baseList ���ڽ��մ���·����Ϣ��stringList
 */
void baseDriver(list<string>* baseList);
#endif //DOCUMENTLOOKUP_DOCUMENTLOOKUP_H
