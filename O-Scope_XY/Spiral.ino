

struct Spiralst3Args
{ 
   float sOStep, sMStep, sIStep, sOScale, sMScale, sIScale;
   char  sTitle[20];
};

//imported .st3 files
//incorporate autoscale, /180*pi
//move to progmem
const struct Spiralst3Args st3Spiral[] = {
     0,  0.3,  3.9,   0,  35,  43, "TooDee",
  12.4,  6.2, 21.2,  89,  88,  78, "Breakout",
  22.7, 11.9,  8.3,  74,  39,  87, "Doilie",
  21.8, 12.8,  1.8,  14,   4,  47, "Penta-Curve",
  23.2,  8.2,  5.8,  41,  47,  98, "Triple Twist 2",
    53,  212,  106,  67,  25,  75, "Lopsi",
   0.1,  8.3,  4.1,   2,   1,   1, "Double Ball", 
   4.1, 16.1,  0.3,  91,  15,  54, "Hourglass",
  21.8,  5.3,  2.8,  37,  47,  49, "Penta-Tubes",
  11.5,   23,  0.8,  71,  64,  87, "Planes",
   8.6,  0.1,  0.3,  94,  77,  34, "Double Ring",
   6.1,  0.1,  6.4,  40,  94,  39, "3 Eggs",
  17.8,  0.1,  5.9,  38,  59,  55, "3 Holes",
  16.6,  0.1, 16.9,  65,  86,  48, "3 More Eggs",
  19.1,  3.2,  6.5,  32,  98,   4, "6 Sided Circles",
   2.5, 16.9, 16.3,  86,  66,  10, "6 Star",
   9.5,  2.3, 14.1,  27,  94,  20, "Big O",
  13.3,  9.3, 21.7,  23,  78,  98, "Celtic",
  11.3,  5.1,  2.7,  70,  45,   1, "Clam",
  15.4,  1.2,  7.1,  57,  39,  93, "Colision",
   0.2,  6.1, 19.1,  42,  23,  73, "Hex Circle",
  11.3,  0.6,  7.7,  22,  97,  31, "Hex Egg",
     2, 20.6,  1.5,  82,  61,  43, "Inset Circles",
   3.7,  2.2,    8,   0,  79,  32, "Iris",
   6.4,  7.8, 16.3,   8,  45,  60, "Lizard Eye",
  13.1, 16.8, 17.8,  51,  17,  22, "Love",
   5.7, 17.3,   23,  71,  55,  72, "Peach",
   3.9, 23.4, 22.2,  83,   2,  17, "Penta-Mouth",
   7.6,    4,  0.9,  45,  39,  62, "Quad Splash",
   3.5, 15.8,   14,  87,  47,  17, "Triple Ball Tube",
   4.2, 16.8, 19.7,  80,  53,  25, "Triple Twist",
};

struct SpiralsitArgs
{ 
   float sOStepFrom,  sMStepFrom,  sIStepFrom;
   float sOStepTo,    sMStepTo,    sIStepTo;
   float sOScaleFrom, sMScaleFrom, sIScaleFrom;
   float sOScaleTo,   sMScaleTo,   sIScaleTo;
   uint8_t sPctPerStep;
   char  sTitle[21];
};

//imported .sti files
//incorporate autoscale, /180*pi
//move to progmem
const struct SpiralsitArgs sitSpiral[] = {
  4.1, 16.1,  0.3,  4.1, 16.1,  0.3,  60,   15,   54,  91,   15,   15,   3, "Breathing Hourglass", 
  8.6,  0.1,  0.3,  8.6,  0.1,  0.3,  94,   77,   34,  30,   34,    5,   2, "Eclipse", 
 19.1,  3.2,  6.5, 19.1,  3.2,  6.5,   4,   98,    6,  60,   70,   10,   3, "Iris In", 
   4.2, 16.8, 19.7,  4.2, 16.8, 19.7,  80,   45,    1,  80,   45,   18,   4, "Triple Twist Growth", 
   15,  0.1,   .4,    1,  0.1,   .4,  94,   77,   34,  30,   34,    5,  2, "Tripple Eclipse", 
   15,  0.1,  1.1,   15,  0.1,   .2,  30,   34,    5,  94,   77,   34,   2, "Unpack", 
// 17.8,  0.1,  5.9, 17.8,  0.1,  5.9,  25,   59,   45,  50,   59,   45,   2, "3 holes", 
//   53,  212,  106,   53,  212,  106,  55,   25,   75,  50,   25,   75,   2, "Mobius", 
//  0.1,  8.3,  4.1,  0.1,  8.3,  4.1, 0.5, 0.25, 0.25, 0.5, 0.25, 0.25,   2, "Turn In Place", 
};

const struct SpiralsitArgs sitSDSpiral[] = {  //Sand Dollar Progression
// 16.1,  0.2, 16.3, 16.1,  0.2, 16.3,  26,   66,   62,  26,   66,   62,   3, "Sand Dollar01", 
 16.1,  0.2, 16.3, 16.1, -0.2, 16.3,  26,   66,   62,  26,   66,   62,   3, "Sand Dollar Prog", 
 16.1, -0.2, 16.3, 16.3, -0.2, 16.3,  26,   66,   62,  26,   66,   62,   3, "Sand Dollar03", 
 16.3, -0.2, 16.3, 16.3, -0.2, 16.5,  26,   66,   62,  26,   66,   62,   3, "Sand Dollar04", 
 16.3, -0.2, 16.5, 16.3, -0.2, 16.5,  26,   66,   62,  26,   66,    0,   6, "Sand Dollar05", 
 16.3, -0.2, 16.5, 16.3, -0.2, 16.5,  26,   66,    0,  26,   66,    0,   6, "Sand Dollar06", 
 16.3, -0.2, 16.5, 16.3, -0.2, 16.5,  26,   66,    0,  26,    0,    0,   3, "Sand Dollar07", 
 16.3, -0.2, 16.5, 16.3, -0.2, 16.5,  26,    0,    0,  26,    0,   25,   6, "Sand Dollar08", 
 16.3, -0.2, 16.5, 16.3, -0.2, 16.5,  26,    0,   25,  26,    0,   25,   6, "Sand Dollar09", 
 16.3, -0.2, 16.5, 16.3, -0.2, 16.5,  26,    0,   25,  26,  100,   25,   6, "Sand Dollar10", 
// 16.3, -0.2, 16.5, 16.3, -0.2, 16.5,  26,  100,   25,  26,  100,   25,   3, "Sand Dollar11", 
 16.3, -0.2, 16.5, 16.1, -0.2, 16.5,  26,  100,   25,  26,  100,   25,   3, "Sand Dollar12", 
 16.1, -0.2, 16.5, 16.1, -0.2, 16.5,  26,  100,   25,  26,   66,   62,   4, "Sand Dollar13", 
 16.1, -0.2, 16.5, 16.1, -0.2, 16.3,  26,   66,   62,  26,   66,   62,   4, "Sand Dollar14", 
 16.1, -0.2, 16.3, 16.1,  0.2, 16.3,  26,   66,   62,  26,   66,   62,   3, "Sand Dollar15", 
 16.1,  0.2, 16.3, 16.1,  0.2, 16.3,  26,   66,   62,  26,   66,   62,   4, "Sand Dollar16", 
};

bool animSpiralAngles()
{
   if(animShowString("Spiral Angle ranges", 0, 200, 3, 2000)) return true;
   for (uint8_t i =0; i< sizeof(st3Spiral)/sizeof(Spiralst3Args); i++)
   {
      Serial.printf("\nst3 #%d: %s...\n", i, st3Spiral[i].sTitle);
      if(animShowString(st3Spiral[i].sTitle, 0, 200, 3, 1500)) return true;
      
      for (float SMult=4.0; SMult <15.0; SMult+=0.5)
      {
         drawSpiral(st3Spiral[i], SMult, 7200); //1 draw takes a bit, no need for animShowSpiral here
         
         SelButton.update();
         if(SelButton.pressed()) return true;
         UpButton.update();
         if(UpButton.pressed()) Serial.printf("SMult = %f\n", SMult);;
         DownButton.update();
         if(DownButton.pressed()) break;
      }
   }
   return false;
}

void drawSpiral(struct Spiralst3Args spiralInfo, float StepMult, uint16_t NumStep)
{
   int16_t X, Y, oldX, oldY;
   float OAngle, MAngle, IAngle, OScale, MScale, IScale, OStep, MStep, IStep;
 
   //Auto Scale
   float AngTotal = spiralInfo.sOScale + spiralInfo.sMScale + spiralInfo.sIScale;
   OScale = spiralInfo.sOScale / AngTotal;
   MScale = spiralInfo.sMScale / AngTotal;
   IScale = spiralInfo.sIScale / AngTotal;

   OAngle = 0; 
   MAngle = 0; 
   IAngle = 0; 
      
   OStep = spiralInfo.sOStep * StepMult / 180 * pi;
   MStep = spiralInfo.sMStep * StepMult / 180 * pi;
   IStep = spiralInfo.sIStep * StepMult / 180 * pi;
   
   oldX = (cos(IAngle) * IScale + cos(MAngle) * MScale + cos(OAngle) * OScale) * 127 + 128;
   oldY = (sin(IAngle) * IScale + sin(MAngle) * MScale + sin(OAngle) * OScale) * 127 + 128;

   for(uint16_t i = 0; i<NumStep; i++)
   {
      OAngle += OStep;
      MAngle += MStep;
      IAngle += IStep;
      
      X = (cos(IAngle) * IScale + cos(MAngle) * MScale + cos(OAngle) * OScale) * 127 + 128;
      Y = (sin(IAngle) * IScale + sin(MAngle) * MScale + sin(OAngle) * OScale) * 127 + 128;

      //drawPoint(X, Y);
      drawLine(X, Y, oldX, oldY);
      oldX = X;
      oldY = Y;
   }
}

void animAllInfSpirals()
{
   if(animShowString("All Inf Spirals", 0, 200, 3, 2000)) return;
   for (uint8_t i =0; i< sizeof(st3Spiral)/sizeof(Spiralst3Args); i++)
   {
      Serial.printf("\nst3 #%d: %s...\n", i, st3Spiral[i].sTitle);
      if(animShowString(st3Spiral[i].sTitle, 0, 200, 3, 1000)) return;
      if(animInfSpiral(st3Spiral[i], 60000)) return;
   }
}

bool animInfSpiral(struct Spiralst3Args spiralInfo, uint32_t TimeMs)
{
   int16_t X, Y, oldX, oldY;
   float OAngle, MAngle, IAngle, OScale, MScale, IScale; //, OStep, MStep, IStep;
 
   //Auto Scale
   float AngTotal = spiralInfo.sOScale + spiralInfo.sMScale + spiralInfo.sIScale;
   OScale = spiralInfo.sOScale / AngTotal;
   MScale = spiralInfo.sMScale / AngTotal;
   IScale = spiralInfo.sIScale / AngTotal;

   OAngle = 0;
   MAngle = 0;
   IAngle = 0;
      
   oldX = (cos(IAngle) * IScale + cos(MAngle) * MScale + cos(OAngle) * OScale) * 127 + 128;
   oldY = (sin(IAngle) * IScale + sin(MAngle) * MScale + sin(OAngle) * OScale) * 127 + 128;

   float StepMult = 4.0; 
   
   uint32_t StartMillis = millis();
   while (millis() - StartMillis < TimeMs) 
   {
      StepMult +=0.00001;
      OAngle += spiralInfo.sOStep * StepMult / 180 * pi;
      MAngle += spiralInfo.sMStep * StepMult / 180 * pi;
      IAngle += spiralInfo.sIStep * StepMult / 180 * pi;
      
      X = (cos(IAngle) * IScale + cos(MAngle) * MScale + cos(OAngle) * OScale) * 127 + 128;
      Y = (sin(IAngle) * IScale + sin(MAngle) * MScale + sin(OAngle) * OScale) * 127 + 128;

      //drawPoint(X, Y);
      drawLine(oldX, oldY, X, Y);
      oldX = X;
      oldY = Y;
      
      SelButton.update();
      if(SelButton.pressed()) return true;
      UpButton.update();
      if(UpButton.pressed()) Serial.printf("SMult = %f\n", StepMult);;
      DownButton.update();
      if(DownButton.pressed()) break;
   }
   return false;
}


bool animIttSitSpiral()
{
   if (animIttSpiral(sitSpiral, sizeof(sitSpiral)/sizeof(SpiralsitArgs), true)) return true;
   if (animShowString(sitSDSpiral[0].sTitle, 0, 200, 3, 1500)) return true;
   if (animIttSpiral(sitSDSpiral, sizeof(sitSDSpiral)/sizeof(SpiralsitArgs), false)) return true;
   return false;
}

bool animIttSpiral(const struct SpiralsitArgs *ThisSitSet, uint16_t size, bool ShowTitle)
{
   struct Spiralst3Args NextSpiral;
   
   for(uint16_t sitNum = 0; sitNum < size; sitNum++)
   {
      Serial.printf("\nsit #%d: %s...\n", sitNum, ThisSitSet[sitNum].sTitle);
      if(ShowTitle) if(animShowString(ThisSitSet[sitNum].sTitle, 0, 200, 3, 1500)) return true;

      float stepAmt = ThisSitSet[sitNum].sPctPerStep/100.0;
      for(float stepRat=0; stepRat<=1.0; stepRat+=stepAmt)
      {
         NextSpiral.sOStep = ThisSitSet[sitNum].sOStepFrom +   (ThisSitSet[sitNum].sOStepTo - ThisSitSet[sitNum].sOStepFrom  ) * stepRat;
         NextSpiral.sMStep = ThisSitSet[sitNum].sMStepFrom +   (ThisSitSet[sitNum].sMStepTo - ThisSitSet[sitNum].sMStepFrom  ) * stepRat;
         NextSpiral.sIStep = ThisSitSet[sitNum].sIStepFrom +   (ThisSitSet[sitNum].sIStepTo - ThisSitSet[sitNum].sIStepFrom  ) * stepRat;
                                                                                                                          
         NextSpiral.sOScale = ThisSitSet[sitNum].sOScaleFrom + (ThisSitSet[sitNum].sOScaleTo - ThisSitSet[sitNum].sOScaleFrom) * stepRat;
         NextSpiral.sMScale = ThisSitSet[sitNum].sMScaleFrom + (ThisSitSet[sitNum].sMScaleTo - ThisSitSet[sitNum].sMScaleFrom) * stepRat;
         NextSpiral.sIScale = ThisSitSet[sitNum].sIScaleFrom + (ThisSitSet[sitNum].sIScaleTo - ThisSitSet[sitNum].sIScaleFrom) * stepRat;
      
         drawSpiral(NextSpiral, 4.0, 1800);
         
         SelButton.update();
         if(SelButton.pressed()) return true;
         //UpButton.update();
         //if(UpButton.pressed()) Serial.printf("SMult = %f\n", SMult);;
         DownButton.update();
         if(DownButton.pressed()) break;

      }
   }
   return false;
}


//  Hasn't been needed since drawSpiral takes so long and other parameters tweaked between...
//bool animShowSpiral(struct Spiralst3Args spiralInfo, uint32_t TimeMs)
//{
//   float StepMult = 5.0;
//   uint32_t StartMillis = millis();
//   while (millis() - StartMillis < TimeMs) 
//   {
//      drawSpiral(spiralInfo, StepMult, 3600);
//      
//      SelButton.update();
//      if(SelButton.pressed()) return true;
//      UpButton.update();
//      if(UpButton.pressed()) 
//      {
//         StepMult+=0.5;
//         Serial.printf("StepMult = %f\n", StepMult);
//      }
//      DownButton.update();
//      if(DownButton.pressed())
//      {
//         StepMult-=0.5;
//         Serial.printf("StepMult = %f\n", StepMult);
//      }
//         
//   }
//   return false;
//}


