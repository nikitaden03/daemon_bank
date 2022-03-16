#include <iostream>
#include "csignal"
#include "MyPipe/MyPipe.h"

using namespace std;

int status = 0;

void my_handler_1([[maybe_unused]] int param) {
    static int code = 1;
    std::cout << "HELLO" << code << std::endl;
    code++;
}

void my_handler_2([[maybe_unused]] int param) {
    status = 1;
}

int main() {
    signal(SIGCONT, my_handler_1);
    signal(SIGTERM, my_handler_2);

    MyPipe cmd_pipe = MyPipe("pidof -s ~/CLionProjects/daemon_bank/daemon_bank_background/cmake-build-debug/daemon_bank_background");

    if (!cmd_pipe.getPID()) {
        system("nohup ~/CLionProjects/daemon_bank/daemon_bank_background/cmake-build-debug/daemon_bank_background &");
    }

    while (!status) {

    }

    return 0;
}
