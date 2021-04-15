#include "Volume.h"

const int trigPin = 2;
const int echoPin = 4;
const int trigPin2 = 12;
const int echoPin2 = 13;

const int arrayLength = 20;
float tones[arrayLength];
float volumes[arrayLength];


Volume vol;

void setup() {
  vol.begin();
  vol.setMasterVolume(0.2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(115200);
}

void loop() {
  float distance1 = distance(trigPin, echoPin); // eerste ultrasoon is om de toonhoogte te veranderen
  float distance2 = distance(trigPin2, echoPin2); // tweede ultrasoon is om de volume te veranderen
  float Tone = map(distance1, 5, 20, 40, 3000); // Map de toonhoogte
  float Volume = map(distance2, 5, 20, 0, 255); // Map de volume
  Tone = constrain(Tone, 40, 3000); // Alle waardes zit in een bepaalde bereik
  Volume = constrain(Volume, 0, 255);

  for(int i = 0; i < arrayLength - 1; i++) {
    tones[i] = tones[i + 1];
  }
  tones[arrayLength - 1] = Tone;

  for(int i = 0; i < arrayLength - 1; i++) {
    volumes[i] = volumes[i + 1];
  }
  volumes[arrayLength - 1] = Volume;

  float total = 0;
  for(int i = 0; i < arrayLength; i++) {
    total += tones[i];
  }
  float averageTone = total / arrayLength; // De gemmidelde toon berekenen
  total = 0;
  for(int i = 0; i < arrayLength; i++) {
    total += volumes[i];
  }
  float averageVolume = total / arrayLength; // De gemmidelde volume berekenen

  Serial.print("Tone: ");
  Serial.println(averageTone);
  Serial.print("Volume: ");
  Serial.println(averageVolume);
  
  vol.tone(averageTone, averageVolume);
}

float distance(int trigger, int echo) {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  float duration = pulseIn(echo, HIGH);

  float distance = duration * 0.017;

//  Serial.print("afstand = ");
//  Serial.println(distance);
//  Serial.print("duration = ");
//  Serial.println(duration);

  return distance;
}
