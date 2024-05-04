/* This example accompanies the books
   "Embedded Systems: Introduction to the MSP432 Microcontroller",
       ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
       ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
       ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2017
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2017, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/
// Negative logic bump sensors
// P8.7 Bump5
// P8.6 Bump4
// P8.5 Bump3
// P8.4 Bump2
// P8.3 Bump1
// P8.0 Bump0

// reflectance LED illuminate connected to P5.3
// reflectance sensor 1 connected to P7.0 (robot's right, robot off road to left)
// reflectance sensor 2 connected to P7.1
// reflectance sensor 3 connected to P7.2
// reflectance sensor 4 connected to P7.3 center
// reflectance sensor 5 connected to P7.4 center
// reflectance sensor 6 connected to P7.5
// reflectance sensor 7 connected to P7.6
// reflectance sensor 8 connected to P7.7 (robot's left, robot off road to right)

#include "msp.h"
#include "..\inc\bump.h"
#include "..\inc\Reflectance.h"
#include "..\inc\Clock.h"
#include "..\inc\SysTickInts.h"
#include "..\inc\CortexM.h"
#include "..\inc\LaunchPad.h"
#include "..\inc\TExaS.h"

volatile uint8_t reflectance_data, bump_data;
volatile uint32_t MainCount=0;

/*
 *
 *
       Questions  :

       1) What does SysTick_Init() do ?

       Ans: Inititalise all the REGs for SysTick Interuupt

       From core_cm4.h:
       typedef struct
        {
          __IOM uint32_t CTRL;                   //!< Offset: 0x000 (R/W)  SysTick Control and Status Register /
          __IOM uint32_t LOAD;                   //!< Offset: 0x004 (R/W)  SysTick Reload Value Register /
          __IOM uint32_t VAL;                    //!< Offset: 0x008 (R/W)  SysTick Current Value Register /
          __IM  uint32_t CALIB;                  //!< Offset: 0x00C (R/ )  SysTick Calibration Register /
        } SysTick_Type;

        We can observe that:
        SysTick->CTRL is STCSR REG , Basic control (Where the bits 2-0 needs to be configured)
        SysTick->LOAD is STRVR REG , value to be loaded into REG when 0 reached
        SysTick->VAL is STCVR REG , current value of count down

        2) How does the SysTick_Handler 'poll' every 1ms

        Ans: SysTick_Init(48000,1);

        Notice the period 48000 parameter is the value that is to be loaded into STRVR REG.
        Clk Source is the Core clk which is 48Mhz.
        Each count would therefore be 1ms

        3) Why red LED keep blinking ?


        4) Why do we need to pause and run to find what is the value in the expression bump_data

        5) Do we need to use any stuff to add to while loop? im confused how the PORT4_IRQHandler() is used .

 *
 */


void SysTick_Handler(void){ // every 1ms
    volatile static uint8_t count=0;
    if(count==0){
        Reflectance_Start();
        //heart = heart^1;
        //LaunchPad_LED(heart);
        P2->OUT ^= 0x01;
    }
    else if (count==1) {
        reflectance_data =  Reflectance_End();
        bump_data = Bump_Read();
        P2->OUT ^= 0x01;
    }
    count++;
    if(count==10)count=0;
}

int main(void){

volatile uint8_t data_pins;

    Clock_Init48MHz();
    LaunchPad_Init();
    Bump_Init();
    Reflectance_Init();
    TExaS_Init(LOGICANALYZER_P7);
    SysTick_Init(48000,1);  // set up SysTick for 1000 Hz interrupts
    EnableInterrupts();

    while(1){
      WaitForInterrupt();
      if(MainCount%10000 == 0) //P2->OUT ^= 0x01; // foreground thread // every 10000 count , LED flash once
      MainCount++;
    }
}

void PORT4_IRQHandler(void){
    // write this as part of Lab 3
    // execute user task
    //uint8_t bump_data;

    bump_data = Bump_Read();
    P4->IFG &= ~0XED; // clear interrupt flag
    P2->OUT ^= 0x01; // LED Blink
}



