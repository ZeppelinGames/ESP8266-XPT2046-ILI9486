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

enum class PointID { NONE = -1, A, B, C, COUNT };

//Calibration - needs to be fixed to calibrate properly
// source points used for calibration
//static TS_Point _screenPoint[] = {
//  TS_Point(30, 40), // point A
//  TS_Point(304, 29), // point B
//  TS_Point(33, 222)  // point C
//};
//
//// touchscreen points used for calibration verification
//static TS_Point _touchPoint[] = {
//  TS_Point(3667, 3355), // point A
//  TS_Point(405, 3519), // point B
//  TS_Point(3635, 611), // point C
//};

static TS_Point _screenPoint[] = {
  TS_Point(214, 74), // point A
  TS_Point(446, 110), // point B
  TS_Point(39, 309)  // point C
};

// touchscreen points used for calibration verification
static TS_Point _touchPoint[] = {
  TS_Point(2324, 3128), // point A
  TS_Point(481, 2712), // point B
  TS_Point(3718, 468), // point C
};

static TS_Calibration cal(
  _screenPoint[(int)PointID::A], _touchPoint[(int)PointID::A],
  _screenPoint[(int)PointID::B], _touchPoint[(int)PointID::B],
  _screenPoint[(int)PointID::C], _touchPoint[(int)PointID::C],
  WIDTH,
  HEIGHT
);

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

void setup()
{
  randomSeed(analogRead(0));
  Serial.begin(115200);

  // Setup the LCD
  tft.init();
  tft.setRotation(ROTATION);

  ts.begin();
  ts.setRotation(ROTATION);
  ts.calibrate(cal);

  //drawKeyboard();
}

void loop() {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();
    Serial.print(p.x);
    Serial.print(", ");
    Serial.println(p.y);

    //isUppercase = !isUppercase;
    //drawKeyboard();
  }
}
