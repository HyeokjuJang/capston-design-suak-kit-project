#include <SoftwareSerial.h>
#include <Servo.h>
#include "ESP8266.h"

#define SSID "JangWiFi"
#define PASS "sherlocked"
#define REQUEST_URL "http://api.thingspeak.com" 


Servo myservo;  // create servo object to control a servo

SoftwareSerial esp8266Serial = SoftwareSerial(8, 9);
ESP8266 wifi = ESP8266(esp8266Serial);

int pos = 0;    // variable to store the servo position
int analogPin = 0;    // 워터센서 analog port 0 연결 선언
int val = 0;          // 전류변화값 변수선언

int suwi = 1;
int servo = 1;
int barcode = 1;

void setup()
{
    myservo.attach(6);
    myservo.write(0);
    //Serial.begin(9600);

    // ESP8266
    esp8266Serial.begin(9600);
    wifi.begin();
    wifi.setTimeout(5000);

    /****************************************/
    /******       Basic commands       ******/
    /****************************************/
    // test
    //Serial.print("test: ");
    //Serial.println(getStatus(wifi.test()));

    // restart
    //Serial.print("restart: ");
    //Serial.println(getStatus(wifi.restart()));
    wifi.test();
    wifi.restart();
   
    // getVersion
    char version[16] = {};
     wifi.getVersion(version, 16);
    //Serial.print("getVersion: ");
    //Serial.print(getStatus(wifi.getVersion(version, 16)));
    //Serial.print(" : ");
    //Serial.println(version);


    /****************************************/
    /******        WiFi commands       ******/
    /****************************************/
    // joinAP
    //Serial.print("joinAP: ");
    //Serial.println(getStatus(wifi.joinAP(SSID, PASS)));
    wifi.joinAP(SSID, PASS);

    /****************************************/
    /******       TCP/IP commands      ******/
    /****************************************/
    // connect
    //Serial.print("connect: ");
    //Serial.println(getStatus(wifi.connect(ESP8266_PROTOCOL_TCP, "api.thingspeak.com", 80)));
    wifi.connect(ESP8266_PROTOCOL_TCP, "api.thingspeak.com", 80);
    // send
    //Serial.print("send: ");
    //Serial.println(getStatus(wifi.send("GET / HTTP/1.0\r\n\r\n")));

}

void loop()
{
    val = analogRead(analogPin);   // analogPin 의 변화값(전류값)을 읽음
   
    if (val > 100)                 // val 값이 100이 넘으면 (전류가 100이 넘으면)
    {                               
          if(suwi == 1){
            myservo.write(0);              // tell servo to go to position in variable 'pos'
          }
          suwi = 0; // 0이 잠금상태
          servo = 1; // 0이 잠금상태
          
          
          delay(500);                       // waits 15ms for the servo to reach the position
    }
    else                           // val 값이 100이하면 (전류가 100이하면)
    {
      if(suwi == 0){
        myservo.write(180);              // tell servo to go to position in variable 'pos'
      }
      suwi = 1; // 1이 열린상태
      servo = 1; // 1이 열린상태
      
      delay(500);
    }
    
    /****************************************/
    /******        WiFi commands       ******/
    /****************************************/
    sendRequest();
    delay (16000);
}

void sendRequest(){
  // read data
    //Serial.print("connect: ");
    //Serial.println(getStatus(wifi.connect(ESP8266_PROTOCOL_TCP, "api.thingspeak.com", 80)));
    wifi.connect(ESP8266_PROTOCOL_TCP, "api.thingspeak.com", 80);
    unsigned int id;
    int length;
    int totalRead;
    //String buffer = String(REQUEST_URL);
    String buffer = String("/update?api_key=9X82ZV4DJCV5TUT1&field1=");
    buffer += suwi; 
    buffer += String("&field2=");
    buffer += servo; 
    buffer += String("&field3=");
    buffer += barcode;
    buffer += "";
   
    String request = String("GET ");
    request += buffer;
    request += " HTTP/1.0\r\n\r\n";
    // send
    //Serial.print("send: ");
    //Serial.println(request);
    //Serial.println(getStatus(wifi.send(request)));
    wifi.send(request);
    
}

String getStatus(bool status)
{
    if (status)
        return "OK";

    return "KO";
}

String getStatus(ESP8266CommandStatus status)
{
    switch (status) {
    case ESP8266_COMMAND_INVALID:
        return "INVALID";
        break;

    case ESP8266_COMMAND_TIMEOUT:
        return "TIMEOUT";
        break;

    case ESP8266_COMMAND_OK:
        return "OK";
        break;

    case ESP8266_COMMAND_NO_CHANGE:
        return "NO CHANGE";
        break;

    case ESP8266_COMMAND_ERROR:
        return "ERROR";
        break;

    case ESP8266_COMMAND_NO_LINK:
        return "NO LINK";
        break;

    case ESP8266_COMMAND_TOO_LONG:
        return "TOO LONG";
        break;

    case ESP8266_COMMAND_FAIL:
        return "FAIL";
        break;

    default:
        return "UNKNOWN COMMAND STATUS";
        break;
    }
}

String getRole(ESP8266Role role)
{
    switch (role) {
    case ESP8266_ROLE_CLIENT:
        return "CLIENT";
        break;

    case ESP8266_ROLE_SERVER:
        return "SERVER";
        break;

    default:
        return "UNKNOWN ROLE";
        break;
    }
}

String getProtocol(ESP8266Protocol protocol)
{
    switch (protocol) {
    case ESP8266_PROTOCOL_TCP:
        return "TCP";
        break;

    case ESP8266_PROTOCOL_UDP:
        return "UDP";
        break;

    default:
        return "UNKNOWN PROTOCOL";
        break;
    }
}
