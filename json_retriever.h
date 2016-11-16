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
    
    /**
     * Пропарсить Json с указанной ссылки.
     * @param json объект JsonObject, куда записать результат.
     * @param url ссылка, по которой находится искомая информация в формате json.
     * @return ссылку на переданный json-объект.
     */
    static JsonObject& parseUrlToJsonObject(JsonObject& json, std::string url);
    
};

#endif /* JSONRETRIEVER_H */

