#define DEBUG true  // turn debug message on or off in serial

void setup()
{
  Serial3.begin(115200);  // using serial 1 if you are using arduino LEO
  Serial.begin(9600);
  
  while (!Serial3) {
  ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  delay(200);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  //sendData("AT+CWSAP=\"ESP8266_HiSERV\",\"ESP8266_HiSERV\",\"1\",\"4\"\r\n",1000,DEBUG);
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address //192.168.4.1
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}

void loop()
{
  if(Serial3.available()) // check if the esp is sending a message
  {
    Serial.println("A");
    if(Serial3.find("+IPD,"))
    {
      Serial.println("IP");
      delay(1000); // wait for the serial buffer to fill up (read all the serial data)
      // get the connection id so that we can then disconnect
      int connectionId = Serial3.read()-48; // subtract 48 because the read() function returns
      // the ASCII decimal value and 0 (the first decimal number) starts at 48
      Serial.println("IP= " +connectionId);
      // on your browser type http://192.168.4.1/?pin=13
      
      Serial3.find("pin="); // advance cursor to "pin="
      
      // get 3 digits
      int pinNumber = (Serial3.read()-48)*100; //
      pinNumber += (Serial3.read()-48)*10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
      pinNumber += (Serial3.read()-48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
      Serial.println("Pin Number" + pinNumber);
      //digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin
      
      // generate web page
      String webpage = String(pinNumber);
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
  }
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

