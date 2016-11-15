/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */

#include "vk_api.h"


UsersCache VKAPI::users;
DialoguesCache VKAPI::dialogues;

UsersCache& VKAPI::getUsers() {
    return users;
}

DialoguesCache& VKAPI::getDialogues() {
    return dialogues;
}

void VKAPI::invalidate() {
    users.invalidateAll();
    dialogues.invalidateAll();
}