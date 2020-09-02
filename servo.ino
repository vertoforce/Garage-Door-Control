#include <ThingsBoard.h>
#include <Servo.h>

Servo mainservo;

// Set the servo to the knob data
RPC_Response setServo(const RPC_Data &data) { 
    double value = data;
    mainservo.write(value);
    return RPC_Response("response", 0);
}

RPC_Response pressButton(const RPC_Data &data) { 
    mainservo.write(170);
    delay(500);
    mainservo.write(0);
    return RPC_Response("response", 0);
}