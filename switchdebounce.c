#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
  P1DIR |= BIT0;                // Set P1.0 to output direction
  P1OUT |= BIT3;                // Select pull up resistor on P1.3
  P1REN |= BIT3;                // and enable it
  P1IES |= BIT3;                // P1.3 high to low edge
  P1IFG &= ~BIT3;               // P1.3 IFG cleared
  P1IE |= BIT3;                 // P1.3 interrupt enabled
  
  __bis_SR_register(LPM4_bits + GIE);     // Enter LPM4 w/interrupt
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1OUT ^= BIT0; // P1.0 = toggle
  P1IFG &= ~BIT3; // P1.3 IFG cleared
}