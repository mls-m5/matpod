#include "wifi.h"
#include "../matpod_config.h"
#include <WiFi.h>

void wifi::connect() {
    WiFi.begin(ssid, password);
}
