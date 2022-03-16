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

    void update_value(std::map<std::string, double> &data);

    static void alarm_process();

public:
    CDaemon();

    CDaemon(CDaemon &daemon) = delete;

    ~CDaemon() = default;

    void parse();

    CDaemon operator=(CDaemon daemon) = delete;

    std::map<std::string, double> get_median();

    std::map<std::string, double> get_mean();
};


#endif //DAEMON_BANK_CDAEMON_H
