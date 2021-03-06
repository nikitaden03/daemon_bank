#include <iostream>
#include <fstream>
#include <cstring>
#include "csignal"
#include "MyPipe/CMyPipe.h"

using namespace std;

int status = 0;
int flag = 0;

/**
 * @brief Обновляет информацию о валютах, полученную демоном
 */
void print_data() {
    ifstream file;
    file.open("../../data.txt");
    std::cout << "\x1B[2J\x1B[H";
    std::string str1, str_help;
    double str2;
    file >> str1 >> str_help;
    cout << "Последнее обновление в " << str1 << " " << str_help << std::endl;
    for (int i = 0; i < 34; i++) {
        file >> str1 >> str2;
        std::cout << str1 << " - " << 1 / str2 << std::endl;
    }
    file.close();
}

/**
 * @brief Выводит среднее и медиану валют
 */
void print_result() {
    ifstream file;
    file.open("../../data.txt");
    std::string str1;
    double str2;
    std::cout << "Средние значения:" << std::endl;
    for (int i = 0; i < 34; i++) {
        file >> str1 >> str2;
        std::cout << str1 << " - " << 1 / str2 << std::endl;
    }
    std::cout << "Медианы значений:" << std::endl;
    for (int i = 0; i < 34; i++) {
        file >> str1 >> str2;
        std::cout << str1 << " - " << 1 / str2 << std::endl;
    }
    file.close();
}

/**
 * @brief Обрабатывает сигнал, полученный от демона, указывающий на необходимость обновить дату
 * @param param
 */
void my_handler_1([[maybe_unused]] int param) {
    print_data();
}

/**
 * @brief Обрабатывает сигнал, о прекращение работы программы
 * @param param
 */
void my_handler_2([[maybe_unused]] int param) {
    std::cout << 3 << flag << 3;
    if (flag) {
        CMyPipe cmd_pipe = CMyPipe("pidof -s ~/CLionProjects/daemon_bank/daemon_bank_background/cmake-build-debug/daemon_bank_background");
        if (cmd_pipe.getPID()) {
            kill(cmd_pipe.getPID(), SIGTERM);
        } else status = 1;
    } else status = 1;
}

/**
 * @brief Обрабатывает сигнал, полученный от демона, в случае его смерти
 * @param param
 */
void my_handler_3([[maybe_unused]] int param) {
    print_result();
    status = 1;
    exit(0);
}

int main(int argc, char * argv[]) {
    signal(SIGCONT, my_handler_1);
    signal(SIGTERM, my_handler_2);
    signal(SIGINT, my_handler_2);
    signal(SIGBUS, my_handler_3);

    if (argc >= 3) {
        fprintf(stderr, "Вы передали слишком много вргументов!");
        exit(0);
    } else if (argc == 2 && (std::strcmp(argv[1], "-c") == 0)) {
        flag = 1;
    } else if (argc != 1){
        std::cout << "Вы передали неправильный флаг!";
        exit(0);
    }

    CMyPipe cmd_pipe = CMyPipe("pidof -s ~/CLionProjects/daemon_bank/daemon_bank_background/cmake-build-debug/daemon_bank_background");

    if (!cmd_pipe.getPID()) {
        system("nohup ~/CLionProjects/daemon_bank/daemon_bank_background/cmake-build-debug/daemon_bank_background &");
    } else {
        print_data();
    }

    while (!status) {}

    return 0;
}
