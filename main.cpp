/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <string>
#include <iostream>
#include "json_retriever.h"
#include "json_object.h"
#include "global_settings.h"
#include "users_cache.h"
#include "dialogues_cache.h"
#include "global_utils.h"
#include "dialogue.h"
#include "logger.h"
#include "vk_api.h"
#include "message.h"

using namespace rapidjson;
using namespace std;

void init() {
    Logger::log("Initializing CURL..\n");
    curl_global_init(CURL_GLOBAL_DEFAULT);
    Logger::log("Preloading settings..\n");
    GlobalSettings::preloadSettings();
    Logger::log("Loading self-info..\n");
    VKAPI::getUsers().load(GlobalSettings::getMyId());
    VKAPI::getDialogues().preload();
}

void cleanup() {
    VKAPI::invalidate();
    curl_global_cleanup();
}

void error(string msg) {
    Logger::log("Ошибка: %s\n", msg.c_str());
}

void printAllChats() {
    Logger::log("Список всех чатов:\n");
    int visibleId = 0;
    for(auto iterator = VKAPI::getDialogues().dialogues.begin(); iterator != VKAPI::getDialogues().dialogues.end(); ++iterator) {
        Dialogue& dialogue = iterator->second;
        Logger::log("%d. %s (%s)\n", ++visibleId, dialogue.getTitle().c_str(), dialogue.isReaden() ? "нет новых" : "есть новые");
    }
}

void update() {
    VKAPI::getUsers().updateAllOldCachedUsers();
    VKAPI::getDialogues().updateAll();
}

void execute() {
    Logger::log("Вводите команды, сир:\n");
    string cmd;
    while(true) {
        getline(cin, cmd);
        if(cmd.length() == 0)
            continue;
        vector<string> args = GlobalUtils::split(cmd, ' ');
        if(args[0] == "listchats") {
            printAllChats();
        }else if(args[0] == "select") {
            if(args.size() < 2) {
                error("Формат команды: select <номер>");
                continue;
            }
            int id = stoi(args[1]);
            Dialogue& selected = VKAPI::getDialogues().selectDialogue(id);
            if(!VKAPI::getDialogues().hasSelectedDialogue()) {
                error("Диалога с таким номером нет.");
                continue;
            }
            Logger::log("Вы перешли в чат '%s'\n", selected.getTitle().c_str());
        }else if(args[0] == "send") {
            if(args.size() < 2) {
                error("Формат команды: send <сообщение>");
                continue;
            }
            if(!VKAPI::getDialogues().hasSelectedDialogue()) {
                error("Для начала, выберите диалог.");
                continue;
            }
            Dialogue& selected = VKAPI::getDialogues().getSelectedDialogue();
            string message, spaced;
            for(int i = 1; i < args.size(); ++i) {
                if(message.length() > 0) {
                    message += "%20";
                    spaced += " ";
                }
                message += args[i];
                spaced += args[i];
            }
            selected.sendMessage(message);
            Logger::log("Вы отправили сообщение '%s' в чат '%s'\n", spaced.c_str(), selected.getTitle().c_str());
        }else if(args[0] == "read") {
            if(!VKAPI::getDialogues().hasSelectedDialogue()) {
                error("Для начала, выберите диалог.");
                continue;
            }
            Dialogue& selected = VKAPI::getDialogues().getSelectedDialogue();
            selected.loadMessages();
            Logger::log("Последние сообщения из '%s':\n", selected.getTitle().c_str());
            for(Message message : selected.getMessages()) {
                Logger::log("%s (%s): %s\n", message.getSender().getFullName().c_str(),
                        GlobalUtils::formatTime(message.getTime()).c_str(), message.getText().c_str());
            }
        }else if(args[0] == "end") {
            return;
        }else if(args[0] == "chatinfo") {
            if(args.size() < 2) {
                error("Формат команды: chatinfo <id чата>");
                continue;
            }
            int id = stoi(args[1]);
            if(id > 0) {
                error("Эту команду нельзя применять к общим чатам.");
                continue;
            }
            id = -id;
            if(!VKAPI::getDialogues().contains(id)) {
                error("Этот чат отсутствует в кеше.");
                continue;
            }
            Dialogue& dialogue = VKAPI::getDialogues().getCached(id);
            VKAPI::getUsers().load(dialogue.getParticipants());
            VKAPI::getUsers().updateAllOldCachedUsers();
            string participants = "";
            for(int participant : dialogue.getParticipants()) {
                if(participants.length() > 0)
                    participants += ", ";
                participants += VKAPI::getUsers().getCached(participant).getFullName();
            }
            participants += ".";
            Logger::log("Информация о чате с номером %d:\nНазвание: '%s'\nРазмер: %d\nСписок участников: %s\n",
                    id, dialogue.getTitle().c_str(), dialogue.getSize(), participants.c_str());
        }else if(args[0] == "debug") {
            GlobalSettings::toggleDebugMode();
            Logger::log("Debug mode toggled (:");
        }else if(args[0] == "update") {
            update();
            Logger::log("Обновляю все, что есть..");
        }
    }
}

int main() {
    init();
    execute();
    cleanup();
    return 0;
}