#ifndef DAEMON_BANK_CPARSER_H
#define DAEMON_BANK_CPARSER_H

#include <string>
#include <nlohmann/json.hpp>

class CParser {
private:
    std::string link_api_ = "https://www.cbr-xml-daily.ru/latest.js";

    /**
     * @brief Совершает запрос, получает данные
     * @return Результат запроса в виде строки
     */
    std::string make_request();

    /**
     * @brief Предобрабатывает полученные данные
     * @param ptr
     * @param size
     * @param nmemb
     * @param data
     * @return
     */
    static size_t parse_data(char *ptr, size_t size, size_t nmemb, std::string *data);

public:
    /**
     * @brief Конвертирует json файл в map
     * @return Результат конвертации
     */
    std::map<std::string, double> parse();
};


#endif //DAEMON_BANK_CPARSER_H
