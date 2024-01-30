int IN1 = 2;  // Relay control pin
//int IN2 = 3;
//int IN3 = 4;

int Pin1 = A0;  // Water sensor. Air/dry is ~500-600
//int Pin2 = A1;
//int Pin3 = A2;

float value1 = 0;

static const int heartbeat = 13;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  pinMode(IN1, OUTPUT);
  pinMode(Pin1, INPUT);
  pinMode(heartbeat)
  digitalWrite(IN1, HIGH);
  delay(1000);
}
void loop() {
  Serial.print("MOISTURE LEVEL:");
  moisture = analogRead(Pin1);
  Serial.println(moisture);
  
  
  if(value1>550)
  {
    // Water for 10 seconds
    digitalWrite(IN1, LOW);
    digitalWrite(heartbeat, HIGH);
    delay(10000);
    digitalWrite(heartbeat, LOW);
    digitalWrite(IN1, HIGH);
    // Wait 5 seconds before checking checking moisture levels again
    delay(5000);
  }

  delay(1000);
}