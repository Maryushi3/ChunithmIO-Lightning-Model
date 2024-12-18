#include <Keyboard.h>
#include <FastLED.h>
#include <EEPROM.h>

#define LEFT_PIN 5
#define RIGHT_PIN 6
#define NUM_LEDS 3

CRGB left_leds[NUM_LEDS];
CRGB right_leds[NUM_LEDS];
CRGB left_color = CRGB::Blue;
CRGB right_color = CRGB::Red;
float dead_color_ratio = 0.15;
CRGB left_color_dead = CRGB::Black;
CRGB right_color_dead = CRGB::Black;
int light_up_speed = 10;
int light_down_speed = 3;
byte led_mode = 0;
byte bg_mode = 1;
bool leDebug = false;

void setBackgroundToRatiod() {
  CHSV tmp_left_color_dead;
  CHSV tmp_right_color_dead;

  tmp_left_color_dead = rgb2hsv_approximate(left_color);
  tmp_left_color_dead.v = tmp_left_color_dead.v * dead_color_ratio;
  left_color_dead = hsv2rgb_spectrum(tmp_left_color_dead);

  tmp_right_color_dead = rgb2hsv_approximate(right_color);
  tmp_right_color_dead.v = tmp_right_color_dead.v * dead_color_ratio;
  right_color_dead = hsv2rgb_spectrum(tmp_right_color_dead);
}

void setBackgroundToBlack() {
  left_color_dead = CRGB::Black;
  right_color_dead = CRGB::Black;
}

void setBackgroundToStatic() {
  left_color_dead = left_color;
  right_color_dead = right_color;
}

void setLedsToCustom() {
}
void choosePreset(byte predef_led_mode);

void setup() {
  Keyboard.begin();
  //"service" button
  pinMode(3, INPUT_PULLUP);
  //sensors
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);

  FastLED.addLeds<WS2811, LEFT_PIN, RGB>(left_leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2811, RIGHT_PIN, RGB>(right_leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(96);
  delay(1000);
  fill_solid(left_leds, NUM_LEDS, CRGB::Red);
  fill_solid(right_leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(1000);
  fill_solid(left_leds, NUM_LEDS, CRGB::Lime);
  fill_solid(right_leds, NUM_LEDS, CRGB::Lime);
  FastLED.show();
  delay(1000);
  fill_solid(left_leds, NUM_LEDS, CRGB::Blue);
  fill_solid(right_leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1000);
  if (digitalRead(3) == LOW) {
    leDebug = !leDebug;
  }
  EEPROM.get(1, bg_mode);
  EEPROM.get(2, led_mode);
  choosePreset(led_mode);
}

void choosePreset(byte predef_led_mode = 255) {
  if (predef_led_mode == 255) {
    led_mode = 0;
    if (digitalRead(8)) { bitSet(led_mode, 0); }
    if (digitalRead(14)) { bitSet(led_mode, 1); }
    if (digitalRead(9)) { bitSet(led_mode, 2); }
  }
  else{
    led_mode = predef_led_mode;
  }

  if (digitalRead(10) && !digitalRead(16)) {
    bg_mode = 0;
  }
  if (!digitalRead(10) && digitalRead(16)) {
    bg_mode = 1;
  }
  if (digitalRead(10) && digitalRead(16)) {
    bg_mode = 2;
  }

  switch (led_mode) {
    default:
    case 0:
      // basic
      left_color = CRGB::White;
      right_color = CRGB::White;
      break;
    case 1:
      // beat saber
      left_color = CRGB::Red;
      right_color = CRGB::Blue;
      break;
    case 2:
      // sound voltex
      left_color = CRGB::Aqua;
      right_color = CRGB::DarkMagenta;
      break;
    case 3:
      // paprykarz
      left_color = CRGB::Yellow;
      right_color = CRGB::Red;
      break;
    case 4:
      // something reddish
      left_color = CRGB::MediumVioletRed;
      right_color = CRGB::MediumVioletRed;
      break;
    case 5:
      // something greenish
      left_color = CRGB::Lime;
      right_color = CRGB::Lime;
      break;
    case 6:
      // something blue-ish
      left_color = CRGB::DeepSkyBlue;
      right_color = CRGB::DeepSkyBlue;
      break;
    case 7:
      // nothing
      left_color = CRGB::Black;
      right_color = CRGB::Black;
      break;
  }
  switch (bg_mode) {
    default:
    case 1:
      setBackgroundToRatiod();
      break;
    case 0:
      setBackgroundToBlack();
      break;
    case 2:
      setBackgroundToStatic();
      break;
  }
  updateLeds();
}

void updateLeds() {
  if (digitalRead(8) == HIGH or digitalRead(14) == HIGH) {
    left_leds[2] = CRGB(constrain(left_leds[2].r + light_up_speed, left_color_dead.r, left_color.r), constrain(left_leds[2].g + light_up_speed, left_color_dead.g, left_color.g), constrain(left_leds[2].b + light_up_speed, left_color_dead.b, left_color.b));
    right_leds[2] = CRGB(constrain(right_leds[2].r + light_up_speed, right_color_dead.r, right_color.r), constrain(right_leds[2].g + light_up_speed, right_color_dead.g, right_color.g), constrain(right_leds[2].b + light_up_speed, right_color_dead.b, right_color.b));
    FastLED.show();
  } else {
    left_leds[2] = CRGB(constrain(left_leds[2].r - light_down_speed, left_color_dead.r, left_color.r), constrain(left_leds[2].g - light_down_speed, left_color_dead.g, left_color.g), constrain(left_leds[2].b - light_down_speed, left_color_dead.b, left_color.b));
    right_leds[2] = CRGB(constrain(right_leds[2].r - light_down_speed, right_color_dead.r, right_color.r), constrain(right_leds[2].g - light_down_speed, right_color_dead.g, right_color.g), constrain(right_leds[2].b - light_down_speed, right_color_dead.b, right_color.b));
    FastLED.show();
  }

  if (digitalRead(9) == HIGH or digitalRead(15) == HIGH) {
    left_leds[1] = CRGB(constrain(left_leds[1].r + light_up_speed, left_color_dead.r, left_color.r), constrain(left_leds[1].g + light_up_speed, left_color_dead.g, left_color.g), constrain(left_leds[1].b + light_up_speed, left_color_dead.b, left_color.b));
    right_leds[1] = CRGB(constrain(right_leds[1].r + light_up_speed, right_color_dead.r, right_color.r), constrain(right_leds[1].g + light_up_speed, right_color_dead.g, right_color.g), constrain(right_leds[1].b + light_up_speed, right_color_dead.b, right_color.b));
    FastLED.show();
  } else {
    left_leds[1] = CRGB(constrain(left_leds[1].r - light_down_speed, left_color_dead.r, left_color.r), constrain(left_leds[1].g - light_down_speed, left_color_dead.g, left_color.g), constrain(left_leds[1].b - light_down_speed, left_color_dead.b, left_color.b));
    right_leds[1] = CRGB(constrain(right_leds[1].r - light_down_speed, right_color_dead.r, right_color.r), constrain(right_leds[1].g - light_down_speed, right_color_dead.g, right_color.g), constrain(right_leds[1].b - light_down_speed, right_color_dead.b, right_color.b));
    FastLED.show();
  }

  if (digitalRead(10) == HIGH or digitalRead(16) == HIGH) {
    left_leds[0] = CRGB(constrain(left_leds[0].r + light_up_speed, left_color_dead.r, left_color.r), constrain(left_leds[0].g + light_up_speed, left_color_dead.g, left_color.g), constrain(left_leds[0].b + light_up_speed, left_color_dead.b, left_color.b));
    right_leds[0] = CRGB(constrain(right_leds[0].r + light_up_speed, right_color_dead.r, right_color.r), constrain(right_leds[0].g + light_up_speed, right_color_dead.g, right_color.g), constrain(right_leds[0].b + light_up_speed, right_color_dead.b, right_color.b));
    FastLED.show();
  } else {
    left_leds[0] = CRGB(constrain(left_leds[0].r - light_down_speed, left_color_dead.r, left_color.r), constrain(left_leds[0].g - light_down_speed, left_color_dead.g, left_color.g), constrain(left_leds[0].b - light_down_speed, left_color_dead.b, left_color.b));
    right_leds[0] = CRGB(constrain(right_leds[0].r - light_down_speed, right_color_dead.r, right_color.r), constrain(right_leds[0].g - light_down_speed, right_color_dead.g, right_color.g), constrain(right_leds[0].b - light_down_speed, right_color_dead.b, right_color.b));
    FastLED.show();
  }
}


void loop() {
  if (digitalRead(8) == HIGH) {
    if (!leDebug) { Keyboard.press('a'); }
  } else {
    if (!leDebug) { Keyboard.release('a'); }
  }
  if (digitalRead(14) == HIGH) {
    if (!leDebug) Keyboard.press('b');
  } else {
    if (!leDebug) Keyboard.release('b');
  }
  if (digitalRead(9) == HIGH) {
    if (!leDebug) Keyboard.press('c');
  } else {
    if (!leDebug) Keyboard.release('c');
  }
  if (digitalRead(15) == HIGH) {
    if (!leDebug) Keyboard.press('d');
  } else {
    if (!leDebug) Keyboard.release('d');
  }
  if (digitalRead(10) == HIGH) {
    if (!leDebug) Keyboard.press('e');
  } else {
    if (!leDebug) Keyboard.release('e');
  }
  if (digitalRead(16) == HIGH) {
    if (!leDebug) Keyboard.press('f');
  } else {
    if (!leDebug) Keyboard.release('f');
  }


  updateLeds();

  while (digitalRead(3) == LOW) {
    while (digitalRead(3) == LOW) {
      choosePreset();
    }
    EEPROM.put(1, bg_mode);
    EEPROM.put(2, led_mode);
  }
}
