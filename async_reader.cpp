/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */

#include <thread>
#include "async_reader.h"
#include "global_utils.h"
#include "logger.h"

using namespace std;

void AsyncReader::init() {
    thread([&](){ process(); }).detach();
}

void AsyncReader::process() {
    while(!stopped) {
        lock.readLock();
        if(this->isDialogueSelected) {
            Dialogue& selected = this->selected;
            selected.loadMessages(25, selected.getLastReadMessageId());
            selected.printLastMessages();
        }
        lock.readUnlock();
        this_thread::sleep_for(chrono::seconds(2));
    }
}

void AsyncReader::selectDialogue(Dialogue& dialogue) {
    lock.writeLock();
    this->selected = dialogue;
    this->isDialogueSelected = true;
    lock.writeUnlock();
}

void AsyncReader::unselectDialogue() {
    lock.writeLock();
    this->isDialogueSelected = false;
    lock.writeUnlock();
}

bool AsyncReader::hasSelectedDialogue() {
    lock.readLock();
    bool result = this->isDialogueSelected;
    lock.readUnlock();
    return result;
}

Dialogue& AsyncReader::getSelectedDialogue() {
    lock.readLock();
    Dialogue& result = this->selected;
    lock.readUnlock();
    return result;
}