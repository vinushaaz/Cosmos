
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ================================================
// COSMO EYES
// ESP32-C3 Super Mini + 128x64 SSD1306 OLED
// Four expressions: Normal, Happy, Angry, Sleepy
// ================================================

#define OLED_SDA 8
#define OLED_SCL 9
#define TOUCH_PIN 4

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1
);

// Expression states
enum Expression {
  NORMAL,
  HAPPY,
  ANGRY,
  SLEEPY
};

Expression expression = NORMAL;

const char* expressionNames[] = {
  "NORMAL", "HAPPY", "ANGRY", "SLEEPY"
};

// Eye positions
const int LEFT_EYE_X = 33;
const int RIGHT_EYE_X = 95;
const int EYE_Y = 32;

// Touch handling
int previousTouch = LOW;
unsigned long lastTouchMs = 0;
const unsigned long debounceMs = 250;

// Animation timing
unsigned long lastFrameMs = 0;
unsigned long nextBlinkMs = 0;
unsigned long blinkStartMs = 0;

const unsigned long frameInterval = 35;
const unsigned long blinkDuration = 150;

bool blinking = false;
int frame = 0;
int lookX = 0;
int lookY = 0;

// ================================================
// DRAW ONE EYE
// ================================================

void drawEye(int x, int y, int w, int h,
             int pupilOffsetX, int pupilOffsetY) {

  int left = x - w / 2;
  int top = y - h / 2;

  // Cyan eye body (white pixels on monochrome OLED)
  display.fillRoundRect(
    left, top, w, h, min(10, h / 2),
    SSD1306_WHITE
  );

  // Angry eyelids: diagonal black masks
  if (expression == ANGRY) {

    if (x < 64) {
      // Left eye slopes down toward the centre
      display.fillTriangle(
        left, top,
        left + w, top,
        left + w, top + h / 2,
        SSD1306_BLACK
      );
    } else {
      // Right eye slopes down toward the centre
      display.fillTriangle(
        left, top,
        left + w, top,
        left, top + h / 2,
        SSD1306_BLACK
      );
    }
  }

  // Sleepy eyelids cover the upper portion
  if (expression == SLEEPY) {
    display.fillRect(
      left, top, w, h / 2,
      SSD1306_BLACK
    );

    // Visible eyelid edge
    display.drawLine(
      left, y,
      x, y + 3,
      SSD1306_WHITE
    );

    display.drawLine(
      x, y + 3,
      left + w, y,
      SSD1306_WHITE
    );
  }

  // Moving dark horizontal pupil/slit
  int slitW = w - 10;
  int slitH = max(2, h / 7);

  int slitX = x - slitW / 2 + pupilOffsetX;
  int slitY = y - slitH / 2 + pupilOffsetY;

  slitX = constrain(slitX, left + 4, left + w - slitW - 4);
  slitY = constrain(slitY, top + 3, top + h - slitH - 3);

  display.fillRoundRect(
    slitX, slitY, slitW, slitH,
    max(1, slitH / 2),
    SSD1306_BLACK
  );
}

// ================================================
// CLOSED EYES FOR BLINKING
// ================================================

void drawClosedEye(int x, int y) {
  display.fillRoundRect(
    x - 18, y - 2, 36, 4, 2,
    SSD1306_WHITE
  );
}

// ================================================
// DRAW BOTH EYES
// ================================================

void drawFace() {
  display.clearDisplay();

  int leftY = EYE_Y + lookY;
  int rightY = EYE_Y + lookY;

  int eyeW = 42;
  int eyeH = 30;

  // Give each expression a different eye shape
  switch (expression) {

    case NORMAL:
      eyeW = 42;
      eyeH = 30;
      break;

    case HAPPY:
      eyeW = 46;
      eyeH = 21;
      leftY += 3;
      rightY += 3;
      break;

    case ANGRY:
      eyeW = 44;
      eyeH = 27;
      leftY += 1;
      rightY += 1;
      break;

    case SLEEPY:
      eyeW = 43;
      eyeH = 29;
      leftY += 5;
      rightY += 5;
      break;
  }

  // Sleepy eyes blink less often
  if (blinking) {
    drawClosedEye(LEFT_EYE_X, leftY);
    drawClosedEye(RIGHT_EYE_X, rightY);
    display.display();
    return;
  }

  drawEye(
    LEFT_EYE_X + lookX,
    leftY, eyeW, eyeH,
    lookX, 0
  );

  drawEye(
    RIGHT_EYE_X + lookX,
    rightY, eyeW, eyeH,
    lookX, 0
  );

  display.display();
}

// ================================================
// CHANGE EXPRESSION ON TOUCH
// ================================================

void changeExpression() {
  expression = (Expression)(
    ((int)expression + 1) % 4
  );

  blinking = false;
  frame = 0;
  lookX = 0;
  lookY = -1;

  nextBlinkMs = millis() + random(1800, 4000);

  Serial.print("COSMO: ");
  Serial.println(expressionNames[expression]);

  drawFace();
}

// ================================================
// SETUP
// ================================================

void setup() {
  Serial.begin(115200);

  pinMode(TOUCH_PIN, INPUT);

  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(
        SSD1306_SWITCHCAPVCC, OLED_ADDR)) {

    Serial.println("OLED initialization failed!");

    while (true) {
      delay(100);
    }
  }

  randomSeed(micros());

  display.clearDisplay();
  display.display();

  // Avoid accidental touch at startup
  while (digitalRead(TOUCH_PIN) == HIGH) {
    delay(10);
  }

  previousTouch = LOW;
  expression = NORMAL;

  nextBlinkMs = millis() + random(1800, 4000);

  drawFace();

  Serial.println("COSMO EYES ready!");
}

// ================================================
// MAIN LOOP
// ================================================

void loop() {
  unsigned long now = millis();
  int touch = digitalRead(TOUCH_PIN);

  // One expression change per touch
  if (touch == HIGH &&
      previousTouch == LOW &&
      now - lastTouchMs >= debounceMs) {

    lastTouchMs = now;
    changeExpression();
  }

  previousTouch = touch;

  // Non-blocking animation
  if (now - lastFrameMs >= frameInterval) {
    lastFrameMs = now;
    frame++;

    // Automatic blinking
    if (!blinking && now >= nextBlinkMs) {
      blinking = true;
      blinkStartMs = now;
    }

    if (blinking &&
        now - blinkStartMs >= blinkDuration) {

      blinking = false;
      nextBlinkMs = now + random(1800, 4000);
    }

    // Smooth-style left, centre, right movement
    // using small pixel steps
    int phase = frame % 90;

    if (expression == SLEEPY) {
      lookX = 0;
      lookY = (frame % 40 < 20) ? 0 : 1;
    } else if (phase < 25) {
      lookX = -2;
      lookY = 0;
    } else if (phase < 50) {
      lookX = 0;
      lookY = -1;
    } else if (phase < 75) {
      lookX = 2;
      lookY = 0;
    } else {
      lookX = 0;
      lookY = 1;
    }

    drawFace();
  }

  delay(2);
}
