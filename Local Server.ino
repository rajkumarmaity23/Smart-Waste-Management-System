#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

String ssid = "while():" ;
String password = "raju12345" ;

// IPAddress localIP(192 , 168 , 0 , 100) ;   //IP we want to set
// IPAddress gateway(192 , 168 , 0 , 1) ;    // IP or gateway of the router
// IPAddress subnet(255 , 255 , 255 , 0) ;  // Subnet of the router 

String message;

AsyncWebServer server(80) ;

const char index_html1[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html>

  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  </head>
  <body>

  <h1 style="color:indigo; font-family:georgia; font-size:45px;"> <center> <u> Smart Dustbin </u> </center> </h1>
  <br><br>
  <center>

  <div id="Division">
  <label for="password" style="font-family:georgia; font-size:16px;"> Enter the Password : </label> &nbsp
  <input type="password" id="password" name="password"><br><br><br>
  <button style="padding:5px 20px; color:black; font-family:georgia; border-radius:16px" onclick="func()">Submit</button>
  <br><br>
  <h7 style="font-family:georgia; font-size:14px;" id="pswd"></h7>
  </div>
  </center>


  <script>
  function func()
  {
      var acct_pass = "Admin@TNU";
      var x = document.getElementById("password").value;
      let message = document.getElementById("pswd") ;
    
      var y = "<center><p style=\"font-family:Times New Roman; font-size:20px;\" id=\"msg\">Dustbin is Full in RN : %Data% </p></center>" ;

        if(x.length == 0)
        {
          message.textContent = "Please fill the password";
        }
        else
        {
          if (x == acct_pass)
          {
              message.textContent = "Successfully login";
      setTimeout(()=>{document.getElementById("Division").innerHTML = y ;} 
      , 300) ;
      
          }
          else
          {
              message.textContent = "Wrong Password";
          }
        } 
  }
  </script>

  </body>
  </html> )rawliteral" ;


String processor(const String& var)
{
  if (var == "Data")
  {
    return message;
  }
  return String();
}


void setup() 
{
  // ----------------------------------------- Initializing WiFi------------------------------------------------------------- 
  Serial.begin(115200) ;
  WiFi.begin(ssid , password) ;
  Serial.println() ;

  // while(!WiFi.config(localIP, gateway, subnet)){Serial.println("Configuration on going");}    // This is for configuring Static IP
  
  while(WiFi.status() != WL_CONNECTED)
  {Serial.print(".."); delay(800);}
  Serial.print("\nConnected to IP : "); Serial.println(WiFi.localIP()) ;

  // ------------------------------------------ Initializing the Server -----------------------------------------------------
  server.on("/" , HTTP_GET , [] (AsyncWebServerRequest *request){
    request->send_P(200 , "text/html" , index_html1 , processor);
  }) ;

  server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request){
        if (request->hasParam("data" , true) && request->hasParam("api_key" , true)) 
        {
          if(request->getParam("api_key" , true)->value() == "1@2#34")
          {
            message = request->getParam("data" , true)->value(); 
            Serial.print("Received from  Client : ") ;
            Serial.println(message) ;
          }
        } 
        else 
        {
            message = "Not Provided";
        }
        request->send(200, "text/plain", "Received from Server - " + message);
    });

  server.begin() ;

}

void loop() 
{
  // GSM code will be written here  
}
