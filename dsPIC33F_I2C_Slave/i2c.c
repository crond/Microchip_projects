  #include "dsPIC33f_i2c.h"

/*
* 7-bit addr
* General call Enabled, to respon to general query
*/
 char gBuffer[32];
 char gData;
// #define BLOCK_ADDR_CHECK 1
#define VERBOSE 1
void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void)
{
	#ifdef VERBOSE	
		memset(gBuffer,0,sizeof(gBuffer));
		sprintf(gBuffer,"IRQ: %d\n",I2C1STAT);
		sendToUart(gBuffer); 
	#endif
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
//	I2C1BRG=300;
	I2C1CON = 0x8000; //Enabling I2C module
	I2C1CONbits.A10M=0b0; //I2C1ADD is 7-bit address
	#ifdef BLOCK_ADDR_CHECK
	    I2C1CONbits.IPMIEN =0b1;
	#endif
	I2C1CONbits.STREN = 0b1; //allow US to lock and release SCLREL
	I2C1CONbits.GCEN = 0b1;//Enabling General Call
	/*Disable Address Masking. 
	*Only Respond to configured single address.
	* If the masking is enabled, then the IPMIEN must be disabled.
	*/
	I2C1MSK = 0x0000;
	I2C1ADD=0b01010101; // Slave Addr - 85
	IEC1bits.MI2C1IE = 0b1;
  	IFS1bits.MI2C1IF = 0b0;
 // 	I2C1BRG=300;
	startI2C();
	return 0;
}
int readData()
{
    char ch=0;
    int data=0;
    memset(gBuffer,0,sizeof(gBuffer));
    //I2C1RCV = I2C1RSR; //done automaticallys
    data  = I2C1RCV;
    sprintf(gBuffer,"Recvd: %d\n",data);
	sendToUart(gBuffer);
	sscanf(gBuffer,"%c",&ch);
	if( (processReq(ch)) < 0)
	   return -1;
	return 0;
}
int processReq(char addr)
{
    char ch='A';
    
    for(ch='A';ch<='Z';ch++){
        if(ch == addr){
            gData = addr;
            return 0;
        }
    }
    
    return -1;
}
int writeData()
{
    sendToUart("write Data - Start");
    if( (checkBus()) == 0)
        sendToUart("Bus Busy");
    else
        sendToUart("Bus Free");
    I2C1TRN = gData; 
    
     sendToUart("write Data - End");
        
    return -1;
}
int startI2C()
{
	sendToUart("Slave Ready: Addr: 0b01010101");
    	while(1){
        tglePort();
        delay(10000);
    }
	return 0;	
}
unsigned char checkBus()
{
	if(I2C1STATbits.P == 1)
		return 1;
	else
		return 0;
	
}
 