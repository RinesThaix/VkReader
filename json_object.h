/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <string>
#include <iostream>
#include <rapidjson/document.h>

#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

using namespace std;
using namespace rapidjson;

class JsonObject {
    
    friend class JsonRetriever;
    
private:
    Value* json;
    
public:
    
    /**
     * Parses json from the given url into usable instance of that class
     * @param url a link to the page, which consists of data in json-format
     */
    void parseFromUrl(string url);
    
    void parseFromVkApi(string method);
    
    /**
     * Loads given jsonObject as a sub-json of current one
     * @param jsonObject json to be loaded
     * @param name the name of current json's field
     */
    JsonObject& loadJsonObject(JsonObject& jsonObject, string name);
    
    JsonObject& loadJsonObject(JsonObject& jsonObject, int id);
    
    void parseFromString(string json);
    
    bool contains(string name);
    
    string getString(string name);
    
    int getInt(string name);
    
    long long int getLong(string name);
    
    double getDouble(string name);
    
    bool getBoolean(string name);
    
    template <typename T>
    T get(string name);
    
    int getArraySize();
    
    Value* getHandle();
    
    void invalidate() {
        
    }
    
};

#endif /* JSON_OBJECT_H */

