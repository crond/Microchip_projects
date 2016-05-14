  #include "dsPIC33f_i2c.h"

 char gBuffer[32];
 
void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void)
{
		memset(gBuffer,0,sizeof(gBuffer));
		sprintf(gBuffer,"IRQ: %d\n",I2C1STAT);
		sendToUart(gBuffer);
		if(I2C1STATbits.GCSTAT == 1)
		    sendToUart("General Call Received");
		if(I2C1STATbits.IWCOL == 1)    
		    sendToUart("Write in Prograss. Cant write new data now");
		if(I2C1STATbits.I2COV == 1){    
		    sendToUart("New Data Recvd,before reading earlier data");
		    I2C1STATbits.I2COV = 0 ;//Clear over flow bit, to recv further Data
		//    readData();
		}
		if(I2C1STATbits.P == 1)    
		    sendToUart("Stop Bit Detected");
		if(I2C1STATbits.S == 1)    
		    sendToUart("Start bit Detected");
		
		if(I2C1STATbits.R_W == 1)    
		    sendToUart("Master Going to Read");
		if(I2C1STATbits.R_W == 0){    
		    sendToUart("Master going to Write");
		}
		if(I2C1STATbits.RBF == 1){    
		    sendToUart("I2CRCV is Full");
	//	    readData();
		}
		
    	if( (I2C1STATbits.RBF == 1) && (I2C1STATbits.R_W == 1)){    
		    sendToUart("I2CRCV is Full. master is going to read");
		//    I2C1CONbits.SCLREL = 0; //Make the bus idle and lock
		//    writeData();
		//    I2C1CONbits.SCLREL = 1; 
		}
		if( (I2C1STATbits.RBF == 1) && (I2C1STATbits.R_W == 0)){    
		    sendToUart("I2CRCV is Full. master is going to write");
	//	    readData();
		}
		
		
		if(I2C1STATbits.D_A == 1)    
		    sendToUart("Last byte recvd is Data");
		if(I2C1STATbits.D_A == 0)    
		    sendToUart("Last byte recvd is Addr");
		if(I2C1STATbits.TBF == 1)    
		    sendToUart("transmit in prograss");
 
        IFS1bits.MI2C1IF = 0;		//Clear the DMA0 Interrupt Flag;

}	  
int initI2C()
{
	I2C1BRG=34;
	I2C1CON = 0x8000; //Enabling I2C module
	IEC1bits.MI2C1IE = 1;
  	IFS1bits.MI2C1IF = 0;
  	I2C1BRG=34;
	startI2C();
	return 0;
}
int startI2C()
{
	if( (checkBus()) == 1)
		sendToUart("Bus Busy\n");
	else
		sendToUart("Bus Idle\n");
		
	I2C1CONbits.SEN =1;//Initiate START condition
	while(I2C1CONbits.SEN == 1);
	sendToUart("SEN Bit ZERo\n");
    //Loading the slave Addr
	I2C1TRN = (0b01101000 << 1 ) | (0b0) ;
	while(I2C1STATbits.ACKSTAT==1);
	sendToUart("ACk Set");
	/*
	I2C1CONbits.SEN =1;//Initiate START condition
	while(I2C1CONbits.SEN == 1);
	sendToUart("SEN Bit ZERo\n");
	//Loading the addr
	I2C1TRN = (0x00 << 1 ) | (0b1) ;
	I2C1CONbits.PEN =1 ; //stop  condition
	while(I2C1STATbits.P == 1);
	sendToUart("Stop bit is set");
	*/
	return 0;	
}
unsigned char checkBus()
{
	if(I2C1STATbits.P == 1)
		return 1;
	else
		return 0;
	
}		
 