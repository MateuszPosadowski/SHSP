/*
   This sketch shows an example of sending a reading to data.sparkfun.com once per day.
   It uses the Sparkfun testing stream so the only customizing required is the WiFi SSID and password.
   The Harringay Maker Space
   License: Apache License v2
*/
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <NTPClient.h>
#include <Arduino_JSON.h>

#define DEBUG_ON
#define PIN_LED BUILTIN_LED
#define RELAY D8

#define RELAY_ON false
#define RELAY_OFF true

const long utcOffsetInSeconds = 7200;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

const char* ssid = "blank";               // Set you WiFi SSID
const char* password = "blank";              // Set you WiFi password
String ip_address_esp;
char ip_address_esp_char[16];
String first_hours_state;
String second_hours_state;

char first_hours_state_char[16];
char second_hours_state_char[16];


uint8_t hour_set_on=21;
uint8_t minutes_set_on=0;

uint8_t hour_set_on_morning=5;
uint8_t minutes_set_on_morning=0;

uint8_t hour_set_off=23;
uint8_t minutes_set_off=0;


uint8_t hour_set_off_morning=6;
uint8_t minutes_set_off_morning=30;


String st;
String content;
int statusCode;

bool realy = RELAY_OFF;
String stan = "OFF";
bool realy_changed = false;

bool first_hours = false;
bool second_hours = false;

WiFiClient client; //obiekt wifi
ESP8266WebServer server(80);

/*
 * The structure contains following fields:
 * struct strDateTime
{
  byte hour;
  byte minute;
  byte second;
  int year;
  byte month;
  byte day;
  byte dayofWeek;
  boolean valid;
};
 */



void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  Serial.println();
  Serial.println("Booted");

  Serial.println("Reading ssid");
  String esid;
  for (int i = 0; i < 32; ++i)
    {
      esid += char(EEPROM.read(i));
    }
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading  password");
  String epass = "";
  for (int i = 32; i < 96; ++i)
    {
      epass += char(EEPROM.read(i));
    }
  Serial.print("PASS: ");
  Serial.println(epass);  
  if ( esid.length() > 1 ) {
      WiFi.begin(esid.c_str(), epass.c_str());
      if (testWifi() == false) {
        setupAP();
        return;
      } 
  }

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESP_relay_driver", "password");


  Serial.println("WiFi connected");

  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  ip_address_esp = WiFi.localIP().toString();

  ip_address_esp.toCharArray(ip_address_esp_char, 16);
  Serial.println(ip_address_esp_char);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  pinMode(PIN_LED, OUTPUT);
  pinMode(RELAY,OUTPUT);


  server.on("/", handleRoot);
  server.on("/on", handleON);
  server.on("/off", handleOFF);
  server.on("/set", setParams);
  server.on("/setting", handleSETTING);
  server.on("/manual", handleMANUAL);
  server.on("/api/on",handleApiOn);
  server.on("/api/off",handleApiOff);
  server.on("/test.svg", drawGraph);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  first_hours_state = "\u2718";
  first_hours_state.toCharArray(first_hours_state_char,16);

  second_hours_state = "\u2718";
  second_hours_state.toCharArray(second_hours_state_char,16);

}

String IpAddress2String(const IPAddress& ipAddress)
{
    return String(ipAddress[0]) + String(".") +
           String(ipAddress[1]) + String(".") +
           String(ipAddress[2]) + String(".") +
           String(ipAddress[3]);
}

void setupAP(void) {
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
     {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
     }
  }
  Serial.println(""); 
  st = "<ol>";
  for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      st += "<li>";
      st += WiFi.SSID(i);
      st += " (";
      st += WiFi.RSSI(i);
      st += ")";
      st += (WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*";
      st += "</li>";
    }
  st += "</ol>";
  delay(100);
  WiFi.softAP("ESP_relay_driver", "password");
  Serial.println("softap");
  launchWeb(1);
  Serial.println("over");
}

void launchWeb(int webtype) {
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer(webtype);
  // Start the server
  server.begin();
  Serial.println("Server started"); 
  while(1)
  {
      server.handleClient();
  }
}

void createWebServer(int webtype)
{
  if ( webtype == 1 ) {
    server.on("/", []() {
        IPAddress ip = WiFi.softAPIP();
        String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
        content = "<!DOCTYPE HTML>\r\n<html>WiFi configuration page for :  ";
        content += ipStr;
        content += "<p>";
        content += st;
        content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
        content += "</html>";
        server.send(200, "text/html", content);  
    });
    server.on("/setting", []() {
        String qsid = server.arg("ssid");
        String qpass = server.arg("pass");
        if (qsid.length() > 0 && qpass.length() > 0) {
          Serial.println("clearing eeprom");
          for (int i = 0; i < 96; ++i) { EEPROM.write(i, 0); }
          Serial.println(qsid);
          Serial.println("");
          Serial.println(qpass);
          Serial.println("");
            
          Serial.println("writing eeprom ssid:");
          for (int i = 0; i < qsid.length(); ++i)
            {
              EEPROM.write(i, qsid[i]);
              Serial.print("Wrote: ");
              Serial.println(qsid[i]); 
            }
          Serial.println("writing eeprom pass:"); 
          for (int i = 0; i < qpass.length(); ++i)
            {
              EEPROM.write(32+i, qpass[i]);
              Serial.print("Wrote: ");
              Serial.println(qpass[i]); 
            }    
          EEPROM.commit();
          content = "{\"Success\":\"saved to eeprom....... reset to boot into new wifi\"}";
          statusCode = 200;
        } else {
          content = "{\"Error\":\"404 not found\"}";
          statusCode = 404;
          Serial.println("Sending 404");
        }
        server.send(statusCode, "application/json", content);
    });
  } else if (webtype == 0) {
    server.on("/", []() {
      IPAddress ip = WiFi.localIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      server.send(200, "application/json", "{\"IP\":\"" + ipStr + "\"}");
    });
    server.on("/cleareeprom", []() {
      content = "<!DOCTYPE HTML>\r\n<html>";
      content += "<p>Clearing the EEPROM</p></html>";
      server.send(200, "text/html", content);
      Serial.println("clearing eeprom");
      for (int i = 0; i < 96; ++i) { EEPROM.write(i, 0); }
      EEPROM.commit();
    });
  }
}

bool testWifi(void) {
  int c = 0;
  Serial.println("Waiting for Wifi to connect to ESP8266");  
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED) { return true; } 
    delay(500);
    Serial.print(WiFi.status());    
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
} 

void setParams()
{
  delay(1);
  hour_set_on=server.arg("hour_on").toInt();
  minutes_set_on=server.arg("minutes_on").toInt();
  hour_set_off=server.arg("hour_off").toInt();
  minutes_set_off=server.arg("minutes_off").toInt();
  
  hour_set_on_morning=server.arg("hour_on_morning").toInt();
  minutes_set_on_morning=server.arg("minutes_on_morning").toInt();
  hour_set_off_morning=server.arg("hour_off_morning").toInt();
  minutes_set_off_morning=server.arg("minutes_off_morning").toInt();

  if(server.arg("hours_1") == "on")
  {
    Serial.println("Set first_hours");
    first_hours = true;

    first_hours_state = "\xE2\x9C\x93";
    first_hours_state.toCharArray(first_hours_state_char,16);
  }
  else 
  {
    Serial.println("Unset first_hours");
    first_hours = false;
    first_hours_state = "\u2718";
    first_hours_state.toCharArray(first_hours_state_char,16);

  }

  if(server.arg("hours_2") == "on")
  {
    Serial.println("Set second_hours");
    second_hours = true;
    second_hours_state = "\xE2\x9C\x93";
    second_hours_state.toCharArray(second_hours_state_char,16);
  }
  else 
  {
    Serial.println("Unset second_hours");
    second_hours = false;
    second_hours_state = "\u2718";
    second_hours_state.toCharArray(second_hours_state_char,16);
    
  }
  
  handleRoot();

  /*
  //NTPch.printDateTime(dateTime);
  digitalWrite(PIN_LED, 1);
  char temp[2048];
  byte hr = timeClient.getHours();
  byte min = timeClient.getMinutes();
  byte sec = timeClient.getSeconds();

  snprintf(temp, 2048,

           "<html>\
  <head>\
    <meta charset='UTF-8' http-equiv='refresh' content='20'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p>Czas: %02d:%02d:%02d</p>\
    <p>Godzina wlaczenia: %02d:%02d</p> \
    <p>Godzina wylaczenia: %02d:%02d</p>\
    </br>\
    <p>Godzina wlaczenia: %02d:%02d</p> \
    <p>Godzina wylaczenia: %02d:%02d</p>\
    <form action='/setting' method='get'>\
    <p>Zmien godzine wlaczenia/wylaczenia</p> \
    <input type='submit' value='Ustawienia' href=/setting />\
    </form>\
    </br></br>\
    <form action='/manual' method='get'>\
    <p>Ustaw recznie</p>\
    <input type='submit' value='ON/OFF' href=/manual/>\
    </form>\
    </br></br>\
  </body>\
</html>",

           hr, min % 60, sec % 60,hour_set_on,minutes_set_on,hour_set_off,minutes_set_off,hour_set_on_morning,minutes_set_on_morning,hour_set_off_morning,minutes_set_off_morning
          );
  delay(1);
  server.send(200, "text/html", temp);
  */
}

void handleMANUAL()
{
    char temp[2048];
    if(realy == RELAY_ON)
    {
        snprintf(temp, 2048,

           "<html>\
  <head>\
    <meta charset='UTF-8' http-equiv='refresh' content='20'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Światło jest obecnie włączone </h1>\
    </br></br>\
     <svg xmlns='http://www.w3.org/2000/svg' width='200' height='200' fill='currentColor' class='bi bi-brightness-high' viewBox='0 0 16 16'>\
  <path d='M8 11a3 3 0 1 1 0-6 3 3 0 0 1 0 6zm0 1a4 4 0 1 0 0-8 4 4 0 0 0 0 8zM8 0a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-1 0v-2A.5.5 0 0 1 8 0zm0 13a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-1 0v-2A.5.5 0 0 1 8 13zm8-5a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1 0-1h2a.5.5 0 0 1 .5.5zM3 8a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1 0-1h2A.5.5 0 0 1 3 8zm10.657-5.657a.5.5 0 0 1 0 .707l-1.414 1.415a.5.5 0 1 1-.707-.708l1.414-1.414a.5.5 0 0 1 .707 0zm-9.193 9.193a.5.5 0 0 1 0 .707L3.05 13.657a.5.5 0 0 1-.707-.707l1.414-1.414a.5.5 0 0 1 .707 0zm9.193 2.121a.5.5 0 0 1-.707 0l-1.414-1.414a.5.5 0 0 1 .707-.707l1.414 1.414a.5.5 0 0 1 0 .707zM4.464 4.465a.5.5 0 0 1-.707 0L2.343 3.05a.5.5 0 1 1 .707-.707l1.414 1.414a.5.5 0 0 1 0 .708z'/>\
</svg>\
</br></br>\
    <form action='/off' method='get'>\
    <input type='submit' value='Zmień' href=/off />\
    </form>\
    </br></br>\
    </form>\
    <form action='/' method='get'>\
    <input type='submit' value='Home' href=/ />\
    </form>\
    </br></br>\
  </body>\
</html>"
          );
  delay(1);
  server.send(200, "text/html", temp);
    } 
    else if (realy == RELAY_OFF)
    {
      snprintf(temp, 2048,

           "<html>\
  <head>\
    <meta charset='UTF-8' http-equiv='refresh' content='20'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Światło jest obecnie wyłączone </h1>\
    </br></br>\
    <svg xmlns='http://www.w3.org/2000/svg' width='200' height='200' fill='currentColor' class='bi bi-brightness-high-fill' viewBox='0 0 16 16'>\
  <path d='M12 8a4 4 0 1 1-8 0 4 4 0 0 1 8 0zM8 0a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-1 0v-2A.5.5 0 0 1 8 0zm0 13a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-1 0v-2A.5.5 0 0 1 8 13zm8-5a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1 0-1h2a.5.5 0 0 1 .5.5zM3 8a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1 0-1h2A.5.5 0 0 1 3 8zm10.657-5.657a.5.5 0 0 1 0 .707l-1.414 1.415a.5.5 0 1 1-.707-.708l1.414-1.414a.5.5 0 0 1 .707 0zm-9.193 9.193a.5.5 0 0 1 0 .707L3.05 13.657a.5.5 0 0 1-.707-.707l1.414-1.414a.5.5 0 0 1 .707 0zm9.193 2.121a.5.5 0 0 1-.707 0l-1.414-1.414a.5.5 0 0 1 .707-.707l1.414 1.414a.5.5 0 0 1 0 .707zM4.464 4.465a.5.5 0 0 1-.707 0L2.343 3.05a.5.5 0 1 1 .707-.707l1.414 1.414a.5.5 0 0 1 0 .708z'/>\
</svg>\
</br></br>\
    <form action='/on' method='get'>\
    <input type='submit' value='Zmień' href=/on />\
    </form>\
    </br></br>\
    </form>\
    <form action='/' method='get'>\
    <input type='submit' value='Home' href=/ />\
    </form>\
    </br></br>\
  </body>\
</html>"
          );
      delay(1);    
      server.send(200, "text/html", temp);      
    }
}  

void handleSETTING()
{
  char temp[2048];

  snprintf(temp, 2048,

           "<html>\
  <head>\
    <meta charset='UTF-8' http-equiv='refresh' content='20'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>USTAWIENIA!</h1>\
    </br></br>\
    <div class='alert alert-warning' role='alert' style='background-color:#ffff00;'>\
       UWAGA! Różnica pomiędzy czasem włączenia a czasem wyłączenia musi wynosić conajmniej minutę\
    </div>\
    </br></br>\
    <h3>Zmień pierwszą godzinę włączenia/wyłączenia</h3> \
    <h4>Włącz o:</h4>\
    <form action='/set' method='get'>\
    <input type='number' name='hour_on'></input>\
    <input type='number' name='minutes_on'></input>\
    </br></br>\
    <h4>Wyłącz o:</h4>\
    <input type='number' name='hour_off'></input>\
    <input type='number' name='minutes_off'></input>\
    </br></br></br>\
    <h3>Zmień drugą godzinę włączenia/wyłączenia</h3> \
    <h4>Włącz o:</h4>\
    <input type='number' name='hour_on_morning'></input>\
    <input type='number' name='minutes_on_morning'></input>\
    </br></br>\
    <h4>Wyłącz o:</h4>\
    <input type='number' name='hour_off_morning'></input>\
    <input type='number' name='minutes_off_morning'></input>\
    </br></br>\
    <h4>Ustaw godziny włączenia/wyłączenia</h4>\
    <input type='checkbox' id='hours_1' name='hours_1'></input>\ 
    <label for='hours_1'>Pierwsze</label>\
    <input type='checkbox' id='hours_2' name='hours_2'></input>\
    <label for='hours_2'>Drugie</label>\
    </br></br>\
    <input type='submit' value='Ustaw' href=/set?hour_on=&minutes_on&hour_off&minutes_off&hour_on_morning=&minutes_on_morning&hour_off_morning&minutes_off_morning&hours_1&hours_2/>\
    </form>\
    </br></br>\
    </form>\
    <form action='/' method='get'>\
    <input type='submit' value='Home' href=/ />\
    </form>\
    </br></br>\
    </br></br>\
  </body>\
</html>"
          );
  delay(1);        
  server.send(200, "text/html", temp);

}


  
void handleRoot() {
  delay(1);
  //NTPch.printDateTime(dateTime);
  digitalWrite(PIN_LED, 1);
  char temp[2048];
  byte hr = timeClient.getHours();
  byte min = timeClient.getMinutes();
  byte sec = timeClient.getSeconds();
  
  snprintf(temp, 2048,

           "<html>\
  <head>\
    <meta charset='UTF-8' http-equiv='refresh' content='20'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <h3>Adres urządzenia: %s </h3>\
    <p>Czas: %02d:%02d:%02d</p>\
    </br>\
    <p>Pierwszy przedział: %s</p>\
    <p>Godzina włączenia: %02d:%02d</p> \
    <p>Godzina wyłączenia: %02d:%02d</p>\
    </br>\
    <p>Drugi przedział: %s</p>\
    <p>Godzina włączenia: %02d:%02d</p> \
    <p>Godzina wyłączenia: %02d:%02d</p>\
    <form action='/setting' method='get'>\
    <p>Zmień godzinę włączenia/wyłączenia</p> \
    <input type='submit' value='Ustawienia' href=/setting />\
    </form>\
    </br></br>\
    <form action='/manual' method='get'>\
    <p>Ustaw ręcznie</p>\
    <input type='submit' value='ON/OFF' href=/manual/>\
    </form>\
    </br></br>\
  </body>\
</html>",

  
           ip_address_esp_char ,hr, min % 60, sec % 60,first_hours_state_char,hour_set_on,minutes_set_on,hour_set_off,minutes_set_off,second_hours_state_char,hour_set_on_morning,minutes_set_on_morning,hour_set_off_morning,minutes_set_off_morning
          );
  delay(1);        
  server.send(200, "text/html", temp);
  digitalWrite(PIN_LED, 0);
}


void handleNotFound() {
  digitalWrite(PIN_LED, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  delay(1);
  server.send(404, "text/plain", message);
  digitalWrite(PIN_LED, 0);
}

void handleApiOn()
{
  delay(1);
  digitalWrite(RELAY,HIGH);
  stan = "ON";
  realy = RELAY_ON;
  server.send(200, "application/json", "{\"relay\": \"ON\"}");
}

void handleApiOff()
{
  delay(1);
  digitalWrite(RELAY,LOW);
  stan = "OFF";
  realy = RELAY_OFF;
  server.send(200, "application/json", "{\"relay\": \"OFF\"}");
}

void handleON()
{
  delay(1);
  digitalWrite(RELAY,HIGH);
  stan = "ON";
  realy = RELAY_ON;
  handleMANUAL();
}

void handleOFF()
{
  delay(1);
  digitalWrite(RELAY,LOW);
  stan = "OFF";
  realy = RELAY_OFF;
  handleMANUAL();
}
void drawGraph() {
  delay(1);
  String out;
  out.reserve(2600);
  char temp[70];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x += 10) {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send(200, "image/svg+xml", out);
}    

void loop() {


  // first parameter: Time zone in floating point (for India); second parameter: 1 for European summer time; 2 for US daylight saving time; 0 for no DST adjustment; (contributed by viewwer, not tested by me)
  timeClient.update();

  /*
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  */
  delay(1);

  byte actualHour = timeClient.getHours();
  byte actualMinute = timeClient.getMinutes();
  byte actualsecond = timeClient.getSeconds();

  
    delay(1);
    if ((actualHour == hour_set_on &&  actualMinute == minutes_set_on && realy == RELAY_OFF && first_hours == true) || (actualHour == hour_set_on_morning &&  actualMinute == minutes_set_on_morning && realy == RELAY_OFF && second_hours == true))
    {
      if(realy_changed==false)
      {
        Serial.println("WLACZONE SWIATLO  ON!");
        digitalWrite(RELAY,HIGH);
        stan = "ON";
        realy = RELAY_ON;
        realy_changed=true;
      }
    }
    else if ((actualHour == hour_set_off && actualMinute == minutes_set_off && realy == RELAY_ON && first_hours == true) || (actualHour == hour_set_off_morning && actualMinute == minutes_set_off_morning && realy == RELAY_ON && second_hours == true))
    {
      if(realy_changed==false)
      {
      Serial.println("WYLACZONE SWIATLO  OFF!");
      digitalWrite(RELAY,LOW);
      stan = "OFF";
      realy = RELAY_OFF;
      realy_changed=true;
      }
    }
    else if ((actualHour != hour_set_on || actualMinute != minutes_set_on) && (actualHour != hour_set_on_morning || actualMinute != minutes_set_on_morning) && (actualHour != hour_set_off || actualMinute != minutes_set_off) && (actualHour != hour_set_off_morning || actualMinute != minutes_set_off_morning)  )
    {
      realy_changed=false;
    }
    delay(1);
    server.handleClient();
    //MDNS.update();
  
}
