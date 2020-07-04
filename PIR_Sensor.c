#define F_CPU 1600000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRC = 0xFF;
  DDRA = 0x00;
  while(1)
  {
	 PORTC = PINA;
  }
}
