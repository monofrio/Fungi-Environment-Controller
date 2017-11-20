// Librarys
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "MQ135.h"
// #include <Losant.h>

#define DHTPIN 4     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // There are multiple kinds of DHT sensors
#define ANALOGPIN A0

int humidiferController = D5;
int greenLed = D7;
int redLed = D6;
int timeSinceLastRead = 0;

int sensorValue;
int digitalValue;
float ppm, rzero;

DHT dht(DHTPIN, DHTTYPE);
MQ135 gasSensor = MQ135(ANALOGPIN);


// WiFi credentials.
#include "../../Fungi-Environment-Controller/WiFiCredentials.h"
WiFiClientSecure wifiClient;

void airSensor(){
//  sensorValue = analogRead(A0);       // read analog input pin 0
//  //digitalValue = digitalRead(A0);
//  Serial.print("Air Quality: ");
//  Serial.print(sensorValue, DEC);  // prints the value read
//  Serial.print(" /t ");
//  //Serial.println(digitalValue, DEC); // not using

rzero = gasSensor.getRZero(); //this to get the rzero value, uncomment this to get ppm value
  Serial.print("RZero=");
  Serial.println(rzero); // this to display the rzero value continuously, uncomment this to get ppm value
   
//  ppm = gasSensor.getPPM(); // this to get ppm value, uncomment this to get rzero value
//  Serial.print("PPM=");
//  Serial.println(ppm); // this to display the ppm value continuously, uncomment this to get rzero value
  

}
void humidityChecker() {
    float _humidity = dht.readHumidity();
    // Humidity checker
    if (_humidity < 80) {
      digitalWrite(humidiferController, LOW);
      Serial.print(" Humidity is bad - ");
      Serial.print(_humidity);
      Serial.print(" % \t ");
      delay(60000);
    }
    else {
      digitalWrite(humidiferController, HIGH);
      Serial.print("Humidity is good - ");
      Serial.print(_humidity);
      Serial.print(" % \t ");
    }
}
void sensorsChecker(){
  humidityChecker();
  airSensor();
}

void connect() {

  // Connect to Wifi.
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long wifiConnectStart = millis();

  while (WiFi.status() != WL_CONNECTED) {
    sensorsChecker();
    // Check to see if
    if (WiFi.status() == WL_CONNECT_FAILED) {
      Serial.println("Failed to connect to WIFI. Please verify credentials: ");
      Serial.println();
      Serial.print("SSID: ");
      Serial.println(WIFI_SSID);
      Serial.print("Password: ");
      Serial.println(WIFI_PASS);
      Serial.println();
    }

    delay(500);
    Serial.println("...");
    // Only try for 5 seconds.
    if(millis() - wifiConnectStart > 5000) {
      Serial.println("Failed to connect to WiFi");
      Serial.println("Please attempt to send updated configuration parameters.");
      return;
    }
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // http request

  Serial.println("Connected!");
  Serial.println();
  Serial.println("This device is now ready for use!");
}

void setup() {
  pinMode(greenLed, OUTPUT);     // Trun on humidifier on green light
  pinMode(redLed, OUTPUT);     // Turn off humidifier on red light
  pinMode(humidiferController, OUTPUT);

  Serial.begin(9600);
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while(!Serial) { }

  Serial.println("Device Started");
  Serial.println("-------------------------------------");
  Serial.println("Running DHT!");
  Serial.println("-------------------------------------");

  humidityChecker();
  connect();
}

void loop() {

   bool toReconnect = false;

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnected from WiFi");
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    toReconnect = true;
  }
  else{
    // Set LED lights to indicate when wifi is connected
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
  }

  //  if (!device.connected()) {
  //    Serial.println("Disconnected from MQTT");
  //    Serial.println(device.mqttClient.state());
  //    toReconnect = true;
  //  }

  if (toReconnect) {
    connect();
  }

  // Report every 2 seconds.
  if(timeSinceLastRead > 2000) {
    sensorsChecker();

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      timeSinceLastRead = 0;
      return;
    }

    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);

    Serial.print("Temperature: ");
    //Serial.print(t);
    //Serial.print(" *C ");
    Serial.print(f);
    Serial.print(" *F \t ");
    Serial.print("Heat index: ");
    //Serial.print(hic);
    //Serial.print(" *C ");
    Serial.print(hif);
    Serial.println(" *F ");
    //    report(h, t, f, hic, hif);
    timeSinceLastRead = 0;
  }
  delay(100);
  timeSinceLastRead += 100;
}
