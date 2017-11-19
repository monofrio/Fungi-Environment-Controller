// Librarys
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// #include <Losant.h>

#define DHTPIN 4     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // There are multiple kinds of DHT sensors

int humidiferController = D7;
int greenLed = D6;
int redLed = D5;
int timeSinceLastRead = 0;

DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials.
#include "../../Fungi-Environment-Controller/WiFiCredentials.h"
WiFiClientSecure wifiClient;

// LosantDevice device(LOSANT_DEVICE_ID);

void humidityChecker() {
    float _humidity = dht.readHumidity();
    // Humidity checker
    if (_humidity < 80) {
      Serial.println("Humidity is bad - ");
      Serial.print(_humidity);
      Serial.print(" %\t");
      digitalWrite(humidiferController, HIGH);
    }
    else {
      Serial.println("Humidity is good - ");
      Serial.print(_humidity);
      Serial.print(" %\t");
      digitalWrite(humidiferController, LOW);          // Turns Red light OFF
    }
}
void sensorsChecker(){
  humidityChecker();
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

  //http request --

//  while(!device.connected()) {
//    delay(500);
//    Serial.print(".");
//  }

  Serial.println("Connected!");
  Serial.println();
  Serial.println("This device is now ready for use!");
}

void setup() {
  pinMode(greenLed, OUTPUT);     // Trun on humidifier on green light
  pinMode(redLed, OUTPUT);     // Turn off humidifier on red light

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
    Serial.print(" *F%\t");
    Serial.print("Heat index: ");
    //Serial.print(hic);
    //Serial.print(" *C ");
    Serial.print(hif);
    Serial.println(" *F");
//    report(h, t, f, hic, hif);
    timeSinceLastRead = 0;
  }
  delay(100);
  timeSinceLastRead += 100;
}
