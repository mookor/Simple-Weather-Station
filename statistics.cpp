#include "statistics.h"

Statistics::Statistics() {
    reset();
}

void Statistics::update(float temperature, float humidity) {
    _currentTemp = temperature;
    _currentHum = humidity;
    _readingsCount++;
    
    // Обновление минимумов и максимумов
    if (_readingsCount == 1) {
        // Первое измерение - инициализируем мин/макс
        _minTemp = temperature;
        _maxTemp = temperature;
        _minHum = humidity;
        _maxHum = humidity;
    } else {
        // Последующие измерения - обновляем мин/макс
        if (temperature < _minTemp) _minTemp = temperature;
        if (temperature > _maxTemp) _maxTemp = temperature;
        if (humidity < _minHum) _minHum = humidity;
        if (humidity > _maxHum) _maxHum = humidity;
    }
}

void Statistics::reset() {
    _currentTemp = 0.0;
    _currentHum = 0.0;
    _minTemp = 999.0;
    _maxTemp = -999.0;
    _minHum = 999.0;
    _maxHum = -999.0;
    _readingsCount = 0;
    _sessionStart = millis();
}

float Statistics::getCurrentTemp() const {
    return _currentTemp;
}

float Statistics::getCurrentHum() const {
    return _currentHum;
}

float Statistics::getMinTemp() const {
    return _minTemp;
}

float Statistics::getMaxTemp() const {
    return _maxTemp;
}

float Statistics::getMinHum() const {
    return _minHum;
}

float Statistics::getMaxHum() const {
    return _maxHum;
}

int Statistics::getReadingsCount() const {
    return _readingsCount;
}

unsigned long Statistics::getUptime() const {
    return (millis() - _sessionStart) / 1000;
}

String Statistics::getUptimeFormatted() const {
    unsigned long uptime = getUptime();
    int hours = uptime / 3600;
    int minutes = (uptime % 3600) / 60;
    return String(hours) + "ч " + String(minutes) + "мин";
}

