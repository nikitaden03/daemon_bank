#ifndef DAEMON_BANK_CDAEMON_H
#define DAEMON_BANK_CDAEMON_H

#include <string>
#include <map>
#include "../Parser/CParser.h"

class CDaemon {
private:
    std::map<std::string, double> sum_;
    std::map<std::string, double> counts_;
    std::map<std::string, double> median_;
    CParser parser_;

    /**
     * @brief Обновляет значения среднего и медианы на основе поученных данных
     * @param data Информация о новом курсе валюты
     */
    void update_value(std::map<std::string, double> &data);

    /**
     * @brief Записывает информацию о текущем курсе валюты в файл, чтобы в дальнейшем передать ее клиентской часте
     * @param data Информация о курсе валюты
     */
    static void share_data(std::map<std::string, double> &data);

    /**
     * @brief Уведомляет клиентскую часть, что данные обновлены
     */
    static void alarm_process();

public:
    CDaemon();

    CDaemon(CDaemon &daemon) = delete;

    ~CDaemon() = default;

    /**
     * @brief Запускает парсер каждые 10 секунд
     */
    void parse();

    CDaemon operator=(CDaemon daemon) = delete;

    /**
   * @brief Записывает информацию о среднем значение и медиане курсов валюты в файл, чтобы в дальнейшем передать ее клиентской часте
   * @param data Информация о курсе валюты
   */
    void write_measure_central_trend();
};


#endif //DAEMON_BANK_CDAEMON_H
