FirmataC
========

This is a simple and lightweigh C library to communicate with Firmata devices such as Arduino.

This library implements [Firmata V2.3](http://firmata.org/wiki/Protocol).

Example
-------

Here is the implementation of [Arduino blinking led tutorial](http://arduino.cc/en/Tutorial/Blink?from=Tutorial.BlinkingLED) using FirmataC.

```C
#include "firmata.h"

int             main()
{
  t_firmata     *firmata;
  int           i = 0;

  firmata = firmata_new("/dev/ttyACM0");
  sleep(5);
  firmata_pinMode(firmata, 13, MODE_OUTPUT);
  while (1)
    {
      sleep(1);
      if (i++ % 2)
        firmata_digitalWrite(firmata, 13, HIGH);
      else
        firmata_digitalWrite(firmata, 13, LOW);
    }
}
```
Reference
---------
```C
t_firmata       *firmata_new(char *name)
```
* name: path to device, usually "/dev/ttyACM0"

```C
int             firmata_pinMode(t_firmata *firmata, int pin, int mode)
```
* pin: #pin
* mode: pinMode can be: MODE_INPUT, MODE_OUTPUT, MODE_SERVO, MODE_PWM, MODE_ANALOG, MODE_SHIFT, MODE_I2C 

```C
int             firmata_digitalWrite(t_firmata *firmata, int pin, int value)
```

* pin: #pin
* value: can be HIGH or LOW

```C
int             firmata_analogWrite(t_firmata *firmata, int pin, int value)
```
* pin: #pin
* value: #value

For more information see the [Arduino documentation](http://arduino.cc/en/Reference/HomePage).


Issues
------

For the moment, only the pinMode() and digitalWrite(), analogWrite() were implemented and tested.

License
-------

See License file included in sources.

Thanks
------

Special thanks to Paul Stoffregen for the [Firmata GUI-friendly](http://firmata.org/wiki/Main_Page) that helped much!
