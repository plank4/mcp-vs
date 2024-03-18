# MXEN2002 Mechatronic Microcontroller Project

### Laboratory A:  Downloading to the microcontroller, driving LEDs

Preliminary reading and reference material:
- Review previous programming notes and material, particularly C language
- The Arduino Mega page at http://arduino.cc/en/Main/ArduinoBoardMega
- GNU C reference: http://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html
- C reference: http://en.cppreference.com/w/c
- You may wish to look at the Atmel ATmega2560 Datasheet: http://www.atmel.com/Images/Atmel-2549-8-bit-AVR-Microcontroller-ATmega640-1280-1281-2560-2561_datasheet.pdf, but be warned it is large

The aim of this laboratory session is to familiarise yourselves with the equipment and software that we will be using for the rest of semester.  By the end of the session, you should have confirmed that the Microcontroller, kit board and development environment are all working correctly, and you should have practiced modifying, compiling, and downloading code to the ATMEGA in order to drive some output LEDs.

To begin, you should download the "mcp-master" code framework from the GitHub repository: https://github.com/mxeng/mcp

This code framework is the foundation of your labwork throughout semester. It contains two project, entitled "robot" and "controller": these simply enable you to program two microcontrollers from within the one code framework. At the end of semester, these two projects will be used to control the two microcontrollers: one mounted to your robot, and the other mounted on your controller. During the weekly labs, you will generally use just one of these projects.

For this lab, you can use the "robot" project, and all of the code you need to edit is contained in the file "robot.c". You may also wish to look at the header file "robot.h", but it shouldn't be necessary to edit it for this lab.

```c

int main(void)
{
  DDRA = 0xFF;//put PORTA into output mode
  PORTA = 0; 
  while(1)//main loop
  {
    _delay_ms(500);     //500 millisecond delay
    PORTA |= (1<<PA3);  // note here PA3 is just an alias for the number 3
                        // this line is equivalent to PORTA = PORTA | 0b00001000   which writes a HIGH to pin 3 of PORTA
    _delay_ms(500); 
    PORTA &= ~(1<<PA3); // this line is equivalent to PORTA = PORTA & (0b11110111)  which writes a HIGH to pin 3 of PORTA
  }
  return(1);
}//end main 
```

1. Calculate the value of current limiting resistor that would be required in series with an LED to be certain that no more than 25mA is sourced by the microcontroller. **(A1)**

2. Open the provided Microchip Studio project, replace the "int main(void)" function with the above code, compile the program, and download it to your board.

3. Use hookup wire to connect PortA (arduino pins 22-29) to eight LEDs on the breadboard, using the appropriate current-limiting resistors.
   Refer to the ArduinoMega schematic to check the correct pin locations.

4. Power up the board, and observe the results.

5. Describe the program functionality in your logbook. How is the written pin specified? What would happen if the | symbol was omitted in "PORTA |= (1<<PA3)"? What would happen if the & symbol was ommitted in "PORTA &= ~(1<<PA3)"? (hint: try it!) **(A2)**

6. Modify your program so that pins 2 and 5 of PORTA (pins 28 and 25 respectively) are blinked in sequence, explain what changes have been made to accomplish this. **(A3)**

7. Modify your program so that the LEDs are lit one at a time in sequence from PA0 to PA7 and then back again, explain what changes have been made to accomplish this. **(A4)**

8. Locate the pins on the Arduino that correspond to Ports A,B,C,K,L (all digital pins)

9. Test the program on at least one other port, explain what changes have been made to accomplish this. This will involve changing both the circuit and the program.  **(A5)**

10. Ensure that all of your work is comprehensively documented in your logbook, including pseudocode or flowcharts where necessary.  You should be able to use the logbook to reproduce the lab session work very quickly if required later. Show your logbook to a demonstator.
