

bool animGeoPat()
{
   unsigned char X, Y, oldX, oldY; //Pattern[128];
   bool InitDone = false;
   double angle;
   double angleInc = pi/180*178.5;
   
   angle = 0;
   for(int numpat=0; numpat<220; numpat++)
   {
      angleInc += pi/180*1.6;
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
      SelButton.update();
      if(SelButton.pressed()) return true;
   }
   return false;
}

bool animSpinPattern(prog_uchar *image, int imagesize, uint8_t NumSpins) 
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
      SelButton.update();
      if(SelButton.pressed()) return true;
   }
   return false;
}

bool animShowPattern(prog_uchar *image, int imagesize, uint32_t TimeMs, const char *title) 
{
   uint32_t StartMillis = millis();
   while (millis() - StartMillis < TimeMs) 
   {
      drawPattern(image, imagesize);
      if (millis() - StartMillis < 2000) drawString(title, 0, 230, 2.5);
      
      SelButton.update();
      if(SelButton.pressed()) return true;
   }
   return false;
}

bool animShowString(const char * Msg, int16_t X, int16_t Y, float Scale, uint32_t TimeMs)
{
   uint32_t StartMillis = millis();
   while (millis() - StartMillis < TimeMs) 
   {
      drawString(Msg, X, Y, Scale);
      SelButton.update();
      if(SelButton.pressed()) return true;
   }
   return false;
}

void animShowDotField() 
{
   float increment = 15.999;
   uint32_t StartMillis = millis();
   
   do
   {
      for (float x = 0; x < 256; x+=increment) 
      {
         for (float y = 0; y < 256; y+=increment) 
         {
            drawPoint(x, y);
         }
      }
      SelButton.update();
   } while (!SelButton.pressed());
}

bool animAnalogClock(uint32_t TimeMs)
{
   uint32_t StartMillis = millis();
   bool showDig = true;
   
   while (millis() - StartMillis < TimeMs)
   {
      drawAnalogClock();
      
      if (showDig)
      {
         drawDigitalClock(44, 74, 2.5);
         drawDate(66, 56, 1.5);
      }
      SelButton.update();
      if(SelButton.pressed()) return true;
      UpButton.update();
      if(UpButton.pressed()) adjustTime(3600);
      DownButton.update();
      if(DownButton.pressed()) adjustTime(60);
   } 
   return false;
}

void animRampDACs()
{
   do
   {
      for (uint16_t i=0; i<256; i++) drawPoint(i, 255-i);
      SelButton.update(); //benchmark testing just did digital read in while loop, this may slow it slightly?
   } while (!SelButton.pressed());
}

void animFillAll()
{
   do
   {
      for (uint16_t x=0; x<256; x++)
      {
         for (uint16_t y=0; y<256; y++) drawPoint(x, y);
      }
      SelButton.update(); 
   } while (!SelButton.pressed());
}

void animCharScales()
{
   while(1)
   {
      for(float Scale = 1; Scale<=10; Scale+=0.25)
      {
         uint32_t StartMillis = millis();
         while (millis() - StartMillis < 250)
         {
            drawAllChars(Scale);
            SelButton.update(); 
            if (SelButton.pressed()) return;
         }
      }
   }
}

void animMenu()
{
   char Buf[][13]={"Demo  Loop", "Analog Clock", "By Others", "Test Patts"};
   uint8_t numEntries = sizeof(Buf)/13;
   uint8_t selection = 0;

   while(1)
   {      
      drawString("Select from:", 0, 225, 2.8);
      for(uint8_t entNum = 0; entNum<numEntries; entNum++)
      {
         drawString(Buf[entNum], 20, 180-entNum * 30, 2.5);
      }
      drawString("*", 0, 182-selection * 30, 2.0);
      
      SelButton.update();
      if(SelButton.pressed()) 
      {
         switch (selection)  
         {//"Demo Loop", "Analog Clock", "By Others", "Test Patts"
         case 0: 
            animDemoLoop();
            break;
         case 1:
            animAnalogClock(-1);
            break;
         case 2:
            animByOthers();
            break;
         case 3:  //test patterns
            //Select to progress through each, these return on button push only
            animShowString("Select for next", 0, 200, 2, -1);
            animRampDACs();
            animShowDotField();
            animCharScales();
            animShowPattern(BoxX_pat, sizeof(BoxX_pat), -1, "");
            animFillAll();
            animShowPattern(starburst,   sizeof(starburst), -1, "");
            break;
         //default:
         }
      }
      
      UpButton.update();
      if(UpButton.pressed()) 
      {
         if(selection==0) selection=numEntries-1;
         else selection--;
      }
      
      DownButton.update();
      if(DownButton.pressed())
      {
         selection++;
         if(selection==numEntries) selection=0;
      }

   }
}

void animByOthers()
{
   if(animShowString("Created by others", 0, 200, 3, 2000)) return;
   if(animShowPattern(tek_logo,    sizeof(tek_logo),    4000, "Tek Logo")      ) return;
   if(animShowPattern(wizardidd,   sizeof(wizardidd),   4500, "Wizard of Idd") ) return;
   if(animShowPattern(starburst,   sizeof(starburst),   2000, "Starburst")     ) return;
   if(animShowPattern(tek_letters, sizeof(tek_letters), 2000, "Tek Letters")   ) return;
   if(animSpinPattern(tek_letters, sizeof(tek_letters), 2)                     ) return;
}

void animDemoLoop()
{
   if(animShowString("Demo  Loop", 0, 200, 5, 1750)) return;
   while(1)
   {
      if(animShowPattern(H_Leaf, sizeof(H_Leaf), 3000, "H's Leaf") ) return;
      if(animSpinPattern(H_Leaf, sizeof(H_Leaf), 3)                ) return;
      
      if(animGeoPat()                                              ) return;
      
      if(animAnalogClock(8000)                                     ) return;
      
      if(animShowPattern(trav, sizeof(trav), 1000, "Trav's Trav")  ) return;
      if(animSpinPattern(trav, sizeof(trav), 3)                    ) return;
      if(animShowPattern(trav, sizeof(trav), 1000, "")  ) return;
   }
}

