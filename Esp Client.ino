#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

String ssid = "while():" ;
String password = "raju12345" ;

String server = "http://192.168.73.239/update" ;
const char* msg = "api_key=1@2#34&data=SB2-203" ;

// int pin = 2 ;

void setup() 
{
  Serial.begin(115200) ;
  
  // ------------------------------- Initialize GPIO 2 pin as Input pin -----------------------------------
  // pinMode(pin, INPUT) ;

  // ----------------------------------- Initializing Wifi ---------------------------------------
  WiFi.begin(ssid , password) ;
  Serial.println("Connecting to Wifi") ;
  while (WiFi.status() != WL_CONNECTED){Serial.print(".."); delay(500) ;}
  Serial.println("\nConnected to Wifi") ;
  Serial.print("IP Address : "); Serial.println(WiFi.localIP()) ;
}

void loop() 
{
  //if Arduino nano gets the signal from Ultrasonic sensor that the dustbin is full , it will send a HIGH pulse to ESP-01 GPIO pin 2 ;
  // if(digitalRead(2)){

  if(WiFi.status() != WL_CONNECTED) {Serial.println(">> ! WiFi is off !");}
  else
  {
    WiFiClient client ; HTTPClient http ;  //Creating Clients
    http.begin(client , server) ;
    
    Serial.println("\n---------------------------------Successfully Connected with Server---------------------------------") ;
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int code = http.POST(msg) ;

    // -------------------------------- if there occure any error then code<0 -----------------------------------
    
    while(code < 0)    // Until the HTTP Post request is successfully done , it will continuously send the request.  
    {
      delay(2000) ;    // Posting request very frequently is not good , so the delay is used.
      
      Serial.printf(">> ! Not completed ! : %s\n" , http.errorToString(code));
      http.begin(client , server) ;
      code = http.POST(msg) ;
    } 
    
    if(code>0)
    {
      String payload = http.getString() ;
      Serial.println(payload) ;
    }

    http.end() ;
    delay(120000) ;  // Remove this delay after modifying the code
  }
  
  // }
}
