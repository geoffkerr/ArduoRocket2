#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <Wire.h>
#include "nunchuk.h"
#include <LiquidCrystal_I2C.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    13

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 16

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

// Declare the LCD configuration
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  // setup LEDs
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(10); // Set BRIGHTNESS to about 1/5 (max = 255)

  // setup wii chuck
  Wire.begin();
  // nunchuk_init_power(); // A1 and A2 is power supply
  nunchuk_init();

  // setup the LCD screen
  lcd.begin();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  //lcd.noBacklight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("- Kerr Family  -");
  lcd.setCursor(0,1);
  lcd.print("- Rocket Ship  -");

  // put your setup code here, to run once:
  // TEMPORARY SERIAL INTERFACE
  //Serial.begin(9600);

}


int  hatX = 0;
int  hatY = 0;
int  butC = false;
int  butZ = false;

void loop() {
  // read the i2c nunchuk
  nunchuk_read();
  
  hatX = nunchuk_joystickX();
  hatY = nunchuk_joystickY();
  butC = nunchuk_buttonC();
  butZ = nunchuk_buttonZ();

  //*****************************************************************
  // set all off
  for(int i=0; i<LED_COUNT; i++) { // For each pixel...
    // strip.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }

  //*****************************************************************
  // control LED strip 1 based on Left and Right orientation
  //*****************************************************************
  // Left
  if (hatX >= 92)
    {
    strip.setPixelColor(0, strip.Color(0,0,150));
    strip.setPixelColor(1, strip.Color(0,0,150));
  }
  // left -1
  else if ((hatX >= 55) && (hatX < 92))
  {
    strip.setPixelColor(1, strip.Color(0,0,150));
    strip.setPixelColor(2, strip.Color(0,0,150));
  }
  // left -2
  else if ((hatX >= 19) && (hatX < 55))
  {
    strip.setPixelColor(2, strip.Color(0,0,150));
    strip.setPixelColor(3, strip.Color(0,0,150));
  }
  // center
  else if ((hatX > -18) && (hatX < 19))
  {
    strip.setPixelColor(3, strip.Color(0,0,150));
    strip.setPixelColor(4, strip.Color(0,0,150));
  }
  // right -2
  else if ((hatX > -54) && (hatX <= -18))
  {
    strip.setPixelColor(4, strip.Color(0,0,150));
    strip.setPixelColor(5, strip.Color(0,0,150));
  }
  // right -1
  else if ((hatX > -91) && (hatX <= -54))
  {
    strip.setPixelColor(5, strip.Color(0,0,150));
    strip.setPixelColor(6, strip.Color(0,0,150));
  }
  // right
  else if (hatX <= -91)
  {
    strip.setPixelColor(6, strip.Color(0,0,150));
    strip.setPixelColor(7, strip.Color(0,0,150));
  }
  
  //*****************************************************************
  // control LED strip 2 based on Up and Down orientation
  //*****************************************************************
  // up
  if (hatY >= 92)
    {
    strip.setPixelColor(8, strip.Color(0,0,150));
    strip.setPixelColor(9, strip.Color(0,0,150));
  }
  // up -1
  else if ((hatY >= 55) && (hatY < 92))
  {
    strip.setPixelColor(9, strip.Color(0,0,150));
    strip.setPixelColor(10, strip.Color(0,0,150));
  }
  // up -2
  else if ((hatY >= 19) && (hatY < 55))
  {
    strip.setPixelColor(10, strip.Color(0,0,150));
    strip.setPixelColor(11, strip.Color(0,0,150));
  }
  // center
  else if ((hatY > -18) && (hatY < 19))
  {
    strip.setPixelColor(11, strip.Color(0,0,150));
    strip.setPixelColor(12, strip.Color(0,0,150));
  }
  // down -2
  else if ((hatY > -54) && (hatY <= -18))
  {
    strip.setPixelColor(12, strip.Color(0,0,150));
    strip.setPixelColor(13, strip.Color(0,0,150));
  }
  // down -1
  else if ((hatY > -91) && (hatY <= -54))
  {
    strip.setPixelColor(13, strip.Color(0,0,150));
    strip.setPixelColor(14, strip.Color(0,0,150));
  }
  // down
  else if (hatY <= -91)
  {
    strip.setPixelColor(14, strip.Color(0,0,150));
    strip.setPixelColor(15, strip.Color(0,0,150));
  }

  if ((butC != 0) && (butZ == 0))
  {
    lcd.noBacklight();
    for(int i=0; i<LED_COUNT; i++) { // For each pixel...
      // strip.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
  }
  else if ((butC == 0) && (butZ != 0))
  {
    lcd.noBacklight();
    for(int i=0; i<LED_COUNT; i++) { // For each pixel...
      // strip.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      strip.setPixelColor(i, strip.Color(0, 255, 0));
    }
  }
  else if ((butC != 0) && (butZ != 0))
  {
    lcd.noBacklight();
    for(int i=0; i<LED_COUNT; i++) { // For each pixel...
      // strip.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      strip.setPixelColor(i, strip.Color(255, 255, 0));
    }
  }

  strip.show();   // Send the updated pixel colors to the hardware.

  // put your main code here, to run repeatedly:
  //if (nunchuk_read()) {
  //    // Work with nunchuk_data
  //    nunchuk_print();
  //}
  delay(50);
  lcd.backlight();
}
