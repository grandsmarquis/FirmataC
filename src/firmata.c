/*  FirmataC Firmata                                                            
 *  Copyright 2013, Jules Dourlens (jdourlens@gmail.com)                       
 *  Mainly based on Firmata GUI-Friendly by Paul Stoffregen (paul@pjrc.com)    
 *                                                                             
 *  This program is free software: you can redistribute it and/or modify       
 *  it under the terms of the GNU General Public License as published by       
 *  the Free Software Foundation, either version 3 of the License, or          
 *  (at your option) any later version.                                        
 *                                                                             
 *  This program is distributed in the hope that it will be useful,            
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of             
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              
 *  GNU General Public License for more details.                               
 *                                                                             
 *  You should have received a copy of the GNU General Public License          
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.      
 */

#include	"serial.h"
#include	"firmata.h"

#include	<string.h>
#include	<stdlib.h>
#include	<stdio.h>

t_firmata	*firmata_new(char *name)
{
  t_firmata	*res;

  printf("Opening device at: %s\n", name);
  res = malloc(sizeof(t_firmata));
  if (!res)
    {
      perror("firmata_new::Failed malloc");
      return (NULL);
    }
  res->serial = serial_new();
  if (!res->serial)
    {
      perror("firmata_new::Failed malloc");
      return (NULL);
    }
  serial_open(res->serial, name);
  firmata_initPins(res);
  serial_setBaud(res->serial, 57600);
  //  firmata_askFirmware(res);
  printf("Device opened at: %s\n", name);
  return (res);
}

void		firmata_initPins(t_firmata *firmata)
{
  int		i;

  for (i = 0; i < 128; i++) {
    firmata->pins[i].mode = 255;
    firmata->pins[i].analog_channel = 127;
    firmata->pins[i].supported_modes = 0;
    firmata->pins[i].value = 0;
  }
}

int		firmata_askFirmware(t_firmata *firmata)
{
  uint8_t	buf[3];
  int		res;

  buf[0] = FIRMATA_START_SYSEX;
  buf[1] = FIRMATA_REPORT_FIRMWARE; // read firmata name & version                     
  buf[2] = FIRMATA_END_SYSEX;
  res = serial_write(firmata->serial, buf, 3);
  return (res);
}

int		firmata_pinMode(t_firmata *firmata, int pin, int mode)
{
  int		res;
  uint8_t	buff[4];

  firmata->pins[pin].mode = mode;
  buff[0] = FIRMATA_SET_PIN_MODE;
  buff[1] = pin;
  buff[2] = mode;
  printf("Setting pinMode at: %i with value: %i\n", pin, mode);
  res = serial_write(firmata->serial, buff, 3);
  return (res);
}

int		firmata_digitalWrite(t_firmata *firmata, int pin, int value)
{
  int		i;
  int		res;
  uint8_t	buff[4];

  if (pin < 0 || pin > 127)
    return (0);
  firmata->pins[pin].value = value;
  int port_num = pin / 8;
  int port_val = 0;
  for (i = 0; i < 8; i++) {
    int p = port_num * 8 + i;
    if (firmata->pins[p].mode == MODE_OUTPUT || firmata->pins[p].mode == MODE_INPUT)
      {
	if (firmata->pins[p].value)
	  {
	    port_val |= (1<<i);
	  }
      }
  }
  printf("Writting digitalWrite at: %i with value: %i\n", pin, value);
  buff[0] = FIRMATA_DIGITAL_MESSAGE | port_num;
  buff[1] = port_val & 0x7F;
  buff[2] = (port_val >> 7) & 0x7F;
  res = serial_write(firmata->serial, buff, 3);
  return (res);
}
