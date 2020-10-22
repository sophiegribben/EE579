#include <msp430.h>
//set up variables
 int test = 0x52;  //0101 0010 in hex
 int mask = 0x01;

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;           // Stop WDT


    P1DIR |= 0x01;                        // P1.0 output for LED

    P1DIR |= (1 << 4);                    // P1DIR P1.4 -- Set up CLOCK on port 1 pin 4
    P1SEL |= (1 << 4);                    // P1SEL P1.4 -- Set up CLOCK on port 1 pin 4

    //Set up oscillator
    DCOCTL |= 0xE0;                       // DC0 CTL     = 1110 0000 for 1.5 MHz
    BCSCTL1 |= 0x87;                      // BCS CTL1     = 1000 0111 

    BCSCTL2 |= DIVS_2;                    // SMCLK divided by 2^2=4

    TACTL = TASSEL_2 + MC_1 + ID_3;       // TA0 CTL = 1011 01000
    CCTL0 = CCIE;                         // TA0 CCTL0
    CCR0 = 24198;                         // TA0 CCR0 value is 24198 (0x5E86)
    
    //Each time counter reaches value of CCR0 (24198) an interupt is triggered
    
    __bis_SR_register(LPM0_bits + GIE);   // LowPower0 + Global Interrupt Enabled
  
}

/**
 * Timer A0 interrupt service routine
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer_a0(void) {
  //transmit ascii LSB first
        if (test &= mask) 
        {
        // if bit is 1
        //set led on (low) by ANDING with 0
        P1OUT &= ~BIT0;
        } else {
        // if bit is 0
        //set led off (high) by ORING with 1
        P1OUT |= BIT0;
        }
    //shift mask to the left
    mask <<=1;  
}