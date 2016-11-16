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
#include "logger.h"

void Dialogue::sendMessage(string msg) {
    GlobalUtils::sendMessageTo(isMultiChat(), getId(), msg);
}

void Dialogue::loadMessages(int count, int startMessageId) {
    messages.clear();
    JsonObject json, sub;
    string adder;
    if(isMultiChat())
        adder = "chat";
    else
        adder = "user";
    string smi = startMessageId > 0 ? "&start_message_id=" + to_string(startMessageId) : "";
    json.parseFromVkApi("messages.getHistory?count=" + to_string(count) + "&" + adder + "_id=" + to_string(getId()) + smi);
    json.loadJsonObject(json, "response");
    messages.resize(json.getArraySize() - 1);
    vector<int> toBeLoaded;
    map<shared_ptr<Message>, int> notActuallyLoaded;
    for(int i = 1; i < json.getArraySize(); ++i) {
        json.loadJsonObject(sub, i);
        int mid = sub.getInt("mid");
        if(isMessageRead(mid))
            continue;
        if(mid > lastReadMessageId)
            lastReadMessageId = mid;
        readMessages.push_back(mid);
        int uid = sub.getInt("uid");
        string body = sub.getString("body");
        long long int time = sub.getInt("date");
        if(!VKAPI::getUsers().contains(uid)) {
            if(find(toBeLoaded.begin(), toBeLoaded.end(), uid) == toBeLoaded.end())
                toBeLoaded.push_back(uid);
            shared_ptr<Message> message = shared_ptr<Message>(new Message(mid, body, time));
            notActuallyLoaded.insert(make_pair(message, uid));
            messages[messages.size() - i] = message;
        }else {
            shared_ptr<Message> message = shared_ptr<Message>(new Message(mid, VKAPI::getUsers().getCached(uid), body, time));
            messages[messages.size() - i] = message;
        }
    }
    messages.erase(remove(messages.begin(), messages.end(), nullptr), messages.end());
    VKAPI::getUsers().load(toBeLoaded);
    for(auto iterator = notActuallyLoaded.begin(); iterator != notActuallyLoaded.end(); ++iterator)
        (*iterator->first.get()).sender = VKAPI::getUsers().getCached(iterator->second);
}

void Dialogue::printLastMessages() {
    if(getMessages().size() == 0)
        return;
    for(auto msgptr : getMessages()) {
        Message message = *msgptr;
        Logger::log("%s (%s): %s\n",
                message.getSender().getFullName().c_str(),
                GlobalUtils::formatTime(message.getTime()).c_str(),
                message.getText().c_str()
        );
    }
}