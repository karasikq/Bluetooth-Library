#include "bluetooth.h"

Bluetooth::Bluetooth(unsigned short rx, unsigned short tx, long br)
{
  RX = rx;
  TX = tx;
  baudrate = br;
  device = new SoftwareSerial(RX, TX);

  memset(message, '1', 51);
}

Bluetooth::Bluetooth(unsigned short rx, unsigned short tx)
{
  RX = rx;
  TX = tx;
  baudrate = deffaultBaudrate;
  device = new SoftwareSerial(RX, TX);

  memset(message, '1', 51);
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
  if (device->available())
    memset(message, '1', 51);
  while (device->available())
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

unsigned short Bluetooth::getTXPin()
{
  return TX;
}

void Bluetooth::setBaudrate(const long br)
{
  if (init)
  {
    strcpy(message, "AT+BAUD");
    baudrate = br;
    switch (br)
    {
      case 1200:
        strcat(message, "1");
        break;
      case 2400:
        strcat(message, "2");
        break;
      case 4800:
        strcat(message, "3");
        break;
      case 9600:
        strcat(message, "4");
        break;
      case 19200:
        strcat(message, "5");
        break;
      case 38400:
        strcat(message, "6");
        break;
      case 57600:
        strcat(message, "7");
        break;
      case 115200:
        strcat(message, "8");
        break;
      case 230400:
        strcat(message, "9");
        break;
      case 460800:
        strcat(message, "10");
        break;
      case 921600:
        strcat(message, "11");
        break;
      case 1382400:
        strcat(message, "12");
        break;
      default:
        strcat(message, "4");
        baudrate = deffaultBaudrate;
        break;
    }
    write(message);
  }
}
