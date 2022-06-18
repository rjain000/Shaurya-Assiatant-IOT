#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

char ssid1[] = "Computer"; // WiFi 1
char password1[] = "davasr@123";

char ssid2[] = "ICT@123"; // WiFi 2
char password2[] = "dav32545";

char ssid3[] = "_Rjain_"; // WiFi 3
char password3[] = "RJain?00";

char ssid4[] = "NULL"; // WiFi 4
char password4[] = "NULL";

IPAddress staticIP709_100(192,168,1,220);
IPAddress gateway709_100(192,168,1,1);
IPAddress subnet709_100(255,255,255,0);

ESP8266WebServer server(80);

uint8_t PLUG1pin = D1;
bool PLUG1status = HIGH;
bool plug1html = false;

uint8_t PLUG2pin = D2;
bool PLUG2status = HIGH;
bool plug2html = false;

void setup() {
  Serial.begin(9600);
  pinMode(PLUG1pin, OUTPUT);
  pinMode(PLUG2pin, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    myNetwork();
  }
  Serial.println("WiFi connected..!");
  
  WiFi.config(staticIP709_100, gateway709_100, subnet709_100);
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  
  server.on("/plug1on", handle_plug1on);
  server.on("/plug1off", handle_plug1off);

  server.on("/plug2on", handle_plug2on);
  server.on("/plug2off", handle_plug2off);

  server.on("/plug1status", handle_plug1status);
  server.on("/plug2status", handle_plug2status);
  
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}


void myNetwork() {
  int flag = 1;
  Serial.println("Searching Wifi......");
  int network = WiFi.scanNetworks();
  Serial.print("Total network found: ");
  Serial.println(network);
  for (int i = 0 ; i < network; i++) {
    switch (flag){
      case 1: 
        flag = 2;
        if (WiFi.SSID(i) == ssid1) {
          WiFi.begin(ssid1, password1);
          Serial.println("Wifi Found");
          delay(2000);
          Serial.print("Connecting with ");
          Serial.print(ssid1);
          Serial.println(" Please Wait");
          delay(8000);
          break;
        }
        case 2:
         flag = 3;
         if (WiFi.SSID(i) == ssid2) {
          WiFi.begin(ssid2, password2);
          Serial.println("Wifi Found");
          delay(2000);
          Serial.print("Connecting with ");
          Serial.print(ssid2);
          Serial.println(" Please Wait");
          delay(8000);
          break;
        }
       case 3:
        flag = 4;
         if (WiFi.SSID(i) == ssid3) {
          WiFi.begin(ssid3, password3);
          Serial.println("Wifi Found");
          delay(2000);
          Serial.print("Connecting with ");
          Serial.print(ssid3);
          Serial.println(" Please Wait");
          delay(8000);
          break;
        }
        case 4:
        flag = 1;
         if (WiFi.SSID(i) == ssid4) {
          WiFi.begin(ssid4, password4);
          Serial.println("Wifi Found");
          delay(2000);
          Serial.print("Connecting with ");
          Serial.print(ssid4);
          Serial.println(" Please Wait");
          delay(8000);
          break;
        }
    }
  }
}

void loop() {
  
  server.handleClient();
  if(PLUG1status)
    digitalWrite(PLUG1pin, HIGH);
  else
    digitalWrite(PLUG1pin, LOW);
  
  if(PLUG2status)
    digitalWrite(PLUG2pin, HIGH);
  else
    digitalWrite(PLUG2pin, LOW);
}

void handle_OnConnect() {  
  
  if(PLUG1status == LOW && PLUG2status == LOW){
    plug1html=true;
    plug2html=true;
  }
  else if(PLUG1status == LOW && PLUG2status == HIGH){
    plug1html=true;
    plug2html=false;
  }
  else if(PLUG1status == HIGH && PLUG2status == LOW){
    plug1html=false;
    plug2html=true;
  }
  else{
    plug1html=false;
    plug2html=false;
  }
  
  server.send(200, "text/html", SendHTML(plug1html,plug2html));
}

void handle_plug1status(){
  if(PLUG1status == HIGH)
    server.send(201, "text/html", SendHTML(plug1html,plug2html));
  else
    server.send(202, "text/html", SendHTML(plug1html,plug2html));
}

void handle_plug2status(){
  if(PLUG2status == HIGH)
    server.send(201, "text/html", SendHTML(plug1html,plug2html));
  else
    server.send(202, "text/html", SendHTML(plug1html,plug2html));
}

void handle_plug1on() {
  PLUG1status = LOW;
  plug1html=true;
  server.send(200, "text/html", SendHTML(plug1html,plug2html)); 
}

void handle_plug1off() {
  PLUG1status = HIGH;
  plug1html = false;
  server.send(200, "text/html", SendHTML(plug1html,plug2html)); 
}

void handle_plug2on() {
  PLUG2status = LOW;
  plug2html = true;
  server.send(200, "text/html", SendHTML(plug1html,plug2html)); 
}

void handle_plug2off() {
  PLUG2status = HIGH;
  plug2html = false;
  server.send(200, "text/html", SendHTML(plug1html,plug2html)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t plug1h, uint8_t plug2h){
  String ptr = "<!DOCTYPE html>\n";
  ptr +="<html align=\"center\">\n";
  ptr +="<head>\n";
  ptr +="<meta charset=\"UTF-8\">\n";
  ptr +="<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
  ptr +="<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  ptr +="<title>PLUG Control</title>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1 style=\"color: rgb(56, 42, 253);\">Smart Plug</h1>\n";
  ptr +="<h3 style=\"color: red;\">Click the switch button to make the Plug ON and OFF..</h3>\n";
  ptr +="<form method=\"post\">\n";
  if(plug1h)
  ptr +="<input type=\"button\" value=\"Light OFF\" onclick=\"window.location.href='/plug1off'\" style=\"border: 2px solid red; background-color: yellow; padding: 5px; margin: 10px;\">\n";
  else
  ptr +="<input type=\"button\" value=\"Light ON\" onclick=\"window.location.href='/plug1on'\" style=\"border: 2px solid cyan; background-color: white; padding: 5px; margin: 10px;\">\n";
  if(plug2h)
  ptr +="<input type=\"button\" value=\"Fan OFF\" onclick=\"window.location.href='/plug2off'\" style=\"border: 2px solid red; background-color: yellow; padding: 5px; margin: 10px;\">\n";
  else
  ptr +="<input type=\"button\" value=\"Fan ON\" onclick=\"window.location.href='/plug2on'\" style=\"border: 2px solid cyan; background-color: white; padding: 5px; margin: 10px;\">\n";
  ptr +="<br>\n";
  ptr +="<input type=\"button\" value=\"Refresh\" onclick=\"window.location.href='/'\" style=\"border: 2px dotted wheat; background-color: grey; color: white; padding: 5px; margin: 10px;\">\n";
  ptr +="</form>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
