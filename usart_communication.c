#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void baud_rate(long USART_BAUDRATE )
{
  UCSRB |= (1<<RXEN)|(1<<TXEN);
  UCSRC |= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
  UBRRL = BAUD_PRESCALE;
  UBRRH = (BAUD_PRESCALE>>8);

}

void Send_Char(char a)
{
  
 while (!( UCSRA & (1<<UDRE)));  
 UDR = a;
}

char Recieve_Data()
{
  while(!(UCSRA &(1<<RXC)));
  return UDR;
}

void send_string(char *str)
{
  for(int i=0;str[i]!=0;i++)
  {
    Send_Char(str[i]);
  }
}

int main()
{

   // char str[] = "DATA";
    baud_rate(9600);
	while(1)
	{
      send_string("Send");
	  _delay_ms(500);
	}
}





