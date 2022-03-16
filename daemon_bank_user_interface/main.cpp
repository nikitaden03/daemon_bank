#include <iostream>
#include <fstream>
#include "csignal"
#include "MyPipe/CMyPipe.h"

using namespace std;

int status = 0;

void print_data() {
    ifstream file;
    file.open("../../data.txt");
    std::cout << "\x1B[2J\x1B[H";
    static int s = 0;
    std::string str1, str2;
    cout << s << std::endl;
    s++;
    for (int i = 0; i < 34; i++) {
        file >> str1 >> str2;
        std::cout << str1 << " - " << str2 << std::endl;
    }
    file.close();
}

void print_result() {
    ifstream file;
    file.open("../../data.txt");
    std::string str1, str2;
    std::cout << "Средние значения:" << std::endl;
    for (int i = 0; i < 34; i++) {
        file >> str1 >> str2;
        std::cout << str1 << " - " << str2 << std::endl;
    }
    std::cout << "Медианы значений:" << std::endl;
    for (int i = 0; i < 34; i++) {
        file >> str1 >> str2;
        std::cout << str1 << " - " << str2 << std::endl;
    }
    file.close();
}

void my_handler_1([[maybe_unused]] int param) {
    print_data();
}

void my_handler_2([[maybe_unused]] int param) {
    status = 1;
}

void my_handler_3([[maybe_unused]] int param) {
    print_result();
    status = 1;
}

int main() {
    signal(SIGCONT, my_handler_1);
    signal(SIGTERM, my_handler_2);
    signal(SIGSTOP, my_handler_3);

    CMyPipe cmd_pipe = CMyPipe("pidof -s ~/CLionProjects/daemon_bank/daemon_bank_background/cmake-build-debug/daemon_bank_background");

    if (!cmd_pipe.getPID()) {
        system("nohup ~/CLionProjects/daemon_bank/daemon_bank_background/cmake-build-debug/daemon_bank_background &");
    } else {
        print_data();
    }

    while (!status) {}

    return 0;
}
