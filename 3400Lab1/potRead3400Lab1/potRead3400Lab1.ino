
int readValue = 0;
int pinName = A0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  readValue = analogRead(pinName);
  Serial.println(readValue);
  delay(500);
}
