#include <FirebaseESP32.h>
#include  <WiFi.h>
#include "DHT.h"
#define FIREBASE_HOST "-----your firebase host-----"
#define WIFI_SSID "--- your wifi ssid ---" // Change the name of your WIFI
#define WIFI_PASSWORD "--- your wifi password ---" // Change the password of your WIFI
#define FIREBASE_Authorization_key "--- your key that you generated from firebase ---"
#define DHTPIN 16
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
FirebaseData firebaseData;
FirebaseJson json;

void setup() {
  Serial.begin(9600);
   dht.begin();
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);

  
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex( h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C ")); //°
  //Serial.print(f);
  //Serial.print(F("F  Heat index: ")); //°
  //Serial.print(hic);
  Serial.println(F("C ")); //°
  //Serial.print(hif);
  //Serial.println(F("°F"));
  Firebase.setFloat(firebaseData, "/ESP32_APP/TEMPERATURE", t);
  Firebase.setFloat(firebaseData, "/ESP32_APP/HUMIDITY", h);
}