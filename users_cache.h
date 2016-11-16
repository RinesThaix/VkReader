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
    
    /**
     * Загружает информацию о пользователе.
     * Если пользователь уже загружен, обновляет его, если это необходимо.
     * @param id идентификатор пользователя.
     */
    void load(int id);
    
    /**
     * Загружает информацию о пользователях.
     * Если какие-то из пользователей уже загружены, то вместо того, чтобы
     * загрузить их, обновит тех из них, для кого это необходимо.
     * @param ids вектор идентификаторов пользователей.
     */
    void load(vector<int> ids);
    
    /**
     * Обновить пользователя в кеше.
     * @param user пользователь.
     */
    void update(User& user);
    
    /**
     * Обновить пользователей в кеше.
     * @param ids вектор идентификаторов пользователей.
     */
    void update(vector<int> ids);
    
    /**
     * Проверить, находится ли пользователь в кеше.
     * @param id идентификатор пользователя.
     * @return true, если пользователь в кеше.
     */
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

