#include "Serial.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
	Serial serial;
	if(!serial.open("/dev/ttyUSB0", 9600)) return -1;
	SerialInfo info = serial.getInfo();
	cout << "open success" << endl;
	cout << "device name:" << info.device_name() << endl;
	cout << "name:" << info.port() << "\n" << endl;
    bool isVisible = false;
    int count = 0;
	while (true) {
        if(count >= 11)break;
		unsigned char v = serial.read1byte();
        if(v == 0x55 && isVisible == false) isVisible = true;
        if(isVisible){
            cout << hex << 0 + v << " ";
            count++;
        }
	}
    cout << endl;
	return 0;
}

/*
UNICODE

int main() {
	std::wcout.imbue(std::locale(""));
	auto list = getSerialList();
	for (const auto info : list) {
		wcout << L"device name:" << info.device_name() << endl;
		wcout << L"name:" << info.port() << L"\n" << endl;
	}
	Serial serial;
	int port;
	cin >> port;
	if (!serial.open(list[port], 9600))
		return -1;
	SerialInfo info = serial.getInfo();
	wcout << L"open success" << endl;
	wcout << L"device name:" << info.device_name() << endl;
	wcout << L"name:" << info.port() << L"\n" << endl;
	while (true) {
		auto v = serial.read();
		for (auto c : v) {
			cout << c;
		}
	}
	return 0;
}
*/