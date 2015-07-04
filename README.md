# note
  '''

  printf("%d<\n",   atoi(strncpy(jetton_tmp,5+strstr(src,p1->name),4))  );  // p->name+5 == jetton 

  '''

hello everyone,today we will hava a discuss 


/*
 * main.c
 */
//******************************************************************************
#include "msp430g2553.h"

#define     LED1                  BIT0
#define     LED2                  BIT6
#define     LED_DIR               P1DIR
#define     LED_OUT               P1OUT

/*long VolMeasured[8];
unsigned char VolMeasuredPosition=0;
long VolAverage;
*/

void InitializeLeds(void);             //³õÊŒ»¯LED£¬Ê¹LED2ºÍLED1¶ŒÃð
void InitializeClocks(void);           //³õÊŒ»¯Ê±ÖÓ
void ConfigureAdc(void);               //ÅäÖÃADC

void main(void)
{
  InitializeLeds();
  InitializeClocks();
  ConfigureAdc();

  while(1)
  {
	  ADC10CTL0 |= ENC + ADC10SC;               //¿ªÊŒ²ÉÑùºÍ×ª»»
	  __bis_SR_register(CPUOFF + GIE);          //œøÈëµÍ¹ŠºÄÄ£Êœ
	 /* VolMeasured[VolMeasuredPosition++] = ADC10MEM;
	     if (VolMeasuredPosition == 8)
	       VolMeasuredPosition = 0;
	     VolAverage = 0;
	     for (i = 0; i < 8; i++)
	       VolAverage += VolMeasured[i];
	     VolAverage >>= 3;
      */
	     if(ADC10MEM>0X2ff)                    //ÈôµçÑ¹ŽóÓÚ2.67V£¬LED2ºÍLED1È«ÁÁ
	     {
	    	  LED_OUT |= (LED1 + LED2);
	     }
	     else if(ADC10MEM>0X0ff)              //ÈôµçÑ¹Ð¡ÓÚ2.67VÇÒŽóÓÚ0.889V£¬LED2ÁÁLED1Ãð
	     {
	    	  LED_OUT &= ~LED1 ;
	    	  LED_OUT |=  LED2 ;
	     }
	     else                                 //ÈôµçÑ¹Ð¡ÓÚ0.889V£¬LED2ÃðLED1ÁÁ
		 {
	    	  LED_OUT &= ~LED2 ;
	    	  LED_OUT |=  LED1 ;
		 }
  }
}

void InitializeLeds(void)
{
  LED_DIR |= LED1 + LED2;
  LED_OUT &= ~(LED1 + LED2);
}

void InitializeClocks(void)
{
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  BCSCTL2 &= ~(DIVS_3);
}

void ConfigureAdc(void)
{
 /* P1SEL|=BIT4;
  P1DIR&=~BIT4; */
  ADC10CTL1 = INCH_4 + ADC10DIV_3;           // Ñ¡ÔñP1.4×ö²ÉÑùÊäÈë
  ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE;//ÉèÖÃ²ÉÑù±£³ÖÊ±Œä¡¢Žò¿ªADC10.ÖÐ¶ÏÊ¹ÄÜ
 // __delay_cycles(1000);                     // Wait for ADC Ref to settle
/*  ADC10CTL0 |= ENC + ADC10SC;               // Sampling and conversion start
  __bis_SR_register(CPUOFF + GIE);          // LPM0 with interrupts enabled
  tempCalibrated = ADC10MEM;
  for (i=0; i < 8; i++)
    tempMeasured[i] = tempCalibrated;
  tempAverage = tempCalibrated;
*/
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // ÍË³öµÍ¹ŠºÄ
}
