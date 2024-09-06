#include "udp.h"
#include "../matpod_config.h"
#include "AsyncUDP.h"
#include "control.h"
#include <Arduino.h>

namespace udp {

unsigned long previousMillis = 0; // Will store last time message was sent
const long interval = 5000; // Interval at which to send message (5 seconds)

AsyncUDP udp;

void init() {
    Serial.println("init udp server");

    udp.listen(8088);

    udp.onPacket([](AsyncUDPPacket packet) {
        if (wifi::controllerType == wifi::HeliController) {
            char buffer[30];
            auto size = packet.readBytesUntil('\n', buffer, 30);
            auto x = atof(buffer);

            size = packet.readBytesUntil('\n', buffer, 30);
            auto y = atof(buffer);

            Control::instance().x = x;
            Control::instance().y = y;

            Serial.println("receive package");
            Serial.println(x);
            Serial.println(y);
        }
        else {
#error "continue here"
        }
    });
}

void handleSubscribe() {
    if (wifi::controllerType == wifi::HeliController) {
        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;

            if (udp.connect(IPAddress(192, 168, 4, 1), 8088)) {
                udp.print("subscribe 8088");
                Serial.println("Sent subscribe 8088 to 192.168.4.1");
            }
            else {
                Serial.println("Failed to connect to 192.168.4.1");
            }
        }
    }
}

} // namespace udp
