#include <msp430g2221.h>

#include 'ina219_slave.c'

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  } 
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
  Setup_USI_Slave();
  
  LPM0;                                     // CPU off, await USI interrupt
  _NOP();
}