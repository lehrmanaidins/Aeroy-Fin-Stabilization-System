
/**
 * +----------------------------------------+
 * | Main Code                              |
 * +----------------------------------------+
 * | @author aeroy-official                 |
 * | @author lehrmanaidins                  |
 * | @version 1.0.0                         |
 * | @date 12/5/2023                        |
 * +----------------------------------------+
 * | Vector3:                               |
 * |   https://github.com/jimmyberg/Vector3 |
 * +----------------------------------------+
*/

#include "/workspaces/Aeroy-Fin-Stabilization-System/arduino-library-files-master/libraries/Wire/Wire.h"
#include "MPU6050_tockn.h"
#include "Servo.h"

#include "controller.cpp"
#include "telemetry.cpp"

Controller controller;
MPU6050 mpu6050;

unsigned long timeMilliseconds = 1000UL;

void setup() {
  mpu6050(Wire);
  controller(mpu6050, "pins.json");
  
  digitalWrite(ledpinr, HIGH);
  digitalWrite(ledping, HIGH);
  digitalWrite(buzzer, HIGH);
}

void loop() {
  mpu6050.update();

  if (timeMilliseconds - millis() <= 0UL) {
    float angleX = mpu6050.getAngleX();
    float angleY = mpu6050.getAngleY();

    printAngles(angleX, angleY);
  }

  if (mpu6050.getAngleX() > -1 && mpu6050.getAngleX() < 1) {
    servo2.write(90);
  } else {
    servo2.write(90 - mpu6050.getAngleY());
  }

  if (mpu6050.getAngleX() == 0) {
    servo1.write(90);
  } else {
    servo1.write(90 + mpu6050.getAngleY());
  }

  // Y-axis / pitch
  if (mpu6050.getAngleY() == 0) {
    servo3.write(90);
  } else {
    servo3.write(90 + mpu6050.getAngleX());
  }

  if (mpu6050.getAngleY() == 0) {
    servo4.write(90);
  } else {
    servo4.write(90 - mpu6050.getAngleX());
  }
}

void printAngles(float angleX, float angleY, float angleZ) {
    Serial.print("x\u00b0: " + angleX + "\ty\u00b0: " + angleY + "\tz\u00b0: " + angleZ);
}
