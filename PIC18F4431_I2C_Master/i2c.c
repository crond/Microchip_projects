  	#include "pic18f4431_I2C_header.h"   
   
  	
  	unsigned char gRecvData=0,gExpectAck=0,gSendingReadCtrlBits=0,gSendingWriteCtrlBits=0,gSendingData=0;
  	char gBuffer[32];
  	
 
  	void interrupt ISR()
    {
        sendToUart("IRQ");
        if(SSPIE && SSPIF)
        {
            
            if(WCOL == 1){
                sendToUart("Write collision Detected. Write failed");
                WCOL=0;
            }
            if(SSPOV == 1){
                sendToUart("Receive Overflow");
                WCOL=0;
            }
            if(gRecvData && BF){
                //No need to clear BF, manually.
                gRecvData= 0;
                sendToUart("Data Recvd");
                 
            }
            if(SSPSTATbits.S == 0b1){
                sendToUart("Start Detected");
            }
            if(SSPSTATbits.P == 0b1){
                sendToUart("Stop Detected");
            }
            
            if(SSPSTATbits.BF == 0b1){
                sendToUart("SSPBUF is Full");
            }
            
            
            
        }
        SSPIF = 0b0; //Clear the Interrupt
    }
    
    #ifdef AAAA
    
    int recvRomData(){
        char recvCh=0;
        int recvVal=0;
        
        recvVal = SSPSR;
        memset(gBuffer,0,sizeof(gBuffer));
        sprintf(gBuffer,"%d",recvVal);
        sscanf(gBuffer,"%c",&recvCh);
        memset(gBuffer,0,sizeof(gBuffer));
        sprintf(gBuffer,"dec=%d hex=%x ch=%c",recvCh);
        sendToUart(gBuffer);
        
        invokeStart();
        return 0;
    }
    int sendRomAddr()
    {
        static char addr=0x41;
        gSendingData =1;
        
        //loading data
        SSPBUF = addr;
        
        if(addr <= 0x5A)
            addr = 0x41;
        else
            addr = addr + 0x01;
            
        return 0;
    }
    #endif
    
    int invokeStop()
  	{
  	    //ToDo: Check for Bus Idle state
  	    
  	    
  	    
  	    
  	    
  	    return 0;
  	}
  	
  	int invokeStart()
  	{
  	    //ToDo: Check for Bus Idle state
  	    SSPCONbits.SSPEN=0b1; //Start Condition
  	    gSendingWriteCtrlBits=1;
  	    while(SSPCONbits.SSPEN == 0);
  	        sendToUart("SSPEN 0 "); 
  	    if(SSPSTATbits.S == 0b1){
                sendToUart("Start Detected");
        }
        else
            sendToUart("Start Finished");
            
        if(SSPSTATbits.P == 0b1){
             sendToUart("Stop Detected");
        }
        
  	    
  	    
  	    return 0;
  	}
  	
  	int start_I2C()
  	{
  	    sendToUart("Starting I2C");
  	    if(SSPIF == 0)
  	        sendToUart("SSPIF 0 ");
  	    else
  	        sendToUart("SSPIF 1");
  	    SSPIF = 0;
  	    invokeStart();
  	    SSPBUF = (SLAVE_ADDR << 1) | MASTER_WRITE;
  	    if(SSPSTATbits.BF == 0b1){
                sendToUart("BF is 1");
            }
        else
           sendToUart("BF is 0"); 
  	    
  	    invokeStop();
  	    
  	    return 0;
  	}
 
  	
  	int init_I2C()
    {
       
    	//  Bind  Rd2,Rd3 to I2C Operations in config bits window, field name CONFIG3H
    	 //PIN ctrl for I2C;PORTD is used, RD2-SDA,RD3-SCL
    	TRISD	=0xFF;
    	
    	//For Master mode, make RD2-3 zero
    	TRISDbits.RD2=0;
    	TRISDbits.RD3=0;
    	PORTDbits.RD2=0;
    	PORTDbits.RD3=0;
    	SSPADD=0x0A;
    	SSPSTATbits.CKE=0b0;
    	//setting bits 3:0 as 1011 to En I2C with start/stop interrupts
    	SSPCONbits.SSPM3 = 0b1;
    	SSPCONbits.SSPM2 = 0b0;
    	SSPCONbits.SSPM1 = 0b1;
    	SSPCONbits.SSPM0 = 0b1;
    	
    	SSPIE=1;
     
    	
    
        return 0;
    }
   