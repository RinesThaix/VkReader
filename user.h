/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <string>

using namespace std;

#ifndef USER_H
#define USER_H

class User {
    
    friend class UsersCache;
    
private:
    int id;
    string firstName;
    string secondName;
    short sex;
    string status;
    bool online;
    long long int lastUpdateTime;
    
public:
    
    User(int id, string firstName, string secondName, short sex, string status, bool online) {
        this->id = id;
        this->firstName = firstName;
        this->secondName = secondName;
        this->sex = sex;
        this->status = status;
        this->online = online;
        this->lastUpdateTime = time(0);
    }
    
    User() {}
    
    void update(string status, bool online) {
        this->status = status;
        this->online = online;
        this->lastUpdateTime = time(0);
    }
    
    /**
     * Идентификатор пользователя.
     * @return идентификатор пользователя.
     */
    int getId() {
        return id;
    }
    
    /**
     * Имя пользователя.
     * @return имя пользователя.
     */
    string getFirstName() {
        return firstName;
    }
    
    /**
     * Фамилия пользователя.
     * @return фамилию пользователя.
     */
    string getSecondName() {
        return secondName;
    }
    
    /**
     * Полное имя пользователя.
     * @return полное имя пользователя.
     */
    string getFullName() {
        return getFirstName() + " " + getSecondName();
    }
    
    /**
     * Проверка пола пользователя.
     * @return true, если пользователь - парень.
     */
    bool isGuy() {
        return sex == 2;
    }
    
    /**
     * Проверка пола пользователя.
     * @return true, если пользователь - девушка.
     */
    bool isGirl() {
        return sex == 1;
    }
    
    /**
     * Статус пользователя.
     * @return статус пользователя.
     */
    string getStatus() {
        return status;
    }
    
    /**
     * Проверка того, находится ли пользователь в онлайне.
     * @return true, если пользователь в онлайне.
     */
    bool isOnline() {
        return online;
    }
    
    /**
     * Время последнего обновления в кеше.
     * @return время последнего обновления в кеше.
     */
    long long int getLastUpdateTime() {
        return lastUpdateTime;
    }
    
};

#endif /* USER_H */

