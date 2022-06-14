/*
   This sketch shows an example of sending a reading to data.sparkfun.com once per day.
   It uses the Sparkfun testing stream so the only customizing required is the WiFi SSID and password.
   The Harringay Maker Space
   License: Apache License v2
*/
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <NTPClient.h>
#include <OneWire.h>

#define DEBUG_ON
#define PIN_LED BUILTIN_LED
//#define RELAY D8
bool isMeasuring = false;
const long utcOffsetInSeconds = 7200;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
OneWire  ds(D7);  // on pin 10 (a 4.7K resistor is necessary)

const char* ssid = "blank";               // Set you WiFi SSID
const char* password = "blank";              // Set you WiFi password
String ip_address_esp;
char ip_address_esp_char[16];

String condition;
float  temperatur_value;
String  api;
String  device_ip_address;

int httpResponseCode;

bool condition_set = false;

byte i;
byte present = 0;
byte type_s;
byte data[9];
byte addr[8];
float celsius, fahrenheit;
  

String st;
String content;
int statusCode;

bool realy = false;
String stan = "ON";
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
  WiFi.softAP("ESP_temp_sensor", "password");


  Serial.println("WiFi connected");

  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  ip_address_esp = WiFi.localIP().toString();

  ip_address_esp.toCharArray(ip_address_esp_char, 16);
  Serial.println(ip_address_esp_char);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  pinMode(PIN_LED, OUTPUT);
  //pinMode(RELAY,OUTPUT);


  server.on("/", handleRoot);
  server.on("/set", setParams);
  server.on("/setting", handleSETTING);
  server.on("/test.svg", drawGraph);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

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
  WiFi.softAP("ESP_temp_sensor", "password");
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

void conditionError()
{
  digitalWrite(PIN_LED, 1);
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
    <h1>BŁĄD</h1>\
    <h3>Błędny warunek. Wróć na poprzednią stronę i wpisz jeden z wymienionych znaków: < > = </h3>\
    <form action='/' method='get'>\
    <input type='submit' value='Home' href=/ />\
    </form>\
    </br></br>\
  </body>\
</html>"
          );
digitalWrite(PIN_LED, 0);
delay(1);
server.send(200, "text/html", temp);
}

void setParams()
{
  if(isMeasuring == false){
  // /set?condition=&temperatur_value&api&device_ip_address/>\
  delay(1);
  condition=server.arg("condition");
  temperatur_value=server.arg("temperatur_value").toInt();
  api=server.arg("api");

  char device_ip_address_char[16];
  device_ip_address=server.arg("device_ip_address");

  device_ip_address.toCharArray(device_ip_address_char, 16);

  condition_set = true;
  

  //NTPch.printDateTime(dateTime);
  digitalWrite(PIN_LED, 1);
  char temp[2048];
  byte hr = timeClient.getHours();
  byte min = timeClient.getMinutes();
  byte sec = timeClient.getSeconds();

 snprintf(temp, 2048,

           "<html>\
  <head>\
    <meta charset='UTF-8'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    </br></br>\
    <h2>Ustawiono warunek: Gdy temperatura %s %.2f</h2>\
    <h2>Wyslij: %s%s </h2>\
    </br></br>\
    <h3>Adres urzadzenia: %s </h3>\
    </br></br>\
    <p>Czas: %02d:%02d:%02d</p>\
    </br></br>\
    <p>Temperatura: %.2f &deg C </p> \
    </br></br>\
    <form action='/setting' method='get'>\
    <p>Ustaw akcje</p> \
    <input type='submit' value='Ustawienia' href=/setting />\
    </form>\
    </br></br>\
    <form action='/' method='get'>\
    <p>Wróć do menu głównego</p> \
    <input type='submit' value='Home' href=/ />\
    </form>\
    </br></br>\
  </body>\
</html>",

  
           condition,temperatur_value,device_ip_address_char,api,ip_address_esp_char ,hr, min % 60, sec % 60,celsius
          );
  delay(1);
  server.send(200, "text/html", temp);
  }
}

void handleMANUAL()
{
    char temp[2048];
    if(realy == true)
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
    <h1>Swiatlo jest obecnie: ON </h1>\
    </br></br>\
    <form action='/off' method='get'>\
    <input type='submit' value='Zmien' href=/off />\
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
    else if (realy == false)
    {
      snprintf(temp, 2048,

           "<html>\
  <head>\
    <meta http-equiv='refresh' content='20'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Swiatlo jest obecnie: OFF </h1>\
    </br></br>\
    <form action='/on' method='get'>\
    <input type='submit' value='Zmien' href=/on />\
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
    <h2>Ustaw warunek</h2> \
    <p>Przyklad: Temperatura > 25 /on 192.168.1.44</p>\
    <form action='/set' method='get'>\
    Temperatura <input type='text' name='condition'></input>\
    <input type='number' name='temperatur_value'></input>\
    </br></br>\
    <h2>Ustaw urzadzenie docelowe</h2> \
    <input type='text' name='api'></input>\
    <input type='text' name='device_ip_address' placeholder='xxx.xxx.xxx.xxx'/></input>\
    </br></br></br>\
    <input type='submit' value='Ustaw' href=/set?condition=&temperatur_value&api&device_ip_address/>\
    </form>\
    </br></br>\
    </form>\
    </br></br>\
    <form action='/' method='get'>\
    <p>Wróć do menu głównego</p> \
    <input type='submit' value='Home' href=/ />\
    </form>\
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
    <div>\
    <svg  style='vertical-align: middle;' xmlns='http://www.w3.org/2000/svg' width='200' height='200' fill='currentColor' class='bi bi-thermometer-half' viewBox='0 0 16 16'>\
    <path d='M9.5 12.5a1.5 1.5 0 1 1-2-1.415V6.5a.5.5 0 0 1 1 0v4.585a1.5 1.5 0 0 1 1 1.415z'/>\
    <path d='M5.5 2.5a2.5 2.5 0 0 1 5 0v7.55a3.5 3.5 0 1 1-5 0V2.5zM8 1a1.5 1.5 0 0 0-1.5 1.5v7.987l-.167.15a2.5 2.5 0 1 0 3.333 0l-.166-.15V2.5A1.5 1.5 0 0 0 8 1z'/>\
    </svg>\
    </div>\
    </br></br>\
    <p>Czas: %02d:%02d:%02d</p>\
    </br></br>\
    <p>Temperatura: %.2f &deg C </p> \
    </br></br>\
    <form action='/setting' method='get'>\
    <p>Ustaw akcje</p> \
    <input type='submit' value='Ustawienia' href=/setting />\
    </form>\
    </br></br>\
    </br></br>\
  </body>\
</html>",

  
           ip_address_esp_char ,hr, min % 60, sec % 60,celsius
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

void sendCMD(){
if(WiFi.status()== WL_CONNECTED){
      
      WiFiClient client;
      HTTPClient http;

      String serverPath = "http://" + device_ip_address+api;
      //String serverPath = "http://192.168.1.1";

      Serial.print("serverPath: ");
      Serial.println(serverPath.c_str());

      // Your Domain name with URL path or IP address with path
      http.begin(client,serverPath);
      
      // Send HTTP GET request
      httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }

}

void loop() {


  // first parameter: Time zone in floating point (for India); second parameter: 1 for European summer time; 2 for US daylight saving time; 0 for no DST adjustment; (contributed by viewwer, not tested by me)
  isMeasuring=true;
  timeClient.update();

  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  delay(1);

  byte actualHour = timeClient.getHours();
  byte actualMinute = timeClient.getMinutes();
  byte actualsecond = timeClient.getSeconds();

  
    if ( !ds.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    //return;
  }
  
  Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      //return;
  }
  Serial.println();
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      //return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  Serial.print("  Data = ");
  Serial.print(present, HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");

  celsius == 40;
  isMeasuring=false;
  if(condition_set==true)
  {
    if(condition == "<")
    {
      if (celsius < temperatur_value)
      {
        sendCMD();
      }
    }
    if(condition == ">")
    {
      if (celsius > temperatur_value)
      {
        sendCMD();
      }
    }
    if(condition == "=")
    {
      if (celsius = temperatur_value)
      {
        sendCMD();
      }
    }
    
  }
  
  delay(1);
  server.handleClient();
    
  
}
