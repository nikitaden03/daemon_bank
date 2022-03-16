#include <unistd.h>
#include <iostream>
#include <csignal>
#include <fstream>

#include "CDaemon.h"
#include "../MyPipe/CMyPipe.h"
#include "../Date/CLogs.h"

CDaemon::CDaemon() {
    sum_ = std::map<std::string, double>();
    median_ = std::map<std::string, double>();
    counts_ = std::map<std::string, double>();
}

void CDaemon::update_value(std::map<std::string, double> &data) {
    CLogs logs(LEVEL);
    logs.log(INFO, "update_value START");
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

    logs.log(INFO, "update_value FINISH");
}

void CDaemon::parse() {
    int i = 0;
    // Will work +- 50 years
    while (i <= 157680000) {
        std::map<std::string, double> answer = parser_.parse();
        if (!answer.empty()) {
            update_value(answer);
            share_data(answer);
        }
        sleep(10);
        i++;
    }
}

void CDaemon::alarm_process() {
    CLogs logs(LEVEL);
    CMyPipe cmd_pipe = CMyPipe(
            "pidof -s ~/CLionProjects/daemon_bank/daemon_bank_user_interface/cmake-build-debug/daemon_bank_user_interface");

    if (cmd_pipe.getPID()) {
        kill(cmd_pipe.getPID(), SIGCONT);
        logs.log(INFO, "send_signal SUCCESSFUL");
        return;
    }
    logs.log(WARNING, "send_signal BAD");
}

void CDaemon::share_data(std::map<std::string, double> &data) {
    std::ofstream file;
    file.open("../../data.txt");

    for (auto &i: data) {
        file << i.first << " " << i.second << " ";
    }

    file.close();
    alarm_process();
}

void CDaemon::write_measure_central_trend() {
    std::ofstream file;
    file.open("../../data.txt");

    for (auto &i: sum_) {
        file << i.first << " " << i.second / counts_[i.first] << " ";
    }

    for (auto &i: median_) {
        file << i.first << " " << i.second << " ";
    }

    file.close();
}
