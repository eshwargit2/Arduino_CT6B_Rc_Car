
const int ENA = 3;   // PWM for left motors
const int IN1 = 5;
const int IN2 = 6;
const int ENB = 11;  // PWM for right motors
const int IN3 = 9;
const int IN4 = 10;


const int throttlePin = A0;  // CH2 - Throttle
const int steeringPin = A1;  // CH1 - Steering

int throttleVal = 0;
int steeringVal = 0;

void setup() {
 
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

 
  pinMode(throttlePin, INPUT);
  pinMode(steeringPin, INPUT);

  Serial.begin(9600);  
}

void loop() {

  throttleVal = pulseIn(throttlePin, HIGH, 25000);  
  steeringVal = pulseIn(steeringPin, HIGH, 25000);  


  Serial.print("Throttle: ");
  Serial.print(throttleVal);
  Serial.print(" | Steering: ");
  Serial.println(steeringVal);


  int throttleMapped = 0;
  int steeringMapped = 0;

  if (throttleVal >= 1000 && throttleVal <= 2000) {
    throttleMapped = map(throttleVal, 1000, 2000, -255, 255);
  }

  if (steeringVal >= 1000 && steeringVal <= 2000) {
    steeringMapped = map(steeringVal, 1000, 2000, -150, 150);  
  }


  int leftSpeed = throttleMapped + steeringMapped;
  int rightSpeed = throttleMapped - steeringMapped;


  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);


  setMotor(ENA, IN1, IN2, leftSpeed);   
  setMotor(ENB, IN3, IN4, rightSpeed);  
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

  analogWrite(enPin, abs(speed));  // Set motor speed using PWM
}
