#ifndef DAEMON_BANK_CPARSER_H
#define DAEMON_BANK_CPARSER_H

#include <string>

class CParser {
private:
    std::string link_api = "https://www.cbr-xml-daily.ru/latest.js";

    std::string curlBuffer;

    void make_request();

    static size_t parse_data(char *ptr, size_t size, size_t nmemb, std::string *data);

public:
    void parse();
};


#endif //DAEMON_BANK_CPARSER_H
