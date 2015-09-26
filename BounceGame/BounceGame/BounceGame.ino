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
  
  if (movingRight) {
    if (cursorCol < 15) { 
      moveRight();
    } else {
      if (buttonState == HIGH) {
        score++;
        movingRight = false;
        moveLeft();
      } else {
        die();
      }
    }
  } else {
    if (cursorCol > 0) {
      moveLeft();
    } else {
      if (buttonState == HIGH) {
        score++;
        movingRight = true;
        moveRight();
      } else {
        die();
      }
    }
  }
  
  // wait for next cycle
  delay(300);
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

void moveLeft() {
  cursorCol--;
}

void moveRight() {
  cursorCol++;
}

void die() {
  lcd.clear();
  intro();
}
