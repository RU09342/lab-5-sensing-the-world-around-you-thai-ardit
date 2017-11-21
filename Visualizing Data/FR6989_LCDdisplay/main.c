/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//   MSP430FR6989
//      LCD Display
//
//   Description: Display input ADC value on a LCD displayer
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO~1MHz
//
//                MSP430
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   Thai Nghiem and Ardit Pranvoku (collaborate with Matthew Rodriguez)
//   Rowan University
//   November 2017
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

//MSP430FR6989
//Displays value from ADC

#include "msp430.h"
#include <LCDDriver.h>
#include <stdlib.h>

void LCDInit(); // Intialize LCD function
char intToChar(int); // Convert number to character function 

int adc_int = 0; //will contain contents from ADC12MEM0
int adcArray[3]; //will contain digits of adc_int


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop WDT

    //initialize lcd
    LCDInit();	
	
	//Prints out characters on the LCD of MSP430FR6989
    showChar('0',0); 
    showChar('0',1);
    showChar('0',2);
    showChar('0',3);
    showChar('0',4);
    showChar('0',5);
    showChar('0',6);

    P1OUT &= ~BIT0;                         // Clears the LED
    P1DIR |= BIT0;                          // Sets Pin 1.0 to output


    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Configure ADC1
      REFCTL0=REFON + REFVSEL_2;       //Sets reference voltage to 2.5V
      ADC12CTL0 = ADC12SHT0_2 | ADC12ON;   // Sampling rate, S&H=16, ADC12 on
      ADC12CTL1 = ADC12SHP;                // Use sampling timer, ADC12SC conversion start, clock=OSC
      ADC12CTL2 |= ADC12RES_2;             // Saves 12-bit conversion results
      ADC12MCTL0 |= ADC12INCH_3;           // input to the ADC
      ADC12IER0 |= ADC12IE0;               // Enables interrupt when ADC conversion completes.
      ADC12CTL0 |= ADC12ENC;               //Enable conversion
      P1SEL0 |=BIT3;                      //Configure pin 1.3 for input channel 3
      P1SEL1 |=BIT3;



    //adc
    while (1)
    {
        __delay_cycles(1000);
        ADC12CTL0 |= ADC12ENC | ADC12SC;    // Start sampling/conversion
        __bis_SR_register(LPM0_bits | GIE); // LPM0, ADC12_ISR will force exit
        __no_operation();                   // For debugger
    }

}




#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC12_VECTOR))) ADC12_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG))
    {
        case ADC12IV_NONE:        break;    // Vector  0:  No interrupt
        case ADC12IV_ADC12OVIFG:  break;    // Vector  2:  ADC12MEMx Overflow
        case ADC12IV_ADC12TOVIFG: break;    // Vector  4:  Conversion time overflow
        case ADC12IV_ADC12HIIFG:  break;    // Vector  6:  ADC12BHI
        case ADC12IV_ADC12LOIFG:  break;    // Vector  8:  ADC12BLO
        case ADC12IV_ADC12INIFG:  break;    // Vector 10:  ADC12BIN
        case ADC12IV_ADC12IFG0:             // Vector 12:  ADC12MEM0 Interrupt

            __delay_cycles(300000); 
            adc_int = ADC12MEM0; // Get value from ADC12
            int count = 0;
                         //iterates through 3 digit adc_int and puts each digit into arrInt in reverse order
                         do{
							 // Turning hex to decimal
                              adcArray[count]=(adc_int%10); 
                              adc_int/=10;
                              count++;
                         }while(adc_int>0);


                //prints out characters to lcd
                showChar(intToChar(adcArray[2]), 1);
                showChar(intToChar(adcArray[1]), 2);
                showChar(intToChar(adcArray[0]), 3);

                // Exit from LPM0 and continue executing main
                __bic_SR_register_on_exit(LPM0_bits);
            break;
        default: break;
    }
}

//initializes values for the LCD
void LCDInit()
{
    PJSEL0 = BIT4 | BIT5;                   // For LFXT

    // Initialize LCD segments 0 - 21; 26 - 43
    LCDCPCTL0 = 0xFFFF;
    LCDCPCTL1 = 0xFC3F;
    LCDCPCTL2 = 0x0FFF;

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Configure LFXT 32kHz crystal
    CSCTL0_H = CSKEY >> 8;                  // Unlock CS registers
    CSCTL4 &= ~LFXTOFF;                     // Enable LFXT
    do
    {
      CSCTL5 &= ~LFXTOFFG;                  // Clear LFXT fault flag
      SFRIFG1 &= ~OFIFG;
    }while (SFRIFG1 & OFIFG);               // Test oscillator fault flag
    CSCTL0_H = 0;                           // Lock CS registers

    // Initialize LCD_C
    // ACLK, Divider = 1, Pre-divider = 16; 4-pin MUX
    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;

    // VLCD generated internally,
    // V2-V4 generated internally, v5 to ground
    // Set VLCD voltage to 2.60v
    // Enable charge pump and select internal reference for it
    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN;

    LCDCCPCTL = LCDCPCLKSYNC;               // Clock synchronization enabled

    LCDCMEMCTL = LCDCLRM;                   // Clear LCD memory
    //Turn LCD on
    LCDCCTL0 |= LCDON;
}

// Converting an interger to a character
char intToChar(int numInput){
    char number;
				
                if(numInput == 0) // Turn number zero to a character 
                {    number = '0';
                }
                else if(numInput == 1) // Turn number one to a character
                {
                   number = '1';
                }
               else if(numInput == 2)  // Turn number two to a character
        {
                   number = '2';
                }
              else if(numInput == 3)  // Turn number three to a character
        {
                   number = '3';
                }
              else if(numInput == 4)	// Turn number four to a character
        {
                   number = '4';
                }
             else if(numInput == 5)		// Turn number five to a character
        {
                   number = '5';
                }
            else if(numInput == 6)  // Turn number six to a character
        {
                   number = '6';
                }
            else if(numInput == 7)	// Turn number seven to a character
        {
                   number = 7;
                }
            else if(numInput == 8)	// Turn number eight to a character
        {
                   number = '8';
                }
            else if(numInput == 9) // Turn number nine to a character
        {
                   number = '9';
                }

    return number;

}
