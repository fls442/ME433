#ifndef UTILITIES__H__
#define UTILITIES__H__

#include <xc.h> // processor SFR definitions
#include <sys/attribs.h> // __ISR macro
#include "nu32dip.h"

#define PBCLK 80000000
#define PLTPTS 100

void Utilities_Startup();   // set MODE idle, initialize ADC
int get_mode();
void set_mode(int numb);
void set_DC(float DC);
float get_DC();
void set_dir(int d);
int get_dir();
void gen_ref_plot();

enum mode_t {IDLE, PWM, ITEST, HOLD, TRACK}; // the definition

#endif // ENCODER__H__
