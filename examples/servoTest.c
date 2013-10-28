#include "servo.h"

int		main()
{
  t_firmata	*firmata;
  t_servo	*servo;
  int		i = 0;

  firmata = firmata_new("/dev/ttyACM0");
  while(!firmata->isReady)
    firmata_pull(firmata);
  sleep(1);
  servo = servo_attach(firmata, 3);
  while (1)
    {
      usleep(10000);
      if (i == 180)
	i = 0;
      servo_write(servo, i++);
    }
}

