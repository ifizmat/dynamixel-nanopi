#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "dynamixel_sdk.h"

#define DEVICENAME "/dev/ttyS2"
#define PROTOCOL 1.0

// test git push
// Servo Dynamixel XL430-W250
#define SERVO_ID 0X02
#define LED_OFF 0
#define LED_ON  1
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
  uint8_t dxl_error = 0;
  uint8_t statusLED = 0;
  int com_result = 0;
  cout << "\nTest 01. Work by Firstname Secondname!\n";
  
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
  packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL);

  cout << "portHandler: " << portHandler << endl;
  
  bool isPortOpened = portHandler->openPort();
  cout << "Port: " << DEVICENAME << endl;
  cout << "Is Port Opened: " << boolalpha << isPortOpened << endl;
  
  int baudRate = portHandler->getBaudRate();
  cout << "Baudrate: " << baudRate << endl;

  packetHandler->write1ByteTxRx(portHandler, SERVO_ID, SERVO_REG_LED_STATUS, LED_OFF, &dxl_error);
  cout << "LED Off error code: " << hex << (int)dxl_error << endl;
  com_result = packetHandler->read1ByteTxRx(portHandler, SERVO_ID, SERVO_REG_LED_STATUS, &statusLED, &dxl_error); 
  cout << "LED status: " << hex << (int)statusLED << endl;
  cout << "LED status reading com_result: " << dec << com_result << endl;
  cout << "Result: " << packetHandler->getTxRxResult(com_result) << endl;
  sleep(2);

  packetHandler->write1ByteTxRx(portHandler, SERVO_ID, SERVO_REG_LED_STATUS, LED_ON, &dxl_error);
  cout << "LED On error code: " << hex << dxl_error << endl;
  com_result = packetHandler->read1ByteTxRx(portHandler, SERVO_ID, SERVO_REG_LED_STATUS, &statusLED, &dxl_error); 
  cout << "LED status: " << hex << statusLED << endl;
  cout << "LED status reading com_result: " << dec << com_result << endl;
  cout << "Result: " << packetHandler->getTxRxResult(com_result) << endl;
  sleep(2);

  portHandler->closePort();
  cout << "CLOSED PORT..." << endl;
  return 0;
}
