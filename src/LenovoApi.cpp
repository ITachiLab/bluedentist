#include "LenovoApi.h"

LenovoApi::LenovoApi() {
	char libraryDir[1024];
	DWORD bufferSize = 1024;
	HKEY key;

	RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Lenovo\\Energy Management", 0, KEY_READ + KEY_WOW64_64KEY, &key);

	if (key) {
		RegQueryValueExA(key, "InstallDir", NULL, NULL, (LPBYTE)libraryDir, &bufferSize);
		RegCloseKey(key);

		strcpy_s(libraryDir + bufferSize - 1, 24, "LenovoEmExpandedAPI.dll");

		this->apiLibrary = LoadLibraryA(libraryDir);

		if (this->apiLibrary) {
			this->setBluetooth = (SetBluetooth)GetProcAddress(this->apiLibrary, "SetBluetooth");
			this->getBluetoothStatus = (GetBluetoothStatus)GetProcAddress(this->apiLibrary, "GetBluetoothStatus");
		} else {
			#ifdef _M_IX86
			throw "Could not load library. Try using x64 version of Bluedentist.";
			#endif

			#ifdef _M_X64
			throw "Could not load library. Try using x86 version of Bluedentist.";
			#endif
		}
	} else {
		throw "Could not find installation directory of Lenovo Energy Management.";
	}

}


LenovoApi::~LenovoApi() {
	FreeLibrary(this->apiLibrary);
}
