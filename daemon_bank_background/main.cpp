#include <csignal>
#include "Parser/CParser.h"
#include "Daemon/CDaemon.h"
#include "MyPipe/MyPipe.h"

void my_handler([[maybe_unused]] int param) {
    MyPipe cmd_pipe = MyPipe("pidof -s ~/CLionProjects/daemon_bank/daemon_bank_user_interface/cmake-build-debug/daemon_bank_user_interface");

    if (cmd_pipe.getPID())
        kill(cmd_pipe.getPID(), SIGTERM);

    exit(0);
}

int main() {
    CDaemon daemon;

    signal(SIGTERM, my_handler);

    daemon.parse();
    return 0;
}