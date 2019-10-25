#include <OneWire.h>
#include <DallasTemperature.h>

const int refreshWait = 2500;
const int tempGoodIfBelow = 60;
const int tempOkIfBelow = 80;

// GPIOs
const int tempBus = 33;
const int rgbRPin = 19;
const int rgbGPin = 18;
const int rgbBPin = 5;

// TempSensor Stuff
OneWire oneWire(tempBus);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();

  pinMode(rgbRPin, OUTPUT);
  pinMode(rgbGPin, OUTPUT);
  pinMode(rgbBPin, OUTPUT);  
}

void loop() {
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
