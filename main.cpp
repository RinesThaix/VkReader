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
    Logger::log("Preloading information about your account..\n");
    VKAPI::getUsers().load(GlobalSettings::getMyId());
    Logger::log("Preloading dialogues..\n");
    VKAPI::getDialogues().preload();
    Logger::log("Initializing AsyncReader..\n");
    VKAPI::getReader().init();
    Logger::log("VkReader has been successfully initialized!\n");
}

void cleanup() {
    Logger::log("Shutting down everything..\n");
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
        if(args[0] == "чаты" || args[0] == "список") {
            printAllChats();
        }else if(args[0] == "выбери" || args[0] == "выбрать") {
            if(args.size() < 2) {
                error("Формат команды: вебери <номер>");
                continue;
            }
            int id = stoi(args[1]);
            Dialogue& selected = VKAPI::getDialogues().selectDialogue(id);
            if(!VKAPI::getReader().hasSelectedDialogue()) {
                error("Диалога с таким номером нет.");
                continue;
            }
            Logger::log("Вы перешли в чат '%s'\n", selected.getTitle().c_str());
        }else if(args[0] == "read") {
            if(!VKAPI::getReader().hasSelectedDialogue()) {
                error("Для начала, выберите диалог.");
                continue;
            }
            Dialogue& selected = VKAPI::getReader().getSelectedDialogue();
            selected.loadMessages(25, selected.getLastReadMessageId());
            Logger::log("Последние сообщения из '%s':\n", selected.getTitle().c_str());
            for(auto msgptr : selected.getMessages()) {
                Message message = *msgptr;
                Logger::log("%s (%s): %s\n", message.getSender().getFullName().c_str(),
                        GlobalUtils::formatTime(message.getTime()).c_str(), message.getText().c_str());
            }
        }else if(args[0] == "end" || args[0] == "пока") {
            Logger::log("Прощайте, сир.\n");
            return;
        }else if(args[0] == "chatinfo" || args[0] == "инфа" || args[0] == "информация") {
            if(!VKAPI::getReader().hasSelectedDialogue()) {
                error("Для начала, выберите диалог.");
                continue;
            }
            Dialogue& dialogue = VKAPI::getReader().getSelectedDialogue();
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
                    dialogue.getId(), dialogue.getTitle().c_str(), dialogue.getSize(), participants.c_str());
        }else if(args[0] == "debug") {
            GlobalSettings::toggleDebugMode();
            Logger::log("Debug mode toggled (:");
        }else if(args[0] == "update") {
            update();
            Logger::log("Обновляю все, что есть..\n");
        }else if(args[0] == "прикрепи" || args[0] == "перешли") {
            if(args.size() < 1) {
                error("Для написания сообщения с пересланными нужен хотя бы 1 аргумент.");
                continue;
            }
            if(!VKAPI::getReader().hasSelectedDialogue()) {
                error("Чтобы писать сообщения, необходимо выбрать диалог.");
                continue;
            }
            Dialogue& selected = VKAPI::getReader().getSelectedDialogue();
            string forwarded = args[1], message, spaced;
            for(int i = 2; i < args.size(); ++i) {
                if(message.length() > 0) {
                    message += "%20";
                    spaced += " ";
                }
                message += args[i];
                spaced += args[i];
            }
            selected.sendMessageForwarded(forwarded, message);
        }else {
            if(args.size() < 1) {
                error("Для написания сообщения нужно хотя бы 1 слово.");
                continue;
            }
            if(!VKAPI::getReader().hasSelectedDialogue()) {
                error("Чтобы писать сообщения, необходимо выбрать диалог.");
                continue;
            }
            Dialogue& selected = VKAPI::getReader().getSelectedDialogue();
            string message, spaced;
            for(int i = 0; i < args.size(); ++i) {
                if(message.length() > 0) {
                    message += "%20";
                    spaced += " ";
                }
                message += args[i];
                spaced += args[i];
            }
            selected.sendMessage(message);
        }
    }
}

int main() {
    init();
    execute();
    cleanup();
    return 0;
}