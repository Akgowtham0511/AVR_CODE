#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>

#define RS PB0  // Rs ->  Register select
#define EN PB1  // En -> Enalble Pin

void LCD_command(unsigned char command)
{
   PORTB = (PORTB & 0x0F)| (command & 0xF0); // Sending upper 4 bits
   PORTB &= ~(1<<RS); //RS -> 0: for command mode
   PORTB |= (1<<EN);

   _delay_ms(2);

   PORTB &= ~(1<<EN);

   PORTB = (PORTB & 0x0F) | (command<<4); // Sending Lower 4 bits
   PORTB |= (1<<EN);
   _delay_ms(1);
   PORTB &= ~(1<<EN);
   _delay_ms(1);
}

void LCD_clear()
{
   LCD_command(0x01); // LCD -> clear
   _delay_ms(5);
   LCD_command(0x80); // Bring the curser back to home
}

void LCD_char(unsigned char value)
{
   PORTB = (PORTB & 0x0F)| (value & 0xF0); // Sending upper 4 bits
   PORTB |= (1<<RS); //RS -> 1: for data mode
   PORTB |= (1<<EN);

   _delay_ms(2);

   PORTB &= ~(1<<EN);
 
   _delay_us(200);

   PORTB = (PORTB & 0x0F) | (value<<4); // Sending Lower 4 bits
   PORTB |= (1<<EN);
   _delay_ms(1);
   PORTB &= ~(1<<EN);
   _delay_ms(1);
}

void LCD_string(char *str)
{
  int i;

  for(i=0;str[i]!=0;i++)
  {
    LCD_char(str[i]);
  }
}

void  LCD_init()
{
   DDRB = 0xFF;

  _delay_ms(20);

  LCD_command(0x02);  // Return Home

  LCD_command(0x28);  // 2 line, 5*7 matrix in 4-bit mode

  LCD_command(0x0C);  // Display onn curser off

  LCD_command(0x06);  // Increment Right Curser

  LCD_command(0x01); //   Clear display screen

  _delay_ms(2);
}


int main()
{

  LCD_init();

  LCD_string("TRILOK!!");

  LCD_command(0xC0);//Setting the curser on the second line 

  LCD_string("SAIN!!");

  while(1);

}



























