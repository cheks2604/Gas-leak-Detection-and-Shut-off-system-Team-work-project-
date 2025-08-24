// ENGR122 01 EASLEY || Prototype 2 Code - Emerson LeDoux, Kameron Robinson, Austin Spencer, Chekwube Osonwa //

/**************** VARIABLES *************/
#define sensorPin A5        // declares analog pin attached to MQ2 sensor
int redLED   = 9;           // variables from lines 6-8 are to program the RGB lighting
int greenLED = 10;
int blueLED  = 11;
unsigned long periodstart1; // variables on lines 9-12 are for a timer system without using the delay() command
unsigned long periodstart2;
const int alarmON1 = 250; const int alarmON2 = 1000;
const int period1 = 5000; const int period2 = 2000;
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#define TRANSMITTER_PIN 12 
RH_ASK driver(2000, 12, TRANSMITTER_PIN);

/*********************************************** MAIN CODE *********************************************/
void setup() {
  Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
  Serial.begin(9600);                  // begin serial monitor @ 9600
  pinMode(redLED, OUTPUT);             // set pinmodes for LED and piezo speaker to OUTPUT
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  Serial.print("Analog output: ");
  Serial.println(readSensor());         // prints defined sensor value 
  LED_control();                        // user defined function (see below)
  Piezo_control();                      // user defined function (see below)
  delay(1000);                          // delay code by 1 second for testing and analyzing purposes
}

/****************************************************** USER-DEFINED FUNCTIONS & VARIABLES ********************************************/
// 1.) MAP INTEGER FOR MQ2 OUTPUT IN SERIAL MONITOR
int readSensor() {                                    // defines sensor as an integer & maps it to an 8-bit value to be printed
  unsigned int sensorValue = analogRead(sensorPin);   // Read the analog value from sensor
  unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data
  return outputValue;                                 // Return analog value
}

// 2.) CONTROL LED BASED ON GAS LEVEL (ANALOG READING FROM MQ2)
void LED_control() {                                   // controls LED color based on danger level
  if (readSensor() <= 40) {                           // if reading <= 40, display green light
    analogWrite(blueLED, 0);
    analogWrite(redLED, 0);
    analogWrite(greenLED, 255);
  }
  if (readSensor() > 40 && readSensor() < 90) {      // if reading btw 40 and 90, display yellow light
    analogWrite(greenLED, 110);
    analogWrite(blueLED, 0);
    analogWrite(redLED, 255);
  }
  if (readSensor() >= 90) {                           // if reading >= 90, display red light
    analogWrite(greenLED, 0);
    analogWrite(blueLED, 0);
    analogWrite(redLED, 255);
  }
}

// 3.) CONTROL PIEZOSPEAKER BASED ON GAS LEVEL (ANALOG READING FROM MQ2)
void Piezo_control() {    // controls piezospeaker based on danger level; !! NO code for <= 40; speaker is automatically off
  if (readSensor() > 40 && readSensor() < 90) {       // if reading btw 40 and 90, play alarm sequence 1
    alarm1();
  }
  if (readSensor() >= 90) {                            // if reading >= 90, play alarm sequence 2
    alarm2();
  }
}

// 4.) AUDIO ALARM FUNCTION FOR MID LPG DETECTION
void alarm1() {         // Function to play speaker every 5 seconds @ 1000Hz
  if (millis() - periodstart1 >= period1) {            // if time since code start (millis) - periodstart1 >= 5 seconds
    periodstart1 += period1;                            // set periodstart1 = periodstart1 + period1 (defined variable)
    tone(13, 1000, alarmON1);                           // play tone at 1000Hz for 0.25 seconds (defined earlier)
    Transmitter2();
  }
}

// 5.) AUDIO ALARM FUNCTION FOR HIGH LPG DETECTION
void alarm2() {         // Function to play speaker every second @ 1000Hz
  if (millis() - periodstart2 >= period2) {           // if time since code start (millis) - periodstart2 >= 2 seconds
    periodstart2 += period2;                            // set periodstart2 = periodstart2 + period2 (defined variable)
    tone(13, 1000, alarmON2);                           // play tone at 1000Hz for 1 second (defined earlier)
    Transmitter3();
  }
}

void Transmitter1() { 
  const char *msg = "Good gas readings!";
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  Serial.println("Good gas readings!");
  delay(1000);
}

void Transmitter2() {
  const char *msg = "Mid gas readings!";
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  Serial.println("Mid gas readings!");
  delay(1000); 
}

void Transmitter3() {
  const char *msg = "Bad gas readings!";
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  Serial.println("Bad gas readings!");
  delay(1000); 
}

