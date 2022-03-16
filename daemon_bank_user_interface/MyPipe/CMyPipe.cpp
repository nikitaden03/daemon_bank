#include "CMyPipe.h"

CMyPipe::CMyPipe(const std::string& path) {
    pipe_ = popen(path.c_str(), "r");
    char buf[512];
    fgets(buf, 512, pipe_);
    pid_ = (pid_t) strtoul(buf, nullptr, 10);
}

CMyPipe::~CMyPipe() {
    if (pipe_)
        pclose(pipe_);
}

FILE *CMyPipe::operator*() {
    return pipe_;
}

pid_t CMyPipe::getPID() const {
    return pid_;
}
