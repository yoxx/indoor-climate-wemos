// Library includes
#include "DHTesp.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>

// Define DHT sensor
DHTesp dht;

// Define input voltage
#define VOLTAGE 3.3
/// The load resistance on the board
#define RLOAD 10.0
/// Parameters for calculating ppm of CO2 from sensor resistance
#define MQ135_SCALINGFACTOR 116.6020682
#define MQ135_EXPONENT -2.769034857
#define MQ135_RO 1177.10 // Use the determine RO script based on a "calibrated" sensor

// Google stuff
WiFiClientSecure client;
const int httpsPort = 443;
const char* G_FINGERPRINT = "CD CF 65 23 DC 03 A8 89 C9 96 49 50 48 1F 3A B9 65 1B 75 B9";
const String GSSID = "<GOOGLE_SHEETS_ID"; // Replace with your own Google sheets ID
const char* host = "script.google.com";

// Network SSID
const char* ssid = "<SSID>"; // Replace with your own SSID
const char* password = "<PASSWORD>"; // Replace with your own SSID

void setup() 
{
  Serial.begin(9600);
  
  dht.setup(2, DHTesp::DHT22);
    // Connect WiFi
  WiFi.hostname("Name");
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Print the IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() 
{
  delay(dht.getMinimumSamplingPeriod());

  // Get Humidity and Temp
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

// Display values to SERIAL output
  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.print("%");
  Serial.print(" Temperature: ");
  Serial.print(temperature, 1);
  Serial.write(0xC2);
  Serial.write(0xB0);
  Serial.print("C");
  
  // Air Quality
  float analogSensorValue;
  float resistance;
  float CO2_ppm;
  float RO;
  float pow_co2;
  
  // Get the sensor value from the MQ135 sensor
  analogSensorValue = analogRead(A0);
  // Convert the analog value to a digital value 1023 for 5V 4095 for 3.3V
  resistance =  ((4095./(float)analogSensorValue) * VOLTAGE - 1.)*RLOAD;
  CO2_ppm = (float)MQ135_SCALINGFACTOR * pow((resistance/MQ135_RO), MQ135_EXPONENT);

  Serial.print(" CO2: ");
  Serial.print((int)CO2_ppm);
  Serial.println("ppm");
  
//  String url = "https://script.google.com/macros/s/" + GSSID + "/exec?temperature=" + String(temperature) + "&humidity=" + String(humidity) + "&ppm=" + String((int)CO2_ppm);

  Serial.print("connecting to ");
  Serial.println(host);
  client.setInsecure();
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(G_FINGERPRINT, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");    
    return;
  }
  String url = "/macros/s/" + GSSID + "/exec?temperature=" + String(temperature) + "&humidity=" + String(humidity) + "&ppm=" + String((int)CO2_ppm);
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
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
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
 
  delay(295000);    //Send a request every 5 mins
}
