/* LED demo for Teensy USB Development Board
 * Portions Copyright (c) 2008, 2010 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>
#include "print.h"
#include "string.h"
#include "usb_serial.h"
#include "kitt.h"

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

/* Enumerate the LEDs by their port numbers (0-7) */
#define FIRST_LED 0
#define LAST_LED 7
#define LED_COUNT (LAST_LED - FIRST_LED + 1)
#define LED_DELAY 50

int main(void)
{
 configure_teensy();
 configure_LEDs();
 configure_usb();

 int16_t lastcmd = '\0', cmd = '\0';

 while (1) 
 {
     wait_for_usb_connection();

     while (1) 
     {
         cmd = usb_serial_getchar();

         if( is_valid(cmd) ) lastcmd = cmd;

         if(lastcmd == 'k') knight_rider();
         else if(lastcmd == 's') step();
         else if(lastcmd == 'f') follow();
         else demo();
     }
 }
}


void configure_LEDs()
{
	for (int i = 0; i < LED_COUNT; i++) led_config(i + FIRST_LED);
}

void wait_for_usb_connection()
{
    // wait for the user to run their terminal emulator program
    // which sets DTR to indicate it is ready to receive.
    while (!(usb_serial_get_control() & USB_SERIAL_DTR)) /* wait */ ;
}

void configure_teensy()
{
	// set for 16 MHz clock, and make sure the LED is off
	CPU_PRESCALE(0);

	// normal mode, 2 MHz, count to 2^16 and roll over
	TCCR1A = 0x00;
	TCCR1B = 0x02;
	TCCR1C = 0x00;
}

void configure_usb()
{
    // initialize the USB, and then wait for the host
	// to set configuration.  If the Teensy is powered
	// without a PC connected to the USB port, this
	// will wait forever.
	usb_init();
	while (!usb_configured()) /* wait */ ;
	_delay_ms(1000);
}



int is_valid(int16_t cmd)
{
    return (cmd == 'k' || cmd == 's' || cmd == 'f' || cmd == 'd');
}

void knight_rider()
{
    int i;
	for (i = 0; i < LED_COUNT; i++) {
        led_on(i + FIRST_LED);
		_delay_ms(LED_DELAY);
		led_off(i + FIRST_LED);
	}
	for (i = 0; i < LED_COUNT; i++) {
        led_on(LAST_LED - i);
		_delay_ms(LED_DELAY);
		led_off(LAST_LED - i);
	}    
}

void demo()
{
	for (int i = 0; i < (LED_COUNT / 2); i++) {
        led_on(FIRST_LED + i);
        led_on(LAST_LED - i);
		_delay_ms(LED_DELAY);
        led_off(FIRST_LED + i);
        led_off(LAST_LED - i);
	}
}

void step()
{
	for (int i = 0; i < LED_COUNT; i++) {
        led_on(i + FIRST_LED);
		_delay_ms(LED_DELAY);
		led_off(i + FIRST_LED);
	}
}

int prev(int position)
{
    if(position < 1) return 7;
    return position - 1;
}

int next(int position)
{
    if(position > 6) return 0;
    return position + 1;
}

void follow()
{
	for (int i = 0; i < LED_COUNT; i++) {
        int current = i + FIRST_LED;
        
        led_on(prev(current));
        led_on(current);
        led_on(next(current));
        
		_delay_ms(LED_DELAY);

        led_off(prev(current));
        led_off(current);
        led_off(next(current));
	}
}

void led_config(int port)
{
    DDRD |= (1<<port);
    led_off(port);
}

void led_on(int port)
{
    PORTD |= (1<<port);
}

void led_off(int port)
{
    PORTD &= ~(1<<port);
}

