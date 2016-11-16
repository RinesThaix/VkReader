/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include "dialogue.h"
#include "json_object.h"
#include "global_utils.h"
#include "vk_api.h"
#include <string>
#include "message.h"

void Dialogue::sendMessage(string msg) {
    GlobalUtils::sendMessageTo(isMultiChat(), getId(), msg);
}

void Dialogue::loadMessages() {
    messages.clear();
    JsonObject json, sub;
    string adder;
    if(isMultiChat())
        adder = "chat";
    else
        adder = "user";
    json.parseFromVkApi("messages.getHistory?count=25&" + adder + "_id=" + to_string(getId()));
    json.loadJsonObject(json, "response");
    messages.resize(json.getArraySize() - 1);
    vector<int> toBeLoaded;
    map<shared_ptr<Message>, int> notActuallyLoaded;
    for(int i = 1; i < json.getArraySize(); ++i) {
        json.loadJsonObject(sub, i);
        int uid = sub.getInt("uid");
        string body = sub.getString("body");
        long long int time = sub.getInt("date");
        if(!VKAPI::getUsers().contains(uid)) {
            if(find(toBeLoaded.begin(), toBeLoaded.end(), uid) == toBeLoaded.end())
                toBeLoaded.push_back(uid);
            shared_ptr<Message> message = shared_ptr<Message>(new Message(body, time));
            notActuallyLoaded.insert(make_pair(message, uid));
            messages[messages.size() - i] = message;
        }else {
            shared_ptr<Message> message = shared_ptr<Message>(new Message(VKAPI::getUsers().getCached(uid), body, time));
            messages[messages.size() - 1] = message;
        }
    }
    VKAPI::getUsers().load(toBeLoaded);
    for(auto iterator = notActuallyLoaded.begin(); iterator != notActuallyLoaded.end(); ++iterator)
        (*iterator->first.get()).sender = VKAPI::getUsers().getCached(iterator->second);
}