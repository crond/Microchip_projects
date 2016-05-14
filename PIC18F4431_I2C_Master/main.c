#include "pic18f4431_I2C_header.h"   

    int toggleLed(void)
    {
    	PORTB = 0x00;
    	while(1)
    	{
    		PORTB = 0xAA;
    		delay(200);
    		PORTB	= 0x00;
    		delay(200);
    	}
    	return 0;	
    }	
    	
    
    int delay(int cnt)
    {
    	int i=0,j=0;
    	for(i =0;i<3;i++)
    	{
    		for(j=0;j<cnt;j++)
    		{
    		}	
    	}
    	return 0;	
    }
    int init(void)
    {
    	//4Mhx interal osc
    	OSCCON	= 0x63;
    		ANSEL0	= 0x00;
    	//For LED
    	PORTB	= 0x00;
    	TRISB	= 0x00;
        TRISC	= 0x80;
        //Enable general,peripheral,ssp interrupts
    	GIE=1;
    	PEIE=1;
    	eusart_init(ASYNC_MODE, TX_8_BIT, 4000000UL, 9600);
    	
    	init_I2C();
        
        /*
        * ToDo:
        * 1. BRG calculation
        * oper voltage calcualton
        * I2C commu freq value
        */
        return 0;
    }		
  
    int main()
    {
        init();
        start_I2C();
         
        while(1){
             
            delay(5000);
        }
        return 0;
    }