/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include "users_cache.h"
#include "user.h"
#include "json_object.h"
#include <string>
#include <map>
#include <rapidjson/document.h>

using namespace std;

void UsersCache::load(int id) {
    if(contains(id)) {
        User& user = getCached(id);
        if(user.isNeedsToBeUpdated())
            update(user);
        return;
    }
    JsonObject json;
    json.parseFromVkApi("users.get?user_ids=" + to_string(id) + "&fields=status,online,sex");
    json.loadJsonObject(json, "response");
    json.loadJsonObject(json, 0);
    User* user = new User(id, json.getString("first_name"), json.getString("last_name"), (short) json.getInt("sex"), json.getString("status"), json.getBoolean("online"));
    users.insert(pair<int, User&>(id, *user));
    json.invalidate();
}

void UsersCache::load(vector<int> ids) {
    if(ids.size() == 0)
        return;
    vector<int> toBeUpdated;
    string s = "";
    for(int id : ids) {
        if(contains(id)) {
            if(getCached(id).isNeedsToBeUpdated())
                toBeUpdated.push_back(id);
            continue;
        }
        if(s.length() > 0)
            s += ",";
        s += to_string(id);
    }
    JsonObject json, sub;
    json.parseFromVkApi("users.get?user_ids=" + s + "&fields=status,online,sex");
    json.loadJsonObject(json, "response");
    for(int i = 0; i < json.getArraySize(); ++i) {
        json.loadJsonObject(sub, i);
        int id = sub.getInt("uid");
        string status = sub.contains("status") ? sub.getString("status") : "";
        User* user = new User(id, sub.getString("first_name"), sub.getString("last_name"), (short) sub.getInt("sex"), status, sub.getBoolean("online"));
        users.insert(pair<int, User&>(id, *user));
    }
    json.invalidate();
    update(toBeUpdated);
}

void UsersCache::update(User& user) {
    JsonObject json;
    json.parseFromVkApi("users.get?user_ids=" + to_string(user.getId()) + "&fields=status,online");
    json.loadJsonObject(json, "response");
    json.loadJsonObject(json, 0);
    user.online = json.getBoolean("online");
    user.status = json.getString("status");
    json.invalidate();
}

void UsersCache::update(vector<int> ids) {
    if(ids.size() == 0)
        return;
    string s = "";
    for(int id : ids) {
        if(!contains(id))
            continue;
        if(s.length() > 0)
            s += ",";
        s += to_string(id);
    }
    JsonObject json, sub;
    json.parseFromVkApi("users.get?user_ids=" + s + "&fields=status,online");
    json.loadJsonObject(json, "response");
    for(int i = 0; i < json.getArraySize(); ++i) {
        json.loadJsonObject(sub, i);
        int id = sub.getInt("uid");
        if(!contains(id))
            continue;
        User& user = getCached(id);
        user.status = sub.contains("status") ? sub.getString("status") : "";
        user.online = sub.getBoolean("online");
    }
    json.invalidate();
}

bool UsersCache::contains(int id) {
    return users.find(id) != users.end();
}

User& UsersCache::getCached(int id) {
    return users[id];
}

void UsersCache::invalidate(User& user) {
    users.erase(user.getId());
    delete &user;
}

void UsersCache::invalidateAll() {
    for(auto iterator = users.begin(); iterator != users.end(); ++iterator)
        delete &(iterator->second);
    users.clear();
}

void UsersCache::updateAllOldCachedUsers() {
    std::string ids = "";
    for(auto iterator = users.begin(); iterator != users.end(); ++iterator) {
        User& user = iterator->second;
        if(user.isNeedsToBeUpdated()) {
            if(ids.length() > 0)
                ids += ",";
            ids += to_string(user.getId());
        }
    }
    JsonObject json, sub;
    json.parseFromVkApi("users.get?user_ids=" + ids + "&fields=status,online");
    json.loadJsonObject(json, "response");
    for(int i = 0; i < json.getArraySize(); ++i) {
        json.loadJsonObject(sub, i);
        int id = sub.getInt("uid");
        if(!contains(id))
            continue;
        User& user = getCached(id);
        user.status = sub.contains("status") ? sub.getString("status") : "";
        user.online = sub.getBoolean("online");
    }
    json.invalidate();
}