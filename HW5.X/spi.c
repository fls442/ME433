#include "spi.h"

// initialize SPI1
void initSPI() {
    // Pin B14 has to be SCK1
    //
    // Turn off analog pins
    //...
    // Make RPB13 Output for CS pin
    TRISBbits.TRISB13 = 0;          //B13 is output pin to be CS
    LATBbits.LATB13 = 1;            //B13 starts high bc CS is active low
    //...
    // Set SDO1
    RPB11Rbits.RPB11R = 0b0011;     //Pin B11 is SDO output
    
    // Set SDI1
    SDI1Rbits.SDI1R = 0b0100;       //Pin B8 is SDI input

    // setup SPI1
    SPI1CON = 0; // turn off the spi module and reset it
    SPI1BUF; // clear the rx buffer by reading from it
    SPI1BRG = 1000; // 1000 for 24kHz, 1 for 12MHz; // baud rate to 10 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0; // clear the overflow bit
    SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1; // master operation
    SPI1CONbits.ON = 1; // turn on spi 
}


// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}

//toggle the CS pin, send first 8 bits over SPI, send second bits
// via SPI, toggle the CS pin
void sendit(unsigned short bits){
    LATBbits.LATB13 = 0;      // chip select pin active low
    spi_io(bits>>8);
    spi_io(bits);
    LATBbits.LATB13 = 1;      // chip select pin idles high)
}

