#include <csignal>
#include "Parser/CParser.h"
#include "Daemon/CDaemon.h"
#include "MyPipe/MyPipe.h"

CDaemon *daemon;

void my_handler([[maybe_unused]] int param) {
    MyPipe cmd_pipe = MyPipe("pidof -s ~/CLionProjects/daemon_bank/daemon_bank_user_interface/cmake-build-debug/daemon_bank_user_interface");

    if (cmd_pipe.getPID()) {
        daemon->write_measure_central_trend();
        kill(cmd_pipe.getPID(), SIGTERM);
    }

    delete daemon;
    exit(0);
}

int main() {
    daemon = new CDaemon();

    signal(SIGTERM, my_handler);

    daemon->parse();

    delete daemon;
    return 0;
}