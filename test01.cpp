#include <iostream>
#include <iomanip>
#include "dynamixel_sdk.h"

#define DEVICENAME "/dev/ttyS2"
#define PROTOCOL 1.0

// test git push
// Servo Dynamixel XL430-W250
#define SERVO_ID 0X02
#define SERVO_REG_ID 7 // RW 8u
#define SERVO_REG_BAUDRATE 8 // RW 8u
#define SERVO_OPERATING_MODE 11 // RW 8u
#define SERVO_REG_MAX_POSITION_LIMIT 48 // RW 32u
#define SERVO_REG_MIN_POSITION_LIMIT 52 // RW 32u
#define SERVO_REG_TORQUE_ENABLE 64 // RW 8u
#define SERVO_REG_LED_STATUS 65 // RW 8u

dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;

int main() {
  using namespace std;
  cout << "\nTest 01. Work by Firstname Secondname!\n";
  
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
  packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL);

  cout << "portHandler: " << portHandler << endl;
  
  bool isPortOpened = portHandler->openPort();
  cout << "Port: " << DEVICENAME << endl;
  cout << "Is Port Opened: " << boolalpha << isPortOpened << endl;
  
  int baudRate = portHandler->getBaudRate();
  cout << "Baudrate: " << baudRate << endl;
  portHandler->closePort();
  cout << "CLOSED PORT..." << endl;
  return 0;
}
