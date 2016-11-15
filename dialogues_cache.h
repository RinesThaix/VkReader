/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <map>
#include "dialogue.h"

#ifndef DIALOGUES_CACHE_H
#define DIALOGUES_CACHE_H

class DialoguesCache {
    
private:
    Dialogue selectedDialogue;
    bool selDialogue = false;
    
public:
    std::map<int, Dialogue&> dialogues;
    
    void preload();
    
    void updateAll();
    
    bool contains(int id);
    
    Dialogue& getCached(int id);
    
    Dialogue& getSelectedDialogue() {
        return selectedDialogue;
    }
    
    Dialogue& selectDialogue(int idInMap);
    
    bool hasSelectedDialogue() {
        return selDialogue;
    }
    
    void invalidate(Dialogue& dialogue);
    
    void invalidate(int id);
    
    void invalidateAll();
    
};

#endif /* DIALOGUES_CACHE_H */

