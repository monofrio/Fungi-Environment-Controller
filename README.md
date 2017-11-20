# Fungi-Environment-Controller

This project is to auto control air quality, humidity and temperature within a 10 gallon glass tank.  Using a custom fitted plexiglass top to maintain internal environment.

I started this project with Arduino Uno and wanted to connect the Arduino Uno to Wifi.
Now working with HiLetgo ESP8266 as a cheap alternative to connect to WiFi

## Hardware:
* DHT-22 Sensor - code from: http://www.ardumotive.com/how-to-use-dht-22-sensor-en.html
  * More info: http://www.ardumotive.com/how-to-use-dht-22-sensor-en.html
  * Download: http://www.ardumotive.com/uploads/1/2/7/2/12726513/dht22_tutorial.zip
* MQ-135 Gas Sensor - code from: http://microcontrollerslab.com/interfacing-mq-135-gas-sensor-arduino/#Code_for_interfacing_ofMQ-135_gas_sensor_with_Arduino
* ~~Arduino Uno~~
* HiLetgo ESP8266 NodeMCU
  * https://www.amazon.com/HiLetgo-Internet-Development-Wireless-Micropython/dp/B010O1G1ES
  * https://www.losant.com/blog/getting-started-with-the-esp8266-and-dht22-sensor
*  Mini ultrasonic humidifier
  * https://www.amazon.com/gp/product/B06XG8VPFY/ref=oh_aui_detailpage_o00_s00?ie=UTF8&psc=1
  * Voltage: DC 5v
  * Power: 2w
* Relay module

## Sample data from inside the tank
```
[Arduino Uno]
Air Quality: 19 %, Humidity: 28.70 %, Temp: 77.72 Fahrenheit, 11pm 10-4-17
[HiLetgo]
Humidity: 36.20 %	Temperature: 24.00 *C 75.20 *F	Heat index: 23.40 *C 74.12 *F
```

## Task List.
- [X] Set up ESP8266 with DHT-22 sensor
- [X] Set up ESP8266 With MQ-135 sensor
- [ ] Set up ESP8266 to database
- [X] Set up humidifier
- [ ] Set up heater for Tank
## TODO
- [ ] Build Shield for all the components
