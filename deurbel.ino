/*
Deurbel sketch..
*/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;


// Pin Configuration:
const int Deurbel = 2;  // the number of the pushbutton pin
const int Switch1 = 3;	// double switch left
const int Switch2 = 4; //  double switch right

// Variables will change:
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(Deurbel, INPUT);
  pinMode(Switch1, INPUT);
  pinMode(Switch2, INPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  myDFPlayer.volume(25);  //Set volume value (0~30).
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  //myDFPlayer.next();
}
  

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(Deurbel);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
    
    
		if(digitalRead(Switch1) == HIGH && digitalRead(Switch2) == HIGH){
		  myDFPlayer.play(1);
		}
		if(digitalRead(Switch1) == LOW && digitalRead(Switch2) == HIGH){
		  myDFPlayer.play(2);
		}
		if(digitalRead(Switch1) == HIGH && digitalRead(Switch2) == LOW){
		  myDFPlayer.play(3);
		}
		if(digitalRead(Switch1) == LOW && digitalRead(Switch2) == LOW){
		  myDFPlayer.play(4);
		}
    
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
