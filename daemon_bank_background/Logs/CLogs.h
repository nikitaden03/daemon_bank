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

    explicit CLogs(Level level);

    CLogs(CLogs& logs) = delete;

    Level level_;

    void log(Level level, const char *message) const;

    CLogs &operator=(CLogs logs) = delete;

    static std::string getDate();
};


#endif //DAEMON_BANK_BACKGROUND_CLOGS_H
