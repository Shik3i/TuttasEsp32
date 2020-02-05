#include <OneWire.h>
#include <DallasTemperature.h>
#include "esp_wpa2.h"
#include "WiFi.h"

//WiFi shit
// SSID to connect to
static const char *ssid = "MMBBS-Public";
// Username for authentification
#define EAP_ID "fiae19k.schmidt"
#define EAP_USERNAME "fiae19k.schmidt"
#define EAP_PASSWORD "undone-race-bring-sulfate"
WiFiServer server(80);

const int refreshWait = 1000;
const int tempGoodIfBelow = 25;
const int tempOkIfBelow = 26;

// GPIOs
const int tempBus = 33;
const int rgbRPin = 19;
const int rgbGPin = 18;
const int rgbBPin = 5; // Wird eigtl. nicht gebraucht
const int testWhite = 21; // Für Testzwecke

// TempSensor Stuff
OneWire oneWire(tempBus);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();

  pinMode(rgbRPin, OUTPUT);
  pinMode(rgbGPin, OUTPUT);
  pinMode(rgbBPin, OUTPUT);  
  pinMode(testWhite, OUTPUT);

  // WiFi Shit
  delay(500);
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ID, strlen(EAP_ID));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_USERNAME, strlen(EAP_USERNAME));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  esp_wifi_sta_wpa2_ent_enable(&config);
  WiFi.begin(ssid);
  // Wait for connection AND IP address from DHCP
  Serial.println();
  Serial.println("Waiting for connection and IP Address from DHCP");
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  // WiFi Shit
  WiFiClient clientS = server.available();
  if (clientS)
  {
      Serial.println("New Client");
      clientS.println("HTTP/1.0 200 OK");
      clientS.println("Content-type:text/html\n");
      clientS.println("<html><body bgcolor=\"#FFFF00\"><center><h1 style=\"font-size:160px;margin-bottom:-20;\">WORKS!</h1><h2 style=\"color:blue;\">Robin ist ein guter Klassensprecher!</h2></center></body></html>");
      clientS.flush();
      clientS.stop();
      toggleWhite();
  }

  // Temp Shit  
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  displayTemp(temperatureC);

  delay(refreshWait);
}


void displayTemp(float temp){
  rgbReset();
  if (temp <= tempGoodIfBelow){
    turnGreen();
  }else if(temp <= tempOkIfBelow){
    turnYellow();
  }else {
    turnRed();
  }
}

void turnGreen(void){
  digitalWrite(rgbGPin, HIGH);
}

void turnRed(void){
  digitalWrite(rgbRPin, HIGH);
}

void turnYellow(void){
  turnRed();
  turnGreen();
}

void rgbReset(void){
  digitalWrite(rgbRPin, LOW);
  digitalWrite(rgbGPin, LOW);
  digitalWrite(rgbBPin, LOW);
}

void toggleWhite(void){
  if (digitalRead(testWhite) == HIGH){
    digitalWrite(testWhite, LOW);
  } else {
    digitalWrite(testWhite, HIGH);
  }
}
