#include "utilities.h"
#include <stdio.h>


volatile enum mode_t mode; // the declaration
volatile float duty_cycle = 0.0; // duty cycle float
volatile int dir = 1;      // direction bit initially zero
static float kp, ki;       // PI control gains

float refarray[PLTPTS], curarray[PLTPTS];


void Utilities_Startup(){
  __builtin_disable_interrupts();

  duty_cycle = 0.25;
  
  RPB15Rbits.RPB15R=0b0101;   // make pin b15 OC1
  
 // configure Timer2 & TMR2 Interrupt for 5kHz
  T2CONbits.TCKPS = 0b100;    // Timer2 prescaler (1:16)
  TMR2 = 0;                   // initial TMR2 count is 0
  PR2 = 60000-1;           // PR2 will rollover (and generate interrupt) at 5kHz

 // configure OC1(pin D0) to use timer3 & have duty cycle
  OC1CONbits.OCM = 0b110;     // PWM mode without fault pin; other OC1CON bits are defaults
  OC1CONbits.OCTSEL = 0;      // Use timer2
  OC1RS = (PR2+1)*duty_cycle;          // OCR = (duty_cycle)*PR
  OC1R  = (PR2+1)*duty_cycle;          // initialize before turning OC1 on; afterward it is read-only
  
  
 // configure pin  as Digital Output
  TRISBbits.TRISB14 = 0;       // Pin b14 is digital output
  LATBbits.LATB14 = 1;         // initially high value output


// turn on timers & OCs
  T2CONbits.ON = 1;           // turn on Timer2
  OC1CONbits.ON = 1;          // turn on OC1 

  __builtin_enable_interrupts();
}


// Supporting functions



void set_DC(float DC){
  duty_cycle = DC;
  LATBbits.LATB14 = get_dir();         // direction output 
  OC1RS = DC*(PR3+1);             // adjust OC1Rs for PWM
}

float get_DC(){
  return duty_cycle;
}

void set_dir(int d){  // set direction variable
  dir = d;
}

int get_dir(){
  return dir;
}

// void set_PWM(float DC){



// }


void set_mode(int numb){
  mode = numb;
}

int get_mode(){
  return mode;
}