#include <unistd.h>
#include <iostream>

#include "CDaemon.h"

CDaemon::CDaemon() {
    sum = std::map<std::string, double>();
    median = std::map<std::string, double>();
    counts = std::map<std::string, double>();
}

void CDaemon::update_value(std::map<std::string, double> &data) {
    std::cout << "update_value START" << std::endl;
    double delta;
    for (auto &i: data) {
        if (sum.find(i.first) == sum.end()) {
            sum[i.first] = 0;
            counts[i.first] = 0;
            median[i.first] = 0;
        }
        sum[i.first] += i.second;
        counts[i.first]++;
        delta = sum[i.first] / counts[i.first] / counts[i.first];
        if (i.second < median[i.first]) median[i.first] -= delta;
        else median[i.first] += delta;
    }
    std::cout << "update_value FINISH " << counts["USD"] << std::endl;
}

std::map<std::string, double> CDaemon::get_median() {
    return median;
}

std::map<std::string, double> CDaemon::get_mean() {
    std::map<std::string, double> result(sum);
    for (auto &i : result) {
        result[i.first] /= counts[i.first];
    }
    return result;
}

void CDaemon::parse() {
    int i = 0;
    // Will work +- 50 years
    while (i <= 157680000) {
        std::map<std::string, double> answer = parser.parse();
        if (!answer.empty())
            update_value(answer);
        sleep(10);
        i++;
    }
}