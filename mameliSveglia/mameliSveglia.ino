#include "shieldSetup.h"
#include "mameli.h"

int sveglio;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(LIGHTSENSOR, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  sveglio = 0;
}

long sonarDistance() {
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  return pulseIn(ECHOPIN, HIGH) / 58.2;
}

void playMameli() {
  for(int i=0; i<63; i++) {
    tone(BUZZER, mameli[i][0]);
    delay(mameli[i][1]*500);
    noTone(BUZZER);
    
    if(sonarDistance() < 5) {
      sveglio = 1;
      return;
    }
    delay(30);
  }
}

void loop() {
  if(analogRead(LIGHTSENSOR) > 100) {
    if(!sveglio) { playMameli(); }
  } else { sveglio = 0; }
}
