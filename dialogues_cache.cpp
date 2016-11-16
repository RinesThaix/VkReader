/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include "json_object.h"
#include "dialogues_cache.h"
#include "dialogue.h"
#include "global_settings.h"
#include "global_utils.h"
#include "vk_api.h"
#include <map>
#include <vector>
#include <string>
#include "logger.h"

using namespace std;

void DialoguesCache::preload() {
    Logger::log("Preloading DialoguesCache..\n");
    vector<int> usersToPreload;
    JsonObject json, sub;
    json.parseFromVkApi("messages.getDialogs?count=20");
    json.loadJsonObject(json, "response");
    for(int i = 1; i < json.getArraySize(); ++i) {
        json.loadJsonObject(sub, i);
        bool mc = sub.contains("admin_id");
        int users, id;
        string title;
        vector<int> participants;
        if(mc) {
            if(!sub.contains("users_count"))
                continue;
            users = sub.getInt("users_count");
            id = sub.getInt("chat_id");
            title = sub.getString("title");
            vector<string> split = GlobalUtils::split(sub.getString("chat_active"), ',');
            for(string s : split)
                participants.push_back(stoi(s));
        }else {
            users = 2;
            id = sub.getInt("uid");
            title = "";
            if(!VKAPI::getUsers().contains(id))
                usersToPreload.push_back(id);
            participants.push_back(id);
            participants.push_back(GlobalSettings::getMyId());
        }
        Dialogue* dialogue = new Dialogue(id, mc, sub.getBoolean("read_state"), participants, title);
        dialogues.insert(pair<long long int, Dialogue&>(id, *dialogue));
    }
    VKAPI::getUsers().load(usersToPreload);
    VKAPI::getUsers().updateAllOldCachedUsers();
    for(int i : usersToPreload)
        dialogues[i].title = VKAPI::getUsers().getCached(i).getFullName();
    json.invalidate();
    Logger::log("Successfully preloaded.\n");
}

void DialoguesCache::updateAll() {
    invalidateAll();
    preload();
}

bool DialoguesCache::contains(int id) {
    return dialogues.find(id) != dialogues.end();
}

Dialogue& DialoguesCache::getCached(int id) {
    return dialogues[id];
}

void DialoguesCache::invalidate(Dialogue& dialogue) {
    dialogues.erase(dialogue.getId());
    delete &dialogue;
}

void DialoguesCache::invalidate(int id) {
    Dialogue& dialogue = dialogues[id];
    dialogues.erase(id);
    delete &dialogue;
}

void DialoguesCache::invalidateAll() {
    for(auto iterator = dialogues.begin(); iterator != dialogues.end(); ++iterator)
        delete &(iterator->second);
    dialogues.clear();
}

Dialogue& DialoguesCache::selectDialogue(int idInMap) {
    int left = idInMap;
    for(auto iterator = dialogues.begin(); iterator != dialogues.end(); ++iterator)
        if(--left == 0) {
            Dialogue& result = iterator->second;
            VKAPI::getReader().selectDialogue(result);
            return result;
        }
    VKAPI::getReader().unselectDialogue();
    return *(Dialogue*) nullptr;
}