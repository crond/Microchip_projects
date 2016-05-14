#include <p33FJ64MC802.h>
#include <stdio.h>
#include <string.h>



//#define TEST_UART 1

 void tglePort(void);
  int delay(long int period);
  int initUART1() ;
  int	sendToUart(char *str);
  int	recvFromUart2();
  int	recvFromUart1();
  int initI2C();
  int startI2C();
  int readData();
   int readData();
  int writeData();
  int processReq(char addr);
 
unsigned char checkBus();