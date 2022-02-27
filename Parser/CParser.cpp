#include <curl/curl.h>
#include <iostream>

#include "CParser.h"


void CParser::make_request() {
    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, link_api.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parse_data);

    CURLcode result = curl_easy_perform(curl);

    if (result == CURLE_COULDNT_RESOLVE_HOST) {
        std::cout << "Bad connection";
    }

    char *ct;

    result = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &ct);

    if((CURLE_OK == result) && ct) std::cout << ct;

    curl_easy_cleanup(curl);
}

void CParser::parse() {
    make_request();
}

size_t CParser::parse_data(char *ptr, size_t size, size_t nmemb, std::string *data) {
    size_t result = 0;
    if (data != nullptr) {
        data->append(ptr, size * nmemb);
        result = size * nmemb;
    }
    return result;
}
