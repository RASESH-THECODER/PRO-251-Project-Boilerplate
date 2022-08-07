#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#define DHTPIN 19
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "KhageshGandhi_2.4G"
#define WLAN_PASS       "9820334411"
/****************************************************************************/

Adafruit_BMP085 bmp;
String serverName="http://192.168.1.9:5000/add-data"

void setup()
{
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (!bmp.begin())
  {
    Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
    while (1) {}
  }
  dht.begin();
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClient client;
    HTTPClient http;

    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    float h = dht.readHumidity();
    http.begin(serverName);
    http.addHeader("content-type","application/json");
    Serial.print("http response code");
    http.end();
//    Serial.println(http response code);

    
//    if (isnan(h))
//    {
//      Serial.println("Failed to read from DHT sensor!");
//      return;
//    }
//    else
//    {
//      Serial.print("Humidity: ");
//      Serial.print(h);
//    }
//
//  }
//  else 
//  {
//    Serial.println("WiFi Disconnected");
//  }

  delay(5000);
}
