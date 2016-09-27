#include <Adafruit_NeoPixel.h>

#define PIN 53
#define IPIN 2
#define OPIN 8

#define TIMER_DURATION 60000 //seconds

Adafruit_NeoPixel strip = Adafruit_NeoPixel(400, PIN, NEO_GRB + NEO_KHZ800);
volatile int program = 0;
volatile unsigned long debounceTimer = 0;

void setup() {
//  randomSeed(analogRead(0));
//  
//  pinMode(IPIN, INPUT);
//  pinMode(OPIN, OUTPUT);
//  
//  digitalWrite(OPIN, HIGH);
  // attachInterrupt(0, nextProgram, HIGH);
  
  strip.begin();
  strip.setBrightness(255);
  strip.show();
}


void loop() {
  solidColor(strip.Color(255, 255, 255));
  delay(50000);
//  switch (program) {
//    case 0:
//      white();
//      colorFill(strip.Color(255, 255, 255), strip.Color(0, 255, 0));
//      colorFlash(strip.Color(255, 255, 255), strip.Color(0 , 255, 0));
//      break;
//    case 1:
//      colorWipe(strip.Color(255, 0, 0), 0);
//      delay(250);
//      strip.clear();
//      delay(1000);
//      colorWipe(strip.Color(255, 0, 0), 50);
//      break;
//     case 2:
//        colorWipe(strip.Color(255, 255, 255), 0);
//        delay(250);
//        colorWipe(strip.Color(0, 255, 0), 50);
//       break;
//     case 3:
//       randomLights();
//       break;
//  }
}

void white() {
  memset(strip.getPixels(), 255, strip.numPixels() * 3);
  strip.show();
}

void nextProgram() {
  if (millis() - debounceTimer > 1000) {
    program = (program + 1) % 3;
    debounceTimer = millis();
  }
}

void randomLights() {
 int currentProgram = program;
  
  uint32_t currentColor = 0;
  
 for (uint16_t i=0; i<strip.numPixels(); i++) {
   if (program != currentProgram) {
    return; 
   }
   
   if (i % 6 == 0) {
     int rgbHigh = random(0,3);
     switch (rgbHigh) {
       case 0:
         currentColor = strip.Color(random(100, 255), random(0, 100), random(0, 100));
         break;
       case 1:
         currentColor = strip.Color(random(0, 100), random(100, 255), random(0, 100));
         break;
       case 2:
         currentColor = strip.Color(random(0, 100), random(0, 100), random(100, 255));
         break;
     }
   }
   
   strip.setPixelColor(i, currentColor);
 } 
 
   strip.show();
   delay(250);
}









//
//  registerInterrpt(1, setMode);
//
//  mode = DEFAULT_MODE;
//}
//
//void setMode() {
//  if (SWITCH_HAS_CHANGED && SWITCH_IS_HIGH) {
//    mode += 1;
//  }
//}

//void loop() {
////  switch (mode) {
////    case RAINBOW:
////      doRainbowMode();
////    case SOLID_WHITE:
////      doSolidWhiteMode();
//rainbowCycle(5);
// colorWipe(strip.Color(0, 255, 0), 50);
// 
// delay(10000);
// colorWipe(strip.Color(255, 220, 220), 100);
// delay(5000);
////  colorWipe(strip.Color(0, 255, 0), 5);
////  colorWipe(strip.Color(0, 0, 255), 5);
//}

//void doRainbowMode() {
//  while (true) {
//    if (mode != RAINBOW) {
//      return; 
//    } 
//    
//  }
//}

void colorFill(uint32_t bg, uint32_t fg) {
  int currentProgram = program;
  unsigned long startTime = millis();
  unsigned long endTime = startTime + (TIMER_DURATION / 2);
  int previousPixelsFilled = 0;
  
  for (unsigned long j = startTime; j < endTime; j=millis()) {
    
    unsigned long currentTime = millis();
    int pixelsFilled = (((float)(currentTime - startTime) / (float)(TIMER_DURATION / 2))) * strip.numPixels();
    int pixelsUnfilled = strip.numPixels() - pixelsFilled;
    unsigned long timeRemaining = currentTime - startTime;
    
    for (uint16_t i = (strip.numPixels() - pixelsFilled); i < (strip.numPixels() - previousPixelsFilled); i++) {
      strip.setPixelColor(i, fg);
    }
   
   for (uint16_t i=5; i<strip.numPixels() - pixelsFilled; i++) {
     if (program != currentProgram) {
      return; 
     }
     strip.setPixelColor(i-5, bg );
     strip.setPixelColor(i-4, fg );
     strip.setPixelColor(i-3, fg );
     strip.setPixelColor(i-2, fg );
     strip.setPixelColor(i-1, fg );
     strip.setPixelColor(i, fg );
     strip.show();
     
     if (timeRemaining / (unsigned long)pixelsUnfilled > 0) {
       delay((timeRemaining / (unsigned long)pixelsUnfilled) / (unsigned long)pixelsUnfilled);
     }
   }
 }
}

//void colorFill(uint32_t bg, uint32_t fg) {
//  int currentProgram = program;
//  int currentTime = millis();
// for( uint16_t j = 0; j < strip.numPixels(); j++ ) {
//   
//   for (uint16_t i=5; i<strip.numPixels() - j; i++) {
//     if (program != currentProgram) {
//      return; 
//     }
//     strip.setPixelColor(i-5, bg );
//     strip.setPixelColor(i-4, fg );
//     strip.setPixelColor(i-3, fg );
//     strip.setPixelColor(i-2, fg );
//     strip.setPixelColor(i-1, fg );
//     strip.setPixelColor(i, fg );
//     strip.show();
//     
//     uint32_t dmillis = ((TIMER_DURATION/strip.numPixels()) / (strip.numPixels() - j));
//     
//     if (dmillis > 0) {
//       delay(dmillis);
//     }
//   } 
//   
//   int32_t dmillis = (TIMER_DURATION/strip.numPixels()) - (millis() - currentTime);
//   
//   if (dmillis > 0) {
//     delay(dmillis);  
//   }
//   currentTime = millis();
// }
//}

void colorFlash(uint32_t bg, uint32_t fg) {
  do {
    solidColor(bg);
    delay(500);
    solidColor(fg);
    delay(500);
  } while (true);
}




void solidColor(uint32_t color) {
  for (uint32_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}



void colorWipe(uint32_t c, uint8_t wait) {
  int currentProgram = program;
  
 for (uint16_t i=0; i<strip.numPixels(); i++) {
   if (program != currentProgram) {
    return; 
   }
   strip.setPixelColor(i, c);
   strip.show();
   delay(wait);
 } 
}


// Slightly different, this makes the rainbow equally distributed throughout
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


//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}


