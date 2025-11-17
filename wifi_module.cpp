#include "wifi_module.h"

SimpleWiFi::SimpleWiFi() {
    _ssid = nullptr;
    _password = nullptr;
}

bool SimpleWiFi::connect(const char* ssid, const char* password, int maxAttempts) {
    _ssid = ssid;
    _password = password;
    
    WiFi.begin(ssid, password);
    Serial.print("Подключение к WiFi");
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi подключен!");
        Serial.print("IP адрес: ");
        Serial.println(WiFi.localIP());
        return true;
    } else {
        Serial.println("\nОшибка подключения WiFi!");
        return false;
    }
}

bool SimpleWiFi::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

String SimpleWiFi::getIP() {
    return WiFi.localIP().toString();
}

