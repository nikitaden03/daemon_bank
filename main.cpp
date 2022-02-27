#define CURL_STATICLIB
#include <iostream>
#include <nlohmann/json.hpp>
#include "Parser/CParser.h"

int main() {
    CParser parser;
    parser.parse();
    return 0;
}