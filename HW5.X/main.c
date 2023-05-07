#include "nu32dip.h"    // constants, functions for startup and UART
#include <math.h>
//#include "spi.h"

#define PI 3.14159265
#define POINTS 100          // data points per sine wave

void delay(int ms);

int main(void) {
  unsigned int vsin, vtri, i=0;
  float rads, prog, amp=1023/2;
  unsigned short a=0b0111<<12, b=0b1111<<12, send=0;
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  //initSPI();
 
  TRISBbits.TRISB6 = 0;          //PIN B6 flips for debugging
  LATBbits.LATB6 = 1;            //
  
  while (1) {
      if(i>POINTS){
          i=0;
      }
      prog = i/POINTS;
      rads = (2*PI)*prog;
      if(i%2==0){
          LATBbits.LATB6 = 0;
      }
      else{
          LATBbits.LATB6 = 1;
      }
      
      // calc sine voltage (0-1023))
      vsin = amp + amp*sin(rads);
      // build sine SPI bits for channel A
      send = a|(vsin<<2);
      // send sine SPI
      //sendit(send);
      
      // calc tri voltage
      if(i<50){
          vtri = prog*2*amp;
      }
      else{
          vtri = (-1*prog*2*amp) + (2*amp);
      }
      // build tri SPI bits
      send = a|(vtri<<2);
      // send tri SPI
      //sendit(send);
      //delay 5 ms to maintain 200 pts/second for 2Hz sine wave
      i++; 
      delay(5);
  }
}


//delay in mili seconds
void delay(int ms){
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() <(ms*24*10^3)){;} //do nothing
}