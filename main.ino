#include <ESP8266WiFi.h>
#include <ThingsBoard.h>
#include <Servo.h>

#include "rpc.h"
#include "temp.h"
#include "wifi.h"

#define SUBMIT_INTERVAL 1000

// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD 115200

// Initialize ThingsBoard client
WiFiClient espClient;
// Initialize ThingsBoard instance
ThingsBoard tb(espClient);

extern Servo mainservo;
extern unsigned long lastSentTemp;

void setup() {
    // initialize serial for debugging
    Serial.begin(SERIAL_DEBUG_BAUD);
    ConnectToWifi();
    mainservo.attach(16);
    lastSentTemp = 0;
}

extern bool subscribed;

void loop() {
    // Make sure wifi is connected
    reconnect();

    // Make sure we are connected to TB
    tb_reconnect();

    // Make sure we are subscribed to RPC
    subscribe();

    // Submit temp data if we have to
    submitTempScheduled();

    tb.loop();
}

void tb_reconnect() {
    // Make sure TB is connected
    if (!tb.connected()) {
        subscribed = false;

        // Connect to the ThingsBoard
        Serial.print("Connecting to: ");
        Serial.print(THINGSBOARD_SERVER);
        Serial.print(" with token ");
        Serial.println(TOKEN);
        if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
            Serial.println("Failed to connect");
            return;
        }
    }
}