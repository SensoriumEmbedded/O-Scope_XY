
//Todo:
//  * combine this, dots pattern (anim?), and clock 
//   Modes: Demo mode or Step through each
//  display letters/string;  "Digital" Clock option?
//  Speech option?  (DACs being used)

//HW: 
// Change to ESP32?  (Has Dual DACs too)
//    tried ESP32-S2, too slow (try DMA or full ESP32?) uses dacWrite instead of analogWrite
//  * Button for clock set?
//  * Select mode button or octal select
//  * RTC or WiFi for time synch
// BNC interface...


//Original: https://www.qsl.net/w2aew/code/logor2r.ino

#include "Patterns.h"

//Dual DAC output from Teensy version 3.5 & 3.6 only. 
#define X_Pin A21
#define Y_Pin A22

#define pi 3.14159

void setup() 
{
  pinMode (X_Pin, OUTPUT);
  pinMode (Y_Pin, OUTPUT);
  
  Serial.begin(115200);
  //while (!Serial);
  Serial.println("Welcome to O-Scope XY !");
}

void loop() 
{
   
   drawPattern(test_pat, sizeof(test_pat), 1000);
   drawPattern(starburst, sizeof(starburst), 2000);  
   animGeoPatOTF();
   //animGeoPatFramed();
   drawPattern(trav, sizeof(trav), 1000);
   animSpinPattern(trav, sizeof(trav), 5);
   drawPattern(xmastree, sizeof(xmastree), 2500);
   
   drawPattern(logo, sizeof(logo), 2500);
   drawPattern(wizardidd, sizeof(wizardidd), 2500);
   animSpinPattern(tek_letters, sizeof(tek_letters), 5);
   delay(750);
}
   
