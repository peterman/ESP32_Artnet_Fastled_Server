void initTest()
{
  for (int i=0; i< NUM_LEDS; i++){
    leds[i]=CRGB::Blue;
    FastLED.show();
    leds[i]=CRGB::Black;
    delay(50);
  }
  for (int i=0; i< NUM_LEDS; i++){
    leds[i]=CRGB::Green;
    FastLED.show();
    leds[i]=CRGB::Black;
    delay(50);
  }
  for (int i=0; i< NUM_LEDS; i++){
    leds[i]=CRGB::Red;
    FastLED.show();
    leds[i]=CRGB::Black;
    delay(50);
  }
  for (int j=0; j<3; j++){
    fill_solid(leds,NUM_LEDS,CRGB::White);
    FastLED.setBrightness(255);
    FastLED.show();
    delay(50);
    FastLED.clear();
    FastLED.show();
    delay(50);
  }
  
  FastLED.setBrightness(128);
  FastLED.clear ();
  FastLED.show();
}
