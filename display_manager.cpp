#include "display_manager.h"

DisplayManager::DisplayManager(uint8_t width, uint8_t height, int8_t reset, uint8_t address) 
    : _display(width, height, &Wire, reset) {
    _width = width;
    _height = height;
    _address = address;
}

bool DisplayManager::begin() {
    if(!_display.begin(SSD1306_SWITCHCAPVCC, _address)) {
        Serial.println("Ошибка инициализации OLED!");
        return false;
    }
    
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    return true;
}

void DisplayManager::showInitMessage() {
    _display.clearDisplay();
    _display.setCursor(0, 0);
    _display.println("Inicializacia...");
    _display.display();
}

void DisplayManager::showWiFiConnecting() {
    _display.clearDisplay();
    _display.setCursor(0, 0);
    _display.println("Podkluchenie");
    _display.print("k WiFi...");
    _display.display();
}

void DisplayManager::showWiFiConnected(String ip) {
    _display.clearDisplay();
    _display.setCursor(0, 0);
    _display.println("WiFi OK!");
    _display.print("IP: ");
    _display.println(ip);
    _display.display();
}

void DisplayManager::showWiFiError() {
    _display.clearDisplay();
    _display.setCursor(0, 0);
    _display.println("WiFi Error!");
    _display.display();
}

void DisplayManager::showBotStarting() {
    _display.clearDisplay();
    _display.setCursor(0, 0);
    _display.println("Zapusk bota...");
    _display.display();
}

void DisplayManager::showBotStarted() {
    _display.clearDisplay();
    _display.setCursor(0, 0);
    _display.println("Bot OK!");
    _display.display();
}

void DisplayManager::showSensorError() {
    _display.clearDisplay();
    _display.setCursor(0, 0);
    _display.setTextSize(1);
    _display.println("Oshibka chtenia");
    _display.println("s datchika!");
    _display.display();
}

void DisplayManager::showSensorData(float temperature, float humidity, bool hasData, bool wifiConnected) {
    _display.clearDisplay();
    
    // Заголовок
    _display.setTextSize(1);
    _display.setCursor(0, 0);
    _display.println("DHT11 Sensor");
    _display.println("----------------");
    
    if (hasData) {
        // Температура
        _display.setTextSize(2);
        _display.setCursor(0, 20);
        _display.print("T: ");
        _display.print(temperature, 1);
        _display.setTextSize(1);
        _display.println(" C");
        
        // Влажность
        _display.setTextSize(2);
        _display.setCursor(0, 42);
        _display.print("V: ");
        _display.print(humidity, 0);
        _display.setTextSize(1);
        _display.println(" %");
    } else {
        // Ожидание данных
        _display.setTextSize(1);
        _display.setCursor(0, 30);
        _display.println("Ozhidanie...");
    }
    
    // Индикаторы в правом верхнем углу
    _display.setCursor(100, 0);
    if (wifiConnected) {
        _display.print("W");  // WiFi
    }
    _display.setCursor(110, 0);
    _display.print("T");  // Telegram
    
    _display.display();
}

