//  MSP430G2x33/G2x53 Demo - ADC10, Sample A1, AVcc Ref, Set P1.0 if > 0.5*AVcc
//
//  Description: A single sample is made on A1 with reference to AVcc.
//  Software sets ADC10SC to start sample and conversion - ADC10SC
//  automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
//  and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
//  conversion complete, ADC10_ISR will force exit from LPM0 in Mainloop on
//  reti. If A1 > 0.5*AVcc, P1.0 set, else reset.
//
//                MSP430G2x33/G2x53
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|P1.1/A1      P1.0|-->LED
//
//  D. Dang
//  Texas Instruments Inc.
//  December 2010
//   Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
#include <msp430.h> 

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                  // Stop WDT
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;// ADC10ON, interrupt enabled
  ADC10CTL1 = INCH_1;                        // input A1
  ADC10AE0 |= 0x02;                          // PA.1 ADC option select
  P2DIR |= BIT1 + BIT3 + BIT5;               // Set P2.1, P2.3 AND P2.5 to output direction
  
  
 for (;;)
  {
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    
    
   //read value of adc
    if (ADC10MEM < 0x1FF) {
     colourchange();              // Set P2.1 LED to colour change function
     int speed = 2500000; 
     __delay_cycles(speed); 
    } else {
      P2OUT = BIT1 + BIT5;                // Set P1.3 LED Purple
    }
  }
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

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}


