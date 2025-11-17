#include "telegram_handler.h"

// Глобальный указатель для статического обработчика
static TelegramHandler* handlerInstance = nullptr;

// Статический обработчик для FastBot
static void staticMessageHandler(FB_msg& msg) {
    if (handlerInstance != nullptr) {
        handlerInstance->handleMessage(msg);
    }
}

TelegramHandler::TelegramHandler(const char* token, Statistics* stats) 
    : _bot(token), _stats(stats) {
    handlerInstance = this;
}

void TelegramHandler::begin() {
    _bot.attach(staticMessageHandler);
    _bot.skipUpdates();
    Serial.println("Telegram бот запущен!");
}

void TelegramHandler::tick() {
    _bot.tick();
}

FastBot* TelegramHandler::getBot() {
    return &_bot;
}

void TelegramHandler::handleMessage(FB_msg& msg) {
    Serial.print("Получено сообщение: ");
    Serial.println(msg.text);
    
    if (msg.text == "/start") {
        handleStart(msg);
    } else if (msg.text == "/now") {
        handleNow(msg);
    } else if (msg.text == "/stats") {
        handleStats(msg);
    } else if (msg.text == "/reset") {
        handleReset(msg);
    } else if (msg.text == "/help") {
        handleHelp(msg);
    } else {
        handleUnknown(msg);
    }
}

void TelegramHandler::handleStart(FB_msg& msg) {
    String welcome = "🌡️ *Привет!*\n\n";
    welcome += "Я бот датчика DHT11 на WEMOS D1 Mini\n\n";
    welcome += "*Доступные команды:*\n";
    welcome += "/now - Текущие показания\n";
    welcome += "/stats - Статистика за сессию\n";
    welcome += "/reset - Сброс статистики\n";
    welcome += "/help - Справка";
    
    _bot.sendMessage(welcome, msg.chatID);
}

void TelegramHandler::handleNow(FB_msg& msg) {
    if (_stats->getReadingsCount() == 0) {
        _bot.sendMessage("⏳ Ожидание данных...\nДатчик еще не снял показания", msg.chatID);
        return;
    }
    
    float currentTemp = _stats->getCurrentTemp();
    float currentHum = _stats->getCurrentHum();
    
    String message = "📊 *Текущие показания*\n\n";
    
    String tempEmoji = getTempEmoji(currentTemp);
    String humEmoji = getHumEmoji(currentHum);
    
    message += tempEmoji + " *Температура:* " + String(currentTemp, 1) + "°C\n";
    message += humEmoji + " *Влажность:* " + String(currentHum, 0) + "%\n";
    
    _bot.sendMessage(message, msg.chatID);
}

void TelegramHandler::handleStats(FB_msg& msg) {
    if (_stats->getReadingsCount() == 0) {
        _bot.sendMessage("📊 Нет данных для статистики", msg.chatID);
        return;
    }
    
    String message = "📉 *Статистика за сессию*\n\n";
    message += "⏱️ *Время работы:* " + _stats->getUptimeFormatted() + "\n";
    message += "📊 *Измерений:* " + String(_stats->getReadingsCount()) + "\n\n";
    
    message += "🌡️ *ТЕМПЕРАТУРА*\n";
    message += "├─ Текущая: " + String(_stats->getCurrentTemp(), 1) + "°C\n";
    message += "├─ Минимум: " + String(_stats->getMinTemp(), 1) + "°C\n";
    message += "└─ Максимум: " + String(_stats->getMaxTemp(), 1) + "°C\n\n";
    
    message += "💧 *ВЛАЖНОСТЬ*\n";
    message += "├─ Текущая: " + String(_stats->getCurrentHum(), 0) + "%\n";
    message += "├─ Минимум: " + String(_stats->getMinHum(), 0) + "%\n";
    message += "└─ Максимум: " + String(_stats->getMaxHum(), 0) + "%";
    
    _bot.sendMessage(message, msg.chatID);
}

void TelegramHandler::handleReset(FB_msg& msg) {
    _stats->reset();
    _bot.sendMessage("✅ Статистика сброшена", msg.chatID);
}

void TelegramHandler::handleHelp(FB_msg& msg) {
    String help = "ℹ️ *Справка*\n\n";
    help += "*О системе:*\n";
    help += "• Датчик: DHT11\n";
    help += "• Контроллер: WEMOS D1 Mini (ESP8266)\n";
    help += "• Дисплей: OLED 128x64\n";
    help += "• Интервал: 30 секунд\n\n";
    help += "*Команды:*\n";
    help += "/now - Показания сейчас\n";
    help += "/stats - Статистика\n";
    help += "/reset - Сброс статистики\n";
    help += "/help - Эта справка";
    
    _bot.sendMessage(help, msg.chatID);
}

void TelegramHandler::handleUnknown(FB_msg& msg) {
    _bot.sendMessage("❓ Неизвестная команда\nИспользуйте /help", msg.chatID);
}

String TelegramHandler::getTempEmoji(float temp) {
    if (temp < 15) return "❄️";
    else if (temp > 25) return "🔥";
    else return "🌤️";
}

String TelegramHandler::getHumEmoji(float hum) {
    if (hum < 30) return "🏜️";
    else if (hum > 60) return "💦";
    else return "💧";
}

