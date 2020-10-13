#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "HiSERV_CHAMP"
#define APPSK  "HiSERV_CHAMP"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send(200, "text/html", "<p>Du bist mit dem Champ 700 verbunden</p>");
}

void handleByPassAn() {
  server.send(200, "text/html", "<p>ByPass an</p>");
  Serial.write("?robot=BYN ");
}

void handleByPassAus() {
  server.send(200, "text/html", "<p>ByPass aus</p>");
  Serial.write("?robot=BYS ");
}

void handleZuendungAn() {
  server.send(200, "text/html", "<p>Zundung an</p>");
  Serial.write("?robot=ZUN ");
}

void handleZuendungAus() {
  server.send(200, "text/html", "<p>Zundung aus</p>");
  Serial.write("?robot=ZUS ");
}

void handleMotorAn() {
  server.send(200, "text/html", "<p>Motor an</p>");
  Serial.write("?robot=MON ");
}

void handleMotorAus() {
  server.send(200, "text/html", "<p>Motor aus</p>");
  Serial.write("?robot=MOS ");
}

void handleLastBetriebAn() {
  server.send(200, "text/html", "<p>Lastbetrieb an</p>");
  Serial.write("?robot=LAN ");
}

void handleLastBetriebAus() {
  server.send(200, "text/html", "<p>Lastbetrieb aus</p>");
  Serial.write("?robot=LAS ");
}

void handleForward() {
  server.send(200, "text/html", "<p>Nach vorne</p>");
  Serial.write("?robot=FWD ");
}

void handleForwardRight() {
  server.send(200, "text/html", "<p>Nach vorne rechts</p>");
  Serial.write("?robot=FWR ");
}

void handleForwardLeft() {
  server.send(200, "text/html", "<p>Nach vorne links</p>");
  Serial.write("?robot=FWL ");
}

void handleReverse() {
  server.send(200, "text/html", "<p>Zurueck</p>");
  Serial.write("?robot=REV ");
}

void handleReverseRecht() {
  server.send(200, "text/html", "<p>Zurueck rechts</p>");
  Serial.write("?robot=RER ");
}

void handleReverseLink() {
  server.send(200, "text/html", "<p>Zurueck links</p>");
  Serial.write("?robot=REL ");
}

void handleStop() {
  server.send(200, "text/html", "<p>Das Fahrzeug wird heruntergefahren</p>");
  Serial.write("?robot=STP ");
}

void handleFrontLigthAn() {
  server.send(200, "text/html", "<p>Scheinwerfer vorne an</p>");
  Serial.write("?robot=SWN");
}

void handleFrontLigthAus() {
  server.send(200, "text/html", "<p>Scheinwerfer vorne aus</p>");
  Serial.write("?robot=SWS ");
}

void handleSireneAn() {
  server.send(200, "text/html", "<p>Sirene an</p>");
  Serial.write("?robot=SIN ");
}

void handleSireneAus() {
  server.send(200, "text/html", "<p>Sirene aus</p>");
  Serial.write("?robot=SIS ");
}

void setup()
{
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  Serial.print("Setting soft-AP ... ");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/BYN", handleByPassAn);
  server.on("/BYS", handleByPassAus);
  server.on("/ZUN", handleZuendungAn);
  server.on("/ZUS", handleZuendungAus);
  server.on("/MON", handleMotorAn);
  server.on("/MOS", handleMotorAus);
  server.on("/LAN", handleLastBetriebAn);
  server.on("/LAS", handleLastBetriebAus);
  server.on("/FWD", handleForward);
  server.on("/FWR", handleForwardRight);
  server.on("/FWL", handleForwardLeft);
  server.on("/REV", handleReverse);
  server.on("/REL", handleReverseLink);
  server.on("/RER", handleReverseRecht);
  server.on("/SWN", handleFrontLigthAn);
  server.on("/SWS", handleFrontLigthAus);
  server.on("/SIN", handleSireneAn);
  server.on("/SIS", handleSireneAus);
  server.on("/STP", handleStop);
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}
