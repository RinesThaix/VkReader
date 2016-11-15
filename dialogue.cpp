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
    for(int i = 1; i < json.getArraySize(); ++i) {
        json.loadJsonObject(sub, i);
        int uid = sub.getInt("uid");
        if(!VKAPI::getUsers().contains(uid))
            VKAPI::getUsers().load(uid);
        Message* message = new Message(VKAPI::getUsers().getCached(uid), sub.getString("body"), sub.getInt("date"));
        messages[messages.size() - i] = *message;
    }
}