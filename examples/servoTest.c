#include "firmata.h"

int		main()
{
  t_firmata	*firmata;
  int		i = 0;

  firmata = firmata_new("/dev/ttyACM0");
  while(!firmata->isReady)
    firmata_pull(firmata);
  firmata_pinMode(firmata, 3, MODE_SERVO);
  while (1)
    {
      firmata_pull(firmata);
      i++;
      usleep(10000);
      if (i == 180)
	i = 0;
      firmata_analogWrite(firmata, 3, i);
    }
}

