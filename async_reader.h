/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */

#ifndef ASYNC_READER_H
#define ASYNC_READER_H

#include "readwrite_lock.h"
#include <atomic>
#include "dialogue.h"

class AsyncReader {
    
private:
    ReadWriteLock lock;
    atomic<bool> stopped;
    Dialogue selected;
    bool isDialogueSelected;
    
    void process();
    
public:
    
    void init();
    
    void stop() {
        stopped = true;
    }
    
    void selectDialogue(Dialogue& dialogue);
    
    void unselectDialogue();
    
    bool hasSelectedDialogue();
    
    Dialogue& getSelectedDialogue();
    
};

#endif /* ASYNC_READER_H */

