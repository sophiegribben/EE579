#include <msp430.h>

int studentNo [9] = {'2', '0', '1', '7', '2', '7', '6', '6', '2'}; //student number as an array (in quotes so ascii)
int mask; //mask for bit shifting
int i;  //counter for working through array


int main(void)
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  P1DIR |= BIT0;    //Set up pin 1 to output direction 
  
  
  while(1)
  { 
    //work through each number in student number
    for (i = 0; i <9; i++) {
        //Start bit LOW
        P1OUT &= ~BIT0;             
        __delay_cycles(75000);     //delay 1 sec   
        
        //transmit ascii LSB first
        for (mask = 0x01; mask >0; mask <<=1) {
              if (studentNo[i] & mask) // if bit is 1
              {
              //set led on (low) by ANDING with 0
              P1OUT &= ~BIT0;
              } 
              else // if bit is 0
              {  
              //set led off (high) by ORING with 1
              P1OUT |= BIT0;
              }
         __delay_cycles(75000);   //delay 1sec
        }    
        
        //Stop bit HIGH
        P1OUT |= BIT0;
        __delay_cycles(75000);   //delay 1 sec
  
      }
  }
}



