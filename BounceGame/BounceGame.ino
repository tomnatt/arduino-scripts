/*
  Bounce a square back and forth
  Press button in end square to score a point
 */

// include the library code:
#include <LiquidCrystal.h>

// set pin numbers:
const int buttonPin = 7;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// variables will change:
int buttonState = 0;
int cursorCol = 0;
int cursorRow = 0;
int score = 0;
int cursorSpeed = 100; // lower is faster
boolean movingRight = true;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  intro();
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // clear screen for new cycle
  lcd.clear();

  // print score
  lcd.setCursor(0, 1);
  lcd.print(score);

  // print char in slot
  lcd.setCursor(cursorCol, cursorRow);
  lcd.write((char)219);

  /*
   Moving left:
   1,14,15 - button doesn't matter, move marker
   2-13 - button HIGH = death, otherwise move marker
   0 - button LOW = death, otherwise reverse and move marker

   Moving right:
   0,1,14 - button doesn't matter, move marker
   2-13 - button HIGH = death, otherwise move marker
   15 - button LOW = death, otherwise reverse and move marker
  */

  switch (cursorCol) {
    case 0:
      endPosition();
      break;

    case 1:
      moveMarker();
      break;

    case 14:
      moveMarker();
      break;

    case 15:
      endPosition();
      break;

    default:
      defaultPosition();
      break;
  }

  // wait for next cycle
  delay(cursorSpeed);
}

// intro / reset sequence
void intro() {
  // Print a message to the LCD.
  lcd.print("Ready!");
  resetVariables();
  delay(2000);
}

void resetVariables() {
  cursorCol = 0;
  cursorRow = 0;
  score = 0;
  movingRight = true;
}

void die() {
  lcd.clear();
  intro();
}

void moveMarker() {
  if (movingRight) {
    cursorCol++;
  } else {
    cursorCol--;
  }
}

void reverseDirection() {
  movingRight = !movingRight;
}

void defaultPosition() {
  if (buttonState == HIGH) {
    die();
  } else {
    moveMarker();
  }
}

void endPosition() {
  // skip most of the logic if it's the first round
  if (score == 0 && cursorCol == 0) {
    moveMarker();
  } else {
    if (buttonState == HIGH) {
      score++;
      reverseDirection();
      moveMarker();
    } else {
      die();
    }
  }
}
