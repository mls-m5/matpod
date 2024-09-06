#include "udp.h"
#include "../matpod_config.h"
#include "AsyncUDP.h"
#include "control.h"
#include "payload.h"
#include <Arduino.h>
#include <cstdint>

namespace udp {

unsigned long previousMillis = 0; // Will store last time message was sent
const long interval = 5000; // Interval at which to send message (5 seconds)

AsyncUDP udp;

void init() {
    Serial.println("init udp server");

    udp.listen(8088);

    udp.onPacket([](AsyncUDPPacket packet) {
        if (wifi::controllerType == wifi::OldController) {
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
            auto maxLen = sizeof(Payload);
            auto payload = Payload{};
            auto len =
                packet.read(reinterpret_cast<uint8_t *>(&payload), maxLen);
            if (len < maxLen) {
                Serial.println("invalid packet, to short");
                return;
            }

            Control::instance().x = payload.faxis(0);
            Control::instance().y = payload.faxis(3);
            // Serial.println("receive logic is disabled");

            Serial.println("receive package");
            Serial.println(Control::instance().x);
            Serial.println(Control::instance().y);
        }
    });
}

void handleSubscribe() {
    if (wifi::controllerType == wifi::HeliController) {
        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;

            if (udp.connect(IPAddress(192, 168, 4, 1), 30)) {
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
