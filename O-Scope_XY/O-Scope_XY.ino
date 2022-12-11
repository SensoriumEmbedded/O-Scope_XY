
//Todo:
//  Modes: Clock, Demo mode or Step through each
//  show mode name, routine name, etc
//    all routines return on button or timeout?
// bmp import

// spiral/vertigo illusion
// incorporate some of this? \O-Scope_XY\other-ref\OsciDisplay-master\OsciVector
//  Speech option?  (DACs being used)

//HW: 
// Up, Down, and select/cancel.
//  * Button for clock set?
//  * Select mode button or octal select

//Reference:
//    drawRampDACs execution time benchmark (256 points X and Y)
//       Dual DAC output from Teensy version 3.5 & 3.6 only. 
//       Teensy 3.5 120MHz, Faster (default):           2283 Hz = 584k dots/sec   9741dots at 60fps (14% of all points)
//       Teensy 3.5 120MHz, Fastest:                    2674 Hz
//       Teensy 3.5 120MHz, Fastest+pure-code:          2841 Hz
//       Teensy 3.5 120MHz, Fastest with LTO:           5714 Hz  (same when pure-code added to this)
//       Teensy 3.5 168MHz (overclock), Faster:         2874 Hz
//       Teensy 3.5 168MHz (overclock), Fastest:        3311 Hz
//       Teensy 3.5 168MHz (ovrclk), Fastest with LTO:  6623 Hz
//       Teensy 3.6 180MHz, Faster (default):           4000 Hz     
//       Teensy 3.6 180MHz, Fastest with LTO:           6061 Hz     
//       Teensy 3.6 256MHz (ovrclk), Fastest with LTO:  7813 Hz (3.4x faster than 3.5 default)
//       ESP32 Dev Mod using dacWrite function           103 Hz Crazy slow!
//      *ESP32 Dev Mod using FastDAC method:            4032 Hz (1.7x faster than 3.5 default, same as 3.6 default)  
//       ESP32-S2 (small) tested w/dacWrite but not measured, too slow; won't run FastDAC code 

//  ESP32 FastDAC via bitluni https://github.com/bitluni/OsciDisplay
//  Tek Block letter XY coords and spin effect idea: Alan Wolke 2013
//  Tek Logos and line draw code: https://www.qsl.net/w2aew/code/logor2r.ino
//  16 seg display decoder by Dave Madison: https://github.com/dmadison/LED-Segment-ASCII

#define usingESP32  //Comment out for Teensy 3.5/3.6

#include <TimeLib.h>
#include "Patterns.h"
#include "16-Segment-ASCII_BIN-NDP.h"

#ifdef usingESP32
 #include "FastDAC.h"
 #include <WiFi.h>
 #define LOCAL_UDP_PORT       8888 // local port to listen for UDP packets
 int timeZone = -8;  //Pacific Daylight Savings Time (USA)
 char WiFiSSID[] = "NETGEAR27";
 char WiFiPassword[] = "silenthippo917";
 char ntpServerName[32] = "us.pool.ntp.org";  // NetTimeProtocol Server name
 IPAddress ntpServerIP; // NTP server's ip address, resolved from name at WiFi connect
 WiFiUDP Udp;
 WiFiClient client; // Use WiFiClient class to create HTTP/TCP connection
#else
 #define X_Pin       A21
 #define Y_Pin       A22
#endif

#define Button1_Pin  33
#define Button2_Pin  32

#define pi 3.14159

void setup() 
{
  Serial.begin(115200);
  //while (!Serial);

#ifdef usingESP32
  dac_output_enable(DAC_CHANNEL_1);
  dac_output_enable(DAC_CHANNEL_2);
  DACPrepare(false);
  WifiConnect();
#else
  pinMode (X_Pin, OUTPUT);
  pinMode (Y_Pin, OUTPUT);
  setTime(4,20,0,20,4,23);
#endif

  pinMode (Button1_Pin, INPUT_PULLUP);
  pinMode (Button2_Pin, INPUT_PULLUP);
  
  Serial.println("Welcome to O-Scope XY !");
}

void loop() 
{
   //test patterns:
   //drawRampDACs(); //returns on button push
   //drawFillAll(); //returns on button push
   //drawDotField(1000);
   //drawPattern(BoxX_pat, sizeof(BoxX_pat), 1000);
   //drawCharScales(2000);
   

   drawAnalogClock(100000);
 
   //drawPattern(H_Leaf, sizeof(H_Leaf), 500);
   //animSpinPattern(H_Leaf, sizeof(H_Leaf), 4);
   //drawPattern(H_Leaf, sizeof(H_Leaf), 500);
   //drawPattern(starburst, sizeof(starburst), 2000);  
   //animGeoPatOTF();
   ////animGeoPatFramed();
   //drawPattern(trav, sizeof(trav), 1000);
   //animSpinPattern(trav, sizeof(trav), 5);
   //drawPattern(tree, sizeof(tree), 2500);
   //
   //drawPattern(logo, sizeof(logo), 2500);
   //drawPattern(wizardidd, sizeof(wizardidd), 2500);
   //animSpinPattern(tek_letters, sizeof(tek_letters), 5);
   ////delay(750);
   
}
   
bool WifiConnect()
{
  Serial.printf("Connecting to SSID %s\n", WiFiSSID);
  WiFi.disconnect(); 
  WiFi.mode(WIFI_STA);
  WiFi.persistent(false);
  WiFi.setSleep(false); // Don't allow WiFi sleep
  WiFi.begin(WiFiSSID, WiFiPassword);
  
  uint8_t WaitCycles = 30; //~15 seconds (seeing 5 sec typical)
  while (WiFi.status() != WL_CONNECTED) 
  {
    if (WaitCycles-- == 0)
    {
      Serial.println("* Timeout waiting for Wifi Connect");
      return false;
    }
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("\nWiFi connected");  
  Serial.print("IP address: ");  Serial.println(WiFi.localIP());
  Serial.printf("Signal strength (RSSI): %d dBm\n", WiFi.RSSI());
  if (WiFi.RSSI() == 0) 
  {
    Serial.println("No Signal?");
    return false;
  }
  
  Serial.println("Starting UDP");
  Udp.begin(LOCAL_UDP_PORT);
  //Done at connect instead of each synch as this resolution can take >1 sec, causing output glitch (though typically <20mS)
  WiFi.hostByName(ntpServerName, ntpServerIP); // get a random server IP from the pool via name
  Serial.printf("Time server: %s     IP: ", ntpServerName);
  Serial.println(ntpServerIP);

  Serial.println("Setting synch provider");
  setSyncProvider(getNtpTime);
  setSyncInterval(3);  //seconds (300 in example)

  Serial.println("Connected to WiFi");
  return true;
}

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  Serial.printf("Updating time from: %s      IP: ", ntpServerName);
  Serial.println(ntpServerIP);
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  sendNTPpacket(ntpServerIP); //only 1-2mS

  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) 
  {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) 
    {
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      Serial.printf("Received NTP Response in %d mS\n", (millis() - beginWait));  //typical <120 mS or timeout
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("NTP Response timeout");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}