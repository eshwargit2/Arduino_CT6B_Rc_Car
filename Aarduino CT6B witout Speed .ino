// === Motor Driver Pins ===
const int ENA = 3;   // PWM for left motors
const int IN1 = 5;
const int IN2 = 6;
const int ENB = 11;  // PWM for right motors
const int IN3 = 9;
const int IN4 = 10;

// === Receiver Input Pins ===
const int throttlePin = A0;  // CH2 - Throttle
const int steeringPin = A1;  // CH1 - Steering

int throttleVal = 0;
int steeringVal = 0;

void setup() {
  // Setup motor driver pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Receiver pins
  pinMode(throttlePin, INPUT);
  pinMode(steeringPin, INPUT);

  Serial.begin(9600);  // Debugging
}

void loop() {
  // === Read receiver PWM signals ===
  throttleVal = pulseIn(throttlePin, HIGH, 25000);  // CH2 - Throttle
  steeringVal = pulseIn(steeringPin, HIGH, 25000);  // CH1 - Steering

  // === Print for debugging ===
  Serial.print("Throttle: ");
  Serial.print(throttleVal);
  Serial.print(" | Steering: ");
  Serial.println(steeringVal);

  // === Map receiver inputs to motor control ===
  int throttleMapped = 0;
  int steeringMapped = 0;

  if (throttleVal >= 1000 && throttleVal <= 2000) {
    throttleMapped = map(throttleVal, 1000, 2000, -255, 255);
  }

  if (steeringVal >= 1000 && steeringVal <= 2000) {
    steeringMapped = map(steeringVal, 1000, 2000, -150, 150);  // Reduce turning sensitivity
  }

  // === Calculate left and right motor speeds ===
  int leftSpeed = throttleMapped + steeringMapped;
  int rightSpeed = throttleMapped - steeringMapped;

  // Constrain speeds to valid range
  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  // Drive motors
  setMotor(ENA, IN1, IN2, leftSpeed);   // Left motors
  setMotor(ENB, IN3, IN4, rightSpeed);  // Right motors
}

// === Motor control function ===
void setMotor(int enPin, int in1, int in2, int speed) {
  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);  // Forward
  } else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH); // Reverse
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);  // Stop
  }

  analogWrite(enPin, abs(speed));  // Set motor speed using PWM
}
