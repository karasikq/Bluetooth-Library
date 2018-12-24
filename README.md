# Bluetooth Library
## Initialization
```
Bluetooth bt(3,4); // rx, tx
Bluetooth bt(3,4, 9600); // rx, tx, baudrate
```
## Methods
```
void begin(); // Starts device
void reset(); // Reset device(ex. for change name)
void setBaudrate(unsigned short tier); // Set baudrate by tier(4 - 9600; 5 - 19200 etc.)
void setDeviceName(const char name[]); // Set name
void setDevicePin(const char pin[]); // Set pin
char* getMessage(); // Get message from buffer
char* getName(); // Get device name
char* getPin(); // Get pin code
unsigned short getRXPin();
unsigned short getTXPin(); 
```