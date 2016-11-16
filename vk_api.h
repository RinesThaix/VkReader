/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */

#ifndef VK_API_H
#define VK_API_H

#include "users_cache.h"
#include "dialogues_cache.h"
#include "async_reader.h"

class VKAPI {
    
private:
    static UsersCache users;
    static DialoguesCache dialogues;
    static AsyncReader reader;
    
public:
    
    static UsersCache& getUsers();
    
    static DialoguesCache& getDialogues();
    
    static AsyncReader& getReader();
    
    static void invalidate();
    
};

#endif /* VK_API_H */

