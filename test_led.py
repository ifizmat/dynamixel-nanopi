#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from dynamixel_sdk import *

BAUDRATE = 57600
DEVICENAME = '/dev/ttyS2'
PROTOCOL_VERSION = 2.0

# Servo Dynamixel XL430-W250
SERVO_ID = 0X02
LED_OFF = 0
LED_ON  = 1
LED_BLINK_COUNT = 4
SERVO_REG_ID = 7 # RW 8u
SERVO_REG_BAUDRATE = 8 # RW 8u
SERVO_REG_OPERATING_MODE = 11 # RW 8u
SERVO_REG_MAX_POSITION_LIMIT = 48 # RW 32u
SERVO_REG_MIN_POSITION_LIMIT = 52 # RW 32u
SERVO_REG_TORQUE_ENABLE = 64 # RW 8u
SERVO_REG_LED_STATUS = 65 # RW 8u

is_port_opened = False
print("Work by Firstname Secondname!")

portHandler = PortHandler(DEVICENAME)
# portHandler.setBaudRate(BAUDRATE)
packetHandler = PacketHandler(PROTOCOL_VERSION)


print(f'portHandler: {portHandler}')
# is_port_opened = portHandler.openPort()
print(f'Port: {DEVICENAME}')
print(f'Is Port Opened: {is_port_opened}')
baudrate = portHandler.getBaudRate()
print(f'Baudrate: {baudrate}')

# portHandler.openPort()

# portHandler.closePort()

