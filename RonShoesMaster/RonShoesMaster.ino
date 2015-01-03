#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_LSM303.h>

#define PIN           6
#define BUTTON_PIN    A9
#define SHOE_SIZE     40




Adafruit_NeoPixel strip = Adafruit_NeoPixel(SHOE_SIZE, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_LSM303 lsm;

int buttonRead;
int phase = 6;
int change = 0;
int previousRead;
int truepress = 0;
int currentx;
int currenty;
int currentz;
int previousx;
int previousy;
int previousz;
int chgup = 50;
int mode = 1;
boolean trigger;

void setup() 
{
  strip.begin();
  Serial.begin(9600);
  strip.show(); // Initialize all pixels to 'off'
    if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }

}


void modeChange()
{
   buttonRead = analogRead(BUTTON_PIN);
   if(buttonRead == 0)
  {
    if(buttonRead == previousRead)
      {
        Serial.println("Press");
        delay(10);
        truepress++;
        Serial.print("True Press: ");
        Serial.println(truepress);
      }
      else
        {
          truepress = 0;
        }
  
      if(truepress == 20)
        {
          mode = mode + 1;
          Serial.println("FUCK YO Couch!");
          Serial.print("Mode is: ");
          Serial.println(mode);
        }
  }
      previousRead = buttonRead;
}  
  


void loop() 
{
  lsm.read();

 modeChange();
//  Serial.print("truepress = ");
//  Serial.println(truepress);

    
    if(change < 0)
    {
      change = 0;
    }
    
    if(change > 350)
    {
      change = 350;
    }


  
    currentx = lsm.accelData.x;
    currenty = lsm.accelData.y;
    currentz = lsm.accelData.z;

    currentx = abs(currentx);
    currenty = abs(currenty);
    currentz = abs(currentz);
    
    
 if(previousx - currentx > 1150 || previousy - currenty > 1150 || previousz - currentz > 1150)
   {
      Serial.print("CX: ");Serial.print(currentx);Serial.print(" (");Serial.print(currentx-previousx);Serial.println(")"); 
      Serial.print("CY: ");Serial.print(currenty);Serial.print(" (");Serial.print(currenty-previousy);Serial.println(")"); 
      Serial.print("CZ: ");Serial.print(currentz);Serial.print(" (");Serial.print(currentz-previousz);Serial.println(")"); 
      Serial.println("Extreme Movement"); 
      change = change + 250;
      trigger = true;
   }
   else if(previousx - currentx > 750 || previousy - currenty > 750 || previousz - currentz > 750)
   {
      Serial.print("CX: ");Serial.print(currentx);Serial.print(" (");Serial.print(currentx-previousx);Serial.println(")"); 
      Serial.print("CY: ");Serial.print(currenty);Serial.print(" (");Serial.print(currenty-previousy);Serial.println(")"); 
      Serial.print("CZ: ");Serial.print(currentz);Serial.print(" (");Serial.print(currentz-previousz);Serial.println(")"); 
      Serial.println("Large Movement"); 
      change = change + 25;
      trigger = true;
   }
   else if(previousx - currentx > 425 || previousy - currenty > 425 || previousz - currentz > 425)
   {
      Serial.print("CX: ");Serial.print(currentx);Serial.print(" (");Serial.print(currentx-previousx);Serial.println(")"); 
      Serial.print("CY: ");Serial.print(currenty);Serial.print(" (");Serial.print(currenty-previousy);Serial.println(")"); 
      Serial.print("CZ: ");Serial.print(currentz);Serial.print(" (");Serial.print(currentz-previousz);Serial.println(")"); 
      Serial.println("Medium Movement"); 
      change = change + 15;
      trigger = true;
   }
   else if(previousx - currentx > 150 || previousy - currenty > 150 || previousz - currentz > 150)
   {
/*      Serial.print("CX: ");Serial.print(currentx);Serial.print(" (");Serial.print(currentx-previousx);Serial.println(")"); 
      Serial.print("CY: ");Serial.print(currenty);Serial.print(" (");Serial.print(currenty-previousy);Serial.println(")"); 
      Serial.print("CZ: ");Serial.print(currentz);Serial.print(" (");Serial.print(currentz-previousz);Serial.println(")"); 
      Serial.println("Small Movement"); */
      change = change + 8;
      trigger = true;
   }
  previousx = currentx;
  previousy = currenty;
  previousz = currentz;
  
  if(mode == 1)    
    {
      fireFeet();
    }
   else if(mode == 2)
    {
      blackLight();
    }
   else if(mode == 3)
    {
       pixie();
    }
    else if(mode == 4)
    {
      nightLight();
    }
    else if(mode == 5)
    {
      fireball(15);
    }
    else
    {
      if(mode >= 7)
      {
        mode = 1;
      }
    }
  
  
}


uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}



  

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}




void blackLight()
{
    for(int i = 0; i < strip.numPixels(); i++)
     {
      strip.setPixelColor(i, 63, 0, 255);
     }
     strip.show();

}



void fireball(int wait)
{
  int trail = 0;
  for(int i = 0; i < strip.numPixels()+ 25; i++) //This runs the strip and the +25 is to ensure the lights run off of the strip.
  {
 
    for(int j = 0; j<5; j++)// This loop determines how long the set of lights is.
    {
      // This is the rainbow sequence.     
      strip.setPixelColor((i+j), 255, 255, 255);
      strip.setPixelColor((i+j)-6, 255, 255, 0);  
      strip.setPixelColor((i+j)-9, 255, 180, 0);
      strip.setPixelColor((i+j)-12, 255, 80, 0);
      strip.setPixelColor((i+j)-15, 140, 0, 0);
      strip.setPixelColor((i+j)-18, 40, 0, 0);
      strip.setPixelColor((i+j)-21, 0, 0, 0);
      trail = random(3);
      if((trail % 2) == 0)
      {
          strip.setPixelColor((i+j)-24, 100, 0, 0);
      }
     
      if((trail % 2) != 0)
      {
        strip.setPixelColor((i+j)-24, 0, 0, 0);   
      }
      strip.setPixelColor((i+j)-27, 0, 0, 0);
                 

      strip.show();
      strip.setPixelColor(i-27, 0,0,0); //This clears everything after the final pixel is lit.
      
    }
    
    delay(wait);
    trail == true;
  }
}




void nightLight()
{

  int bluefire;
  int greenfire;
  int blackfireblue;
  int blackfirered;
  switch(phase)
  {
    
    case 0:
    {
        for(int i = 0; i < strip.numPixels(); i++)
        {
          bluefire = random(255) + 50; 
          greenfire = random(150);
          blackfireblue = random(150) + 40;
          blackfirered = random(56);
          strip.setPixelColor(i+random(3), (blackfirered * 1.15), 0, (blackfireblue * 1.15));
          strip.setPixelColor(i*random(3), (blackfirered * .67), 0, (blackfireblue * .67));
          strip.setPixelColor(i-random(5), blackfirered, 0, blackfireblue);
          if((i % 2) == 0)
          {
            strip.setPixelColor(i+random(10), 0, 255, 255);
            strip.setPixelColor(i-random(4), 0, greenfire, (greenfire * .70));
          }
        }
        
        
      strip.show();
      change++;
      if(change == 100)
      {
        phase = 1;
      }
      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
    }
    
    
    case 1:
    {
        for(int i = 0; i < strip.numPixels(); i++)
        {
          bluefire = random(200) + 40; 
          greenfire = random(150);
          blackfireblue = random(150) + 40;
          blackfirered = random(56);
          strip.setPixelColor(i+random(3), (blackfirered * 1.15), 0, (blackfireblue * 1.15));
          strip.setPixelColor(i-random(4), 0, greenfire, (greenfire * .70));
          strip.setPixelColor(i-random(5), blackfirered, 0, blackfireblue);
          if((i % 2) == 0)
          {
            strip.setPixelColor(i-random(5), 0, (greenfire * .31373), 0);
            strip.setPixelColor(i*random(3), 0, 0, bluefire * 4);
            strip.setPixelColor(i-random(4), 0, (greenfire * .40), greenfire * .7);
          }
        }
        
        
      strip.show();
      change++;
      if(change == 200)
      {
        phase = 2;
      }
      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
    }
    
    
    case 2:
    {
        for(int i = 0; i < strip.numPixels(); i++)
        {
          bluefire = random(120) + 30; 
          greenfire = random(150);
          blackfireblue = random(150) + 40;
          blackfirered = random(56);
          strip.setPixelColor(i+random(3), 0, greenfire, (greenfire * .31373));
          strip.setPixelColor(i-random(4), 0, greenfire, (greenfire * .70));
          if((i % 2) == 0)
          {
            strip.setPixelColor(i-random(5), 0, greenfire, (greenfire * .31373));
            strip.setPixelColor(i*random(3), 0, 0, bluefire * 4);
            strip.setPixelColor(i*random(6), blackfirered, 0, blackfireblue);
          }
        }
        
        
      strip.show();
      change++;
      if(change == 300)
      {
        phase = 4;
      }
      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
    }
    
    
    
    
    case 3:
    {
      for(int i = 0; i < strip.numPixels(); i++)
        {
          bluefire = random(90) + 20; 
          greenfire = random(150);
          strip.setPixelColor(i*random(3), 0, greenfire, (greenfire * .31373));
          strip.setPixelColor(i*random(6), 0, greenfire, (greenfire * .70));
          if((i % 2) == 0)
          {
            strip.setPixelColor(i*random(3), 0, 0, bluefire);
          }
        }
        
        
      strip.show();
      change++;
      if(change == 400)
      {
        phase = 4;
      }
      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
      }
      
      
    case 4:
    {
          
      for(int i = 0; i < strip.numPixels(); i++)
        {
          bluefire = random(70) + 10;
          greenfire = random(150);
          strip.setPixelColor(i-random(6), 0, 0, bluefire);
          strip.setPixelColor(i*random(3), 0, greenfire, (greenfire * .31373));
        }
      strip.show();
      change++;
      if(change == 500)
      {
        phase = 5;
      }
      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
    }
          
 
    
    
    
    case 5:
    {

        for(int i = 0; i < strip.numPixels(); i++)
        {
          bluefire = random(50);
          greenfire = random(150);
          strip.setPixelColor(i, 0, 0, bluefire);
          if((i % 2) == 0)
          {
            strip.setPixelColor(i+random(6), 0, greenfire, (greenfire * .31373));
            strip.setPixelColor(i*random(3), 0, 0, 0);
            strip.setPixelColor(i+random(3), 0, 0, 0);
            strip.setPixelColor(i-random(3), 0, 0, 0);
          }
        }
      strip.show();
      change++;
      if(change == 600)
      {
        phase = 6;
      }
      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
    }
    
    
    default:
    {
      for(int i = 0; i < strip.numPixels(); i++)
      {
        strip.setPixelColor(i, 0, 0, 255);
      }
      strip.show();
      phase = 0;
      change = 0;
     
    }
        
  }
    
}





void pixie()
{

  int green;
  int lightblue;
  switch(phase)
  {
    
    case 0:
    {

        for(int i = 0; i < strip.numPixels(); i++)
        {
          green = random(50);
          strip.setPixelColor(i, 0, green, 0);
          
          if((i % 2) == 0)
          {
            strip.setPixelColor(i*random(3), 0, 0, 0);
            strip.setPixelColor(i+random(3), 0, 0, 0);
            strip.setPixelColor(i-random(3), 0, 0, 0);
            strip.setPixelColor(i-random(2), 0, 0, 0);
          }
        }
      strip.show();
      change = change - 3;
      if(change >= chgup)
      {
        phase = 1;
      }
//      Serial.print("Phase: "); Serial.println(phase);
//      Serial.print("Change: ");Serial.println(change);
      break;
    }
    
    case 1:
    {

        for(int i = 0; i < strip.numPixels(); i++)
        {
          green = random(50);
          lightblue = random(150);
          strip.setPixelColor(i, 0, green, 0);
          if((i % 2) == 0)
          {
            strip.setPixelColor(i+random(6), 0, (lightblue * .31373), lightblue);
            strip.setPixelColor(i*random(3), 0, 0, 0);
            strip.setPixelColor(i+random(3), 0, 0, 0);
            strip.setPixelColor(i-random(3), 0, 0, 0);
          }
        }
      strip.show();
      change = change - 5;
      if(change >= chgup * 2)
      {
        phase = 2;
      }
      if(change <= chgup)
      {
        phase = 0;
      }
//      Serial.print("Phase: "); Serial.println(phase);
//      Serial.print("Change: ");Serial.println(change);
      break;
    }
    
    
    
    case 2:
    {
          
      for(int i = 0; i < strip.numPixels(); i++)
        {
          green = random(50);
          lightblue = random(150);
          strip.setPixelColor(i-random(6), 0, green, 0);
          strip.setPixelColor(i*random(3), 0, (lightblue * .31373), lightblue);
          if((i % 2) == 0)
          {
            strip.setPixelColor(i*random(4), 0, 0, 0);
          }
        }
      strip.show();
      change = change - 8;
      if(change <= chgup * 2)
      {
        phase = 1;
      }
//      Serial.print("Phase: "); Serial.println(phase);
//      Serial.print("Change: ");Serial.println(change);
      break;
    }
    
    
    default:
    {
      phase = 0;
      change = 0;
     
    }
        
  }
    
}





void fireFeet()
{

  int lowfire;
  int yellowfire;
  int whitefire;
  switch(phase)
  {
    
    case 0:
    {

        for(int i = 0; i < strip.numPixels(); i++)
        {
          lowfire = random(50);
          yellowfire = random(150);
          strip.setPixelColor(i, lowfire, 0, 0);
          
          if((i % 2) == 0)
          {
            strip.setPixelColor(i*random(3), 0, 0, 0);
            strip.setPixelColor(i+random(3), 0, 0, 0);
            strip.setPixelColor(i-random(3), 0, 0, 0);
            strip.setPixelColor(i-random(2), 0, 0, 0);
          }
        }
      strip.show();
      change = change - 3;
      if(change >= chgup)
      {
        phase = 1;
      }
      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
    }
    
    case 1:
    {

        for(int i = 0; i < strip.numPixels(); i++)
        {
          lowfire = random(50);
          yellowfire = random(150);
          strip.setPixelColor(i, lowfire, 0, 0);
          if((i % 2) == 0)
          {
            strip.setPixelColor(i+random(6), yellowfire, (yellowfire * .31373), 0);
            strip.setPixelColor(i*random(3), 0, 0, 0);
            strip.setPixelColor(i+random(3), 0, 0, 0);
            strip.setPixelColor(i-random(3), 0, 0, 0);
          }
        }
      strip.show();
      change = change - 5;
      if(change >= chgup * 2)
      {
        phase = 2;
      }
      if(change <= chgup)
      {
        phase = 0;
      }
      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
    }
    
    
    
    case 2:
    {
          
      for(int i = 0; i < strip.numPixels(); i++)
        {
          lowfire = random(50);
          yellowfire = random(150);
          strip.setPixelColor(i-random(6), lowfire, 0, 0);
          strip.setPixelColor(i*random(3), yellowfire, (yellowfire * .31373), 0);
          if((i % 2) == 0)
          {
            strip.setPixelColor(i*random(4), 0, 0, 0);
          }
        }
      strip.show();
      change = change - 8;
      if(change >= chgup * 3)
      {
        phase = 3;
      }
      if(change <= chgup * 2)
      {
        phase = 1;
      }
      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
    }
    
    case 3:
    {
      for(int i = 0; i < strip.numPixels(); i++)
        {
          lowfire = random(50); 
          yellowfire = random(150);
          strip.setPixelColor(i*random(3), yellowfire, (yellowfire * .31373), 0);
          strip.setPixelColor(i*random(6), yellowfire, (yellowfire * .70), 0);
          if((i % 2) == 0)
          {
            strip.setPixelColor(i*random(3), lowfire, 0, 0);
            strip.setPixelColor(i*random(4), 0, 0, 0);
          }
        }
        
        
      strip.show();
      change = change - 12;
      if(change >= chgup * 4)
      {
        phase = 4;
      }
      
      if(change <= chgup * 3)
      {
        phase = 2;
      }
      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
      }
      
      
    case 4:
    {
        for(int i = 0; i < strip.numPixels(); i++)
        {
          lowfire = random(50); 
          yellowfire = random(150);
          whitefire = random(125) + 50;
          strip.setPixelColor(i+random(3), yellowfire, (yellowfire * .31373), 0);
//          strip.setPixelColor(i-random(4), yellowfire, (yellowfire * .70), 0);
          if((i % 2) == 0)
          {
            strip.setPixelColor(i-random(5), yellowfire, (yellowfire * .31373), 0);
            strip.setPixelColor(i*random(3), lowfire * 4, 0, 0);
            strip.setPixelColor(i*random(6), whitefire, whitefire, whitefire);
            strip.setPixelColor(i*random(3), 0, 0, 0);
          }
        }
        
        
      strip.show();
      change = change - 13;
      if(change >= chgup * 5)
      {
        phase = 5;
      }
      if(change <= chgup * 4)
      {
        phase = 3;
      }
      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
    }
      
      
    case 5:
    {
        for(int i = 0; i < strip.numPixels(); i++)
        {
          lowfire = random(50); 
          yellowfire = random(150);
          whitefire = random(125) + 50;
          strip.setPixelColor(i+random(3), (whitefire * 1.15), (whitefire * 1.15), (whitefire * 1.15));
          strip.setPixelColor(i-random(4), yellowfire, (yellowfire * .70), 0);
          strip.setPixelColor(i-random(5), whitefire, whitefire, whitefire);
          if((i % 2) == 0)
          {
            strip.setPixelColor(i-random(5), yellowfire, (yellowfire * .31373), 0);
            strip.setPixelColor(i*random(3), lowfire * 4, 0, 0);
            strip.setPixelColor(i-random(4), yellowfire, (yellowfire * .70), 0);
            strip.setPixelColor(i*random(3), 0, 0, 0);
          }
        }
        
        
      strip.show();
      change = change - 15;
      if(change >= chgup * 6)
      {
        phase = 6;
      }
      if(change <= chgup * 5)
      {
        phase = 4;
      }

      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
    }
      
      
    case 6:
    {
        for(int i = 0; i < strip.numPixels(); i++)
        {
          lowfire = random(50); 
          yellowfire = random(150);
          whitefire = random(155) + 100;
          strip.setPixelColor(i+random(3), (whitefire * 1.15), (whitefire * 1.15), (whitefire * 1.15));
          strip.setPixelColor(i*random(3), (whitefire * .67), (whitefire * .67), (whitefire * .67));
          strip.setPixelColor(i/random(5), whitefire, whitefire, whitefire);
          if((i % 2) == 0)
          {
            strip.setPixelColor(i+random(10), 255, 255, 255);
            strip.setPixelColor(i-random(4), yellowfire, (yellowfire * .70), 0);
            strip.setPixelColor(i*random(4), 0, 0, 0);
          }
        }
        
        
      strip.show();
      change = change - 25;
      
      if(change <= chgup * 6)
      {
        phase = 5;
      }
      
      Serial.print("Phase: "); Serial.println(phase);
      Serial.print("Change: ");Serial.println(change);
      break;
    }
    
    
    default:
    {
      phase = 0;
      change = 0;
    }
        
  }
    
}
