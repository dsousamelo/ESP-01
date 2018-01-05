


#include <SoftwareSerial.h>
#include <EventManager.h>
#include <MsTimer2.h>
#include <DHT_U.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>

#define DHTPIN A0
#define DHTTYPE DHT11

  const byte rxPin = 2;
  const byte txPin = 3;
  

  SoftwareSerial ESP8266 (rxPin, txPin);
  DHT dht(DHTPIN, DHTTYPE);
  EventManager gEM;

  int ldrPin = 1; //LDR no pino analógico 1
  int ldrValor = 0; //Valor lido do LDR
  int temperature;
  String contentI = "{\"value\":";
  String contentI2 = "{\"state\":";


void printResponse() {
  while (ESP8266.available()) {
    Serial.println(ESP8266.readStringUntil('\n')); 
  }
}

void setup() {
  
    Serial.begin(115200);   
    
    ESP8266.begin(115200);    
    ESP8266.println("AT+RST"); 
    ESP8266.println("AT+CWJAP=\"TP-LINK_8DDDAE\",\"labiotm06\" ");  
    ESP8266.println("AT+CWMODE=3"); 
    
    /*MsTimer2::set(10000, updateTemp ); 
    MsTimer2::start();*/

    dht.begin();

    delay(2000);
  
}



void loop(){
       
   //updateTemp();
   //delay(100);
   updateDoor();
   delay(100);
   updateLu();
   
} 

void updateTemp(){ 
    
    Serial.println("//////////////////////TEMPERATURA//////////////////////////");

        temperature = dht.readTemperature();   

        Serial.println(temperature);           
        String str = String(temperature);  
        String  contentTemp = contentI+str+"}";          
    
        ESP8266.println("AT+CIPMUX=1");
        delay(100);
   
    
        ESP8266.println("AT+CIPSTART=4,\"TCP\",\"172.18.9.100\",3000");
        delay(100);
        
        String cmd2 = "PUT /temperatures/1 HTTP/1.1\r\nHost:172.18.9.100:3000\r\nUser-Agent: Arduino/1.0\r\nAccept: application/json\r\nContent-Length:"+(String)contentTemp.length()+"\r\nContent-Type: application/json\r\nConnection: close\r\n\n"+contentTemp;
        ESP8266.println("AT+CIPSEND=4," + String(cmd2.length()+4));   
        delay(100); 
   
        
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
        
        ///////////////////////////////////////////////////////////// 
        
        delay(100);  
        ESP8266.println("");
       
   
}

void updateLu(){

    Serial.println("//////////////////////LUZ//////////////////////////");
  
    ldrValor = analogRead(ldrPin);

    Serial.println("VALOR LDR:"+ldrValor);
  
    String contentLu;
    
    if(ldrValor>=1020){  
       contentLu = contentI2+"false}";
    
    }
    else{
      contentLu = contentI2+"true}";
    }

    ESP8266.println("AT+CIPMUX=1");
    delay(100);
    

    ESP8266.println("AT+CIPSTART=4,\"TCP\",\"172.18.9.100\",3000");
    delay(100);
  

    String cmd2 = "PUT /lights/1 HTTP/1.1\r\nHost:172.18.9.100:3000\r\nUser-Agent: Arduino/1.0\r\nAccept: application/json\r\nContent-Length:"+(String)contentLu.length()+"\r\nContent-Type: application/json\r\nConnection: close\r\n\n"+contentLu;
    ESP8266.println("AT+CIPSEND=4," + String(cmd2.length()+4));
    delay(100);
 
  
    Serial.println(cmd2);
    
    ESP8266.println("PUT /lights/1 HTTP/1.1");
    ESP8266.println("Host:172.18.9.100:3000");    
    ESP8266.println("User-Agent: Arduino/1.0");
    ESP8266.println("Accept: application/json");
    ESP8266.print("Content-Length: ");
    ESP8266.println(contentLu.length());    
    ESP8266.println("Content-Type: application/json");
    ESP8266.println("Connection: close");
    ESP8266.println();
    ESP8266.println(contentLu); 
    ///////////////////////////////////////////////////////////////

     
    delay(100);  
    ESP8266.println("");
    
  
}


void updateDoor(){

    Serial.println("//////////////////////PORTA//////////////////////////");
  
    int doorState = digitalRead(7);
    String contentDoor;
  
    if(doorState==HIGH){  
       contentDoor = contentI2+"false}";
    
    }
    else{
      contentDoor = contentI2+"true}";
    }
  
    ESP8266.println("AT+CIPMUX=1");
    delay(100);
   

    ESP8266.println("AT+CIPSTART=4,\"TCP\",\"172.18.9.100\",3000");
    delay(100);
  

    String cmd2 = "PUT /doors/1 HTTP/1.1\r\nHost:172.18.9.100:3000\r\nUser-Agent: Arduino/1.0\r\nAccept: application/json\r\nContent-Length:"+(String)contentDoor.length()+"\r\nContent-Type: application/json\r\nConnection: close\r\n\n"+contentDoor;
    ESP8266.println("AT+CIPSEND=4," + String(cmd2.length()+4));
    delay(100);

  
    Serial.println(cmd2);
   
    ESP8266.println("PUT /doors/1 HTTP/1.1");
    ESP8266.println("Host:172.18.9.100:3000");    
    ESP8266.println("User-Agent: Arduino/1.0");
    ESP8266.println("Accept: application/json");
    ESP8266.print("Content-Length: ");
    ESP8266.println(contentDoor.length());    
    ESP8266.println("Content-Type: application/json");
    ESP8266.println("Connection: close");
    ESP8266.println();
    ESP8266.println(contentDoor); 

    
    /////////////////////////////////////////////////////////////
    
    delay(100);  
    ESP8266.println("");
    
}



