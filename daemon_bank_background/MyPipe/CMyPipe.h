#ifndef DAEMON_BANK_BACKGROUND_CMYPIPE_H
#define DAEMON_BANK_BACKGROUND_CMYPIPE_H

#include <cstdio>
#include <string>

class CMyPipe {

private:
    FILE *pipe_;
    pid_t pid_;

public:
    virtual ~CMyPipe();

    FILE *operator*();

    explicit CMyPipe(const std::string &path);

    [[nodiscard]] pid_t getPID() const;
};


#endif //DAEMON_BANK_BACKGROUND_CMYPIPE_H
