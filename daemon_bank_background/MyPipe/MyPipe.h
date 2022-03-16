#ifndef DAEMON_BANK_BACKGROUND_MYPIPE_H
#define DAEMON_BANK_BACKGROUND_MYPIPE_H

#include <cstdio>
#include <string>

class MyPipe {

private:
    FILE *pipe_;
    pid_t pid_;

public:
    virtual ~MyPipe();

    FILE *operator*();

    explicit MyPipe(const std::string &path);

    [[nodiscard]] pid_t getPID() const;
};


#endif //DAEMON_BANK_BACKGROUND_MYPIPE_H
