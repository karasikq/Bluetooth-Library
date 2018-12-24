#include <SoftwareSerial.h>
#include "bluetooth.h"

Bluetooth bt(3,4);

void setup() 
{
    Serial.begin(9600);
    bt.begin();
    bt.setDeviceName("NEW");
    bt.setBaudrate(5);
    bt.reset();
}
 
void loop()
{
    Serial.write(bt.getMessage());
    Serial.write(bt.getName());
    delay(500);
}
