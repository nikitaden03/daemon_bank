#include <iostream>
#include "Parser/CParser.h"
#include "Daemon/CDaemon.h"

int main() {
    CDaemon daemon;
    daemon.parse();
    return 0;
}