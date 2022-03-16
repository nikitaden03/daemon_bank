#include <curl/curl.h>
#include <iostream>

#include "CParser.h"

std::string CParser::make_request() {

    std::cout << "make_request START" << std::endl;

    CURL *curl = curl_easy_init();

    std::string curlBuffer;

    curl_easy_setopt(curl, CURLOPT_URL, link_api_.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parse_data);

    CURLcode result = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if (result != CURLE_OK) {
        std::cout << "make_request FINISH ERROR" << std::endl;
        return "{}";
    }
    std::cout << "make_request FINISH OK" << std::endl;
    return curlBuffer;
}

std::map<std::string, double> CParser::parse() {
    std::string answer = make_request();
    nlohmann::json j = nlohmann::json::parse(answer);
    if (answer == "{}") return {};
    else return std::map<std::string, double>(j["rates"]);
}

size_t CParser::parse_data(char *ptr, size_t size, size_t nmemb, std::string *data) {
    size_t result = 0;
    if (data != nullptr) {
        data->append(ptr, size * nmemb);
        result = size * nmemb;
    }
    return result;
}
