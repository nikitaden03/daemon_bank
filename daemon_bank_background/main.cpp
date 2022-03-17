#include <csignal>
#include "Parser/CParser.h"
#include "Daemon/CDaemon.h"
#include "MyPipe/CMyPipe.h"
#include "Logs/CLogs.h"

CDaemon *daemon;

/**
 * @brief Обрабатывает сигнал, отключающий программу от процесса
 * @param param
 */
void my_handler([[maybe_unused]] int param) {
    CLogs logs(LEVEL);

    CMyPipe cmd_pipe = CMyPipe("pidof -s ~/CLionProjects/daemon_bank/daemon_bank_user_interface/cmake-build-debug/daemon_bank_user_interface");

    logs.log(DEBUG, "my_handler OK");

    logs.log(DEBUG, std::to_string(cmd_pipe.getPID()).c_str());

    if (cmd_pipe.getPID()) {
        logs.log(DEBUG, "my_handler send_signal OK");
        daemon->write_measure_central_trend();
        kill(cmd_pipe.getPID(), SIGBUS);
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