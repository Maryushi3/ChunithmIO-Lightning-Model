#include <Keyboard.h>
#include <FastLED.h>
#define LEFT_PIN      5
#define RIGHT_PIN     6
#define NUM_LEDS    3

CRGB left_leds[NUM_LEDS];
CRGB right_leds[NUM_LEDS];
CRGB left_color = CRGB(0,0x7F,0x4F);
CRGB right_color = CRGB(0x7F,0,0x4F);
CRGB left_color_dead = CRGB(0,0x1F,0x0F);
CRGB right_color_dead = CRGB(0x1F,0,0x0F);
bool leDebug = false;
void setup() {
 Keyboard.begin();
 FastLED.addLeds<WS2811, LEFT_PIN, RGB>(left_leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
 FastLED.addLeds<WS2811, RIGHT_PIN, RGB>(right_leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
 FastLED.setBrightness(64);
 delay(1000);
//  fill_solid(right_leds, NUM_LEDS, CRGB(0x7F,0,0x23));
//  fill_solid(left_leds, NUM_LEDS, CRGB(0,0x7F,0x7F));
 FastLED.show(); 
 pinMode(8, INPUT_PULLUP);
 pinMode(9, INPUT_PULLUP);
 pinMode(10, INPUT_PULLUP);
 pinMode(14, INPUT_PULLUP);
 pinMode(15, INPUT_PULLUP);
 pinMode(16, INPUT_PULLUP);
 delay(1000);
}

void loop() {
  // --- input ---
  if (digitalRead(8) == HIGH)
  {
    if (!leDebug) {Keyboard.press('a');}
  }
  else
  {
    if (!leDebug) {Keyboard.release('a');}
  }
  if (digitalRead(14) == HIGH)
  {
    if (!leDebug) Keyboard.press('b');
  }
  else
  {
    if (!leDebug) Keyboard.release('b');
  }
  if (digitalRead(9) == HIGH)
  {
    if (!leDebug) Keyboard.press('c');
  }
  else
  {
    if (!leDebug) Keyboard.release('c');
  }
  if (digitalRead(15) == HIGH)
  {
    if (!leDebug) Keyboard.press('d');
  }
  else
  {
    if (!leDebug) Keyboard.release('d');
  }
  if (digitalRead(10) == HIGH)
  {
    if (!leDebug) Keyboard.press('e');
  }
  else
  {
    if (!leDebug) Keyboard.release('e');
  }
  if (digitalRead(16) == HIGH)
  {
    if (!leDebug) Keyboard.press('f');
  }
  else
  {
    if (!leDebug) Keyboard.release('f');
  }  

// -- LEDs shenanigans --- 
  if (digitalRead(8) == HIGH or digitalRead(14) == HIGH){
    left_leds[2] = left_color;
    right_leds[2] = right_color;
    FastLED.show();
  }
  else{
    left_leds[2] = left_color_dead;
    right_leds[2] = right_color_dead;
    FastLED.show();
  }

  if (digitalRead(9) == HIGH or digitalRead(15) == HIGH){
    left_leds[1] = left_color;
    right_leds[1] = right_color;
    FastLED.show();
  }
  else{
    left_leds[1] = left_color_dead;
    right_leds[1] = right_color_dead;
    FastLED.show();
  }

  if (digitalRead(10) == HIGH or digitalRead(16) == HIGH){
    left_leds[0] = left_color;
    right_leds[0] = right_color;
    FastLED.show();
  }
  else{
    left_leds[0] = left_color_dead;
    right_leds[0] = right_color_dead;
    FastLED.show();
  }
}
