#include "wifi.h"
#include "../matpod_config.h"
#include "led.h"
#include <WiFi.h>

namespace wifi {

void connect() {
    if (!enabled) {
        return;
    }

    Serial.printf("connecting to %s ", ssid);

    WiFi.begin(ssid, password);
    WiFi.hostname(hostname);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        led::blink();
    }

    led::flash();

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void check() {
    if (WiFi.status() != WL_CONNECTED) {
        connect();
    }
}

}