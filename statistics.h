#ifndef STATISTICS_H
#define STATISTICS_H

#include <Arduino.h>

class Statistics {
public:
    Statistics();
    
    // Обновление данных
    void update(float temperature, float humidity);
    
    // Сброс статистики
    void reset();
    
    // Получение данных
    float getCurrentTemp() const;
    float getCurrentHum() const;
    float getMinTemp() const;
    float getMaxTemp() const;
    float getMinHum() const;
    float getMaxHum() const;
    int getReadingsCount() const;
    unsigned long getUptime() const;
    
    // Форматированный вывод
    String getUptimeFormatted() const;
    
private:
    float _currentTemp;
    float _currentHum;
    float _minTemp;
    float _maxTemp;
    float _minHum;
    float _maxHum;
    int _readingsCount;
    unsigned long _sessionStart;
};

#endif

