/*
   Original code from : Bi Pride Necklace
   by brightcolorfulflickers
   August 2016

   github.com/brightcolorfulflickers
   brightcolorfulflickers.tumblr.com
   instagram.com/brightcolorfulflickers

Hacked a bit...
   
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define LED_PIN 3
#define BUTTON 0
#define NUM_LEDS 24
int Count = 5;


unsigned long lastButtonCheck = 0;
const unsigned long buttonDebounceTime = 200; //200 ms
bool firstUpdate = false;

byte buttonFlag;//this flag is used to communicate to the main loop that a new value was read.

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Colors!
const uint32_t pan_blue = 38505;// = Wheel(120);
const uint32_t pan_pink = 15728655;// = Wheel(250);
const uint32_t pan_yellow = 9857280;// = Wheel(35);

const uint32_t white = 16777215;// = strip.Color(255, 255, 255);
const uint32_t black = 0;

//Flags!
const uint32_t panFlag[NUM_LEDS] = {pan_pink, pan_pink, pan_pink, pan_pink, pan_yellow, pan_yellow, pan_blue, pan_blue, pan_blue, pan_blue, pan_blue, pan_blue, pan_yellow, pan_yellow, pan_pink, pan_pink};
const uint32_t panChase[NUM_LEDS] = {pan_pink, pan_yellow, pan_blue, black, black, black, black, black, pan_pink, pan_yellow, pan_blue, black, black, black, black, black};

void setup() {
  strip.begin();
  strip.setBrightness(30);
  strip.show(); // Initialize all pixels to 'off'
  pinMode(BUTTON, INPUT);
}

void loop() {
  strip.setBrightness(30);
  FlagRotate(100);
  FlagRotate(10);
  FlagRotate(100);
  FlagRotate(10);
  PinkDisplay(1);
  delay(3000);
}


/* PAN PRIDE */



void FlagRotate(uint8_t wait) {
  uint8_t i;
  uint8_t j;

  for (j = 0; j < strip.numPixels(); j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, panFlag[(i + j) % NUM_LEDS]);
    }
    strip.show();
    //we need to check the button in here because of the delay
    long startWait = millis();
    while ((unsigned long)(millis() - startWait) < wait) {
      if ((unsigned long)(millis() - lastButtonCheck) > buttonDebounceTime) {
        int buttonRead = digitalRead(BUTTON);
        lastButtonCheck = millis();
      }
    }
  }
}


void PinkDisplay(uint8_t wait) {
  int R = 255;
  int G = 45;
  int B = 180;


  int TOTAL_LEDS = NUM_LEDS;
  float MaximumBrightness = 100;
  float SpeedFactor = 0.008; // I don't actually know what would look good
  float StepDelay = 8; // ms for a step delay on the lights

  // Make the lights breathe
  for (int i = 0; i <  2360; i++) {
    // Intensity will go from 10 - MaximumBrightness in a "breathing" manner
    float intensity = MaximumBrightness / 2.0 * (1.0 + sin(SpeedFactor * i));
    strip.setBrightness(intensity);
    // Now set every LED to that color
    for (int ledNumber = 0; ledNumber < TOTAL_LEDS; ledNumber++) {
      strip.setPixelColor(ledNumber, R, G, B);
    }

    strip.show();
    //Wait a bit before continuing to breathe
    delay(StepDelay);

  }
}
