//
// Created by Dengzhanhong on 2020/9/6.
//

#ifndef SCREENSHOT_SCREENSHOT_H
#define SCREENSHOT_SCREENSHOT_H
#include <string>
#include <windows.h>
#include <wininet.h>
#include <winuser.h>
#include <conio.h>
#include <fstream>
#include <strsafe.h>
#include <io.h>
#include <crtdefs.h>
#include <fstream>
#include <GdiPlus.h>
#pragma comment(lib,"Wininet.lib")
#pragma comment (lib,"gdiplus.lib")
using namespace Gdiplus;
using namespace std;

/**
 *
 * @param file 保存文件的路径
 */
void screenshot(string file);
#endif //SCREENSHOT_SCREENSHOT_H
