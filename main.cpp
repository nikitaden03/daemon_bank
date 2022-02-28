#define CURL_STATICLIB
#include <iostream>
#include "Parser/CParser.h"

int main() {
    CParser parser;
    parser.parse();
    return 0;
}