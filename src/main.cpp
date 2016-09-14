#include "main.h"

LenovoApi *lenovoApi;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	try {
		lenovoApi = new LenovoApi();

		HWND hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)MyDialog);

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return (int)msg.wParam;
	} catch (const char* exception) {
		MessageBoxA(NULL, exception, "Error", MB_OK + MB_ICONERROR);
	}
}

BOOL CALLBACK MyDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CLOSE:
		DestroyWindow(hDlg);
		return TRUE;
	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
	case WM_INITDIALOG:
		checkBluetoothStatus(hDlg);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_RADIO1) {
			lenovoApi->setBluetooth(1, 0);
			checkBluetoothStatus(hDlg);
		}
		if (LOWORD(wParam) == IDC_RADIO2) {
			lenovoApi->setBluetooth(0, 0);
			checkBluetoothStatus(hDlg);
		}

		return TRUE;
	}

	return FALSE;
}

void checkBluetoothStatus(HWND hDlg) {
	int bluetoothStatus;
	lenovoApi->getBluetoothStatus(&bluetoothStatus, 0);

	if (bluetoothStatus) {
		CheckDlgButton(hDlg, IDC_RADIO1, BST_CHECKED);
	} else {
		CheckDlgButton(hDlg, IDC_RADIO2, BST_CHECKED);
	}
}