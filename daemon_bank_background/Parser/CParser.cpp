#include <curl/curl.h>

#include "CParser.h"
#include "../Date/CLogs.h"

std::string CParser::make_request() {

    CLogs logs(LEVEL);

    logs.log(INFO, "make_request START");

    CURL *curl = curl_easy_init();

    std::string curlBuffer;

    curl_easy_setopt(curl, CURLOPT_URL, link_api_.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parse_data);

    CURLcode result = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if (result != CURLE_OK) {
        logs.log(ERROR, "make_request FINISH");
        return "{}";
    }
    logs.log(INFO, "make_request FINISH OK");
    return curlBuffer;
}

std::map<std::string, double> CParser::parse() {
    std::string answer = make_request();
    nlohmann::json j = nlohmann::json::parse(answer);
    if (answer == "{}") {
        CLogs logs(LEVEL);
        logs.log(WARNING, "make_request - answer is empty");
        return {};
    }
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
