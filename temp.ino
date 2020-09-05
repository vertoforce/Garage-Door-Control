#include <DHT.h>

// DHT
#define DHTPIN 13
#define DHTTYPE DHT22   

#define SUBMIT_INTERVAL 15000

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void dht_init() {
    Serial.println("init DHT");
    dht.begin();
}

float read_temp() {
    return dht.readTemperature();
}

float read_humidity() {
    return dht.readHumidity();
}

extern ThingsBoard tb;

// read the temperature and submit it to thingsboard
void submitData() {
    tb.sendTelemetryFloat("temperature", read_temp());
    tb.sendTelemetryFloat("humidity", read_humidity());
}

unsigned long lastSentTemp;

// Read and submit temp to thingsboard only if we haven't in the last
// submitInterval time
void submitTempScheduled() {
    if ((millis() - lastSentTemp) > SUBMIT_INTERVAL) {
        submitData();
        lastSentTemp = millis();
    }
}