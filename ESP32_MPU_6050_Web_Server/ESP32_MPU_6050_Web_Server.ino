#include <Arduino.h>
#include <ESP8266WiFi.h> //import for wifi functionality
#include <WebSocketsServer.h> //import for websocket


#include <WiFiClient.h> 
#include <ESP8266WebServer.h>


#define ENA  14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)



const char *ssid =  "HelloHPC - Wifi";   //Wifi SSID (Name)   
const char *pass =  "12345678"; //wifi password

WebSocketsServer webSocket = WebSocketsServer(81); //websocket init with port 81

    int speedCar = 1000;         // 400 - 1023.
    int speed_Coeff = 3;
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
//webscket event method
    String cmd = "";


    switch(type) {
        case WStype_DISCONNECTED:
            Serial.println("Websocket is disconnected");
            //case when Websocket is disconnected
            break;
        case WStype_CONNECTED:{
            //wcase when websocket is connected
            Serial.println("Websocket is connected");
            Serial.println(webSocket.remoteIP(num).toString());
            webSocket.sendTXT(num, "connected");}
            break;
        case WStype_TEXT:
            cmd = "";
            for(int i = 0; i < length; i++) {
                cmd = cmd + (char) payload[i]; 
            } //merging payload to single string
            Serial.println(cmd);

            // if(cmd == "poweron"){ //when command from app is "poweron"
            //     digitalWrite(ledpin, HIGH);   //make ledpin output to HIGH  
            // }else if(cmd == "poweroff"){
            //     digitalWrite(ledpin, LOW);    //make ledpin output to LOW on 'pweroff' command.
            // }


      if (cmd == "F") goAhead();
      else if (cmd == "B") goBack();
      else if (cmd == "L") goLeft();
      else if (cmd == "R") goRight();
      else if (cmd == "I") goAheadRight();
      else if (cmd == "G") goAheadLeft();
      else if (cmd == "J") goBackRight();
      else if (cmd == "H") goBackLeft();
      else if (cmd == "0") speedCar = 400;
      else if (cmd == "1") speedCar = 470;
      else if (cmd == "2") speedCar = 540;
      else if (cmd == "3") speedCar = 610;
      else if (cmd == "4") speedCar = 680;
      else if (cmd == "5") speedCar = 750;
      else if (cmd == "6") speedCar = 820;
      else if (cmd == "7") speedCar = 890;
      else if (cmd == "8") speedCar = 960;
      else if (cmd == "9") speedCar = 1023;
      else if (cmd == "S") stopRobot();

            if(cmd == "poweron")
             webSocket.sendTXT(num, "poweron:success");
            else
              webSocket.sendTXT(num, "poweroff:success");
             //send response to mobile, if command is "poweron" then response will be "poweron:success"
             //this response can be used to track down the success of command in mobile app.
            break;
        case WStype_FRAGMENT_TEXT_START:
            break;
        case WStype_FRAGMENT_BIN_START:
            break;
        case WStype_BIN:
            hexdump(payload, length);
            break;
        default:
            break;
    }
}

void setup() {



 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
  
  //Serial.begin(115200);

  
   Serial.begin(9600); //serial start

   Serial.println("Connecting to wifi");
   
   IPAddress apIP(192, 168, 0, 1);   //Static IP for wifi gateway
   WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); //set Static IP gateway on NodeMCU
   WiFi.softAP(ssid, pass); //turn on WIFI

   webSocket.begin(); //websocket Begin
   webSocket.onEvent(webSocketEvent); //set Event for websocket
   Serial.println("Websocket is started");
}


void goAhead(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goBack(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goAheadRight(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar/speed_Coeff);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
   }

void goAheadLeft(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void goBackRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar/speed_Coeff);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goBackLeft(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }







void loop() {
   webSocket.loop(); //keep this line on loop method
}