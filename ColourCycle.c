// Colour cycling LED
// Sock Gribben 

#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;       // Stop WDT
  P2DIR |= BIT1 + BIT3 + BIT5;    // Set P2.1, P2.3 AND P2.5 to output direction

  while (1)
  {
    P2OUT |= BIT5;  
  }
  
}