//Example ATmega2560 Project
//File: ATmega2560Project.c
//An example file for second year mechatronics project

//include this .c file's header file
#include "Controller.h"

//static function prototypes, functions only called in this file

int main(void)
{
  //variable declarations
  //timer setup
  //WMG12 - WMG13 Top Value ICR1 - ICIE1 - Prescaler CS10
  cli();
  TCCR1A = 0;                                   //disable hardware output
  TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS10);    //enables CTC mode, sets prescaler to 1
  TCNT1 = 0;
  ICR1 = 1000;      //edit to change frequency

  TIMSK1 = (1<<ICIE1);        //
  sei();

  
  while(1)//main loop
  {
   
  }
  return(1);        //test
}//end main 

ISR(TMER1_CAPT_vect)
{

}

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