#include "dht_sensor.h"

DHTSensor::DHTSensor(uint8_t pin, uint8_t type) : _dht(pin, type) {
    _lastReadValid = false;
}

void DHTSensor::begin() {
    _dht.begin();
}

bool DHTSensor::read(float &temperature, float &humidity) {
    humidity = _dht.readHumidity();
    temperature = _dht.readTemperature();
    
    // Проверка корректности чтения
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Ошибка чтения с DHT11!");
        _lastReadValid = false;
        return false;
    }
    
    _lastReadValid = true;
    return true;
}

bool DHTSensor::isValid() const {
    return _lastReadValid;
}

