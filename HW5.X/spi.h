#ifndef SPI__H__
#define SPI__H__

#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "nu32dip.h"    // constants, functions for startup and UART


void initSPI();
unsigned char spi_io(unsigned char o);
void sendit(unsigned short bits);

#endif // SPI__H__