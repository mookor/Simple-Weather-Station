// ===== ПОДКЛЮЧЕНИЕ МОДУЛЕЙ =====
#include "config.h"
#include "wifi_module.h"
#include "dht_sensor.h"
#include "display_manager.h"
#include "statistics.h"
#include "telegram_handler.h"

// ===== ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ =====
SimpleWiFi wifi;
DHTSensor dhtSensor(DHTPIN, DHTTYPE);
DisplayManager display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_RESET, SCREEN_ADDRESS);
Statistics stats;
TelegramHandler telegram(BOT_TOKEN, &stats);

// ===== ПЕРЕМЕННЫЕ =====
unsigned long lastReadingTime = 0;

void setup() {
  // Инициализация Serial для отладки
  Serial.begin(115200);
  Serial.println("Запуск...");
  
  // Инициализация DHT11
  dhtSensor.begin();
  
  // Инициализация OLED дисплея
  if(!display.begin()) {
    for(;;); // Остановка программы при ошибке OLED
  }
  
  // Показать сообщение инициализации
  display.showInitMessage();
  delay(2000);
  
  // Подключение к WiFi
  display.showWiFiConnecting();
  
  if (wifi.connect(WIFI_SSID, WIFI_PASSWORD)) {
    display.showWiFiConnected(wifi.getIP());
    delay(1000);
    
    // Инициализация Telegram бота
    display.showBotStarting();
    telegram.begin();
    
    display.showBotStarted();
    delay(1000);
  } else {
    display.showWiFiError();
  }
}

void loop() {
  // Обработка сообщений от Telegram бота
  telegram.tick();
  
  // Чтение данных с датчика каждые 30 секунд
  if (millis() - lastReadingTime >= READING_INTERVAL) {
    lastReadingTime = millis();
    
    float temperature, humidity;
    
    // Чтение данных с DHT11
    if (dhtSensor.read(temperature, humidity)) {
      // Успешное чтение - обновляем статистику
      stats.update(temperature, humidity);
      
      // Вывод в Serial для отладки
      Serial.print("Temperatura: ");
      Serial.print(temperature);
      Serial.print(" C, Vlazhnost': ");
      Serial.print(humidity);
      Serial.println(" %");
    } else {
      // Ошибка чтения датчика
      display.showSensorError();
      delay(2000);
    }
  }
  
  // Отображение на OLED дисплее (обновляется каждый цикл)
  display.showSensorData(
    stats.getCurrentTemp(), 
    stats.getCurrentHum(), 
    stats.getReadingsCount() > 0,
    wifi.isConnected()
  );
  
  // Небольшая задержка для стабильности
  delay(100);
}
