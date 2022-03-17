#ifndef DAEMON_BANK_BACKGROUND_CLOGS_H
#define DAEMON_BANK_BACKGROUND_CLOGS_H

#include <string>
#include <vector>

#define LEVEL DEBUG

enum Level {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
};

class CLogs {
    std::vector<std::string> print_information{"DEBUG", "INFO", "WARNING", "ERROR"};
public:

    Level level_;

    explicit CLogs(Level level);

    CLogs(CLogs& logs) = delete;

    /**
     * @brief Печатает сообщение в лог файл
     * @param level Уровень важности сообщения
     * @param message Текст сообщения
     */
    void log(Level level, const char *message) const;

    CLogs &operator=(CLogs logs) = delete;

    /**
     * @return Возвращает дату в формате YYYY:MM:DD HH:MM:SS
     */
    static std::string getDate();
};


#endif //DAEMON_BANK_BACKGROUND_CLOGS_H
