#ifndef DAEMON_BANK_CPARSER_H
#define DAEMON_BANK_CPARSER_H

#include <string>
#include <nlohmann/json.hpp>

class CParser {
private:
    std::string link_api_ = "https://www.cbr-xml-daily.ru/latest.js";

    std::string make_request();

    static size_t parse_data(char *ptr, size_t size, size_t nmemb, std::string *data);

public:
    std::map<std::string, double> parse();
};


#endif //DAEMON_BANK_CPARSER_H
