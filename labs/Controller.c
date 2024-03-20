//Example ATmega2560 Project
//File: ATmega2560Project.c
//An example file for second year mechatronics project

//include this .c file's header file
#include "Controller.h"

//static function prototypes, functions only called in this file
volatile uint8_t button_pos =1;

#include <cstdint>
int main(void)
{
	//variable declarations
	char lcd_string[33] = {0}; //declare and initialise string for LCD
	cli(); //pause interrupts
	DDRD &= ¬(1<<DD0);//INT0 input mode
	DDRC = 0xFF; //portC in output mode
	DDRA = 0x00; //set port A to input mode
	DDRB = 0xFF; //set portB to output
	DDRL = 0xFF;
	PORTB = 0;
	PORTL = 0x00; //set Port L to Low
	PORTA = 0; //set port A to low
	PORTC = 0; //PORTC low
	PORTL |= (PA3<<1); // set PL3 (RS) to high
	PORTD |= (1<<PD0); //enable pd0 pullup resistor
	EICRA |= (1<<ISC01);//INT0 set
	EICRA &= (1<<ISC00);//falling edge
	EIMSK |= (1<<INT0); //INT0 enbable
	sei(); //enable interupts
	//initialisation section, runs once
	adc_init(); //initialse ADC
	lcd_init(); //initialise 

	_delay_ms(20);
	uint16_t variableToPrint = 0;
	
	//main loop
	while(1)
	{	
		
    lcd_goto(0);      //Put cursor at position 0
    lcd_home();       // same as lcd_goto(0);
		lcd_puts( "This is the number 32" ); //Print string to LCD first line
		lcd_goto( 0x40 );     //Put cursor to first character on second line

		if(button_pos==1){
			variableToPrint = PA0; //if button is not toggled set var to Vout of range sensor

		}
		sprintf( lcd_string , "This is the number %u" , variableToPrint ); 
    //print to string, %u special character to be replaced by variables in later arguments
    lcd_puts( lcd_string ); //Print string to LCD second line, same as first line
    //%u for unsigned integers, %i,%d for signed integers
    //%lu for long unsigned ...
    lcd_clrscr();     //Clear everything on LCD
		variableToPrint = 111;
		sprintf( lcd_string , "%u" , variableToPrint );
		lcd_goto(0);     
    lcd_puts( lcd_string ); //Screen shows 111
		variableToPrint = 3;
		sprintf( lcd_string , "%u" , variableToPrint );
		lcd_puts( lcd_string ); // screen shows 311
		sprintf( lcd_string , "%3u" , variableToPrint );
		lcd_puts( lcd_string ); // screen now has 3
		//loop code goes here		
	}
	return(1);
} //end main

ISR(INT0_vect){
	//interrupt code
	PORTC ^= (1<<PC1); //toggle LED
	button_pos ^= 1;
	_delay_ms(20);
}


