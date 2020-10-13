// < ---  ArduinoMega Mainboard Controller Programm --- >
// < --- von Boris Foko Kouti --- 

//Servos Bibliothek include
#include <Servo.h>

// Debug modus aus
#define DEBUG false

// Lenkung (Servos) Pin
#define ServosPin 3

// DC Motors Pins 8, 9, 10, 11
// Bei 8 & 10 auf HIGH und 9 & 11 auf LOW geht es vorwärts
// Bei 8 & 10 auf LOW und 9 & 11 auf HIGH geht es rückwärts
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define AEN1 4
#define AEN2 5

// Beleuchtung (LED) Pins 

// Front Scheinwerfer
#define FScheinWLED1 25
#define FScheinWLED2 26
// Sirene 
#define SireneLED1 24
#define SireneLED2 22

// Back Scheinwerfer
#define BScheinWLED1 23
#define BScheinWLED2 27
bool SireneOn = false;
bool FScheinWStatus = false;

// Trackunit Pins Output
#define BetriebsstundenPin 51
#define ZuendungPin 50
#define Batterieverbrauch 52
#define LastBSTPin 53

#define ZuendungSongPin 30
#define MotorSongPin 31

// Trackunit Pins Input
int SchluesselZugangPin = A8;
bool SchluesselZugangStatus = false;
bool BetriebsstundenStatus = false;
bool LastBSTStatus = false;
bool ByPassPin = false;
bool ZuendungOn = false;

// Servo Kontrolle Funktion Inizialisierung
Servo ServoLenkung;

void setup() {
  //Init Lautsprecher Modul
  //AudioPlayer.reset();
  // Init Lenkung Servo
  ServoLenkung.attach(ServosPin);
  ServoLenkungNull();
  // Init LED Pins
  pinMode(FScheinWLED1,OUTPUT);
  pinMode(FScheinWLED2,OUTPUT);
  pinMode(BScheinWLED1,OUTPUT);
  pinMode(BScheinWLED2,OUTPUT);
  pinMode(SireneLED1,OUTPUT);
  pinMode(SireneLED2,OUTPUT);

  digitalWrite(FScheinWLED1,HIGH);
  digitalWrite(FScheinWLED2,HIGH);
  digitalWrite(SireneLED1,HIGH);
  digitalWrite(SireneLED2,HIGH);
  delay(300);
  digitalWrite(BScheinWLED1,HIGH);
  digitalWrite(BScheinWLED2,HIGH);
  
  digitalWrite(FScheinWLED1,LOW);
  digitalWrite(FScheinWLED2,LOW);
  digitalWrite(SireneLED1,LOW);
  digitalWrite(SireneLED2,LOW);
  delay(300);
  digitalWrite(BScheinWLED1,LOW);
  digitalWrite(BScheinWLED2,LOW);

  //init Song interrupt Pins
  pinMode(ZuendungSongPin, OUTPUT);
  pinMode(MotorSongPin, OUTPUT);
  digitalWrite(ZuendungSongPin, LOW);
  digitalWrite(MotorSongPin, LOW);
  
  // DC Motors Init
  pinMode(AEN1, OUTPUT);
  pinMode(AEN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(AEN1, 150);
  analogWrite(AEN2, 150);
  
  //Trackunit Dual Id Steuerung
  pinMode(BetriebsstundenPin, OUTPUT);
  pinMode(ZuendungPin, OUTPUT);
  pinMode(Batterieverbrauch, OUTPUT);
  pinMode(LastBSTPin, OUTPUT);
  digitalWrite(BetriebsstundenPin, LOW);
  digitalWrite(ZuendungPin, LOW);
  digitalWrite(Batterieverbrauch, LOW);
  digitalWrite(LastBSTPin, LOW);
  pinMode(48, OUTPUT);
  digitalWrite(48, HIGH);
  int value = 0;
  value = analogRead(SchluesselZugangPin);
  Serial.print("Value = ");
  Serial.println(value);
  // Init Serials für die Kommunikation
  Serial3.begin(115200);  // using serial 1 if you are using arduino LEO
  Serial.begin(9600);
  
  while (!Serial3) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  delay(200);
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  Serial.println("Reseted");
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  Serial.println("Configured");
  sendData("AT+CWSAP=\"HiSERV_CHAMP\",\"HiSERV_CHAMP\",5,3\r\n",1000,DEBUG);
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address //192.168.4.1
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
  Serial.println("Server on");
}

void loop() {
  if(Serial3.available()) // prüf, ob eine Nachricht erhalten ist
  {
    if(Serial3.find("+IPD,"))
    {
      Serial3.find("?");
      String msg;
      msg = Serial3.readStringUntil(' ');
      //Serial.println("Message: " + msg);
      String command1 = msg.substring(0, 5);
      String command2 = msg.substring(6); 
      int value = 0;
      value = analogRead(SchluesselZugangPin);             
      if (DEBUG) 
      {
        Serial.println(command1);//Must print "robot"
        Serial.println(command2);//Must print "BYP" or "TES" or "ZUN" or "MOR" or "LAB" or "FWD" or "FWL" or "FWR" or "REV" or "REL" or "RER" or "STP" or "SWF" or "SIF"
        Serial.print("Value = ");
        Serial.println(value);
      }
      
      if(command2 == "TES"){
        //Test Connection
        Serial.println("Test");
        sirene();
        //sendMessage(1, 0);
      }
      if (command2 == "BYP"){
        if (!ByPassPin) {
           //ByPass
           ByPassPin = true;
           Serial.println("ByPass ON");
		       //sendMessage(1, 0);
        }else {
           //ByPass
           ByPassPin = false;
           Serial.println("ByPass OFF");
		       //sendMessage(2, 0);
        }  
      }
      if (value > 1000 && value < 1040){
            SchluesselZugangStatus = false;
      } 
      else if (value > 340 && value < 450) {
        SchluesselZugangStatus = true;
        Serial.println("KeyPad freigeschaltet");
      }
      if (ByPassPin || ZuendungOn || SchluesselZugangStatus){
        if (command2 == "ZUN"){
           digitalWrite(SireneLED1, HIGH);
           delay(200);
           digitalWrite(SireneLED1, LOW);
          if (!ZuendungOn){
             ZuendungOn = true;
             digitalWrite(ZuendungPin, HIGH);
             digitalWrite(ZuendungSongPin, HIGH);
             digitalWrite(MotorSongPin, LOW);
             Serial.println("Zuendung On");
			       //sendMessage(1, 0);
          }
          else {
            ZuendungOn = false;
            digitalWrite(ZuendungPin, LOW);
            digitalWrite(BetriebsstundenPin, LOW);
            digitalWrite(ZuendungSongPin, LOW);
            digitalWrite(MotorSongPin, LOW);
            Serial.println("Zuendung Off");
			      //sendMessage(2, 0);
          }
        }
        if (ZuendungOn){
           if (command2 == "MOR"){
              digitalWrite(SireneLED2, HIGH);
              delay(200);
              digitalWrite(SireneLED2, LOW);
              if (!BetriebsstundenStatus){
                digitalWrite(BetriebsstundenPin, HIGH);
                BetriebsstundenStatus = true;
                digitalWrite(ZuendungSongPin, LOW);
                digitalWrite(MotorSongPin, HIGH);
				        //sendMessage(1, 0);
              }
              else {
                digitalWrite(BetriebsstundenPin, LOW);
                BetriebsstundenStatus = false;
				        //sendMessage(2, 0);
              }      
           }
           if (command2 == "LAB"){
              SireneOn = !SireneOn; 
              if (!LastBSTStatus){
                digitalWrite(LastBSTPin, HIGH);
                LastBSTStatus = true;
				        //sendMessage(1, 0);
              }
              else {
                digitalWrite(LastBSTPin, LOW);
                LastBSTStatus = false;
				        //sendMessage(2, 0);
              }      
           }
           if (BetriebsstundenStatus){
              if (command2 == "STP"){
                 stoprobot();
              } 
              else if (command2 == "FWD"){
              forward();
              }
              else if (command2 == "FWR"){
                 rightForward();
              }
              else if (command2 == "LEF"){
                ServoLenkungLinks();
              }
              else if (command2 == "RIG"){
                ServoLenkungRechts();
              }
              else if (command2 == "FWL"){
                 leftForward();
              }
              else if (command2 == "REV"){
                 reverse();
              }
              else if (command2 == "RER"){
                 rightReverse();
              }
              else if (command2 == "REL"){
                 leftReverse();
              }
            }
         }
         if (command2 == "SWF"){
          if (!FScheinWStatus){
            //Scheinwerfer Vorne an
            digitalWrite(FScheinWLED1, HIGH);
            digitalWrite(FScheinWLED2, HIGH);
            FScheinWStatus = true;
          }else{
            FScheinWStatus = false;
            //Scheinwerfer Vorne aus
            digitalWrite(FScheinWLED1, LOW);
            digitalWrite(FScheinWLED2, LOW);
          }
         }
         if (command2 == "SIF"){
            //Sirene an/aus
            SireneOn = !SireneOn; 
         }
         if (SireneOn){
            sirene();
         } 
        }
      }
    }
    if (SireneOn){
       sirene();
    }
}

void _forward()
{
  //SONG_ON = true;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void forward()
{
  digitalWrite(ZuendungSongPin, LOW);
  digitalWrite(MotorSongPin, HIGH);
  ServoLenkungNull();
  _forward();
}

void _reverse()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void reverse()
{
  digitalWrite(ZuendungSongPin, LOW);
  digitalWrite(MotorSongPin, HIGH);
  ServoLenkungNull();
  _reverse();
}

void leftForward()
{
  digitalWrite(ZuendungSongPin, LOW);
  digitalWrite(MotorSongPin, HIGH);
  ServoLenkungLinks();
  _forward();
}

void rightForward()
{
  digitalWrite(ZuendungSongPin, LOW);
  digitalWrite(MotorSongPin, HIGH);
  ServoLenkungRechts();
  _forward();
}

void leftReverse()
{
  digitalWrite(ZuendungSongPin, LOW);
  digitalWrite(MotorSongPin, HIGH);
  ServoLenkungLinks();
  _reverse();
}

void rightReverse()
{
  digitalWrite(ZuendungSongPin, LOW);
  digitalWrite(MotorSongPin, HIGH);
  ServoLenkungRechts();
  _reverse();
}

void stoprobot()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void sirene(){
  digitalWrite(SireneLED1, HIGH);
  digitalWrite(SireneLED2, HIGH);
  //digitalWrite(BScheinWLED1, HIGH);
  //digitalWrite(BScheinWLED2, HIGH);
  delay(200);
  digitalWrite(SireneLED1, LOW);
  digitalWrite(SireneLED2, LOW);
  //digitalWrite(BScheinWLED1, LOW);
  //digitalWrite(BScheinWLED2, LOW);
  delay(100);
}

/*
 * Send Any Message
 */
void sendMessage(int message, int connectionId){
  // generate web page
  String webpage = String(message);
  String cipSend = "AT+CIPSEND=";
  cipSend += connectionId;
  cipSend += ",";
  cipSend +=webpage.length();
  cipSend +="\r\n";
  sendData(cipSend,1000,DEBUG);
  sendData(webpage,1000,DEBUG);
  
  // make close command
  String closeCommand = "AT+CIPCLOSE=";
  closeCommand+=connectionId; // append connection id
  closeCommand+="\r\n";
  
  sendData(closeCommand,1000,DEBUG); // close connection
}
 

/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  
  Serial3.print(command); // send the read character to the esp8266
  
  long int time = millis();
  
  while( (time+timeout) > millis())
  {
    while(Serial3.available())
    {
    
    // The esp has data so display its output to the serial window
    char c = Serial3.read(); // read the next character.
    response+=c;
    }
  }
  
  if(debug)
  {
    Serial.print(response);
  }
  
  return response;
}

void ServoPosition(){
  Serial.print("Servos Position: ");
  Serial.println(ServoLenkung.read());
}

void ServoLenkungRechts(){
  int currentPos = ServoLenkung.read();
  while(currentPos > 25) {
    currentPos = currentPos - 5;
    ServoLenkung.write(currentPos);
    delay(50);
  }
}

void ServoLenkungLinks(){
  int currentPos = ServoLenkung.read();
  while(currentPos < 80) {
    currentPos = currentPos + 5;
    ServoLenkung.write(currentPos);
    delay(50);
  }
  Serial.println("Links");
}

void ServoLenkungNull(){
  int currentPos = ServoLenkung.read();
  if (currentPos != 45){
    if (currentPos > 45){
      while(currentPos > 45) {
        currentPos = currentPos - 5;
        ServoLenkung.write(currentPos);
        delay(50);
      }
    } else {
      while(currentPos < 45) {
        currentPos = currentPos + 5;
        ServoLenkung.write(currentPos);
        delay(50);
      }
    }
   }
}
