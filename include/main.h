#pragma once
#include <windows.h>
#include "resource.h"
#include "LenovoApi.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
BOOL CALLBACK MyDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void checkBluetoothStatus(HWND hDlg);