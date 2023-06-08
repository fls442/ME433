#include "nu32dip.h" // constants, functions for startup and UART
#include "utilities.h"


int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  Utilities_Startup();
  
  float cyc[50];
  float maxDC = 0.0125;
  float minDC = 0.075;
  float stepSize = (minDC - maxDC) / 49.0;
  
  
  for(int i = 0; i<50; i++){
      cyc[i] = minDC - i * stepSize;
  }
  while(1) {
      for(int i = 0; i<100; i++){
          set_DC(cyc[i]);
          delay(100);
      }

      
  }
}


		
