/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include "user.h"
#include <map>
#include <vector>

#ifndef USERS_CACHE_H
#define USERS_CACHE_H

class UsersCache {
    
private:
    std::map<int, User&> users;
    
public:
    
    void load(int id);
    
    void load(vector<int> ids);
    
    /**
     * Обновить пользователя в кеше.
     * @param user пользователь.
     */
    void update(User& user);
    
    bool contains(int id);
    
    /**
     * Получить закешированную версию пользователя.
     * @param id идентификатор пользователя.
     * @return объект пользователя, если он находился в кеше.
     */
    User& getCached(int id);
    
    /**
     * Удалить из кеша пользователя.
     * @param user пользователь.
     */
    void invalidate(User& user);
    
    /**
     * Полностью очистить кеш.
     */
    void invalidateAll();
    
    /**
     * Обновить всех пользователей, которые лежат в кеше без обновления слишком долго.
     */
    void updateAllOldCachedUsers();
    
};

#endif /* USERS_CACHE_H */

