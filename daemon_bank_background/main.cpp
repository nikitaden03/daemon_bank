#include <csignal>
#include "Parser/CParser.h"
#include "Daemon/CDaemon.h"
#include "MyPipe/CMyPipe.h"
#include "Date/CLogs.h"

CDaemon *daemon;

void my_handler([[maybe_unused]] int param) {
    CLogs logs(LEVEL);

    CMyPipe cmd_pipe = CMyPipe("pidof -s ~/CLionProjects/daemon_bank/daemon_bank_user_interface/cmake-build-debug/daemon_bank_user_interface");

    logs.log(DEBUG, "my_handler OK");

    if (cmd_pipe.getPID()) {
        daemon->write_measure_central_trend();
        kill(cmd_pipe.getPID(), SIGSTOP);
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