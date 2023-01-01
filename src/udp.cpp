#include "udp.h"
#include "AsyncUDP.h"
#include "control.h"
#include <Arduino.h>

namespace udp {

AsyncUDP udp;

void init() {
    Serial.println("init udp server");

    udp.listen(8088);

    udp.onPacket([](AsyncUDPPacket packet) {
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
    });
}

} // namespace udp