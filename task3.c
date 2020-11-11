#include <msp430.h> 

int counter = 0;                                 //initialise counter

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                  // Stop WDT
  
  P2DIR |= BIT1 + BIT3 + BIT5;               // Set P2.1, P2.3 AND P2.5 to output direction
  
  //set up timer A
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 6554-1;                            // CCRO value set so led blinks at 1 Hz 
  TACTL = TASSEL_1 + MC_1;                  // ACLK, upmode
  
  //set up ADC
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;// ADC10ON, interrupt enabled
  ADC10CTL1 = INCH_1;                        // input A1
  ADC10AE0 |= 0x02;                          // PA.1 ADC option select

 for (;;)
  {
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
  }
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
  
     if (ADC10MEM < 0x1FE && ADC10MEM > 0x180 || ADC10MEM > 0x202 && ADC10MEM < 0x280) {     //close to middle (1)
        counter++;
        if (counter > 10) {
          colourchange();
          counter = 0;
        }
    } 
    else if (ADC10MEM <= 0x180 && ADC10MEM > 0x100 || ADC10MEM >= 0x280 && ADC10MEM < 0x300){      //futher out (2)
        counter++;
        if (counter > 5) {
          colourchange();
          counter = 0;
        }
     } 
     else if (ADC10MEM <= 0x100 && ADC10MEM > 0x80 || ADC10MEM >= 0x300 && ADC10MEM < 0x380){      //futher out (3)
        counter++;
        if (counter > 2) {
          colourchange();
          counter = 0;
        }
     } 
     else if (ADC10MEM <= 0x80 || ADC10MEM >= 0x380){   //farthest out (4)
      colourchange();
    } 
     else {                                          //in middle
       counter=0;
    }  
 
}


// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}


int colourchange(){
  switch (P2OUT) {
  case BIT1:                          //Red to green
       P2OUT = BIT3;
       break;
       
  case BIT3:                          //green to blue
       P2OUT = BIT5;
       break;  
    
  case BIT5:                          //blue to purple
       P2OUT = BIT1 + BIT5;
       break; 
    
  case BIT1 + BIT5:                  //purple to white
       P2OUT = BIT1 + BIT3 + BIT5;
       break; 

  case BIT1 + BIT3 + BIT5:           //white to red
       P2OUT = BIT1;
       break;        
 
     default:                           //default to red
       P2OUT = BIT1;
       break;
  }
}




