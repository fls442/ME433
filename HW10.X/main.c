#include "nu32dip.h" // constants, functions for startup and UART
#include "ws2812b.h"




int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  ws2812b_setup();
  int numLED = 8;
  wsColor LED[numLED];
  float hue[numLED];
  float div = 360/(numLED*4);
  
  for(int ii=0;ii<numLED;ii++){
      hue[ii] = ii*div;
  }
 
  while (1) {
    
      for(int i=0;i<numLED;i++){
        hue[i] += div;
        if(hue[i]>360){
            hue[i]=0;
        }
      }
      
      for(int j=0;j<numLED;j++){
      LED[j] = HSBtoRGB(hue[j], 0.75, 25);
      }
      ws2812b_setColor(LED, 8);
      delay(50);
  }
  

}


		
