CXX = g++
CXXFLAGS = -g -Wall -Wextra -ISerialPort/SerialPort/

main: main.cpp SerialPort/SerialPort/Linux_Serial.cpp SerialPort/SerialPort/Serial.cpp

clean:
	$(RM) main