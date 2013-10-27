
#include "firmata.h"

int             main()
{
  t_firmata     *firmata;
  int           i = 0;

  firmata = firmata_new("/dev/ttyACM0");
  while(!firmata->isReady)
    firmata_pull(firmata);
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

