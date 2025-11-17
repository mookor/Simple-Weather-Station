#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class DisplayManager {
public:
    DisplayManager(uint8_t width, uint8_t height, int8_t reset, uint8_t address);
    
    // Инициализация дисплея
    bool begin();
    
    // Показать сообщение инициализации
    void showInitMessage();
    
    // Показать сообщение подключения к WiFi
    void showWiFiConnecting();
    
    // Показать успешное подключение к WiFi
    void showWiFiConnected(String ip);
    
    // Показать ошибку WiFi
    void showWiFiError();
    
    // Показать запуск бота
    void showBotStarting();
    
    // Показать успешный запуск бота
    void showBotStarted();
    
    // Показать ошибку чтения датчика
    void showSensorError();
    
    // Показать данные датчика
    void showSensorData(float temperature, float humidity, bool hasData, bool wifiConnected);
    
private:
    Adafruit_SSD1306 _display;
    uint8_t _width;
    uint8_t _height;
    uint8_t _address;
};

#endif

