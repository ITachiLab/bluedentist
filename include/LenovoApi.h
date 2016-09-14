#pragma once
#include "Windows.h"

typedef int(__fastcall *SetBluetooth)(int, int);
typedef int(__fastcall *GetBluetoothStatus)(int*, int);

class LenovoApi {
public:
	LenovoApi();
	~LenovoApi();

	SetBluetooth setBluetooth;
	GetBluetoothStatus getBluetoothStatus;
private:
	HINSTANCE apiLibrary;
};

