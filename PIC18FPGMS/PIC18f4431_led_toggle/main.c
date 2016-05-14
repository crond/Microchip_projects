#include "htc.h"

int  setSlaveAddr(unsigned char addr);
int delay(int cnt);
int init(void);
int toggleLed(void);

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
int  setSlaveAddr(unsigned char addr)
{
	unsigned char addrBkp=0;
	
	addrBkp = addr;
	
	
	SSPADD = addr;
	delay(100);
	addr = SSPADD;
	if(addr == addrBkp)
		return 0;
	else
		return -1;	
}	

int delay(int cnt)
{
	int i=0,j=0;
	for(i =0;i<cnt;i++)
	{
		for(j=0;j<cnt;j++)
		{
		}	
	}
	return 0;	
}
int init(void)
{
	//8Mhx interal osc
	OSCCON	= 0x73;
	
	//For LED
	PORTB	= 0x00;
	TRISB	= 0x00;
	
	//PIN ctrl for I2C
	TRISD	=0xFF;
	PORTD	=0xFF;
	
	//Clk -High,I2C Pin-Enble,Addr-7 bit
	SSPCON = 0x36;
	
	//Enable general,peripheral,ssp interrupts
	GIE=1;
	PEIE=1;
	SSPIE=1;
	
	return 0;
}		
int main()
{

	init();
	setSlaveAddr(0x1F);
	while(1)
	{
		if(SSPIF == 1)
		 	break;
		 	
	}
	SSPIF = 0;	
	toggleLed();

	return 0;

}
	