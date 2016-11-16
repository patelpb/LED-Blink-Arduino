//intial source for code: http://www.instructables.com/id/Programming-a-HTTP-Server-on-ESP-8266-12E/?ALLSTEPS   
//The Purpose of this code is to connect to a WiFi server and control the status of the LED on the ESP8266
  //using a website.
    #include <ESP8266WiFi.h>
     WiFiServer server(80); //Initialize the server on Port 80
     const short int LED_PIN = 16;//GPIO16
      void setup() {
         WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint
         WiFi.softAP("Hello_IoT", "12345678"); // This is the (SSID, password); .
         server.begin(); // Start the HTTP Server
         
         Serial.begin(115200);
         IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // This is the IP of the Server

         pinMode(LED_PIN, OUTPUT); //GPIO16 is an OUTPUT pin;
         digitalWrite(LED_PIN, HIGH); //Initial state is OFF
     }
     
     void loop() {
         WiFiClient client = server.available();
         if (!client) {
return; }
         String request = client.readStringUntil('\r');
         Serial.println(request);
         // Handle the Request
         //LOW corresponds to ON and HIGH corresponds to OFF (status of the LED)
         if (request.indexOf("/ONCE") != -1){
           digitalWrite(LED_PIN, LOW);
           delay (1000);
           digitalWrite(LED_PIN, HIGH);}
         else if (request.indexOf("/TWICE") != -1){
           digitalWrite(LED_PIN, LOW);
           delay (1000);
           digitalWrite(LED_PIN, HIGH);
           delay (1000);
           digitalWrite(LED_PIN, LOW);
           delay (1000);
           digitalWrite(LED_PIN, HIGH);
         }
         
         // Prepare the HTML document to respond and add buttons:
         String s = "HTTP/1.1 200 OK\r\n";
         s += "Content-Type: text/html\r\n\r\n";
         s += "<!DOCTYPE HTML>\r\n<html>\r\n";
         s += "<br><input type=\"button\" name=\"b1\" value=\"LED Once\" onclick=\"location.href='/ONCE'\">";
         s += "<br><br><br>";
         s += "<br><input type=\"button\" name=\"b1\" value=\"LED Twice\" onclick=\"location.href='/TWICE'\">";
         s += "</html>\n";
         
         //Serve the HTML document to the browser.
         client.flush(); //clear previous info in the stream
         client.print(s); // Send the response to the client
         delay(1);
}
