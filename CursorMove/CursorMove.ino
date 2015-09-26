/*
  LiquidCrystal Library
  
  Moves a square around the edge of a 16x2 LCD screen.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int col = 0;
int row = 0;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Beginning!");
  delay(1000);
}

void loop() {
  lcd.clear();
  
  // print char in slot
  lcd.setCursor(col, row);
  lcd.write((char)219);
  delay(300);
  
  // ready new cursor position
  
  // if on first row, increment
  if (row == 0) {
    if (col < 15) { 
      col++;
    } else {
      row = 1;
    }
  
  // if on second row, decrement  
  } else {
    if (col > 0) {
      col--;
    } else {
      row = 0;
    }
  }
}

