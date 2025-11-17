#ifndef TELEGRAM_HANDLER_H
#define TELEGRAM_HANDLER_H

#include <FastBot.h>
#include "statistics.h"

class TelegramHandler {
public:
    TelegramHandler(const char* token, Statistics* stats);
    
    // Инициализация бота
    void begin();
    
    // Обработка обновлений
    void tick();
    
    // Обработчик сообщений
    void handleMessage(FB_msg& msg);
    
    // Получение указателя на бота
    FastBot* getBot();
    
private:
    FastBot _bot;
    Statistics* _stats;
    
    // Обработчики команд
    void handleStart(FB_msg& msg);
    void handleNow(FB_msg& msg);
    void handleStats(FB_msg& msg);
    void handleReset(FB_msg& msg);
    void handleHelp(FB_msg& msg);
    void handleUnknown(FB_msg& msg);
    
    // Вспомогательные функции
    String getTempEmoji(float temp);
    String getHumEmoji(float hum);
};

#endif

