#include "MyPipe.h"

MyPipe::MyPipe(const std::string& path) {
    pipe_ = popen(path.c_str(), "r");
    char buf[512];
    fgets(buf, 512, pipe_);
    pid_ = (pid_t) strtoul(buf, nullptr, 10);
}

MyPipe::~MyPipe() {
    if (pipe_)
        pclose(pipe_);
}

FILE *MyPipe::operator*() {
    return pipe_;
}

pid_t MyPipe::getPID() const {
    return pid_;
}
