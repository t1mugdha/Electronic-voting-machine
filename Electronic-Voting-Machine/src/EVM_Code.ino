#include <LiquidCrystal_I2C.h>

// Button Pins
#define sw1 2  // Button 1
#define sw2 3  // Button 2
#define sw3 4  // Button 3
#define sw4 5  // Button 4
#define sw5 6  // Button 5 for result

// Vote counters
int vote1 = 0;
int vote2 = 0;
int vote3 = 0;
int vote4 = 0;

// Initialize LCD with I2C address (0x27) and size (16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Set button pins as input
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
  pinMode(sw4, INPUT_PULLUP);
  pinMode(sw5, INPUT_PULLUP);

  // Set LED pins as output
  pinMode(13, OUTPUT); // Red LED
  pinMode(12, OUTPUT); // Green LED

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Welcome Message
  lcd.setCursor(0, 0);
  lcd.print("     EVM");
  lcd.setCursor(0, 1);
  lcd.print("  DLD Project");
  delay(2000);
  lcd.clear();

  // Display voting options
  lcd.setCursor(0, 0);
  lcd.print("CSE EEE NFE SWE");
}

void loop() {
  // Display current vote counts
  lcd.setCursor(0, 1);
  lcd.print(vote1);  // BJP votes
  lcd.setCursor(4, 1);
  lcd.print(vote2);  // INC votes
  lcd.setCursor(8, 1);
  lcd.print(vote3);  // AAP votes
  lcd.setCursor(12, 1);
  lcd.print(vote4);  // OTH votes

  // Check for button presses and update votes
  if (digitalRead(sw1) == LOW) {
    vote1++;
    flashLED(12); // Green LED
  }
  if (digitalRead(sw2) == LOW) {
    vote2++;
    flashLED(12); // Green LED
  }
  if (digitalRead(sw3) == LOW) {
    vote3++;
    flashLED(12); // Green LED
  }
  if (digitalRead(sw4) == LOW) {
    vote4++;
    flashLED(12); // Green LED
  }

  // Check result button
  if (digitalRead(sw5) == LOW) {
    digitalWrite(13, HIGH); // Turn on Red LED for result processing
    showResult();
    digitalWrite(13, LOW);
  }
}

// Function to flash an LED
void flashLED(int pin) {
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
  delay(500);
}

// Function to display results
void showResult() {
  lcd.clear();
  int totalVotes = vote1 + vote2 + vote3 + vote4;

  if (totalVotes > 0) {
    if (vote1 > vote2 && vote1 > vote3 && vote1 > vote4) {
      lcd.print("CSE Wins");
    } else if (vote2 > vote1 && vote2 > vote3 && vote2 > vote4) {
      lcd.print("EEE Wins");
    } else if (vote3 > vote1 && vote3 > vote2 && vote3 > vote4) {
      lcd.print("NFE Wins");
    } else if (vote4 > vote1 && vote4 > vote2 && vote4 > vote3) {
      lcd.print("SWE Wins");
    } else {
      lcd.print("Tie Or No Result");
    }
  } else {
    lcd.print("No Votes Cast");
  }

  delay(5000); // Show result for 5 seconds
  resetVotes();
}

// Function to reset vote counts
void resetVotes() {
  vote1 = 0;
  vote2 = 0;
  vote3 = 0;
  vote4 = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CSE EEE NFE SWE");
}
