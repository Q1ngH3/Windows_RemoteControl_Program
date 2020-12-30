//
// Created by Dengzhanhong on 2020/9/7.
//

#include "documentLookUp.h"
#include "cstring"

void travelDoc(char* base, DOC_LIST* docListPtr) {
    long hDoc;
    struct _finddata64i32_t data;
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    strcpy_s(buff, base);
    strcat(buff, "*");
    hDoc = _findfirst(buff, &data);
    if (-1 == hDoc) {
        return;
    }
    docListPtr->push_front(data);
    while (!_findnext64i32(hDoc, &data)) {
        docListPtr->push_front(data);
    }
    _findclose(hDoc);
}

void baseDriver(list<string>* baseList) {
    int driveStrLen = GetLogicalDriveStrings(0, NULL);
    if (driveStrLen == 0) {
        return;
    }
    LPSTR driveStr = (LPSTR)HeapAlloc(GetProcessHeap(), 0, driveStrLen * sizeof(DWORD));
    GetLogicalDriveStrings(driveStrLen, driveStr);

    int i = 0;
    while (driveStr[i]) {
        char dir[4] = { driveStr[i],':','\\', '\0' };
        baseList->push_front(dir);
        i = i + 4;
    }
}