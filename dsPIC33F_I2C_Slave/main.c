   #include "dsPIC33f_i2c.h"
  
   __CONFIG(FWDT, WDTDIS);
   
 //to check GIT  
void tglePort(void)
{
	static char ch=0;
	if(ch == 0)
	{
		ch =1;
		PORTBbits.RB4 = 0x0;
		PORTAbits.RA4 = 0x0;
	}
	else
	{   
		ch = 0;
		PORTBbits.RB4 = 0x1;
		PORTAbits.RA4 = 0x1;
	
	}
}
	
int delay(long int period)
{

	long int i=0,j=0;
	for(i=0;i<3;i++)
		for(j=0;j<period;j++);
	 
	return 0;
}
int initPorts(void)
{
	LATA  = 0x0000; 				// set latch levels
	TRISA = 0x0000; 				// set IO as outputs
	LATB  = 0x0000; 				// set latch levels
	TRISB = 0x0000; 				// set IO as outputs
	OSCCON=0x0680;
	
	TRISAbits.TRISA3 = 1;   //User Input switch- Defineing as input
	
	PORTBbits.RB4 = 0x1;   //Set High, which make LED to Turn OFF
	PORTAbits.RA4 = 0x1;   //User LEd, turn off
	

 	return 0;
}	   
   
int init()
{	
   	initPorts();
   	initUART1();
  	initI2C(); 
   	while(1)
	{
	   tglePort();
	    delay(5000);
	}
    return 0;	
} 
 

int main()
{
    init();
    while(1){
        
        delay(50);
    }
    return 0;
}