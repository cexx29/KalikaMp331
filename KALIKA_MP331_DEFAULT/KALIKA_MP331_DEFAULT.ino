#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include <FastLED.h>
#include <Keypad.h>
#include <Encoder.h>
#include <Bounce2.h>
#include "HID-Project.h"

// Library with a lot of the HID definitions and methods
// Can be installed from the library manager, search for "HID-project"
// and install the one by NicoHood
// https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h
// https://www.arduino.cc/en/Reference/KeyboardModifiers
// https://github.com/NicoHood/HID/blob/master/src/HID-APIs/ConsumerAPI.h

// to change rgb colors
// https://www.w3schools.com/colors/colors_picker.asp

// some libraries at
// https://github.com/cexx29/KalikaMp331/tree/main/Library%20Macropad

//Keypad buttons
#define C1  21
#define C2  20
#define C3  5

#define R1  7
#define R2  8
#define R3  9

const byte ROWS = 3;
const byte COLS = 3;

char keys[COLS][ROWS] = {
  {'7', '4', '1'},
  {'8', '5', '2'},
  {'9', '6', '3'}
};

byte rowPins[ROWS] = {R1, R2, R3};
byte colPins[COLS] = {C1, C2, C3};
Keypad kpd = Keypad( makeKeymap(keys), colPins, rowPins, COLS, ROWS);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define LED_PIN 14
#define NUM_LEDS 9

#define OLED_RESET     4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

CRGB leds[NUM_LEDS];

int a;
int b;

int currentState = 0;

int lastDebounceTime = 0;
const int debounceTime = 10;

//Encoder
#define SW  19
#define DT  16
#define CLK  15

Encoder volumeKnob(DT, CLK);
Bounce encoderButton = Bounce(SW, 10);
int timeLimit = 100; // Jeda hold mode
long oldPosition = -999;

void setup() {

  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(3, 30); // Volt (max 5v), Ampere untuk kecerahan cahaya led
  FastLED.clear();
  FastLED.show();
  display.clearDisplay();

  pinMode(CLK, INPUT_PULLUP);

  Keyboard.begin();
  Consumer.begin();

  display.setTextSize(2);  
  display.setTextColor(WHITE);
  display.setCursor(30, 12);
  display.println("KALIKA");
  display.display();
  delay(1000);
  display.setCursor(31, 36);
  display.println("MP 331");
  display.display();
  delay(1000);

}

void ChangeState() {
  currentState++;
  delay(100);
  if (currentState > 3) {
    currentState = 0;
  }
  return;
}

void effect1() {
  //display.fillRoundRect(a, b, 41, 16, 5, WHITE);
  display.display();
  delay(20);
}

//untuk mapping button
void Layout1(char button) {
  switch (button) {
    case '1':
      a = 0;
      b = 48;
      Keyboard.press(KEY_LEFT_ARROW);
      Keyboard.releaseAll();
      effect1();
      break;
    case '2':
      a = 43;
      b = 48;
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.releaseAll();
      effect1();
      break;
    case '3':
      a = 86;
      b = 48;
      Keyboard.press(KEY_RIGHT_ARROW);
      Keyboard.releaseAll();
      effect1();
      break;
    case '4':
      a = 0;
      b = 30;
      Consumer.write(MEDIA_VOLUME_MUTE);
      effect1();
      break;
    case '5':
      a = 43;
      b = 30;
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.releaseAll();
      effect1();
      break;
    case '6':
      a = 86;
      b = 30;
      Consumer.write(MEDIA_STOP);
      effect1();
      break;
    case '7':
      a = 0;
      b = 12;
      Consumer.write(MEDIA_PLAY_PAUSE);
      effect1();
      break;
    case '8':
      a = 43;
      b = 12;
      Consumer.write(MEDIA_NEXT);
      effect1();
      break;
    case '9':
      a = 86;
      b = 12;
      Consumer.write(MEDIA_PREVIOUS);
      break;
  };
}//

void Layout2(char button) {
  switch (button) {
    case '1'://
      a = 0;
      b = 48;
      Keyboard.press(KEY_DELETE);
      Keyboard.releaseAll();
      effect1();
      break;
    case '2'://
      a = 43;
      b = 48;
      Keyboard.press(KEY_SPACE);
      Keyboard.releaseAll();
      effect1();
      break;
    case '3'://
      a = 86;
      b = 48;
      Keyboard.press(KEY_SPACE);
      Keyboard.releaseAll();
      effect1();
      break;
    case '4'://
      a = 0;
      b = 30;
      Keyboard.press(KEY_CAPS_LOCK);
      Keyboard.releaseAll();
      effect1();
      break;
    case '5'://
      a = 43;
      b = 30;
      effect1();
      break;
    case '6'://Return
      a = 86;
      b = 30;
      Keyboard.press(KEY_ENTER);
      Keyboard.releaseAll();
      effect1();
      break;
    case '7'://Escape
      a = 0;
      b = 12;
      Keyboard.press(KEY_ESC);
      Keyboard.releaseAll();
      effect1();
      break;

    case '8'://
      a = 43;
      b = 12;
      Keyboard.press(KEY_TAB);
      Keyboard.releaseAll();
      effect1();
      break;
    case '9'://
      a = 86;
      b = 12;
      Keyboard.press(KEY_BACKSPACE);
      Keyboard.releaseAll();
      effect1();
      break;
  };
}

void Layout3(char button) {
  switch (button) {
    case '1':
      Keyboard.print('G');
      break;
    case '2':
      Keyboard.print('H');
      break;
    case '3':
      Keyboard.print('I');
      break;
    case '4':
      Keyboard.print('D');
      break;
    case '5':
      Keyboard.print('E');
      break;
    case '6':
      Keyboard.print('F');
      break;
    case '7':
      Keyboard.print('A');
      break;
    case '8':
      Keyboard.print('B');
      break;
    case '9':
      Keyboard.print('C');
      break;
  };
}

void Layout4(char button) {
  switch (button) {
    case '1':
      Keyboard.print('g');
      break;
    case '2':
      Keyboard.print('h');
      break;
    case '3':
      Keyboard.print('i');
      break;
    case '4':
      Keyboard.print('d');
      break;
    case '5':
      Keyboard.print('e');
      break;
    case '6':
      Keyboard.print('f');
      break;
    case '7':
      Keyboard.print('a');
      break;
    case '8':
      Keyboard.print('b');
      break;
    case '9':
      Keyboard.print('c');
      break;
  };
}

//ukuran frame tulisan di display
void frame () {
  display.drawRoundRect(0, 12, 41, 16, 5, WHITE);
  display.drawRoundRect(43, 12, 41, 16, 5, WHITE);
  display.drawRoundRect(86, 12, 41, 16, 5, WHITE);
  display.drawRoundRect(0, 30, 41, 16, 5, WHITE);
  display.drawRoundRect(43, 30, 41, 16, 5, WHITE);
  display.drawRoundRect(86, 30, 41, 16, 5, WHITE);
  display.drawRoundRect(0, 48, 41, 16, 5, WHITE);
  display.drawRoundRect(43, 48, 41, 16, 5, WHITE);
  display.drawRoundRect(86, 48, 41, 16, 5, WHITE);
  display.display();
}
//untuk ganti tulisan di display
void loop() {
  display.clearDisplay();
  FastLED.clear();
  char key = kpd.getKey();
  //cth : display.setCursor(53(angka ini yang dirubah, angka kecil semakin ke kiri), 16)
  //Serial.print(currentState);
  if (currentState == 0) {
    for (int i = 0; i < NUM_LEDS; i++ )
      leds[i] = CRGB(255, 255, 255 );
    FastLED.show();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 1);
    display.println("==    ARYASATYA    ==");
    display.setCursor(9, 16); display.println("PLAY"); display.setCursor(53, 16); display.println("NEXT"); display.setCursor(95, 16); display.println("PREV");
    display.setCursor(9, 34); display.println("MUTE"); display.setCursor(59, 34); display.println("UP"); display.setCursor(95, 34); display.println("STOP");
    display.setCursor(9, 52); display.println("LEFT"); display.setCursor(53, 52); display.println("DOWN"); display.setCursor(93, 52); display.println("RIGHT");
    frame();
    display.display();
  }
  if (currentState == 1) {
    for (int i = 0; i < NUM_LEDS; i++ )
      leds[i] = CRGB(100, 255, 0 );
    FastLED.show();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 1);
    display.println("==    BRATINDRA    ==");
    display.setCursor(12, 16); display.println("ESC"); display.setCursor(53, 16); display.println("REDO"); display.setCursor(92, 16); display.println("BACKS");
    display.setCursor(9, 34); display.println("CAPS"); display.setCursor(53, 34); display.println("UNDO"); display.setCursor(92, 34); display.println("ENTER");
    display.setCursor(7, 52); display.println("PG_DN"); display.setCursor(49, 52); display.println("SPACE"); display.setCursor(93, 52); display.println("PG_UP");
    frame();
    display.display();
  }
  if (currentState == 2) {
    for (int i = 0; i < NUM_LEDS; i++ )
      leds[i] = CRGB(0, 255, 255 );
    FastLED.show();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 1);
    display.println("==   CITAPRASADA   ==");
    display.setCursor(18, 16); display.println("A"); display.setCursor(62, 16); display.println("B"); display.setCursor(104, 16); display.println("C");
    display.setCursor(18, 34); display.println("D"); display.setCursor(62, 34); display.println("E"); display.setCursor(104, 34); display.println("F");
    display.setCursor(18, 52); display.println("G"); display.setCursor(62, 52); display.println("H"); display.setCursor(104, 52); display.println("I");
    frame();
    display.display();
  }
  if (currentState == 3) {
    for (int i = 0; i < NUM_LEDS; i++ )
      leds[i] = CRGB(255, 255, 0 );
    FastLED.show();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 1);
    display.println("==    DANANJAYA    ==");
    display.setCursor(18, 16); display.println("a"); display.setCursor(62, 16); display.println("b"); display.setCursor(104, 16); display.println("c");
    display.setCursor(18, 34); display.println("d"); display.setCursor(62, 34); display.println("e"); display.setCursor(104, 34); display.println("f");
    display.setCursor(18, 52); display.println("g"); display.setCursor(62, 52); display.println("h"); display.setCursor(104, 52); display.println("i");
    frame();
    display.display();
  }

  if (key) {
    switch (key) {
      case '*':
        ChangeState();
        break;
      default:
        switch (currentState) {
          case 0:
            Layout1(key);
            break;
          case 1:
            Layout2(key);
            break;
          case 2:
            Layout3(key);
            break;
          case 3:
            Layout4(key);
            break;

        }
    }
  }

  //check the encoder button
  if (encoderButton.update()) {
    if (encoderButton.fallingEdge()) {
      int fall = millis();
      while (!encoderButton.update()) {}
      if (encoderButton.risingEdge()) {
        int rise = millis();
        //Serial.println(rise - fall);
        if (rise - fall > timeLimit) {
          //Consumer.write(MEDIA_NEXT);
          //Serial.print("Next");
          ChangeState();
        } else {
          Consumer.write(MEDIA_PLAY_PAUSE);
          //Serial.print("Play/Pause");
        }
      }
      Keyboard.releaseAll();
    }
  }
  //untuk mapping encoder
  //check encoder rotation
  long newPosition = volumeKnob.read();
  if (newPosition != oldPosition) {
    Serial.print(newPosition);

    if((newPosition - oldPosition)>0){   
  switch(currentState){
  case 0:
  Consumer.write(MEDIA_VOLUME_UP);
  break;
  case 1:
  // Photoshop, Krita Brush size
  Keyboard.write(']');
  break;
  case 2:
  // Photoshop, Krita zoom in
  Keyboard.press(KEY_RIGHT_CTRL);
  Keyboard.press('=');
  Keyboard.releaseAll();
  break;
  case 3:
  break;
  }
    }else{
  switch(currentState){
  case 0:
  Consumer.write(MEDIA_VOLUME_DOWN);
  break;
  case 1:
  // Photoshop, Krita Brush size
  // Photoshop, Krita Brush size
  Keyboard.write('[');
  break;
  case 2:
  // Photoshop, Krita zoom out
  Keyboard.press(KEY_RIGHT_CTRL);
  Keyboard.press('-');
  Keyboard.releaseAll();
  break;
  case 3:
  break;
  }
}
    oldPosition = newPosition;
    Keyboard.releaseAll();
    delay(10); //a delay of 200 seems to be the sweet spot for this encoder.
  }
}
