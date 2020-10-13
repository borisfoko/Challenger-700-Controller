/*
 Example: Control a WTV020-SD-16P module to play voices from an Arduino board.
 Created by ELECTRONOOBS, oct 14, 2016.
 */

#include <Wtv020sd16p.h>

// Lautsprechen Pins 5, 6, 9, 10
#define RESETPIN 5  // pin nummer für "reset". Grün
#define CLOCKPIN 6  // pin nummer für "clock". Blau
#define DATAPIN 9  // pin nummer für die "data". Gelb
#define BUSYPIN 10  // pin nummer für "busy". Orange

#define ZUNPIN 2 
#define MOTORPIN 3  
/*
Create an instance of the Wtv020sd16p class.
 1st parameter: Reset pin number.
 2nd parameter: Clock pin number.
 3rd parameter: Data pin number.
 4th parameter: Busy pin number.
*/
 
Wtv020sd16p AudioPlayer(RESETPIN,CLOCKPIN,DATAPIN,BUSYPIN);
// Audio Funktion Inizialisierung
bool MOTOR_ON = false;
bool ZUN_ON = false;

void setup() {
  //Initializes the module.
  AudioPlayer.reset();
  Serial.begin(9600);
  pinMode(ZUNPIN, INPUT_PULLUP);
  pinMode(MOTORPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ZUNPIN), zunChange, CHANGE );
  attachInterrupt(digitalPinToInterrupt(MOTORPIN), motorChange, CHANGE );
}

void loop() {
  playMotorSong();
  if  (MOTOR_ON) {
    playMotorSong();
  }
  else if (ZUN_ON){
    playZundSong();
  }
}

void motorChange(){
  Serial.println("Motor State Change");
  if (digitalRead(MOTORPIN) == HIGH){
    MOTOR_ON = true;
  }else{
    MOTOR_ON = false;
  }
  Serial.println(MOTOR_ON);
}

void zunChange(){
  Serial.println("Zündung State Change");
  if (digitalRead(ZUNPIN) == HIGH){
    ZUN_ON = true;
  }else{
    ZUN_ON = false;
  }
  Serial.println(ZUN_ON);
}


void playZundSong(){
  Serial.println("Song 1 ist playing");
  playSong(1, 5000);
}

void playMotorSong(){
  Serial.println("Song 7 ist playing");
  playSong(7, 5000);
}

void playSong(int songNummer, int duration){
  AudioPlayer.asyncPlayVoice(songNummer);
  delay(duration);
  AudioPlayer.stopVoice();
}
