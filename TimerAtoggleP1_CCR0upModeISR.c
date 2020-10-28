//Sophie Gribben - 201727662
//EE579 task 2


#include <msp430.h>
int switchFlag;
int counter; 
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  
  //set up timer A
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 16384-1;                           // CCRO value set so led blinks at 1 Hz 
  TACTL = TASSEL_1 + MC_1;                  // ACLK, upmode
  
  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt
  
 }

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 (Green LED)  
}
