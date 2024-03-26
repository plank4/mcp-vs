//Example ATmega2560 Project
//File: ATmega2560Project.c

//include this .c file's header file
#include "Controller.h"
# define DEBOUNCE_PERIOD 100

//static function prototypes, functions only called in this file

int main(void)
{
  //variable declaration
  milliseconds_init();
  lcd_init();
  serial0_init();

  _delay_ms(20);
  uint16_t variableToPrint;
  //Timer Setup
  //WGM12 - WGM13 - Top Value ICR1 - ICIE1 - Prescaler CS10
  cli();
  TCCR1A = 0;
  TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS10);
  TCNT1 = 0;
  ICR1 = 1000;
  TIMSK1 = (1<<ICIE1);
  //Button interrupt setup
  DDRD &= ~(1<<DD0)&(1<<DD1)&(1<<DD2); //INT0 INT1 INT2 INPUT MODE
  PORTD |= (1<<PD0)|(1<<PD1)|(1<<PD2); //ENABLE PULLUPS
  EICRA |= (1<<ISC01)|(1<<ISC11)|(1<<ISC21); 
  EICRA &= ~(1<<ISC00)&(1<<ISC10)&(1<<ISC20); //FALLING EDGE TRIGGER
  EIMSK |= (1<<INT0)|(1<<INT1)|(1<<INT2); //ENABLE INT0 INT1 INT2
  sei();

  //main loop
  while(1){
    lcd_goto(0);
    lcd_home();
    lcd_puts();
    lcd_goto(0x40);
    variableToPrint = 32
    sprintf();
    lcd_puts(lcd_string);
  }return(1);
}//end main 

ISR(INT0_vect){//BUTTON INTERRUPT
uint32_t time0 = milliseconds_now(); //EXPERIMENTAL BETTER TRIGGER METHOD
static uint32_t prevTime0 = 0;
if(time0 > (prevTime0 + DEBOUNCE_PERIOD)){
  PORTA ^= (1<<PA0); //TOGGLE LED
  prevTime0 = time0;
}
//_delay_ms(20); //REPLACE WITH THIS IN FAILURE
//PORTA ^= (1<<PA0);
}

ISR(INT1_vect){//BUTTON INTERRUPT
uint32_t time1 = milliseconds_now(); //EXPERIMENTAL BETTER TRIGGER METHOD
static uint32_t prevTime1 = 0;
if(time1 > (prevTime1 + DEBOUNCE_PERIOD)){
  PORTA ^= (1<<PA1); //TOGGLE LED
  prevTime1 = time1;
}
//_delay_ms(20); //REPLACE WITH THIS IN FAILURE
//PORTA ^= (1<<PA1);
}

ISR(INT2_vect){//BUTTON INTERRUPT
uint32_t time2 = milliseconds_now(); //EXPERIMENTAL BETTER TRIGGER METHOD
static uint32_t prevTime2 = 0;
if(time2 > (prevTime2 + DEBOUNCE_PERIOD)){
  PORTA ^= (1<<PA2); //TOGGLE LED
  prevTime2 = time2;
}
//_delay_ms(20); //REPLACE WITH THIS IN FAILURE
//PORTA ^= (1<<PA2);
}