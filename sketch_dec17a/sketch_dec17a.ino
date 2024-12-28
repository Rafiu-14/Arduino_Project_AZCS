#include <Servo.h>  // Import the Servo library

// Define the two servos
Servo myservo;
Servo myservo1;
Servo myservo2;

// LED pins
const int led = 13;
const int led1 = 12;

// Buzzer pin
const int buzzerPin = 11;

// 7-segment display pins (A to G)
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8};

// Left digit control pin
const int leftDigit = 10;

// Digit patterns for 0 to 9 (common cathode display)
const byte digitPatterns[] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110  // 9
};

void setup() {
  // Set up the LED and buzzer pins
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Attach servos to their respective pins
  myservo.attach(9, 500, 2500);
  myservo1.attach(10, 500, 2500);
  myservo2.attach(A0, 500, 2500); // Attach servo2 to A0

  // Set all segment pins as OUTPUT
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Set the left digit pin as OUTPUT
  pinMode(leftDigit, OUTPUT);
}

// Function to display a number on the 7-segment display
void displayDigit(int digit) {
  // Turn off the digit before setting segments
  digitalWrite(leftDigit, LOW);

  // Send the pattern for the desired digit to the segments
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], (digitPatterns[digit] >> (7 - i)) & 1);
  }

  // Turn on the left digit
  digitalWrite(leftDigit, HIGH);
}

void loop() {
  for (int count = 9; count >= 0; count--) {
    displayDigit(count);
    delay(1000);  // Wait for 1 second

    // Activate a beep for each second when the countdown reaches 5 seconds or below
    if (count <= 6 && count > 1) {
      tone(buzzerPin, 1000, 500);  // Beep for 500 milliseconds
    }
  }

  // Perform the servo and LED sequence after countdown
// First sequence: Servo 1 ON, Servo 2 OFF
myservo.write(90);       // Servo 1 moves to 90°
myservo1.write(0);       // Servo 2 stays at 0°
myservo2.write(0);
digitalWrite(led, HIGH); // LED 1 ON
delay(20000);             // Wait for 8 seconds
digitalWrite(led, LOW);  // LED 1 OFF

// Reset servos before the second sequence
myservo.write(0);        // Reset Servo 1 to 0°
delay(1000);             // Give time to reset

// Second sequence: Servo 2 ON, Servo 1 OFF
myservo1.write(90);      // Servo 2 moves to 90°
myservo2.write(90);
digitalWrite(led1, HIGH);// LED 2 ON
delay(10000);             // Wait for 8 seconds
digitalWrite(led1, LOW); // LED 2 OFF

// // Reset Servo 2
// myservo1.write(0);       // Reset Servo 2 to 0°
// delay(1000);             // Give time to reset


}
