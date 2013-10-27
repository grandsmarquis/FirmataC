
#include "firmata.h"

int             main()
{
  t_firmata     *firmata;
  int           i = 0;

  firmata = firmata_new("/dev/ttyACM0"); //init Firmata
  while(!firmata->isReady) //Wait until device is up
    firmata_pull(firmata);
  firmata_pinMode(firmata, 13, MODE_OUTPUT); //set pin 13 (led on most arduino) to out
  while (1)
    {
      sleep(1);
      if (i++ % 2)
        firmata_digitalWrite(firmata, 13, HIGH); //light led
      else
        firmata_digitalWrite(firmata, 13, LOW); //unlight led
    }
}

