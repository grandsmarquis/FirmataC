#include "firmata.h"

int		main()
{
  t_firmata	*firmata;
  int		i = 0;

  firmata = firmata_new("/dev/ttyACM0");
  sleep(5);
  firmata_pinMode(firmata, 3, MODE_SERVO);
  while (1)
    {
      i++;
      usleep(10000);
      if (i == 180)
	i = 0;
      firmata_analogWrite(firmata, 3, i);
    }
}

