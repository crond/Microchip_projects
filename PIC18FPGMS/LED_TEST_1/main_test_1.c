#include <htc.h>
//__CONFIG(1, IESODIS & FCMDIS & RCIO);
//__CONFIG(2, BORV18 & BOREN & PWRTDIS & WDTPS32K & WDTDIS);
//__CONFIG(3, MCLRDIS & HFSTABLE);
//__CONFIG(4, LVPDIS & STVRDIS);

void delay(unsigned int count);
unsigned char counter=0;
void anuche_init()
{
 
	OSCCON = 0x52;
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;	
	TRISD = 0x00;
	WDTCON = 0x00;
}

void do_timer()
{
   T0PS0=1; //Prescaler is divide by 256

   T0PS1=1;
   T0PS2=1;

   PSA=0;      //Timer Clock Source is from Prescaler

   T0CS=0;     //Prescaler gets clock from FCPU (5MHz)

   T08BIT=1;   //8 BIT MODE

   TMR0IE=1;   //Enable TIMER0 Interrupt
   PEIE=1;     //Enable Peripheral Interrupt

   GIE=1;      //Enable INTs globally

   TMR0ON=1;      //Now start the timer!

    

  // while(1);   //Sit Idle Timer will do every thing!
}

void interrupt ISR()
{
   //Check if it is TMR0 Overflow ISR
   static int flag=0;
   if(TMR0IE && TMR0IF)
   {
      //TMR0 Overflow ISR
      counter++;  //Increment Over Flow Counter
/*********************************************************
1. prescale =111, and counter=50 times overflow will give 
    6.63 seconds of delay
2. prescale =111, and counter=40 times overflow will give 
    5.32 seconds of delay
3. prescale =111, and counter=30 times overflow will give 
    4.3 seconds of delay
4. prescale =111, and counter=10 times overflow will give 
    1.32 seconds of delay



************************************************************/
   if(counter==4)   
   {
        //Toggle PORTA (LED)
        if(flag == 0)
        	PORTA =0xAA;
	 else	 
		PORTA = ~PORTA;
   }
	else if(counter == 8)
	{
		if(flag == 0)
         	PORTC =0xAA;
		else	 
			PORTC = ~PORTC;
	}
	else if(counter == 12)
	{
		if(flag == 0)
        {
		 	PORTD =0xAA;
			flag =1;
		}
		else	 
		{
			PORTD = ~PORTD;
			flag =0;
		}
		 counter=0;  //Reset Counter
	}
		

      //Clear Flag
      TMR0IF=0;
   }
}

void main()
{
	int i,k =5;
	int j = 5;
	anuche_init();	
	while(1)
	{
		PORTA = 0xAA;
		delay(3000);
		PORTA = ~PORTA;
		delay(3000);
		
		PORTC = 0xAA;
		delay(3000);
		PORTC = ~PORTC;
		delay(3000);

		PORTD = 0xAA;
		delay(3000);
		PORTD = ~PORTD;
		delay(3000);
		
	/*	PORTB = 0xAA;	
		delay(3000);
		PORTB = 0x5A;
		delay(3000);*/
     

		
	}
    do_timer();
	while(1);
/*	PORTD = 0x01;
	while(k--)
	{
		for(j = 0; j < 7; j++)
		{
			delay(3000);
			PORTD <<= 1;
			delay(3000);
		}
		for(j = 0; j < 7; j++)
		{
			delay(3000);
			PORTD >>= 1;
			delay(3000);
		}
	}
	PORTD = 0x00;
	delay(5000);
	i = 5000;
	j = -500;
	while(1)
	{
		if(i == 1000)
		{
			j = 500;
		}
		else if(i == 5000)
		{
			j = -500;
		}
		i = i + j;
		PORTD = 0x81;
		delay(i);
		PORTD = 0x42;
		delay(i);
		PORTD = 0x24;
		delay(i);
		
		PORTD = 0x18;
		delay(i);
		
		PORTD = 0x24;
		delay(i);
		PORTD = 0x42;
		delay(i);
		PORTD = 0x81;
		delay(i);
		
		//--------------
		
		PORTD = 0x81;
		delay(i);
		PORTD |= 0x42;
		delay(i);
		PORTD |= 0x24;
		delay(i);
		
		PORTD |= 0x18;
		delay(i);
		
		PORTD = 0xE7;
		delay(i);
		PORTD = 0xC3;
		delay(i);
		PORTD = 0x81;
		delay(i);
	}*/
}

void delay(unsigned int count)
{
	unsigned int i;
	for(i = 0; i < count; i++);
}
