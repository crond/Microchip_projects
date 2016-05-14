#include <htc.h>
//#include <pic18f45j50.h>
#include <stdio.h>
#include <string.h>
  
#define MASTER_WRITE   0b0
#define MASTER_READ    0b1
#define SLAVE_ADDR      0b01010101
/* 
 * USART Header file for PIC18F4550
 * For Enhanced USART module
 */

 

#define ASYNC_MODE 			0
#define SYNC_MASTER_MODE 	1
#define SYNC_SLAVE_MODE		2

#define TX_8_BIT	0
#define TX_9_BIT	1
 
void eusart_init(unsigned char usart_mode, char tx_mode, 
	unsigned long fosc, unsigned int baud);
void uart_send_byte(unsigned char byte);
unsigned char uart_recv_byte(void);
void uart_send_pkt(unsigned char *pkt, unsigned char size);
unsigned char uart_recv_pkt(unsigned char *pkt, unsigned char size);

 

int toggleLed(void);
int delay(int cnt);
int init(void);
int init_I2c();
int readData();
int initUart();
int start_I2C();
int sendToUart(const char *data);
int invokeStart();
int recvRomData();
int sendRomAddr();
 
