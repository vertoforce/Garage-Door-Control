#include "servo.h"

const size_t callbacks_size = 2;
RPC_Callback callbacks[callbacks_size] = {
    {"set_servo", setServo},
    {"press_button", pressButton}};

bool subscribed = false;

void subscribe() {
    if (subscribed) {
        return;
    }

    Serial.println("Subscribing for RPC...");

    if (!tb.RPC_Subscribe(callbacks, callbacks_size)) {
        Serial.println("Failed to subscribe for RPC");
        return;
    }

    Serial.println("Subscribe done");
    subscribed = true;

    return;
}