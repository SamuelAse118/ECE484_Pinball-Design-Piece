/*
Copyright (c) 2024 Samuel Asebrook
*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define the OLED screen
Adafruit_SSD1306 display(128, 64, &WIRE, -1);

// Define the pin numbers for the sensors
const int opticalSensorPin = A0; // 5V
const int limitSwitchPin = 2; // 3.3V
// LCD SDA Pin = A4
// LCD SCL Pin = A5

unsigned long startTime;
unsigned long elapsedTime;
int multiplier = 1;
int score = 0;
int highScore = 0;
bool gameStarted = false;
bool state0_moved = false;
bool state1_moved = false;
bool state2_moved = false;
bool state3_moved = false;
bool state4_moved = false;

int state_0, state_1, state_2, state_3, state_4 = 0; // Dummy variables strictly for local compilation purposes, REMOVE UPON GROUP COMPILATION

/*
void scrollText(int row, String message, int delayTime) {
  message = message + "           ";

  for (int i = 0; i < message.length(); i++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(i));

    delay(delayTime);
  }
}
*/

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Hell Yeah!");
  display.setCursor(0,16);
  display.println("Pinball!");
  display.display();

  pinMode(opticalSensorPin, INPUT);
  pinMode(limitSwitchPin, INPUT_PULLUP);
}

void loop() {
  int opticalSensorState = digitalRead(opticalSensorPin);
  int limitSwitchState = digitalRead(limitSwitchPin);

  if (opticalSensorState == HIGH && !gameStarted) {
    // The launcher has been pulled back, start the game
    startTime = millis();
    gameStarted = true;

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("Good Luck!");
    display.setCursor(0,16);
    display.println("You Will Need It!");
    display.display();
    delay(1000);
  }

  if ((state_1 == 1 && state1_moved == false) || (state_2 == 1 && state2_moved == false) || (state_3 == 1 && state3_moved == false) || (state_4 == 1 && state4_moved == false) ) {
    score = score + (multiplier * 100);

    if (state_1 == 1) {
      state1_moved = true;
    } else if (state_2 == 1) {
      state2_moved = true;
    } else if (state_3 == 1) {
      state3_moved = true;
    } else if (state_4 == 1) {
      state4_moved = true;
    }
  }

  if ((state_1 == 2 && state1_moved == true) || (state_2 == 2 && state2_moved == true) || (state_3 == 2 && state3_moved == true) || (state_4 == 2 && state4_moved == true) ) {
    score = score + (multiplier * 200);

    if (state_1 == 2) {
      state1_moved = false;
    } else if (state_2 == 2) {
      state2_moved = false;
    } else if (state_3 == 2) {
      state3_moved = false;
    } else if (state_4 == 2) {
      state4_moved = false;
    }
  }

  if ((state_1 == 3 && state1_moved == false) || (state_2 == 3 && state2_moved == false) || (state_3 == 3 && state3_moved == false) || (state_4 == 3 && state4_moved == false) ) {
    score = score + (multiplier * 300);

    if (state_1 == 3) {
      state1_moved = true;
    } else if (state_2 == 3) {
      state2_moved = true;
    } else if (state_3 == 3) {
      state3_moved = true;
    } else if (state_4 == 3) {
      state4_moved = true;
    }
  }

  if ((state_1 == 4 && state1_moved == true) || (state_2 == 4 && state2_moved == true) || (state_3 == 4 && state3_moved == true) || (state_4 == 4 && state4_moved == true) ) {
    score = score + (multiplier * 1000);

    if (state_1 == 4) {
      state1_moved = false;
    } else if (state_2 == 4) {
      state2_moved = false;
    } else if (state_3 == 4) {
      state3_moved = false;
    } else if (state_4 == 4) {
      state4_moved = false;
    }
  }

  if (state_1 == 4 && state_2 == 4 && state_3 == 4 && state_4 == 4) {
    
    state_1 == 0;
    state_2 == 0;
    state_3 == 0;
    state_4 == 0;

    multiplier = multiplier * 2;
  }

  if (gameStarted && limitSwitchState == LOW) {
    // The limit switch has been pressed, end the game
    elapsedTime = millis() - startTime;
    gameStarted = false;

    // Calculate the score
    score = score + (elapsedTime / 100);
    if (score > highScore) {
      highScore = score;
    }

    // Display the score on the OLED
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    
    display.setCursor(0,0);
    display.print("Score: ");
    display.println(score);
    
    display.setCursor(0,16);
    display.print("High: ");
    display.println(highScore);

    display.display();

    // Reset game score and score multiplier at end of game
    score = 0;
    multiplier = 1;
  }
}
