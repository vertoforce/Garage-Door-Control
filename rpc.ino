#include "relay.h"

const size_t callbacks_size = 1;
RPC_Callback callbacks[callbacks_size] = {
    {"push_relay", pushRelay}};

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