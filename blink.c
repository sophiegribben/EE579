#include "msp430.h"

extern void setup();
int counter;  //make global so assembler can see

int main (void)
{
  //stop WDT to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD; 
  
  setup(); 
  
  while (1)
  {
    flash(); 
  }
}