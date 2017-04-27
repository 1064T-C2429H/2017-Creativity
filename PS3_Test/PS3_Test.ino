#include <usbhub.h>
#include <PS3BT.h>

USB usb;
BTD btd(&usb);
PS3BT remote(&btd);

int JOYSTICK_THRESHOLD_MAX = 137;
int JOYSTICK_THRESHOLD_MIN = 117;


void setup() {
  Serial.begin(115200);
  if(usb.Init() == -1){ //Did not start
    Serial.print("The bluetooth device did not start! Stopping code!");
    while(1);
  }
  Serial.print("Bluetooth Innitialized! \n");
}

void loop() {
  usb.Task();

  if (remote.PS3Connected || remote.PS3NavigationConnected) {
    if (remote.getAnalogHat(LeftHatX) > 137 || remote.getAnalogHat(LeftHatX) < 117 || remote.getAnalogHat(LeftHatY) > 137 || remote.getAnalogHat(LeftHatY) < 117 || remote.getAnalogHat(RightHatX) > 137 || remote.getAnalogHat(RightHatX) < 117 || remote.getAnalogHat(RightHatY) > 137 || remote.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(remote.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(remote.getAnalogHat(LeftHatY));
      if (remote.PS3Connected) { // The Navigation controller only have one joystick
        Serial.print(F("\tRightHatX: "));
        Serial.print(remote.getAnalogHat(RightHatX));
        Serial.print(F("\tRightHatY: "));
        Serial.print(remote.getAnalogHat(RightHatY));
      }
    }
  }
}
