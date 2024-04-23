
// Motor control pins
int in1Pin = 2;  // Connect IN1 to Arduino digital pin 2
int in2Pin = 3;  // Connect IN2 to Arduino digital pin 3
int in3Pin = 4;
int in4Pin = 5;

byte ma = 0;
byte mb = 0;
byte mc = 0;

void setup() {
  Serial.begin(9600);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
}

void loop() {
  // handling
  if (Serial.available()) {
    String receivedString = Serial.readStringUntil('\n');
    
    // Pass the received string to another function
    handler(receivedString);
  }
  // Motor A
  if (ma == 0) {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
  }
  if (ma == 1) {
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
  }
  if (ma == 2) {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
  }

  // Motor B
  if (mb == 0) {
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, LOW);
  }
  if (mb == 1) {
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, LOW);
  }
  if (mb == 2) {
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, HIGH);
  }
  delay(1000);
}
void handler(String str) {
  Serial.println(str);
  if (str[0] == 'a' || str[0] == 'A') {
    ma = str[1] - '0';
  }
  if (str[0] == 'b' || str[0] == 'B') {
    mb = str[1] - '0';
  }
  if (str[0] == 'c' || str[0] == 'C') {
    mc = str[1] - '0';
  }
}
