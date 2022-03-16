#include <unistd.h>
#include <iostream>
#include <csignal>

#include "CDaemon.h"
#include "../MyPipe/MyPipe.h"

CDaemon::CDaemon() {
    sum_ = std::map<std::string, double>();
    median_ = std::map<std::string, double>();
    counts_ = std::map<std::string, double>();
}

void CDaemon::update_value(std::map<std::string, double> &data) {
    std::cout << "update_value START" << std::endl;
    double delta;
    for (auto &i: data) {
        if (sum_.find(i.first) == sum_.end()) {
            sum_[i.first] = 0;
            counts_[i.first] = 0;
            median_[i.first] = 0;
        }
        sum_[i.first] += i.second;
        counts_[i.first]++;
        delta = sum_[i.first] / counts_[i.first] / counts_[i.first];
        if (i.second < median_[i.first]) median_[i.first] -= delta;
        else median_[i.first] += delta;
    }

    alarm_process();

    std::cout << "update_value FINISH " << counts_["USD"] << std::endl;
}

std::map<std::string, double> CDaemon::get_median() {
    return median_;
}

std::map<std::string, double> CDaemon::get_mean() {
    std::map<std::string, double> result(sum_);
    for (auto &i : result) {
        result[i.first] /= counts_[i.first];
    }
    return result;
}

void CDaemon::parse() {
    int i = 0;
    // Will work +- 50 years
    while (i <= 157680000) {
        std::map<std::string, double> answer = parser_.parse();
        if (!answer.empty())
            update_value(answer);
        sleep(10);
        i++;
    }
}

void CDaemon::alarm_process() {
    MyPipe cmd_pipe = MyPipe("pidof -s ~/CLionProjects/daemon_bank/daemon_bank_user_interface/cmake-build-debug/daemon_bank_user_interface");

    if (cmd_pipe.getPID()) {
        kill(cmd_pipe.getPID(), SIGCONT);
        std::cout << "send_signal SUCCESSFUL " << std::endl;
        return;
    }
    std::cout << "send_signal BAD " << std::endl;
}
