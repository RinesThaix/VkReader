/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <string>
#include "user.h"

#ifndef MESSAGE_H
#define MESSAGE_H

class Message {
    
    friend class Dialogue;
    
private:
    int mid;
    User sender;
    string text;
    long long int time;
    
public:
    
    Message(int mid, User& sender, string text, long long int time) {
        this->mid = mid;
        this->sender = sender;
        this->text = text;
        this->time = time;
    }
    
    Message(int mid, string text, long long int time) {
        this->mid = mid;
        this->text = text;
        this->time = time;
    }
    
    Message() {}
    
    int getId() {
        return mid;
    }
    
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

