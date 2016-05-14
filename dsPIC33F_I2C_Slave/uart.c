 #include "dsPIC33f_i2c.h"


void __attribute__ ((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
	IFS0bits.U1TXIF = 0;
}

void __attribute__ ((interrupt, no_auto_psv)) _U1RXInterrupt(void) {

	IFS0bits.U1RXIF = 0;
	

}
int initUART1() 
{
	
	RPINR18 = 0x000D; //Rx ,RB-15
	RPOR7 |= 0x0003;   //Tx, RB-14
	
	
	TRISBbits.TRISB15	= 1; //setting Rx as input
	IEC0bits.U1TXIE=0b1;
	IEC0bits.U1RXIE=0b1;
	
//	U1BRG = 1; //46; //((7370000/2)L/(16L*115200L))-1L;
	U1BRG = 23; //46; //((7370000/2)L/(16L*9600L))-1L;
	
	/********** Code from MPLAB Reference*******************************************/
	// configure U1MODE
	U1MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	//U1MODEbits.notimplemented;	// Bit14
	U1MODEbits.USIDL = 0;	// Bit13 Continue in Idle
	U1MODEbits.IREN = 0;	// Bit12 No IR translation
	U1MODEbits.RTSMD = 0;	// Bit11 Simplex Mode
	//U1MODEbits.notimplemented;	// Bit10
	U1MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
	U1MODEbits.WAKE = 0;	// Bit7 No Wake up (since we don't sleep here)
	U1MODEbits.LPBACK = 0;	// Bit6 No Loop Back
	U1MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')
	U1MODEbits.URXINV = 0;	// Bit4 IdleState = 1  (for dsPIC)
	U1MODEbits.BRGH = 0;	// Bit3 16 clocks per bit period
	U1MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
	U1MODEbits.STSEL = 0;	// Bit0 One Stop Bit
	
	// Load all values in for U1STA SFR
	U1STAbits.UTXISEL1 = 0;	//Bit15 Int when Char is transferred (1/2 config!)
	U1STAbits.UTXINV = 0;	//Bit14 N/A, IRDA config
	U1STAbits.UTXISEL0 = 0;	//Bit13 Other half of Bit15
	//U1STAbits.notimplemented = 0;	//Bit12
	U1STAbits.UTXBRK = 0;	//Bit11 Disabled
	U1STAbits.UTXEN = 0;	//Bit10 TX pins controlled by periph
	U1STAbits.UTXBF = 0;	//Bit9 *Read Only Bit*
	U1STAbits.TRMT = 0;	//Bit8 *Read Only bit*
	U1STAbits.URXISEL = 0;	//Bits6,7 Int. on character recieved
	U1STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
	U1STAbits.RIDLE = 0;	//Bit4 *Read Only Bit*
	U1STAbits.PERR = 0;		//Bit3 *Read Only Bit*
	U1STAbits.FERR = 0;		//Bit2 *Read Only Bit*
	U1STAbits.OERR = 0;		//Bit1 *Read Only Bit*
	U1STAbits.URXDA = 0;	//Bit0 *Read Only Bit*
	U1MODEbits.UARTEN = 1;	// And turn the peripheral on
	U1STAbits.UTXEN = 1;
/*********************************************************************************/
 #ifdef TEST_UART
 	char buffer[32];
 	while(1)
 	{
		memset(buffer,0,32);
		sprintf(buffer,"OC:0x%x\n",1000);
		sendToUart(buffer);
		delay(10000);
		tglePort();	
			
	}
 
 #endif
 return 0;
}

void InitUART2() 
{
/********** Code from MPLAB Reference*******************************************/
	// configure U2MODE
	U2MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	//U2MODEbits.notimplemented;	// Bit14
	U2MODEbits.USIDL = 0;	// Bit13 Continue in Idle
	U2MODEbits.IREN = 0;	// Bit12 No IR translation
	U2MODEbits.RTSMD = 0;	// Bit11 Simplex Mode
	//U2MODEbits.notimplemented;	// Bit10
	U2MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
	U2MODEbits.WAKE = 0;	// Bit7 No Wake up (since we don't sleep here)
	U2MODEbits.LPBACK = 0;	// Bit6 No Loop Back
	U2MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')
	U2MODEbits.URXINV = 0;	// Bit4 IdleState = 1  (for dsPIC)
	U2MODEbits.BRGH = 0;	// Bit3 16 clocks per bit period
	U2MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
	U2MODEbits.STSEL = 0;	// Bit0 One Stop Bit
	
	 
 	U2BRG = 23;//(8000000L/(16L*9600L))-1L;
	// Load all values in for U2STA SFR
	U2STAbits.UTXISEL1 = 0;	//Bit15 Int when Char is transferred (1/2 config!)
	U2STAbits.UTXINV = 0;	//Bit14 N/A, IRDA config
	U2STAbits.UTXISEL0 = 0;	//Bit13 Other half of Bit15
	//U2STAbits.notimplemented = 0;	//Bit12
	U2STAbits.UTXBRK = 0;	//Bit11 Disabled
	U2STAbits.UTXEN = 0;	//Bit10 TX pins controlled by periph
	U2STAbits.UTXBF = 0;	//Bit9 *Read Only Bit*
	U2STAbits.TRMT = 0;	//Bit8 *Read Only bit*
	U2STAbits.URXISEL = 0;	//Bits6,7 Int. on character recieved
	U2STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
	U2STAbits.RIDLE = 0;	//Bit4 *Read Only Bit*
	U2STAbits.PERR = 0;		//Bit3 *Read Only Bit*
	U2STAbits.FERR = 0;		//Bit2 *Read Only Bit*
	U2STAbits.OERR = 0;		//Bit1 *Read Only Bit*
	U2STAbits.URXDA = 0;	//Bit0 *Read Only Bit*
	
	U2MODEbits.UARTEN = 1;	// And turn the peripheral on

	U2STAbits.UTXEN = 1;
/*********************************************************************************/
	return ;
 
}

int	sendToUart(char *str)
{
	 int i=0,len=0;
	 len =strlen(str);
	 for(i=0;i<len;i++)
	 {
	 //	U2TXREG=str[i];
	 	U1TXREG=str[i];
	 	delay(700);
	 
	 }
	 U1TXREG='\n';
	 delay(700);
	 U1TXREG='\r';
//	 PORTC = 0xffff;
	
	 return 0;
}
int	recvFromUart2()
{
	char ch;
	while(1)
	{
//		PORTC = 0x0000;
		while(U2STAbits.URXDA == 1)
		{
			ch = U2RXREG;
	//		sendToUart(&ch);
		//	delay(DEF_SERPORT_DLY-10);
		}
//		PORTC = 0xffff;
	
	}
	return 0;
}
int	recvFromUart1()
{
	char ch;
	sendToUart("zzz");
	while(1)
	{
//		PORTC = 0x0000;
		while(U1STAbits.URXDA == 1)
		{
			ch = U1RXREG;
			sendToUart("zzz");
		//	delay(DEF_SERPORT_DLY-10);
		}
//		PORTC = 0xffff;
	
	}
	return 0;
}
