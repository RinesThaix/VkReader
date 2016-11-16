/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */

#include "vk_api.h"


UsersCache VKAPI::users;
DialoguesCache VKAPI::dialogues;
AsyncReader VKAPI::reader;

UsersCache& VKAPI::getUsers() {
    return users;
}

DialoguesCache& VKAPI::getDialogues() {
    return dialogues;
}

AsyncReader& VKAPI::getReader() {
    return reader;
}

void VKAPI::invalidate() {
    users.invalidateAll();
    dialogues.invalidateAll();
    reader.stop();
}