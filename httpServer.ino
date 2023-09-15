#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// The web server
ESP8266WebServer server(80);

/**
 * Go to http://192.168.4.1 in a web browser connected to this access point to see it.
 */
void handleRoot() {
    server.send(200, "text/html", SendHTML());
}

void handleGetTime() {
    Serial.println("GET /time");
    server.send(200, "text/plain", getTimeStr());
}

void handleGetTimeOfDay() {
    Serial.println("GET /timeofday");
    int hour, minute;
    getTimeOfDay(&hour, &minute);
    char timeOfDay[128];
    sprintf(timeOfDay, "getTimeofDay: %.2d-%.2dT", hour, minute);

    server.send(200, "text/plain", String(timeOfDay));
}

void handlePutTime() {
    Serial.println("PUT /time");
    String newTimeValue = server.arg("value");
    Serial.println("PUT /time?value=" + newTimeValue);
    setDateTime(newTimeValue);
    server.send(200, "text/plain", getTimeStr());
}

String SendHTML() {
     String ptr = "<!DOCTYPE html> <html>\n";
     ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
     ptr +="<title>LED Control</title>\n";
     ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
     ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
     ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
     ptr +=".button-on {background-color: #1abc9c;}\n";
     ptr +=".button-on:active {background-color: #16a085;}\n";
     ptr +=".button-off {background-color: #34495e;}\n";
     ptr +=".button-off:active {background-color: #2c3e50;}\n";
     ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
     ptr +="</style>\n";
     ptr +="</head>\n";
     ptr +="<body>\n";
     ptr +="<h1>ESP8266 Web Server</h1>\n";
     ptr +="<h3>Using Access Point(AP) Mode</h3>\n";

     ptr +="<p>Time: " + getTimeStr() + "</p>\n";

    ptr +="</body>\n";
    ptr +="</html>\n";

    return ptr;
}

/** Setup the HTTP Server and define the endpoints */
void setupHttpServer() {
    server.on("/time", HTTP_GET, handleGetTime);
    server.on("/timeofday", HTTP_GET, handleGetTimeOfDay);
    server.on("/time", HTTP_PUT, handlePutTime);
    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started");
}

void serverHandleClient() {
    server.handleClient();
}
