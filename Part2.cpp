#include <Arduino.h>

const int buttonPin1 = 32; // Button 1
const int buttonPin2 = 13; // Button 2
const int buttonPin3 = 21; // Button 3
const int buttonPin4 = 22; // Button 4
const int buttonPin5 = 23; // Button 5
const int buttonPin6 = 18; // Button 6
const int buttonPin7 = 16; // Button 7
const int buttonPin8 = 17; // Button 8

const int light1 = 14; // Out to pin
const int light2 = 27; // Out to pin
const int light3 = 26; // Out to pin
const int light4 = 25; // Out to pin
const int light5 = 33; // Out to pin

const int onboardLedPin = 2;          // GPIO 2 connected for blue light on ESP32 board


int a0 = 0; // variable for input state of the button 1
int a1 = 0; // variable for input state of the button 2
int a2 = 0; // variable for input state of the button 3
int a3 = 0; // variable for input state of the button 4
int b0 = 0; // variable for input state of the button 5
int b1 = 0; // variable for input state of the button 6
int b2 = 0; // variable for input state of the button 7
int b3 = 0; // variable for input state of the button 8


int s0 = 0, s1 = 0, s2 = 0, s3 = 0;
int c0 = 0, c1 = 0, c2 = 0, c3 = 0;



void setup() {
  Serial.begin(9600);

  pinMode(light1, OUTPUT); // set led as output
  digitalWrite(light1, LOW);
  pinMode(light2, OUTPUT); // set led as output
  digitalWrite(light2, LOW);
  pinMode(light3, OUTPUT); // set led as output
  digitalWrite(light3, LOW);
  pinMode(light4, OUTPUT); // set led as output
  digitalWrite(light4, LOW);
  pinMode(light5, OUTPUT); // set led as output
  digitalWrite(light5, LOW);

  // set pins as inputs, the open button logic state for all will be HIGH
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);
  pinMode(buttonPin8, INPUT_PULLUP);
}

void loop() {
  a0 = digitalRead(buttonPin1);
  a0 = !a0;
  a1 = digitalRead(buttonPin2);
  a1 = !a1;
  a2 = digitalRead(buttonPin3);
  a2 = !a2;
  a3 = digitalRead(buttonPin4);
  a3 = !a3;
  b0 = digitalRead(buttonPin5);
  b0 = !b0;
  b1 = digitalRead(buttonPin6);
  b1 = !b1;
  b2 = digitalRead(buttonPin7);
  b2 = !b2;
  b3 = digitalRead(buttonPin8);
  b3 = !b3;

  // Half-Adder
  int s0 = (!a0 && b0) || (a0 && !b0);
  int c0 = (a0 && b0);

  // Full-Adder 1
  int s1 = (!c0 && !a1 && b1) || (!c0 && a1 && !b1) || (c0 && !a1 && !b1) || (c0 && a1 && b1);
  int c1 = (!c0 && a1 && b1) || (c0 && !a1 && b1) || (c0 && a1 && !b1) || (c0 && a1 && b1);

  // Full-Adder 2
  int s2 = (!c1 && !a2 && b2) || (!c1 && a2 && !b2) || (c1 && !a2 && !b2) || (c1 && a2 && b2);
  int c2 = (!c1 && a2 && b2) || (c1 && !a2 && b2) || (c1 && a2 && !b2) || (c1 && a2 && b2);
  
  //Full-Adder 3
  int s3 = (!c2 && !a3 && b3) || (!c2 && a3 && !b3) || (c2 && !a3 && !b3) || (c2 && a3 && b3);
  int c3 = (!c2 && a3 && b3) || (c2 && !a3 && b3) || (c2 && a3 && !b3) || (c2 && a3 && b3);

  if(s0 == HIGH) {
    digitalWrite(light1, HIGH);
  } else {
    digitalWrite(light1, LOW);
  }

  if(s1 == HIGH || c0 == HIGH) {
    digitalWrite(light2, HIGH);
  } else {
    digitalWrite(light2, LOW);
  }

  if(s2 == HIGH || c1 == HIGH) {
    digitalWrite(light3, HIGH);
  } else {
    digitalWrite(light3, LOW);
  }

  if(s3 == HIGH || c2 == HIGH) {
    digitalWrite(light4, HIGH);
  } else {
    digitalWrite(light4, LOW);
  }

  if(c3 == HIGH) {
    digitalWrite(light5, HIGH);
  } else {
    digitalWrite(light5, LOW);
  }
}
