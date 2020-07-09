
//ESP-XAC-Joystick Software
//ESP-XAC-Joystick
//Written by: Milad Hajihassan
//Version 1.0 (07/08/2020)
//Github Link: https://github.com/milador/ESP-XAC-Joystick

#include <WiFi.h>
#include "NetworkConfig.h"

#define BUTTON_U_PIN 6
#define BUTTON_L_PIN 7
#define BUTTON_R_PIN 8
#define BUTTON_D_PIN 9

#define BUTTON_X_PIN 10
#define BUTTON_Y_PIN 11
#define BUTTON_A_PIN 12
#define BUTTON_B_PIN 13

#define BUTTON_DELAY 100

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

//Button states

bool buttonUState = true;
bool buttonLState = true;
bool buttonRState = true;
bool buttonDState = true;

bool buttonXState = true;
bool buttonYState = true;
bool buttonAState = true;
bool buttonBState = true;


// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time
const long timeoutTime = 500;

void setup() {
  delay(3000);
  Serial.begin(115200);

  // Initialize the output states
  digitalWrite(BUTTON_U_PIN, HIGH);
  digitalWrite(BUTTON_L_PIN, HIGH);
  digitalWrite(BUTTON_R_PIN, HIGH);
  digitalWrite(BUTTON_D_PIN, HIGH);
  
  digitalWrite(BUTTON_X_PIN, HIGH);
  digitalWrite(BUTTON_Y_PIN, HIGH);
  digitalWrite(BUTTON_A_PIN, HIGH);
  digitalWrite(BUTTON_B_PIN, HIGH);

  Serial.println();

  WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected.");

  Serial.print("Please use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect.");
  server.begin();
}

void loop(){

  WiFiClient client = server.available();   // Listen for incoming client calls

  if (client) {                             // If a new client connects 
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          //Print a message out in the serial port
    String currentLine = "";                //Make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  //Loop while the client's connected
      currentTime = millis();
      if (client.available()) {             //If there's bytes to read from the client,
        char c = client.read();             //Read a byte, then
        Serial.write(c);                    //Print it out the serial monitor
        header += c;
        if (c == '\n') {                    //If the byte is a newline character
          //If the current line is blank, you got two newline characters in a row.
          //that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.write("HTTP/1.1 200 OK\r\n");
            client.write("Content-type:text/html\r\n");
            client.write("Connection: Keep-Alive\r\n");
            client.write("\r\n");
            
            if (header.indexOf("GET /x/press") >= 0) {
              Serial.println("Button X pressed.");
              buttonXState = LOW;
              digitalWrite(BUTTON_X_PIN, LOW);
              delay(BUTTON_DELAY);
              buttonXState = HIGH;
              digitalWrite(BUTTON_X_PIN, HIGH);
            } else if (header.indexOf("GET /y/press") >= 0) {
              Serial.println("Button Y pressed.");
              buttonYState = LOW;
              digitalWrite(BUTTON_Y_PIN, LOW);
              delay(BUTTON_DELAY);
              buttonYState = HIGH;
              digitalWrite(BUTTON_Y_PIN, HIGH);
            } else if (header.indexOf("GET /a/press") >= 0) {
              Serial.println("Button A pressed.");
              buttonAState = LOW;
              digitalWrite(BUTTON_A_PIN, LOW);
              delay(BUTTON_DELAY);
              buttonAState = HIGH;
              digitalWrite(BUTTON_A_PIN, HIGH);
            } else if (header.indexOf("GET /b/press") >= 0) {
              Serial.println("Button B pressed.");
              buttonBState = LOW;
              digitalWrite(BUTTON_B_PIN, LOW);
              delay(BUTTON_DELAY);
              buttonBState = HIGH;
              digitalWrite(BUTTON_B_PIN, HIGH);
            } else if (header.indexOf("GET /u/press") >= 0) {
              Serial.println("Button UP pressed.");
              buttonUState = LOW;
              digitalWrite(BUTTON_U_PIN, LOW);
              delay(BUTTON_DELAY);
              buttonUState = HIGH;
              digitalWrite(BUTTON_U_PIN, HIGH);
            } else if (header.indexOf("GET /l/press") >= 0) {
              Serial.println("Button LEFT pressed.");
              buttonLState = LOW;
              digitalWrite(BUTTON_L_PIN, LOW);
              delay(BUTTON_DELAY);
              buttonLState = HIGH;
              digitalWrite(BUTTON_L_PIN, HIGH);
            } else if (header.indexOf("GET /a/press") >= 0) {
              Serial.println("Button RIGHT pressed.");
              buttonRState = LOW;
              digitalWrite(BUTTON_R_PIN, LOW);
              delay(BUTTON_DELAY);
              buttonRState = HIGH;
              digitalWrite(BUTTON_R_PIN, HIGH);
            } else if (header.indexOf("GET /b/press") >= 0) {
              Serial.println("Button DOWN pressed.");
              buttonDState = LOW;
              digitalWrite(BUTTON_D_PIN, LOW);
              delay(BUTTON_DELAY);
              buttonDState = HIGH;
              digitalWrite(BUTTON_D_PIN, HIGH);
            }
            
            // Display HTML web page
            client.write("<!DOCTYPE html><html>\r\n");
            client.write("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\r\n");
            client.write("<link rel=\"icon\" href=\"data:,\">\r\n");
            // Style buttons 
            client.write("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\r\n");
            client.write(".button-x { background-color: #1873ff; border: none; color: white; padding: 20px 20px;\r\n");
            client.write("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\r\n");
            
            client.write(".button-y { background-color: #ffe618; border: none; color: white; padding: 20px 20px;\r\n");
            client.write("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\r\n");

            client.write(".button-a { background-color: #42ff18; border: none; color: white; padding: 20px 20px;\r\n");
            client.write("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\r\n");

            client.write(".button-b { background-color: #ff1818; border: none; color: white; padding: 20px 20px;\r\n");
            client.write("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\r\n");

            client.write(".button-arrow { background-color: #444444; border: none; color: white; padding: 20px 20px;\r\n");
            client.write("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\r\n");

            client.write("#header { width: 100%; background-color: #bbbbbb; height: 50px;}\r\n");
 
            client.write("#container { width: 80%; background-color: #ffcc33; margin: auto;}\r\n");

            client.write("#left-pad { width: 50%; float: left; height: 300px; background-color: #999999;}\r\n");

            client.write("#right-pad { width: 50%; float: left; height: 300px; background-color: #555555;}\r\n"); 

            client.write("#half-pad { width: 50%; float: left; height: 50%;}\r\n");

            client.write("#third-pad { width: 33%; float: left; height: 33%;}\r\n"); 
            
            client.write("#clear { clear: both;}\r\n"); 
                                    
            client.write(".button-active {background-color: #555555;}</style></head>\r\n");
                        
            // Web Page Headings
            client.write("<body><div id=\"header\"><h2>ESP-XAC-Joystick Server</h2></div>\r\n");

            client.write("<div id=\"container\">\r\n"); 

            client.write("<div id=\"left-pad\"><div id=\"third-pad\"></div>\r\n"); 

            if (buttonUState==HIGH) {
              client.write("<div id=\"third-pad\"><div><p><a href=\"/u/press\"><button class=\"button-arrow\">U</button></a></p></div></div>\r\n");
            } 

            client.write("<div id=\"third-pad\"></div>\r\n"); 
 
            if (buttonLState==HIGH) {
              client.write("<div id=\"third-pad\"><div><p><a href=\"/l/press\"><button class=\"button-arrow\">L</button></a></p></div></div>\r\n");
            }       

            client.write("<div id=\"third-pad\"></div>\r\n");          

            if (buttonRState==HIGH) {
              client.write("<div id=\"third-pad\"><div><p><a href=\"/r/press\"><button class=\"button-arrow\">R</button></a></p></div></div>\r\n");
            }    

            client.write("<div id=\"third-pad\"></div>\r\n"); 

            if (buttonDState==HIGH) {
              client.write("<div id=\"third-pad\"><div><p><a href=\"/d/press\"><button class=\"button-arrow\">D</button></a></p></div></div>\r\n");
            }                    

            client.write("<div id=\"third-pad\"></div>\r\n"); 

            client.write("</div><div id=\"right-pad\">\r\n"); 
            
            // Display current state for GPIO 10  
            //client.write("<p>GPIO 10 : Button X</p>\r\n");
 
            if (buttonXState==HIGH) {
              client.write("<div id=\"half-pad\"><div><p><a href=\"/x/press\"><button class=\"button-x\">X</button></a></p></div></div>\r\n");
            } 
               
            // Display current state for GPIO 11  
            //client.write("<p>GPIO 11 : Button Y</p>\r\n");    
            if (buttonXState==HIGH) {
              client.write("<div id=\"half-pad\"><div><p><a href=\"/y/press\"><button class=\"button-y\">Y</button></a></p></div></div>\r\n");
            }  

            // Display current state for GPIO 12  
            //client.write("<p>GPIO 12 : Button A</p>\r\n");    
            if (buttonAState==HIGH) {
              client.write("<div id=\"half-pad\"><div><p><a href=\"/a/press\"><button class=\"button-a\">A</button></a></p></div></div>\r\n");
            }  

            // Display current state for GPIO 13  
            //client.write("<p>GPIO 13 : Button B</p>\r\n");    
            if (buttonBState==HIGH) {
              client.write("<div id=\"half-pad\"><div><p><a href=\"/b/press\"><button class=\"button-b\">B</button></a></p></div></div>\r\n");
            }  
            
            client.write("</div><div id=\"clear\"></div></div></body></html>\r\n");
            
            // The HTTP response ends with another blank line
            client.write("\r\n");
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
