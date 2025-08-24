#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;
int solenoidValvePin = 7;  // Pin connected to the solenoid valve

void setup() {
  Serial.begin(9600);    // Debugging only
  if (!driver.init())
    Serial.println("init failed");
  pinMode(solenoidValvePin, OUTPUT);
  digitalWrite(solenoidValvePin, LOW); // Ensure the solenoid valve is initially closed
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    buf[buflen] = 0; // Null-terminate the string
    Serial.print("Message received: ");
    Serial.println((char*)buf);
    
    // Check the message and control the solenoid valve to either open or close
    if (strcmp((char*)buf, "Mid gas readings!") == 0 || strcmp((char*)buf, "Bad gas readings!") == 0) {
      digitalWrite(solenoidValvePin, HIGH); // Close the valve
      Serial.println("Solenoid valve closed due to non ideal gas readings.");
    } else {
      digitalWrite(solenoidValvePin, LOW); // Open the valve for good readings
      Serial.println("Solenoid valve now open (good gas readings).");
    }
  }
}
