/*
   Bluetooth library
   Author: https://github.com/karasikq
   Last update: 25.12.2018
   License: GNU GPLv3
*/


#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include "Arduino.h"
#include <SoftwareSerial.h>

const unsigned short nameSize = 40;
const long deffaultBaudrate = 9600;
const unsigned int waitTime =  2000;
const unsigned short messageSize = 10;

class Bluetooth
{
  private:
    SoftwareSerial  *device;
    bool init = false;
    unsigned short RX;
    unsigned short TX;
    long baudrate;
    char message[messageSize + nameSize + 1];
    char deviceName[nameSize + 1];
    char devicePin[4 + 1];
    void clearSerial();
    void receive();
    void write(const char buffer[]);
  public:
    Bluetooth(unsigned short rx, unsigned short tx, long br);
    Bluetooth(unsigned short rx, unsigned short tx);
    ~Bluetooth();

    void begin();
    void reset();
    void setBaudrate(const long tier);
    void setDeviceName(const char name[]);
    void setDevicePin(const char pin[]);
    char* getMessage();
    char* getName();;
    char* getPin();
    unsigned short getRXPin();
    unsigned short getTXPin();
};

#endif
