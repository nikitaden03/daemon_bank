#include <iostream>
#include "CLogs.h"

std::string CLogs::getDate() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    return std::to_string(1900 + ltm->tm_year) + "-" + std::to_string(ltm->tm_mon) + "-" +
           std::to_string(ltm->tm_mday) + " " +
           std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" +
           std::to_string(ltm->tm_sec);
}

void CLogs::log(Level level, const char *message) const {

    if (level >= level_) {
        std::cout << CLogs::getDate() << " " << print_information[level] << " " << message << std::endl;
    }
}

CLogs::CLogs(Level level) {
    level_ = level;
}
