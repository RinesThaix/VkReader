/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include "json_object.h"
#include <string>
#include <curl/curl.h>
#include <rapidjson/document.h>

#ifndef JSONRETRIEVER_H
#define JSONRETRIEVER_H

class JsonRetriever {
    
public:
    
    /*
     * Returns JsonObject which represents a json, parsed from the given url
     */
    static JsonObject& parseUrlToJsonObject(JsonObject& json, std::string url);
    
};

#endif /* JSONRETRIEVER_H */

