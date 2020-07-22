#define BLYNK_PRINT Serial
 
 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Servo.h>
Servo servo;
 
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "929a265008254f2bbaaf5dc7bf18b453";
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "homeautosensor";
char pass[] = "homeautosensor";
 
#define DHTPIN 0          // D3
 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301
 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
 
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}
 
void setup()
{
  // Debug console
  Serial.begin(9600);
 
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
  dht.begin();
 
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  servo.attach(15); 
}
 
void loop()
{
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V1)
{
   servo.write(param.asInt());
}

BLYNK_WRITE(V2)
{
  servo.write(90);
}
BLYNK_WRITE(V3)
{
  servo.write(180);
}
BLYNK_WRITE(V4)
{
  servo.write(0);
}
