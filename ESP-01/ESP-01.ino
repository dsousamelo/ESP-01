
#include <SoftwareSerial.h>

const byte rxPin = 2;
const byte txPin = 3;

SoftwareSerial ESP8266 (rxPin, txPin);

unsigned long lastTimeMillis = 0;

  String contentTemp = "{\"value\":666}";

void setup() {
  Serial.begin(115200);   
  ESP8266.begin(115200);
  ESP8266.println("AT+RST");  
  ESP8266.println("AT+CWJAP=\"TP-LINK_8DDDAE\",\"labiotm06\" ");
  delay(2000);
}

void printResponse() {
  while (ESP8266.available()) {
    Serial.println(ESP8266.readStringUntil('\n')); 
  }
}

void loop() {

  if (millis() - lastTimeMillis > 30000) {
    lastTimeMillis = millis();

    ESP8266.println("AT+CIPMUX=1");
    delay(1000);
    printResponse();

    ESP8266.println("AT+CIPSTART=4,\"TCP\",\"172.18.9.100\",3000");
    delay(1000);
    printResponse();

    String cmd = "GET /temperatures/1 HTTP/1.1";
    String cmd2 = "PUT /temperatures/1 HTTP/1.1\r\nHost:172.18.9.100:3000\r\nUser-Agent: Arduino/1.0\r\nAccept: application/json\r\nContent-Length:"+(String)contentTemp.length()+"\r\nContent-Type: application/json\r\nConnection: close\r\n\n"+contentTemp;
    ESP8266.println("AT+CIPSEND=4," + String(cmd2.length()+4));
    delay(1000);
    Serial.println(cmd2);

    ESP8266.println("PUT /temperatures/1 HTTP/1.1");
    ESP8266.println("Host:172.18.9.100:3000");
    ESP8266.println("User-Agent: Arduino/1.0");
    ESP8266.println("Accept: application/json");
    ESP8266.print("Content-Length:");
    ESP8266.println(contentTemp.length());
    ESP8266.println("Content-Type: application/json");
    ESP8266.println("Connection: close");
    ESP8266.println("");
    ESP8266.println(contentTemp);
    

    
    delay(1000);
    ESP8266.println(""); 
  }

  if (ESP8266.available()) {
    Serial.write(ESP8266.read());
  }

}
