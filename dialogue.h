/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <string>
#include <vector>
#include "message.h"

using namespace std;

#ifndef DIALOGUE_H
#define DIALOGUE_H

class Dialogue {
    
    friend class DialoguesCache;
    
private:
    long long int id;
    bool multiChat;
    bool readState;
    vector<int> participants;
    string title;
    vector<shared_ptr<Message>> messages;
    vector<int> readMessages;
    int lastReadMessageId = 0;
    
public:
    
    Dialogue(long long int id, bool multiChat, bool readState, vector<int> participants, string title) :
        id(id),
        multiChat(multiChat),
        readState(readState),
        participants(participants),
        title(title) {}
        
    Dialogue() {}
    
    /**
     * Идентификатор диалога.
     * @return chat_id, если это мультичат, или идентификатор пользователя в противном случае.
     */
    long long int getId() {
        return id;
    }
    
    /**
     * Проверяет, является ли данный диалог чатом 1х1 или мультичатом.
     * @return true, если это не диалог 1х1.
     */
    bool isMultiChat() {
        return multiChat;
    }
    
    /**
     * Проверяет, прочитано ли последнее сообщение из данного чата.
     * @return true, если последнее сообщение прочитано.
     */
    bool isReaden() {
        return readState;
    }
    
    /**
     * Количество пользователей в диалоге.
     * @return кол-во пользователей в диалоге.
     */
    int getSize() {
        return participants.size();
    }
    
    /**
     * Получить всех участников беседы.
     * @return вектор идентификаторов всех участников беседы.
     */
    vector<int> getParticipants() {
        return participants;
    }
    
    /**
     * Название диалога.
     * @return название диалога.
     */
    string getTitle() {
        return title;
    }
    
    /**
     * Отправить сообщение в беседу.
     * @param msg сообщение.
     */
    void sendMessage(string msg);
    
    /**
     * Отправить сообщение в беседу, сопроводив его одним или несколькими пересланными.
     * @param forwarded идентификаторы пересылаемых сообщений, разделенные запятой
     * @param msg текст сообщения.
     */
    void sendMessageForwarded(string forwarded, string msg);
    
    /**
     * Получить последние сообщения беседы.
     * @return вектор указателей последних сообщений беседы.
     */
    vector<shared_ptr<Message>> getMessages() {
        return messages;
    }
    
    /**
     * Загрузить последние сообщения беседы.
     * @param count количество сообщений.
     */
    void loadMessages(int count, int startMessageId);
    
    /**
     * Проверка, является ли сообщение прочитанным в данной сессии.
     * @param mid идентификатор сообщения
     * @return true, если сообщение было прочитано в течение данной сессии.
     */
    bool isMessageRead(int mid) {
        return find(readMessages.begin(), readMessages.end(), mid) != readMessages.end();
    }
    
    /**
     * Выводит последние полученные сообщения.
     */
    void printLastMessages();
    
    /**
     * Функция, позволяющая получить идентификатор последнего полученного сообщения из чата.
     * @return идентификатор последнего полученного (и прочитанного) сообщения из чата.
     */
    int getLastReadMessageId() {
        return lastReadMessageId;
    }
    
};

#endif /* DIALOGUE_H */

