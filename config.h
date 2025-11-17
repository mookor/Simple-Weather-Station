#ifndef CONFIG_H
#define CONFIG_H

// ===== НАСТРОЙКИ WiFi =====
const char* WIFI_SSID = "ВАШ_SSID";           // Имя вашей WiFi сети
const char* WIFI_PASSWORD = "ВАШ_ПАРОЛЬ";     // Пароль WiFi

// ===== НАСТРОЙКИ TELEGRAM БОТА =====
#define BOT_TOKEN "ВАШ_ТОКЕН_БОТА"  // Токен от @BotFather

// ===== НАСТРОЙКИ DHT11 =====
#define DHTPIN D3       // Пин подключения DHT11
#define DHTTYPE DHT11   // Тип датчика DHT11

// ===== НАСТРОЙКИ OLED ДИСПЛЕЯ =====
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1          // Для ESP8266 обычно используется -1
#define SCREEN_ADDRESS 0x3C    // Адрес I2C (может быть 0x3C или 0x3D)

// ===== ИНТЕРВАЛЫ ВРЕМЕНИ =====
const unsigned long READING_INTERVAL = 30000;  // 30 секунд между измерениями

#endif

