#include <ThingsBoard.h>
#include <Servo.h>

#define RELAY_PIN 12

void setup_relay() {
    // Set relay pin
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
}

// Push the relay for the fixed delay
RPC_Response pushRelay(const RPC_Data &data) { 
    digitalWrite(RELAY_PIN, HIGH);
    delay(800);
    digitalWrite(RELAY_PIN, LOW);
    return RPC_Response("response", 0);
}
