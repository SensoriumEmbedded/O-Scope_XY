
void animGeoPatFramed()
{
   unsigned char Pattern[128];
   double angle;
   double angleInc = 3.14159*33/32;
   
   for(int numpat=0; numpat<128; numpat++)
   {
      angle = 0;
      for (uint16_t i=0; i<sizeof(Pattern); i+=2)
      {
         Pattern[i] = sin(angle)*120+128;
         Pattern[i+1] = cos(angle)*120+128;
         angle += angleInc;
         //drawLine(x1, y1, x2, y2)
      }
      animShowPattern(Pattern, sizeof(Pattern), 100);
      angleInc += 3.14159/32;
   }
}

void animGeoPatOTF()
{
   unsigned char X, Y, oldX, oldY; //Pattern[128];
   bool InitDone = false;
   double angle;
   double angleInc = 3.14159/180*178.5;
   
   angle = 0;
   for(int numpat=0; numpat<220; numpat++)
   {
      angleInc += 3.14159/180*1.6;
      for (int i=0; i<270; i++)
      {
         X = sin(angle)*120+128;
         Y = cos(angle)*120+128;
         angle += angleInc;
         if (InitDone) drawLine(X, Y, oldX, oldY);
         else InitDone = true;
         oldX=X;
         oldY=Y;
      }
   }
}

void animSpinPattern(prog_uchar *image, int imagesize, uint8_t NumSpins) 
{
   bool darkvector;
   uint16_t i=0;
   
   for (float angle = pi/2; angle < pi/2*(NumSpins*4+1) ; angle+=0.005) 
   { //Start at full scale
      i = 0;
      darkvector = false;
      byte x1 = 128+(pgm_read_byte_near(image+i++)-128)*sin(angle); //scale it!
      byte y1 = pgm_read_byte_near(image+i++);
      while (i < imagesize) 
      {
          byte x2 = pgm_read_byte_near(image+i++);
          if (x2 == 255) 
          { // dark drawLine (move)
              x2 = pgm_read_byte_near(image+i++);
              darkvector = true;
          }
          x2= 128+(x2-128)*sin(angle);  //scale it!
          byte y2 = pgm_read_byte_near(image+i++);
          if (!darkvector) drawLine(x1, y1, x2, y2);
          else darkvector = false;
          x1 = x2;
          y1 = y2;
      }
   }
}

void animShowPattern(prog_uchar *image, int imagesize, uint32_t TimeMs) 
{
   uint32_t StartMillis = millis();
   while (millis() - StartMillis < TimeMs) 
   {
      drawPattern(image, imagesize);
      
      SelButton.update();
      if(SelButton.pressed()) return;
      //UpButton.update();
      //if(UpButton.isPressed()) adjustTime(1);
      //DownButton.update();
      //if(DownButton.isPressed()) adjustTime(60);
   }
}

void animShowDotField(uint32_t TimeMs) 
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

void animAnalogClock(uint32_t TimeMs)
{
   uint32_t StartMillis = millis();
   
   while (millis() - StartMillis < TimeMs)
   {
      drawAnalogClock();
      
      drawDigitalClock(64, 74, 2);
      drawDate(88, 64, 1);
      
      SelButton.update();
      if(SelButton.pressed()) return;
      UpButton.update();
      if(UpButton.pressed()) adjustTime(1);
      DownButton.update();
      if(DownButton.pressed()) adjustTime(60);
   } 
   
}

void animRampDACs()
{
   while(digitalRead(btnUp_Pin))
   {
      for (uint16_t i=0; i<256; i++)
      {
         drawPoint(i, 255-i);
      }
   }
}

void animFillAll()
{
   while(digitalRead(btnDn_Pin))
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

void animCharScales(uint32_t TimeMs)
{
   for(uint8_t Scale = 1; Scale<=10; Scale++)
   {
      uint32_t StartMillis = millis();
      while (millis() - StartMillis < TimeMs)
      {
         drawAllChars(Scale);
      }
   }
}
