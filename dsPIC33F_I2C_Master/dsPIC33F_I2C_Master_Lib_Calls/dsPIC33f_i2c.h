#include <p33FJ64MC802.h>
#include <stdio.h>
#include <string.h>
#include <i2c.h>
#define MMA845x_WHO_AM_I_REG 0x0D
#define MMA845x_STATUS_REG  0x00
#define MMA845x_STATUS_SYSMOD   0x0B
#define MMA845x_CTRL_REG1 0x2A
#define MMA845x_CTRL_REG2 0x2B
#define CTRL_REG1_SET_DEVICE_ACTIVE_AND_DATA_RATE  ( 0x01 | 0x18 )
#define CTRL_REG2_SET_DEVICE_MODS      ( 0x02 ) 


//#define TEST_UART 1

 void tglePort(void);
  int delay(long int period);
  int initUART1() ;
  int	sendToUart(char *str);
  int	recvFromUart2();
  int	recvFromUart1();
  int initI2C();
  int doI2C();
  int readData();
  int writeData();
 
unsigned char checkBus();