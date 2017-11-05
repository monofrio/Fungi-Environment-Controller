/* Fungi Environment Controller
   Hardwear:
    - DHT-22 Sensor - code from: http://www.ardumotive.com/how-to-use-dht-22-sensor-en.html
    - MQ-135 Gas Sensor - code from: http://microcontrollerslab.com/interfacing-mq-135-gas-sensor-arduino/#Code_for_interfacing_ofMQ-135_gas_sensor_with_Arduino
    - Arduino Uno
    
    ## Sample data from inside the tank
    - Air Quality: 19 %, Humidity: 28.70 %, Temp: 77.72 Fahrenheit, 11pm 10-4-17 
    
    ## Progjects TODO.
    - Make a 12 powersuppply 
    - - Transformer down to 5v to power Arduino 
    - Set up Relay with Pin 7 To improve Air Quality
    - Set up heater for Tank
    - Set up humidifier
*/

int sensorValue;
int digitalValue;

int redLed = 13;
int greenLed = 12;

//Libraries
#include <dht.h> 
dht DHT;
//Constants
#define DHT22_PIN 2     // DHT 22  (AM2302) - what pin we're connected to
#define RELAY1  7       

//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup()
{
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  //pinMode(RELAY1, OUTPUT); 
  Serial.begin(9600);      // sets the serial port to 9600
}

void loop()
{
  sensorValue = analogRead(0);       // read analog input pin 0
  digitalValue = digitalRead(0);
  Serial.print("Air Quality: ");
  Serial.print(sensorValue, DEC);  // prints the value read
  //Serial.println(digitalValue, DEC); // not using

  /* - Air Quality Regulator -
     Setup with Red and Green LED Lights
  */
  //TODO: use this area to turn on a vent fan
  if (sensorValue > 19) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(RELAY1,LOW);           // Turns ON Relays 1
  }
  // Have MQ-135 Sensor control Air Quality
  if (sensorValue < 20) {
    digitalWrite(redLed, LOW);          // Turns Red light OFF
    digitalWrite(greenLed, HIGH);       // Turns Green Light ON
    digitalWrite(RELAY1,HIGH);          // Turns Relay Off
  }

  int chk = DHT.read22(DHT22_PIN);
  //Read data and store it to variables hum and temp  
  hum = DHT.humidity;
  temp = DHT.temperature;
  //Print temp and humidity values to serial monitor
  Serial.print(" %, Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp * 9 / 5 + 32 ); // converted to Fahrenheit... for Americans
  //Serial.println(" Celsius");
  Serial.println(" Fahrenheit");

  delay(10000); // wait 100ms for next reading
}



