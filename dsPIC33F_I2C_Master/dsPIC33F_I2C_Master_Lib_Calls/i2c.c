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
 	unsigned int i2cConfig = (I2C1_ON & I2C1_IDLE_CON & I2C1_CLK_HLD & I2C1_IPMI_DIS & I2C1_7BIT_ADD &
                    I2C1_SLW_DIS & I2C1_SM_DIS & I2C1_GCALL_DIS & I2C1_STR_DIS &
                    I2C1_ACK & I2C1_ACK_EN & I2C1_RCV_EN &
                    I2C1_STOP_DIS & I2C1_RESTART_DIS & I2C1_START_DIS );
    EnableIntSI2C1;
    OpenI2C1( i2cConfig , 34 ); // Start
    I2C1ADD=0b01010101; // Slave Addr - 85
    IFS1bits.MI2C1IF = 0; // Clear the inturrupt flag for i2c1 port  
	return 0;
}
int doI2C()
{
    char ch=0;
    char tmpBuffer[32];
    StartI2C1();
    sendToUart("Starting I2C...\n\r"); 
    while(1){
        IdleI2C1();
        sendToUart("Idle Over\n\r");
        tglePort();
        ch =SlaveReadI2C1();
        memset(tmpBuffer,0,sizeof(tmpBuffer));
        sprintf(tmpBuffer,"I2C Data: %c\n\nr",ch);
        sendToUart(tmpBuffer); 
        tglePort();   
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
 