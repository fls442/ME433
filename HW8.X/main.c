#include "font.h"
#include "i2c.h"
#include "mpu6050.h"
#include "nu32dip.h" // constants, functions for startup and UART
#include "ssd1306.h"

#include <stdio.h>



void blink(int, int); // blink the LEDs function

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    blink(2, 500);
    init_mpu6050();
    ssd1306_setup();
	
    /// COMMENTED FROM HERE
	// char array for the raw data
    unsigned char d[14];
	// floats to store the data
    float ax, ay, az, gx, gy, gz, t;
	
	// read whoami
    unsigned char who;
    who = whoami();
	// print whoami
    char m[100];
    sprintf(m, "0x%X\r\n", who);
    NU32DIP_WriteUART1(m);
	// if whoami is not 0x68, stuck in loop with LEDs on
//    if(who != 0x68){
//        while(1){
//            blink(1, 1000);
//        }
//    }
	// wait to print until you get a newline
//    char m_in[100];
//    NU32DIP_ReadUART1(m_in,100);
    //TO HERE
    
    while (1) {
		// use core timer for exactly 100Hz loop
        _CP0_SET_COUNT(0);
        blink(1, 100);
//        ssd1306_drawChar(10, 10, 0x3f);
        char msg[50];
        
       
        
      
        
                
        // read IMU
        burst_read_mpu6050(d);
		// convert data
        az = conv_zXL(d);
        
        // send the data to SSD1306
        sprintf(msg, "%f z accel", az);
        ssd1306_drawString(10,10, msg);
      
        
        float dt = _CP0_GET_COUNT()/48000; // should really check for overflow here
        sprintf(msg, "%f ms per frame", dt);
        ssd1306_drawString(10,20,msg);
        
       
        

        ssd1306_update();
    }
}

// blink the LEDs
void blink(int iterations, int time_ms) {
    int i;
    unsigned int t;
    for (i = 0; i < iterations; i++) {
        NU32DIP_GREEN = 0; // on
        NU32DIP_YELLOW = 1; // off
        t = _CP0_GET_COUNT(); // should really check for overflow here
        // the core timer ticks at half the SYSCLK, so 24000000 times per second
        // so each millisecond is 24000 ticks
        // wait half in each delay
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }

        NU32DIP_GREEN = 1; // off
        NU32DIP_YELLOW = 0; // on
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
    }
}

