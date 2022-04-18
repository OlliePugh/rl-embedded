// https://lastminuteengineers.com/a4988-stepper-motor-driver-arduino-tutorial/

// Include the AccelStepper Library
#include <AccelStepper.h>
#include <ezButton.h>

#define BOTTOM_LIMIT_PIN 6
#define TOP_LIMIT_PIN 8
#define DIRECTION_PIN 2
#define STEP_PIN 3
#define MOTOR_INTERFACE_TYPE 1
#define DEBOUNCE_TIME 50
#define STEPPER_SPEED 500

ezButton bottomLimit(BOTTOM_LIMIT_PIN);  
ezButton topLimit(TOP_LIMIT_PIN);  
AccelStepper stepper(MOTOR_INTERFACE_TYPE, STEP_PIN, DIRECTION_PIN);

boolean moveUp = true;

void setup() {
  Serial.begin(9600);
  pinMode(12, INPUT_PULLUP);  // TO ACT AS MASTER FOR NOW
  bottomLimit.setDebounceTime(DEBOUNCE_TIME); // set debounce time to 50 milliseconds
  topLimit.setDebounceTime(DEBOUNCE_TIME);
  stepper.setMaxSpeed(500);
}

void loop() {
  bottomLimit.loop();
  topLimit.loop();

  moveUp = digitalRead(12);

  if (moveUp && topLimit.getState() == HIGH) {  // desired point is top and not already there
    stepper.setSpeed(-STEPPER_SPEED);
    stepper.runSpeed();
  }
  else if (!moveUp && bottomLimit.getState() == HIGH) {  // desired point is bottom and is not already there
    stepper.setSpeed(STEPPER_SPEED);
    stepper.runSpeed();
  }
}
