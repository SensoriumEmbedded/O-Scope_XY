
//Todo:
//  * combine this, dots patter, and clock into 1 sketch

//HW: 
//  * Button for clock set?
//  * Select mode: 
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
#if 0
   //test pattern
   vector(0,0,254,0);
   vector(254,0,254,254);
   vector(254,254,0,254);
   vector(0,254,0,0);
   vector(0,0,254,254);
   vector(0,254,254,0);
   vector(254,254,0,0);
   vector(254,0,0,254);
   
#else
   drawpattern();
   drawloop(trav, sizeof(trav), 3500);
   drawloop(xmastree, sizeof(xmastree), 2500);
   drawloop(wizardidd, sizeof(wizardidd), 2500);
   drawloop(logo, sizeof(logo), 2500);
   drawloop(starburst, sizeof(starburst), 2500);  
#endif
}
   
void plot(int x, int y)
{
   analogWrite(X_Pin, x);
   analogWrite(Y_Pin, y);
}

/*  Quadrants
    2  |  1
-------|-----
    3  |  4

*/
void vector(byte x1, byte y1, byte x2, byte y2)
{
    // optimized implementation of Bresenham's Algorithm
    // also known as a DDA - digital differential analyzer
    int acc;

    // special routines for horizontal and vertical lines
    // to improve performance of the SPI version
    // aren't needed for the direct-load DAC
#if 0
  if (x1 == x2) { // trivial vertical
        if (y1 < y2)  { // up
            for (; y1 < y2; y1++) {
                plot(x1, y1);
            }
          }
        else {   // down
            for (; y1 > y2; y1--) {
                plot(x1, y1);
            }
         }
    }
    else if (y1 == y2) { // trivial horizontal
        if (x1 < x2) { // right
            for (; x1 < x2; x1++) {
                plot(x1, y1);
            }
        }
        else {  // left
            for (; x1 > x2; x1--) {
                plot(x1, y1);
            }
        }
    }
    else
#endif
    // for speed, there are 8 DDA's, one for each octant
    if (y1 < y2) { // quadrant 1 or 2
        byte dy = y2 - y1;
        if (x1 < x2) { // quadrant 1
            byte dx = x2 - x1;
            if (dx > dy) { // < 45
                acc = (dx >> 1);
                for (; x1 < x2; x1++) {
                    plot(x1, y1);
                    acc -= dy;
                    if (acc < 0) {
                        y1++;
                        acc += dx;
                    }
                }
            }
            else {   // > 45
                acc = dy >> 1;
                for (; y1 < y2; y1++) {
                    plot(x1, y1);
                    acc -= dx;
                    if (acc < 0) {
                        x1++;
                        acc += dy;
                    }
                }
            }
        }
        else {  // quadrant 2
            byte dx = x1 - x2;
            if (dx > dy) { // < 45
                acc = dx >> 1;
                for (; x1 > x2; x1--) {
                    plot(x1, y1);
                    acc -= dy;
                    if (acc < 0) {
                        y1++;
                        acc += dx;
                    }
                }
            }
            else {  // > 45
                acc = dy >> 1;
                for (; y1 < y2; y1++) {
                    plot(x1, y1);
                    acc -= dx;
                    if (acc < 0) {
                        x1--;
                        acc += dy;
                    }
                }
            }        
        }
    }
    else { // quadrant 3 or 4
        byte dy = y1 - y2;
        if (x1 < x2) { // quadrant 4
            byte dx = x2 - x1;
            if (dx > dy) {  // < 45
                acc = dx >> 1;
                for (; x1 < x2; x1++) {
                    plot(x1, y1);
                    acc -= dy;
                    if (acc < 0) {
                        y1--;
                        acc += dx;
                    }
                }
            
            }
            else {  // > 45
                acc = dy >> 1;
                for (; y1 > y2; y1--) {
                    plot(x1, y1);
                    acc -= dx;
                    if (acc < 0) {
                        x1++;
                        acc += dy;
                    }
                }

            }
        }
        else {  // quadrant 3
            byte dx = x1 - x2;
            if (dx > dy) { // < 45
                acc = dx >> 1;
                for (; x1 > x2; x1--) {
                    plot(x1, y1);
                    acc -= dy;
                    if (acc < 0) {
                        y1--;
                        acc += dx;
                    }
                }

            }
            else {  // > 45
                acc = dy >> 1;
                for (; y1 > y2; y1--) {
                    plot(x1, y1);
                    acc -= dx;
                    if (acc < 0) {
                        x1--;
                        acc += dy;
                    }
                }
            }
        }
    
    }
}

void drawloop(prog_uchar *image, int imagesize, int TimeMs) 
{
   elapsedMillis NumMillis;
   while (NumMillis < TimeMs) draw(image, imagesize);
}

void draw(prog_uchar *image, int imagesize) 
{
    bool darkvector = false;
    int i = 0;
    byte x1 = pgm_read_byte_near(image+i++);
    byte y1 = pgm_read_byte_near(image+i++);
    while (i < imagesize) 
    {
        byte x2 = pgm_read_byte_near(image+i++);
        if (x2 == 255) 
        { // dark vector (move)
            x2 = pgm_read_byte_near(image+i++);
            darkvector = true;
        }
        byte y2 = pgm_read_byte_near(image+i++);
        if (!darkvector) vector(x1, y1, x2, y2);
        else darkvector = false;
        x1 = x2;
        y1 = y2;
    }
}

void drawpattern()
{
   unsigned char Pattern[128];
   double angle;
   double angleInc = 3.14159*33/32;
   
   for(int numpat=0; numpat<128; numpat++)
   {
      angle = 0;
      for (int i=0; i<sizeof(Pattern); i+=2)
      {
         Pattern[i] = sin(angle)*120+128;
         Pattern[i+1] = cos(angle)*120+128;
         angle += angleInc;
         //vector(x1, y1, x2, y2)
      }
      drawloop(Pattern, sizeof(Pattern), 100);
      angleInc += 3.14159/32;
   }
}


