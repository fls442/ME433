#ifndef I2C_H__
#define I2C_H__
// Header file for i2c_master_noint.c
// helps implement use I2C1 as a master without using interrupts
#include <xc.h>

#define WRITE 0b01000000
#define READ  0b01000001


void i2c_master_setup(void); // set up I2C1 as master
void i2c_master_start(void); // send a START signal
void i2c_master_restart(void); // send a RESTART signal
void i2c_master_send(unsigned char byte); // send a byte (either an address or data)
unsigned char i2c_master_recv(void); // receive a byte of data
void i2c_master_ack(int val); // send an ACK (0) or NACK (1)
void i2c_master_stop(void); // send a stop


// Below are the custom functions I'm writing
void i2cWrite(unsigned char add, unsigned char reg, unsigned char val);
void GP7on(void);
void GP7off(void);
unsigned char i2cRead(unsigned char addW, unsigned char addR, unsigned char reg);
unsigned char GP0read(void);



#endif
