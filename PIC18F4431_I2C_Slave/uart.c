 #include "pic18f4431_I2C_header.h"


void eusart_init(unsigned char usart_mode, char tx_mode, 
	unsigned long fosc, unsigned int baud)
{
//	TRISC6 = 0;		// UART Tx enable
//	TRISC7 = 1;		// UART Rx enable
	switch(usart_mode)
	{
		case ASYNC_MODE:
		{
			BRG16 = 1;
			 
			SPBRG = (int)(fosc/(4UL * baud) -1);	// Formula varies based on UART settings
			TXSTA = 0x24;	// 8-Bit mode, Enable TX
			RCSTA = 0x90;	// Enable serial comm, 9-Bit mode, Enables continous RX
			break;
		}
		case SYNC_MASTER_MODE:
		{
			break;
		}
		case SYNC_SLAVE_MODE:
		{
			break;
		}		
	}
}

void uart_send_byte(unsigned char byte)
{
	while(!TXIF)
	{
		continue;
	}
	TXREG = byte;
}

unsigned char uart_recv_byte(void)
{
	while(!RCIF)
	{
		continue;
	}
	return RCREG;
}

int sendToUart(const char *pkt)
{
	int i;
	int size=0;
	
	size = strlen(pkt);
	for(i = 0; i < size; i++)
	{
		uart_send_byte(pkt[i]);
		delay(10);
	}
	uart_send_byte('\n');
	return 0;
}

unsigned char uart_recv_pkt(unsigned char *pkt, unsigned char size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		pkt[i] = uart_recv_byte();
	}
	return size;
}

