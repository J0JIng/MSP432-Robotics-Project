// RSLK Self Test via UART

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
// RSLK
#include "msp.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "..\inc\UART0.h"
#include "..\inc\EUSCIA0.h"
#include "..\inc\FIFO0.h"
#include "..\inc\Clock.h"
//#include "..\inc\SysTick.h"
#include "..\inc\SysTickInts.h"
#include "..\inc\CortexM.h"
#include "..\inc\TimerA1.h"
//#include "..\inc\Bump.h"
#include "..\inc\BumpInt.h"
#include "..\inc\LaunchPad.h"
#include "..\inc\Motor.h"
#include "../inc/IRDistance.h"
#include "../inc/ADC14.h"
#include "../inc/LPF.h"
#include "..\inc\Reflectance.h"
#include "../inc/TA3InputCapture.h"
#include "../inc/Tachometer.h"

#define P2_4 (*((volatile uint8_t *)(0x42098070)))
#define P2_3 (*((volatile uint8_t *)(0x4209806C)))
#define P2_2 (*((volatile uint8_t *)(0x42098068)))
#define P2_1 (*((volatile uint8_t *)(0x42098064)))
#define P2_0 (*((volatile uint8_t *)(0x42098060)))

/***********************************************/

void BSC_MotorTest(void);
void BSC_IRTest(void);
void BSC_BumperTest(void);
void BSC_ReflectanceTest(void);
void BSC_TachometerTest(void);
void ADV_BumpTest(void);
void ADV_LineFollowTest(void);
void MotorActivate(int32_t state,int32_t Position);

/******************APP UTIL*********************/

/*
 * This function takes an 8-bit unsigned integer and converts
 * it into its binary representation as a character string.
 * The binary string is stored in a static buffer and is null-terminated.
 *
 * @param x The 8-bit unsigned integer to convert to binary.
 * @return A pointer to a null-terminated character string representing the binary
 *         representation of the input integer.
 */
const char *toByte(uint8_t x)
{
    static char b[9];
    b[0] = '\0';

    uint8_t z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

/*
 * Enumeration for specifying different UART send operations.
 */
typedef enum
{
    SEND,    // Send the string
    REPLACE  // Replace the string
} UARTSendType;

/*
 * This function sends a string via UART with optional actions based on the sendType.
 * If sendType is REPLACE, it first sends an escape sequence to replace the existing content.
 *
 * @param str The string to be sent via UART.
 * @param sendType The type of UART send operation (SEND or REPLACE).
 */
static void UARTSend(char *str, UARTSendType sendType)
{
    if (sendType == REPLACE) UART0_OutString("\033[A\33[2K\r");
    UART0_OutString(str);
    EUSCIA0_OutChar(CR);
    EUSCIA0_OutChar(LF);
}

/*
 * Pauses the program execution for the specified time duration.
 *
 * @param time The time duration in milliseconds.
 */
void TimedPause(uint32_t time){
  Clock_Delay1ms(time);          // run for a while and stop
  Motor_Stop();
}
/************************************************/


/****************** RSLK_RST ********************/
void RSLK_Reset(void){
    DisableInterrupts();
    LaunchPad_Init();
    EnableInterrupts();
}
/************************************************/



/*************** Bumper Variables ***************/
static volatile uint8_t bumpIntData, IsCollidedFlag;
void BumpDetected(uint8_t bumpSensor)
{
    Motor_Stop();
    bumpIntData = bumpSensor; // bumpSensor is the 6-bit positive logic result from Bumb_Read
    IsCollidedFlag = 1;
    P4->IFG &= ~0xED; // clear interrupt flags (reduce possibility of extra interrupt)
}

uint8_t bump_data;
bool bumperArr[6] = {0};
char bumperBuf[30];
/************************************************/



/************ IR Sensors variables **************/
volatile uint32_t ADCvalue;
volatile uint32_t ADCflag;
volatile uint32_t nr, nc, nl;

void IR_ISR(void)
{  // runs at 2000 Hz
    uint32_t raw17, raw12, raw16;
    //P1OUT ^= 0x01; are used for profiling or debugging purposes.
    P1OUT ^= 0x01;         // profile
    P1OUT ^= 0x01;         // profile
    ADC_In17_12_16(&raw17, &raw12, &raw16);  // sample
    nr = LPF_Calc(raw17);  // right is channel 17 P9.0
    nc = LPF_Calc2(raw12);  // center is channel 12, P4.1
    nl = LPF_Calc3(raw16);  // left is channel 16, P9.1
    ADCflag = 1;           // semaphore
    P1OUT ^= 0x01;         // profile
}
/************************************************/



/************ Tachometer variables **************/
// SMCLK 12Mhz

uint16_t Period0;              // (1/SMCLK) units = 83.3 ns units
uint16_t First0 = 0;           // Timer A3 first edge, P10.4
uint32_t Done0 = 0;            // set each rising

uint16_t Period2;              // (1/SMCLK) units = 83.3 ns units
uint16_t First2 = 0;           // Timer A3 first edge, P8.2
uint32_t Done2 = 0;            // set each rising
uint32_t LeftRPM = 0, RightRPM = 0;

// max period is (2^16-1)*83.3 ns = 5.4612 ms
// min period determined by time to run ISR, which is about 1 us
void PeriodMeasure0(uint16_t time)
{
    Period0 = (time - First0) & 0xFFFF; // 16 bits, 83.3 ns resolution
    First0 = time;                      // setup for next
    Done0++;
}

// max period is (2^16-1)*83.3 ns = 5.4612 ms
// min period determined by time to run ISR, which is about 1 us
void PeriodMeasure2(uint16_t time)
{
    Period2 = (time - First2) & 0xFFFF; // 16 bits, 83.3 ns resolution
    First2 = time;                      // setup for next
    Done2++;
}
/************************************************/

/**************** FSM variables *****************/

// Linked data structure
struct State {
  uint32_t OUT;                // 2-bit output
  uint32_t DELAY;              // time to delay in 1ms
  const struct State *NEXT[4]; // Next if 2-bit input is 0-3
};
typedef const struct State State_t;

#define CENTER    &fsm[0]
#define LEFT      &fsm[1]
#define RIGHT     &fsm[2]



State_t fsm[3]={
  {0x03, 25, { RIGHT, LEFT,   RIGHT,  CENTER }},  // Center
  {0x02, 25, { LEFT,  CENTER, RIGHT,  CENTER }},  // Left
  {0x01, 25, { RIGHT, LEFT,   CENTER, CENTER }}   // Right
};


State_t *Spt;  // pointer to the current state
uint32_t INPUT;
uint32_t OUTPUT;

/************************************************/

// RSLK Self-Test
// Sample program of how the text based menu can be designed.
// Only one entry (RSLK_Reset) is coded in the switch case. Fill up with other menu entries required for Lab5 assessment.
// Init function to various peripherals are commented off.  For reference only. Not the complete list.

int main(void) {
  uint32_t cmd=0xDEAD, menu=0;

  DisableInterrupts();
  Clock_Init48MHz();  // makes SMCLK=12 MHz
  //SysTick_Init(48000,2);  // set up SysTick for 1000 Hz interrupts
  Motor_Init();
  //Motor_Stop();
  LaunchPad_Init();
  BumpInt_Init(&BumpDetected);
  //Bumper_Init();
  //IRSensor_Init();
  //Tachometer_Init();
  EUSCIA0_Init();     // initialize UART
  EnableInterrupts();

  while(1){                     // Loop forever
      // write this as part of Lab 5
      EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("RSLK Testing"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[0] [BSC] RSLK Reset"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[1] [BSC] Motor Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[2] [BSC] IR Sensor Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[3] [BSC] Bumper Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[4] [BSC] Reflectance Sensor Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[5] [BSC] Tachometer Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[6] [ADV] Simultaneous Bump test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[7] [ADV] Line Following test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

      EUSCIA0_OutString("CMD: ");
      cmd=EUSCIA0_InUDec();
      EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

      switch(cmd){
          case 0:
              RSLK_Reset();
              menu =1;
              cmd=0xDEAD;
              UARTSend("[BASIC] SYSTEM RESET", SEND);
              break;
          case 1:
              // Motor Test
              UARTSend("[BASIC] STARTING MOTOR TEST", SEND);
              BSC_MotorTest();
              UARTSend("MOTOR TEST DONE", SEND);
              break;

          case 2:
              // IR Sensor test
              UARTSend("[BASIC] STARTING IR SENSOR TEST", SEND);
              BSC_IRTest();
              UARTSend("IR SENSOR TEST DONE", SEND);
              break;

          case 3:
              // Bumpers
              UARTSend("[BASIC] STARTING BUMPER TEST", SEND);
              BSC_BumperTest();
              UARTSend("BUMPER TEST DONE", SEND);
              break;

          case 4:
              // reflectance
              UARTSend("[BASIC] STARTING REFLECTANCE SENSOR TEST", SEND);
              BSC_ReflectanceTest();
              UARTSend("REFLECTANCE SENSOR TEST DONE", SEND);
              break;

          case 5:

              // Tachometer test
              UARTSend("[BASIC] STARTING TACHOMETER SENSOR TEST", SEND);
              BSC_TachometerTest();
              UARTSend("TACHOMETER SENSOR TEST DONE", SEND);
              break;

          case 6:
              // Bumpers

              UARTSend("[ADVANCED] SIMULTANEOUS BUMP SWITCHES TEST", SEND);
              UARTSend(" ", SEND);
              ADV_BumpTest();
              UARTSend("SIMULTANEOUS BUMP SWITCHES TEST DONE",SEND);
              break;

          case 7:
              // Bumpers

              UARTSend("[ADVANCED] LINE FOLLOWING TEST", SEND);
              UARTSend(" ", SEND);
              ADV_LineFollowTest();
              UARTSend("LINE FOLLOWING TEST DONE",SEND);
              break;

          default:
              menu=1;
              break;
      }

      if(!menu)Clock_Delay1ms(3000);
      else{
          menu=0;
      }
  }
}


void BSC_MotorTest(void)
{

    // Maximum duty is 10_000
    UARTSend("DIRECTION: FORWARD", REPLACE);
    Motor_Forward(3000, 3000);
    TimedPause(2000);

    UARTSend("DIRECTION: BACKWARD", REPLACE);
    Motor_Backward(3000, 3000);
    TimedPause(2000);

    UARTSend("DIRECTION: RIGHT", REPLACE);
    Motor_Left(3000, 3000);
    TimedPause(2000);

    UARTSend("DIRECTION: LEFT", REPLACE);
    Motor_Right(3000, 3000);
    TimedPause(2000);

    UARTSend("RIGHT MOTOR ONLY", REPLACE);
    Motor_Forward(3000, 0);
    TimedPause(2000);

    UARTSend("LEFT MOTOR ONLY", REPLACE);
    Motor_Forward(0, 3000);
    TimedPause(2000);
    Motor_Stop();
}

void BSC_IRTest(void)
{
    IsCollidedFlag = 0;

    char buf[100];
    uint32_t raw17, raw12, raw16;
    uint32_t s; // s for Size-point average ,determines the number of data points that will be used for averaging when filtering a signal
    uint32_t n;

    ADCflag = 0; // ADCflag is used as a semaphore to indicate that new data is available.
    s = 256; // replace with your choice

    ADC0_InitSWTriggerCh17_12_16();   // initialize channels 17,12,16

    ADC_In17_12_16(&raw17, &raw12, &raw16);  // sample

    LPF_Init(raw17, s);     // P9.0/channel 17
    LPF_Init2(raw12, s);     // P4.1/channel 12
    LPF_Init3(raw16, s);     // P9.1/channel 16

    UART0_Init();          // initialize UART0 115,200 baud rate

    TimerA1_Init(&IR_ISR, 250);    // 2000 Hz sampling
    EnableInterrupts();

    while (1)
    {
        for (n = 0; n < 250; n++)
        {
            //busy-wait loop. keeps checking the ADCflag in a tight loop until it's set to a non-zero value.
            while (ADCflag == 0);
            ADCflag = 0; // show every nth point
        }

        if (IsCollidedFlag) // break out of loop
        {
            IsCollidedFlag = 0;
            return;
        }

        sprintf(buf, "%5dmm,%5dmm,%5dmm", LeftConvert(nl), CenterConvert(nc),RightConvert(nr));
        UARTSend(buf, REPLACE);
    }

}

void BSC_BumperTest(void)
{
    IsCollidedFlag = 0;

    while (!bumperArr[0] || !bumperArr[1] || !bumperArr[2] || !bumperArr[3] || !bumperArr[4] || !bumperArr[5])  // While all the bump switch are NOT pressed
    {
        bump_data = Bump_Read();

        for (uint8_t i = 0; i < 6; i++)
        {
            if ((((bump_data >> i & 0xF) & 0x1)) == 0 && bumperArr[i] == 0) // checks 1. switch corresponding bit 0 && 2. bump has never been pressed
            {
                bumperArr[i] = true;
                char buf[30];
                snprintf(buf, 30, "BUMPER %d PRESSED", i);
                UARTSend(buf, REPLACE);

            }
        }
    }
    for (uint8_t i = 0; i < 6; i++)  bumperArr[i] = false; // To reset

}

void BSC_ReflectanceTest(void)
{
    IsCollidedFlag = 0;

    uint8_t Data;
    int32_t Position;

    char refBuf[20] = "";

    while (1)
    {
        if (IsCollidedFlag)
        {
            IsCollidedFlag = 0;
            break;
        }
        Data = Reflectance_Read(2000);
        Position = Reflectance_Position(Data);
        sprintf(refBuf, "%s, %d mm", toByte(Data), Position / 10); //format a string and store the result in the refBuf
        UARTSend(refBuf, REPLACE);
        Clock_Delay1ms(100); // Delay to improve readability
    }
}

void BSC_TachometerTest(void)
{
    IsCollidedFlag = 0;
    EnableInterrupts();
    uint32_t count = 0;
    char buf[100];
    TimerA3Capture_Init(&PeriodMeasure0, &PeriodMeasure2);
    TimedPause(500);
    Motor_Forward(1500, 1500);
    EnableInterrupts();
    while (1)
    {
        WaitForInterrupt();
        count++;
        if (count % 100 == 0)
        {
            memset(buf, 0, sizeof(buf));
            LeftRPM = ((60 * 1000 * 1000) / (360 * 83.3 * Period0 / 1000));
            RightRPM = ((60 * 1000 * 1000) / (360 * 83.3 * Period2 / 1000));

            sprintf(buf, "RIGHT RPM = %2d, LEFT RPM = %2d", RightRPM, LeftRPM);

            UARTSend(buf, REPLACE);
        }
        if (IsCollidedFlag)
        {

            IsCollidedFlag = 0;
            return;
        }
    }
}

void ADV_BumpTest(void)
{
    while (1)
    {

        int pressed = 0;
        strcpy(bumperBuf, "PRESSED ON SWITCHES: ");
        bump_data = Bump_Read();
        if ((((bump_data >> 0) & 0x1)) == 0)
        {
            strcat(bumperBuf, "0 ");
            pressed = 1;
        }
        if ((((bump_data >> 1) & 0x1)) == 0)
        {
            strcat(bumperBuf, "1 ");
            pressed = 1;
        }
        if ((((bump_data >> 2) & 0x1)) == 0)
        {
            strcat(bumperBuf, "2 ");
            pressed = 1;
        }
        if ((((bump_data >> 3) & 0x1)) == 0)
        {
            strcat(bumperBuf, "3 ");
            pressed = 1;
        }
        if ((((bump_data >> 4) & 0x1)) == 0)
        {
            strcat(bumperBuf, "4 ");
            pressed = 1;
        }
        if ((((bump_data >> 5) & 0x1)) == 0)
        {
            strcat(bumperBuf, "5 ");
            pressed = 1;
        }

        if (!pressed)
        {
            UARTSend("NO BUMPERS PRESSED...", REPLACE);
        }
        else
            UARTSend(bumperBuf, REPLACE);

        if ((bump_data & 0b111111) == 0)
        {

            UARTSend("ALL BUMPERS PRESSED", REPLACE);
            return;
        }

        Clock_Delay1ms(100);

    }
}

void ADV_LineFollowTest(void)
{
    IsCollidedFlag = 0;
    uint8_t Data = Reflectance_Read(2000);
    int32_t Position =  Reflectance_Position(Data);
    Spt = CENTER;

    while(!IsCollidedFlag)
    {
        OUTPUT = Spt->OUT;            // set output from FSM
        MotorActivate(OUTPUT,Position);
        Clock_Delay1ms(Spt->DELAY);   // wait
        Data = Reflectance_Read(2000);
        Position = Reflectance_Position(Data);

        if(Data == 0x0){ // for turning
            if(Spt = LEFT )Motor_Right(1500, 1500);
            else Motor_Left(1500, 1500);
            Clock_Delay1ms(500);
        }

     }

    IsCollidedFlag = 0;
    UARTSend("BUMBPER DETECTED. TASK TERMINATING .", REPLACE);
}


void MotorActivate(int32_t state,int32_t Position)
{

    switch (state)
    {
        case 1:
            Motor_Right(1500, 1500);
            if(Position>=-180)
            {
                Spt = CENTER ;
            }
            //UARTSend("turn right.", REPLACE);
            break;

        case 2:
            Motor_Left(1500, 1500);
            if(Position<=180)
            {
                Spt = CENTER ;
            }

            //UARTSend("turn left.", REPLACE);
            break;

        case 3:
            Motor_Forward(1500, 1500);
            if(Position>180)
            {
                Spt = RIGHT ;
            }

            else if(Position<-180)
            {
                Spt = LEFT ;
            }
            //UARTSend("forward.", REPLACE);
            break;

        default:
            Motor_Forward(500, 500);

    }
}


#if 0
//Sample program for using the UART related functions.
int Program5_4(void){
//int main(void){
    // demonstrates features of the EUSCIA0 driver
  char ch;
  char string[20];
  uint32_t n;
  DisableInterrupts();
  Clock_Init48MHz();  // makes SMCLK=12 MHz
  EUSCIA0_Init();     // initialize UART
  EnableInterrupts();
  EUSCIA0_OutString("\nLab 5 Test program for EUSCIA0 driver\n\rEUSCIA0_OutChar examples\n");
  for(ch='A'; ch<='Z'; ch=ch+1){// print the uppercase alphabet
     EUSCIA0_OutChar(ch);
  }
  EUSCIA0_OutChar(LF);
  for(ch='a'; ch<='z'; ch=ch+1){// print the lowercase alphabet
    EUSCIA0_OutChar(ch);
  }
  while(1){
    EUSCIA0_OutString("\n\rInString: ");
    EUSCIA0_InString(string,19); // user enters a string
    EUSCIA0_OutString(" OutString="); EUSCIA0_OutString(string); EUSCIA0_OutChar(LF);

    EUSCIA0_OutString("InUDec: ");   n=EUSCIA0_InUDec();
    EUSCIA0_OutString(" OutUDec=");  EUSCIA0_OutUDec(n); EUSCIA0_OutChar(LF);
    EUSCIA0_OutString(" OutUFix1="); EUSCIA0_OutUFix1(n); EUSCIA0_OutChar(LF);
    EUSCIA0_OutString(" OutUFix2="); EUSCIA0_OutUFix2(n); EUSCIA0_OutChar(LF);

    EUSCIA0_OutString("InUHex: ");   n=EUSCIA0_InUHex();
    EUSCIA0_OutString(" OutUHex=");  EUSCIA0_OutUHex(n); EUSCIA0_OutChar(LF);
  }
}
#endif
