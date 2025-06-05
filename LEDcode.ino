#include <FastLED.h>

#define NUM_LEDS 13
#define LED_PIN 13

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}

void loop() {

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Brown;
    FastLED.show();
    delay(50);
    leds[i] = CRGB::Black;
  }

  for(int i = NUM_LEDS - 1; i >= 0; i--) {
    leds[i] = CRGB::Brown;
    FastLED.show();
    delay(50);
    leds[i] = CRGB::Black;
  }
  //leds[0] = CRGB::Amethyst;
  //leds[1] = CRGB::Amethyst;
  //FastLED.show();
}
