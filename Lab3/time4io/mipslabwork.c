/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
//volatile int(för att pekaren PE/TE kan plötsligt ändra sitt värde vilket gör att compilatorn kmr vilja optimisera variabeln till sitt gamla värde vilket vi inte vill).
//PE Port E are set as outputs (med att göra PE är 0)Port E so that bits 7 through 0
//TE Register TRISE has address 0xbf886100 (outputs)
volatile int* PE = (volatile int*) 0xbf886110;
volatile int* TE = (volatile int*) 0xbf886100;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
    //port D so that bits 11 through 5 of Port D are set as inputs.
    TRISDSET = (0xFF << 5);
    *TE &= ~(0xFF);
    *PE &= ~(0xFF);
    return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
    if((*PE & 0xFF) == 0xFF){
      *PE &= ~(0xFF);
    }
    //BTN4 copies the value from SW4 through SW1 into the first digit of mytime.
    if(getbtns()){
      if(getbtns() & 4){
        mytime &= 0x0FFF;
        mytime |= getsw() << 12;
      }
    //BTN3 copies the value from SW4 through SW1 into the second digit of mytime.
      if(getbtns() & 2){
        mytime &= 0xF0FF;
        mytime |= getsw() << 8;
      }
    //BTN2 copies the value from SW4 through SW1 into the third digit of mytime.
        if(getbtns() & 1){
        mytime &= 0xFF0F;
        mytime |= getsw() << 4;
      }
    }
    
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  *PE = *PE + 1;
  display_image(96, icon);
}
//Q2
//TRISE, TRISESET, and TRISECLR.
//TRISE:(where E is the port). This registers tells if the port is an output (bit value is 0) or input (bit value is 1)
//TRISESET: Den sätter alla bits till 1 (gör de input)
//TRISECLR: Den sätter alla bits till 0  (gör de output)

//Q3
//$v-registers

//Q4
// PE pin 26
// PD  pin 36


