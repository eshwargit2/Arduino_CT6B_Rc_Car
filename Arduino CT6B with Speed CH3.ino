// === Motor Driver Pins ===
const int ENA = 3;   // Left motor speed (PWM)
const int IN1 = 5;
const int IN2 = 6;
const int ENB = 11;  // Right motor speed (PWM)
const int IN3 = 9;
const int IN4 = 10;

// === Receiver Input Pins ===
const int ch1Pin = A1;  // Steering (Left/Right)
const int ch3Pin = A2;  // Throttle (Forward/Reverse)

int ch1Val = 0;
int ch3Val = 0;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ch1Pin, INPUT);
  pinMode(ch3Pin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // === Read signals ===
  ch1Val = pulseIn(ch1Pin, HIGH, 25000);  // Steering
  ch3Val = pulseIn(ch3Pin, HIGH, 25000);  // Throttle

  Serial.print("CH1 (Steering): ");
  Serial.print(ch1Val);
  Serial.print(" | CH3 (Throttle): ");
  Serial.println(ch3Val);

  int speed = 0;
  int steer = 0;

  // === Throttle: center = 1500. Add dead zone ===
  if (ch3Val > 1520) {
    speed = map(ch3Val, 1520, 2000, 0, 255);  // Forward
  } else if (ch3Val < 1480) {
    speed = map(ch3Val, 1000, 1480, -255, 0);  // Reverse
  } else {
    speed = 0;  // within dead zone
  }

  // === Steering ===
  if (ch1Val >= 1350 && ch1Val <= 1550) {
    steer = 0;  // centered
  } else if (ch1Val >= 1000 && ch1Val <= 2000) {
    steer = map(ch1Val, 1000, 2000, -300, 300);
  }

  // === Steering mix ===
  int leftSpeed = speed + steer;
  int rightSpeed = speed - steer;

  leftSpeed = constrain(leftSpeed, -300, 300);
  rightSpeed = constrain(rightSpeed, -300, 300);

  // === Drive motors ===
  setMotor(ENA, IN1, IN2, leftSpeed);   // Left
  setMotor(ENB, IN3, IN4, rightSpeed);  // Right
}

void setMotor(int enPin, int in1, int in2, int speed) {
  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);  // Stop
  }

  analogWrite(enPin, abs(speed));
}
