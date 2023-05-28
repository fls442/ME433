#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c.h"

unsigned char MCPw = 0b01000000 , MCPr = 0b01000001;


void blink(int, int); // blink the LEDs function
void heartbeat();     // this just gonna call the blink function
void delay(int ms);     // delay by ms miliseconds

int main(void) {
  NU32DIP_Startup();    // cache on, interrupts on, LED/button init, UART init
  i2c_master_setup();   // turn on ye i2c
  i2cWrite(MCPw, 0x00, 0b01111111); // MAKE GP0 INPUT, MAKE GP7 OUTPUT
  
// Little test sequence
  GP7on(); 
  delay(1000);
  GP7off();
  unsigned char pushed;
  
  while (1) {
      GP7off();
      
      pushed = GP0read();
      int onoff = !(pushed && 0b1);
      
      if(onoff){GP7on();}
      heartbeat();
  }

}


// blink the LEDs
void blink(int iterations, int time_ms){
	int i;
	unsigned int t;
	for (i=0; i< iterations; i++){
		NU32DIP_GREEN = 0; // on
		NU32DIP_YELLOW = 1; // off
		t = _CP0_GET_COUNT(); // should really check for overflow here
		// the core timer ticks at half the SYSCLK, so 24000000 times per second
		// so each millisecond is 24000 ticks
		// wait half in each delay
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
		
		NU32DIP_GREEN = 1; // off
		NU32DIP_YELLOW = 0; // on
		t = _CP0_GET_COUNT(); // should really check for overflow here
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
	}
}
		
void delay(int ms){
    _CP0_SET_COUNT(0);                // set core timer counter to 0
    int target_ticks = 24000*ms;    // 24000 ticks per ms * ms
    while(_CP0_GET_COUNT()<target_ticks){
        // do nothing
    }   
}

void heartbeat(){
    blink(1, 600);
}