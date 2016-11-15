/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include "json_retriever.h"
#include "json_object.h"
#include "rapidjson/document.h"
#include "global_settings.h"
#include <iostream>
#include "logger.h"

using namespace std;
using namespace rapidjson;

size_t writeStdString(void* contents, size_t size, size_t nmemb, string *s) {
    size_t newlen = size * nmemb, oldlen = s->size();
    try {
        s->resize(oldlen + newlen);
    }catch(bad_alloc &e) {
        return 0;
    }
    copy((char*) contents, (char*) contents + newlen, s->begin() + oldlen);
    return size * nmemb;
}

string openCurl(string address) {
    CURL* curl = curl_easy_init();
    string result;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeStdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        if(curl_easy_perform(curl) != CURLE_OK)
            Logger::fatal("Something is wrong with curl o_O\n");
        curl_easy_cleanup(curl);
    }
    if(GlobalSettings::isInDebugMode())
        Logger::debug("Got in answer: %s\n", result.c_str());
    return result;
}

JsonObject& JsonRetriever::parseUrlToJsonObject(JsonObject& json, string url) {
    string s = openCurl(url);
    json.parseFromString(s);
    return json;
}