/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <string>
#include "user.h"

#ifndef MESSAGE_H
#define MESSAGE_H

class Message {
    
private:
    User sender;
    string text;
    long long int time;
    
public:
    
    Message(User& sender, string text, long long int time) {
        this->sender = sender;
        this->text = text;
        this->time = time;
    }
    
    Message() {}
    
    string getText() {
        return text;
    }
    
    User& getSender() {
        return sender;
    }
    
    long long int getTime() {
        return time;
    }
    
};

#endif /* MESSAGE_H */

