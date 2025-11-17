#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <DHT.h>

class DHTSensor {
public:
    DHTSensor(uint8_t pin, uint8_t type);
    
    // Инициализация датчика
    void begin();
    
    // Чтение данных с датчика
    bool read(float &temperature, float &humidity);
    
    // Проверка валидности последнего чтения
    bool isValid() const;
    
private:
    DHT _dht;
    bool _lastReadValid;
};

#endif

