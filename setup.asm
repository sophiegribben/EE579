#include "msp430.h"     ; define controlled include file
  
        NAME setup              ; module name
        PUBLIC setup            ; make the setup label visible
                                ; outside this module
        PUBLIC flash            ; make the flash visible outside
        EXTERN counter          ; bring in counter from c

        RSEG CODE               ; place routine in CODE segment

setup:  MOV.B     #0X1, P1DIR    ;SET DDR for P1.0 output
        RET                     ; then return 

flash:  INC.W counter
        JN led_on               ; is incremented counter negative? 
        MOV.B   #0x1, P1OUT     ; if not, turn LED off
        RET                     ; then return 
led_on: MOV.B   #0x0, P1OUT     ; if so, turn LED on 
        RET

END
