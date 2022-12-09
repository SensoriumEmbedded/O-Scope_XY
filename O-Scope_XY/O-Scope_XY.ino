
//Todo:
//   Modes: Clock, Demo mode or Step through each
//   all routines return on button or time?
//  display letters/string;  "Digital" Clock option?
// spiral/vertigo illusion
// bmp import
// incorporate some of this? \O-Scope_XY\other-ref\OsciDisplay-master\OsciVector
//  Speech option?  (DACs being used)

//HW: 
//  * Button for clock set?
//  * Select mode button or octal select
//  * batt backed RTC or WiFi for time synch
//       can add coin cell to Teensy
//       C:\Program Files (x86)\Arduino\hardware\teensy\avr\libraries\Time\examples\TimeTeensy3

//    drawRampDACs execution time benchmark (256 points X and Y)
//       Teensy 3.5 120MHz, Faster (default):          2283 Hz = 584k dots/sec   9741dots at 60fps (14% of all points)
//       Teensy 3.5 120MHz, Fastest:                   2674 Hz
//       Teensy 3.5 120MHz, Fastest+pure-code:         2841 Hz
//       Teensy 3.5 120MHz, Fastest with LTO:          5714 Hz  (same when pure-code added to this)
//       Teensy 3.5 168MHz (overclock), Faster:        2874 Hz
//       Teensy 3.5 168MHz (overclock), Fastest:       3311 Hz
//       Teensy 3.5 168MHz (ovrclk), Fastest with LTO: 6623 Hz
//       Teensy 3.6 180MHz, Faster (default):          4000 Hz     
//       Teensy 3.6 180MHz, Fastest with LTO:          6061 Hz     
//       Teensy 3.6 256MHz (ovrclk), Fastest with LTO: 7813 Hz (3.4x faster than 3.5 default)
//       ESP32 Dev Mod:                                 103 Hz   22x sloweer than T3.5
//       ESP32-S2 (small) tested but not measured, too slow 
//          ESPs use dacWrite instead of analogWrite, pins 25/26
//          try DMA?   See https://github.com/bitluni/OsciDisplay
//  Writing 1M Samples with API functions: 327011 Sa/s
//  Writing 1M Samples with FastDAC functions: 2044989 Sa/s  6.25x improvement


// Tek Block letter XY coords and spin effect idea: Alan Wolke 2013
// Tek Logos and line draw code: https://www.qsl.net/w2aew/code/logor2r.ino

#include <TimeLib.h>
#include "Patterns.h"

//Dual DAC output from Teensy version 3.5 & 3.6 only. 
#define X_Pin       A21
#define Y_Pin       A22
#define Button1_Pin  33
#define Button2_Pin  34

#define pi 3.14159

void setup() 
{
  pinMode (X_Pin, OUTPUT);
  pinMode (Y_Pin, OUTPUT);
  pinMode (Button1_Pin, INPUT_PULLUP);
  pinMode (Button2_Pin, INPUT_PULLUP);
  
  Serial.begin(115200);
  //while (!Serial);
  
  setTime(4,20,0,20,4,23);
  
  Serial.println("Welcome to O-Scope XY !");
}

void loop() 
{
   drawFillAll(); //returns on button push
   drawRampDACs(); //returns on button push
   drawAnalogClock(100000);
   
   //drawDotField(1000);
   //drawPattern(test_pat, sizeof(test_pat), 1000);
   //drawPattern(starburst, sizeof(starburst), 2000);  
   //animGeoPatOTF();
   ////animGeoPatFramed();
   //drawPattern(trav, sizeof(trav), 1000);
   //animSpinPattern(trav, sizeof(trav), 5);
   //drawPattern(xmastree, sizeof(xmastree), 2500);
   //
   //drawPattern(logo, sizeof(logo), 2500);
   //drawPattern(wizardidd, sizeof(wizardidd), 2500);
   //animSpinPattern(tek_letters, sizeof(tek_letters), 5);
   //delay(750);
   
}
   
