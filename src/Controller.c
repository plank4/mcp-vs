#include "Controller.h"

//static function prototypes, functions only called in this file

bool button_pos = 0;

int main(void)
{
	//variable declarations
	char lcd_string[33] = {0}; //declare and initialise string for LCD

	//initialisation section, runs once
	PORTD |= (1<<PD0); //enable pd0 pullup resistor
	EICRA |= (1<<ISC01);//INT0 set
	EICRA &= (1<<ISC00);//falling edge
	EIMSK |= (1<<INT0); //INT0 enbable
	sei(); //enable interupts
	adc_init(); //initialse ADC
	lcd_init(); //initialise 
	

	_delay_ms(20);
	float variableToPrint;
	
	//main loop
	while(1)
	{	
		
    lcd_goto(0);      //Put cursor at position 0
    lcd_home();       // same as lcd_goto(0);
		sprintf(lcd_string, "%d", variableToPrint);
		lcd_puts(lcd_string); //Print string to LCD first line
		lcd_goto( 0x40 );     //Put cursor to first character on second line
		if(button_pos == 1){
			variableToPrint =(adc_read(3));
			
		}
		
		_delay_ms(20);
		
	}
	return(1);
} //end main
ISR(INT0_vect){
	//interrupt code
	PORTC ^= (1<<PC1); //toggle LED
	button_pos ^= 1;
	_delay_ms(20);
}
