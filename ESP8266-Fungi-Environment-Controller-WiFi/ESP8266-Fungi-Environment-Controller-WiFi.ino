// Librarys
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include "MQ135.h"

#define DHTPIN D4     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // There are multiple kinds of DHT sensors
#define ANALOGPIN A0
#define RELAY1  D7
#define RELAY2  D8

const int humidiferController = RELAY1;
const int relay_2 = RELAY2;
const int greenLed = D6;
const int redLed = D5;

int timeSinceLastRead = 0;
int sensorTime = 0;

int sensorValue;
int digitalValue;
float ppm, rzero;

DHT dht(DHTPIN, DHTTYPE);
MQ135 gasSensor = MQ135(ANALOGPIN);

void setup() {
//  pinMode(greenLed, OUTPUT);     // Trun on humidifier on green light
//  pinMode(redLed, OUTPUT);     // Turn off humidifier on red light
  pinMode(humidiferController, OUTPUT);
  pinMode(relay_2, OUTPUT);
  
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(humidiferController, HIGH);
  digitalWrite(relay_2, LOW);

  Serial.begin(9600);
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while(!Serial) { }

  Serial.println("Device Started");
  Serial.println("-------------------------------------");
  Serial.println("Running DHT!");
  Serial.println("-------------------------------------");
}

void loop() {  
  // Report every 2 seconds.
  if(timeSinceLastRead > 2000) {

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);
    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      timeSinceLastRead = 0;
      return;
    }
       
    sensorValue = analogRead(A0);       // read analog input pin 0
    //digitalValue = digitalRead(A0);
    Serial.print("Air Quality: ");
    //Serial.print(sensorValue);  // prints the value read
    Serial.print(sensorValue, DEC);  // prints the value read
    Serial.print(" \t ");
    //Serial.println(digitalValue, DEC); // not using Digital Value 
    
//    rzero = gasSensor.getRZero(); //this to get the rzero value, uncomment this to get ppm value
//      Serial.print("RZero=");
//      Serial.print(rzero); // this to display the rzero value continuously, uncomment this to get ppm value
//      Serial.println();
//    ppm = gasSensor.getPPM(); // this to get ppm value, uncomment this to get rzero value
//      Serial.print("PPM=");
//      Serial.println(ppm); // this to display the ppm value continuously, uncomment this to get rzero value

    Serial.print("Temperature: ");
    //Serial.print(t);
    //Serial.print(" *C ");
    Serial.print(f);
    Serial.print(" *F \t ");
    Serial.print("Heat index: ");
    //Serial.print(hic);
    //Serial.print(" *C ");
    Serial.print(hif);
    Serial.print(" *F \t");
    //    report(h, t, f, hic, hif);
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println(" % \t ");  

/* Check Humidity */
    if ( h < 90  ) {
        digitalWrite(humidiferController, HIGH);
        sensorTime += 1;
        Serial.print("Sensor Time: ");
        Serial.println(sensorTime);
    }
    else if(   h > 90 || sensorTime > 10){ 
      digitalWrite(humidiferController, LOW);
      sensorTime = 0;
    }
/*  Controle Relay 2 / Fan
 *  Relay 2 seems to be no working correctly so need to set it as 
 *  On will turn off the fan. */
 
    if(sensorValue >= 150){
        Serial.println("FAN ON");
        digitalWrite(relay_2, HIGH);
      }
      if (sensorValue < 150){
        Serial.println("FAN OFF" );
        digitalWrite(relay_2, LOW);
//        sensorTime = 0;
      }
      
    timeSinceLastRead = 0;
    Serial.println(sensorTime);
  }
    delay(100);
    timeSinceLastRead += 100;
    
    
}
