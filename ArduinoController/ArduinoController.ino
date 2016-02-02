#include <Servo.h>

#include "BMP085.h"
#include "HMC5883L.h"
#include "MPU6050.h"

enum ServoPin {
  // TODO: Assign pins
  LEFT_FORWARD = 11,
  RIGHT_FORWARD = 10,
  LEFT_STRAFE = 9,
  RIGHT_STRAFE = 8,
  FRONT_DIVE = 7,
  BACK_DIVE = 6
};

typedef union _data {
  float f;
  char  s[4];
} floatData;

uint16_t readShort() {
  while(Serial.available() < 2) {}
  return Serial.read() << 8 | Serial.read();
}

class Controller {
 public:
  virtual void execute() = 0;
};

class ThrustController : public Controller {
 private:
   const uint16_t IDLE = 1500;
   Servo servo_;
 public:
  ThrustController(ServoPin servoPin) {
    servo_.attach(servoPin);
    servo_.writeMicroseconds(IDLE);
  }
  void execute() {
    uint16_t val = readShort();
    servo_.writeMicroseconds(val);
  }
};

class EscController : public Controller {
private:
  const uint8_t GPIO_PINS[6] = {35, 39, 41, 47, 49, 53};
public:
  EscController() {
    for(int i = 0; i < 6; i++) {
      pinMode(GPIO_PINS[i], OUTPUT);
      digitalWrite(GPIO_PINS[i], HIGH);
    }
  }
  void execute() {
    while(!Serial.available());
    uint8_t toggle = Serial.read();
    for(int i = 0; i < 6; i++) {
      digitalWrite(GPIO_PINS[i], !toggle);
    }
  }
};

class LedController : public Controller {
private:
  const uint8_t GREEN = 22;
  const uint8_t WHITE = 52;
public:
  LedController() {
    pinMode(WHITE, OUTPUT);
    digitalWrite(WHITE, LOW);
  }
  void execute() {
    for(int i = 0; i < 2; i++) {
      digitalWrite(WHITE, HIGH);
      delay(250);
      digitalWrite(WHITE, LOW);
      delay(250);
    }
  }
};

class EnvironmentController : public Controller {
private:
  BMP085 environment;
public:
  EnvironmentController() {
    environment.initialize(IMU_ENVIRONMENT_HIGHRES); 
  }
  void execute() {
    floatData t;
    floatData p;
    t.f = environment.readTemperature();
    p.f = environment.readAltitude();
    Serial.write(t.s, 4);
    Serial.write(p.s, 4);
  }
};

class CompassController : public Controller {
private:
  HMC5883L compass;
public:
  CompassController() {
    compass.setSampleAverage(HMC5883L::Sample::Sx4);
    compass.setOutputRate(HMC5883L::Rate::Hz75);
  }
  void execute() {
    uint16_t val;
    compass.setMode(HMC5883L::Mode::Single);
    delay(10);
    
    val = compass.X();
    Serial.write(val>>8);
    Serial.write(val);
    val = compass.Y();
    Serial.write(val>>8);
    Serial.write(val);
    val = compass.Z();
    Serial.write(val>>8);
    Serial.write(val);
  }
};

class MotionController : public Controller {
private:
  MPU6050 motion;
public:
  MotionController() {
    motion.awake();
  }
  void execute() {
    floatData temp;
    uint16_t val;
    val = motion.accel_X();
    Serial.write(val>>8);
    Serial.write(val);
    val = motion.accel_Y();
    Serial.write(val>>8);
    Serial.write(val);
    val = motion.accel_Z();
    Serial.write(val>>8);
    Serial.write(val);
    val = motion.gyro_X();
    Serial.write(val>>8);
    Serial.write(val);
    val = motion.gyro_Y();
    Serial.write(val>>8);
    Serial.write(val);
    val = motion.gyro_Z();
    Serial.write(val>>8);
    Serial.write(val);
    temp.f = motion.temperature();
    Serial.write(temp.s, 4);
  }
};

class 

Controller* controllers[11];

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  controllers[0] = new ThrustController(LEFT_FORWARD);
  controllers[1] = new ThrustController(RIGHT_FORWARD);
  controllers[2] = new ThrustController(LEFT_STRAFE);
  controllers[3] = new ThrustController(RIGHT_STRAFE);
  controllers[4] = new ThrustController(FRONT_DIVE);
  controllers[5] = new ThrustController(BACK_DIVE);
  controllers[6] = new EscController();
  controllers[7] = new LedController();
  controllers[8] = new EnvironmentController();
  controllers[9] = new CompassController();
  controllers[10]= new MotionController();
}

void loop() {
  if(Serial.available()) {
    uint8_t controllerNumber = Serial.read();
    controllers[controllerNumber]->execute();
  }
}
