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
    static std::string getDate();

    std::vector<std::string> print_information{"DEBUG", "INFO", "WARNING", "ERROR"};
public:

    explicit CLogs(Level level);

    Level level_;

    void log(Level level, const char *message) const;
};


#endif //DAEMON_BANK_BACKGROUND_CLOGS_H
