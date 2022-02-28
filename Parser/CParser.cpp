#include <curl/curl.h>

#include <iostream>

#include "CParser.h"

std::string CParser::make_request() {
    CURL *curl = curl_easy_init();

    std::string curlBuffer;

    curl_easy_setopt(curl, CURLOPT_URL, link_api.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parse_data);

    CURLcode result = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if (result != CURLE_OK) return "";
    return curlBuffer;
}

nlohmann::json CParser::parse() {
    std::string answer = make_request();
    nlohmann::json j = nlohmann::json::parse(answer);
    if (answer.compare("") == 1) j["isSuccessful"] = false;
    else j["isSuccessful"] = true;
    return j;
}

size_t CParser::parse_data(char *ptr, size_t size, size_t nmemb, std::string *data) {
    size_t result = 0;
    if (data != nullptr) {
        data->append(ptr, size * nmemb);
        result = size * nmemb;
    }
    return result;
}
