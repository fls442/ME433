#include "nu32dip.h"    // constants, functions for startup and UART
#include <stdio.h>      // input/output library
#include <math.h>

#define PI 3.14159265
#define POINTS 100

void blink(int, int);   // blink the LEDs function
void delay(int ms);     // delay by ms miliseconds
void sendarray();       // function to call 

double data[100];
int i = 0;


int main(void) {
  NU32DIP_Startup();    // cache on, interrupts on, LED/button init, UART init
  
  for(i=0; i <= POINTS; i++){
    double sined = sin(((float)i/POINTS)*2*PI);
    data[i] = 3.3*sined*sined;
    }
  
//  for (int i=0; i<= POINTS; i++){
//      data[i] = ((float)i/100)*3.3;
  
  
  while(1){
      if ( PORTAbits.RA4 == 0){
          sendarray();
      }
    }
}


void delay(int ms){
    _CP0_SET_COUNT(0);                // set core timer counter to 0
    int target_ticks = 24000*ms;    // 24000 ticks per ms * ms
    while(_CP0_GET_COUNT()<target_ticks){
        // do nothing
    }   
}


void sendarray(){
    char message[100];
    int i=0;
    for(i=0; i<=100; i++){ 
          sprintf(message, "%f\r\n", data[i]);
          NU32DIP_WriteUART1(message);
          delay(1);         // delay 1ms
      }
      delay(5000);          //delay 5seconds
    
}
		
