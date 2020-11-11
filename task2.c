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
  
  //set up switch interrupt
  P1OUT |= BIT3;                            // Select pull up resistor on P1.3
  P1REN |= BIT3;                            // Enable it 
  P1IES |= BIT3;                            // P1.3 high to low edge
  P1IFG &= ~BIT3;                           // P1.3 IGF cleared
  P1IE |= BIT3;                             // P1.3 Interupt enabledcan 
  
  counter = 0;                              // initialise counter
  switchFlag = 0x00;                        // intitialise flag 
  
  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt
  
 }

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  if (switchFlag == 0x01)                    //If switch pressed
  {
    if (counter < 60) {                      //if less than 30 secs passed
      counter++;                             //increase counter by 1
    } else {
      switchFlag = 0x00;                     // Clear switch flag
      counter = 0;                           // Reset counter
      P1OUT |= BIT0;                         // LED ON
    }
  }
  else                                      //If Switch not pressed
  {
  P1OUT ^= 0x01;                            // Toggle P1.0
  }
}

//Port 1 (switch) interupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1OUT &= ~BIT0;                            // P1.0 = off
  switchFlag = 0x01;                         // set switch flag 
  P1IFG &= ~BIT3;                            // P1.3 IFG cleared
}