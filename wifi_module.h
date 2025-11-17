#ifndef SIMPLE_WIFI_H
#define SIMPLE_WIFI_H

#include <ESP8266WiFi.h>

class SimpleWiFi {
public:
    SimpleWiFi();
    
    // Подключение к WiFi сети
    bool connect(const char* ssid, const char* password, int maxAttempts = 30);
    
    // Проверка подключения
    bool isConnected();
    
    // Получение IP адреса
    String getIP();
    
private:
    const char* _ssid;
    const char* _password;
};

#endif

