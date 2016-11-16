/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include "logger.h"
#include "json_object.h"
#include "rapidjson/document.h"
#include "json_retriever.h"
#include "global_settings.h"
#include "rapidjson/error/en.h"

using namespace std;
using namespace rapidjson;

Value& getValue(Value* value, string name) {
    return (*value)[name.c_str()];
}

Value& getValue(Value* value, int id) {
    return (*value)[id];
}

void JsonObject::parseFromUrl(string url) {
    if(GlobalSettings::isInDebugMode())
        Logger::debug("Parsing from %s\n", url.c_str());
    JsonRetriever::parseUrlToJsonObject(*this, url);
}

void JsonObject::parseFromVkApi(string method) {
    method = "https://api.vk.com/method/" + method + "&access_token=" + GlobalSettings::getToken();
    return parseFromUrl(method);
}

void JsonObject::parseFromString(string s) {
    Document* d = new Document();
    if(d->Parse(s.c_str()).HasParseError()) {
        fprintf(stderr, "String is: '%s'\nError(offset %u): %s\n", 
                s.c_str(),
                (unsigned)d->GetErrorOffset(),
                GetParseError_En(d->GetParseError())
        );
    }
    this->json = d;
}

bool JsonObject::contains(string name) {
    return (*json).FindMember(name.c_str()) != (*json).MemberEnd();
}

string JsonObject::getString(string name) {
    return getValue(json, name).GetString();
}

int JsonObject::getInt(string name) {
    return getValue(json, name).GetInt();
}

double JsonObject::getDouble(string name) {
    return getValue(json, name).GetDouble();
}

bool JsonObject::getBoolean(string name) {
    return getValue(json, name).GetInt() == 1;
}

template <typename T>
T JsonObject::get(string name) {
    return getValue(json, name).Get<T>();
}

Value* JsonObject::getHandle() {
    return json;
}

JsonObject& JsonObject::loadJsonObject(JsonObject& jsonObject, string name) {
    jsonObject.json = &getValue(json, name);
    return jsonObject;
}

JsonObject& JsonObject::loadJsonObject(JsonObject& jsonObject, int id) {
    jsonObject.json = &getValue(json, id);
    return jsonObject;
}

int JsonObject::getArraySize() {
    return (*json).Size();
}
