#include "bluetooth.h"

Bluetooth::Bluetooth(unsigned short rx, unsigned short tx, unsigned int br)
{
    RX = rx;
    TX = tx;
    baudrate = br;
    device = new SoftwareSerial(RX, TX);
}

Bluetooth::Bluetooth(unsigned short rx, unsigned short tx)
{
    RX = rx;
    TX = tx;
    baudrate = deffaultBaudrate;
    device = new SoftwareSerial(RX, TX);
}

Bluetooth::~Bluetooth()
{
    delete device;
}

void Bluetooth::begin()
{
    device->begin(baudrate);
    delay(waitTime);
    init = true;
    setBaudrate(baudrate);
    clearSerial();
    Serial.write("Ready.");
}

void Bluetooth::reset()
{
    if (init) 
    {
        strcpy(message, "AT+RESET");
        write(message);
    }
}

void Bluetooth::write(const char buffer[])
{
    device->write(buffer);
    delay(waitTime);
}

void Bluetooth::clearSerial()
{
    char garbage; 
    while (device->available())
        garbage = device->read();
}

void Bluetooth::receive() 
{
    int index = 0;
    if(device->available())
        strcpy(message, "");
    while(device->available()) 
    {
        message[index] = device->read();
        index++;
    }
    message[index] = '\0';
}

void Bluetooth::setDeviceName(const char name[])
{
    if (strlen(name) <= nameSize) 
    {
        strcpy(message, "AT+NAME");
        strcat(message, name);
        strcpy(deviceName, name);
        write(message);
    }
}

void Bluetooth::setDevicePin (const char pin[]) {
    if (strlen(pin) == 4) {
        for (int c = 0; c < 4; c++) {
            if (pin[c] < 0x30 || pin[c] > 0x90) {
                return;
            }
        }
        strcpy(message, "AT+PIN");
        strcat(message, pin);
        strcpy(devicePin, pin);
        write(message);
    }
}

char* Bluetooth::getMessage()
{
    receive();
    return message;
}

char* Bluetooth::getName()
{
    return deviceName;
}

char* Bluetooth::getPin()
{
    return devicePin;
}

unsigned short Bluetooth::getRXPin() 
{
    return RX;
}

unsigned short Bluetooth::getTXPin () 
{
    return TX;
}

void Bluetooth::setBaudrate (unsigned short tier)
{
    if (init) 
    {
        strcpy(message, "AT+BAUD");
        switch (tier) {
            case 1:
                strcat(message, "1");
                baudrate = 1200;
                break;
            case 2:
                strcat(message, "2");
                baudrate = 2400;
                break;
            case 3:
                strcat(message, "3");
                baudrate = 4800;
                break;
            case 4:
                strcat(message, "4");
                baudrate = 9600;
                break;
            case 5:
                strcat(message, "5");
                baudrate = 19200;
                break;
            case 6:
                strcat(message, "6");
                baudrate = 38400;
                break;
            case 7:
                strcat(message, "7");
                baudrate = 57600;
                break;
            case 8:
                strcat(message, "8");
                baudrate = 115200;
                break;
            case 9:
                strcat(message, "9");
                baudrate = 230400;
                break;
            case 10:
                strcat(message, "10");
                baudrate = 460800;
                break;
            case 11:
                strcat(message, "11");
                baudrate = 921600;
                break;
            case 12:
                strcat(message, "12");
                baudrate = 1382400;
                break;
            default:
                strcat(message, "4");
                baudrate = deffaultBaudrate;
                break;
        }
        write(message);
    }
}
