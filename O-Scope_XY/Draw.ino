
//These routines (draw*) draw something once and return.  Itterations made by anim* routines

const uint8_t SixteenSegToXYPlot[32] = {
// converts 16 segment display segments to vector lines
// Each byte contains X (Upper nibble) and Y (Lower nibble) points, 2 points for line
// capable of 16x16, but only 6x8 used (before scaling)
//XY Start,	XY End
0x08,	0x38,	// seg a
0x38,	0x68,	// seg b
0x68,	0x64,	// seg c
0x64,	0x60,	// seg d
0x60,	0x30,	// seg e
0x30,	0x00,	// seg f
0x00,	0x04,	// seg g
0x04,	0x08,	// seg h
0x34,	0x08,	// seg k
0x34,	0x38,	// seg m
0x34,	0x68,	// seg n
0x34,	0x64,	// seg p
0x34,	0x60,	// seg r
0x34,	0x30,	// seg s
0x34,	0x00,	// seg t
0x34,	0x04,	// seg u
};



void drawPoint(int x, int y)
{
#ifdef usingESP32
   DAC1Write(x);
   DAC2Write(y);
#else
   analogWrite(X_Pin, x);
   analogWrite(Y_Pin, y);
#endif
}

void drawLine(byte x1, byte y1, byte x2, byte y2)
{
    // optimized implementation of Bresenham's Algorithm
    // also known as a DDA - digital differential analyzer
    int acc;

    // for speed, there are 8 DDA's, one for each octant
    //  Quadrants
    //  2  |  1
    // ----|----
    //  3  |  4
    if (y1 < y2) { // quadrant 1 or 2
        byte dy = y2 - y1;
        if (x1 < x2) { // quadrant 1
            byte dx = x2 - x1;
            if (dx > dy) { // < 45
                acc = (dx >> 1);
                for (; x1 < x2; x1++) {
                    drawPoint(x1, y1);
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
                    drawPoint(x1, y1);
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
                    drawPoint(x1, y1);
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
                    drawPoint(x1, y1);
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
                    drawPoint(x1, y1);
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
                    drawPoint(x1, y1);
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
                    drawPoint(x1, y1);
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
                    drawPoint(x1, y1);
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

void drawLineOffset(int x1, int y1, int x2, int y2)  
{//offset to center of display
   drawLine(x1+128, y1+128, x2+128, y2+128);
}

void drawTriangleOffset(int x1, int y1, int x2, int y2, int x3, int y3)  
{//offset to center of display
   drawLineOffset(x1, y1, x2, y2);
   drawLineOffset(x2, y2, x3, y3);
   drawLineOffset(x3, y3, x1, y1);
}

void drawCircle(uint8_t X, uint8_t Y, uint8_t Radius, float StepRad)
{
   for (float angle = 0; angle < 2*pi; angle+=StepRad)
      drawPoint(X+sin(angle)*Radius, Y+cos(angle)*Radius);
}

void drawPattern(prog_uchar *image, int imagesize) 
{
   bool darkvector = false;
   uint16_t i = 0;
   byte x1 = pgm_read_byte_near(image+i++);
   byte y1 = pgm_read_byte_near(image+i++);
   while (i < imagesize) 
   {
      byte x2 = pgm_read_byte_near(image+i++);
      if (x2 == 255) 
      { // dark drawLine (move)
          x2 = pgm_read_byte_near(image+i++);
          darkvector = true;
      }
      byte y2 = pgm_read_byte_near(image+i++);
      if (!darkvector) drawLine(x1, y1, x2, y2);
      else darkvector = false;
      x1 = x2;
      y1 = y2;
   }
}

void drawCharacter(uint8_t Character, int16_t *X, int16_t *Y, float Scale)
{
   //chars are 6x8 (before scaling)
   Character -= 32; //array starts at space (32)
   if (Character>=96) return; //only 96 characters

   if (*X + 6 * Scale >= 256) //will run over, wrap to next line (char is 6 wide)
   {
      *X=0;
      *Y-= 10 * Scale; //char height +2 spacing
   }
   if(*Y<0) return; //*Y = 255 - 10 * Scale; //wrap back to top(?)

   if (Character == ':'-32)
   { //special case for colon...
      drawLine(*X+Scale*3, *Y+Scale*2, *X+Scale*3, *Y+Scale*3);
      drawLine(*X+Scale*3, *Y+Scale*6, *X+Scale*3, *Y+Scale*7);
   }
   else
   {
      for (uint8_t bitnum = 0; bitnum < 16; bitnum++) 
      {
         if (SixteenSegmentASCII[Character] & (1<<bitnum))
         {
            drawLine(*X+Scale*(SixteenSegToXYPlot[bitnum*2] >> 4), *Y+Scale*(SixteenSegToXYPlot[bitnum*2] & 0x0f),
                 *X+Scale*(SixteenSegToXYPlot[bitnum*2+1] >> 4), *Y+Scale*(SixteenSegToXYPlot[bitnum*2+1] & 0x0f));
         }
      }
   }
   *X += 8 * Scale; //char width +2 spacing
}

void drawAllChars(float Scale)
{
   int16_t X = 0;
   int16_t Y = 255 - 10 * Scale;
   for(uint16_t cNum=48; cNum<128; cNum++) drawCharacter(cNum, &X, &Y, Scale);
   for(uint16_t cNum=32; cNum< 48; cNum++) drawCharacter(cNum, &X, &Y, Scale);
}

void drawString(const char * Msg, int16_t X, int16_t Y, float Scale)
{
   while(*Msg) drawCharacter(*Msg++, &X, &Y, Scale);
}

void drawDigitalClock(int16_t X, int16_t Y, float Scale)
{
   char Buf[15];
   
   //sprintf(Buf, "%d:%02d:%02d %s", hourFormat12(), minute(), second(), isPM() ? "pm":"am");
   sprintf(Buf, "%d:%02d:%02d", hourFormat12(), minute(), second());
   drawString(Buf, X, Y, Scale);
}

void drawDate(int16_t X, int16_t Y, float Scale)
{
   char Buf[15];
   
   sprintf(Buf, "%02d/%02d/%02d", month(), day(), year());
   drawString(Buf, X, Y, Scale);
}

void drawAnalogClock()
{
   float angle;
   
   //outer circle, dot per minute:
   drawCircle(128, 128, 127, pi/30); 
   
   //tick marks on hour:
   for (angle = 0; angle < 2*pi; angle+=pi/6) 
      drawLineOffset(sin(angle)*127, cos(angle)*127, sin(angle)*100, cos(angle)*100);
   
   //second hand, digital movement
   angle = second()*pi/30; 
   drawLineOffset(sin(angle+pi)*25, cos(angle+pi)*25, sin(angle)*100, cos(angle)*100);
   
   //minute hand, analog movement
   angle = angle/60 + minute()*pi/30;
   drawTriangleOffset(sin(angle)*110, cos(angle)*110,  sin(angle+pi*0.9)*20, cos(angle+pi*0.9)*20,  sin(angle-pi*0.9)*20, cos(angle-pi*0.9)*20);
  
   //hour hand, analog movement
   angle = angle/12 + hourFormat12()*pi/6;
   drawTriangleOffset(sin(angle)*60, cos(angle)*60,    sin(angle+pi*0.9)*25, cos(angle+pi*0.9)*25,  sin(angle-pi*0.9)*25, cos(angle-pi*0.9)*25);

   //center point
   drawPoint(128, 128); 
}