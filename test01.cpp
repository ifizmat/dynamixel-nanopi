#include <iostream>
#include <iomanip>
#include "dynamixel_sdk.h"

#define DEVICENAME "/dev/ttyS2"

dynamixel::PortHandler *portHandler;

int main() {
  using namespace std;
  cout << "\nTest 01. Work by Firstname Secondname!\n";
  
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
  cout << "portHandler: " << portHandler << endl;
  
  bool isPortOpened = portHandler->openPort();
  cout << "Port: " << DEVICENAME << endl;
  cout << "Is Port Opened: " << boolalpha << isPortOpened << endl;
  
  int baudRate = portHandler->getBaudRate();
  cout << "Baudrate: " << baudRate << endl;
  return 0;
}
