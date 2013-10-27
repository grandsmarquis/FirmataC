/*  FirmataC Serial                                    
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

#ifndef __H_FIRMATAC_SERIAL_
#define __H_FIRMATAC_SERIAL_

#include <stdint.h>

#include <termios.h>

typedef struct		s_serial
{
  int			port_is_open;
  char			*port_name;
  int			baud_rate;
  char			*error_msg;

  int			port_fd;
  struct termios	settings_orig;
  struct termios	settings;
  int			tx;
  int			rx;
}			t_serial;

t_serial		*serial_new();
int             serial_open(t_serial *serial, char *name);
int		serial_setBaud(t_serial *serial, int baud);
int		serial_read(t_serial *serial, void *ptr, int count);
int		serial_write(t_serial *serial, void *ptr, int len);
int		serial_waitInput(t_serial *serial, int msec);
int		serial_discardInput(t_serial *serial);
void		serial_flushOutput(t_serial *serial);
int		serial_setControl(t_serial *serial, int dtr, int rts);

#endif
