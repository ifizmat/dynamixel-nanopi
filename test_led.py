#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import fcntl
import struct
import termios                                                                                          
from dynamixel_sdk import *

BAUDRATE = 57600
DEVICENAME = '/dev/ttyS2'
PROTOCOL_VERSION = 2.0

# Servo Dynamixel XL430-W250
SERVO_ID = 0X01
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

    
def main():
    global is_port_opened
    print("Work by Firstname Secondname!")
    portHandler = PortHandler(DEVICENAME)

    packetHandler = PacketHandler(PROTOCOL_VERSION)
    
    is_port_opened = portHandler.openPort()

    if is_port_opened:
        portHandler.setBaudRate(BAUDRATE)
        # Clearly down DTR/RTS
        portHandler.ser.dtr = False        
        portHandler.ser.rts = False        

        # Set mode RS485 through ioctl
        TIOCSRS485 = 0x542F
        rs485_struct = struct.pack('IIIIIIII', 0X0001, 0, 0, 0, 0, 0, 0, 0)
        try:
            fcntl.ioctl(portHandler.ser.fd, TIOCSRS485, rs485_struct)
            print(f'[OK] RS485 mode enabled')
            
            attrs = termios.tcgetattr(portHandler.ser.fd)
            # c_iflag: IGNPAR - Ignore parity errors, if - input flag
            attrs[0] = termios.IGNPAR
            
            # c_oflag: 0, of - output flag
            attrs[1] = 0
            
            # c_cflag: boadrate | CS8 | CLOCAL | CREAD, cf - control flags
            attrs[2] = termios.B57600 | termios.CS8 | termios.CLOCAL | termios.CREAD
            
            # c_lflag: 0 (turn off echo and processing), lf - local flags
            attrs[3] = 0
            
            # ispeed, ospeed - boadrate
            attrs[4] = termios.B57600
            attrs[5] = termios.B57600
            
            # cc: VTIME = 0, VMIN = 0, cc - control chars
            attrs[6][termios.VTIME] = 0
            attrs[6][termios.VMIN] = 0
            
            # Apply settings through TCSANOW (as in the C++ SDK)
            termios.tcsetattr(portHandler.ser.fd, termios.TCSANOW, attrs)
            print('[OK] termios settigs applied (IGNPAR, TCSANOW)')
            
            
        except Exception as e:
            print(f'[WARNING] Failed to set RS485 mode: {e}')
        
    
    port_debug_info(portHandler)    
    led_debug_info('LED Off error code: ', portHandler, packetHandler)
    portHandler.closePort()


def led_debug_info(message, portHandler, packetHandler):
    dxl_error = 0
    status_led = 0
    dxl_comm_result = 0
    status_led, dxl_comm_result, dxl_error = packetHandler.read1ByteTxRx(portHandler, SERVO_ID, SERVO_REG_LED_STATUS)
    print(f'LED status: {status_led}')
    print(f'message {dxl_error}')
    print(f'LED status reading communication result: {dxl_comm_result}')
    print(f'Result: {packetHandler.getTxRxResult(dxl_comm_result)}')
    
    
def port_debug_info(portHandler):
    print(f'portHandler: {portHandler}')
    print(f'Port: {DEVICENAME}')
    print(f'Is Port Opened: {is_port_opened}')
    baudrate = portHandler.getBaudRate()
    print(f'Baudrate: {baudrate}')
    print(f'DTR: {portHandler.ser.dtr}')
    print(f'RTS: {portHandler.ser.rts}')


if __name__ == "__main__":
    main()
    
