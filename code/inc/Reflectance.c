// Reflectance.c
// Provide functions to take measurements using a QTR-8RC reflectance
// sensor array (Pololu part number 961).  This works by outputting to
// the sensor, waiting, then reading the digital value of each of the
// eight phototransistors.  The more reflective the target surface is,
// the faster the voltage decays.

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


// reflectance LED illuminate connected to P5.3
// reflectance sensor 1 connected to P7.0 (robot's right, robot off road to left)
// reflectance sensor 2 connected to P7.1
// reflectance sensor 3 connected to P7.2
// reflectance sensor 4 connected to P7.3 center
// reflectance sensor 5 connected to P7.4 center
// reflectance sensor 6 connected to P7.5
// reflectance sensor 7 connected to P7.6
// reflectance sensor 8 connected to P7.7 (robot's left, robot off road to right)

#include <stdint.h>
#include "msp432.h"
#include "..\inc\Clock.h"

#define RSLK_MAX 1

#if (RSLK_MAX)
void Port9_Init(void); //RSLK-MAX
#endif

void Port5_Init(void);
void Port7_Init(void);
void Port7_Output_ChargeCap(void);
void Port7_InitToInput(void);

// ------------Reflectance_Init------------
// Initialize the GPIO pins associated with the QTR-8RC reflectance sensor.
// Port7 are configured as inputs to read the reflectance value.
// Port5.3 is configured as output to control the IR LED firing
// Infrared illumination LEDs are initially off.
// Input: none
// Output: none

void Reflectance_Init(void){
    Port5_Init();
    Port7_Init();
#if (RSLK_MAX)
    //RSLK-MAX
    Port9_Init();
#endif
}
// Initialisation Step 1.
// Initialise Port 5 and Port 9 for Reflectance Sensing
// Registers: SEL0, SEL1, DIR, REN, OUT.
void Port5_Init(void){
    // write this as part of Lab 2
    // Code to initialise GPIO related registers
    P5->SEL0 &= ~0x08;
    P5->SEL1 &= ~0x08;                        // configure P5.3 as GPIO
    P5->DIR |= 0x08;                         // make P5.3 out (0000_1000) // Output is logic 1
    P5->REN &= ~0x08;                         // Enable P5.3 pullup/down resistor (0000_1000) 1->Enable
    P5->OUT |= 0x08;                         // set to low

//    P5->SEL0 &= ~0x08;
//        P5->SEL1 &= ~0x08;                        // configure P5.3 as GPIO
//        P5->DIR |= 0x08;                         // make P5.3 out (0000_1000) // Output is logic 1
//        P5->REN |= 0x08;                         // Enable P5.3 pullup/down resistor (0000_1000) 1->Enable
//        P5->OUT = 0x00;                         // set to low

}

void Port9_Init(void){
    // write this as part of Lab 2
    // Code to initialise GPIO related registers
//    P9->SEL0 = 0x00;
//    P9->SEL1 = 0x00;                        // configure P9.2 as GPIO
//    //P9->DS = 0x04;                          // make P9.2 high drive strength (0000_0100)
//    P9->DIR |= 0x04;                         // make P9.2 out (0000_0100) // Output is logic 1
//    P9->REN |= 0x04;                         // Enable P9.2 pullup/down resistor (0000_1000) 1->Enable
//    P9->OUT &= 0x00;                         // set to low

    P9->SEL0 &= ~0x04;
    P9->SEL1 &= ~0x04;                        // configure P9.2 as GPIO
    P9->DIR |= 0x04;                         // make P9.2 out (0000_1000) // Output is logic 1
    P9->REN &= ~0x04;                         // Enable P9.2 pullup/down resistor (0000_1000) 1->Enable
    P9->OUT |= 0x04;                         // set to low

}

// Initialisation Step 2.
// Initialise Port 7 for Reflectance Sensing
// Registers: SEL0, SEL1, DIR.
void Port7_Init(void){
    // write this as part of Lab 2
    // Code to initialise GPIO related registers
    P7->SEL0 &= 0x00;
    P7->SEL1 &= 0x00;                        // configure P7.7-P7.0 as GPIO
    //P7->DS = 0xFF;                          // make P7.7-P7.0 high drive strength (1111_1111)
    P7->DIR &= ~0xFF;                         // make P7.7-P7.0 in (0000_0000) // Output is logic 1, input is logic 0
    //P7->OUT = 0x00;                         // all off

}

// Reflectance Reading Step 2.
// Set Port7 to output high to charge the capacitors
// Registers: DIR, OUT.
void Port7_Output_ChargeCap(void){
    // write this as part of Lab 2
    P7->DIR |= 0xFF;                         // make P7.7-P7.0 output pins // Output is logic 1, input is logic 0
    P7->OUT |= 0xFF;                         // all high

}

// Reflectance reading Step 4.
// Initialise Port7 to input mode
// Registers: DIR.
void Port7_InitToInput(void){
    // write this as part of Lab 2
    P7->DIR &= ~0xFF;                         // make P7.7-P7.0 in (0000_0000) // Output is logic 1, input is logic 0
}




// ------------Reflectance_Read------------
// Read the eight sensors
// Turn on the 8 IR LEDs
// Pulse the 8 sensors high for 10 us
// Make the sensor pins input
// wait t us
// Read sensors
// Turn off the 8 IR LEDs
// Input: time to wait in usec
// Output: sensor readings
// Assumes: Reflectance_Init() has been called
uint8_t Reflectance_Read(uint32_t time){
  uint8_t result;
  // write this as part of Lab 2
  // Translate Step 1-8 of the reflectance read procedure to code.

  // Step1.  RSLK-MAX. P5.3 = HIGH and P9.2 = HIGH => IR LED ON
  P5->OUT |= 0x08;
#if(RSLK_MAX)
  P9->OUT |= 0x04;
#endif
  Port7_Output_ChargeCap();     // Step 2, Configure P7.7 – P7.0 as output pins. Set the pins to Logic ‘1’
  Clock_Delay1us(10);           // Step 3, wait for 10us
  Port7_InitToInput();          // Step 4, configure P7.7-P7.0 as input pins
  Clock_Delay1us(time);         // Step 5, wait for 'time'
  result = P7->IN;              // Step 6, Read P7.7 – P7.0 digital inputs.

  P5->OUT &= ~0x08;
#if(RSLK_MAX)
  P9->OUT &= ~0x04;
#endif
  return result;                // Step 8, Return 8-bit binary value read in step 6
}

// ------------Reflectance_Center------------
// Read *ONLY* the two center sensors
// Turn on the 8 IR LEDs
// Pulse the 8 sensors high for 10 us
// Make the sensor pins input
// wait t us
// Read sensors
// Turn off the 8 IR LEDs
// Input: time to wait in usec
// Output: 0 (off road), 1 off to left, 2 off to right, 3 on road
// (Left,Right) Sensors
// 1,1          both sensors   on line
// 0,1          just right     off to left
// 1,0          left left      off to right
// 0,0          neither        lost
// Assumes: Reflectance_Init() has been called
uint8_t Reflectance_Center(uint32_t time){
    uint8_t result;
    // write this as part of Lab 2
    // Use bit shifting and extraction to shift the center two bits to the
    // right to occupy the last two bits of the result variable

    P5->OUT |= 0x08;
  #if(RSLK_MAX)
    P9->OUT |= 0x04;
  #endif
    Port7_Output_ChargeCap();     // Step 2, Configure P7.7 – P7.0 as output pins. Set the pins to Logic ‘1’
    Clock_Delay1us(10);           // Step 3, wait for 10us
    Port7_InitToInput();          // Step 4, configure P7.7-P7.0 as input pins
    Clock_Delay1us(time);         // Step 5, wait for 'time'
    result = P7->IN;              // Step 6, Read P7.7 – P7.0 digital inputs.

  #if(RSLK_MAX)
    P9->OUT &= ~0x04;
  #endif
    result = (result>>3)&0x03;
    return result;                // Step 8, Return 8-bit binary value read in step 6
}


// Perform sensor integration
// Input: data is 8-bit result from line sensor
// Output: position in 0.1mm relative to center of line
int32_t Reflectance_Position(uint8_t data){
    uint32_t position;
    uint32_t denom;

    // write this as part of Lab 2
    // Extract the appropriate bits from the reflectance read data
    // to multiply to the corresponding weights in W[].
    // Bit shifting and extraction.
    int32_t W[8] = {332, 237, 142, 47, -47, -142, -237, -332};

    position = 0;
    for (int i = 0; i < 8; i++) {
        position += ((data>>i) & 0x01)*(W[i]);
    }

//    position = 0;
//    denom = 0;
//    uint32_t d = 0;
//    for (int i = 0; i < 8; i++) {
//        d = ((data>>i) & 0x01);
//        denom += d;
//        position += d*(W[i]);
//    }
//
//    position = position/denom;
//
//    return position;

    return position;
}


// ------------Reflectance_Start------------
// Begin the process of reading the eight sensors
// Turn on the 8 IR LEDs
// Pulse the 8 sensors high for 10 us
// Make the sensor pins input
// Input: none
// Output: none
// Assumes: Reflectance_Init() has been called
void Reflectance_Start(void){
    // write this as part of Lab 3
    // Step 1-4 of the Reflectance Read in Lab2.

    // Step 1                // Set P5.3 and P9.2 high ( turn on 8 IR LED)
    P5->OUT |= 0x08;
    #if(RSLK_MAX)
        P9->OUT |= 0x04;
    #endif

    // Step 2
    Port7_Output_ChargeCap(); // Make the P7.7-P7.0 outputs, and set them all high

    // Step 3
    Clock_Delay1us(10);   // Wait 10 μs

    // Step 4
    Port7_InitToInput();  // Make the P7.7-P7.0 inputs
}


// ------------Reflectance_End------------
// Finish reading the eight sensors
// Read sensors
// Turn off the 8 IR LEDs
// Input: none
// Output: sensor readings
// Assumes: Reflectance_Init() has been called
// Assumes: Reflectance_Start() was called 1 ms ago
uint8_t Reflectance_End(void){
    uint8_t result;
    // write this as part of Lab 3
    // Step 6-7 of Reflectance Read in Lab2.

    // Step 6
    result = P7->IN;  // Read the 8-bit sensor result

    // Step 7
    P5->OUT &= ~0x08;  // Turn off the 8 IR LEDs (P5.3) low
      #if(RSLK_MAX)
        P9->OUT &= ~0x04;
      #endif


    return result;
}




