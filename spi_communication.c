#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//MASTER MODE
void In_It_master()
{
  DDRB |= (1<<PB5)|(1<<PB7)|(1<<PB4);

  DDRB &= ~(1<<PB4);

  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

  SPSR &= ~(1<<SPI2X);
}

void spi_write_master(char value)
{

  while(!(SPSR&(1<<SPIF)));
   SPDR = value;
}

char spi_read_master()
{
  SPDR = 0xFF;
  while(!(SPSR&(1<<SPIF)));
  return (SPDR);
}

//SLAVE MODE

void in_it_slave()
{
   DDRB |= (1<<PB4)|(1<<PB5)|(1<<PB7);
   DDRB &= (1<<PB6);
   SPCR = (1<<SPE);
}

char spi_read_slave()
{
    SPDR = 0xFF;
  while(!(SPSR&(1<<SPIF)));
  return (SPDR);
}

void spi_write_slave(char value)
{
     while(!(SPSR&(1<<SPIF)));
      SPDR = value;
}

int main()
{
  
}








