#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define MQ2_PIN   A0
#define MQ135_PIN A1

DHT dht(DHTPIN, DHTTYPE);

unsigned long lastMs = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();

 
  delay(2000); 
}

void loop() {
 
  if (millis() - lastMs < 1000) return;
  lastMs = millis();

  int mq2_raw = analogRead(MQ2_PIN);       
  int mq135_raw = analogRead(MQ135_PIN);  

  float hum = dht.readHumidity();
  float temp = dht.readTemperature(); 
  
  bool dht_ok = true;
  if (isnan(hum) || isnan(temp)) {
    dht_ok = false;
    hum = -1;
    temp = -1;
  }

  
  Serial.print("{\"mq2\":");
  Serial.print(mq2_raw);
  Serial.print(",\"mq135\":");
  Serial.print(mq135_raw);
  Serial.print(",\"temp\":");
  Serial.print(temp, 1);
  Serial.print(",\"hum\":");
  Serial.print(hum, 1);
  Serial.print(",\"dht_ok\":");
  Serial.print(dht_ok ? "true" : "false");
  Serial.println("}");
}

