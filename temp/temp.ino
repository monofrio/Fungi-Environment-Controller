#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

 const char* ssid      = "BoardGameZone-5G-Guest";       // SSID
 const char* password  = "9147724158";   // Password
 const char* host      = "http://www.markonofrio.com";              // website
int sensorPin = A0; //the analog pin

WiFiServer server(80);
#define TEST_DELAY   5000

// this will store the temperature
float temperature;

void connect(){
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
void setup(){
  Serial.begin(115200);
  // I like to set the temperature to all zeros to start
  temperature = 0000;
  connect();
}
void loop(){

  int reading = analogRead(sensorPin); // current voltage off the sensor
  float voltage = reading * 3.3; // using 3.3v input
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree with 500 mV offset
                                       //to degrees C ((voltage - 500mV) times 100)
  int temperatureF = (temperatureC * 9 / 5 + 32 ) ;
  // not really necessary, just feels right to me to have a nice clean temperature variable :)
  temperature = temperatureF;

  /// Use WiFiClient class to create TCP connections
  WiFiClient client;

  // port = 80 for web stuffs
  const int httpPort = 80;

  // try out that connection plz
  if (!client.connect(host, httpPort)) {
    return;
  }

  String url = "/fungi_controller/write.php?fahrenheit=";
  url += String(temperature);

//  Serial.print("requesting URL: ");
//  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               //"Content-Type: application/x-www-form-urlencoded" +
               "Connection: close\r\n\r\n");
 Serial.println("request sent ");
 Serial.println(temperature);
 
  // unless you want to hammer your website, you need to put in a delay
  delay(TEST_DELAY);

}
