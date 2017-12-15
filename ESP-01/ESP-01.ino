// Programa : Teste modulo wireless ESP8266
// Autor : Arduino e Cia

// Carrega as bibliotecas ESP8266 e SoftwareSerial
#include "ESP8266.h"
#include "SoftwareSerial.h"
#include <doxygen.h>
#include <SPI.h>

#define DEBUG true

// Cria uma serial nas portas 2 (RX) e 3 (TX)
SoftwareSerial esp(2 , 3); 

// Define que o modulo ira utilizar a serial minhaSerial
//ESP8266 wifi(esp);

// Configuracao ID e senha da rede Wireless
#define SSID        "TP-LINK_8DDDAE"
#define PASSWORD    "labiotm06"


void setup(){   
    
    delay(2000);
  
    Serial.begin(115200);
    esp.begin(115200);

    //Envia o comandos AT
 
    // reseta o modulo
    sendData("AT+RST\r",2000,DEBUG);
    Serial.println("////////////////////////////////////////////////////////////////////////////");
    // configure as access point e estação (ambos)  
    sendData("AT+CWMODE=1\r",5000,DEBUG);
    Serial.println("////////////////////////////////////////////////////////////////////////////");
    //conecta ao roteador com a senha
    //(esta configuração deve ser feita, pois o seu roteador tem nome diferente do meu e senha)
    sendData("AT+CWJAP=\"TP-LINK_8DDDAE\",labiotm06\"\r",15000,DEBUG);
    Serial.println("////////////////////////////////////////////////////////////////////////////");
    sendData("AT+CIFSR\r",15000,DEBUG);
    Serial.println("////////////////////////////////////////////////////////////////////////////");
    //seta o caminho 
    sendData("AT+ CIPMUX=0\r",2000,DEBUG);
    Serial.println("////////////////////////////////////////////////////////////////////////////");
    sendData("AT + CIPSTART = TCP,192.18.9.100,3000\r",2000,DEBUG);
    Serial.println("////////////////////////////////////////////////////////////////////////////");
    sendData("AT+RST\r",2000,DEBUG);
    

    
}

void loop(void){


  if(esp.available()){
      Serial.println("SERIAL CONECTADA");
      //sendData("AT+CWLAP\r\n",10000,DEBUG);
     
    }

    delay(2000);

  
   /* Serial.print("Inicializando modulo\r\n");
    Serial.print("Versao do firmware: ");
    Serial.println(wifi.getVersion().c_str());
    // Define modo de operacao como STA (station)
    if (wifi.setOprToStation()) {
        Serial.print("Modo STA ok\r\n");
    } else {
        Serial.print("Erro ao definir modo STA !r\n");
    }
    
    // Conexao a rede especificada em SSID
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Conectado com sucesso a rede wireless\r\n");
        Serial.print("IP: ");       
        Serial.println(wifi.getLocalIP().c_str());
    } else {
        Serial.print("Erro ao conectar rede wireless !!!\r\n");
    }
    
    Serial.print("*** Fim ***\r\n");
    while(1){}*/
}

//Metodo que envia os comandos para o esp8266
String sendData(String command, const int timeout, boolean debug)
{
    //variavel de resposta do esp8266
    String response = "";
   
    // send a leitura dos caracteres para o esp8266
    esp.println(command);
   
    long int time = millis();
   
    while( (time+timeout) > millis())
    {
      while(esp.available())
      {
       
 
        //Concatena caracter por caractere recebido do modulo esp8266
        char c = esp.read();
        response+=c;
      }  
    }
   
    //debug de resposta do esp8266
    if(debug)
    {
      //Imprime o que o esp8266 enviou para o arduino
      Serial.println("Arduino : " + response);
      
    }
   
    return response;
}
