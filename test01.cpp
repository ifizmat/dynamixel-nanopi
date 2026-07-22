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

void portDebugInfo(dynamixel::PortHandler *portHandler, dynamixel::PacketHandler *packetHandler);
void ledDebugInfo(std::string message, dynamixel::PortHandler *portHandler, dynamixel::PacketHandler *packetHandler);

int main() {
  using namespace std;
  uint8_t dxl_error = 0;

  cout << "\nTest 01. Work by Firstname Secondname!\n";
  
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
  packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL);

  portDebugInfo(portHandler, packetHandler);

  packetHandler->write1ByteTxRx(portHandler, SERVO_ID, SERVO_REG_LED_STATUS, LED_OFF, &dxl_error);
  ledDebugInfo("LED Off error code: ", portHandler, packetHandler);
  sleep(2);

  packetHandler->write1ByteTxRx(portHandler, SERVO_ID, SERVO_REG_LED_STATUS, LED_ON, &dxl_error);
  ledDebugInfo("LED On error code: ", portHandler, packetHandler);
  sleep(2);

  portHandler->closePort();
  cout << "CLOSED PORT..." << endl;
  return 0;
}

void ledDebugInfo(std::string message, dynamixel::PortHandler *portHandler, dynamixel::PacketHandler *packetHandler) {
  uint8_t dxl_error = 0;
  uint8_t statusLED = 0;
  int com_result = 0;
  std::cout << message << std::hex << (int)dxl_error << std::endl;
  com_result = packetHandler->read1ByteTxRx(portHandler, SERVO_ID, SERVO_REG_LED_STATUS, &statusLED, &dxl_error); 
  std::cout << "LED status: " << std::hex << (int)statusLED << std::endl;
  std::cout << "LED status reading com_result: " << std::dec << com_result << std::endl;
  std::cout << "Result: " << packetHandler->getTxRxResult(com_result) << std::endl;
  packetHandler->write1ByteTxRx(portHandler, SERVO_ID, SERVO_REG_LED_STATUS, LED_OFF, &dxl_error);
}

void portDebugInfo(dynamixel::PortHandler *portHandler, dynamixel::PacketHandler *packetHandler) {
  std::cout << "portHandler: " << portHandler << std::endl;
  
  bool isPortOpened = portHandler->openPort();
  std::cout << "Port: " << DEVICENAME << std::endl;
  std::cout << "Is Port Opened: " << std::boolalpha << isPortOpened << std::endl;
  
  int baudRate = portHandler->getBaudRate();
  std::cout << "Baudrate: " << baudRate << std::endl;
}
