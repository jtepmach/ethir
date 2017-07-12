ARDUINO_VERSION=105

BOARD_TAG    = nano328
BOARD_TAG    = pro328

PANA = true
ARDUINO_LIBS = UIPEthernet UIPEthernet/utility IRLib SPI OneWire pubsubclient

ISP = true	# install does ispload

#ALTERNATE_CORE = optiboot-v5.0a

#AVRDUDE_ARD_PROGRAMMER = usbasp
#ARDUINO_PORT = usb
#ARDUINO_PORT = /dev/tty.usbserial-A603AT99
#AVRDUDE_ARD_PROGRAMMER = arduino
ARDUINO_PORT = /dev/tty.wchusbserial1410

#AVRDUDE_ARD_BAUDRATE=115200


#ISP_PROG = -c usbasp # old style makefile
ISP_PROG = usbasp
ISP_PORT = usb

#ISP_LOW_FUSE = 0xe2
#ISP_HIGH_FUSE = 0xda
#ISP_EXT_FUSE = 0x05

 
include ../arduino-mk/Arduino.mk
