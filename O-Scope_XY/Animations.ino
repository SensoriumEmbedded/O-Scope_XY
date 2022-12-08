
void animGeoPatFramed()
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
         //drawLine(x1, y1, x2, y2)
      }
      drawPattern(Pattern, sizeof(Pattern), 100);
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

