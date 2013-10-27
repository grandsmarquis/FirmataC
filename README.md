FirmataC
========

This is a simple and lightweigh C library to communicate with Firmata devices such as Arduino.

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

Issues
------

For the moment, only the pinMode() and digitalWrite() were implemented and tested.
