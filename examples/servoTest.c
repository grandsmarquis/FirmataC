#include "servo.h"

int		main()
{
  t_firmata	*firmata;
  t_servo	*servo;

  firmata = firmata_new("/dev/ttyACM0");
  while(!firmata->isReady)
    firmata_pull(firmata);
  sleep(1);
  servo = servo_attach(firmata, 3);
  while (1)
    {
      usleep(10000);
      if (servo->value == 180)
	servo->value = 0;
      servo_write(servo, servo->value++);
    }
}

