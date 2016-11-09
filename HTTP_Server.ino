
    #include <ESP8266WiFi.h>
     WiFiServer server(80); //Initialize the server on Port 80
     const short int LED_PIN = 16;//GPIO16
      void setup() {
         WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint
         WiFi.softAP("Hello_IoT", "12345678"); // Provide the (SSID, password); .
         server.begin(); // Start the HTTP Server
         //Looking under the hood
         Serial.begin(115200);
         IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server
         Serial.print("Server IP is: "); // Print the IP to the monitor window
         Serial.println(HTTPS_ServerIP); 

         pinMode(LED_PIN, OUTPUT); //GPIO16 is an OUTPUT pin;
         digitalWrite(LED_PIN, HIGH); //Initial state is OFF
     }
     void loop() {
         WiFiClient client = server.available();
         if (!client) {
return; }
         //Looking under the hood
         Serial.println("Somebody has connected :)");
         //Read what the browser has sent into a String class
         
//and print the request to the monitor
         String request = client.readStringUntil('\r');
         //Looking under the hood
         Serial.println(request);
         // Handle the Request
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
         Serial.println("Client disonnected"); //Looking under the hood
}
