#include <Servo.h>
#include <PS3BT.h>
#include <usbhub.h>

USB usb;
BTD btd(&usb);
PS3BT remote(&btd);

Servo MOTOR[12];
int motorPin[12] = {33,32,31,30,29,28,27,26,25,24,23,22};
int digitalSensor[12] = {38,41,40,37,36,35,34,39,42,43};
int analogSensor[12] = {4,3,6,7,8,9,10,11,12,13};
int led[3] = {5, 49, 3};
int i = 0;
bool isDisplaying[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
int lastMotorUP = -1;

void setup() {
  Serial.begin(115200);
  if(usb.Init() == -1){
    while(1);
  }
  Serial.print("BT Enabled");
  for(int i=0; i < 3; i++){
    pinMode(led[i], OUTPUT);
  }
  
  attachMotor(2);
  attachMotor(3);
  attachMotor(4);
  
}

void loop() {
  usb.Task();
  if(remote.PS3Connected){
    if(remote.getButtonClick(TRIANGLE)){
      displayPicture(2);
    }
    if(remote.getButtonClick(UP)){
      stopDisplayingPicture(2);
    }
    if(remote.getButtonClick(CIRCLE)){
      displayPicture(3);
    }
    if(remote.getButtonClick(RIGHT)){
      stopDisplayingPicture(3);
    }
    if(remote.getButtonClick(CROSS)){
      displayPicture(4);
    }
    if(remote.getButtonClick(DOWN)){
      stopDisplayingPicture(4);
    }
  }
}

/**
 * Attach the motors
 * @prams motorNumber The Motor that needs to be attach
 */
void attachMotor(int motorNumber) {
  pinMode(motorNumber-1, OUTPUT);
  MOTOR[motorNumber - 1].attach(motorPin[motorNumber - 1], 1000, 2000);
}

/**
 * Set the motor at a certain speed, direction;
 * @prams motorNumber     The Motor that need to turn
 * @prams dir             The direction that the motor need to turn -1 counter, 1 clockwidse
 * @prams speedPercentage The power of the motor.
 */
void setMotor(int motorNumber, int dir, int speedPercentage) {
  if (speedPercentage > 100) {
    speedPercentage = 100;
  }
  else if (speedPercentage <= 0) {
    speedPercentage = 0;
  }
  if (motorNumber <= 12 && motorNumber >= 1) {
    if (dir == 1) {
      MOTOR[motorNumber - 1].write(90 + (90 * speedPercentage));
    }
    else if (dir == -1) {
      MOTOR[motorNumber - 1].write(90 - (90 * speedPercentage));
    }
  }
}

void displayPicture(int motor){
  if(!isDisplaying[motor-1]){
    lastMotorUP = -1;
    isDisplaying[motor-1] = true;
    setMotor(motor, 1, 100);
    delay(180);
    setMotor(motor, 1, 0);
  }
}

void stopDisplayingPicture(int motor){
  if(isDisplaying[motor-1]){
    isDisplaying[motor-1] = false;
    setMotor(motor, -1, 50);
    delay(50);
    setMotor(motor, -1, 0);
  }
}

