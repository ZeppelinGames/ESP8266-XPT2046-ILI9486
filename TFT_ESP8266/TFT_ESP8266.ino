#define WIDTH 480
#define HEIGHT 320
#define HCENTRE 240
#define VCENTRE 160

#define ROTATION 0

#define CS_PIN 15

#include <XPT2046_Calibrated.h>
#include <TFT_eSPI.h>
#include <SPI.h>

XPT2046_Calibrated ts(CS_PIN);
TFT_eSPI tft = TFT_eSPI();

#define TFT_GREY 0x7BEF

//Calibration - needs to be fixed to calibrate properly
#define VERIFY_CALIBRATION
static TS_Point _screenPoint[] = {
  TS_Point(13,  11), // point A
  TS_Point(312, 113), // point B
  TS_Point(167, 214)  // point C
};

static TS_Point _touchPoint[] = {
  TS_Point(3795, 3735), // point A
  TS_Point(482, 2200), // point B
  TS_Point(2084,  583), // point C
};

static TS_Calibration cal(
  _screenPoint[0], _touchPoint[0],
  _screenPoint[1], _touchPoint[1],
  _screenPoint[2], _touchPoint[2],
  WIDTH,
  HEIGHT
);

void setup()
{
  randomSeed(analogRead(0));
  Serial.begin(115200);

  ts.begin();
  ts.setRotation(ROTATION);
  ts.calibrate(cal);

  // Setup the LCD
  tft.init();
  tft.setRotation(ROTATION);

  drawKeyboard();
}

String keyboard_lower[][10] = {
  (String[10]) {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"},
  (String[10]) {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p"},
  (String[10]) {"a", "s", "d", "f", "g", "h", "j", "k", "l", "<-"},
  (String[10]) {"^", "z", "x", "c",  "__", "__", "v", "b", "n", "m"},
};


String keyboard_upper[][10] = {
  (String[10]) {"!", "@", "#", "$", "%", "^", "&", "*", "(", ")"},
  (String[10]) {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"},
  (String[10]) {"A", "S", "D", "F", "G", "H", "J", "K", "L", "<-"},
  (String[10]) {"/\\", "Z", "X", "C", "__", "__", "V", "B", "N", "M"},
};

bool isUppercase = false;

void drawKeyboard() {
  //DRAW KEYBOARD
  int items = (sizeof(keyboard_lower) / sizeof(keyboard_lower[0]));
  Serial.println(items);

  String keyboardarr[items][10];
  memcpy(keyboardarr, (isUppercase ? keyboard_upper : keyboard_lower), sizeof(keyboardarr));

  int keysize = 32;
  int hks = (int)(keysize / 4);
  int heightOffset = WIDTH - (items * keysize);

  int pad = 2;
  int hpad = (int)(pad / 2);

  tft.fillRect(0, heightOffset, WIDTH, 100, TFT_GREY);
  for (int i = 0; i < items; i++) {
    for (int j = 0; j < 10; j++) {
      tft.fillRect(j * keysize + hpad, i * keysize + heightOffset + hpad, keysize - pad, keysize - pad, TFT_BLACK);
      tft.drawString(keyboardarr[i][j] + " ", j * keysize + hks + hpad, i * keysize + heightOffset + hpad + hks);
    }
  }
}

void loop() {
  if (ts.touched()) {
    isUppercase = !isUppercase;
    drawKeyboard();
  }
}
