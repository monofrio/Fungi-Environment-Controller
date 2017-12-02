#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

 const char* ssid      = "Kram2";       // SSID
 const char* password  = "@dzam626!";   // Password
 const char* host      = "esp8266.markonofrio.com";              // website
int sensorPin = A0; //the analog pin
const int httpsPort = 443;

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



 // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }


  String url = "/fungi_controller/write.php?fahrenheit=";
  url += String(temperature);
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
  
  // unless you want to hammer your website, you need to put in a delay
  delay(TEST_DELAY);

}
