#include <DHT.h>

// DHT
#define DHTPIN 15
#define DHTTYPE DHT22

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

double read_temp() {
    return dht.readHumidity();
}

double read_humidity() {
    return dht.readTemperature();
}

extern ThingsBoard tb;

// read the temperature and submit it to thingsboard
void submitTemp() {
    double temp = read_temp();
    Serial.println(temp);
    tb.sendTelemetryFloat("temperature", temp);
}

unsigned long lastSentTemp;

// Read and submit temp to thingsboard only if we haven't in the last
// submitInterval time
void submitTempScheduled() {
    if ((millis() - lastSentTemp) > SUBMIT_INTERVAL) {
        submitTemp();
        lastSentTemp = millis();
    }
}