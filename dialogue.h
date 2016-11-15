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
    vector<Message> messages;
    
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
    
    void sendMessage(string msg);
    
    vector<Message> getMessages() {
        return messages;
    }
    
    void loadMessages();
    
};

#endif /* DIALOGUE_H */

