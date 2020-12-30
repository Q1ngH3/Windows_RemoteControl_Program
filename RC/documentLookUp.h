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
 * @param base 需要遍历的目录
 * @param docList 用于接收目录中文件信息的list
 */
void travelDoc(char* base, DOC_LIST* docList);

/**
 *  获取用户所有磁盘路径
 * @param baseList 用于接收磁盘路径信息的stringList
 */
void baseDriver(list<string>* baseList);
#endif //DOCUMENTLOOKUP_DOCUMENTLOOKUP_H
