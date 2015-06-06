#include <Adafruit_NeoPixel.h>

#define PIN 53

Adafruit_NeoPixel strip = Adafruit_NeoPixel(117, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(15);
  strip.show();
//
//  registerInterrpt(1, setMode);
//
//  mode = DEFAULT_MODE;
}
//
//void setMode() {
//  if (SWITCH_HAS_CHANGED && SWITCH_IS_HIGH) {
//    mode += 1;
//  }
//}

void loop() {
//  switch (mode) {
//    case RAINBOW:
//      doRainbowMode();
//    case SOLID_WHITE:
//      doSolidWhiteMode();
//
//rainbowCycle(5);
 colorWipe(strip.Color(255, 180, 180), 5);
 delay(10000);
 colorWipe(strip.Color(255, 220, 220), 100);
 delay(5000);
//  colorWipe(strip.Color(0, 255, 0), 5);
//  colorWipe(strip.Color(0, 0, 255), 5);
}

//void doRainbowMode() {
//  while (true) {
//    if (mode != RAINBOW) {
//      return; 
//    } 
//    
//  }
//}




void colorWipe(uint32_t c, uint8_t wait) {
 for (uint16_t i=0; i<strip.numPixels(); i++) {
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


