#include "nu32dip.h"    // constants, functions for startup and UART
#include <math.h>
#include "spi.h"

#define PI 3.14159265

void delay(int ms);

int main(void) {
  unsigned int vsin, vtri, i=0;
  double rads, prog, amp=511.5, points=100, m=20.46;
  unsigned short a=0b0111<<12, b=0b1111<<12, senda=0, sendb=0;
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  initSPI();
 
  TRISBbits.TRISB6 = 0;          //PIN B6 flips for debugging
  LATBbits.LATB6 = 1;            //
  
  while (1) {
      if(i>points){
          i=0;
      }
      rads = (2*PI)*(i/points);
      
//      if(i%2==0){
//          LATBbits.LATB6 = 0;
//      }
//      else{
//          LATBbits.LATB6 = 1;
//      }
      
     
      vsin = amp + amp*sin(rads);    // calc sine voltage (0-1023))
      senda = a|(vsin<<2);           // build sine SPI bits for channel A
      // send sine SPI
      sendit(senda);
      
      // calc tri voltage
      if(i<50){vtri = m*i;}
      else{vtri = (-1*m*i) + (4*amp);}
      if(vtri<0){vtri=1023;}
      if(vtri>1023){vtri=0;}
      
      // build tri SPI bits
      sendb = b|(vtri<<2);
      // send tri SPI
      sendit(sendb);
      //delay 5 ms to maintain 200 pts/second for 2Hz sine wave
      i++; 
      delay(3);
  }
}


//delay in mili seconds
void delay(int ms){
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() <(ms*24*pow(10, 3))){;} //do nothing
}