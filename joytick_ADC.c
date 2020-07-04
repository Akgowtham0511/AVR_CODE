#define F_CPU 16000000UL 
#include <avr/io.h>
#include <util/delay.h>

void ADC_Init()
{
	DDRA=0x0;			 
	ADCSRA = 0x87;		
	ADMUX = 0x40;		
	
}

int Analog_Read(char value)
{

	ADMUX=ADMUX|(value & 0x0f);	
	ADCSRA |= (1<<ADSC);		
	while((ADCSRA&(1<<ADIF))==0);	
	_delay_ms(5);
    int  first_4bit = (int)ADCL;		
    int 	last_4bit = (int)ADCH*256;		
    int complete_bit = first_4bit + last_4bit;				
	return(complete_bit);		
}

 
int main()
{
	int vrx,vry;
	ADC_Init();
    char read_data_vrx[10];   
	char read_data_vry[10];
	while(1)
	{
		vrx = Analog_Read(0);	// connected to  the adc pin 0 ->A0
		vry = Analog_Read(1);   // connected to the adc pin 1 -> A1
		itoa(vrx,read_data_vrx,10);	
		itoa(vry,read_data_vry,10); 
	//alternative to itoa -> sprintf
	}
  return 0;
}
