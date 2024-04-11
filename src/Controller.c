//Example ATmega2560 Project
//File: ATmega2560Project.c

//include this .c file's header file
#include "Controller.h"
# define DEBOUNCE_PERIOD 100

//static function prototypes, functions only called in this file
int map(uint16_t adcVal, uint8_t joyMin, uint16_t joyMax, uint16_t compMin, uint16_t compMax){
  return((adcVal - joyMin)*(compMax-compMin)/(joyMax-joyMin)+compMin);
}

int main(void){
  //variable declarations
  adc_init();
  
  int16_t adc1 = 0; //Joystick 1
  int16_t adc2 = 0; //Joystick 2
  uint16_t comp1 = 0;
  uint16_t comp2 = 0;

  //Timer Setup
  //PWM Req: 50Hz, pulse duration 1000-2000us
  TCCR1A = (1<<COM1A1)|(1<<COM1B1);
  TCCR1B = (1<<WGM13)|(1<<CS11); //Mode 8 Prescaler 8 (PWM, Phase and Freq Correct, ICR1 Top Value)
  ICR1 =20000; //Top Value with N=8, for f=50Hz
  DDRB |= (1<<PB5)|(1<<PB6); //OCR1A,0CR1B output PWMs **UNCLEAR IF THIS IS CORRECT
  OCR1A = comp1; //range from 8000 to 16000
  OCR1B = comp2; 
  
  _delay_ms(20);
  
  while(1){ //Main Loop
  adc1 = adc_read(3); //Read Voltage at ADC3 - returns 10bit value
  adc2 = adc_read(4); //Read Voltage at ADC4 - returns 10bit value

  comp1= adc1+1000;
  comp2= adc2+1000;

  //comp1 ()= map(adc1, 0, 1023, 1000, 2000); //Maps adc values to comparison values for servo
  //comp2 = map(adc2, 0, 1023, 1000, 2000);
  OCR1A = comp1; //range from 8000 to 16000
  OCR1B = comp2;
  }

}