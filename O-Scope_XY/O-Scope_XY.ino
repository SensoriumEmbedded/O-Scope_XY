
//Todo:
//  * combine this, dots patter, and clock into 1 sketch
//   Modes: Demo mode or Step through each
//  display letters/string;  "Digital" Clock option


//HW: 
//  * Button for clock set?
//  * Select mode button or octal select
//  * RTC or WiFi for time synch


//Original: https://www.qsl.net/w2aew/code/logor2r.ino

#include "Patterns.h"

//Dual DAC output from Teensy version 3.5 & 3.6 only. 
#define X_Pin A21
#define Y_Pin A22

void setup() 
{
  pinMode (X_Pin, OUTPUT);
  pinMode (Y_Pin, OUTPUT);
  
  Serial.begin(115200);
  //while (!Serial);
  Serial.println("Welcome to XY Scope!");
}

void loop() 
{
   drawPattern(test_pat, sizeof(test_pat), 1000);
   drawPattern(starburst, sizeof(starburst), 2000);  
   animGeoPatOTF();
   //animGeoPatFramed();
   drawPattern(trav, sizeof(trav), 3000);
   drawPattern(xmastree, sizeof(xmastree), 2500);
   drawPattern(logo, sizeof(logo), 2500);
   drawPattern(wizardidd, sizeof(wizardidd), 2500);
   delay(750);
}
   
