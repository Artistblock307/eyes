#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  140
#define SERVOMAX  520

uint8_t servonum = 0;

int xval = 0;
int yval = 0;
int knobval = 0;
int buttonval = 0;

/*
//separate eye movement not enabled in this version
int left_eye_x_axis = 0;
int left_eye_y_axis = 0 ;

int right_eye_x_axis = 0;
int right_eye_y_axis = 0;
*/

int eye_x_axis = 0;
int eye_y_axis = 0;

int blink_upper_eyelid_pulse_length = 0;
int blink_lower_eyelid_pulse_length = 0;

const int Joy1 = A0;
const int Joy2 = A1;
const int Knob = A2;
const int Button = 2;

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
  pinMode(Joy1, INPUT);
  pinMode(Joy2, INPUT);
  pinMode(Knob, INPUT);
  pinMode(Button, INPUT);

  pwm.begin();

  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
}

void loop() {

  /*
  left_eye_x_axis = map(xval, 0, 1023, 220, 440);
  right_eye_x_axis = left_eye_x_axis;
  */

  xval = analogRead(Joy1);
  eye_x_axis = constrain(xval, 220, 440);

  /*
  left_eye_y_axis = map(yval, 0, 1023, 250, 500);
  right_eye_y_axis = left_eye_y_axis;
  */

  yval = analogRead(Joy2);
  eye_y_axis = constrain(yval, 250, 500);
  
  knobval = constrain(analogRead(Knob), -40, 40);
  blink_upper_eyelid_pulse_length = constrain(yval, 280, 400);
  blink_lower_eyelid_pulse_length = 680 - blink_upper_eyelid_pulse_length;

  pwm.setPWM(0, 0, eye_x_axis);
  pwm.setPWM(1, 0, eye_y_axis);

  if (Button == HIGH) {
    pwm.setPWM(2, 0, 400);
    pwm.setPWM(3, 0, 240);
    pwm.setPWM(4, 0, 240);
    pwm.setPWM(5, 0, 400);
  }
  else if (Button == LOW) {
    pwm.setPWM(2, 0, blink_upper_eyelid_pulse_length);
    pwm.setPWM(3, 0, blink_lower_eyelid_pulse_length);
    pwm.setPWM(4, 0, blink_upper_eyelid_pulse_length);
    pwm.setPWM(5, 0, blink_lower_eyelid_pulse_length);
  }
}