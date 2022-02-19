#include "wifi.h"
#include "../matpod_config.h"
#include "led.h"
#include <WiFi.h>

void wifi::connect() {
    if (!enabled) {
        return;
    }

    Serial.printf("connecting to %s ", ssid);

    WiFi.begin(ssid, password);
    WiFi.hostname(hostname);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    led::flash();

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
