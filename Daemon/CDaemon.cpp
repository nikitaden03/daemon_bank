#include "CDaemon.h"

void CDaemon::update_value(std::map<std::string, double> &data) {
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
}

std::map<std::string, double> CDaemon::get_median() {
    return median;
}

std::map<std::string, double> CDaemon::get_mean() {
    std::map<std::string, double> result(sum);
    for (auto &i : result) {
        result[i.first] /= counts[i.first];
    }
}
