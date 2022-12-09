



void drawPoint(int x, int y)
{
   analogWrite(X_Pin, x);
   analogWrite(Y_Pin, y);
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

void drawPatternOnce(prog_uchar *image, int imagesize) 
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

/*******************repeating patterns/shapes*******************/

void drawPattern(prog_uchar *image, int imagesize, uint32_t TimeMs) 
{
   uint32_t StartMillis = millis();
   while (millis() - StartMillis < TimeMs) drawPatternOnce(image, imagesize);
}

void drawDotField(uint32_t TimeMs) 
{
   float increment = 15.999;
   uint32_t StartMillis = millis();
   
   while (millis() - StartMillis < TimeMs)
   {
      for (float x = 0; x < 256; x+=increment) 
      {
         for (float y = 0; y < 256; y+=increment) 
         {
            drawPoint(x, y);
         }
      }
   }
}

void drawAnalogClock(uint32_t TimeMs)
{
   uint32_t StartMillis = millis();
   float angle;
   
   while (millis() - StartMillis < TimeMs)
   {
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
      angle = angle/12 + hour()*pi/6;
      drawTriangleOffset(sin(angle)*60, cos(angle)*60,    sin(angle+pi*0.9)*25, cos(angle+pi*0.9)*25,  sin(angle-pi*0.9)*25, cos(angle-pi*0.9)*25);

      //center point
      drawPoint(128, 128); 
      
      if(!digitalRead(Button1_Pin)) adjustTime(1);
      if(!digitalRead(Button2_Pin)) adjustTime(60);
   } 
   
}

void drawRampDACs()
{
   while(digitalRead(Button1_Pin))
   {
      for (uint16_t i=0; i<256; i++)
      {
         drawPoint(i, 255-i);
      }
   }
}

void drawFillAll()
{
   while(digitalRead(Button2_Pin))
   {
      for (uint16_t x=0; x<256; x++)
      {
         for (uint16_t y=0; y<256; y++)
         {
            drawPoint(x, y);
         }
      }
   }
}