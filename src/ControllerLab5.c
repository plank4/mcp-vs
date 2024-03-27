//Example ATmega2560 Project
//File: ATmega2560Project.c

//include this .c file's header file
#include "Controller.h"
# define DEBOUNCE_PERIOD 100

//static function prototypes, functions only called in this file

//Global initialisation
volatile uint32_t time_ms = 0;
volatile uint8_t time_s = 0;
volatile uint8_t time_m = 0;

int main(void)
{
  //variable declaration
  milliseconds_init();
  lcd_init();
  serial0_init();

  _delay_ms(20);
  //Timer Setup
  //WGM12 - WGM13 - Top Value ICR1 - ICIE1 - Prescaler CS10
  cli(); //DISABLE INTERRUPTS
  TCCR1A = 0;
  TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS10); //SET INTERRUPT ON CAPTURE FLAG / PRESCALER 1
  //WGM13, WGM12 set CTC and timer sequencing
  TCNT1 = 0;
  ICR1 = 15999; //SET TOP VALUE / (0.001*16000000/1)-1
  TIMSK1 = (1<<ICIE1); //INPUT CAPTURE ENABLE
  //Button interrupt setup
  DDRD &= ~(1<<DD0)&(1<<DD1); //INT0 INT1 INPUT MODE
  PORTD |= (1<<PD0)|(1<<PD1); //ENABLE PULLUPS
  EICRA |= (1<<ISC01)|(1<<ISC11); 
  EICRA &= ~(1<<ISC00)&(1<<ISC10); //FALLING EDGE TRIGGER
  EIMSK |= (1<<INT0)|(1<<INT1); //ENABLE INT0 INT1 INT2
  sei(); //ENABLE INTERRUPTS

  //main loop
  while(1){
    char serial_string[16] = {0}; //STRING TO PRINT
    //CHECKS FOR NUM OF SECONDS AND UPDATES MINUTES
    while(time_s >= 60){
      time_s -= 60;
      time_m += 1;
    }
    //CHECKS FOR NUM OF MILLIS AND UPDATES SECONDS
    while(time_ms >= 1000){
      time_ms -= 1000;
      time_s += 1;
    }
    sprintf(serial_string, "%d m %d s %d ms", time_m, time_s, time_ms); //FORMAT TIME VARIABLES INTO STRING
    serial0_print_string(serial_string); //PRINT STRING
  }return(1);
}//end main 

ISR(TIMER1_CAPT_vect){//TIMER INCREMENT
time_ms += 1;
}

ISR(INT0_vect){//BUTTON 0
uint32_t time0 = milliseconds_now(); //EXPERIMENTAL BETTER TRIGGER METHOD
static uint32_t prevTime0 = 0;
if(time0 > (prevTime0 + DEBOUNCE_PERIOD)){
  PORTA ^= (1<<PC0); //TOGGLE LED
  prevTime0 = time0;
  TIMSK1 ^= 1;
}
//_delay_ms(20); //REPLACE WITH THIS IN FAILURE
//PORTA ^= (1<<PA0);
}

ISR(INT1_vect){//BUTTON 1
uint32_t time1 = milliseconds_now(); //EXPERIMENTAL BETTER TRIGGER METHOD
static uint32_t prevTime1 = 0;
if(time1 > (prevTime1 + DEBOUNCE_PERIOD)){
  PORTA ^= (1<<PC1); //TOGGLE LED
  prevTime1 = time1;
  time_ms = 0, time_s = 0, time_m = 0;
  
}
//_delay_ms(20); //REPLACE WITH THIS IN FAILURE
//PORTA ^= (1<<PA1);
}
